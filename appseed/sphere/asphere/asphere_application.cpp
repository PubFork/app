#include "framework.h"

//#if defined(LINUX) || defined(APPLEOS)
//#include <dlfcn.h>
//#endif



namespace asphere
{


   application::application()
   {

      m_mapBg["dark"] = ARGB(160, 0x16, 0x19, 0x1e);
      m_mapBg["blue"] = ARGB(160, 0xA0, 0xA8, 0xB8);
      m_mapBg["lite"] = ARGB(160, 0xff, 0xff, 0xff);

      m_mapIconGlow["dark"] = ARGB(255, 0x16, 0x19, 0x1e);
      m_mapIconGlow["blue"] = ARGB(255, 0x48, 0x58, 0x88);
      m_mapIconGlow["lite"] = ARGB(255, 0xff, 0xff, 0xff);

      m_mapMg["dark"] = ARGB(151, 0x16, 0x19, 0x1e);
      m_mapMg["blue"] = ARGB(151, 0xA0, 0xA8, 0xB8);
      m_mapMg["lite"] = ARGB(140, 255, 255, 255);

      m_mapFg["dark"] = ARGB(255, 223, 223, 208);
      m_mapFg["blue"] = ARGB(255, 255, 255, 255);
      m_mapFg["lite"] = ARGB(255, 0, 0, 0);

      m_mapText["dark"] = ARGB(255, 155, 155, 155);
      m_mapText["blue"] = ARGB(255, 55, 50, 80);
      m_mapText["lite"] = ARGB(255, 0, 0, 0);

      m_mapBack["dark"] = ARGB(160, 0, 0, 0);
      m_mapBack["blue"] = ARGB(160, 205, 200, 250);
      m_mapBack["lite"] = ARGB(160, 255, 255, 255);


   }


   application::~application()
   {

   }


   bool application::initialize_application()
   {

      if (!::core::application::initialize_application())
      {

         return false;

      }

#if !defined(APPLE_IOS)

      Sess(this).userex()->shell()->m_straThemeableIconName.add("google-android.ico");
      Sess(this).userex()->shell()->m_straThemeableIconName.add("Folders-OS-Windows-8-Metro.ico");
      Sess(this).userex()->shell()->m_straThemeableIconName.add("firefox_weather.ico");

      ::file::patha patha;

      dir().matter_ls("sphere/theme", patha);

      m_straTheme.add_unique("blue");
      m_straTheme.add_unique("dark");
      m_straTheme.add_unique("lite");

      for (auto & path : patha)
      {

         if (dir().is(path))
         {

            string strTheme = path.name();

            m_straTheme.add_unique(strTheme);

         }

      }

      connect_command("theme", &application::_001OnTheme);

#endif

      sync_context_theme();

      ::fork(this, [&]()
      {

         while (get_thread_run())
         {

            sync_context_theme();

            Sleep(1000);

         }

         TRACE("finished sync context theme thread");

      });

      return true;

   }


   bool application::initialize1()
   {

      if(!::core::application::initialize1())
         return false;

      return true;

   }

   bool application::initialize()
   {

      if(!::core::application::initialize())
         return false;


      return true;

   }


   void application::_001OnTheme(::message::message * pobj)
   {

      if (pobj != NULL)
      {

         pobj->m_bRet = true;

      }

      output_debug_string("changing theme\n");

      if (m_straTheme.get_size() <= 0)
      {

         return;

      }

      string strTheme = get_theme();

      strsize iFind = m_straTheme.find_first(strTheme);

      if (iFind < 0)
      {

         iFind = 0;

      }
      else
      {

         iFind++;

         iFind %= m_straTheme.get_size();

      }

      strTheme = m_straTheme[iFind];

      set_context_theme(strTheme);

   }


   ::file::path   application::get_theme_path()
   {

      return m_pathTheme;

   }


   void application::get_theme_text_color(COLORREF & crText, COLORREF & crBack)
   {

      crText = m_crText;

      crBack = m_crBack;

   }


   void application::on_change_theme()
   {

      string strTheme = get_theme();

      Sess(this).userex()->shell()->m_strShellThemePrefix = "desk/" + strTheme + "/";

      m_crFg = m_mapFg[strTheme];
      m_crBg = m_mapBg[strTheme];
      m_crMg = m_mapMg[strTheme];

      m_crIconGlow = m_mapIconGlow[strTheme];

      if (!m_mapText.Lookup(get_theme(), m_crText))
      {

         m_crText = ARGB(255, 255, 255, 255);

      }

      if (!m_mapBack.Lookup(get_theme(), m_crBack))
      {

         m_crBack = ARGB(208, 23, 23, 23);

      }

      m_pathTheme = ::file::path("theme") / get_theme();

   }


   void application::sync_context_theme()
   {

      set_context_theme(get_current_context_theme());

   }


   string application::get_theme_context()
   {

      string strEtime = Application.file().as_string(::dir::system() / "weather_etime.txt");

      string strContext;

      if (strEtime.is_empty())
      {

         strEtime = "day";

      }

      strContext += "." + strEtime;

      string strMain1 = Application.file().as_string(::dir::system() / "config/weather_main1.txt");

      if (strMain1.has_char())
      {

         if (strMain1.find_ci("cloud") >= 0 && strMain1.find_ci("partly") < 0)
         {

            strContext += ".dampened";

         }
         else if (strMain1.find_ci("rain") >= 0)
         {

            strContext += ".dampened";

         }

      }

      return strContext;

   }


   string application::get_context_default_theme()
   {

      string strTheme;

      string strContext = get_theme_context();

      if (strContext.find_ci(".night") >= 0 && m_straTheme.contains_ci("dark"))
      {

         strTheme = "dark";

      }
      else if (strContext.find_ci(".dampened") && m_straTheme.contains_ci("blue"))
      {

         strTheme = "blue";

      }
      else if (strContext.find_ci(".day") && m_straTheme.contains_ci("lite"))
      {

         strTheme = "lite";

      }
      else if (m_straTheme.contains_ci("dark"))
      {

         strTheme = "dark";

      }
      else if (m_straTheme.contains_ci("lite"))
      {

         strTheme = "blue";

      }
      else if(m_straTheme.has_elements())
      {

         strTheme = m_straTheme[0];

      }

      return strTheme;

   }


   string application::get_current_context_theme()
   {

      string strTheme = app_get("theme-" + get_theme_context());

      if (strTheme.is_empty())
      {

         strTheme = get_context_default_theme();

      }

      return strTheme;

   }


   void application::set_context_theme(string strTheme)
   {

      if (strTheme == m_strTheme)
      {

         return;

      }

      string strContextTheme;

      strContextTheme = get_current_context_theme();

      if (strContextTheme != strTheme)
      {

         app_set("theme-" + get_theme_context(), strTheme);

      }

      m_strTheme = strTheme;

      on_change_theme();

   }


   string application::get_theme()
   {

      return m_strTheme;

   }

//void application::set_theme(::sphere::e_theme etheme)
//{

//   int iTheme = (int)etheme;

//   int iThemeCount = (int)::sphere::theme_count;

//   if (iTheme < 0)
//   {

//      iTheme = 0;

//   }
//   else
//   {

//      iTheme %= iThemeCount;

//   }

//   m_etheme = (::sphere::e_theme) iTheme;

//   data_save("application.theme", iTheme);

//   output_debug_string("theme set to " + ::str::from(iTheme) + "\n");

//}

//::sphere::e_theme application::get_theme()
//{

//   return m_etheme;

//}



} //namespace sphere





