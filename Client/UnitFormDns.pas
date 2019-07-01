unit UnitFormDns;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.StdCtrls, Vcl.ExtCtrls, Vcl.ComCtrls,
  Vcl.Samples.Spin, Vcl.Menus, System.ImageList, Vcl.ImgList,
  System.Win.ScktComp, System.StrUtils, Winapi.WinSock;

type
  TDnsForm = class(TForm)
    Panel_1: TPanel;
    Label_SizeLeft: TLabel;
    Button_1: TButton;
    Button_2: TButton;
    Button_3: TButton;
    ListView_Dns: TListView;
    Panel_Edit: TPanel;
    Edit_DNS: TEdit;
    SpinEdit_Port: TSpinEdit;
    Label_1: TLabel;
    Label_2: TLabel;
    PopupMenu_1: TPopupMenu;
    MenuItem_Add1: TMenuItem;
    MenuItem_Delete1: TMenuItem;
    MenuItem_Edit1: TMenuItem;
    Button_4: TButton;
    Button_5: TButton;
    ImageList_1: TImageList;
    MenuItem_SaveToFile1: TMenuItem;
    MenuItem_LoadFromFile1: TMenuItem;
    ClientSocket1: TClientSocket;
    procedure FormShow(Sender: TObject);
    procedure MenuItem_Add1Click(Sender: TObject);
    procedure Button_4Click(Sender: TObject);
    procedure Button_5Click(Sender: TObject);
    procedure PopupMenu_1Popup(Sender: TObject);
    procedure MenuItem_Delete1Click(Sender: TObject);
    procedure MenuItem_Edit1Click(Sender: TObject);
    procedure Button_1Click(Sender: TObject);
    procedure ClientSocket1Error(Sender: TObject; Socket: TCustomWinSocket;
      ErrorEvent: TErrorEvent; var ErrorCode: Integer);
    procedure Button_2Click(Sender: TObject);
    procedure Button_3Click(Sender: TObject);
  private
    { Private declarations }
    IsEdit: Boolean;
    ItemIndex: Integer;
    BytesLeft: Integer;
    procedure SwitchToEdit(b: Boolean);
  public
    { Public declarations }
    procedure LoadFromString(s: string);
    function DNSList(): string;
  end;

var
  DnsForm: TDnsForm;

implementation

{$R *.dfm}

procedure TDnsForm.Button_1Click(Sender: TObject);
var
  i: Integer;
  t: DWORD;
begin
  for i := 0 to ListView_Dns.Items.Count - 1 do
  begin
    try
      ClientSocket1.Address := ListView_Dns.Items[i].Caption;
      ClientSocket1.Port := StrToInt(ListView_Dns.Items[i].SubItems[0]);
      ClientSocket1.Active := True;
      ListView_Dns.Items[i].ImageIndex := 4;
      ClientSocket1.Active := False;
    except
      ListView_Dns.Items[i].ImageIndex := 3;
    end;
    Application.ProcessMessages;
  end;
end;

procedure TDnsForm.Button_2Click(Sender: TObject);
begin
  ModalResult := mrOk;
end;

procedure TDnsForm.Button_3Click(Sender: TObject);
begin
  ModalResult := mrCancel;
end;

procedure TDnsForm.Button_4Click(Sender: TObject);
begin
  if Edit_DNS.Text = '' then
  begin
    MessageBox(Handle, 'Dns is empty', 'error', MB_ICONERROR or MB_OK);
    Exit;
  end;

  if IsEdit then
  begin
    if BytesLeft < Length(Edit_DNS.Text) - Length(Caption) then
    begin
      MessageBox(Handle, 'buf not enough', 'error', MB_ICONERROR or MB_OK);
      Exit;
    end;
    BytesLeft := BytesLeft - (Length(Edit_DNS.Text) - Length(Caption));

    with ListView_Dns.Items[ItemIndex] do
    begin
      Caption := Edit_DNS.Text;
      SubItems[0] := IntToStr(SpinEdit_Port.Value);
      ImageIndex := -1;
      Update;
    end;
  end else
  begin
    if BytesLeft < Length(Edit_DNS.Text) + 5 then
    begin
      MessageBox(Handle, 'buf not enough', 'error', MB_ICONERROR or MB_OK);
      Exit;
    end;
    BytesLeft := BytesLeft - Length(Edit_DNS.Text) - 3;

    ListView_Dns.Items.BeginUpdate;
    with ListView_Dns.Items.Add do
    begin
      Caption := Edit_DNS.Text;
      SubItems.Add(IntToStr(SpinEdit_Port.Value));
      ImageIndex := -1;
    end;
    ListView_Dns.Items.EndUpdate;
  end;

  Label_SizeLeft.Caption := Format('Size Left: %d', [BytesLeft]);
  SwitchToEdit(False);
end;

procedure TDnsForm.Button_5Click(Sender: TObject);
begin
  SwitchToEdit(False);
end;

procedure TDnsForm.ClientSocket1Error(Sender: TObject; Socket: TCustomWinSocket;
  ErrorEvent: TErrorEvent; var ErrorCode: Integer);
begin
  ErrorCode := 0;
end;

function TDnsForm.DNSList: string;
var
  i: Integer;
  sl: TStringList;
begin
  sl := TStringList.Create;
  try
    for i := 0 to ListView_Dns.Items.Count - 1 do
    begin
      sl.Add(ListView_Dns.Items[i].Caption + ':' + ListView_Dns.Items[i].SubItems[0]);
    end;
    sl.Delimiter := ',';
    Result := sl.DelimitedText;
  finally
    FreeAndNil(sl);
  end;
end;

procedure TDnsForm.FormShow(Sender: TObject);
begin
  SwitchToEdit(False);
end;

procedure TDnsForm.LoadFromString(s: string);
var
  sl, sl2: TStringList;
  i: Integer;
begin
  BytesLeft := 255;
  ListView_Dns.Clear;

  if s <> '' then
  begin
    sl := TStringList.Create;
    sl2 := TStringList.Create;
    try
      sl.Delimiter := ',';
      sl.DelimitedText := s;

      for i := 0 to sl.Count - 1 do
      begin
        sl2.Delimiter := ':';
        sl2.DelimitedText := sl.Strings[i];
        with ListView_Dns.Items.Add do
        begin
          Caption := sl2.Strings[0];
          SubItems.Add(sl2.Strings[1]);
          ImageIndex := -1;
          BytesLeft := BytesLeft - Length(Caption) - 3;
        end;
      end;
    finally
      FreeAndNil(sl);
      FreeAndNil(sl2);
    end;
  end;

  Label_SizeLeft.Caption := Format('Size Left: %d', [BytesLeft]);
  ShowModal;
end;

procedure TDnsForm.MenuItem_Add1Click(Sender: TObject);
begin
  IsEdit := False;
  SwitchToEdit(True);
end;

procedure TDnsForm.MenuItem_Delete1Click(Sender: TObject);
begin
  ListView_Dns.DeleteSelected;
end;

procedure TDnsForm.MenuItem_Edit1Click(Sender: TObject);
begin
  ItemIndex := ListView_Dns.Selected.Index;
  IsEdit := True;
  Edit_DNS.Text := ListView_Dns.Selected.Caption;
  SpinEdit_Port.Value := StrToInt(ListView_Dns.Selected.SubItems[0]);
  SwitchToEdit(True);
end;

procedure TDnsForm.PopupMenu_1Popup(Sender: TObject);
begin
  MenuItem_Delete1.Enabled := ListView_Dns.Selected <> nil;
  MenuItem_Edit1.Enabled := ListView_Dns.Selected <> nil;
end;

procedure TDnsForm.SwitchToEdit(b: Boolean);
begin
  if b then
  begin
    if not IsEdit then
    begin
      Edit_DNS.Text := '';
      SpinEdit_Port.Value := 0;
    end;

    ListView_Dns.Align := alNone;
    ListView_Dns.Visible := False;

    Panel_1.Align := alNone;
    Panel_1.Visible := False;

    Panel_Edit.Align := alClient;
    Panel_Edit.Visible := True;
  end else
  begin
    ListView_Dns.Align := alClient;
    ListView_Dns.Visible := True;

    Panel_1.Align := alBottom;
    Panel_1.Visible := True;

    Panel_Edit.Align := alNone;
    Panel_Edit.Visible := False;
  end;
end;

end.
