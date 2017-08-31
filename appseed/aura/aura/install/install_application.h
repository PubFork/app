#pragma once


#if defined(INSTALL_SUBSYSTEM)


namespace install
{


   class CLASS_DECL_AURA application :
      virtual public ::aura::application,
      virtual public ::aura::ipc::rx::receiver
   {
   public:


      enum e_message
      {
         message_none,
         message_ok,
         message_failed,
         message_unknown,
      };


      window *                         m_pwindow;
      bool                             m_bRunMainLoop;
      bool                             m_bAdmin;

      double                           m_dProgress;
      double                           m_dProgress1;
      double                           m_dProgress2;

      string                           m_strInstallId;

      ::install::socket_thread *       m_pthreadSsl;

      string                           m_strConfiguration;
      bool                             m_bFinished;

      string_map < bootstrap * >       m_bootstrap;



      e_message                        m_emessage;
      HANDLE                           m_hmutexSpabootInstall;
      ::aura::ipc::rx                  m_rxchannel;

      bool                             m_bInstallerInstalling;
      sp(mutex)                        m_spmutexAppInstall;


      application();
      virtual ~application();


      virtual bool start_instance();

      virtual int32_t exit_application();

      virtual void on_request(::create * pcreate);


      void add_command_line(string str);
      string pick_command_line();


      virtual string install_get_id() override;

      void install_set_id(const char * psz);


      virtual int app_app_main();
      virtual int start_app_app(string strPlatform);

      virtual bool install_get_admin();
      virtual void install_set_admin(bool bSet);

      virtual bool show_window();
      virtual bool hide_window();

      virtual void end_app_app();


      virtual bool is_user_service_running();

      //virtual string get_configuration(string strConfiguration);



      virtual void start_web_server();

      virtual void get_system_locale_schema(string & strLocale, string & strSchema);

      virtual void defer_show_debug_box();

      
      bool are_ca2_framework_shared_libraries_busy();

      



      virtual void on_receive(::aura::ipc::rx * prx, const char * pszMessage);

      virtual bool initialize_app_install();


   };


} // namespace install



#endif





