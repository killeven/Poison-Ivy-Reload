unit UnitClientContext;

interface
uses
  Winapi.Windows, System.SysUtils, System.Classes, System.SyncObjs, diocp_tcp_server, UnitRC4, SimpleMsgPack,
  Vcl.ComCtrls, UnitGlobal;

type
  TClientMessage = class
    cmd: TCOMMAND;
    buffer: TMemoryStream;
  end;

  TClientContext = class(TIocpClientContext)
  private
    FBuffer: TMemoryStream;
    FSendSBox: TRC4_SBOX;
    FRecvSBox: TRC4_SBOX;
    FSendLock: TCriticalSection;
    FIsReceiveBody: Boolean;
    FPacketHeader: TPROTO_HEADER;
    FThumbnail_Index: Integer;
    FImage_Index: Integer;
    FOperateForm: Pointer;
  protected
    procedure DoCleanUp; override;
    procedure OnRecvBuffer(buf: Pointer; len: Cardinal; ErrCode: WORD); override;
    procedure OnDisconnected; override;
    procedure OnConnected; override;
    procedure ProcessPacket();
    procedure ProcessMsg(var ms: TMemoryStream);
    procedure ShrinkBuffer(size: SIZE_T);
    procedure AddLog(s: string);
  public
    constructor Create(); override;
    destructor Destroy(); override;
    procedure SendCmd(cmd: TCOMMAND; data: Pointer; size: SIZE_T); overload;
    procedure SendCmd(cmd: TCOMMAND); overload;
    procedure SendPing();
  public
    property Thumbnail_Index: Integer read FThumbnail_Index write FThumbnail_Index;
    property Image_Index: Integer read FImage_Index write FImage_Index;
    property OperateForm: Pointer read FOperateForm write FOperateForm;
  end;

implementation
uses
  FormMain, UnitCompress;

{ TClientContext }

procedure TClientContext.AddLog(s: string);
begin
  SendMessage(MainForm.Handle, WM_ADD_STATS, 0, Integer(s));
end;

constructor TClientContext.Create();
begin
  inherited Create;
  FBuffer := TMemoryStream.Create;
  FSendLock := TCriticalSection.Create;
  Data := nil;
  FOperateForm := nil;
end;

destructor TClientContext.Destroy;
begin
  FreeAndNil(FBuffer);
  FreeAndNil(FSendLock);
  inherited Destroy;
end;

procedure TClientContext.DoCleanUp;
begin
  FBuffer.Clear;
  Self.Data := nil;
  Self.FOperateForm := nil;
  inherited DoCleanUp;
end;

procedure TClientContext.OnConnected;
begin
  // 因为池的原因，并不是每个都会调用create，所以把初始化key写在connect事件里
  rc4_init(FSendSBox, PByte(PAnsiChar(g_Password)), Length(g_Password));
  rc4_init(FRecvSBox, PByte(PAnsiChar(g_Password)), Length(g_Password));
  FImage_Index := -1;
  FThumbnail_Index := -1;
  FIsReceiveBody := False;

  g_TotalAttempts := g_TotalAttempts + 1;
  SendMessage(MainForm.Handle, WM_CONNECTED, Integer(Self), 0);
end;

procedure TClientContext.OnDisconnected;
begin
  SendMessage(MainForm.Handle, WM_DISCONNECTED, Integer(Self), 0);
end;

procedure TClientContext.OnRecvBuffer(buf: Pointer; len: Cardinal;
  ErrCode: WORD);
begin
  FBuffer.Write(buf, len);
  ProcessPacket;
end;

procedure TClientContext.ProcessMsg(var ms: TMemoryStream);
var
  client_message: TClientMessage;
begin
  // 统计
  g_Recv_UnCompressed := g_Recv_UnCompressed + SizeOf(TPROTO_HEADER);
  if (ms <> nil) then g_Recv_UnCompressed := g_Recv_UnCompressed + ms.Size;

  client_message := TClientMessage.Create;
  client_message.cmd := TCOMMAND(FPacketHeader.cmd);
  client_message.buffer := ms;

  if (client_message.cmd = CMD_LOGIN_INFO) then
  begin
    g_TotalConnections := g_TotalConnections + 1;
  end;

  SendMessage(MainForm.Handle, WM_CLIENT_MESSAGE, Integer(Self), Integer(client_message));

  FreeAndNil(client_message);
  FreeAndNil(ms);
end;

procedure TClientContext.ProcessPacket();
var
  ms: TMemoryStream;
  data: Pointer;
begin
  while True do
  begin
    if (not FIsReceiveBody) then
    begin
      if (FBuffer.Size < SizeOf(TPROTO_HEADER)) then Exit;

      FPacketHeader := PPROTO_HEADER(FBuffer.Memory)^;
      rc4_crypt(FRecvSBox, @FPacketHeader, SizeOf(FPacketHeader));

      if (FPacketHeader.signature <> PACKET_HEADER_SIGNATURE) then
      begin
        PostWSACloseRequest();
        AddLog(Format('bad signature = 0x%X.', [FPacketHeader.signature]));
        Exit;
      end;

      if (FPacketHeader.packet_size = 0) then
      begin
        ms := nil;
        ProcessMsg(ms);
        ShrinkBuffer(SizeOf(TPROTO_HEADER));
        FIsReceiveBody := False;
      end else
        FIsReceiveBody := True;
    end;

    if (FBuffer.Size < FPacketHeader.packet_size + SizeOf(TPROTO_HEADER)) then Exit;

    data := Pointer(PAnsiChar(FBuffer.Memory) + SizeOf(TPROTO_HEADER));
    rc4_crypt(FRecvSBox, data, FPacketHeader.packet_size);

    ms := TMemoryStream.Create;
    try
      ms.SetSize(FPacketHeader.packet_unpacked_size);
      if (FPacketHeader.packet_unpacked_size <> FPacketHeader.packet_size) then
      begin
        if (not decompress(data, FPacketHeader.packet_size, ms.Memory, FPacketHeader.packet_unpacked_size)) then
        begin
          PostWSACloseRequest;
          AddLog('decompress error');
          Exit;
        end;
      end else
      begin
        ms.Write(data, FPacketHeader.packet_size);
      end;

      ShrinkBuffer(FPacketHeader.packet_size + SizeOf(TPROTO_HEADER));

      FIsReceiveBody := False;
      ms.Seek(0, soBeginning);
      ProcessMsg(ms);
    finally
      FreeAndNil(ms);
    end;
  end;
end;

procedure TClientContext.SendCmd(cmd: TCOMMAND; data: Pointer; size: SIZE_T);
var
  send_buf: TBytes;
  buf: Pointer;
  ph: PPROTO_HEADER;
  compressed_size: DWORD;
begin
  // 统计
  g_Sent_UnCompressed := g_Sent_UnCompressed + size + SizeOf(TPROTO_HEADER);

  SetLength(send_buf, size + SizeOf(TPROTO_HEADER));

  ph := PPROTO_HEADER(send_buf);
  buf := Pointer(PByte(send_buf) + SizeOf(TPROTO_HEADER));

  ph^.random := Random(GetTickCount());
  ph^.signature := PACKET_HEADER_SIGNATURE;
  ph^.cmd := uint8(cmd);
  ph^.packet_unpacked_size := size;

  if (size >= MIN_COMPRESS_DATA_SIZE) then
  begin
    compressed_size := compress(data, size, buf, size);
  end else
  begin
    compressed_size := size;
    CopyMemory(buf, data, size);
  end;

  ph^.packet_size := compressed_size;

  FSendLock.Enter;
  rc4_crypt(FSendSBox, Pointer(ph), SizeOf(TPROTO_HEADER));
  rc4_crypt(FSendSBox, buf, compressed_size);
  PostWSASendRequest(send_buf, SizeOf(TPROTO_HEADER) + compressed_size);
  FSendLock.Leave;
end;

procedure TClientContext.SendCmd(cmd: TCOMMAND);
var
  ph: TPROTO_HEADER;
begin
  // 统计
  g_Sent_UnCompressed := g_Sent_UnCompressed + SizeOf(TPROTO_HEADER);

  ZeroMemory(@ph, SizeOf(TPROTO_HEADER));
  ph.random := Random(GetTickCount());
  ph.signature := PACKET_HEADER_SIGNATURE;
  ph.cmd := uint8(cmd);

  FSendLock.Enter;
  rc4_crypt(FSendSBox, @ph, SizeOf(TPROTO_HEADER));
  PostWSASendRequest(@ph, SizeOf(TPROTO_HEADER));
  FSendLock.Leave;
end;

procedure TClientContext.SendPing;
var
  tick: DWORD;
begin
  tick := GetTickCount;
  SendCmd(CMD_PING, @tick, SizeOf(tick));
end;

procedure TClientContext.ShrinkBuffer(size: SIZE_T);
begin
  if (FBuffer.Size > size) then
  begin
    CopyMemory(FBuffer.Memory, PAnsiChar(FBuffer.Memory) + size, FBuffer.Size - size);
    FBuffer.SetSize(FBuffer.Size - size);
  end else
  begin
    FBuffer.Clear;
  end;
end;

end.
