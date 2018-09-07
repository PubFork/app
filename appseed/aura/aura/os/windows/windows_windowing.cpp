#include "framework.h"
#include "windows_windowing.h"


#define ___TEMP_CLASS_NAME_SIZE 4096


CLASS_DECL_AURA void defer_dock_application(bool bDock)
{

   UNREFERENCED_PARAMETER(bDock);

}



CLASS_DECL_AURA bool os_init_windowing()
{

   return true;

}


CLASS_DECL_AURA void os_term_windowing()
{

}



::user::interaction * get_system_window_interaction(::os_system_window * psystemwindow)
{

   return NULL;

}


CLASS_DECL_AURA i64 oswindow_id(HWND hwnd)
{

   return (i64)hwnd;

}



wstring windows_calc_icon_window_class(::user::interaction * pui, uint32_t dwDefaultStyle, const char * pszMatter)
{

   string strPath = App(pui->get_app()).dir().matter(pszMatter, "icon.ico");

   HICON hIcon = (HICON) ::LoadImageW(NULL, wstring(Sys(pui->get_app()).get_matter_path(strPath)), IMAGE_ICON, 256, 256, LR_LOADFROMFILE);

   wstring strClass = windows_get_user_interaction_window_class(pui);

   if (hIcon != NULL)
   {

      // will fill lpszClassName with default WNDCLASS name
      // ignore instance handle from pre_create_window.

      WNDCLASSW wndcls;

      if (strClass.get_length() > 0 && GetClassInfoW(System.m_hinstance, strClass, &wndcls) && wndcls.hIcon != hIcon)
      {
         // register a very similar WNDCLASS

         return windows_register_window_class(get_app(), wndcls.style, wndcls.hCursor, wndcls.hbrBackground, hIcon);

      }

   }

   return strClass;

}




wstring CLASS_DECL_AURA windows_get_user_interaction_window_class(::user::interaction * pui)
{

   ::user::interaction::e_type etype = pui->get_window_type();

   WNDCLASSW wndcls;
   memset(&wndcls, 0, sizeof(WNDCLASSW));   // start with NULL defaults
   wndcls.lpfnWndProc = DefWindowProcW;
   wndcls.hInstance = pui->m_papp->m_hinstance;

   INITCOMMONCONTROLSEX init;
   init.dwSize = sizeof(init);
   if (etype == ::user::interaction::type_frame || etype == ::user::interaction::type_view)
   {
      // SDI Frame or MDI Child windows or views - normal colors
      wndcls.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
      //wndcls.style = CS_HREDRAW | CS_VREDRAW;
      wndcls.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
      if (windows_register_with_icon(&wndcls, gen_WndFrameOrView, 0))
      {
         return wndcls.lpszClassName;
      }
   }

   return windows_register_window_class(pui->get_app(), 0);

}



bool CLASS_DECL_AURA windows_register_with_icon(WNDCLASSW* pWndCls, const unichar * lpszClassName, UINT nIDIcon)
{
   pWndCls->lpszClassName = lpszClassName;
   pWndCls->hIcon = ::LoadIconW(NULL, MAKEINTRESOURCEW(32512));
   return windows_register_class(pWndCls);
}




__declspec(thread) unichar t_szTempClassName[___TEMP_CLASS_NAME_SIZE] = { 0 };

CLASS_DECL_AURA const unichar * windows_register_window_class(::aura::application * papp, UINT nClassStyle, HCURSOR hCursor, HBRUSH hbrBackground, HICON hIcon)
{
   // Returns a temporary string name for the class
   //  Save in a string if you want to use it for a long time
   LPWSTR lpszName = t_szTempClassName;

   // generate a synthetic name for this class

   if (hCursor == NULL && hbrBackground == NULL && hIcon == NULL)
   {
      C_RUNTIME_ERRORCHECK_SPRINTF(_snwprintf_s(lpszName, ___TEMP_CLASS_NAME_SIZE, ___TEMP_CLASS_NAME_SIZE - 1, L"ca2FrameOrView:::%p:%x", papp->m_hinstance, nClassStyle));
   }
   else
   {
      C_RUNTIME_ERRORCHECK_SPRINTF(_snwprintf_s(lpszName, ___TEMP_CLASS_NAME_SIZE, ___TEMP_CLASS_NAME_SIZE - 1, L"ca2FrameOrView:::%p:%x:%p:%p:%p", papp->m_hinstance, nClassStyle,
                                   hCursor, hbrBackground, hIcon));
   }

   // see if the class already exists
   WNDCLASSW wndcls;
   if (::GetClassInfoW(papp->m_psystem->m_hinstance, lpszName, &wndcls))
   {
      // already registered, assert everything is good
      ASSERT(wndcls.style == nClassStyle);

      // NOTE: We have to trust that the hIcon, hbrBackground, and the
      //  hCursor are semantically the same, because sometimes Windows does
      //  some internal translation or copying of those handles before
      //  storing them in the internal WNDCLASS retrieved by GetClassInfo.
      return lpszName;
   }

   // otherwise we need to register a new class
   wndcls.style = nClassStyle;
   wndcls.lpfnWndProc = DefWindowProcW;
   wndcls.cbClsExtra = wndcls.cbWndExtra = 0;
   wndcls.hInstance = NULL;
   wndcls.hIcon = hIcon;
   //wndcls.hCursor = hCursor;
   wndcls.hCursor = NULL;
   wndcls.hbrBackground = hbrBackground;
   wndcls.lpszMenuName = NULL;
   wndcls.lpszClassName = lpszName;
   if (!windows_register_class(&wndcls))
      _throw(resource_exception(get_app()));

   // return thread-local pointer
   return lpszName;
}


CLASS_DECL_AURA bool windows_register_class(WNDCLASSW* lpWndClass)
{

   WNDCLASSW wndcls;

   if (GetClassInfoW(lpWndClass->hInstance, lpWndClass->lpszClassName, &wndcls))
   {
      return TRUE;
   }

   if (!::RegisterClassW(lpWndClass))
   {
      return FALSE;
   }

   bool bRet = TRUE;


   return bRet;
}


CLASS_DECL_AURA WINBOOL is_window(oswindow oswindow)
{

   return ::IsWindow(oswindow);

}


CLASS_DECL_AURA oswindow get_focus()
{

   return ::GetFocus();

}


CLASS_DECL_AURA oswindow set_focus(oswindow oswindow)
{

   return ::SetFocus(oswindow);

}


CLASS_DECL_AURA oswindow get_active_window()
{

   return ::GetActiveWindow();

}


CLASS_DECL_AURA oswindow set_active_window(oswindow oswindow)
{

   return ::SetActiveWindow(oswindow);

}


CLASS_DECL_AURA oswindow get_capture()
{

   return ::GetCapture();

}


CLASS_DECL_AURA oswindow set_capture(oswindow oswindow)
{

   return ::SetCapture(oswindow);

}


CLASS_DECL_AURA WINBOOL release_capture()
{

   return ::ReleaseCapture();

}


CLASS_DECL_AURA WINBOOL destroy_window(oswindow oswindow)
{

   return ::DestroyWindow(oswindow);

}


CLASS_DECL_AURA oswindow get_desktop_window()
{

   return ::GetDesktopWindow();

}


CLASS_DECL_AURA oswindow get_window(oswindow oswindow, int iWindow)
{

   return ::GetWindow(oswindow, iWindow);

}

