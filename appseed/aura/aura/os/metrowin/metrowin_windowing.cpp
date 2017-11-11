#include "framework.h"
//#include "metrowin_window_impl.h"
//#include "base/user/user.h"




namespace user
{

   class interaction_impl;

} // namespace user


class oswindow_dataptra :
   public comparable_raw_array < oswindow_data * >
{
public:


};

oswindow_dataptra * g_oswindow_dataptra()
{
   static oswindow_dataptra * s_pdataptra = new oswindow_dataptra;

   return s_pdataptra;
}


::user::interaction_impl * oswindow_data::window()
{

   if (this == NULL)
      return NULL;

   return m_pimpl;

}


index oswindow_find(::user::interaction_impl * pimpl)
{

   for (int i = 0; i < g_oswindow_dataptra()->get_count(); i++)
   {

      if (g_oswindow_dataptra()->element_at(i)->m_pimpl == pimpl)
      {

         return i;

      }

   }

   return -1;

}


oswindow_data::oswindow_data(::user::interaction_impl * pimpl)
{

   m_pimpl = pimpl;

}

bool oswindow_data::is_child(::oswindow oswindow)
{

   if (oswindow == NULL || oswindow->m_pimpl == NULL || oswindow->m_pimpl->m_pui == NULL)
   {

      return false;

   }

   if (m_pimpl == NULL || m_pimpl->m_pui == NULL)
   {

      return false;

   }

   return m_pimpl->m_pui->IsChild(oswindow->m_pimpl->m_pui);

}


::oswindow oswindow_data::get_parent()
{

   if (m_pimpl == NULL || m_pimpl->m_pui == NULL)
   {

      return NULL;

   }

   ::user::interaction * pui = m_pimpl->m_pui->GetParent();

   if (pui == NULL)
   {

      return NULL;

   }

   return pui->get_safe_handle();

}


::oswindow oswindow_data::set_parent(::oswindow oswindow)
{

   if (m_pimpl == NULL || m_pimpl->m_pui == NULL)
   {

      return NULL;

   }

   ::user::interaction * pui;

   if (oswindow == NULL || oswindow->m_pimpl == NULL || oswindow->m_pimpl->m_pui == NULL)
   {

      pui = m_pimpl->m_pui->SetParent(NULL);

   }
   else
   {

      pui = m_pimpl->m_pui->SetParent(oswindow->m_pimpl->m_pui);

   }

   return pui->get_safe_handle();

}


bool oswindow_data::show_window(int nCmdShow)
{
   if (m_pimpl == NULL || m_pimpl->m_pui == NULL)
   {

      return false;

   }

   return m_pimpl->m_pui->ShowWindow(nCmdShow);
}

LONG oswindow_data::get_window_long_ptr(int nIndex)
{
   if (m_pimpl == NULL || m_pimpl->m_pui == NULL)
   {

      return 0;

   }
   return (LONG)m_pimpl->m_pui->get_window_long_ptr(nIndex);
}

LONG oswindow_data::set_window_long_ptr(int nIndex, LONG l)
{
   if (m_pimpl == NULL || m_pimpl->m_pui == NULL)
   {

      return 0;

   }

   return (LONG)m_pimpl->m_pui->set_window_long_ptr(nIndex, (LONG)l);

}

#if OSBIT == 64

LONG_PTR oswindow_data::get_window_long_ptr(int nIndex)
{

   if (m_pimpl == NULL || m_pimpl->m_pui == NULL)
   {

      return 0;

   }

   return m_pimpl->m_pui->get_window_long_ptr(nIndex);

}


LONG_PTR oswindow_data::set_window_long_ptr(int nIndex, LONG_PTR l)
{
   if (m_pimpl == NULL || m_pimpl->m_pui == NULL)
   {

      return 0;

   }
   return m_pimpl->m_pui->set_window_long_ptr(nIndex, l);
}

#endif

bool oswindow_data::client_to_screen(LPPOINT lppoint)
{
   if (m_pimpl == NULL || m_pimpl->m_pui == NULL)
   {

      return false;

   }

   return m_pimpl->m_pui->ClientToScreen(lppoint);
}

bool oswindow_data::screen_to_client(LPPOINT lppoint)
{
   if (m_pimpl == NULL || m_pimpl->m_pui == NULL)
   {

      return false;

   }

   return m_pimpl->m_pui->ScreenToClient(lppoint);
}

bool oswindow_data::is_iconic()
{
   if (m_pimpl == NULL || m_pimpl->m_pui == NULL)
   {

      return false;

   }

   return m_pimpl->m_pui->WfiIsIconic();
}

bool  oswindow_data::is_window_visible()
{
   if (m_pimpl == NULL || m_pimpl->m_pui == NULL)
   {

      return false;

   }

   return m_pimpl->m_pui->IsWindowVisible();
}

oswindow oswindow_get(::user::interaction_impl * pimpl)
{

   int_ptr iFind = oswindow_find(pimpl);

   if (iFind >= 0)
      return g_oswindow_dataptra()->element_at(iFind);

   oswindow pdata = new oswindow_data;

   pdata->m_pimpl = pimpl;

   g_oswindow_dataptra()->add(pdata);

   return pdata;

}




//int_bool oswindow_remove(::user::interaction_impl * pui)
//{
//
//   int_ptr iFind = oswindow_find(pui);
//
//   if(iFind < 0)
//      return false;
//
//   g_oswindow_dataptra()->remove_at(iFind);
//
//   return true;
//
//}



Agile < Windows::UI::Core::CoreWindow > get_os_window(oswindow window)
{

   return window->m_pimpl->m_pui->get_os_window();

}


static oswindow g_oswindowFocus;


oswindow WINAPI WinGetFocus()
{

   return g_oswindowFocus;

}

oswindow WINAPI WinSetFocus(oswindow __oswindow)
{

   ::oswindow oswindowOldFocus = g_oswindowFocus;

   g_oswindowFocus = __oswindow;

   // todo
   //SendMessage(__oswindow, WM_SETFOCUS, WPARAM, (LPARAM) (void *) oswindowOldFocus)
   //SendMessage(oswindowOldFocus, WM_KILLFOCUS, WPARAM, (LPARAM) (void *) __oswindow)

   return oswindowOldFocus;

}



static oswindow g_oswindowCapture;


oswindow WINAPI WinGetCapture()
{

   return g_oswindowCapture;

}

oswindow WINAPI WinSetCapture(oswindow __oswindow)
{

   ::oswindow oswindowOldCapture = g_oswindowCapture;

   g_oswindowCapture = __oswindow;

   // todo
   //SendMessage(__oswindow, WM_SETFOCUS, WPARAM, (LPARAM) (void *) oswindowOldFocus)
   //SendMessage(oswindowOldFocus, WM_KILLFOCUS, WPARAM, (LPARAM) (void *) __oswindow)

   return oswindowOldCapture;

}


oswindow WINAPI WinReleaseCapture()
{

   ::oswindow oswindowOldCapture = g_oswindowCapture;

   g_oswindowCapture = NULL;

   // todo
   //SendMessage(__oswindow, WM_SETFOCUS, WPARAM, (LPARAM) (void *) oswindowOldFocus)
   //SendMessage(oswindowOldFocus, WM_KILLFOCUS, WPARAM, (LPARAM) (void *) __oswindow)

   return oswindowOldCapture;

}


static oswindow g_oswindowActive;


oswindow WINAPI WinGetActiveWindow()
{

   return g_oswindowActive;

}

oswindow WINAPI WinSetActiveWindow(oswindow __oswindow)
{

   ::oswindow oswindowOldActive = g_oswindowActive;

   g_oswindowActive = __oswindow;

   // todo
   //SendMessage(__oswindow, WM_SETFOCUS, WPARAM, (LPARAM) (void *) oswindowOldFocus)
   //SendMessage(oswindowOldFocus, WM_KILLFOCUS, WPARAM, (LPARAM) (void *) __oswindow)

   return oswindowOldActive;

}



//oswindow_data * WINAPI GetParent(oswindow_data * pdata)
//{
//
//   if (pdata == NULL)
//      return NULL;
//
//   if (!::WinIsWindow(pdata))
//      return NULL;
//
//   return (oswindow_data *)pdata->m_pimpl->m_pui->GetParent()->get_os_data();
//
//
//}
//


WINBOOL WinIsWindow(oswindow oswindow)
{

   if (((void *)oswindow) == NULL)
      return FALSE;

   return TRUE;

}

int DestroyWindow(oswindow oswindow)
{

   return TRUE;

}



CLASS_DECL_AURA ::user::interaction * oswindow_interaction(oswindow oswindow)
{

   if (is_ptr_null(oswindow, sizeof(*oswindow)))
   {

      return NULL;

   }

   if (is_ptr_null(oswindow->m_pimpl, sizeof(*oswindow->m_pimpl)))
   {

      return NULL;

   }

   return oswindow->m_pimpl->m_pui;

}


CLASS_DECL_AURA::user::interaction_impl * oswindow_get(oswindow oswindow)
{

   if(oswindow == NULL)
   {

      return NULL;

   }

   return oswindow->m_pimpl;

}

