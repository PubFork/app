#include "framework.h"


static oswindow g_oswindowSplash = NULL;


void set_splash(oswindow oswindow)
{

   g_oswindowSplash = oswindow;

}


oswindow get_splash()
{

   return g_oswindowSplash;

}



