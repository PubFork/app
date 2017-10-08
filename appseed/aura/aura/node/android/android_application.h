#pragma once


namespace android
{


   class CLASS_DECL_AURA application :
      virtual public ::aura::application
   {
      public:


         ::command::command            m_commandStartup;


         application(::aura::application * papp);
         virtual ~application();

         virtual HINSTANCE GetHinstance();
         bool _001OnDDECommand(const char * lpcsz);
         virtual void _001EnableShellOpen();
         ///virtual ::aura::document *  _001OpenDocumentFile(var varFile);
         virtual void _001OnFileNew();


         virtual string get_version();

         virtual bool Ex2OnAppInstall();
         virtual bool Ex2OnAppUninstall();

         virtual void TermThread(HINSTANCE hInstTerm);

         virtual void SetCurrentHandles();

         virtual bool process_command(::command::command * pdata);

         virtual bool process_initialize();
         virtual bool initialize1();
         virtual bool initialize2();
         virtual bool initialize3();
         virtual int32_t  exit_application() override;

         virtual bool win_init(::command::command * pdata);

         virtual void ShowWaitCursor(bool bShow = true);

         virtual void get_time(struct timeval *p);
         virtual void set_env_var(const string & var,const string & value);
         virtual IDTHREAD get_thread_id();
         string draw2d_get_default_library_name();


   };



} // namespace android






