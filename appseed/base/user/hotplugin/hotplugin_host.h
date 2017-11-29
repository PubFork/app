#pragma once


#ifdef 


namespace hotplugin
{

   
   class CLASS_DECL_BASE host :
      virtual public plugin
   {
   public:


      ::hotplugin::composer *       m_pbasecomposer;
      plugin *                      m_pplugin;
      memory           m_memory;
      double                        m_dProgressRate;
      bool                          m_bShowProgress;


      bool                          m_bCa2InstallationReady;
      // this flag is only set if spaadmin is installing ca files while npca2 is *started*
      // it isn't set when npca2 is already running and spaadmin starts, may be only in the case above, when npca2 *restarts*.
      // this enables spaadmin to install ca files to ca folder, because npca2 would not use any ca shared libraries.
      bool                          m_bRunningSpaAdmin;


      mutex                         m_mutexSystem;

      ::draw2d::dib_sp              m_dib;

      rect                          m_rect;
      rect                          m_rectClient;
      rect                          m_rectWindow;

      bool                          m_bHostStarterStart;



      host();
      virtual ~host();


      virtual void * get_system();
      //virtual void set_system(void * pvoidSystem);


      virtual void   redraw() override;

      // host should implement
      virtual bool         open_link(const string & strLink,const string & pszTarget) override;
      virtual bool         reload_plugin() override;

      // Host location is not the updated url - if there is a way to update the url and 
      // maintain the same plugin instance, what would lead to an out-of-date location url.
      // It is the location url of the page that hosts the plugin when the plugin was created.
      virtual string     get_host_location_url() override;

      virtual void         post_message(UINT uiMessage, WPARAM wparam, LPARAM lparam) override;
      virtual oswindow         get_host_window() override;


      using ::hotplugin::plugin::GetWindowRect;
      virtual bool GetWindowRect(RECT64 * prect) override;

      using ::hotplugin::plugin::GetClientRect;
      virtual bool GetClientRect(RECT64 * lprect) override;

      virtual bool hotplugin_host_begin();
      virtual bool hotplugin_host_is_initialized();
      virtual bool hotplugin_host_initialize();


      virtual void hotplugin_host_on_write();


      virtual void   set_memory(void * puchMemory, ::count c) override;
      virtual void   append_memory(void * puchMemory, ::count c) override;
      virtual ::count get_memory_length() override;
      virtual ::count read_memory(void * puchMemory, ::count c) override;
      virtual void   free_memory() override;
      //static_function  void   free_memory(byte ** ppuchMemory);


      virtual void set_ready() override;
      virtual void on_ready() override;


      virtual bool plugin_initialize() override;
      virtual bool plugin_finalize() override;


      virtual void start_plugin() override;

      virtual int32_t  start_ca2_system() override;

      virtual void on_paint(::draw2d::graphics * pgraphics, const RECT & lprect) override;

      virtual int32_t start_app_install(const char * pszCommandLine);

      static_function int32_t start_app_install(const char * pszCommandLine,::aura::application * papp,host * phost, plugin * pplugin = NULL);

      static_function int32_t host_starter_start_sync(const char * pszCommandLine,::aura::application * papp,host * phost,plugin * pplugin = NULL);

      virtual void deferred_prodevian_redraw() override;

      virtual void start_ca2() override;

      virtual void set_progress_rate(double dRate) override;

      virtual double get_progress_rate() override;

      virtual void set_ca2_installation_ready(bool bReady = true) override;

      virtual bool is_ca2_installation_ready();

      virtual void set_status(const char * pszStatus) override;

      virtual void set_bitmap(::draw2d::graphics * pdib, const RECT & lprect);

      virtual void paint_bitmap(::draw2d::graphics * pdib,const RECT & lprect);

      virtual void blend_bitmap(::draw2d::graphics * pdib,const RECT & lprect);

      virtual void translate_mouse_message(int * px, int * py) override;

      //virtual bool ShowWindow(int nCmdShow);
      //virtual bool DestroyWindow();

      virtual void message_handler(::message::base * pbase) override;
      virtual void plugin_message_handler(UINT message,WPARAM wparam,LPARAM lparam, bool bEnsureTx) override;
      virtual void plugin_message_handler(MESSAGE * pmsg, bool bEnsureTx) override;


      using ::hotplugin::plugin::SetWindowPos;
      virtual bool SetWindowPos(int_ptr z,int32_t x,int32_t y,int32_t cx,int32_t cy,UINT nFlags) override;


   };


} // namespace hotplugin


#endif


