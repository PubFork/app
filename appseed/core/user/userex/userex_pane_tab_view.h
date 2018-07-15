#pragma once


namespace userex
{


   class pane_view;

   class CLASS_DECL_CORE pane_tab_view :
      virtual public ::user::tab_view,
      virtual public ::user::form_callback
   {
   public:

      id_map < sp(::html_document) >   m_mapForm;
      sp(pane_view)                    m_ppaneview;
      ::object *                       m_pfilemanager;
      ::object *                       m_pfilemanagerTabbed;
      sp(::user::document)             m_pdocAppOptions;
      font_view *                      m_pfontview;
      color_view *                     m_pcolorview;


      pane_tab_view(::aura::application * papp);
      virtual ~pane_tab_view();


      virtual void install_message_routing(::message::sender * psender) override;


      DECL_GEN_SIGNAL(_001OnCreate);

      
      virtual void _001OnRemoveTab(::user::tab_pane * ptab) override;

      virtual ::user::interaction * get_view_uie() override;

      virtual id get_view_id() override;

      virtual void on_show_view() override;

      virtual void defer_hide_tab_with_id_that_contains_preserve_current(string strIdPart);

      virtual void hide_tab_with_id_that_contains_preserve_current(string strIdPart);

      virtual bool on_prepare_view_creator_data(::user::view_creator_data * pcreatordata) override;

      virtual bool on_after_create_view_creator_data(::user::view_creator_data * pcreatordata) override;

      virtual void GetTabClientRect(LPRECT lprect) override;

      virtual bool on_hold(::user::interaction * pui, ::user::place_holder * pholder) override;

      virtual ::index create_tab_by_id(id id) override;

      virtual void on_create_view(::user::view_creator_data * pcreatordata) override;

      virtual ::filemanager::manager & filemanager_manager();

      virtual ::filemanager::manager & tabbed_filemanager_manager();

      virtual void FileManagerSaveAs(::user::document * pdocument);

      virtual void TabbedFileManagerSaveAs(::user::document * pdocument);

      virtual void _001OnTabClose(int32_t iTab);

      virtual string get_cred(const string & strRequestUrl, const RECT & rect, string & strUsername, string & strPassword, string strToken, string strTitle, bool bInteractive);

      virtual bool create_app_options(::user::view_creator_data * pcreatordata);

      virtual void on_update(::user::impact * pSender, LPARAM lHint, ::object* pHint) override;

      virtual void _001OnNcDraw(::draw2d::graphics * pgraphics) override;

      virtual void on_control_event(::user::control_event * pevent) override;

      virtual void prepare_form(id id, ::html_document * pdocument);

   };


} // namespace userex
