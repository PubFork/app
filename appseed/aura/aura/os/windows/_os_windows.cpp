#include "framework.h"

#include <fcntl.h>
#include <VersionHelpers.h>
#undef new
#define min MIN
#define max MAX
#include <gdiplus.h>
#undef min
#undef max
#define new AURA_NEW
#include <ddeml.h>
#include <share.h>
#include <io.h>
#include <process.h>
#include <Winsvc.h>


#include "windows_ansi_file.cpp"
#include "windows_application.cpp"
#include "windows_aura.cpp"
#include "windows_debug.cpp"
#include "windows_dll.cpp"
#include "windows_error.cpp"
#include "windows_file.cpp"
#include "windows_file_watcher.cpp"
#include "windows_gdi.cpp"
#include "windows_gdi_cursor.cpp"
#include "windows_gdi_icon.cpp"
#include "windows_graphics.cpp"
#include "windows_internal.cpp"
#include "windows_ipc.cpp"
#include "windows_launcher.cpp"
#include "windows_library.cpp"
#include "windows_local_memory_map.cpp"
#include "windows_lock.cpp"
#include "windows_main.cpp"
#include "windows_message_loop.cpp"
#include "windows_multithreading.cpp"
#include "windows_process.cpp"
#include "windows_process_env_reader.cpp"
#include "windows_registry.cpp"
#include "windows_serial.cpp"
#include "windows_simple_app.cpp"
#include "windows_simple_shell_launcher.cpp"
#include "windows_small_ipc_channel.cpp"
#include "windows_system_interaction_impl.cpp"
#include "windows_time.cpp"
#include "windows_user.cpp"
#include "windows_util.cpp"
#include "windows_utils.cpp"
#include "windows_window_buffer.cpp"
#include "windows_windowing.cpp"



