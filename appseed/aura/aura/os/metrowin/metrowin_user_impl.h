#pragma once


#include "metrowin_gdi_winrt.h"

#ifdef __cplusplus

//CLASS_DECL_AURA string normalize_path(const char * lpcszPath);


//string key_to_char(WPARAM wparam,LPARAM lparam);

#endif

//extern CLASS_DECL_AURA int g_iMouse;

#define GW_HWNDFIRST        0
#define GW_HWNDLAST         1
#define GW_HWNDNEXT         2
#define GW_HWNDPREV         3
#define GW_OWNER            4
#define GW_CHILD            5
#if(WINVER <= 0x0400)
#define GW_MAX              5
#else
#define GW_ENABLEDPOPUP     6
#define GW_MAX              6
#endif


//CLASS_DECL_AURA bool __cdecl __is_idle_message(::message::message * pobj);
//CLASS_DECL_AURA bool __cdecl __is_idle_message(MESSAGE * pMsg);


//CLASS_DECL_AURA oswindow WINAPI WinGetFocus();
//CLASS_DECL_AURA oswindow WINAPI WinSetFocus(oswindow oswindow);

CLASS_DECL_AURA oswindow get_capture();
CLASS_DECL_AURA oswindow set_capture(oswindow oswindow);
CLASS_DECL_AURA WINBOOL release_capture();

CLASS_DECL_AURA oswindow get_active_window();
CLASS_DECL_AURA oswindow set_active_window(oswindow oswindow);



CLASS_DECL_AURA int_bool is_window(oswindow oswindow);


//CLASS_DECL_AURA int WINAPI GetSystemMetrics(int i);

namespace user
{

   class interaction_impl;
   class interaction;
   //   class interaction;
   //
   //
} // namespace user


#include "aura/graphics/graphics_window_graphics.h"
//#include "metrowin_gdi_winrt.h"








struct CLASS_DECL_AURA oswindow_data
{
public:


   ::user::interaction_impl * m_pimpl;

   int_ptr_to_int_ptr *          m_plongptrmap;

   ::user::interaction_impl * window();

   oswindow_data(::user::interaction_impl * pimpl = NULL);
   ~oswindow_data();

   bool is_child(::oswindow oswindow);
   ::oswindow get_parent();
   ::oswindow set_parent(::oswindow oswindow);
   bool show_window(int nCmdShow);
   LONG_PTR get_window_long_ptr(int nIndex);
   LONG_PTR set_window_long_ptr(int nIndex, LONG_PTR l);


   bool client_to_screen(LPPOINT lppoint);
   bool screen_to_client(LPPOINT lppoint);
   bool is_iconic();
   bool is_window_visible();


};
//
//
//class oswindow_dataptra;
//
//
//
/////static oswindow_dataptra * s_pdataptra;
CLASS_DECL_AURA index oswindow_find(::user::interaction_impl * pui);
CLASS_DECL_AURA oswindow oswindow_get(::user::interaction_impl * pui);
CLASS_DECL_AURA oswindow oswindow_remove(::user::interaction_impl * pui);
#if defined(__cplusplus_winrt)
//CLASS_DECL_AURA Agile<Windows::UI::Core::CoreWindow> get_os_window(oswindow window);
CLASS_DECL_AURA Agile < Windows::UI::Core::CoreWindow > get_os_window(oswindow window);

#endif

