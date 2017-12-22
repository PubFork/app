#pragma once


#ifdef __cplusplus

CLASS_DECL_AURA void defer_dock_application(bool bDock);

#endif

BEGIN_EXTERN_C
CLASS_DECL_AURA WINBOOL IsProcessRunning(DWORD pid);
END_EXTERN_C


#include "os_threading.h"

#include "cross.h"

/*
#if _POSIX_C_SOURCE == 200809L
#error "Only for test!! Good error!! _POSIX_C_SOURCE still 200809L"
#endf
*/


#ifdef cplusplus

inline bool IsDirSep(WCHAR ch);



#endif

CLASS_DECL_AURA void set_splash(oswindow oswindow);
CLASS_DECL_AURA oswindow get_splash();

CLASS_DECL_AURA int get_processor_count();

CLASS_DECL_AURA void output_debug_string(const char * psz);
CLASS_DECL_AURA void w_output_debug_string(const unichar * psz);
#ifdef __cplusplus
CLASS_DECL_AURA void output_debug_string(const unichar * pwsz);
#endif
CLASS_DECL_AURA void writeln(const char * psz);




//CLASS_DECL_AURA int_bool ui_get_cursor_pos(POINT * ppt);


BEGIN_EXTERN_C

CLASS_DECL_AURA int_bool is_windows_98_or_lesser();

CLASS_DECL_AURA int_bool is_windows_nt();

CLASS_DECL_AURA int_bool is_windows_nt_lesser_than_2000();
CLASS_DECL_AURA int_bool is_windows_2000_or_greater();
CLASS_DECL_AURA int_bool is_windows_xp_or_greater();
CLASS_DECL_AURA int_bool is_windows_vista_or_greater();
CLASS_DECL_AURA int_bool is_windows_7_or_lower();
CLASS_DECL_AURA int_bool is_windows_8_or_greater();

CLASS_DECL_AURA int_bool is_windows_native_unicode();



END_EXTERN_C

#include "os_time.h"

/*
#if _POSIX_C_SOURCE == 200809L
#error "Only for test!! Good error!! _POSIX_C_SOURCE still 200809L"
#endf
*/

//#ifdef __cplusplus
//
//class string;
//
//CLASS_DECL_AURA bool file_copy_dup(const string & strDup,const string & strSrc, bool bOverwrite = true);
//
//#endif // __cplusplus

BEGIN_EXTERN_C

CLASS_DECL_AURA void set_command_line_dup(const char * psz);
CLASS_DECL_AURA void get_command_line_dup(char * psz, int iBuffer);

END_EXTERN_C

#ifdef __cplusplus

#include "os_windowing.h"

class runnable
{
   
public:
   
   virtual void run() = 0;
   
};

void run_runnable_on_main_thread(runnable * prunnable);

#endif


#include "os_graphics.h"




