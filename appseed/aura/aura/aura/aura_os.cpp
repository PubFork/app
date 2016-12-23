#include "framework.h"


namespace aura
{


   os::os(::aura::application * papp) :
      object(papp)
   {
   }

   os::~os()
   {
   }


   bool os::shutdown(bool bIfPowerOff)
   {
      UNREFERENCED_PARAMETER(bIfPowerOff);
      throw interface_only_exception(get_app(), "this is an interface");
   }

   bool os::reboot()
   {
      throw interface_only_exception(get_app(), "this is an interface");
   }

   void os::terminate_processes_by_title(const char * pszName)
   {
      UNREFERENCED_PARAMETER(pszName);
      throw interface_only_exception(get_app(), "this is an interface");
   }

   bool os::get_pid_by_path(const char * pszName, uint32_t & dwPid)
   {
      UNREFERENCED_PARAMETER(pszName);
      UNREFERENCED_PARAMETER(dwPid);
      throw interface_only_exception(get_app(), "this is an interface");
   }

   bool os::get_pid_by_title(const char * pszName, uint32_t & dwPid)
   {
      UNREFERENCED_PARAMETER(pszName);
      UNREFERENCED_PARAMETER(dwPid);
      throw interface_only_exception(get_app(), "this is an interface");
   }

   int os::get_pid()
   {
      throw interface_only_exception(get_app(),"this is an interface");
   }

   ::file::path os::get_process_path(uint32_t dwPid)
   {
      UNREFERENCED_PARAMETER(dwPid);
      throw interface_only_exception(get_app(), "this is an interface");
   }

   void os::get_all_processes(uint_array & dwa )
   {
      UNREFERENCED_PARAMETER(dwa);
      throw interface_only_exception(get_app(), "this is an interface");
   }

#ifdef WINDOWS

   ::file::path os::get_module_path(HMODULE hmodule)
   {
      UNREFERENCED_PARAMETER(hmodule);
      throw interface_only_exception(get_app(), "this is an interface");
   }

#endif


   bool os::connection_settings_get_auto_detect()
   {

      return true;

   }


   string os::connection_settings_get_auto_config_url()
   {

      return "";

   }

   bool os::local_machine_set_run(const char * pszKey, const char * pszCommand)
   {

      UNREFERENCED_PARAMETER(pszKey);
      UNREFERENCED_PARAMETER(pszCommand);

      return false;

   }

   bool os::local_machine_set_run_once(const char * pszKey, const char * pszCommand)
   {

      UNREFERENCED_PARAMETER(pszKey);
      UNREFERENCED_PARAMETER(pszCommand);

      return false;

   }

   bool os::current_user_set_run(const char * pszKey, const char * pszCommand)
   {

      UNREFERENCED_PARAMETER(pszKey);
      UNREFERENCED_PARAMETER(pszCommand);

      return false;

   }

   bool os::current_user_set_run_once(const char * pszKey, const char * pszCommand)
   {

      UNREFERENCED_PARAMETER(pszKey);
      UNREFERENCED_PARAMETER(pszCommand);

      return false;

   }

   bool os::defer_register_ca2_plugin_for_mozilla()
   {

      return false;

   }

   bool os::file_extension_get_open_with_list_keys(stringa & straKey, const char * pszExtension)
   {

      UNREFERENCED_PARAMETER(straKey);
      UNREFERENCED_PARAMETER(pszExtension);

      return false;

   }

   bool os::file_extension_get_open_with_list_commands(stringa & straCommand, const char * pszExtension)
   {

      UNREFERENCED_PARAMETER(straCommand);
      UNREFERENCED_PARAMETER(pszExtension);

      return false;

   }


   bool os::file_association_set_default_icon(const char * pszExtension, const char * pszExtensionNamingClass, const char * pszIconPath)
   {

      UNREFERENCED_PARAMETER(pszExtension);
      UNREFERENCED_PARAMETER(pszExtensionNamingClass);
      UNREFERENCED_PARAMETER(pszIconPath);

      return false;

   }


   bool os::file_association_set_shell_open_command(const char * pszExtension, const char * pszExtensionNamingClass,  const char * pszCommand, const char * pszParam)
   {

      UNREFERENCED_PARAMETER(pszExtension);
      UNREFERENCED_PARAMETER(pszExtensionNamingClass);
      UNREFERENCED_PARAMETER(pszCommand);
      UNREFERENCED_PARAMETER(pszParam);

      return false;

   }


   bool os::file_association_get_shell_open_command(const char * pszExtension, string & strExtensionNamingClass, string & strCommand, string & strParam)
   {

      UNREFERENCED_PARAMETER(pszExtension);
      UNREFERENCED_PARAMETER(strExtensionNamingClass);
      UNREFERENCED_PARAMETER(strCommand);
      UNREFERENCED_PARAMETER(strParam);

      return false;

   }

#ifdef WINDOWS

   bool os::open_in_ie(const char * lpcsz)
   {

      ::exception::throw_interface_only(get_app());

      return false;

   }

#endif


   bool os::create_service(::aura::application * papp)
   {


      ::exception::throw_not_implemented(get_app());


      return false;


   }


   bool os::remove_service(::aura::application * papp)
   {


      ::exception::throw_not_implemented(get_app());


      return false;


   }


   bool os::start_service(::aura::application * papp)
   {


      ::exception::throw_not_implemented(get_app());


      return false;


   }


   bool os::stop_service(::aura::application * papp)
   {


      ::exception::throw_not_implemented(get_app());


      return false;


   }


   bool os::create_service(const string & strServiceName,const string & strDisplayName,const string & strCommand,const string & strUser,const string & strPass)
   {


      ::exception::throw_not_implemented(get_app());


      return false;


   }


   bool os::remove_service(const string & strServiceName)
   {


      ::exception::throw_not_implemented(get_app());


      return false;


   }


   bool os::start_service(const string & strServiceName)
   {


      ::exception::throw_not_implemented(get_app());


      return false;


   }


   bool os::stop_service(const string & strServiceName)
   {


      ::exception::throw_not_implemented(get_app());


      return false;


   }


   bool os::is_remote_session()
   {

      return false;

   }


   void os::set_file_status(const char * lpszFileName, const ::file::file_status& status)
   {

      ::exception::throw_interface_only(get_app());

   }


   bool os::resolve_link(string & strTarget, string & strDirectory, string & strParams, const string & pszSource,::user::primitive * puiMessageParentOptional)
   {

      ::exception::throw_interface_only(get_app());

      return false;

   }


   bool os::initialize_wallpaper_fileset(::file::set * pfileset, bool bAddSearch)
   {

      ::stringa stra;

      //stra.add("_inheaven_1920x1080_o.JPG");
      //stra.add("02209_stratosphere_1920x1080_o.JPG");
      //stra.add("Bamboo Weathered Standard.jpg");

      stra.add("bambu1.jpg");
      stra.add("bambu2.jpg");
      stra.add("bambu3.jpg");
      stra.add("bambu33.png");
      stra.add("bambu4.jpg");
      
      ::file::path pathFolder;
      
      pathFolder = "https://server.ca2.cc/image/cc/ca2core/bkimageoftheday/common/";

      for (auto & str : stra)
      {

         ::file::path path = pathFolder / (str + string("?sessid=noauth"));

         pfileset->m_straFileAddUp.add(path);

      }

      return true;

   }

   bool os::file_open(string str)
   {

      return false;

   }

   string os::get_default_browser()
   {

      string strId;

      ::file::path path;

      string strParam;

      if (!get_default_browser(strId, path, strParam))
      {

         return "";

      }

      return strId;

   }


   bool os::get_default_browser(string & strId, ::file::path & path, string & strParam)
   {

      UNREFERENCED_PARAMETER(strId);
      UNREFERENCED_PARAMETER(path);
      UNREFERENCED_PARAMETER(strParam);

      return false;

   }


} // namespace core





