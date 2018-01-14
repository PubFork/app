//
//  macos_window.cpp
//  base
//
//  Created by Camilo Sasuke Tsumanuma on 2013-09-17.
//
//

#include "framework.h"
#include "ios_window_impl.h"


//oswindow_dataptra * g_poswindowdataptra = NULL;


//int oswindow_find(nswindow window)
//{
//
//   for(int i = 0; i < g_poswindowdataptra->get_count(); i++)
//   {
//      if(g_poswindowdataptra->element_at(i)->m_nswindow == window)
//      {
//         return i;
//      }
//   }
//
//   return -1;
//
//}

//oswindow_data * oswindow_get(nswindow window)
//{
//
//   int_ptr iFind = oswindow_find(window);
//
//   if(iFind >= 0)
//      return g_poswindowdataptra->element_at(iFind);
//
//   ::oswindow_data * pdata = new ::oswindow_data;
//
//   pdata->m_nswindow    = window;
//
//   g_poswindowdataptra->add(pdata);
//
//   return pdata;
//
//}


oswindow_data::oswindow_data()
{

   m_nswindow  = NULL;
   m_pimpl     = NULL;
   m_plongmap  = new int_to_int;

}


oswindow_data::oswindow_data(nswindow window)
{

   m_nswindow  = window;
   m_pimpl     = NULL;
   m_plongmap  = new int_to_int;

}


oswindow_data::oswindow_data(const oswindow_data & oswindow)
{

   m_nswindow  = oswindow.m_nswindow;
   m_pimpl     = oswindow.m_pimpl;
   m_plongmap  = oswindow.m_plongmap;

}


oswindow_data::~oswindow_data()
{

   delete m_plongmap;

}


oswindow_data & oswindow_data::operator = (const oswindow_data & oswindow)
{

   if(&oswindow != this)
   {

      m_nswindow  = oswindow.m_nswindow;
      m_pimpl     = oswindow.m_pimpl;
      m_plongmap  = oswindow.m_plongmap;

   }

   return *this;

}


//bool oswindow_remove(nswindow window)
//{
//
//   int_ptr iFind = oswindow_find(window);
//
//   if(iFind < 0)
//      return false;
//
//   g_poswindowdataptra->remove_at(iFind);
//
//   return true;
//
//}


void oswindow_data::set_user_interaction_impl(::user::interaction_impl * pimpl)
{

   if(is_null())
      _throw(simple_exception(get_app(), "error, m_pdata cannot be NULL to ::oswindow::set_user_interaction"));

   m_pimpl = pimpl;

}


::user::interaction_impl * oswindow_data::get_user_interaction_impl()
{

   if(is_null())
      return NULL;

   return m_pimpl;

}

::user::interaction_impl * oswindow_data::get_user_interaction_impl() const
{

   if(is_null())
      return NULL;

   return m_pimpl;

}

::user::interaction * oswindow_data::get_user_interaction()
{

   if(is_null())
      return NULL;

   if(m_pimpl == NULL)
      return NULL;

   return m_pimpl->m_pui;

}

::user::interaction * oswindow_data::get_user_interaction() const
{

   if(is_null())
      return NULL;

   if(m_pimpl == NULL)
      return NULL;

   return m_pimpl->m_pui;

}


oswindow oswindow_data::get_parent()
{

   if(is_null())
      return NULL;

   return m_pimpl->m_pui->GetParentHandle();

}


oswindow oswindow_data::set_parent(oswindow oswindow)
{
   
   if(is_null())
      return NULL;
   
   ::oswindow oswindowOldParent = get_parent();
   
   if(oswindow == NULL || oswindow->m_pimpl == NULL || oswindow->m_pimpl->m_pui == NULL)
   {
      
      m_pimpl->m_pui->SetParent(NULL);
      
   }
   else
   {
      
      m_pimpl->m_pui->SetParent(oswindow->m_pimpl->m_pui);
      
   }
   
   return oswindowOldParent;
   
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

int32_t oswindow_data::get_window_long(int32_t iIndex)
{

   if(is_null())
      return 0;

   if(m_plongmap == NULL)
      return 0;

   return m_plongmap->operator[](iIndex);

}


int32_t oswindow_data::set_window_long(int32_t iIndex, int32_t iNewLong)
{

   if(is_null())
      return 0;

   if(m_plongmap == NULL)
      return 0;

   int32_t iLong = m_plongmap->operator[](iIndex);

   m_plongmap->operator[](iIndex) = iNewLong;

   return iLong;

}


//static oswindow g_oswindowCapture;
//
//
//oswindow GetCapture()
//{
//   return g_oswindowCapture;
//}
//
//oswindow SetCapture(oswindow window)
//{
//
//   oswindow windowOld(g_oswindowCapture);
//
//   if(window->window() == NULL)
//      return NULL;
//
//   g_oswindowCapture = window;
//
//   /*   if(XGrabPointer(window.display(), window.window(), False, ButtonPressMask | ButtonReleaseMask | PointerMotionMask, GrabModeAsync, GrabModeAsync, None, None, 8CurrentTime) == GrabSuccess)
//    {
//
//    g_oswindowCapture = window;
//
//    return windowOld;
//
//    }*/
//
//   return windowOld;
//
//}
//
//
//WINBOOL ReleaseCapture()
//{
//
//   //ifGetCapture().display() == NULL)
//   // return FALSE;
//
//   //  WINBOOL bRet = XUngrabPointer(GetCapture().display(), CurrentTime) != FALSE;
//
//   WINBOOL bRet = TRUE;
//
//   if(bRet)
//      g_oswindowCapture = NULL;
//
//   return bRet;
//
//}
//
//
//oswindow GetFocus();
//
//
//oswindow SetFocus(oswindow window)
//{
//
//   if(!IsWindow(window))
//      return NULL;
//
//   oswindow windowOld = ::GetFocus();
//
//   return windowOld;
//
//}
//
//oswindow GetFocus()
//{
//
//   //isplay * pdisplay = XOpenDisplay(NULL);
//
//   //   Window window = None;
//
//   //   int revert_to = 0;
//
//   //bool bOk = XGetInputFocus(pdisplay, &window, &revert_to) != 0;
//
//   //XCloseDisplay(pdisplay);
//
//   //   if(!bOk)
//   //    return NULL;
//
//   // if(window == None || window == PointerRoot)
//   //  return NULL;
//
//   //return oswindow::defer_get(window);
//   return NULL;
//
//}
//
//
//
//
//static oswindow g_oswindowActive = NULL;
//
//
//oswindow GetActiveWindow()
//{
//   return g_oswindowActive;
//}
//
//oswindow SetActiveWindow(oswindow window)
//{
//
//   oswindow windowOld(g_oswindowActive);
//
//   if(window->window() == NULL)
//      return NULL;
//
//   g_oswindowActive = window;
//
//   return windowOld;
//
//}
//


