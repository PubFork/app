#include "framework.h"

namespace win32
{


   dialog::dialog()
   {

      m_pszResource = NULL;

   }


   dialog::dialog(::aura::application * papp, LPCWSTR pszResource) :
      ::object(papp),
      m_pszResource(pszResource)
   {

   }


   dialog::~dialog()
   {


   }

   bool dialog::create_dialog(window * pwnd)
   {

      int i = GetThreadLocale();
      SetThreadLocale(65001);
      int i2 = GetThreadLocale();


      CreateDialogParamW(System.m_hinstance, m_pszResource,
                         pwnd == NULL ? NULL : pwnd->m_hwnd, &DialogProc, (LPARAM)this);

      return true;

   }


#ifdef WINDOWS

   INT_PTR CALLBACK dialog::DialogProc(HWND hwnd, UINT uiMessage, WPARAM wparam, LPARAM lparam)
   {

      dialog * pdialog;

      if (uiMessage == WM_INITDIALOG)
      {

         SetWindowLongPtr(hwnd, GWLP_USERDATA, lparam);

         pdialog = (dialog *)lparam;

         pdialog->m_hwnd = hwnd;

      }
      else
      {

         pdialog = (dialog *)GetWindowLongPtr(hwnd, GWLP_USERDATA);

      }

      if (pdialog != NULL)
      {

         return pdialog->on_dialog_message(uiMessage, wparam, lparam);

      }

      return 0;

   }

   INT_PTR dialog::on_dialog_message(UINT uiMessage, WPARAM wparam, LPARAM lparam)
   {

      if (uiMessage == WM_INITDIALOG)
      {

         if (!on_init_dialog())
         {

            return 0;

         }

         return true;

      }
      else if (uiMessage == WM_COMMAND)
      {
         if (HIWORD(wparam) > 3)
         {
            on_notify(HIWORD(wparam), LOWORD(wparam));
         }
         else
         {
            on_command(LOWORD(wparam));

         }

      }
      else if (uiMessage == WM_NOTIFY)
      {

         on_notify((NMHDR *)lparam);
      }
      else if (uiMessage == WM_CLOSE)
      {

         on_close();


         return 1;

      }

      return 0;

   }

#endif

   bool dialog::on_init_dialog()
   {

      return true;

   }

   void dialog::on_close()
   {

   }
   void dialog::on_notify(NMHDR * p)
   {


   }

   void dialog::on_notify(int iCode, int iId)
   {

   }
} // namespace os




