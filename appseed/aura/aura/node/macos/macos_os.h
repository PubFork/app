#pragma once


namespace macos
{


   class CLASS_DECL_AURA os :
      virtual public ::aura::os
   {
   public:


      os(::aura::application * papp);
      virtual ~os();

      
      virtual string get_command_line() override;

      virtual bool reboot() override;
      
      virtual bool shutdown(bool bPowerOff) override;

      virtual void terminate_processes_by_title(const char * pszName) override;
      //virtual string get_module_path(HMODULE hmodule);
      
      virtual bool get_pid_by_path(const char * pszName, DWORD & dwPid) override;
      
      virtual bool get_pid_by_title(const char * pszName, DWORD & dwPid) override;
      
      virtual void get_all_processes(uint_array & dwa) override;
       virtual ::file::path get_process_path(DWORD dwPid) override;

      virtual bool connection_settings_get_auto_detect() override;
      virtual string connection_settings_get_auto_config_url() override;


      virtual bool local_machine_set_run(const char * pszKey, const char * pszCommand);
      virtual bool local_machine_set_run_once(const char * pszKey, const char * pszCommand);
      virtual bool current_user_set_run(const char * pszKey, const char * pszCommand);
      virtual bool current_user_set_run_once(const char * pszKey, const char * pszCommand);
      virtual bool defer_register_ca2_plugin_for_mozilla() override;
      

      virtual bool file_extension_get_open_with_list_keys(stringa & straKey, const char * pszExtension) override;
      
      virtual bool file_extension_get_open_with_list_commands(stringa & straCommand, const char * pszExtension) override;

      virtual bool file_association_set_default_icon(const char * pszExtension, const char * pszExtensionNamingClass, const char * pszIconPath) override;
      
      virtual bool file_association_set_shell_open_command(const char * pszExtension, const char * pszExtensionNamingClass,  const char * pszCommand, const char * pszParam) override;

      virtual bool file_association_get_shell_open_command(const char * pszExtension, string & strExtensionNamingClass, string & strCommand, string & strParam) override;

      virtual bool open_in_ie(const char * lpcsz);

      virtual bool create_service(sp(::aura::application) papp);
      
      virtual bool remove_service(sp(::aura::application) papp);

      virtual bool start_service(sp(::aura::application) papp);

      virtual bool stop_service(sp(::aura::application) papp);

      virtual bool resolve_link(::file::path & pathTarget, string & strFolder, string & strParams, const string & strSource, ::user::primitive * puiMessageParentOptional = NULL) override;

      void raise_exception( DWORD dwExceptionCode, DWORD dwExceptionFlags);

      virtual bool is_remote_session() override;

      virtual void post_to_all_threads(UINT message, WPARAM wParam, LPARAM lParam);
      
      virtual int get_pid() override;
      
      virtual bool initialize_wallpaper_fileset(::file::set * pfileset, bool bAddSearch) override;

      virtual bool get_default_browser(string & strId, ::file::path & path, string & strParam) override;

      virtual bool set_default_browser(::aura::application * papp) override;

      virtual ::file::path get_app_path(const string & strApp) override;
      
      virtual void on_process_command(::command::command * pcommand) override;
      
      virtual bool file_open(::aura::application * papp, ::file::path path, string strParams = "", string strFolder = "") override;
      
      virtual void set_file_status(const char * lpszFileName, const ::file::file_status& status) override;
      
      virtual bool browse_folder(oswindow oswindowOwner, property_set &set) override;
      virtual bool browse_file_open(oswindow oswindowOwner, property_set &set) override;
      
   };



} // namespace macos




