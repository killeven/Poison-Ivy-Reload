unit UnitCommon;

interface
uses
  Winapi.Windows, System.SysUtils, System.StrUtils, System.Types;

function GetAccType(i: Integer): string;
function SizeToStr(Size: int64): string;
function GetVersion(ver: DWORD): string;
function GetOsVersion(v: string): string;

implementation

function GetAccType(i: Integer): string;
begin
  if i = 0 then
    Result := 'Direct'
  else
    Result := 'Socks5';
end;

function SizeToStr(Size: int64): string;
const
  K = int64(1024);
  M = K * K;
  G = K * M;
  T = K * G;
begin
  if size < K then
    Result := Format('%d bytes', [size])
  else if size < M then
    Result := Format('%f KB', [size / K])
  else if size < G then
    Result := Format('%f MB', [size / M])
  else if size < T then
    Result := Format('%f GB', [size / G])
  else
    Result := Format('%f TB', [size / T]);
end;

function GetVersion(ver: DWORD): string;
begin
  Result := IntToStr(ver and $f);
  Result := IntToStr(ver and $f0 shr 4) + '.' + Result;
  Result := IntToStr(ver and $f00 shr 8) + '.' + Result;
end;

function GetOsVersion(v: string): string;
var
  strs: TStringDynArray;
begin
  Result := 'Unknow';

  strs := SplitString(v, '.');
  if (Length(strs) <> 4) then Exit;

  if (strs[0] = '5') then
  begin
    if (strs[1] = '0') then
    begin
      Result := 'Win2000';
    end else
    if (strs[1] = '1') then
    begin
      Result := 'WinXP';
    end else
    if (strs[1] = '2') then
    begin
      Result := 'Win2003';
    end else
    begin
      Result := 'Unknow ' + strs[0] + '.' + strs[1];
    end;
  end else
  if (strs[0] = '6') then
  begin
    if (strs[1] = '0') then
    begin
      Result := 'WinVista'
    end else
    if (strs[1] = '1') then
    begin
      Result := 'Win7'
    end else
    if (strs[1] = '2') then
    begin
      Result := 'Win8'
    end else
    if (strs[1] = '3') then
    begin
      Result := 'Win8.1'
    end else
    begin
      Result := 'Unknow ' + strs[0] + '.' + strs[1];
    end;
  end else
  if (strs[0] = '10') then
  begin
    Result := 'Win10';
  end else
  begin
    Result := 'WinNT';
  end;

  Result := Result + ' Build(' + strs[2] + ')';
end;

end.
