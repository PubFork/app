#include "framework.h"
#include "linux_user_impl.h"
#include <X11/Xatom.h>
#include <sys/stat.h>



Display * x11_get_display();
void wm_toolwindow(oswindow w,bool bToolWindow);
void wm_state_hidden_raw(oswindow w, bool bSet);
CLASS_DECL_AURA int_bool mq_remove_window_from_all_queues(oswindow oswindow);


#ifdef LINUX
int32_t _c_XErrorHandler(Display * display, XErrorEvent * perrorevent);
#endif


struct MWMHints
{

   unsigned long flags;
   unsigned long functions;
   unsigned long decorations;
   long input_mode;
   unsigned long status;

};


#define MWM_HINTS_DECORATIONS   (1L << 1)


/* MWM decorations values */
#define MWM_DECOR_NONE          0
#define MWM_DECOR_ALL           (1L << 0)
#define MWM_DECOR_BORDER        (1L << 1)
#define MWM_DECOR_RESIZEH       (1L << 2)
#define MWM_DECOR_TITLE         (1L << 3)
#define MWM_DECOR_MENU          (1L << 4)
#define MWM_DECOR_MINIMIZE      (1L << 5)
#define MWM_DECOR_MAXIMIZE      (1L << 6)


oswindow_data::oswindow_data()
{

   m_plongptrmap           = new int_ptr_to_int_ptr();

   m_hthread               = 0;

   m_window                = None;

   m_pimpl                 = NULL;

   m_bMessageOnlyWindow    = false;

   m_osdisplay             = NULL;

   ZERO(m_visual);

   m_iDepth                = -1;

   m_iScreen               = -1;

   m_colormap              = None;

}

oswindow_data::~oswindow_data()
{

   ::aura::del(m_plongptrmap);

}




oswindow_dataptra * oswindow_data::s_pdataptra = NULL;
mutex * oswindow_data::s_pmutex = NULL;


int32_t oswindow_find_message_only_window(::user::interaction_impl * pimpl)
{

   if(pimpl == NULL)
      return -1;

   single_lock slOsWindow(oswindow_data::s_pmutex, true);
   //
   //xdisplay d(x11_get_display());

   for(int32_t i = 0; i < ::oswindow_data::s_pdataptra->get_count(); i++)
   {

      if(::oswindow_data::s_pdataptra->element_at(i)->m_bMessageOnlyWindow
      && ::oswindow_data::s_pdataptra->element_at(i)->m_pimpl == pimpl)
      {

         return i;

      }

   }

   return -1;

}

int32_t oswindow_find(Display * pdisplay, Window window)
{

   single_lock slOsWindow(::oswindow_data::s_pmutex, true);
   //xdisplay d(x11_get_display());

   for(int32_t i = 0; i < ::oswindow_data::s_pdataptra->get_count(); i++)
   {
      if(!::oswindow_data::s_pdataptra->element_at(i)->m_bMessageOnlyWindow
      &&  ::oswindow_data::s_pdataptra->element_at(i)->m_osdisplay->display() == pdisplay
      &&  ::oswindow_data::s_pdataptra->element_at(i)->m_window == window)
      {
         return i;
      }
   }

   return -1;

}

int32_t oswindow_find(Window window)
{

   single_lock slOsWindow(::oswindow_data::s_pmutex, true);
   //xdisplay d(x11_get_display());

   for(int32_t i = 0; i < ::oswindow_data::s_pdataptra->get_count(); i++)
   {
      if(!::oswindow_data::s_pdataptra->element_at(i)->m_bMessageOnlyWindow
      &&  ::oswindow_data::s_pdataptra->element_at(i)->m_window == window)
      {
         return i;
      }
   }

   return -1;

}

oswindow_data * oswindow_get_message_only_window(::user::interaction_impl * pui)
{

   if(pui == NULL)
      return NULL;

   //single_lock slUser(&user_mutex(), true);

   single_lock slOsWindow(::oswindow_data::s_pmutex, true);
   //xdisplay d(x11_get_display());

   int_ptr iFind = oswindow_find_message_only_window(pui);

   if(iFind >= 0)
      return ::oswindow_data::s_pdataptra->element_at(iFind);

   ::oswindow_data * pdata = new oswindow_data;

   pdata->m_bMessageOnlyWindow      = true;
   pdata->m_window                  = None;
   pdata->m_pimpl                   = pui;
   pdata->m_osdisplay               = NULL;
   pdata->m_parent                  = NULL;



   ::oswindow_data::s_pdataptra->add(pdata);

   return pdata;

}


oswindow_data * oswindow_get(Display * pdisplay, Window window, Visual * pvisual, int iDepth, int iScreen, Colormap colormap)
{

   //single_lock slUser(&user_mutex(), true);

   single_lock slOsWindow(::oswindow_data::s_pmutex, true);
//   xdisplay d(x11_get_display());

   int_ptr iFind = oswindow_find(pdisplay, window);

   if(iFind >= 0)
      return ::oswindow_data::s_pdataptra->element_at(iFind);

   ::oswindow_data * pdata = new ::oswindow_data;

   pdata->m_bMessageOnlyWindow      = false;
   pdata->m_osdisplay               = osdisplay_get(pdisplay);
   pdata->m_window                  = window;

   if(pvisual != NULL)
   {

      pdata->m_visual               = *pvisual;

   }

   pdata->m_iDepth                  = iDepth;
   pdata->m_iScreen                 = iScreen;
   pdata->m_colormap                = colormap;
   pdata->m_parent                  = NULL;


   ::oswindow_data::s_pdataptra->add(pdata);

   return pdata;

}

oswindow_data * oswindow_get(Window window)
{

   single_lock slOsWindow(::oswindow_data::s_pmutex, true);
//   xdisplay d(x11_get_display());

   int_ptr iFind = oswindow_find(window);

   if(iFind < 0)
      return NULL;

   return ::oswindow_data::s_pdataptra->element_at(iFind);

}

/*
oswindow::oswindow()
{

   m_pdata = NULL;

}

oswindow::oswindow(::user::interaction_base * pui)
{

   single_lock slOsWindow(s_pmutex, true);

   m_pdata = get_message_only_window(pui);



}

oswindow::oswindow(Display * pdisplay, Window window, Visual * pvisual)
{

   single_lock slOsWindow(s_pmutex, true);

   m_pdata = get(pdisplay, window);

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


oswindow oswindow_defer_get(Window window)
{

   return oswindow_get(window);

}



bool oswindow_remove(Display * pdisplay, Window window)
{

   //single_lock slOsWindow(::oswindow_data::s_pmutex, true);
   xdisplay d(x11_get_display());

   int_ptr iFind = oswindow_find(pdisplay, window);

   if(iFind < 0)
      return false;

   delete ::oswindow_data::s_pdataptra->element_at(iFind);

   ::oswindow_data::s_pdataptra->remove_at(iFind);

   return true;

}


bool oswindow_remove_message_only_window(::user::interaction_impl * puibaseMessageOnlyWindow)
{

   //single_lock slOsWindow(::oswindow_data::s_pmutex, true);
   xdisplay d(x11_get_display());

   int_ptr iFind = oswindow_find_message_only_window(puibaseMessageOnlyWindow);

   if(iFind < 0)
      return false;

   delete ::oswindow_data::s_pdataptra->element_at(iFind);

   ::oswindow_data::s_pdataptra->remove_at(iFind);

   return true;

}


int32_t oswindow_data::store_name(const char * psz)
{

   //single_lock sl(&user_mutex(), true);

   //single_lock slOsWindow(s_pmutex, true);

   xdisplay d(display());

   return XStoreName(display(), window(), psz);

}


int32_t oswindow_data::select_input(int32_t iInput)
{


   //single_lock sl(&user_mutex(), true);

   //single_lock slOsWindow(s_pmutex, true);

   xdisplay d(display());

   return XSelectInput(display(), window(), iInput);

}


int32_t oswindow_data::select_all_input()
{

   xdisplay d(display());

   return select_input(ExposureMask | ButtonPressMask);

}


int32_t oswindow_data::map_window()
{


   //single_lock sl(&user_mutex(), true);

   //single_lock slOsWindow(s_pmutex, true);

   xdisplay d(display());

   return XMapWindow(display(), window());

}


void oswindow_data::post_nc_destroy()
{

   //single_lock slOsWindow(s_pmutex, true);

   oswindow_remove(display(), window());

}


void oswindow_data::set_user_interaction(::user::interaction_impl * pimpl)
{

   single_lock slOsWindow(s_pmutex, true);

//   xdisplay d(x11_get_display());

   if(this == NULL)
      _throw(simple_exception(get_app(), "error, m_pdata cannot be NULL to ::oswindow::set_user_interaction"));

   m_pimpl = pimpl;

   m_hthread = pimpl->m_pauraapp->get_os_handle();

   oswindow_assign(this, pimpl);

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


Window oswindow_data::get_parent_handle()
{

   single_lock slOsWindow(s_pmutex, true);

//   xdisplay d(x11_get_display());

   if(this == NULL)
      return 0;

   if(m_parent)

   return m_parent;

}


oswindow oswindow_data::get_parent()
{

   //single_lock sl(&user_mutex(), true);

   //single_lock slOsWindow(s_pmutex, true);
   xdisplay d(x11_get_display());

   if(this == NULL)
      return NULL;

   return NULL;

//   return oswindow_get(display(), get_parent_handle());

}

oswindow oswindow_data::set_parent(oswindow oswindow)
{

   //single_lock sl(&user_mutex(), true);

   //single_lock slOsWindow(s_pmutex, true);

   //xdisplay d(x11_get_display());

   if(this == NULL)
      return NULL;

   xdisplay d(display());

   ::oswindow oswindowOldParent = get_parent();

   XReparentWindow(display(), window(), oswindow->window(), 0, 0);

   return oswindowOldParent;

}


/**
 * Post an event from the client to the X server
 */
void oswindow_data::send_client_event(Atom atom, unsigned int numArgs, ...)
{
	XEvent xevent;
	unsigned int i;
	va_list argp;
	va_start(argp, numArgs);
   ZERO(xevent);
	xevent.xclient.type = ClientMessage;
	xevent.xclient.serial = 0;
	xevent.xclient.send_event = False;
	xevent.xclient.display = display();
	xevent.xclient.window = window();
	xevent.xclient.message_type = atom;
	xevent.xclient.format = 32;

	for (i = 0; i < numArgs; i++)
	{
		xevent.xclient.data.l[i] = va_arg(argp, int);
	}

//	DEBUG_X11("Send ClientMessage Event: wnd=0x%04X",
	//          (unsigned int) xevent.xclient.window);
	XSendEvent(display(), RootWindow(display(), m_iScreen), False, SubstructureRedirectMask | SubstructureNotifyMask, &xevent);
	XSync(display(), False);
	va_end(argp);
}

bool oswindow_data::show_window(int32_t nCmdShow)
{

   //single_lock sl(&user_mutex(), true);

   //single_lock slOsWindow(s_pmutex, true);

   xdisplay d(display());

   if(d.is_null())
   {

      return false;

   }

   if(nCmdShow == SW_HIDE)
   {

      XWindowAttributes attr;

      if(!XGetWindowAttributes(display(), window(), &attr))
      {

         return false;

      }

      if(attr.map_state == IsViewable)
      {

         XWithdrawWindow(display(), window(), m_iScreen);
         //XUnmapWindow();

      }

   }
   else if(nCmdShow == SW_MAXIMIZE)
   {

			/* Set the window as maximized */
      send_client_event(XInternAtom(display(), "_NET_WM_STATE", false), 4,
                        XInternAtom(display(), "_NET_WM_STATE_ADD", false),
                        XInternAtom(display(), "_NET_WM_STATE_MAXIMIZED_VERT", false),
                        XInternAtom(display(), "_NET_WM_STATE_MAXIMIZED_HORZ", false), 0);

			/*
			 * This is a workaround for the case where the window is maximized locally before the rail server is told to maximize
			 * the window, this appears to be a race condition where the local window with incomplete data and once the window is
			 * actually maximized on the server - an update of the new areas may not happen. So, we simply to do a full update of
			 * the entire window once the rail server notifies us that the window is now maximized.
			 */
//			if (appWindow->rail_state == WINDOW_SHOW_MAXIMIZED)
//			{
//				xf_UpdateWindowArea(xfc, appWindow, 0, 0, appWindow->windowWidth,
//				                    appWindow->windowHeight);
//			}

   }
   else if(nCmdShow == SW_MINIMIZE)
   {

      XIconifyWindow(display(), window(), m_iScreen);

   }
   else
   {

      /* Ensure the window is not maximized */
      send_client_event(XInternAtom(display(), "_NET_WM_STATE", false), 4,
                        XInternAtom(display(), "_NET_WM_STATE_REMOVE", false),
                        XInternAtom(display(), "_NET_WM_STATE_MAXIMIZED_VERT", false),
                        XInternAtom(display(), "_NET_WM_STATE_MAXIMIZED_HORZ", false), 0);

   }

   XFlush(display());

}



LONG_PTR oswindow_data::get_window_long_ptr(int32_t nIndex)
{

   return m_plongptrmap->operator[](nIndex);

/*   Atom type = 0;
   int32_t format = 0;
   unsigned long itemcount = 0;
   unsigned long remaining = 0;
   LONG * pl = NULL;
   LONG l;

   if(XGetWindowProperty(display(), window(), m_pdata->m_osdisplay.get_window_long_atom(nIndex), 0, 1, False, m_pdata->m_osdisplay.atom_long_type(), &type, &format, &itemcount, &remaining, (unsigned char **) &pl) == Success)
   {

      if(pl != NULL)
      {

         l = *pl;

         XFree(pl);

      }
      else
      {

         l = 0;

      }

   }
   else
   {

      l = 0;

   }


   return l;*/

}


LONG_PTR oswindow_data::set_window_long_ptr(int32_t nIndex, LONG_PTR l)
{

   LONG_PTR lOld = m_plongptrmap->operator[](nIndex);

   if(nIndex == GWL_EXSTYLE)
   {

      if((l & WS_EX_TOOLWINDOW) ^ (m_plongptrmap->operator[](nIndex) & WS_EX_TOOLWINDOW) != 0)
      {

         wm_toolwindow(this, (l & WS_EX_TOOLWINDOW) != 0);

      }

   }

   m_plongptrmap->operator[](nIndex) = l;


/*   LONG lOld = get_window_long(nIndex);

   XChangeProperty(display(), window(), m_osdisplay.get_window_long_atom(nIndex), m_osdisplay.atom_long_type(), 32, PropModeReplace, (unsigned char *) &l, 1);*/

   return lOld;

}


bool oswindow_data::client_to_screen(POINT * pp)
{

   return true;

}


bool oswindow_data::screen_to_client(POINT * pp)
{

   return true;

}

Atom get_window_long_atom(int32_t nIndex);




long oswindow_data::get_state()
{


  //single_lock sl(&user_mutex(), true);

  xdisplay d(display());

  static const long WM_STATE_ELEMENTS = 2L;

  unsigned long nitems = 0;
  unsigned long leftover = 0;
  Atom xa_WM_STATE = 0;
  Atom actual_type = 0;
  int32_t actual_format = 0;
  int32_t status = 0;
  unsigned char* p = NULL;

  xa_WM_STATE = XInternAtom(display(), "WM_STATE", false);

  status = XGetWindowProperty(display(), window(), xa_WM_STATE, 0L, WM_STATE_ELEMENTS, False, xa_WM_STATE, &actual_type, &actual_format, &nitems, &leftover, &p);


  if(status == 0)
  {
     long lStatus = -1;
     if(p!= NULL)
      lStatus = (long)*p;
      XFree(p);
      return lStatus;
  }

  return -1;

}




bool oswindow_data::is_iconic()
{

   return get_state() == IconicState;

}

bool oswindow_data::is_window_visible()
{

   xdisplay d(display());

   if(d.m_pdata->m_pdisplay == NULL)
      return false;

   XWindowAttributes attr;

   if(!XGetWindowAttributes(display(), window(), &attr))
      return false;

   return attr.map_state == IsViewable;

}






static oswindow g_oswindowCapture;


oswindow GetCapture()
{
      return g_oswindowCapture;
}

oswindow SetCapture(oswindow window)
{

   //single_lock sl(&user_mutex(), true);

   oswindow windowOld(g_oswindowCapture);

   if(window->display() == NULL)
      return NULL;

   if(window->window() == None)
      return NULL;

   xdisplay d(window->display());

   if(XGrabPointer(window->display(), window->window(), False, ButtonPressMask | ButtonReleaseMask | PointerMotionMask, GrabModeAsync, GrabModeAsync, None, None, CurrentTime) == GrabSuccess)
   {

      g_oswindowCapture = window;

      return windowOld;

   }

   return NULL;

}


WINBOOL ReleaseCapture()
{

   //single_lock sl(&user_mutex(), true);

   if(g_oswindowCapture == NULL)
      return FALSE;

   xdisplay d(g_oswindowCapture->display());


   WINBOOL bRet = XUngrabPointer(g_oswindowCapture->display(), CurrentTime) != FALSE;

   if(bRet)
      g_oswindowCapture = NULL;

   return bRet;

}


oswindow SetFocus(oswindow window)
{

   //single_lock sl(&user_mutex(), true);

   if(window == NULL)
      return NULL;

   xdisplay display(window->display());

   if(!IsWindow(window))
      return NULL;

   oswindow windowOld = ::GetFocus();

   if(!IsWindowVisible(window))
      return NULL;

   if(!XSetInputFocus(window->display(), window->window(), RevertToNone, CurrentTime))
      return NULL;

   return windowOld;

}

oswindow GetFocus()
{

   //single_lock sl(&user_mutex(), true);

   xdisplay pdisplay;

   pdisplay.open(NULL);

   if(pdisplay == NULL)
      return NULL;

   Window window = None;

   int revert_to = 0;

   bool bOk = XGetInputFocus(pdisplay, &window, &revert_to) != 0;

    pdisplay.close();

   if(!bOk)
      return NULL;

   if(window == None || window == PointerRoot)
      return NULL;

   return oswindow_defer_get(window);

}


oswindow GetActiveWindow()
{

   return GetFocus();

}


oswindow SetActiveWindow(oswindow window)
{

   return SetFocus(window);

}


oswindow oswindow_get_next_found(Display * pdisplay, long *array, int iStart, int numItems)
{

   for(index i = iStart; i < numItems; i++)
   {

      if(::oswindow_find(array[i]) >= 0)
      {

         return ::oswindow_get(array[i]);

      }

   }

   return NULL;

}

oswindow oswindow_get_previous_found(Display * pdisplay, long *array, int iStart)
{

   for(index i = iStart; i >= 0; i--)
   {

      if(::oswindow_find(array[i]) >= 0)
      {

         return ::oswindow_get(array[i]);

      }

   }

   return NULL;

}


oswindow oswindow_get_next_found(Window *array, int iStart, int numItems)
{

   for(index i = iStart; i < numItems; i++)
   {

      if(::oswindow_find(array[i]) >= 0)
      {

         return ::oswindow_get(array[i]);

      }

   }

   return NULL;

}

oswindow oswindow_get_previous_found(Window *array, int iStart)
{

   for(index i = iStart; i >= 0; i--)
   {

      if(::oswindow_find(array[i]) >= 0)
      {

         return ::oswindow_get(array[i]);

      }

   }

   return NULL;

}

oswindow GetWindow(oswindow windowParam, int iParentHood)
{

   //single_lock sl(&user_mutex(), true);

   oswindow window = windowParam;

   if(window == NULL)
      return NULL;

   xdisplay d(window->display());

   Window w = window->window();

   if(iParentHood == GW_HWNDFIRST
   || iParentHood == GW_HWNDLAST
   || iParentHood == GW_HWNDNEXT
   || iParentHood == GW_HWNDPREV)
   {

      window = ::GetParent(window);

      if(window == NULL)
      {

         window = windowParam;

         w = window->get_parent_handle();

      Atom a = XInternAtom(windowParam->display(), "_NET_CLIENT_LIST_STACKING" , False);
      Atom actualType;
      int format;
      unsigned long numItems, bytesAfter;
      unsigned char *data =0;
      int status = XGetWindowProperty(windowParam->display(),
                           RootWindow(windowParam->display(), windowParam->m_iScreen),
                           a,
                           0L,
                           1024,
                           false,
                           AnyPropertyType,
                           &actualType,
                           &format,
                           &numItems,
                           &bytesAfter,
                           &data);

         if (status >= Success && numItems)
         {
            // success - we have data: Format should always be 32:
      //		Q_ASSERT(format == 32);
            // cast to proper format, and iterate through values:
            long *array = (long*) data;
            //for (quint32 k = 0; k < numItems; k++)
            //{
               // get window Id:
               //Window w = (Window) array[k];

               //qDebug() << "Scanned client window:" << w;
            //}
         switch(iParentHood)
         {
            case GW_CHILD:
            case GW_HWNDFIRST:
            {

               if(data == NULL)
                  return NULL;

               window = oswindow_get_next_found(windowParam->display(), array, 0, numItems);

            }
            break;
            case GW_HWNDLAST:
            {

               if(data == NULL)
                  return NULL;

               window = oswindow_get_previous_found(windowParam->display(), array, numItems - 1);

            }
            break;
            case GW_HWNDNEXT:
            case GW_HWNDPREV:
            {

               if(data == NULL) // ????
                  return NULL;

               int iFound = -1;

               for(int i = 0; i < numItems; i++)
               {
                     if(array[i] == windowParam->window())
                     {
                        iFound = i;
                        break;
                     }
               }

               if(iFound < 0)
               {
                  XFree(data);
                  return NULL;
               }

               if(iParentHood == GW_HWNDNEXT)
               {

                  if(iFound + 1 >= numItems)
                  {
                     XFree(data);
                     return NULL;
                  }

                    window = ::oswindow_get_next_found(windowParam->display(), array, iFound + 1, numItems);

               }
               else
               {

                  if(iFound - 1 < 0)
                  {
                     XFree(data);
                     return NULL;
                  }

                  window = ::oswindow_get_previous_found(windowParam->display(), array, iFound - 1);


               }

            }

         }
         XFree(data);
         return window;

         }
      }

   }

   Window root = 0;
   Window parent = 0;
   Window * pchildren = NULL;
   uint32_t ncount = 0;


   XQueryTree(window->display(), w, &root, &parent, &pchildren, &ncount);

   switch(iParentHood)
   {
      case GW_CHILD:
      case GW_HWNDFIRST:
      {

         if(pchildren == NULL)
            return NULL;

         window = ::oswindow_get_next_found(pchildren, 0, ncount);

      }
      break;
      case GW_HWNDLAST:
      {

         if(pchildren == NULL)
            return NULL;

         window = ::oswindow_get_previous_found(pchildren, ncount - 1);

      }
      break;
      case GW_HWNDNEXT:
      case GW_HWNDPREV:
      {

         if(pchildren == NULL) // ????
            return NULL;

         int iFound = -1;

         for(int i = 0; i < ncount; i++)
         {
               if(pchildren[i] == windowParam->window())
               {
                  iFound = i;
                  break;
               }
         }

         if(iFound < 0)
            return NULL;

         if(iParentHood == GW_HWNDNEXT)
         {

            if(iFound + 1 >= ncount)
               return NULL;

            window = ::oswindow_get_next_found(pchildren, iFound + 1, ncount);

         }
         else
         {

            if(iFound - 1 < 0)
               return NULL;

            window = ::oswindow_get_previous_found(pchildren, iFound - 1);

         }

      }

   }


   if(pchildren != NULL)
      XFree(pchildren);


   return window;

}



WINBOOL DestroyWindow(oswindow window)
{

   //single_lock sl(&user_mutex(), true);

   if(!IsWindow(window) && !window->is_destroying())
      return FALSE;

   Display * pdisplay = window->display();

   Window win = window->window();

   oswindow_data * pdata = (oswindow_data *) (void *) window;

//   pdata->m_bDestroying = true;
//
//   for(index i = 0; i < pdata->m_bptraTellMeDestroyed.get_count(); i++)
//   {
//
//      *pdata->m_bptraTellMeDestroyed[i] = true;
//
//   }

   bool bIs = IsWindow(window);

   sp(::user::interaction) pui = window->m_pimpl->m_pui;

   pui->send_message(WM_DESTROY, 0, 0);

   mq_remove_window_from_all_queues(window);

   pui->send_message(WM_NCDESTROY, 0, 0);

   oswindow_remove(window->m_pimpl);

   oswindow_remove(pdisplay, win);

   xdisplay d(pdisplay);

   XUnmapWindow(pdisplay, win);

   XSync(pdisplay, False);

   XDestroyWindow(pdisplay, win);

   XSync(pdisplay, False);

   return true;

}


bool oswindow_data::is_destroying()
{

   if(this == NULL)
      return true;

   if(m_pimpl == NULL)
      return true;

   if(!m_pimpl->m_pui->m_bUserElementalOk)
      return true;

   return false;

}


WINBOOL IsWindow(oswindow oswindow)
{

   if(oswindow == NULL)
   {

      return false;

   }

   if(oswindow->display() == NULL)
   {

      return false;

   }

   if(oswindow->window() == None)
   {

      return false;

   }

   if(oswindow->m_pimpl == NULL)
   {

      return true;

   }

   if(!oswindow->m_pimpl->m_pui->m_bUserElementalOk)
   {

      return false;

   }

   return true;

}


oswindow g_oswindowDesktop;
Display * x11_get_display();

bool c_xstart()
{


   if(!XInitThreads())
      return -1;



   Display * dpy = x11_get_display();

   g_oswindowDesktop = oswindow_get(dpy, DefaultRootWindow(dpy));

   XSelectInput(g_oswindowDesktop->display(), g_oswindowDesktop->window(), StructureNotifyMask);

   return true;

}



oswindow GetDesktopWindow()
{

return g_oswindowDesktop;
}



#include "framework.h"

#include <X11/Xatom.h>


//extern cairo_surface_t *  g_cairosurface;
//extern cairo_t *  g_cairo;



























































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


//#include "cairo/cairo-xlib.h"
#include <X11/Xlib.h>


#define SIZEX 100
#define SIZEY  50


void message_box_paint(::draw2d::graphics * pgraphics, stringa & stra, bool_array  & baTab, int_array  & ya,SIZE * psize)
{

	pgraphics->FillSolidRect(0, 0, psize->cx, psize->cy, RGB(84, 90, 80));

   draw2d::brush_sp pen(pgraphics->allocer());

	pen->create_solid(0);

	for(index i = 0; i < stra.get_count(); i++)
	{
      pgraphics->text_out(10.0 + 50.0 + (baTab[i] ? 25.0 : 0), 10.0 + 50.0 + ya[i], stra[i]);
	}



}

#define _NET_WM_STATE_REMOVE        0    // remove/unset property
#define _NET_WM_STATE_ADD           1    // add/set property
#define _NET_WM_STATE_TOGGLE        2    // toggle property

Atom * wm_get_list_raw(oswindow w, Atom atomList, unsigned long int * items);
int wm_test_state(oswindow w, const char * pszNetStateFlag);
int wm_test_state_raw(oswindow w, const char * pszNetStateFlag);
int wm_test_list_raw(oswindow w, Atom atomList, Atom atomFlag);
bool wm_add_remove_list_raw(oswindow w, Atom atomList, Atom atomFlag, bool bSet);

void wm_add_remove_state_mapped_raw(oswindow w, const char * pszNetStateFlag, bool bSet)
{

   Display * display = w->display();

   Window window = w->window();

   int scr=DefaultScreen(display);

   Window rootw=RootWindow(display,scr);

   Atom atomFlag = XInternAtom(display, pszNetStateFlag, 1);

   if( atomFlag == None )
   {

      output_debug_string("ERROR: cannot find atom for " + string(pszNetStateFlag) + "!\n");

      return;

   }

   Atom atomNetState = XInternAtom(display, "_NET_WM_STATE", 1);

   if( atomNetState == None )
   {

      output_debug_string("ERROR: cannot find atom for _NET_WM_STATE !\n");

      return;

   }

   if(wm_test_list_raw(w, atomNetState, atomFlag))
   {

      if(bSet)
      {

         return;

      }

   }
   else
   {

      if(!bSet)
      {

         return;

      }


   }


   XClientMessageEvent xclient;

   ZERO(xclient);

   xclient.type            = ClientMessage;
   xclient.window          = window;
   xclient.message_type    = atomNetState;
   xclient.format          = 32;
   xclient.data.l[0]       = bSet ? _NET_WM_STATE_ADD : _NET_WM_STATE_REMOVE;
   xclient.data.l[1]       = atomFlag;
   xclient.data.l[2]       = 0;
   xclient.data.l[3]       = 0;
   xclient.data.l[4]       = 0;

   XSendEvent(display, rootw, False, SubstructureRedirectMask | SubstructureNotifyMask, (XEvent *)&xclient );

}

void wm_add_remove_state_mapped(oswindow w, const char * pszNetStateFlag, bool bSet)
{

   xdisplay d(w->display());

   wm_add_remove_state_mapped_raw(w, pszNetStateFlag, bSet);

}

void wm_add_remove_state_unmapped_raw(oswindow w, const char * pszNetStateFlag, bool bSet)
{

   Display * display = w->display();

   Window window = w->window();

   int scr=DefaultScreen(display);

   Window rootw=RootWindow(display,scr);

   Atom atomFlag = XInternAtom(display, pszNetStateFlag, 1);

   if( atomFlag == None )
   {

      output_debug_string("ERROR: cannot find atom for " + string(pszNetStateFlag) + "!\n");

      return;

   }

   Atom atomNetState = XInternAtom(display, "_NET_WM_STATE", 1);

   if( atomNetState == None )
   {

      output_debug_string("ERROR: cannot find atom for _NET_WM_STATE !\n");

      return;

   }

   wm_add_remove_list_raw(w, atomNetState, atomFlag, bSet);

}

void wm_add_remove_state_unmapped(oswindow w, const char * pszNetStateFlag, bool bSet)
{

   xdisplay d(w->display());

   wm_add_remove_state_unmapped_raw(w, pszNetStateFlag, bSet);

}

void wm_add_remove_state_raw(oswindow w, const char * pszState, bool bSet)
{

   if(IsWindowVisibleRaw(w))
   {

      wm_add_remove_state_mapped_raw(w, pszState, bSet);

   }
   else
   {

      wm_add_remove_state_unmapped_raw(w, pszState, bSet);

   }

}


void wm_add_remove_state(oswindow w, const char * pszState, bool bSet)
{

   xdisplay d(w->display());

   wm_add_remove_state_raw(w, pszState, bSet);

}


void wm_state_above_raw(oswindow w, bool bSet)
{

   wm_add_remove_state_raw(w, "_NET_WM_STATE_HIDDEN", false);

   wm_add_remove_state_raw(w, "_NET_WM_STATE_BELOW", false);

   wm_add_remove_state_raw(w, "_NET_WM_STATE_ABOVE", bSet);

}


void wm_state_below_raw(oswindow w, bool bSet)
{

   wm_add_remove_state_raw(w, "_NET_WM_STATE_HIDDEN", false);

   wm_add_remove_state_raw(w, "_NET_WM_STATE_ABOVE", false);

   wm_add_remove_state_raw(w, "_NET_WM_STATE_BELOW", bSet);

}


void wm_state_hidden_raw(oswindow w, bool bSet)
{

   wm_add_remove_state_raw(w, "_NET_WM_STATE_BELOW", false);

   wm_add_remove_state_raw(w, "_NET_WM_STATE_ABOVE", false);

   wm_add_remove_state_raw(w, "_NET_WM_STATE_HIDDEN", bSet);

}


void wm_state_above(oswindow w, bool bSet)
{

   xdisplay d(w->display());

   wm_state_above_raw(w, bSet);

}

void wm_state_below(oswindow w, bool bSet)
{

   xdisplay d(w->display());

   wm_state_above_raw(w, bSet);

}


void wm_state_hidden(oswindow w, bool bSet)
{

   xdisplay d(w->display());

   wm_state_hidden_raw(w, bSet);

}


void wm_toolwindow(oswindow w,bool bToolWindow)
{

   xdisplay d(w->display());

   Display * display = w->display();

   Window window = w->window();

   int scr=DefaultScreen(display);

   Window rootw=RootWindow(display,scr);

   Atom atomWindowType = XInternAtom(display,"_NET_WM_WINDOW_TYPE",False);

   if(atomWindowType != None)
   {

      Atom atomWindowTypeValue;

      if(bToolWindow)
      {

         atomWindowTypeValue = XInternAtom(display,"_NET_WM_WINDOW_TYPE_SPLASH",False);

      }
      else
      {

         atomWindowTypeValue = XInternAtom(display,"_NET_WM_WINDOW_TYPE_NORMAL",False);

      }

      if(atomWindowType != None)
      {

         XChangeProperty(display,window,atomWindowType,XA_ATOM,32,PropModeReplace, (unsigned char *)&atomWindowTypeValue,1);

      }

   }

   wm_add_remove_state(w, "_NET_WM_STATE_SKIP_TASKBAR", bToolWindow);

}


void wm_nodecorations(oswindow w, int map)
{

   int set;

   xdisplay d(w->display());

   Display * dpy = w->display();

   Window window = w->window();

   int scr=DefaultScreen(dpy);

   Window rootw=RootWindow(dpy,scr);

   Atom atomMotifHints = XInternAtom(dpy,"_MOTIF_WM_HINTS",True);

   if(atomMotifHints != None)
   {

      MWMHints hints = {MWM_HINTS_DECORATIONS,0, MWM_DECOR_NONE,0,0};

      XChangeProperty(dpy,window,atomMotifHints,atomMotifHints,32, PropModeReplace,(unsigned char *)&hints, sizeof(MWMHints) / 4);

   }

//   WM_HINTS = XInternAtom(dpy,"KWM_WIN_DECORATION",True);
//   if(WM_HINTS != None)
//   {
//      long KWMHints = KDE_tinyDecoration;
//      XChangeProperty(dpy,window,WM_HINTS,WM_HINTS,32,
//         PropModeReplace,(unsigned char *)&KWMHints,
//         sizeof(KWMHints) / 4);
//   }

//   WM_HINTS = XInternAtom(dpy,"_WIN_HINTS",True);
//   if(WM_HINTS != None) {
//      long GNOMEHints = 0;
//      XChangeProperty(dpy,window,WM_HINTS,WM_HINTS,32,
//         PropModeReplace,(unsigned char *)&GNOMEHints,
//         sizeof(GNOMEHints) / 4);
//   }
//   WM_HINTS = XInternAtom(dpy,"_NET_WM_WINDOW_TYPE",True);
//   if(WM_HINTS != None) {
//      Atom NET_WMHints[2];
//      NET_WMHints[0] = XInternAtom(dpy,
//         "_KDE_NET_WM_WINDOW_TYPE_OVERRIDE",True);
//      NET_WMHints[1] = XInternAtom(dpy,"_NET_WM_WINDOW_TYPE_TOOLBAR",True);
//      XChangeProperty(dpy,window,
//         WM_HINTS,XA_ATOM,32,PropModeReplace,
//         (unsigned char *)&NET_WMHints,2);
//   }
   //XSetTransientForHint(dpy,window,rootw);

   if(map)
   {

      XUnmapWindow(dpy,window);

      XMapWindow(dpy,window);

   }

}



void wm_iconify_window(oswindow w)
{

   xdisplay d(w->display());

   Display * display = w->display();

   Window window = w->window();

   int scr=DefaultScreen(display);

   XIconifyWindow(display, window, scr);

}




WINBOOL IsWindowVisibleRaw(Display * display, Window window)
{

   XWindowAttributes attr;

   if(!XGetWindowAttributes(display, window, &attr))
      return false;

   return attr.map_state == IsViewable;

}



WINBOOL IsWindowVisibleRaw(oswindow w)
{

   Display * display = w->display();

   Window window = w->window();

   return IsWindowVisibleRaw(display, window);

}

Atom * wm_get_list_raw(oswindow w, Atom atomList, unsigned long int * pnum_items)
{


   if(atomList == None )
   {

      return NULL;

   }

   Display * display = w->display();

   Window window = w->window();

   Atom actual_type;

   int actual_format;

   unsigned long int bytes_after;

   Atom *atoms = NULL;

   XGetWindowProperty(display, window, atomList, 0, 1024, False, XA_ATOM, &actual_type, &actual_format, pnum_items, &bytes_after, (unsigned char**)&atoms);

   return atoms;

}


int wm_test_list_raw(oswindow w, Atom atomList, Atom atomFlag)
{

   Display * display = w->display();

   Window window = w->window();

   Atom actual_type;

   int actual_format;

   unsigned long i, num_items;

   Atom *atoms = wm_get_list_raw(w, atomList, &num_items);

   if(atoms == NULL)
   {

      return 0;

   }

   bool bFind = false;

   for(i = 0; i < num_items; i++)
   {

      if(atoms[i] == atomFlag)
      {

         bFind = true;

         break;

      }

   }

   XFree(atoms);

   return bFind ? 1 : 0;

}


int wm_test_state_raw(oswindow w, const char * pszNetStateFlag)
{

   Atom atomFlag = XInternAtom(w->display(), pszNetStateFlag, 1);

   if( atomFlag == None )
   {

      output_debug_string("ERROR: cannot find atom for " + string(pszNetStateFlag) + "!\n");

      return 0;

   }

   Atom atomNetState = XInternAtom(w->display(), "_NET_WM_STATE", 1);

   if( atomNetState == None )
   {

      output_debug_string("ERROR: cannot find atom for _NET_WM_STATE !\n");

      return 0;

   }

   return wm_test_list_raw(w, atomNetState, atomFlag);

}


int wm_test_state(oswindow w, const char * pszNetStateFlag)
{

   xdisplay d(w->display());

   return wm_test_state_raw(w, pszNetStateFlag);

}



bool wm_add_remove_list_raw(oswindow w, Atom atomList, Atom atomFlag, bool bSet)
{

   if( atomFlag == None )
   {

      return false;

   }

   if( atomList == None )
   {

      return false;

   }

   Display * display = w->display();

   Window window = w->window();

   int scr = DefaultScreen(display);

   Window rootw = RootWindow(display,scr);

   if(bSet)
   {

      if(!wm_test_list_raw(w, atomList, atomFlag))
      {

         XChangeProperty(display,window,atomList,XA_ATOM,32,PropModeAppend, (unsigned char *)&atomFlag,1);

      }

   }
   else
   {

      unsigned long num_items;

      Atom * plist = wm_get_list_raw(w, atomList, &num_items);

      if(plist == NULL)
      {

         return false;

      }

      int iFind = -1;

      int i;

      for(i = 0; i < num_items; i++)
      {

         if(plist[i] == atomFlag)
         {

            iFind = i;

            break;

         }

      }

      if(iFind >= 0)
      {

         memmove(&plist[iFind], &plist[iFind + 1], (num_items - iFind - 1) *sizeof(Atom));

         XChangeProperty(display,window,atomList,XA_ATOM,32,PropModeReplace, (unsigned char *)plist,num_items-1);

      }

      XFree(plist);

   }

   return true;

}


bool wm_set_icon(oswindow w, ::draw2d::dib * p)
{

   // http://stackoverflow.com/questions/10699927/xlib-argb-window-icon
   // http://stackoverflow.com/users/432509/ideasman42

   xdisplay d(w->display());


   #if 0

      unsigned int buffer[] = {
            16, 16,
            4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 338034905, 3657433343, 0, 184483840, 234881279, 3053453567, 3221225727, 1879048447, 0, 0, 0, 0, 0, 0, 0, 1224737023, 3305111807, 3875537151,0, 0, 2063597823, 1291845887, 0, 67109119, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 50266112, 3422552319, 0, 0, 3070230783, 2063597823, 2986344703, 771752191, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3422552319, 0, 0, 3372220671, 1509949695, 704643327, 3355443455, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 3422552319, 0, 134152192, 3187671295, 251658495, 0, 3439329535, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3422552319, 0, 0, 2332033279, 1342177535, 167772415, 3338666239, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 3422552319, 0, 0, 436207871, 3322085628, 3456106751, 1375731967, 4278255360, 4026597120, 3758161664, 3489726208, 3204513536, 2952855296, 2684419840, 2399207168, 2130771712, 1845559040, 1593900800, 1308688128, 1040252672, 755040000, 486604544, 234946304, 4278255360, 4043374336, 3774938880, 3506503424, 3221290752, 2952855296, 2667642624, 2399207168, 2130771712, 1862336256, 1627453957, 1359017481, 1073805064, 788591627, 503379721, 218169088, 4278255360, 4043374336, 3758161664, 3506503424, 3221290752, 2952855296, 2684419840, 2415984384, 2130771712, 1862336256, 1577123584, 1308688128, 1040252672, 755040000, 486604544, 218169088, 4278190335, 4026532095, 3758096639, 3489661183, 3221225727, 2952790271, 2667577599, 2415919359, 2130706687, 1862271231, 1593835775, 1325400319, 1056964863, 771752191, 520093951, 234881279, 4278190335, 4026532095, 3758096639, 3489661183, 3221225727, 2952790271, 2667577599, 2415919359, 2130706687, 1862271231, 1593835775, 1325400319, 1056964863, 771752191, 503316735, 234881279, 4278190335, 4026532095, 3758096639, 3489661183, 3221225727, 2952790271, 2684354815, 2399142143, 2130706687, 1862271231, 1593835775, 1325400319, 1040187647, 771752191, 520093951, 234881279, 4294901760, 4043243520, 3774808064, 3506372608, 3221159936, 2952724480, 2684289024, 2399076352, 2147418112, 1862205440, 1593769984, 1308557312, 1040121856, 771686400, 503250944, 234815488, 4294901760, 4060020736, 3758030848, 3506372608, 3221159936, 2952724480, 2684289024, 2415853568, 2130640896, 1862205440, 1593769984, 1308557312, 1040121856, 771686400, 503250944, 234815488, 4294901760, 4043243520, 3774808064, 3489595392, 3237937152, 2952724480, 2684289024, 2415853568, 2147418112, 1862205440, 1593769984, 1325334528, 1056899072, 788463616, 503250944, 234815488,
            32, 32,
            4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 0, 0, 0, 0, 0, 0, 0, 0, 268369920, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 1509949695, 3120562431, 4009754879, 4194304255, 3690987775, 2130706687, 83886335, 0, 50331903, 1694499071, 3170894079, 3992977663, 4211081471, 3657433343, 1879048447, 16777471, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3087007999, 2281701631, 1191182591, 1040187647, 2030043391, 4127195391, 2566914303, 0, 16777471, 3254780159, 2181038335, 1191182591, 973078783, 2030043391,4177527039, 2130706687, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 0, 0, 0, 0, 2214592767, 4093640959, 0, 0, 0, 0, 0, 0, 0, 2298478847, 3909091583, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2214592767, 3607101695, 0, 0, 0, 0, 0, 0, 0, 1946157311, 4093640959, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 0, 536871167, 1191182591, 2281701631,3019899135, 637534463, 0, 0, 0, 100597760, 251592704, 33488896, 0, 3321889023, 2919235839, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2550137087, 4278190335, 4278190335, 3405775103, 570425599, 0, 0, 0, 0, 0, 0, 2046820607, 4043309311, 620757247, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 33488896, 0, 0, 218104063, 1291845887, 3841982719, 3388997887, 0, 0, 0, 0, 0, 1996488959, 4093640959, 1073742079, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1761607935, 4278190335, 150995199, 0, 0, 67109119, 2550137087, 3909091583, 889192703, 0, 0, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 0, 0, 0, 0, 2181038335, 3925868799, 0, 0, 218104063, 3070230783, 3623878911, 570425599, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 805306623, 3288334591, 1795162367, 1040187647, 1023410431, 2231369983, 4211081471, 1694499071, 0, 369099007, 3456106751, 3825205503, 1174405375, 872415487, 872415487, 872415487, 872415487, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4293984270, 2046951677, 3422552319, 4110418175, 4177527039, 3405775103, 1409286399, 0, 0, 1409286399, 4278190335, 4278190335, 4278190335, 4278190335, 4278190335, 4278190335, 4278190335, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760,4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4278255360, 4144037632, 4009819904, 3875602176, 3741384448, 3607166720, 3472948992, 3338731264, 3204513536, 3053518592, 2936078080, 2801860352, 2650865408, 2516647680, 2382429952, 2264989440, 2113994496, 1996553984, 1862336256, 1728118528, 1577123584, 1459683072, 1325465344, 1191247616, 1040252672, 922812160, 771817216, 637599488, 503381760, 385941248, 234946304, 100728576, 4278255360, 4144037632, 4009819904, 3875602176, 3724607232, 3607166720, 3472948992, 3338731264, 3204513536, 3070295808, 2936078080, 2801860352, 2667642624, 2516647680, 2399207168, 2264989440, 2130771712, 1996553984, 1845559040, 1728118528, 1593900800, 1459683072, 1308688128, 1191247616, 1057029888, 922812160, 788594432, 637599488, 503381760, 369164032, 234946304, 117505792, 4278255360, 4144037632, 4009819904, 3875602176, 3741384448, 3607166720, 3472948992, 3338731264, 3204513536, 3053518592, 2919300864, 2801860352, 2650865408, 2533424896, 2399207168, 2264989440, 2113994496, 1996553984, 1862336256, 1728118528,1593900800, 1459683072, 1325465344, 1191247616, 1040252672, 906034944, 771817216, 654376704, 503381760, 369164032, 234946304, 117505792, 4278255360, 4144037632, 4009819904, 3858824960, 3741384448, 3607166720, 3472948992, 3338731264, 3204513536, 3070295808, 2936078080, 2801860352, 2667642624, 2533424896, 2382429952, 2264989440, 2130771712, 1979776768, 1862336256, 1728118528, 1577123584, 1442905856, 1325465344, 1191247616, 1040252672, 922812160, 771817216, 637599488, 503381760, 369164032, 234946304, 100728576, 4278255360, 4144037632, 4009819904, 3875602176, 3741384448, 3607166720, 3472948992, 3338731264, 3204513536, 3070295808, 2919300864, 2801860352, 2667642624, 2533424896, 2399207168, 2264989440, 2113994496, 1996553984, 1862336256, 1728118528, 1593900800, 1442905856, 1342241795, 1174470400, 1057029888, 906034944, 788594432, 654376704, 503381760, 385941248, 251723520, 100728576, 4278190335, 4160749823, 4026532095, 3892314367, 3741319423, 3623878911, 3472883967, 3338666239, 3221225727, 3070230783, 2952790271, 2818572543, 2667577599, 2533359871, 2399142143, 2264924415, 2147483903, 1996488959, 1862271231, 1728053503, 1593835775, 1459618047, 1325400319, 1191182591, 1056964863, 922747135, 788529407, 654311679, 520093951,385876223, 251658495, 117440767, 4278190335, 4160749823, 4026532095, 3892314367, 3741319423, 3623878911, 3489661183, 3355443455, 3221225727, 3087007999, 2936013055, 2801795327, 2667577599, 2533359871, 2399142143, 2281701631, 2130706687, 1996488959, 1862271231, 1728053503, 1593835775,1459618047, 1325400319, 1191182591, 1056964863, 922747135, 788529407, 654311679, 520093951, 385876223, 234881279, 100663551, 4278190335, 4160749823, 4026532095, 3892314367, 3758096639, 3623878911, 3489661183, 3355443455, 3221225727, 3087007999, 2936013055, 2801795327, 2667577599, 2550137087, 2415919359, 2264924415, 2130706687, 1996488959, 1862271231, 1728053503, 1593835775, 1459618047, 1325400319, 1191182591, 1056964863, 922747135, 788529407, 654311679, 503316735, 369099007, 251658495, 100663551, 4278190335, 4160749823, 4026532095, 3892314367, 3758096639, 3623878911, 3489661183, 3355443455, 3204448511, 3087007999, 2936013055, 2818572543, 2667577599, 2533359871, 2399142143, 2264924415, 2130706687, 1996488959, 1879048447, 1728053503, 1593835775, 1459618047, 1325400319, 1191182591, 1056964863, 922747135, 788529407, 654311679, 520093951, 385876223, 251658495, 117440767, 4278190335, 4160749823, 4026532095, 3892314367, 3758096639, 3623878911, 3489661183, 3355443455, 3221225727, 3087007999, 2952790271, 2818572543, 2667577599, 2533359871, 2399142143, 2264924415, 2147483903, 2013266175, 1862271231, 1744830719, 1610612991, 1476395263, 1342177535, 1191182591, 1056964863, 922747135, 788529407, 654311679, 520093951, 385876223, 251658495, 100663551, 4294901760, 4160684032, 4026466304, 3909025792, 3774808064, 3623813120, 3489595392, 3355377664, 3237937152, 3103719424, 2952724480, 2818506752, 2684289024, 2550071296, 2415853568, 2281635840, 2147418112, 2013200384, 1878982656, 1744764928, 1593769984, 1476329472,1325334528, 1207894016, 1056899072, 939458560, 788463616, 654245888, 520028160, 385810432, 251592704, 117374976, 4294901760, 4177461248, 4043243520, 3909025792, 3774808064, 3640590336, 3506372608, 3355377664, 3221159936, 3086942208, 2952724480, 2818506752, 2701066240, 2550071296, 2415853568, 2281635840, 2147418112, 2013200384, 1878982656, 1727987712, 1610547200, 1476329472, 1325334528, 1191116800, 1073676288, 922681344, 788463616, 654245888, 520028160, 385810432, 251592704, 100597760, 4294901760, 4177461248, 4043243520, 3909025792, 3774808064, 3640590336, 3489595392, 3372154880, 3237937152, 3103719424, 2952724480, 2818506752, 2700935170, 2550071296, 2415853568, 2281635840, 2147418112, 2013200384, 1878982656, 1744764928, 1610547200, 1459552256, 1342111744, 1191116800, 1056899072, 922681344, 788463616, 671023104, 520028160, 385810432, 251592704, 100597760, 4294901760, 4177461248, 4043243520, 3909025792, 3774808064, 3640590336, 3489595392, 3372154880, 3237937152, 3086942208, 2969501696, 2818506752, 2684289024, 2550071296, 2432630784, 2281635840, 2147418112, 2013200384, 1862205440, 1744764928, 1610547200, 1476329472, 1342111744, 1191116800, 1056899072, 922681344, 788463616, 654245888, 520028160, 385810432, 251592704, 117374976, 4294901760, 4177461248, 4043243520, 3909025792, 3774808064, 3623813120, 3506372608, 3372154880, 3237937152, 3103719424, 2952724480, 2835283968, 2684289024, 2550071296, 2432630784, 2281635840, 2147418112, 2046492676, 1862205440, 1744764928, 1610547200, 1476329472, 1342111744,1207894016, 1056899072, 939458560, 788463616, 654245888, 536281096, 385810432, 251592704, 134152192,
    };
    Display *display = w->display();
    int s = DefaultScreen(display);
    Atom net_wm_icon = XInternAtom(display, "_NET_WM_ICON", False);
    Atom cardinal = XInternAtom(d, "CARDINAL", False);
    //Window w;
    //XEvent e; //w = XCreateWindow(d, RootWindow(d, s), 0, 0, 200, 200, 0,
    //CopyFromParent, InputOutput, CopyFromParent, 0, 0);
    int length = 2 + 16 * 16 + 2 + 32 * 32;
    int status = XChangeProperty(d, w->window(), net_wm_icon, cardinal, 32, PropModeReplace, (const unsigned char*) buffer, length);
    //XMapWindow(d, w);
    //while(1)
    //XNextEvent(d, &e);
    //(void)argc, (void)argv;
//}
   if(status != 0)
   {

      //file_put_contents_dup("/home/camilo/window.txt", ::str::from((int)w->window()));
      return false;

   }
   #elif 1

      ::draw2d::dib_sp d1(w->m_pimpl->m_pui->allocer());

   if(!d1->create(32, 32))
   {

      return false;

   }

   d1->get_graphics()->SetStretchBltMode(HALFTONE);

   d1->get_graphics()->StretchBlt(0, 0, d1->m_size.cx, d1->m_size.cy, p->get_graphics(), 0, 0, p->m_size.cx, p->m_size.cy);

   memory m(w->m_pimpl->m_pui->get_app());

   int length = 2 + d1->area();

   m.allocate(length * 4);

   unsigned int * pcr = (unsigned int *) m.get_data();

   pcr[0] = d1->m_size.cx;

   pcr[1] = d1->m_size.cy;

   int c = d1->area();

   for(int i = 0; i < c; i++)
   {

      pcr[i+2] = d1->m_pcolorref[i];

   }

   Display *display = w->display();

   Atom net_wm_icon = XInternAtom(display, "_NET_WM_ICON", False);

   Atom cardinal = XInternAtom(display, "CARDINAL", False);

   int status = XChangeProperty(display, w->window(), net_wm_icon, cardinal, 32, PropModeReplace, (const unsigned char*) pcr, length);


   if(status == BadAlloc)
   {
   }
   if(status != 0)
   {

      //file_put_contents_dup("/home/camilo/window.txt", ::str::from((int)w->window()));
      return false;

   }

   #else



   ::draw2d::dib_sp d1(w->m_pimpl->m_pui->allocer());

   if(!d1->create(24, 24))
   {

      return false;

   }

   d1->get_graphics()->SetStretchBltMode(HALFTONE);

   d1->get_graphics()->StretchBlt(0, 0, d1->m_size.cx, d1->m_size.cy, p->get_graphics(), 0, 0, p->m_size.cx, p->m_size.cy);

   ::draw2d::dib_sp d2(w->m_pimpl->m_pui->allocer());

   if(!d2->create(54, 54))
   {

      return false;

   }

   d2->get_graphics()->SetStretchBltMode(HALFTONE);

   d2->get_graphics()->StretchBlt(0, 0, d2->m_size.cx, d2->m_size.cy, p->get_graphics(), 0, 0, p->m_size.cx, p->m_size.cy);

   memory m(w->m_pimpl->m_pui->get_app());

   int length = 2 + d1->area() + 2 + d2->area();

   m.allocate(length * 4);

   unsigned int * pcr = (unsigned int *) m.get_data();

   pcr[0] = d1->m_size.cx;

   pcr[1] = d1->m_size.cy;

   int c = d1->area();

   for(int i = 0; i < c; i++)
   {

      pcr[i+2] = d1->m_pcolorref[i];

   }

   memory_offset_t o;

   o = 2 + d1->area();

   pcr[o] = d2->m_size.cx;

   pcr[o+1] = d2->m_size.cy;

   c = d2->area();

   for(int i = 0; i < c; i++)
   {

      pcr[i+o+2] = d2->m_pcolorref[i];

   }

   Display *display = w->display();

   Atom net_wm_icon = XInternAtom(display, "_NET_WM_ICON", False);

   Atom cardinal = XInternAtom(display, "CARDINAL", False);

   int status = XChangeProperty(display, w->window(), net_wm_icon, cardinal, 32, PropModeReplace, (const unsigned char*) pcr, length);


   if(status != 0)
   {

      //file_put_contents_dup("/home/camilo/window.txt", ::str::from((int)w->window()));
      return false;

   }
#endif
   return true;

}


bool wm_set_icon(oswindow w, stringa & straMatter)
{

   ::aura::application * papp = w->m_pimpl->m_pui->get_app();

   ::file::path path;

   for (auto & strMatter : straMatter)
   {

      path = strMatter;

      path = App(papp).dir().matter(path / "linux.txt");

      if(App(papp).file().exists(path))
      {

         ::file::path path2;

         path2 = getenv("HOME");

         path2 /= ".local/share/applications";

         string strApp = App(papp).m_strAppName;

         strApp.replace("-", "_");
         strApp.replace("/", "_");
         strApp.replace(".", "_");

         path2 /= (strApp + ".desktop");

         if(!App(papp).file().exists(path2))
         {

            App(papp).file().copy(path2, path);

            chmod(path2, S_IRUSR | S_IWUSR );

         }

         xdisplay d(w->display());

         Atom net_wm_icon = XInternAtom(w->display(), "_BAMF_DESKTOP_FILE", False);

         Atom cardinal = XInternAtom(w->display(), "STRING", False);

         int ixa= XA_STRING;

         int status = XChangeProperty(w->display(), w->window(), net_wm_icon, ixa, 8, PropModeReplace, (const unsigned char*) (const char *) path2, path2.get_length());

         if(status != 0)
         {

            //file_put_contents_dup("/home/camilo/window.txt", ::str::from((int)w->window()));

            return false;

         }

         return true;

      }

   }

   return false;

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



CLASS_DECL_AURA ::user::interaction_impl * oswindow_get(oswindow oswindow)
{

   if (oswindow == NULL)
   {

      return NULL;

   }

#ifdef WINDOWSEX

   cslock slOsWindow(::user::g_pcsImpl);

   return ::user::g_pmapImpl->operator[](oswindow);

#else

   if (oswindow == NULL)
   {

      return NULL;

   }


   return oswindow->m_pimpl;

#endif

}


void process_message(osdisplay_data * pdata, Display * pdisplay);
void send_message(MESSAGE & msg);


bool g_bSkipMouseMessageInXcess = true;
DWORD g_dwLastMotion = 0;
DWORD g_dwMotionSkipTimeout = 23;

UINT __axis_x11_thread(void * p)
{

   osdisplay_data * pdata = (osdisplay_data *) p;

   Display * display = pdata->display();

   if(display == NULL)
   {

      return 0;

   }

   int x11_fd = ConnectionNumber(display);

   fd_set in_fds;

   MESSAGE msg;

   struct timeval tv;

   bool bPending;

   while(::aura::system::g_p != NULL && ::aura::system::g_p->thread_get_run())
   {

//      ZERO(msg);
//
//      FD_ZERO(&in_fds);
//
//      FD_SET(x11_fd, &in_fds);
//
//      tv.tv_usec = 0;
//
//      tv.tv_sec = 1;
//
//      int num_ready_fds = select(x11_fd + 1, &in_fds, NULL, NULL, &tv);
//
//      if (num_ready_fds > 0)
//      {
//
//         // Event Received
//
//      }
//      else if (num_ready_fds == 0)
//      {
//
//         // Timer fired
//
//      }
//      else
//      {
//
//         // Error
//
//      }

      bPending = false;

      {

         xdisplay d(display);

         bPending = XPending(display);

      }

      if(bPending)
      {

         process_message(pdata, display);

      }
      else
      {

         Sleep(1);

      }

   }

}

int g_xxx = 0;

void process_message(osdisplay_data * pdata, Display * display)
{

   XEvent e;

   MESSAGE msg;

   ZERO(msg);

   {

      xdisplay d(display);

      XNextEvent(display, &e);

   }

   bool bRet = false;

   if(e.type == Expose)
   {

      if(e.xexpose.count == 0)
      {

         msg.message       = WM_PAINT;
         msg.hwnd          = oswindow_get(display, e.xexpose.window);
         msg.lParam        = 0;
         msg.wParam        = 0;

         send_message(msg);

      }

   }
   else if(e.type == PropertyNotify)
   {

      msg.hwnd = oswindow_get(display, e.xproperty.window);



      if(msg.hwnd != NULL && msg.hwnd->m_pimpl != NULL)
      {

         ::user::interaction * pui = msg.hwnd->m_pimpl->m_pui;

         if(pui != NULL)
         {

            ::user::interaction_impl_base * pimpl = pui->m_pimpl;

            bool bHandled = false;

            if(pimpl != NULL)
            {

               g_xxx++;

               if(g_xxx >= 9)
               {
                  output_debug_string("g_xxx");
               }
               if(pui->m_eappearance == ::user::appearance_iconic && !msg.hwnd->is_iconic())
               {

                  //file_put_contents_dup("/home/camilo/xxx.txt", "");

                  pui->m_eappearance == ::user::appearance_none;

                  ::fork(pui->get_app(), [=]()
                  {

                     if(pui->m_eappearanceBefore == ::user::appearance_iconic)
                     {

                        pui->_001OnDeiconify(::user::appearance_normal);

                     }
                     else
                     {

                        pui->_001OnDeiconify(pui->m_eappearanceBefore);

                     }

                  });

                  bHandled = true;


               }

            }

         }
      }

   }
   else if(e.type == MapNotify || e.type == UnmapNotify)
   {

      msg.message       = WM_SHOWWINDOW;
      msg.hwnd          = oswindow_get(display, e.xmap.window);
      msg.wParam        = e.type == MapNotify;
      msg.lParam        = 0;

      send_message(msg);

   }
   else if(e.type == ConfigureNotify)
   {

      msg.hwnd = oswindow_get(display, e.xconfigure.window);

      if(msg.hwnd != NULL)
      {

         ::user::interaction_impl_base * pimpl = msg.hwnd->m_pimpl;

         if(pimpl != NULL)
         {

            ::user::interaction * pui = pimpl->m_pui;

            bool bHandled = false;

            if(pui != NULL)
            {

               g_xxx++;

               if(g_xxx >= 9)
               {
                  output_debug_string("g_xxx");
               }
               if(pui->m_eappearance == ::user::appearance_iconic)
               {

                  //file_put_contents_dup("/home/camilo/xxx.txt", "");

                  pui->m_eappearance == ::user::appearance_none;

                  ::fork(pui->get_app(), [=]()
                  {

                     if(pui->m_eappearanceBefore == ::user::appearance_iconic)
                     {

                        pui->_001OnDeiconify(::user::appearance_normal);

                     }
                     else
                     {

                        pui->_001OnDeiconify(pui->m_eappearanceBefore);

                     }

                  });

                  bHandled = true;


               }


               if(!bHandled)
               {

                  //rect64 rectWindow;

                  //rectWindow.left = e.xconfigure.x;

                  //rectWindow.top = e.xconfigure.y;

                  //rectWindow.right = rectWindow.left + e.xconfigure.width;

                  //rectWindow.bottom = rectWindow.top + e.xconfigure.height;

                  ::rect rectWindow;

                  ::GetWindowRect(msg.hwnd, rectWindow);

                  ::copy(pimpl->m_rectParentClientRequest, rectWindow);

                  pui->set_need_layout();

               }

            }

         }

      }

      if(e.xconfigure.window == g_oswindowDesktop->window())
      {

         for(int j = 0; j < ::oswindow_data::s_pdataptra->get_count(); j++)
         {

            PostMessage(::oswindow_data::s_pdataptra->element_at(j), WM_DISPLAYCHANGE, 0, 0);

         }

      }

   }
   else if(e.type == ButtonPress || e.type == ButtonRelease)
   {

      bRet                 = true;

      if(e.xbutton.type == ButtonPress)
      {

         if(e.xbutton.button == Button1)
         {

            msg.message = WM_LBUTTONDOWN;

         }
         else if(e.xbutton.button == Button2)
         {

            msg.message = WM_MBUTTONDOWN;

         }
         else if(e.xbutton.button == Button3)
         {

            msg.message = WM_RBUTTONDOWN;

         }
         else
         {

            bRet = false;

         }

      }
      else if(e.xbutton.type == ButtonRelease)
      {

         if(e.xbutton.button == Button1)
         {

            msg.message = WM_LBUTTONUP;

         }
         else if(e.xbutton.button == Button2)
         {

            msg.message = WM_MBUTTONUP;

         }
         else if(e.xbutton.button == Button3)
         {

            msg.message = WM_RBUTTONUP;

         }
         else
         {

            bRet = false;

         }

      }
      else
      {

         bRet = false;

      }


      if(bRet)
      {

         msg.hwnd          = oswindow_get(display, e.xbutton.window);
         msg.wParam        = 0;
         msg.lParam        = MAKELONG(e.xbutton.x_root, e.xbutton.y_root);

         send_message(msg);

      }

   }
   else if(e.type == KeyPress || e.type == KeyRelease)
   {

      oswindow w = oswindow_get(display, e.xexpose.window);

      bRet                 = true;

      if(e.xkey.type == KeyPress)
      {

         msg.message = WM_KEYDOWN;

      }
      else if(e.xkey.type == KeyRelease)
      {

         msg.message = WM_KEYUP;

      }
      else
      {

         bRet = false;

      }

      if(bRet)
      {

         msg.hwnd          = oswindow_get(display, e.xbutton.window);
         msg.wParam        = e.xkey.keycode;
         msg.lParam        = MAKELONG(0, e.xkey.keycode);

         send_message(msg);

      }
   }
   else if(e.type == MotionNotify)
   {


      msg.hwnd          = oswindow_get(display, e.xbutton.window);
      msg.message       = WM_MOUSEMOVE;
      msg.wParam        = 0;
      msg.lParam        = MAKELONG(e.xmotion.x_root, e.xmotion.y_root);

      synch_lock sl(pdata->m_pmutexMouse);

      if(pdata->m_messsageaMouse.get_size() > 1000)
      {

         pdata->m_messsageaMouse.remove_at(0, 499);

      }

      pdata->m_messsageaMouse.add(msg);

   }
   else if(e.type == DestroyNotify)
   {

      msg.hwnd          = oswindow_get(display, e.xdestroywindow.window);
      msg.message       = WM_DESTROY;

      send_message(msg);

   }
   else if(e.type == FocusIn)
   {

      msg.hwnd          = oswindow_get(display, e.xdestroywindow.window);
      msg.message       = WM_SETFOCUS;

      send_message(msg);

   }
   else if(e.type == FocusOut)
   {

      msg.hwnd          = oswindow_get(display, e.xdestroywindow.window);
      msg.message       = WM_KILLFOCUS;

      send_message(msg);

   }


}








void send_message(MESSAGE & msg)
{

   try
   {

      if(msg.hwnd == NULL)
      {

         ::aura::system::g_p->post_message(msg.message, msg.wParam, msg.lParam);

      }
      else
      {

         if(msg.hwnd != NULL && msg.hwnd->m_pimpl != NULL && msg.hwnd->m_pimpl->m_pui != NULL)
         {

            ::user::interaction * pui = msg.hwnd->m_pimpl->m_pui;

            pui->send_message(msg.message, msg.wParam, msg.lParam);

         }

      }

   }
   catch(...)
   {

   }

}





UINT __axis_x11mouse_thread(void * p)
{

   osdisplay_data * pdata = (osdisplay_data *) p;

   __begin_thread(::aura::system::g_p,&__axis_x11_thread,pdata,::multithreading::priority_normal,0,0,NULL);

   single_lock sl(pdata->m_pmutexMouse);

   MESSAGE msg;

   bool bOk;

   while(::aura::system::g_p != NULL && ::aura::system::g_p->thread_get_run())
   {

      bOk = false;

      {

         sl.lock();

         if(pdata->m_messsageaMouse.has_elements())
         {

            msg = pdata->m_messsageaMouse.last();

            pdata->m_messsageaMouse.remove_all();

            bOk = true;

         }

         sl.unlock();

      }

      if(bOk)
      {

         ::user::interaction * pui = msg.hwnd->m_pimpl->m_pui;

         if(pui != NULL)
         {

            pui->send_message(msg.message, msg.wParam, msg.lParam);

         }

      }
      else
      {

         Sleep(23);

      }

   }

   return 0;

}






namespace user
{



   LRESULT interaction_child::send_x11_event(void * pvoidEvent)
   {

      XEvent * pevent = (XEvent *) pvoidEvent;

      smart_pointer < ::message::base > spbase;

      spbase = Session.get_message_base(pvoidEvent, m_pui);

      try
      {
         sp(::user::interaction) pui = m_pui;
         while(pui != NULL && pui->GetParent() != NULL)
         {
            try
            {
               pui->pre_translate_message(spbase);
            }
            catch(...)
            {
               break;
            }
            if(spbase->m_bRet)
               return spbase->get_lresult();
            try
            {
               pui = pui->GetParent();
            }
            catch(...)
            {
               break;
            }
         }
      }
      catch(...)
      {
      }

      message_handler(spbase);

      return spbase->get_lresult();

   }


} // namespace user


namespace aura
{


   sp(::message::base) application::get_message_base(void * pevent,::user::interaction * pwnd)
   {

      _throw(todo(get_app()));

      return NULL;

   }


} // namespace aura





void os_init_windowing()
{


      set_TranslateMessage(&axis_TranslateMessage);

      set_DispatchMessage(&axis_DispatchMessage);

      oswindow_data::s_pdataptra = new oswindow_dataptra;

      oswindow_data::s_pmutex = new mutex;

      osdisplay_data::s_pdataptra = new osdisplay_dataptra;

      osdisplay_data::s_pmutex = new mutex;

      XSetErrorHandler(_c_XErrorHandler);

}


void os_term_windowing()
{

      delete osdisplay_data::s_pmutex;

      osdisplay_data::s_pmutex = NULL;

      delete osdisplay_data::s_pdataptra;

      osdisplay_data::s_pdataptra = NULL;

      delete oswindow_data::s_pmutex;

      oswindow_data::s_pmutex = NULL;

      delete oswindow_data::s_pdataptra;

      oswindow_data::s_pdataptra = NULL;

}





int xlib_error_handler(Display * d, XErrorEvent * e)
{

   if(e->request_code == 12) //
   {

      if(e->error_code == BadValue)
      {
      }

   }
   char sz[1024];
   XGetErrorText(d, e->error_code, sz, sizeof(sz));
   fputs(sz, stderr);

   abort();

}

