#pragma once


namespace userstack
{


   class view;


   class CLASS_DECL_SPHERE application :
      virtual public ::prompt::application
   {
   public:


      index                                                          m_iEdge;

      bool                                                           m_bShowPlatform;

      sp(::aura::application)                                            m_pappCurrent;
      string_map < sp(::aura::application) >               m_mapApplication;


      sp(::user::single_document_template)                         m_ptemplate_main;
      sp(::user::single_document_template)                         m_ptemplate_pane;

      pane_view *                                                    m_ppaneview;


      var                                                            m_varTopicFile;
      var                                                            m_varCurrentViewFile;

      bool                                                           m_bDrawCursor;

      string_map < ::user::wndfrm::interaction * >     m_mapUinteraction;


      application();
      virtual ~application();


      void construct();


      virtual bool init_instance() override;
      virtual void term_application() override;

      virtual bool bergedge_start() override;

      void OnFileManagerOpenFile(::filemanager::data * pdata, ::fs::item_array & itema);

      void load_string_table() override;

      virtual bool file_manager_open_file(::filemanager::data * pdata, ::fs::item_array & itema);

      void initialize_bergedge_application_interface();

      virtual void request_topic_file(var & varQuery);

      virtual void request_topic_file();

      virtual void check_topic_file_change();

      bool on_exclusive_instance_conflict(::EExclusiveInstance eexclusive) override;

      void launch_app(const char * psz);
      void install_app(const char * psz);

      virtual bool init1() override;

      virtual bool init() override;

      virtual bool os_native_bergedge_start() override;

      virtual void main() override;

      virtual bool on_unstall() override;

      virtual bool is_serviceable() override;

      virtual service_base * allocate_new_service() override;

      void on_request(::create * pcreate) override;

      sp(::aura::application) application_get(const char * pszAppId, bool bCreate = true, bool bSynch = true, application_bias * pbiasCreate = NULL);

      sp(::aura::application) get_current_application();

      virtual bool on_install() override;

      virtual void set_app_title(const char * pszType, const char * pszAppId, const char * pszTitle);

   };


} // namespace userstack



