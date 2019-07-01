unit UnitRC4;

interface

type
  PRC4_SBOX = ^TRC4_SBOX;
  TRC4_SBOX = array [0..255] of Byte;

procedure rc4_init(var sbox: TRC4_SBOX; key: PByte; key_len: Cardinal);
procedure rc4_crypt(var sbox: TRC4_SBOX; data: Pointer; data_len: Cardinal);

implementation

procedure rc4_init(var sbox: TRC4_SBOX; key: PByte; key_len: Cardinal);
var
  k: array [0..255] of Byte;
  i, j: Cardinal;
  temp: Byte;
begin
  for i := 0 to 255 do
  begin
    sbox[i] := i;
    k[i] := key[i mod key_len];
  end;

  j := 0;
  for i := 0 to 255 do
  begin
    j := (j + sbox[i] + k[i]) mod 256;
    temp := sbox[i];
    sbox[i] := sbox[j];
    sbox[j] := temp;
  end;
end;

procedure rc4_crypt(var sbox: TRC4_SBOX; data: Pointer; data_len: Cardinal);
var
  i, j, k, t: Cardinal;
  temp: Byte;
  d: PByte;
begin
  d := PByte(data);
  i := 0;
  j := 0;
  for k := 0 to data_len - 1 do
  begin
    i := (i + 1) mod 256;
    j := (j + sbox[i]) mod 256;
    temp := sbox[i];
    sbox[i] := sbox[j];
    sbox[j] := temp;
    t := (sbox[i] + sbox[j]) mod 256;
    d[k] := d[k] xor sbox[t];
  end;
end;

end.
