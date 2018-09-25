#include "framework.h"


namespace win32
{

   window::window()
   {

      m_hwnd = NULL;

   }


   window::~window()
   {


   }


   void window::attach(HWND hwnd)
   {

      m_hwnd = hwnd;

   }


   void window::destroy_window()
   {

      if (m_hwnd == NULL)
      {

         return;

      }

      ::DestroyWindow(m_hwnd);

      m_hwnd = NULL;

   }


   void window::set_dlg_item_font(int iItem, font & font)
   {

      window window;
      get_dlg_item(window, iItem);
      window.set_font(font);

   }

   void window::set_dlg_item_text(int iItem, string str)
   {

      window window;
      get_dlg_item(window, iItem);
      window._set_window_text(str);

   }

   void window::set_font(font & font)
   {

      ::SendMessageW(m_hwnd, WM_SETFONT, (WPARAM)font.get_os_data(), FALSE);

   }
   void window::on_command(UINT nID)
   {

   }


   int_ptr window::send_message(UINT uiMessage, WPARAM wparam, LPARAM lparam)
   {

      return ::SendMessage(m_hwnd, uiMessage, wparam, lparam);

   }


   int_ptr window::send_message_w(UINT uiMessage, WPARAM wparam, LPARAM lparam)
   {

      return ::SendMessageW(m_hwnd, uiMessage, wparam, lparam);

   }

   void window::post_message(UINT uiMessage, WPARAM wparam, LPARAM lparam)
   {
      ::PostMessageW(m_hwnd, uiMessage, wparam, lparam);
   }

   void window::enable_window(bool bEnable)
   {

      ::EnableWindow(m_hwnd, bEnable ? TRUE : FALSE);


   }

   void window::enable_children(bool bEnable)
   {

      HWND hwnd = GetWindow(m_hwnd, GW_CHILD);

      while (hwnd != NULL)
      {

         ::EnableWindow(hwnd, bEnable ? TRUE : FALSE);

         RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ALLCHILDREN);

         hwnd = GetWindow(hwnd, GW_HWNDNEXT);

      }


   }

   void window::_set_window_text(const char * psz)
   {

      ::SetWindowTextW(m_hwnd, wstring(psz));

   }
   void window::redraw_window()
   {

      RedrawWindow(m_hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ALLCHILDREN);

   }
   string window::get_window_text()
   {

      strsize s = ::GetWindowTextLengthW(m_hwnd);

      wstring wstr;

      unichar * p = wstr.alloc(s + 1);

      GetWindowTextW(m_hwnd, p, s + 1);

      wstr.release_buffer();

      return wstr;

   }

   void window::set_parent(window * pwindow)
   {
      if (pwindow == NULL)
      {

         SetParent(m_hwnd, NULL);
      }
      else
      {

         SetParent(m_hwnd, pwindow->m_hwnd);

      }


   }

   int_ptr window::get_combo_sel()
   {

      return send_message(CB_GETCURSEL);

   }

   void window::show_window(int nCmdShow)
   {

      ::ShowWindow(m_hwnd, nCmdShow);

   }

} // namespace win32


