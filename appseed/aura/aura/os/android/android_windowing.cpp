#include "framework.h"
#include "aura/os/android/android_windowing.h"

::user::interaction * get_system_window_interaction(::os_system_window * psystemwindow)
{

   if (psystemwindow == NULL)
   {

      return NULL;

   }

   return psystemwindow->m_pui;

}


CLASS_DECL_AURA int32_t oswindow_find_message_only_window(::user::interaction_impl * puibaseMessageWindow);
//CLASS_DECL_AURA int32_t oswindow_find(Display * pdisplay,Window window);
//CLASS_DECL_AURA int32_t oswindow_find(Window window);
CLASS_DECL_AURA oswindow_data * oswindow_get_message_only_window(::user::interaction_impl * puibaseMessageWindow);
//CLASS_DECL_AURA oswindow_data * oswindow_get(Display * pdisplay,Window window,Visual * pvisual = NULL,int iDepth = -1,int iScreen = -1,Colormap colormap = None);
//CLASS_DECL_AURA oswindow_data * oswindow_get(Window window);
//CLASS_DECL_AURA oswindow oswindow_defer_get(Window w);
//CLASS_DECL_AURA bool oswindow_remove(Display * pdisplay,Window window);
CLASS_DECL_AURA bool oswindow_remove_message_only_window(::user::interaction_impl * puibaseMessageOnlyWindow);


namespace user
{


   class interaction_base;
   class interaction;


} // namespace user



oswindow_data::oswindow_data()
{

   m_hthread = (HTHREAD) NULL;

   m_pimpl = NULL;

   m_bMessageOnlyWindow = false;

   m_bDestroying = false;

}


oswindow_data::~oswindow_data()
{

}



#define CA2_X11_WINDOW_LONG "ca2_ccvotagus_fontopu_window_long"
#define CA2_X11_WINDOW_LONG_STYLE "ca2_ccvotagus_fontopu_window_long_style"
#define CA2_X11_WINDOW_LONG_STYLE_EX "ca2_ccvotagus_fontopu_window_long_style_ex"

//oswindow_dataptra * oswindow_data::s_pdataptra = new oswindow_dataptra;
//mutex * oswindow_data::s_pmutex = new mutex;


int32_t oswindow_find_message_only_window(::user::interaction_impl * pimpl)
{

   if (pimpl == NULL)
   {

      return -1;

   }

   synch_lock slOsWindow(oswindow_data::s_pmutex);

   for (int32_t i = 0; i < ::oswindow_data::s_pdataptra->get_count(); i++)
   {

      if (::oswindow_data::s_pdataptra->element_at(i)->m_bMessageOnlyWindow
            && ::oswindow_data::s_pdataptra->element_at(i)->m_pimpl == pimpl)
      {

         return i;

      }

   }

   return -1;

}



int32_t oswindow_find(::user::interaction_impl * pimpl)
{

   synch_lock slOsWindow(::oswindow_data::s_pmutex);

   for (int32_t i = 0; i < ::oswindow_data::s_pdataptra->get_count(); i++)
   {
      if (!::oswindow_data::s_pdataptra->element_at(i)->m_bMessageOnlyWindow
            &&  ::oswindow_data::s_pdataptra->element_at(i)->m_pimpl == pimpl)
      {
         return i;
      }
   }

   return -1;

}

oswindow_data * oswindow_get_message_only_window(::user::interaction_impl * pimpl)
{

   if (pimpl == NULL)
      return NULL;

   synch_lock slOsWindow(::oswindow_data::s_pmutex);

   int_ptr iFind = oswindow_find_message_only_window(pimpl);

   if (iFind >= 0)
   {

      return ::oswindow_data::s_pdataptra->element_at(iFind);

   }

   ::oswindow_data * pdata = new oswindow_data;

   pdata->m_bMessageOnlyWindow = true;

   pdata->m_pimpl = pimpl;

   ::oswindow_data::s_pdataptra->add(pdata);

   return pdata;

}


oswindow_data * oswindow_get(::user::interaction_impl * pimpl)
{

   synch_lock slOsWindow(::oswindow_data::s_pmutex);

   int_ptr iFind = oswindow_find(pimpl);

   if (iFind >= 0)
      return ::oswindow_data::s_pdataptra->element_at(iFind);

   ::oswindow_data * pdata = new ::oswindow_data;

   pdata->m_bMessageOnlyWindow = false;
   pdata->m_pimpl = pimpl;

   ::oswindow_data::s_pdataptra->add(pdata);

   return pdata;

}



/*
oswindow::oswindow()
{

m_pdata = NULL;

}

oswindow::oswindow(::user::interaction * pui)
{

synch_lock slOsWindow(s_pmutex);

m_pdata = get_message_only_window(pui);



}

oswindow::oswindow(Display * pdisplay, Window interaction_impl, Visual * pvisual)
{

synch_lock slOsWindow(s_pmutex);

m_pdata = get(pdisplay, interaction_impl);

if(pvisual != NULL)
{

m_pdata->m_pvisual = pvisual;

}


}

oswindow::oswindow(const oswindow & oswindow)
{

m_pdata = oswindow.m_pdata;

}

oswindow::oswindow(const void * p)
{

m_pdata = (data *) p;

}

oswindow::oswindow(const LPARAM & lparam)
{

m_pdata = (data *) lparam;

}

oswindow::oswindow(const WPARAM & wparam)
{

m_pdata = (data *) wparam;

}






oswindow & oswindow::operator = (const oswindow & oswindow)
{

m_pdata = oswindow.m_pdata;

return *this;

}



*/


oswindow oswindow_defer_get(::user::interaction_impl * pimpl)
{

   return pimpl->m_oswindow;

}



//int_bool oswindow_remove(::user::interaction * pui)
//{
//
//   synch_lock slOsWindow(::oswindow_data::s_pmutex);
//
//   int_ptr iFind = oswindow_find(pui);
//
//   if(iFind < 0)
//      return false;
//
//   ::oswindow_data::s_pdataptra->remove_at(iFind);
//
//   return true;
//
//}


bool oswindow_remove_message_only_window(::user::interaction_impl * pui)
{

   synch_lock slOsWindow(::oswindow_data::s_pmutex);

   int_ptr iFind = oswindow_find_message_only_window(pui);

   if (iFind < 0)
      return false;

   ::oswindow_data::s_pdataptra->remove_at(iFind);

   return true;

}


int32_t oswindow_data::store_name(const char * psz)
{

   synch_lock sl(m_pimpl == NULL || m_pimpl->m_pui ? NULL : m_pimpl->m_pui->m_pmutex);

   synch_lock slOsWindow(s_pmutex);

   /*

   xdisplay d(display());

   return XStoreName(display(), interaction_impl(), psz);

   */

   return 0;

}


int32_t oswindow_data::select_input(int32_t iInput)
{

   synch_lock sl(m_pimpl == NULL || m_pimpl->m_pui ? NULL : m_pimpl->m_pui->m_pmutex);

   synch_lock slOsWindow(s_pmutex);

   /*

   xdisplay d(display());

   return XSelectInput(display(), interaction_impl(), iInput);

   */

   return 0;

}


int32_t oswindow_data::select_all_input()
{

   /*

   xdisplay d(display());

   return select_input(ExposureMask | ButtonPressMask);

   */

   return 0;

}


int32_t oswindow_data::map_window()
{

   /*

   synch_lock sl(m_pui == NULL ? NULL : m_pui->m_pmutex);

   synch_lock slOsWindow(s_pmutex);

   xdisplay d(display());

   return XMapWindow(display(), interaction_impl());

   */

   return 0;

}


void oswindow_data::post_nc_destroy()
{

   synch_lock slOsWindow(s_pmutex);

   oswindow_remove(m_pimpl);

}


void oswindow_data::set_impl(::user::interaction_impl * pimpl)
{

   synch_lock slOsWindow(s_pmutex);

   if (this == NULL)
   {

      _throw(simple_exception(get_app(), "error, m_pdata cannot be NULL to ::oswindow::set_user_interaction"));

   }

   m_pimpl = pimpl;

   m_hthread = m_pimpl->m_pui->m_papp->get_os_handle();

}


::user::interaction_impl * oswindow_data::get_impl()
{

   single_lock slOsWindow(s_pmutex, true);

   if (this == NULL)
   {

      return NULL;

   }

   return m_pimpl;

}


::user::interaction_impl * oswindow_data::get_impl() const
{

   single_lock slOsWindow(s_pmutex, true);

   if (this == NULL)
   {

      return NULL;

   }

   return m_pimpl;

}


::user::interaction * oswindow_data::get_user_interaction()
{

   ::user::interaction_impl * pimpl = get_impl();

   try
   {

      return pimpl->m_pui;

   }
   catch (...)
   {

   }

   return NULL;

}


::user::interaction * oswindow_data::get_user_interaction() const
{

   ::user::interaction_impl * pimpl = get_impl();

   try
   {

      return pimpl->m_pui;

   }
   catch (...)
   {

   }

   return NULL;

}



bool oswindow_data::is_child(::oswindow oswindow)
{

   synch_lock sl(m_pimpl == NULL || m_pimpl->m_pui ? NULL : m_pimpl->m_pui->m_pmutex);

   synch_lock slOsWindow(s_pmutex);

   oswindow = oswindow->get_parent();

   while (!oswindow->is_null())
   {
      if (oswindow == this)
         return true;
   }

   return false;

}


oswindow oswindow_data::get_parent()
{

   return NULL;

}


oswindow oswindow_data::set_parent(oswindow oswindow)
{

   return NULL;

}


bool oswindow_data::show_window(int32_t nCmdShow)
{

   synch_lock sl(m_pimpl == NULL || m_pimpl->m_pui ? NULL : m_pimpl->m_pui->m_pmutex);

   synch_lock slOsWindow(s_pmutex);

   if(nCmdShow == SW_HIDE)
   {

      m_pimpl->m_pui->ModifyStyle(WS_VISIBLE, 0);

   }
   else
   {

      m_pimpl->m_pui->ModifyStyle(0, WS_VISIBLE);

   }

   return false;

}


LONG_PTR oswindow_data::get_window_long_ptr(int32_t nIndex)
{

   return m_pimpl->get_window_long_ptr(nIndex);

}


LONG_PTR oswindow_data::set_window_long_ptr(int32_t nIndex, LONG_PTR l)
{

   return m_pimpl->set_window_long_ptr(nIndex, l);

}


bool oswindow_data::client_to_screen(POINT * pp)
{

   return true;

}


bool oswindow_data::screen_to_client(POINT * pp)
{

   return true;

}


long oswindow_data::get_state()
{

   return -1;

}


bool oswindow_data::is_iconic()
{

   return m_bIconic;
}


bool oswindow_data::is_window_visible()
{

   synch_lock sl(m_pimpl == NULL || m_pimpl->m_pui ? NULL : m_pimpl->m_pui->m_pmutex);

   if (m_pimpl == NULL)
   {

      return false;

   }

   return get_window_long_ptr(GWL_STYLE) & WS_VISIBLE;

}






/* Copyright (c) 2012 the authors listed at the following URL, and/or
the authors of referenced articles or incorporated external code:
http://en.literateprograms.org/Hello_World_(C,_Cairo)?action=history&offset=20070528220552

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Retrieved from: http://en.literateprograms.org/Hello_World_(C,_Cairo)?oldid=10388
*/


void message_box_paint(::draw2d::graphics * pgraphics, stringa & stra, bool_array  & baTab, int_array  & ya, SIZE * psize)
{

   pgraphics->fill_solid_rect_dim(0, 0, psize->cx, psize->cy, RGB(84, 90, 80));

   draw2d::brush_sp pen(pgraphics->allocer());

   pen->create_solid(0);

   for (index i = 0; i < stra.get_count(); i++)
   {
      pgraphics->text_out(10.0 + 50.0 + (baTab[i] ? 25.0 : 0), 10.0 + 50.0 + ya[i], stra[i]);
   }



}



static oswindow g_oswindowCapture;
static oswindow g_oswindowFocus;
static oswindow g_oswindowActive;


oswindow get_capture()
{

   return g_oswindowCapture;

}

oswindow set_capture(oswindow oswindow)
{

   ::oswindow oswindowCapturePrevious = g_oswindowCapture;

   g_oswindowCapture = oswindow;

   return oswindowCapturePrevious;

}


int_bool release_capture()
{

   g_oswindowCapture = NULL;

   return true;

}


oswindow set_focus(oswindow oswindow)
{

   ::oswindow oswindowFocusPrevious = g_oswindowFocus;

   g_oswindowFocus = oswindow;

   return g_oswindowFocus;

}


oswindow get_focus()
{

   return g_oswindowFocus;

}


int_bool GetClientRect(oswindow_data * pdata, RECT * prect)
{

   *prect = pdata->m_pimpl->m_rectParentClient;

   prect->right -= prect->left;
   prect->bottom -= prect->top;
   prect->left = 0;
   prect->top = 0;

   return TRUE;

}


int_bool GetWindowRect(oswindow_data * pdata, RECT * prect)
{

   *prect = pdata->m_pimpl->m_rectParentClientRequest;

   return TRUE;

}


//WINBOOL ShowWindow(oswindow_data * pdata, int nCmdShow)
//{
//
//   return pdata->show_window(nCmdShow);
//
//}


WINBOOL SetWindowPos(oswindow_data * pdata, oswindow_data * pdataAfter, int x, int y, int cx, int cy, unsigned int uiFlags)
{

   return pdata->m_pimpl->SetWindowPos((int_ptr)pdataAfter, x, y, cx, cy, uiFlags);
   //if (uiFlags & SWP_NOMOVE)
   //{
   // if (uiFlags & SWP_NOSIZE)
   // {
   // }
   // else
   // {
   //    pdata->m_rect.right = pdata->m_rect.left + cx;
   //    pdata->m_rect.bottom = pdata->m_rect.top + cy;
   // }
   //}
   //else
   //{
   // if (uiFlags & SWP_NOSIZE)
   // {
   //    int offsetX = pdata->m_rect.left - x;
   //    int offsetY = pdata->m_rect.top - y;
   //    pdata->m_rect.left += offsetX;
   //    pdata->m_rect.top += offsetY;
   //    pdata->m_rect.right += offsetX;
   //    pdata->m_rect.bottom += offsetY;
   // }
   // else
   // {
   //    pdata->m_rect.left = x;
   //    pdata->m_rect.top = y;
   //    pdata->m_rect.right = x + cx;
   //    pdata->m_rect.bottom = y + cy;

   // }

   //}

   return TRUE;

}

//oswindow_data * GetParent(oswindow_data * pdata)
//{
//
//   if (pdata == NULL)
//      return NULL;
//
//   if (!IsWindow(pdata))
//      return NULL;
//
//   return pdata->get_parent();
//
//
//}
//
int_bool IsAscendant(oswindow_data * pdata, oswindow_data * pdataAscendant)
{

   if (pdata == NULL)
      return FALSE;

   oswindow_data * pdataParent = pdata->get_parent();

   if (pdataAscendant == NULL)
   {
      if (pdataParent == NULL)
         return TRUE;
      else
         return FALSE;
   }

   while (pdataParent != NULL)
   {

      if (pdataParent == pdataAscendant)
         return TRUE;

      pdataParent = pdataParent->get_parent();
   }

   return FALSE;

}


//oswindow g_oswindowActive = NULL;


oswindow get_active_window()
{

   return g_oswindowActive;

}


oswindow set_active_window(oswindow oswindow)
{

   ::oswindow oswindowPrevious = g_oswindowActive;

   g_oswindowActive = oswindow;

   return g_oswindowActive;

}


oswindow get_window(oswindow windowParam, int iParentHood)
{

   synch_lock sl(windowParam == NULL ? NULL : (windowParam->m_pimpl == NULL || windowParam->m_pimpl->m_pui == NULL ? NULL : windowParam->m_pimpl->m_pui->m_pmutex));

   oswindow interaction_impl = windowParam;

   if (interaction_impl == NULL)
   {

      return NULL;

   }

   return NULL;

}



int_bool destroy_window(oswindow w)
{

   synch_lock sl(w == NULL || w->m_pimpl == NULL || w->m_pimpl->m_pui == NULL ? NULL : w->m_pimpl->m_pui->m_pmutex);

   if (!is_window(w))
   {

      return FALSE;

   }

   return FALSE;

}


bool oswindow_data::is_destroying()
{

   if (this == NULL)
      return true;

   if (m_bDestroying)
      return true;

   return false;

}


//bool IsWindow(oswindow oswindow)
//{
//
//   return oswindow->get_user_interaction() != NULL && !oswindow->is_destroying();
//
//}


oswindow g_oswindowDesktop;


bool c_xstart()
{

   /*
   Display * dpy = XOpenDisplay(NULL);

   g_oswindowDesktop = oswindow_get(dpy, DefaultRootWindow(dpy));

   XSelectInput(g_oswindowDesktop->display(), g_oswindowDesktop->interaction_impl(), StructureNotifyMask);


   return true;

   */


   return false;

}



oswindow get_desktop_window()
{

   return g_oswindowDesktop;
}


POINT g_ptCursor;


int_bool SetCursorPos(LPPOINT lppt)
{
   g_ptCursor = *lppt;
   return TRUE;
}


int_bool GetCursorPos(LPPOINT lppt)
{
   *lppt = g_ptCursor;
   return TRUE;
}







//bool IsWindow(oswindow oswindow)
//{
//   return (oswindow->get_user_interaction() == NULL && oswindow->display() != NULL && oswindow->window() != None)
//      || (oswindow->get_user_interaction() != NULL && !oswindow->is_destroying());
//}





//int32_t IsWindowVisible(oswindow window)
//{
//
//   if (!IsWindow(window))
//      return false;
//
//   return window->is_window_visible();
//
//}
//


//LONG GetWindowLongA(oswindow window, int nIndex)
//{
//
//   if (!IsWindow(window))
//      return false;
//
//   return (LONG) window->get_window_long_ptr(nIndex);
//
//}
//
//
//LONG SetWindowLongA(oswindow window, int nIndex, LONG lValue)
//{
//
//   if (!IsWindow(window))
//      return false;
//
//   return (LONG) window->set_window_long_ptr(nIndex, lValue);
//
//}

//
//oswindow SetParent(oswindow window, oswindow windowNewParent)
//{
//
//   if (!IsWindow(window) || !(windowNewParent == NULL || ::IsWindow(windowNewParent)))
//      return NULL;
//
//   return window->SetParent(windowNewParent);
//
//}



//int32_t IsIconic(oswindow window)
//{
//
//   if (!IsWindow(window))
//      return false;
//
//   return window->is_iconic();
//
//}


::user::interaction_impl * window_from_handle(oswindow oswindow)
{

   if (oswindow == NULL)
      return NULL;

   return oswindow->m_pimpl;

}



//bool IsChild(oswindow windowParent, oswindow oswindowCandidateChildOrDescendant)
//{
//
//   if (!IsWindow(windowParent) || !IsWindow(oswindowCandidateChildOrDescendant))
//      return false;
//
//
//   return windowParent->is_child(oswindowCandidateChildOrDescendant);
//
//
//}

void on_post_nc_destroy(oswindow window)
{

   window->post_nc_destroy();

}


bool is_message_only_window(oswindow window)
{

   return window->m_bMessageOnlyWindow;

}


int translate_android_key_message(::message::key * pkey, int keyCode, int iUni);



extern "C"
void android_mouse(unsigned int message, float x, float y)
{

   if (::aura::system::g_p == NULL)
      return;

   if (::aura::system::g_p->m_psystem == NULL)
      return;

   if (::aura::system::g_p->m_psystem->m_possystemwindow == NULL)
      return;

   if (::aura::system::g_p->m_psystem->m_possystemwindow->m_pui == NULL)
      return;

   MESSAGE msg;

   msg.hwnd = ::aura::system::g_p->m_psystem->m_possystemwindow->m_pui->get_handle();

   msg.message = message;

   msg.wParam = 0;

   msg.lParam = MAKELPARAM((long)x, (long)y);

   msg.pt.x = (long)x;

   msg.pt.y = (long)y;

   ::aura::system::g_p->m_psystem->m_possystemwindow->m_pui->message_handler(&msg);


}


extern "C"
void android_l_button_down(float x, float y)
{

   android_mouse(WM_LBUTTONDOWN, x, y);

}





extern "C"
void android_mouse_move(float x, float y)
{

   android_mouse(WM_MOUSEMOVE, x, y);

}





extern "C"
void android_l_button_up(float x, float y)
{

   android_mouse(WM_LBUTTONUP, x, y);

}

void _android_key(unsigned int message, int keyCode, int iUni);


extern "C"
void android_key(unsigned int message, int keyCode, int iUni)
{

   ::fork(::aura::system::g_p, [=]()
   {

      _android_key(message, keyCode, iUni);

   });

}

void _android_key(unsigned int message, int keyCode, int iUni)
{

   if (::aura::system::g_p == NULL)
      return;

   if (::aura::system::g_p->m_psystem == NULL)
      return;

   if (::aura::system::g_p->m_psystem->m_possystemwindow == NULL)
      return;

   if (::aura::system::g_p->m_psystem->m_possystemwindow->m_pui == NULL)
      return;

   sp(::message::key) pkey = canew(::message::key(get_app()));

   pkey->m_id = message;

   if (!translate_android_key_message(pkey, keyCode, iUni))
   {

      return;

   }

   ::aura::system::g_p->m_psystem->m_possystemwindow->m_pui->message_handler(pkey);


}


void _android_size(float xDummy, float yDummy, float cx, float cy)
{

   UNREFERENCED_PARAMETER(xDummy);

   UNREFERENCED_PARAMETER(yDummy);

   if (::aura::system::g_p == NULL)
      return;

   if (::aura::system::g_p->m_psystem == NULL)
      return;

   if (::aura::system::g_p->m_psystem->m_possystemwindow == NULL)
      return;

   if (::aura::system::g_p->m_psystem->m_possystemwindow->m_pui == NULL)
      return;

   ::aura::system::g_p->m_psystem->m_possystemwindow->m_pui->SetWindowPos(ZORDER_TOP, 0, 0, cx, cy, SWP_SHOWWINDOW);


}


extern "C"
void android_key_down(int keyCode, int iUni)
{

   output_debug_string("here???555");

   android_key(WM_KEYDOWN, keyCode, iUni);

}

// aPokemon : oh_Isee_a_pattern_and_I_am_clown_describing_exactly_pay_attention_exactly_as_inphysical_mirror_that_is_surely_a_perfect_human_mirror_than_another_person

void _android_size(float xScreen, float yScreen, float aPok, float yBitmap);


extern "C"
void android_on_size(float xScreen, float yScreen, float pikachu, float yBitmap)
{

   output_debug_string("android_on_size\n");

   ::fork(::aura::system::g_p, [=]()
   {

      _android_size(xScreen, yScreen, pikachu, yBitmap);

   });

}


extern "C"
void android_key_up(int keyCode, int iUni)
{
   output_debug_string("here???444");

   android_key(WM_KEYUP, keyCode, iUni);

}




int translate_android_key_message(::message::key * pkey, int keyCode, int iUni)
{

   output_debug_string("here???333");

   if (0x80000000 & iUni)
   {

      return 0;

   }
   bool bOk = true;
   switch (keyCode)
   {
   case 62:
      pkey->m_ekey = ::user::key_space;
      break;
   case 67:
      pkey->m_ekey = ::user::key_back;
      break;
   case 112:
      pkey->m_ekey = ::user::key_delete;
      break;
   case 59:
      pkey->m_ekey = ::user::key_lshift;
      break;
   case 60:
      pkey->m_ekey = ::user::key_rshift;
      break;
   case 66:
      pkey->m_ekey = ::user::key_return;
      break;
   default:
      bOk = false;
   }

   //if (keyCode >= 29 && keyCode <= 54)
   if(!bOk)
   {

      //pkey->m_ekey = (::user::e_key) ((int) ::user::key_a + keyCode - 29);
      pkey->m_ekey = ::user::key_refer_to_text_member;

      unichar32 u32sz[2];
      u32sz[0] = iUni;
      u32sz[1] = 0;

      pkey->m_strText = utf32_to_utf8(u32sz);

   }
   //else if (keyCode >= 7 && keyCode <= 16)
   //{

   //   pkey->m_ekey = (::user::e_key) ((int) ::user::key_0 + keyCode - 7);

   //   pkey->m_ekey = ::user::key_refer_to_text_member;

   //   pkey->m_strText = string((unichar)iUni);

   //}
   //else
   //{

   //}

   return 1;

}

void _android_on_text(string str);

extern "C"
void android_on_text(e_os_text etext, const wchar_t * pwch, size_t len)
{

   output_debug_string("here???222");

   string strText(pwch, len);

   ::aura::system::g_p->fork([=]()
   {

      ::aura::system::g_p->on_os_text(etext, strText);

   });

}


namespace aura
{

   void system::on_os_text(e_os_text etext, string strText)
   {

      if (m_possystemwindow == NULL || m_possystemwindow->m_pui == NULL)
         return;

      sp(::message::key) pkey = canew(::message::key(get_app()));

      pkey->m_id = WM_KEYDOWN;

      pkey->m_ekey = ::user::key_refer_to_text_member;

      pkey->m_strText = strText;

      if (pkey->m_strText == "\n" || pkey->m_strText == "\r\n" || pkey->m_strText == "\r")
      {

         pkey->m_strText.Empty();

         pkey->m_ekey = ::user::key_return;

         m_possystemwindow->m_pui->message_handler(pkey);

      }
      else
      {

         m_possystemwindow->m_pui->message_handler(pkey);

      }


   }


} // namespace base


CLASS_DECL_AURA void defer_dock_application(bool bDock)
{

   UNREFERENCED_PARAMETER(bDock);


}

CLASS_DECL_AURA ::user::interaction * oswindow_interaction(oswindow oswindow)
{

   return oswindow->m_pimpl->m_pui;

}


CLASS_DECL_AURA ::user::interaction_impl * oswindow_get(oswindow oswindow)
{

   if (oswindow == NULL)
   {

      return NULL;

   }

   return oswindow->m_pimpl;

}

mutex * oswindow_data::s_pmutex = NULL;

oswindow_dataptra * oswindow_data::s_pdataptra = NULL;

bool os_init_windowing()
{

   //set_TranslateMessage(&axis_TranslateMessage);

   //set_DispatchMessage(&axis_DispatchMessage);

   oswindow_data::s_pdataptra = new oswindow_dataptra;

   oswindow_data::s_pmutex = new mutex;

   return true;

}


void os_term_windowing()
{

   ::aura::del(oswindow_data::s_pmutex);

   ::aura::del(oswindow_data::s_pdataptra);

}


WINBOOL is_window(oswindow oswindow)
{

   if (::oswindow_data::s_pdataptra->find_first(oswindow) < 0)
   {

      return FALSE;

   }

   return TRUE;

}


i64 oswindow_id(oswindow w)
{

   return (i64)(w);

}

