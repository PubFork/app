#include "framework.h"


namespace linux
{


   desktop_file::desktop_file(::aura::application * papp) :
      ::object(papp)
   {

   }

   desktop_file::~desktop_file()
   {


   }


   //AudioVideo   Application for presenting, creating, or processing multimedia (audio/video)
   //Audio        An audio application                                                          Desktop entry must include AudioVideo as well
   //Video        A video application	                                                         Desktop entry must include AudioVideo as well
   //Development  An application for development
   //Education    Educational software
   //Game         A game
   //Graphics     Application for viewing, creating, or processing graphics
   //Network      Network application such as a web browser
   //Office       An office type application
   //Science      Scientific software
   //Settings     Settings applications                                                         Entries may appear in a separate menu or as part of a "Control Center"
   //System       System application, "System Tools" such as say a log viewer or network monitor
   //Utility      Small utility application, "Accessories"

   stringa desktop_file::registered_categories()
   {

      stringa stra;

      stra.add("AudioVideo");
      stra.add("Audio");
      stra.add("Video");
      stra.add("Development");
      stra.add("Education");
      stra.add("Game");
      stra.add("Graphics");
      stra.add("Network");
      stra.add("Office");
      stra.add("Science");
      stra.add("Settings");
      stra.add("System");
      stra.add("Utility");

      return stra;

   }


   string desktop_file::proper_category(string str)
   {

      if(str.compare_ci("Multimedia") == 0)
      {

         return "AudioVideo";

      }
      else if(str.compare_ci("Accessory") == 0)
      {

         return "Utility";

      }
      else if(str.compare_ci("Accessories") == 0)
      {

      return "Utility";

      }
      else if(str.compare_ci("Utility") == 0)
      {

         return "Utility";

      }
      else if(str.compare_ci("Utilities") == 0)
      {

         return "Utility";

      }
      else
      {

         stringa stra = registered_categories();

         index iFind = stra.find_first_ci(str);

         if(iFind >= 0)
         {

            return stra[iFind];

         }

      }

      return "";

   }


   stringa desktop_file::proper_category(stringa straCategoryParam)
   {

      stringa straCategory;

      for(auto strCategoryParam : straCategoryParam)
      {

         string strCategory = proper_category(strCategoryParam);

         if(strCategory.has_char())
         {

            straCategory.add(strCategory);

            if(strCategory == "Audio" || strCategory == "Video")
            {

               straCategory.add("AudioVideo");

            }

         }
         else
         {

            string strMessage;

            strMessage.Format("Category \"%s\"has not been found", strCategoryParam);

            TRACE(strMessage);

         }

      }

      straCategory.remove_duplicates_ci();

      return straCategory;

   }


   ::file::path desktop_file::get_board_path()
   {

      ::file::path path;

      path = ::dir::home();

      path /= ".config/ca2/local/localconfig/desk/2desk";

      string strPrgName = Application.m_strAppId;

      strPrgName.replace("/", ".");

      strPrgName.replace("_", "-");

      path /= ("cc.ca2." + strPrgName + ".desktop");

      return path;

   }


   ::file::path desktop_file::get_file_path()
   {

      ::file::path path;

      path = ::dir::home();

      path /= ".local/share/applications";

      string strPrgName = Application.m_strAppId;

      strPrgName.replace("/", ".");

      strPrgName.replace("_", "-");

      path /= ("cc.ca2." + strPrgName + ".desktop");

      return path;

   }


   void desktop_file::create_default()
   {

      stringa & straLine = m_straLine;

      straLine.add("[Desktop Entry]");
      straLine.add("Version=1.0");
      straLine.add("Type=Application");
      straLine.add("Name=");
      straLine.add("GenericName=");
      straLine.add("Comment=");
      straLine.add("Exec=");
      straLine.add("Icon=");
      straLine.add("Terminal=false");
      straLine.add("X-MultipleArgs=false");
      straLine.add("Categories=Utilities;");
      straLine.add("StartupNotify=true");
      straLine.add("MimeType=");

   }


   void desktop_file::create()
   {

      ::file::path path = Application.dir().matter("app.desktop");

      Application.file().lines(m_straLine, path);

      if(m_straLine.is_empty())
      {

         create_default();

      }

      string strTitle = Application.get_title();

      stringa straCategories = proper_category(Application.get_categories());

      string strPrgName = Application.m_strAppId;

      strPrgName.replace("/", ".");

      strPrgName.replace("_", "-");

      ::file::path pathIcon = Application.dir().matter("main/icon-256.png");

      stringa & straLine = m_straLine;

      straLine._007SetLine("GenericName", strTitle);
      straLine._007SetLine("Name", strTitle);
      straLine._007SetLine("Comment", strTitle + " Comment");
      straLine._007SetLine("Exec", "\"" + string(System.file().module()) + "\" %U");
      straLine._007SetLine("StartupWMClass", "cc.ca2." + strPrgName);

      if(Application.file().exists(pathIcon))
      {

         straLine._007SetLine("Icon", pathIcon);

      }

      if(straCategories.has_elements() && straCategories.implode("").has_char())
      {

         straLine._007SetLine("Categories", straCategories.implode(";") + ";");

      }

   }


   void desktop_file::write()
   {

      ::file::path path = get_file_path();

      Application.file().put_lines(path, m_straLine);

      chmod(path, S_IRUSR | S_IWUSR | S_IXUSR);

      path = get_board_path();

      Application.file().put_lines(path, m_straLine);

      chmod(path, S_IRUSR | S_IWUSR | S_IXUSR);

   }


   bool desktop_file::bamf_set_icon(oswindow oswindow)
   {

      ::file::path path = get_file_path();

      xdisplay d(oswindow->display());

      Atom net_wm_icon = XInternAtom(oswindow->display(), "_BAMF_DESKTOP_FILE", False);

      Atom cardinal = XInternAtom(oswindow->display(), "STRING", False);

      int ixa = XA_STRING;

      int status = XChangeProperty(
                     oswindow->display(),
                     oswindow->window(),
                     net_wm_icon,
                     ixa,
                     8,
                     PropModeReplace,
                     (const unsigned char*) (const char *) path,
                     path.get_length());

      if(status != 0)
      {

         return false;

      }

      return true;

   }


} // namespace linux
