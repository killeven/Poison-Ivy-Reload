{
  使用ntdll函数压缩
  使用COMPRESSION_ENGINE_MAXIMUM那个压缩速度简直无法直视
}
unit UnitCompress;

interface
uses
  Winapi.Windows;

function compress(src: Pointer; src_len: DWORD; dest: Pointer; dest_len: DWORD): DWORD;
function decompress(src: Pointer; src_len: DWORD; dest: Pointer; dest_len: DWORD): Boolean;

implementation
const
  COMPRESSION_FORMAT_DEFAULT = $0001;
  COMPRESSION_FORMAT_LZNT1 = $0002;
  COMPRESSION_ENGINE_MAXIMUM = $0100;
  COMPRESSION_ENGINE_STANDARD = $0000;

function RtlGetCompressionWorkSpaceSize(CompressionFormatAndEngine: USHORT;
  var CompressBufferWorkSpaceSize: ULONG; var CompressFragmentWorkSpaceSize: ULONG): LONG; stdcall;
 external 'ntdll.dll' name 'RtlGetCompressionWorkSpaceSize';

function RtlCompressBuffer(CompressionFormatAndEngine: USHORT;
  UncompressedBuffer: Pointer; UncompressedBufferSize: ULONG;
  CompressedBuffer: Pointer; CompressedBufferSize: ULONG; UncompressedChunkSize: ULONG;
  var FinalCompressedSize: ULONG; WorkSpace: Pointer): LONG; stdcall;
 external 'ntdll.dll' name 'RtlCompressBuffer';

function RtlDecompressBuffer(CompressionFormat: USHORT; UncompressedBuffer: Pointer; UncompressedBufferSize: ULONG;
  CompressedBuffer: Pointer; CompressedBufferSize: ULONG; var FinalUncompressedSize: ULONG): LONG; stdcall;
    external 'ntdll.dll' name 'RtlDecompressBuffer';

function compress(src: Pointer; src_len: DWORD; dest: Pointer; dest_len: DWORD): DWORD;
var
  compressWorkSpaceSize, compressFragmentSpaceSize, compressedSize: ULONG;
  workmemory: Pointer;
begin
  Result := 0;
  if (RtlGetCompressionWorkSpaceSize(COMPRESSION_FORMAT_LZNT1 or COMPRESSION_ENGINE_STANDARD,
    compressWorkSpaceSize, compressFragmentSpaceSize) < 0) then Exit;
  workmemory := GetMemory(compressWorkSpaceSize);
  if (RtlCompressBuffer(COMPRESSION_FORMAT_LZNT1 or COMPRESSION_ENGINE_STANDARD,
    src, src_len, dest, dest_len, 0, compressedSize, workmemory) >= 0) then
  begin
    Result := compressedSize;
  end;
  FreeMemory(workmemory);
end;

function decompress(src: Pointer; src_len: DWORD; dest: Pointer; dest_len: DWORD): Boolean;
var
  ret: LONG;
  final_len: DWORD;
begin
  Result := True;
  ret := RtlDecompressBuffer(COMPRESSION_FORMAT_LZNT1 or COMPRESSION_ENGINE_STANDARD,
    dest, dest_len, src, src_len, final_len);
  if ((ret < 0) or (final_len <> dest_len)) then Result := False;
end;

end.
