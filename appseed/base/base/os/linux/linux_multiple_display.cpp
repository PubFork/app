#include "framework.h"
#include "aura/aura/os/linux/linux_user_impl.h"
#define pointer x11_pointer
#include <X11/extensions/Xrandr.h>
#include <X11/extensions/Xinerama.h>
#undef pointer

int os_get_monitor_count()
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


        bool os_get_monitor_rect(index iMonitor, LPRECT lprect)
        {


            xdisplay  d;

                  if (!d.open(NULL))
                     return false;

                  //int iCount = ScreenCount(d.m_pdata->m_pdisplay);
                  //Display *d= ScreenCount(d.m_pdata->m_pdisplay);

                  bool success = false;

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
                           success = true;
                        }

                        XFree(p);

                     }

                  }

                  if (success)
                  {

                     return true;

                  }

                  int iCount;

                  XRRScreenSize * psize = XRRSizes(d.m_pdata->m_pdisplay, 0, &iCount);

                  lprect->left = 0;
                  lprect->right = WidthOfScreen(DefaultScreenOfDisplay(d.m_pdata->m_pdisplay));
                  lprect->top = 0;
                  lprect->bottom = HeightOfScreen(DefaultScreenOfDisplay(d.m_pdata->m_pdisplay));

                  return true;

        }




        int os_get_screen_size(int& width, int& height)
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

