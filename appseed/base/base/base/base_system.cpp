#include "framework.h" // from "axis/user/user.h"
//#include "base/user/user/user_windowing.h"
#include "base/user/user.h"
#include "base/node/node.h"


#ifndef WINDOWS
#include <ft2build.h>
#include FT_FREETYPE_H
#endif

CLASS_DECL_BASE void black_body(float * r, float * g, float * b, DWORD dwTemp);

CLASS_DECL_BASE int os_get_monitor_count();
CLASS_DECL_BASE bool os_get_monitor_rect(index i, LPRECT lprect);
CLASS_DECL_BASE int os_get_screen_size(int& width, int& height);

#ifdef WINDOWSEX



//#include "base/os/windows/windows_system_interaction_impl.h"


#include <HighLevelMonitorConfigurationAPI.h>

DWORD mc_color_kelvin(MC_COLOR_TEMPERATURE e)
{
   switch (e)
   {
   case MC_COLOR_TEMPERATURE_4000K:
      return 4000;
   case MC_COLOR_TEMPERATURE_5000K:
      return 5000;
   case MC_COLOR_TEMPERATURE_6500K:
      return 6500;
   case MC_COLOR_TEMPERATURE_7500K:
      return 7500;
   case MC_COLOR_TEMPERATURE_8200K:
      return 8200;
   case MC_COLOR_TEMPERATURE_9300K:
      return 9300;
   case MC_COLOR_TEMPERATURE_10000K:
      return 10000;
   case MC_COLOR_TEMPERATURE_11500K:
      return 11500;
   default:
      return 0;
   }
}

MC_COLOR_TEMPERATURE kelvin_mc_color(DWORD kelvin)
{
   if (kelvin < 4500)
   {
      return MC_COLOR_TEMPERATURE_4000K;
   }
   else if (kelvin < 5750)
   {
      return MC_COLOR_TEMPERATURE_5000K;
   }
   else if (kelvin < 7000)
   {
      return MC_COLOR_TEMPERATURE_6500K;
   }
   else if (kelvin < 7850)
   {
      return MC_COLOR_TEMPERATURE_7500K;
   }
   else if (kelvin < 8750)
   {
      return MC_COLOR_TEMPERATURE_8200K;
   }
   else if (kelvin < 9650)
   {
      return MC_COLOR_TEMPERATURE_9300K;
   }
   else if(kelvin < 10750)
   {
      return MC_COLOR_TEMPERATURE_10000K;
   }
   else
   {
      return MC_COLOR_TEMPERATURE_11500K;
   }
}

#elif defined(LINUX)


#endif


namespace base
{



   system::system(::aura::application * papp) :
      ::aura::system(this, NULL),
      ::axis::system(this)
   {

      factory().creatable_small < ::visual::icon >();

      g_pszCooperativeLevel = "base";

#ifdef WINDOWSEX

      m_psystemwindow = NULL;

#endif


#if defined(METROWIN) || defined(APPLE_IOS) || defined(VSNORD)

      m_possystemwindow = new os_system_window();

#endif



      set_app(this);

      m_pbasesystem = this;

      if (papp == NULL)
      {

         oprop("parent_system") = (sp(object)) NULL;

      }
      else
      {

         oprop("parent_system") = papp->m_paxissystem;

      }


      __node_base_factory_exchange(this);

      m_bSystemSynchronizedCursor = true;

      m_bSystemSynchronizedScreen = true;

   }



   system::~system()
   {

   }



   int32_t system::exit_application()
   {

      try
      {

         for(auto & pair : System.m_appmap)
         {

            try
            {

               if(pair.m_element2->m_pbasesystem == this)
               {

                  pair.m_element2->m_pbasesystem = NULL;

               }

            }
            catch(...)
            {

            }

         }

      }
      catch(...)
      {

      }

#ifdef WINDOWSEX

      try
      {

         ::aura::del(m_psystemwindow);

      }
      catch (...)
      {

         m_iReturnCode = -2;

      }


#endif
      axis::system::exit_application();



      return m_iReturnCode;

   }


   ::aura::session * system::on_create_session()
   {

      return new ::base::session(this);

   }










   void system::set_active_guie(::user::interaction * pui)
   {

#if defined(METROWIN)

      if (pui == NULL)
      {

         ::WinSetActiveWindow(NULL);

      }
      else
      {

         ::WinSetActiveWindow(pui->get_wnd()->get_safe_handle());

      }
#else
      if (pui == NULL)
      {

         ::SetActiveWindow(NULL);

      }
      else
      {

         ::SetActiveWindow(pui->get_wnd()->get_safe_handle());

      }
#endif
      return;

      //#else
      //
      //      synch_lock sl(&m_uiptraFrame);
      //
      //      if(m_uiptraFrame.find(pui) > 0)
      //      {
      //
      //         m_uiptraFrame.remove(pui);
      //
      //         m_uiptraFrame.insert_at(0,pui);
      //
      //      }
      //
      //      return pui;
      //
      //#endif

   }


   void system::set_focus_guie(::user::interaction * pui)
   {

      if (pui == NULL)
      {

#ifdef METROWIN

         ::WinSetFocus(NULL);
#else
         ::SetFocus(NULL);
#endif

         return;

      }


#ifdef METROWIN

      ::WinSetFocus(pui->get_safe_handle());

#else

      ::SetFocus(pui->get_safe_handle());

#endif

      if (pui->get_wnd() != NULL)
      {

         pui->SetFocus();

      }

      return;

   }

   ::count system::get_monitor_count()
   {

#ifdef LINUX

      return os_get_monitor_count();

#else

      return ::axis::system::get_monitor_count();

#endif


   }


   DWORD system::get_monitor_color_temperature(index iMonitor)
   {

#ifdef METROWIN

      return 0;

#elif defined(LINUX)

      return 0;

#elif defined(MACOS)

      return 0;

#elif defined(APPLE_IOS)

      return 0;

#elif defined(ANDROID)

      return 0;

#else

      if (iMonitor < 0)
      {

         return 0;

      }

      if (iMonitor >= m_hmonitora.get_count())
      {

         return 0;

      }

      MC_COLOR_TEMPERATURE e;

      if (!GetMonitorColorTemperature(m_hmonitora[iMonitor], &e))
      {

         return 0;

      }

      return mc_color_kelvin(e);

#endif

   }

   mutex g_monitor_adjust(NULL);
   bool system::adjust_monitor(index iMonitor, DWORD dwTemperature, double dBrightness, double dGamma)
   {

#ifdef METROWIN

      return true;

#elif defined(LINUX)

      return true;

#elif defined(MACOS)

      return true;

#elif defined(APPLE_IOS)

      return true;

#elif defined(ANDROID)

      return true;

#else

      synch_lock sl(&g_monitor_adjust);

      if (iMonitor < 0)
      {

         return 0;

      }

      if (iMonitor >= m_hmonitora.get_count())
      {

         return 0;

      }

      if (dBrightness <= 0.0)
      {

         dBrightness = 0.1;

      }

      if (dBrightness >= 1.0)
      {

         dBrightness = 1.0;

      }

      if (dGamma <= 0.1)
      {

         dGamma = 0.1;

      }

      if (dGamma >= 10.0)
      {

         dGamma = 10.0;

      }


      DWORD dwMinDriveR;
      DWORD dwCurDriveR;
      DWORD dwMaxDriveR;
      DWORD dwMinDriveG;
      DWORD dwCurDriveG;
      DWORD dwMaxDriveG;
      DWORD dwMinDriveB;
      DWORD dwCurDriveB;
      DWORD dwMaxDriveB;
      DWORD dwMinGainR;
      DWORD dwCurGainR;
      DWORD dwMaxGainR;
      DWORD dwMinGainG;
      DWORD dwCurGainG;
      DWORD dwMaxGainG;
      DWORD dwMinGainB;
      DWORD dwCurGainB;
      DWORD dwMaxGainB;

      float r;
      float g;
      float b;

      //dwTemperature = 4000;

      black_body(&r, &g, &b, dwTemperature);

      MC_COLOR_TEMPERATURE e = kelvin_mc_color(dwTemperature);

      HMONITOR hMonitor = NULL;
      DWORD cPhysicalMonitors;
      LPPHYSICAL_MONITOR pPhysicalMonitors = NULL;

      // Get the number of physical monitors.
      BOOL bSuccess = GetNumberOfPhysicalMonitorsFromHMONITOR(
                      m_hmonitora[iMonitor],
                      &cPhysicalMonitors
                      );

      if (!bSuccess || cPhysicalMonitors <= 0)
      {

         return 0;

      }

      PHYSICAL_MONITOR monitor;

      bSuccess = GetPhysicalMonitorsFromHMONITOR(m_hmonitora[iMonitor], 1, &monitor);

      Sleep(500);

      //MC_COLOR_TEMPERATURE e = kelvin_mc_color(dwTemperature);



      //if (!SetMonitorColorTemperature(monitor.hPhysicalMonitor, e))
      //{

      //   return false;

      //}
      //return true;


      if (!GetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_RED_GAIN, &dwMinGainR, &dwCurGainR, &dwMaxGainR))
      {

         DWORD dwLastError = GetLastError();

         TRACELASTERROR();

         goto error;

      }

      if (!GetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_GREEN_GAIN, &dwMinGainG, &dwCurGainG, &dwMaxGainG))
      {

         return false;

      }

      if (!GetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_BLUE_GAIN, &dwMinGainB, &dwCurGainB, &dwMaxGainB))
      {

         return false;

      }

      if (!GetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_RED_DRIVE, &dwMinDriveR, &dwCurDriveR, &dwMaxDriveR))
      {

         return false;

      }

      if (!GetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_GREEN_DRIVE, &dwMinDriveG, &dwCurDriveG, &dwMaxDriveG))
      {

         return false;

      }

      if (!GetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_BLUE_DRIVE, &dwMinDriveB, &dwCurDriveB, &dwMaxDriveB))
      {

         return false;

      }


//    SetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_RED_GAIN, dwMinGainR);
//    SetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_GREEN_GAIN, dwMinGainG);
//    SetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_BLUE_GAIN, dwMinGainB);
      //SetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_RED_DRIVE, (DWORD)(dwMinDriveR + (dwMaxDriveR - dwMinDriveR) * r));
      //SetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_GREEN_DRIVE, (DWORD)(dwMinDriveG + (dwMaxDriveG - dwMinDriveG) * g));
      //SetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_BLUE_DRIVE, (DWORD)(dwMinDriveB + (dwMaxDriveB - dwMinDriveB) * b));
      //SetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_RED_GAIN, dwMaxGainR);
      //SetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_GREEN_GAIN, dwMaxGainG);
      //SetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_BLUE_GAIN, dwMaxGainB);
      bool bDifferent = false;
      if (dwMaxDriveR != dwCurDriveR)
      {
         SetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_RED_DRIVE, dwMaxDriveR);
         bDifferent = true;
      }
      if (dwMaxDriveG != dwCurDriveG)
      {
         SetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_GREEN_DRIVE, dwMaxDriveG);
         bDifferent = true;
      }
      if (dwMaxDriveB != dwCurDriveB)
      {
         SetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_BLUE_DRIVE, dwMaxDriveB);
         bDifferent = true;
      }


      /* Helper macro used in the fill functions */
//#define F(Y, C)  pow(dBrightness * C, 1.0 / dGamma)
#define F(C)  pow(dBrightness * C, 1.0 / dGamma)

      DWORD dwR = (DWORD)(dwMinGainR + (dwMaxGainR - dwMinGainR) * F(r));
      DWORD dwG = (DWORD)(dwMinGainG + (dwMaxGainG - dwMinGainG) * F(g));
      DWORD dwB = (DWORD)(dwMinGainB + (dwMaxGainB - dwMinGainB) * F(b));

      if (dwR != dwCurGainR)
      {
         SetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_RED_GAIN, dwR);
         bDifferent = true;
      }
      if (dwG != dwCurGainG)
      {
         SetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_GREEN_GAIN, dwG);
         bDifferent = true;
      }
      if (dwB != dwCurGainB)
      {
         SetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_BLUE_GAIN, dwB);
         bDifferent = true;
      }

#undef F

      if (!bDifferent)
      {

         goto finalize;

      }

      int iRepeat = 0;
repeat:

      bDifferent = false;

      if (GetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_RED_DRIVE, &dwMinDriveR, &dwCurDriveR, &dwMaxDriveR))
      {

         if (dwCurDriveR != dwMaxDriveR)
         {
            Sleep(500);
            SetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_RED_DRIVE, dwMaxDriveR);
            Sleep(500);
            bDifferent = true;
         }

      }

      if (GetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_GREEN_DRIVE, &dwMinDriveG, &dwCurDriveG, &dwMaxDriveG))
      {

         if (dwCurDriveG != dwMaxDriveG)
         {
            Sleep(500);
            SetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_GREEN_DRIVE, dwMaxDriveG);
            Sleep(500);
            bDifferent = true;
         }

      }

      if (GetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_BLUE_DRIVE, &dwMinDriveB, &dwCurDriveB, &dwMaxDriveB))
      {

         if (dwCurDriveB != dwMaxDriveB)
         {
            Sleep(500);
            SetMonitorRedGreenOrBlueDrive(monitor.hPhysicalMonitor, MC_BLUE_DRIVE, dwMaxDriveB);
            Sleep(500);
            bDifferent = true;
         }

      }

      if (GetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_RED_GAIN, &dwMinGainR, &dwCurGainR, &dwMaxGainR))
      {

         if (dwCurGainR != dwR)
         {
            Sleep(500);
            SetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_RED_GAIN, dwR);
            Sleep(500);
            bDifferent = true;
         }


      }

      if (GetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_GREEN_GAIN, &dwMinGainG, &dwCurGainG, &dwMaxGainG))
      {

         if (dwCurGainG != dwG)
         {
            Sleep(500);
            SetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_GREEN_GAIN, dwG);
            Sleep(500);
            bDifferent = true;
         }

      }

      if (GetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_BLUE_GAIN, &dwMinGainB, &dwCurGainB, &dwMaxGainB))
      {

         if (dwCurGainB != dwB)
         {
            Sleep(500);
            SetMonitorRedGreenOrBlueGain(monitor.hPhysicalMonitor, MC_BLUE_GAIN, dwB);
            Sleep(500);
            bDifferent = true;
         }

      }

      if (bDifferent)
      {

         iRepeat++;

         if (iRepeat < 3)
         {

            goto repeat;

         }

      }
      Sleep(500);
finalize:
      ;
      DestroyPhysicalMonitors(1, &monitor);
      return true;
error:
      ;
      Sleep(500);
      // Close the monitor handles.
      DestroyPhysicalMonitors(1, &monitor);
      return false;

#endif

   }


   bool system::get_monitor_rect(index iMonitor, LPRECT lprect)
   {

#ifdef METROWIN

      get_window_rect(m_possystemwindow->m_pwindow, lprect);

      return true;

#elif defined(LINUX)

      return os_get_monitor_rect(iMonitor, lprect);


#else

      return ::axis::system::get_monitor_rect(iMonitor, lprect);

#endif

   }


   bool system::get_wkspace_rect(index iWkspace, LPRECT lprect)
   {

      //#ifdef LINUX
      //
      //      xdisplay  d;
      //
      //      if(!d.open(NULL))
      //         return false;
      //
      //      lprect->left = 0;
      //      lprect->right = WidthOfScreen(DefaultScreenOfDisplay(d.m_pdata->m_pdisplay));
      //      lprect->top = 0;
      //      lprect->bottom= HeightOfScreen(DefaultScreenOfDisplay(d.m_pdata->m_pdisplay));
      //
      //      return true;
      //
      //#else

      return ::axis::system::get_wkspace_rect(iWkspace, lprect);

      //#endif

   }



   void system::on_setting_changed(::aura::e_setting esetting)
   {

      sp(::user::interaction) pui;

      ::base::session * psession = m_pbasesession;

      if(psession == NULL)
      {

         return;

      }

      while(psession->get_frame(pui))
      {

         pui->on_setting_changed(esetting);

      }

   }




   bool system::process_initialize()
   {

#ifndef WINDOWS

      int32_t error = FT_Init_FreeType((FT_Library *)&m_ftlibrary);
      if (error)
      {
         TRACE("an error occurred during Free Type library initialization");
         return false;
      }

#endif

      //if (m_peengine != NULL)
      //{

      //   m_peengine = new ::exception::engine(this);

      //}


      if (!::base::application::process_initialize())
         return false;

      if (!::axis::system::process_initialize())
         return false;


      //System.factory().cloneable_large < ::OS::window_buffer >   (System.type_info < ::window_graphics > ());



      m_spos.alloc(allocer());





      return true;

   }


   bool system::initialize_native_window1()
   {

#if !defined(LINUX) && !defined(WINDOWSEX) && !defined(MACOS)

      m_possystemwindow->m_pui = new ::user::interaction(this);

#endif

      return true;

   }


} // namespace base















/* colorramp.c -- color temperature calculation source
This file is part of Redshift.
Redshift is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
Redshift is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with Redshift.  If not, see <http://www.gnu.org/licenses/>.
Copyright (c) 2013-2014  Jon Lund Steffensen <jonlst@gmail.com>
Copyright (c) 2013  Ingo Thies <ithies@astro.uni-bonn.de>
*/

/* Whitepoint values for temperatures at 100K intervals.
These will be interpolated for the actual temperature.
This table was provided by Ingo Thies, 2013. See
the file README-colorramp for more information. */
static const float g_fa_blackbody_color[] =
{
   1.00000000,  0.18172716,  0.00000000, /* 1000K */
   1.00000000,  0.25503671,  0.00000000, /* 1100K */
   1.00000000,  0.30942099,  0.00000000, /* 1200K */
   1.00000000,  0.35357379,  0.00000000, /* ...   */
   1.00000000,  0.39091524,  0.00000000,
   1.00000000,  0.42322816,  0.00000000,
   1.00000000,  0.45159884,  0.00000000,
   1.00000000,  0.47675916,  0.00000000,
   1.00000000,  0.49923747,  0.00000000,
   1.00000000,  0.51943421,  0.00000000,
   1.00000000,  0.54360078,  0.08679949,
   1.00000000,  0.56618736,  0.14065513,
   1.00000000,  0.58734976,  0.18362641,
   1.00000000,  0.60724493,  0.22137978,
   1.00000000,  0.62600248,  0.25591950,
   1.00000000,  0.64373109,  0.28819679,
   1.00000000,  0.66052319,  0.31873863,
   1.00000000,  0.67645822,  0.34786758,
   1.00000000,  0.69160518,  0.37579588,
   1.00000000,  0.70602449,  0.40267128,
   1.00000000,  0.71976951,  0.42860152,
   1.00000000,  0.73288760,  0.45366838,
   1.00000000,  0.74542112,  0.47793608,
   1.00000000,  0.75740814,  0.50145662,
   1.00000000,  0.76888303,  0.52427322,
   1.00000000,  0.77987699,  0.54642268,
   1.00000000,  0.79041843,  0.56793692,
   1.00000000,  0.80053332,  0.58884417,
   1.00000000,  0.81024551,  0.60916971,
   1.00000000,  0.81957693,  0.62893653,
   1.00000000,  0.82854786,  0.64816570,
   1.00000000,  0.83717703,  0.66687674,
   1.00000000,  0.84548188,  0.68508786,
   1.00000000,  0.85347859,  0.70281616,
   1.00000000,  0.86118227,  0.72007777,
   1.00000000,  0.86860704,  0.73688797,
   1.00000000,  0.87576611,  0.75326132,
   1.00000000,  0.88267187,  0.76921169,
   1.00000000,  0.88933596,  0.78475236,
   1.00000000,  0.89576933,  0.79989606,
   1.00000000,  0.90198230,  0.81465502,
   1.00000000,  0.90963069,  0.82838210,
   1.00000000,  0.91710889,  0.84190889,
   1.00000000,  0.92441842,  0.85523742,
   1.00000000,  0.93156127,  0.86836903,
   1.00000000,  0.93853986,  0.88130458,
   1.00000000,  0.94535695,  0.89404470,
   1.00000000,  0.95201559,  0.90658983,
   1.00000000,  0.95851906,  0.91894041,
   1.00000000,  0.96487079,  0.93109690,
   1.00000000,  0.97107439,  0.94305985,
   1.00000000,  0.97713351,  0.95482993,
   1.00000000,  0.98305189,  0.96640795,
   1.00000000,  0.98883326,  0.97779486,
   1.00000000,  0.99448139,  0.98899179,
   1.00000000,  1.00000000,  1.00000000, /* 6500K */
   0.98947904,  0.99348723,  1.00000000,
   0.97940448,  0.98722715,  1.00000000,
   0.96975025,  0.98120637,  1.00000000,
   0.96049223,  0.97541240,  1.00000000,
   0.95160805,  0.96983355,  1.00000000,
   0.94303638,  0.96443333,  1.00000000,
   0.93480451,  0.95923080,  1.00000000,
   0.92689056,  0.95421394,  1.00000000,
   0.91927697,  0.94937330,  1.00000000,
   0.91194747,  0.94470005,  1.00000000,
   0.90488690,  0.94018594,  1.00000000,
   0.89808115,  0.93582323,  1.00000000,
   0.89151710,  0.93160469,  1.00000000,
   0.88518247,  0.92752354,  1.00000000,
   0.87906581,  0.92357340,  1.00000000,
   0.87315640,  0.91974827,  1.00000000,
   0.86744421,  0.91604254,  1.00000000,
   0.86191983,  0.91245088,  1.00000000,
   0.85657444,  0.90896831,  1.00000000,
   0.85139976,  0.90559011,  1.00000000,
   0.84638799,  0.90231183,  1.00000000,
   0.84153180,  0.89912926,  1.00000000,
   0.83682430,  0.89603843,  1.00000000,
   0.83225897,  0.89303558,  1.00000000,
   0.82782969,  0.89011714,  1.00000000,
   0.82353066,  0.88727974,  1.00000000,
   0.81935641,  0.88452017,  1.00000000,
   0.81530175,  0.88183541,  1.00000000,
   0.81136180,  0.87922257,  1.00000000,
   0.80753191,  0.87667891,  1.00000000,
   0.80380769,  0.87420182,  1.00000000,
   0.80018497,  0.87178882,  1.00000000,
   0.79665980,  0.86943756,  1.00000000,
   0.79322843,  0.86714579,  1.00000000,
   0.78988728,  0.86491137,  1.00000000, /* 10000K */
   0.78663296,  0.86273225,  1.00000000,
   0.78346225,  0.86060650,  1.00000000,
   0.78037207,  0.85853224,  1.00000000,
   0.77735950,  0.85650771,  1.00000000,
   0.77442176,  0.85453121,  1.00000000,
   0.77155617,  0.85260112,  1.00000000,
   0.76876022,  0.85071588,  1.00000000,
   0.76603147,  0.84887402,  1.00000000,
   0.76336762,  0.84707411,  1.00000000,
   0.76076645,  0.84531479,  1.00000000,
   0.75822586,  0.84359476,  1.00000000,
   0.75574383,  0.84191277,  1.00000000,
   0.75331843,  0.84026762,  1.00000000,
   0.75094780,  0.83865816,  1.00000000,
   0.74863017,  0.83708329,  1.00000000,
   0.74636386,  0.83554194,  1.00000000,
   0.74414722,  0.83403311,  1.00000000,
   0.74197871,  0.83255582,  1.00000000,
   0.73985682,  0.83110912,  1.00000000,
   0.73778012,  0.82969211,  1.00000000,
   0.73574723,  0.82830393,  1.00000000,
   0.73375683,  0.82694373,  1.00000000,
   0.73180765,  0.82561071,  1.00000000,
   0.72989845,  0.82430410,  1.00000000,
   0.72802807,  0.82302316,  1.00000000,
   0.72619537,  0.82176715,  1.00000000,
   0.72439927,  0.82053539,  1.00000000,
   0.72263872,  0.81932722,  1.00000000,
   0.72091270,  0.81814197,  1.00000000,
   0.71922025,  0.81697905,  1.00000000,
   0.71756043,  0.81583783,  1.00000000,
   0.71593234,  0.81471775,  1.00000000,
   0.71433510,  0.81361825,  1.00000000,
   0.71276788,  0.81253878,  1.00000000,
   0.71122987,  0.81147883,  1.00000000,
   0.70972029,  0.81043789,  1.00000000,
   0.70823838,  0.80941546,  1.00000000,
   0.70678342,  0.80841109,  1.00000000,
   0.70535469,  0.80742432,  1.00000000,
   0.70395153,  0.80645469,  1.00000000,
   0.70257327,  0.80550180,  1.00000000,
   0.70121928,  0.80456522,  1.00000000,
   0.69988894,  0.80364455,  1.00000000,
   0.69858167,  0.80273941,  1.00000000,
   0.69729688,  0.80184943,  1.00000000,
   0.69603402,  0.80097423,  1.00000000,
   0.69479255,  0.80011347,  1.00000000,
   0.69357196,  0.79926681,  1.00000000,
   0.69237173,  0.79843391,  1.00000000,
   0.69119138,  0.79761446,  1.00000000, /* 15000K */
   0.69003044,  0.79680814,  1.00000000,
   0.68888844,  0.79601466,  1.00000000,
   0.68776494,  0.79523371,  1.00000000,
   0.68665951,  0.79446502,  1.00000000,
   0.68557173,  0.79370830,  1.00000000,
   0.68450119,  0.79296330,  1.00000000,
   0.68344751,  0.79222975,  1.00000000,
   0.68241029,  0.79150740,  1.00000000,
   0.68138918,  0.79079600,  1.00000000,
   0.68038380,  0.79009531,  1.00000000,
   0.67939381,  0.78940511,  1.00000000,
   0.67841888,  0.78872517,  1.00000000,
   0.67745866,  0.78805526,  1.00000000,
   0.67651284,  0.78739518,  1.00000000,
   0.67558112,  0.78674472,  1.00000000,
   0.67466317,  0.78610368,  1.00000000,
   0.67375872,  0.78547186,  1.00000000,
   0.67286748,  0.78484907,  1.00000000,
   0.67198916,  0.78423512,  1.00000000,
   0.67112350,  0.78362984,  1.00000000,
   0.67027024,  0.78303305,  1.00000000,
   0.66942911,  0.78244457,  1.00000000,
   0.66859988,  0.78186425,  1.00000000,
   0.66778228,  0.78129191,  1.00000000,
   0.66697610,  0.78072740,  1.00000000,
   0.66618110,  0.78017057,  1.00000000,
   0.66539706,  0.77962127,  1.00000000,
   0.66462376,  0.77907934,  1.00000000,
   0.66386098,  0.77854465,  1.00000000,
   0.66310852,  0.77801705,  1.00000000,
   0.66236618,  0.77749642,  1.00000000,
   0.66163375,  0.77698261,  1.00000000,
   0.66091106,  0.77647551,  1.00000000,
   0.66019791,  0.77597498,  1.00000000,
   0.65949412,  0.77548090,  1.00000000,
   0.65879952,  0.77499315,  1.00000000,
   0.65811392,  0.77451161,  1.00000000,
   0.65743716,  0.77403618,  1.00000000,
   0.65676908,  0.77356673,  1.00000000,
   0.65610952,  0.77310316,  1.00000000,
   0.65545831,  0.77264537,  1.00000000,
   0.65481530,  0.77219324,  1.00000000,
   0.65418036,  0.77174669,  1.00000000,
   0.65355332,  0.77130560,  1.00000000,
   0.65293404,  0.77086988,  1.00000000,
   0.65232240,  0.77043944,  1.00000000,
   0.65171824,  0.77001419,  1.00000000,
   0.65112144,  0.76959404,  1.00000000,
   0.65053187,  0.76917889,  1.00000000,
   0.64994941,  0.76876866,  1.00000000, /* 20000K */
   0.64937392,  0.76836326,  1.00000000,
   0.64880528,  0.76796263,  1.00000000,
   0.64824339,  0.76756666,  1.00000000,
   0.64768812,  0.76717529,  1.00000000,
   0.64713935,  0.76678844,  1.00000000,
   0.64659699,  0.76640603,  1.00000000,
   0.64606092,  0.76602798,  1.00000000,
   0.64553103,  0.76565424,  1.00000000,
   0.64500722,  0.76528472,  1.00000000,
   0.64448939,  0.76491935,  1.00000000,
   0.64397745,  0.76455808,  1.00000000,
   0.64347129,  0.76420082,  1.00000000,
   0.64297081,  0.76384753,  1.00000000,
   0.64247594,  0.76349813,  1.00000000,
   0.64198657,  0.76315256,  1.00000000,
   0.64150261,  0.76281076,  1.00000000,
   0.64102399,  0.76247267,  1.00000000,
   0.64055061,  0.76213824,  1.00000000,
   0.64008239,  0.76180740,  1.00000000,
   0.63961926,  0.76148010,  1.00000000,
   0.63916112,  0.76115628,  1.00000000,
   0.63870790,  0.76083590,  1.00000000,
   0.63825953,  0.76051890,  1.00000000,
   0.63781592,  0.76020522,  1.00000000,
   0.63737701,  0.75989482,  1.00000000,
   0.63694273,  0.75958764,  1.00000000,
   0.63651299,  0.75928365,  1.00000000,
   0.63608774,  0.75898278,  1.00000000,
   0.63566691,  0.75868499,  1.00000000,
   0.63525042,  0.75839025,  1.00000000,
   0.63483822,  0.75809849,  1.00000000,
   0.63443023,  0.75780969,  1.00000000,
   0.63402641,  0.75752379,  1.00000000,
   0.63362667,  0.75724075,  1.00000000,
   0.63323097,  0.75696053,  1.00000000,
   0.63283925,  0.75668310,  1.00000000,
   0.63245144,  0.75640840,  1.00000000,
   0.63206749,  0.75613641,  1.00000000,
   0.63168735,  0.75586707,  1.00000000,
   0.63131096,  0.75560036,  1.00000000,
   0.63093826,  0.75533624,  1.00000000,
   0.63056920,  0.75507467,  1.00000000,
   0.63020374,  0.75481562,  1.00000000,
   0.62984181,  0.75455904,  1.00000000,
   0.62948337,  0.75430491,  1.00000000,
   0.62912838,  0.75405319,  1.00000000,
   0.62877678,  0.75380385,  1.00000000,
   0.62842852,  0.75355685,  1.00000000,
   0.62808356,  0.75331217,  1.00000000,
   0.62774186,  0.75306977,  1.00000000, /* 25000K */
   0.62740336,  0.75282962,  1.00000000  /* 25100K */
};

static void
interpolate_color(float a, const float *c1, const float *c2, float *r, float *g, float *b)
{
   *r = (1.0f - a)*c1[0] + a*c2[0];
   *g = (1.0f - a)*c1[1] + a*c2[1];
   *b = (1.0f - a)*c1[2] + a*c2[2];
}




CLASS_DECL_BASE void black_body(float * r, float * g, float * b, DWORD dwTemp)
{

   int temp_index = ((dwTemp - 1000) / 100) * 3;

   if (temp_index < 0)
   {

      temp_index = 0;

   }
   else if (temp_index > (sizeof(g_fa_blackbody_color) / sizeof(float)) - 3)
   {

      temp_index = (sizeof(g_fa_blackbody_color) / sizeof(float)) - 3;

   }

   float alpha = (dwTemp % 100) / 100.0f;

   interpolate_color(alpha, &g_fa_blackbody_color[temp_index], &g_fa_blackbody_color[temp_index + 3], r, g, b);

}

