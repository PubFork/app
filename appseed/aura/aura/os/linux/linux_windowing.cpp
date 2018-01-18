#include "framework.h"
#include "linux_user_impl.h"
#include <X11/Xatom.h>
#include <sys/stat.h>
#include <X11/extensions/xf86vmode.h>




//int get_best_ordered_monitor(::user::interaction * pui, int & l, int & t, int & cx, int & cy);
//int get_best_monitor(::user::interaction * pui, int & l, int & t, int & cx, int & cy);

extern SnLauncheeContext* g_psncontext;
Display * x11_get_display();
void wm_toolwindow(oswindow w,bool bToolWindow);
void wm_state_hidden_raw(oswindow w, bool bSet);
CLASS_DECL_AURA int_bool mq_remove_window_from_all_queues(oswindow oswindow);


#ifdef LINUX
int32_t _c_XErrorHandler(Display * display, XErrorEvent * perrorevent);
#endif


int g_iIgnoreXDisplayError = 0;


void x_display_error_trap_push(SnDisplay * display, Display * xdisplay)
{

  g_iIgnoreXDisplayError++;

}

void x_display_error_trap_pop(SnDisplay * display, Display * xdisplay)
{

  g_iIgnoreXDisplayError--;

  if(g_iIgnoreXDisplayError == 0)
  {

    XSync(xdisplay, false);

  }

}

int32_t _c_XErrorHandler(Display * display, XErrorEvent * perrorevent)
{

   return 0;

}



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


Atom get_window_long_atom(int32_t nIndex);

// Change _NET_WM_STATE if Window is Mapped
void mapped_net_state (bool add, Display * d, Window w, int iScreen, Atom state1, Atom state2)
{

  XClientMessageEvent xclient;

#define _NET_WM_STATE_REMOVE        0    /* remove/unset property */
#define _NET_WM_STATE_ADD           1    /* add/set property */
#define _NET_WM_STATE_TOGGLE        2    /* toggle property  */

  ZERO(xclient);
  xclient.type = ClientMessage;
  xclient.window = w;
  xclient.message_type = XInternAtom(d, "_NET_WM_STATE", False);
  xclient.format = 32;
  xclient.data.l[0] = add ? _NET_WM_STATE_ADD : _NET_WM_STATE_REMOVE;
  xclient.data.l[1] = state1;
  xclient.data.l[2] = state2;
  xclient.data.l[3] = 1; /* source indication */
  xclient.data.l[4] = 0;

  XSendEvent (d, RootWindow(d, iScreen), False, SubstructureRedirectMask | SubstructureNotifyMask, (XEvent *)&xclient);

}


void unmapped_net_state(Display * d, Window w, ...)
{

	XEvent xevent;

	unsigned int i;

	va_list argp;

	va_start(argp, w);

   ZERO(xevent);

   array < Atom > atoms;

	while(true)
	{

      Atom atom = va_arg(argp, int);

      if(atom == 0)
      {

         break;

      }

		atoms.add(atom);

	}

	if(atoms.has_elements())
   {

      XChangeProperty(d, w, XInternAtom(d, "_NET_WM_STATE", False),
                      XA_ATOM, 32, PropModeReplace,
                      (guchar*) atoms.get_data(), atoms.get_size());
   }
   else
   {

      XDeleteProperty(d, w, XInternAtom(d, "_NET_WM_STATE", False));

   }

	va_end(argp);

}


static oswindow g_oswindowCapture;


oswindow GetCapture()
{

   return g_oswindowCapture;

}


oswindow SetCapture(oswindow window)
{

   oswindow windowOld(g_oswindowCapture);

   if(window->display() == NULL)
   {

      return NULL;

   }

   if(window->window() == None)
   {

      return NULL;

   }

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

   if(g_oswindowCapture == NULL)
   {

      return FALSE;

   }

   xdisplay d(g_oswindowCapture->display());

   WINBOOL bRet = XUngrabPointer(g_oswindowCapture->display(), CurrentTime) != FALSE;

   if(bRet)
   {

      g_oswindowCapture = NULL;

   }

   return bRet;

}


oswindow SetFocus(oswindow window)
{

   if(window == NULL)
   {

      return NULL;

   }

   xdisplay display(window->display());

   if(!IsWindow(window))
   {

      return NULL;

   }

   oswindow windowOld = ::GetFocus();

   if(!IsWindowVisible(window))
   {

      return NULL;

   }

   if(!XSetInputFocus(window->display(), window->window(), RevertToNone, CurrentTime))
   {

      return NULL;

   }

   return windowOld;

}


oswindow GetFocus()
{

   xdisplay pdisplay;

   pdisplay.open(NULL);

   if(pdisplay == NULL)
   {

      return NULL;

   }

   Window window = None;

   int revert_to = 0;

   bool bOk = XGetInputFocus(pdisplay, &window, &revert_to) != 0;

   pdisplay.close();

   if(!bOk)
   {

      return NULL;

   }

   if(window == None || window == PointerRoot)
   {

      return NULL;

   }

   return oswindow_defer_get(window);

}


oswindow GetActiveWindow()
{

   return GetFocus();

}


oswindow SetActiveWindow(oswindow window)
{

   xdisplay d(window->display());

   XEvent xev;

   ZERO(xev);

   Window wRoot = RootWindow(window->display(), window->m_iScreen);

   Atom atomActiveWindow = XInternAtom (window->display(), "_NET_ACTIVE_WINDOW", False);

   xev.xclient.type = ClientMessage;
   xev.xclient.send_event = True;
   xev.xclient.display = window->display();
   xev.xclient.window = window->window();
   xev.xclient.message_type = atomActiveWindow;
   xev.xclient.format = 32;
   xev.xclient.data.l[0] = 1;
   xev.xclient.data.l[1] = 0;
   xev.xclient.data.l[2] = 0;
   xev.xclient.data.l[3] = 0;
   xev.xclient.data.l[4] = 0;

   XSendEvent (d, wRoot, False, SubstructureRedirectMask | SubstructureNotifyMask, &xev);

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


























































/* Copyright (c) 2012 the authors listed at the following URL, and/or
the authors of referenced articles or incorporated external code:
http://en.literateprograms.org/Hello_World_(C,_Cairo)?action=history&offset=20070528220552

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to uxse, cxopy, mxodify, mxerge, pxublish,
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

WINBOOL IsWindowVisibleRaw(Display * display, Window window);

void wm_iconify_window(oswindow w)
{

   xdisplay d(w->display());

   Display * display = w->display();

   Window window = w->window();

   int scr = DefaultScreen(display);

   if(IsWindowVisibleRaw(display, window))
   {

      XIconifyWindow(display, window, scr);

   }
   else
   {

      if(w->m_pimpl->m_pui->get_appearance() !=::user::appearance_iconic)
      {

         w->m_pimpl->m_pui->set_appearance(::user::appearance_iconic);

      }

      unmapped_net_state(display, window, XInternAtom(display, "_NET_WM_STATE_HIDDEN", False));

   }

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

   return 0;

}


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

               if(pui->m_eappearance == ::user::appearance_iconic && !msg.hwnd->is_iconic())
               {

                  //file_put_contents_dup("/home/camilo/xxx.txt", "");

                  // 1111111111111111111111111111111111111111111

                  pui->m_eappearance = ::user::appearance_none;

                  pui->fork([=]()
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

               if(pui->m_eappearance != ::user::appearance_iconic
                  && pui->m_eappearance != ::user::appearance_none
                  && msg.hwnd->is_iconic())
               {

                  pui->set_appearance(::user::appearance_iconic);

               }

               if(pui->m_eappearanceRequest == ::user::appearance_full_screen
                  && pui->m_eappearance != ::user::appearance_full_screen
                  && !msg.hwnd->is_iconic())
               {

                  pui->set_appearance(::user::appearance_full_screen);

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

      if(e.type == MapNotify)
      {
         if(msg.hwnd != NULL && msg.hwnd->m_pimpl != NULL)
         {

            ::user::interaction * pui = msg.hwnd->m_pimpl->m_pui;

            if(pui->m_eappearance == ::user::appearance_iconic && !msg.hwnd->is_iconic())
            {

               //file_put_contents_dup("/home/camilo/xxx.txt", "");

               // 1111111111111111111111111111111111111111111

               pui->m_eappearance = ::user::appearance_none;

               pui->fork([=]()
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

//               bHandled = true;

            }

         }

      }

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

               if(pui->m_eappearance == ::user::appearance_iconic && !msg.hwnd->is_iconic())
               {

                  //file_put_contents_dup("/home/camilo/xxx.txt", "");

                  // 33333333333333333333333333333333333333333333333333333333333333

                  pui->m_eappearance = ::user::appearance_none;

                  pui->fork([=]()
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

                  rect64 rectWindow;

                  rectWindow.left = e.xconfigure.x;

                  rectWindow.top = e.xconfigure.y;

                  rectWindow.right = rectWindow.left + e.xconfigure.width;

                  rectWindow.bottom = rectWindow.top + e.xconfigure.height;

                  auto rect = pimpl->m_rectParentClient;

                  ::copy(pimpl->m_rectParentClientRequest, rectWindow);

                  if(rectWindow.top_left() != rect.top_left())
                  {

                     pimpl->m_pui->post_message(WM_MOVE);

                  }

                  if(rectWindow.size() != rect.size())
                  {

                     pimpl->m_pui->post_message(WM_SIZE);

                  }

               }

            }

         }

      }

      if(g_oswindowDesktop != NULL && e.xconfigure.window == g_oswindowDesktop->window())
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

      WPARAM wparam(0);

      if(e.xmotion.state & Button1Mask)
      {

         wparam |= MK_LBUTTON;

      }

      msg.hwnd          = oswindow_get(display, e.xbutton.window);
      msg.message       = WM_MOUSEMOVE;
      msg.wParam        = wparam;
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
            {

               return spbase->get_lresult();

            }

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






WINBOOL SetWindowPos(oswindow hwnd, oswindow hwndInsertAfter, int32_t x, int32_t y, int32_t cx, int32_t cy, UINT nFlags)
{

   return hwnd->set_window_pos(hwndInsertAfter, x, y, cx, cy, nFlags);

}




WINBOOL GetWindowRect(oswindow hwnd, LPRECT lprect)
{

   //single_lock sl(&user_mutex(), true);

   //synch_lock sl(::oswindow_data::s_pmutex);

   xdisplay d(hwnd->display());


   //oswindow window = oswindow_get(hwnd->display(), e.xbutton.window);

   XWindowAttributes attrs;

   /* Fill attribute structure with information about root window */

   if(!XGetWindowAttributes(hwnd->display(), hwnd->window(), &attrs))
   {

      return FALSE;

   }

//   int x;
//   int y;
//   Window child;
//
//   if(!XTranslateCoordinates(hwnd->display(), hwnd->window(), DefaultRootWindow(hwnd->display()), 0, 0, &x, &y, &child))
//   {
//
//      return FALSE;
//
//   }


   lprect->left      = attrs.x;
   lprect->top       = attrs.y;
   lprect->right     = attrs.x    + attrs.width;
   lprect->bottom    = attrs.y    + attrs.height;

   return TRUE;

}




WINBOOL GetClientRect(oswindow hwnd, LPRECT lprect)
{

   xdisplay display(hwnd->display());

   //single_lock sl(&user_mutex(), true);

   XWindowAttributes attrs;

   /* Fill attribute structure with information about root window */

   if(XGetWindowAttributes(hwnd->display(), hwnd->window(), &attrs) == 0)
   {

      return FALSE;

   }

   lprect->left      = 0;
   lprect->top       = 0;
   lprect->right     = lprect->left    + attrs.width;
   lprect->bottom    = lprect->top     + attrs.height;

   return TRUE;

}



WINBOOL GetCursorPos(LPPOINT lpptCursor)
{

   //single_lock sl(user_mutex(), true);


   Window root_return;
   Window child_return;
   int32_t win_x_return;
   int32_t win_y_return;
   uint32_t mask_return;

   xdisplay display;

   display.open(NULL);

   if(display == NULL)
        return FALSE;

   XQueryPointer(display, display.default_root_window(), &root_return, &child_return, &lpptCursor->x, &lpptCursor->y, &win_x_return, &win_y_return, & mask_return);

   return TRUE;

}




::user::interaction * get_system_window_interaction(::os_system_window * psystemwindow)
{

   return NULL;

}



void wm_full_screen(oswindow w, LPCRECT lpcrect)
{

   w->full_screen(lpcrect);

}



CLASS_DECL_AURA void defer_dock_application(bool bDock)
{

   UNREFERENCED_PARAMETER(bDock);

}







bool os_init_windowing()
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

   if(e->request_code == 12)
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
