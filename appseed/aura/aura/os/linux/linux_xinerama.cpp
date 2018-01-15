#include "framework.h"
#include "aura/aura/os/linux/linux_user_impl.h"
#define pointer x11_pointer
#include <X11/extensions/Xrandr.h>
#include <X11/extensions/Xinerama.h>
#undef pointer


CLASS_DECL_AURA int xinerama_get_monitor_count();
CLASS_DECL_AURA int xinerama_get_monitor_rect(index i, LPRECT lprect);
CLASS_DECL_AURA int xinerama_get_screen_size(int& width, int& height);




int xinerama_get_monitor_count()
{

   int heads = 0;

   xdisplay  d;

   if (!d.open(NULL))
   {

      return 1;

   }

   int dummy1, dummy2;

   if (XineramaQueryExtension(d, &dummy1, &dummy2))
   {

      if (XineramaIsActive(d))
      {

         XineramaScreenInfo *p = XineramaQueryScreens(d, &heads);

         XFree(p);

      }

   }

   return MAX(1, heads);

}


int xinerama_get_monitor_rect(index iMonitor, LPRECT lprect)
{

   xdisplay  d;

   if (!d.open(NULL))
      return -1;

   //int iCount = ScreenCount(d.m_pdata->m_pdisplay);
   //Display *d= ScreenCount(d.m_pdata->m_pdisplay);

   int screen_number = -1;

   int dummy1, dummy2;

   if (XineramaQueryExtension(d, &dummy1, &dummy2))
   {

      if (XineramaIsActive(d))
      {

         int heads = 0;

         XineramaScreenInfo *p = XineramaQueryScreens(d, &heads);

         if (iMonitor >= 0 && iMonitor < heads)
         {

            lprect->left = p[iMonitor].x_org;
            lprect->top = p[iMonitor].y_org;
            lprect->right = lprect->left + p[iMonitor].width;
            lprect->bottom = lprect->top + p[iMonitor].height;
            //      lprect->right = WidthOfScreen(DefaultScreenOfDisplay(d.m_pdata->m_pdisplay));
            //      lprect->top = 0;
            //      lprect->bottom= HeightOfScreen(DefaultScreenOfDisplay(d.m_pdata->m_pdisplay));

            //             for (int x=0; x<heads; ++x)
            //                cout << "Head " << x+1 << " of " << heads << ": " <<
            //                   p[x].width << "x" << p[x].height << " at " <<
            //                   p[x].x_org << "," << p[x].y_org << endl;
            screen_number = p[iMonitor].screen_number;
         }

         XFree(p);

      }

   }

   if (screen_number >= 0)
   {

      return screen_number;

   }

   int iCount;

   XRRScreenSize * psize = XRRSizes(d.m_pdata->m_pdisplay, 0, &iCount);

   lprect->left = 0;
   lprect->right = WidthOfScreen(DefaultScreenOfDisplay(d.m_pdata->m_pdisplay));
   lprect->top = 0;
   lprect->bottom = HeightOfScreen(DefaultScreenOfDisplay(d.m_pdata->m_pdisplay));

   return 0;

}


int xinerama_get_screen_size(int& width, int& height)
{

   int num_sizes;
   Rotation original_rotation;

   Display *dpy = XOpenDisplay(NULL);
   Window root = RootWindow(dpy, 0);
   XRRScreenSize *xrrs = XRRSizes(dpy, 0, &num_sizes);
   //
   //     GET CURRENT RESOLUTION AND FREQUENCY
   //
   XRRScreenConfiguration *conf = XRRGetScreenInfo(dpy, root);
   short original_rate = XRRConfigCurrentRate(conf);
   SizeID original_size_id = XRRConfigCurrentConfiguration(conf, &original_rotation);

   width = xrrs[original_size_id].width;
   height = xrrs[original_size_id].height;

   XCloseDisplay(dpy);
   return 0;    //Return a value that can be used for error checking.

}




// it doesn't work for final purpose, but it has example on how to "sort" rectangles with stability
::array < rect > get_ordered_monitor_recta(::aura::application * papp)
{

   index iMonitor = 0;

   ::array < ::rect > rectaMonitor;

   ::aura::system & system = Sys(papp);

   ::count cMonitor = system.get_monitor_count();

   ::rect rectMonitor;

   rectaMonitor.set_size(cMonitor);

   for(; iMonitor < cMonitor; iMonitor++)
   {

      system.get_monitor_rect(iMonitor, &rectMonitor);

      rectaMonitor[iMonitor] = rectMonitor;

      output_debug_string(::str::from(rectMonitor.left));

      output_debug_string(::str::from(rectMonitor.top));

      output_debug_string(::str::from(rectMonitor.right));

      output_debug_string(::str::from(rectMonitor.bottom));

   }

   // sort horizontally

   ::sort::pred_stable_sort(rectaMonitor, [](auto & r1, auto & r2){ return r1.left <= r2.left; });

   // sort vertically in stable way

   ::sort::pred_stable_sort(rectaMonitor, [](auto & r1, auto & r2){ return r1.top <= r2.top; });

   for(auto & rectItem: rectaMonitor)
   {

      output_debug_string(::str::from(rectItem.left));

      output_debug_string(::str::from(rectItem.top));

      output_debug_string(::str::from(rectItem.right));

      output_debug_string(::str::from(rectItem.bottom));

   }

   return rectaMonitor;

}

// it doesn't work for final purpose,
// but it calls function that "sorts" rectangles with stability
int get_best_ordered_monitor(::user::interaction * pui, LPRECT lprectRet)
{

   auto rectaOrdered = get_ordered_monitor_recta(pui->get_app());

   index iJustForComparison = pui->best_monitor(lprectRet, null_rect(), FALSE, 0, 0);

   index iOrdered = rectaOrdered.pred_find_first([&](auto & rectMonitorSorted){ return rectMonitorSorted == *lprectRet; });

   output_debug_string(::str::from(iJustForComparison));

   output_debug_string(::str::from(iOrdered));

   return iOrdered;

}


int best_xinerama_monitor(::user::interaction * pui, LPCRECT lpcrect, LPRECT lprectRet)
{

   *lprectRet = null_rect();

   if(lpcrect == NULL)
   {

      lpcrect = lprectRet;

   }

   index iOrdered = pui->best_monitor(lprectRet, *lpcrect, false, 0, 0);

   ::count cMonitor = xinerama_get_monitor_count();

   ::rect rectMonitor;

   for(index i = 0; i < cMonitor; i++)
   {

      int iScreen = xinerama_get_monitor_rect(i, &rectMonitor);

      if(rectMonitor == *lpcrect)
      {

         iOrdered = iScreen;

         break;

      }

   }

   output_debug_string(::str::from(iOrdered));

   return iOrdered;

}


int best_xinerama_monitor(::user::interaction * pui, LPRECT lprectRet)
{

   return best_xinerama_monitor(pui, NULL, lprectRet);

}


int get_best_monitor(::user::interaction * pui, LPCRECT lpcrect, LPRECT lprectRet)
{

   rect rNull = null_rect();

   if(lpcrect == NULL)
   {

      lpcrect = &rNull;

   }

   index i = pui->best_monitor(lprectRet, *lpcrect, FALSE, 0, 0);

   return i;

}


int get_best_monitor(::user::interaction * pui, LPRECT lprectRet)
{

   return get_best_monitor(pui, NULL, lprectRet);

}
