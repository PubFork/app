#include "framework.h"


namespace asphere
{


   application::application()
   {
      
      m_bSync = false;
      
      m_iSyncCount = 0;

      m_bContextTheme = true;


   }


   application::~application()
   {

   }


   bool application::init_instance()
   {

      if (!::core::application::init_instance())
      {

         return false;

      }

      if (m_bContextTheme)
      {
         
         initialize_contextualized_theme();
       
      }

      m_watchid = System.dir().add_watch(::dir::system()/"config", this, false);
      
      return true;

   }


   bool application::init1()
   {

      if(!::core::application::init1())
         return false;

      return true;

   }


   bool application::init()
   {

      if (!::core::application::init())
      {

         return false;

      }

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


   void application::sync_with_stored_theme()
   {

      set_context_theme(stored_theme());

   }


   string application::get_current_weather()
   {

#ifdef METROWIN

      return "";

#endif

      ::file::path pathWeatherState = ::dir::system() / "config/weather_state.txt";

      string strState = Application.file().as_string(pathWeatherState);

      if (strState.is_empty())
      {

         return "";

      }

      string strContext;

      if(strState.contains_ci("night"))
      {

         strContext += ".night";

      }
      else
      {

         strContext += ".day";

      }

      if (strState.contains_ci("cloud") && !strState.contains_ci("partly"))
      {

         strContext += ".dampened";

      }
      else if (strState.contains_ci("rain"))
      {

         strContext += ".dampened";

      }

      return strContext;

   }


   string application::get_default_theme()
   {

      string strTheme;

      string strWeather = get_current_weather();

      if (strWeather.find_ci(".night") >= 0 && m_straTheme.contains_ci("dark"))
      {

         strTheme = "dark";

      }
      else if (strWeather.find_ci(".dampened") && m_straTheme.contains_ci("blue"))
      {

         strTheme = "blue";

      }
      else if (strWeather.find_ci(".day") && m_straTheme.contains_ci("lite"))
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


   string application::stored_theme()
   {
      
      string strCurrentWeather = get_current_weather();

      string strTheme = app_get("theme-" + strCurrentWeather);

      if (strTheme.is_empty())
      {

         strTheme = get_default_theme();

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

      strContextTheme = stored_theme();

      if (strContextTheme != strTheme)
      {

         app_set("theme-" + get_current_weather(), strTheme);

      }

      m_strTheme = strTheme;

      on_change_theme();

   }


   string application::get_theme()
   {

      return m_strTheme;

   }


   uint32_t application::guess_code_page(const string & str)
   {

      return charguess(str)();

   }


   colorertake5::ParserFactory & application::parser_factory()
   {

      if(m_pparserfactory == NULL)
      {

         m_pparserfactory = new colorertake5::ParserFactory(this);

      }

      return *m_pparserfactory;

   }
      void application::handle_file_action(::file_watcher::id watchid, const char * dir, const char * filename, ::file_watcher::e_action action)
      {
         
         string strFilename = filename;
         
         if (strFilename.ends_ci("weather_state.txt"))
         {
            
            delay_fork(&m_bSync, &m_iSyncCount, millis(300),
                         [=]
                         ()
                         {
                            
                            on_change_weather_state();

                         });
            
         }
         
         
      }
   
   

   void application::on_change_weather_state()
   {
   
      ::file::path pathWeatherState = ::dir::system() / "config/weather_state.txt";
      
      string strWeatherState = Application.file().as_string(pathWeatherState);
      
      m_strWeatherState = strWeatherState;
      
      bool bDay = m_strWeatherState.find_ci(".day") >= 0;
      
      string strDayNight;
      
      string strDayNightTheme;
      
      if (bDay)
      {
         
         strDayNight = "day";
         
         strDayNightTheme = "lite";
         
      }
      else
      {
         
         strDayNight = "night";
         
         strDayNightTheme = "dark";
         
      }
      
      m_strDayNight = strDayNight;
      
      m_strDayNightTheme = strDayNightTheme;
      
      if(m_bContextTheme)
      {
         
         sync_with_stored_theme();
         
      }
      
   }
   
   
   string application::get_weather_state()
   {
    
      return m_strWeatherState;
      
   }


   string application::get_day_night()
   {
      
      return m_strDayNight;
      
   }
   
   
   string application::get_day_night_theme()
   {
      
      return m_strDayNightTheme;
      
   }


   void application::initialize_contextualized_theme()
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
      
      sync_with_stored_theme();

      
   }
   
   
} //namespace sphere



