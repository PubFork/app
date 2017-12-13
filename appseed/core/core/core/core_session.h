#pragma once

#define platform_parent session( )

namespace core
{


   class view;

   class session_docs;


   class CLASS_DECL_CORE session :
      virtual public ::core::application,
      virtual public ::base::session,
      virtual public ::filemanager::item_action
   {
   public:


      class run_application
      {
      public:
         run_application();
         index                   m_iEdge;
         string                  m_strApp;
         string                  m_strQuery;
         sp(::core::session)      m_pbergedgeParent;
         sp(::aura::application)   m_pauraapp;
         bool                    m_bMakeVisible;
         sp(::user::interaction) m_puiParent;
         property_set      m_setParameters;
      };



      class CLASS_DECL_CORE map :
         virtual public ::map < index, index, ::core::session *, ::core::session * >
      {
      };


      index                                              m_iEdge;

      sp(::filemanager::filemanager)                     m_pfilemanager;

      session_docs *                                     m_pdocs;
      //nature::database *                                 m_pdatabase;


      string_map < sp(::object) >                          m_mapUinteraction; // ::user::wndfrm::wndfrm

      sp(::object)                                       m_pobjectUserex;
      ::userex::userex *                                 m_puserex;

      ::visual::font_list_data *                         m_pfontlistdata;





      session(::aura::application * papp);
      virtual ~platform_parent;


      virtual int64_t add_ref() override
      {
         return ::object::add_ref();
      }
      virtual int64_t dec_ref() override
      {
         return ::object::dec_ref();
      }


      virtual void install_message_routing(::message::sender * psender) override;

      virtual bool process_initialize_userex();
      virtual bool initialize1_userex();
      virtual bool init2() override;
      bool init_application() override;
      bool on_initial_update();
      virtual void term_application() override;

      bool InitializeLocalDataCentral();

      virtual bool bergedge_start() override;

      void _001OnFileNew();

      virtual void _001OnCmdMsg(::user::command * pcommand) override;

      virtual ::user::document * userex_on_request(::create * pcreate);

      void OnFileManagerOpenFile(::filemanager::data * pdata, ::fs::item_array & itema);

      void load_string_table() override;

      virtual bool open_file(::filemanager::data * pdata, ::fs::item_array & itema) override;

      void initialize_bergedge_application_interface();

      //virtual bool create_bergedge(::create * pcreate);

      virtual void use_font_sel();

      virtual void on_app_request_bergedge_callback(::aura::application * papp);


      virtual void on_frame_window_drop_files(::user::interaction * pui, ::file::patha & patha);


      // semantics defined by application
      virtual void request_create(::create * pcreate) override;
      // main loosely coupled semantics
      // varFile   : empty, one file path, many file paths, one file object, one or more file objects to be opened
      // varQuery  : more ellaborated requests for the application - syntax and semantic defined by requested application

      virtual sp(::user::interaction) get_request_parent_ui(sp(::user::interaction) pinteraction, ::create * pcreate) override;

      virtual bool place(::user::main_frame * pmainframe, ::create * pcreate);

      virtual void request_topic_file(var & varQuery);

      virtual void request_topic_file();

      virtual void check_topic_file_change();

      inline ::filemanager::filemanager            & filemanager() { return *m_pfilemanager; }

      string filemanager_get_initial_browse_path();
      bool on_exclusive_instance_conflict(EExclusiveInstance eexclusive) override;

      void launch_app(const char * psz);
      void install_app(const char * psz);



      sp(::user::document)                  get_document();
      sp(::user::impact)                      get_view() override;
      sp(::user::document)                  get_platform();
      sp(::user::document)                    get_nature();


      inline ::userex::userex *               userex() { return m_puserex;  }


      virtual bool process_init() override;

      virtual bool init1() override;

      virtual bool init() override;

      virtual bool os_native_bergedge_start() override;

      virtual void main() override;

      virtual bool on_unstall() override;

      virtual bool is_serviceable() override;

      virtual service_base * allocate_new_service() override;

      void on_request(::create * pcreate) override;

      sp(::aura::application) get_current_application();

      virtual bool on_install() override;

      virtual void set_app_title(const char * pszAppId, const char * pszTitle);

      virtual sp(::core::session) get_session();

      virtual void term() override;

      virtual bool open_by_file_extension(const char * pszPathName, application_bias * pbiasCreate = NULL) override;
      virtual bool open_by_file_extension(::create * pcc) override;

      virtual bool is_session() override;

      virtual bool is_mouse_button_pressed(::user::e_mouse emouse);

      virtual bool is_remote_session();

      //virtual ::visual::cursor * get_cursor() override;
      virtual ::visual::cursor * get_default_cursor() override;

      virtual ::count   get_monitor_count() override;
      virtual bool      get_monitor_rect(index iMonitor,LPRECT lprect) override;


      virtual void register_bergedge_application(::aura::application * papp);
      virtual void unregister_bergedge_application(::aura::application * papp);

      virtual ::aura::application * application_get(const char * pszAppId, bool bCreate = true, bool bSynch = true, application_bias * pbiasCreate = NULL);

      virtual ::core::session *             query_bergedge();

      virtual void on_user_login(::fontopus::user * puser) override;

      virtual void _001OnDefaultTabPaneDrawTitle(::user::tab_pane & pane, ::user::tab * ptab, ::draw2d::graphics * pgraphics, LPCRECT lpcrect, ::draw2d::brush_sp & brushText) override;

      virtual stringa get_user_wallpaper();

      virtual ::user::interaction * create_menu_button(::aura::application * papp) override;

   };


} // namespace core



