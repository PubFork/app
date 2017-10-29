#pragma once


// define portable types for 32-bit / 64-bit OS
//typedef int32_t WINBOOL;
typedef uint8_t BYTE;
//typedef uint16_t WORD;
typedef uint32_t DWORD;
//typedef int32_t LONG;


#undef FAR
#undef  NEAR
#define FAR
#define NEAR
#ifndef CONST
#define CONST               const
#endif


#ifdef __cplusplus



struct hthread;

namespace ca2
{


   class thread_base;


} // namespace ca2


//class oswindow_data;


//typedef oswindow_data * oswindow;



namespace user
{


   class interaction;
   class interaction;


} // namespace user


class oswindow_dataptra;


class event;


class mutex;


//typedef hthread * HTHREAD;


class oswindow_data;


CLASS_DECL_AURA int32_t oswindow_find_message_only_window(::user::interaction_impl * puibaseMessageWindow);
CLASS_DECL_AURA int32_t oswindow_find(Display * pdisplay, Window window);
CLASS_DECL_AURA int32_t oswindow_find(Window window);
CLASS_DECL_AURA oswindow_data * oswindow_get_message_only_window(::user::interaction_impl * puibaseMessageWindow);
CLASS_DECL_AURA oswindow_data * oswindow_get(Display * pdisplay, Window window, Visual * pvisual = NULL, int iDepth = -1, int iScreen = -1, Colormap colormap = None);
CLASS_DECL_AURA oswindow_data * oswindow_get(Window window);
CLASS_DECL_AURA oswindow oswindow_defer_get(Window w);
CLASS_DECL_AURA bool oswindow_remove(Display * pdisplay, Window window);
CLASS_DECL_AURA bool oswindow_remove_message_only_window(::user::interaction_impl * puibaseMessageOnlyWindow);






#endif
