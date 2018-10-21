#pragma once


namespace user
{

   class tab_pane;
   class tab_drop_target_window;
   class single_document_template;


   class CLASS_DECL_CORE tab_view :
      virtual public ::user::impact,
      virtual public ::user::tab,
      virtual public ::user::tab_callback,
      virtual public ::user::view_creator
   {
   public:


      sp(tab_drop_target_window)             m_pdroptargetwindow;
      ::user::view_creator_data *            m_pviewdata;
      ::user::view_creator_data *            m_pviewdataOld;
      ::user::view_creator *                 m_pviewcreator;
      bool                                   m_bCloseDocumentIfNoTabs;



      tab_view(::aura::application * papp);
      virtual ~tab_view();


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;


      virtual void install_message_routing(::message::sender * pinterface) override;


      DECL_GEN_SIGNAL(_001OnMenuMessage);
      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnSetFocus);


      virtual void on_change_pane_count(::array < ::user::tab_pane * > array = ::array < ::user::tab_pane * >()) override;


      virtual id get_view_id() override;

      virtual ::user::interaction * get_view_uie() override;
      virtual ::user::view_creator_data * get_view_creator_data();
      virtual ::user::document * get_view_document() override;

      void _000OnDraw(::draw2d::graphics * pgraphics) override;

      void _001OnDropTab(index iPane, e_position eposition) override;

      ::user::interaction * _001GetTabWnd(int32_t iTab);

      void route_command_message(::user::command * pcommand) override;


      virtual void set_view_creator(::user::view_creator * pview);
      virtual ::user::view_creator * get_view_creator();


      virtual void _001DropTargetWindowInitialize(::user::tab * pinterface) override;
      virtual void _001DropTargetWindowRelay(::user::tab * pinterface) override;
      virtual void _001DropTargetWindowFinalize(::user::tab * pinterface) override;

      virtual void rotate();

      virtual ::user::view_creator_data * get_impact(id id, bool bCallOnCreateView = true);
      virtual ::user::view_creator_data * get_impact(id id, LPCRECT lpcrectCreate, bool bCallOnCreateView = true);
      virtual ::user::view_creator_data * create_impact(id id);
      virtual ::user::view_creator_data * create_impact(id id, LPCRECT lpcrectCreate) override;
      virtual ::user::view_creator_data * create_impact(id id, ::user::frame_window * pframewindow);
      virtual ::user::view_creator_data * create_impact(id id, LPCRECT lpcrectCreate, ::user::frame_window * pframewindow) override;
      virtual ::index create_tab_by_id(id id) override;

      virtual void _001OnShowTab(::user::tab * ptab) override;
      virtual void on_show_view() override;
      virtual void on_stage_view() override;

      void _001OnTabClick(int32_t iTab);


      virtual void on_update(::user::impact * pSender, LPARAM lHint, object* pHint) override;
      virtual bool pre_create_window(::user::create_struct& cs) override;

      virtual void OnActivateView(bool bActivate, sp(impact) pActivateView, sp(impact) pDeactiveView) override;

      virtual void _001OnRemoveTab(class tab_pane * ptab) override;

   };


   class tab_drop_target_window :
      virtual public ::user::interaction
   {
   public:


      array < e_position >                   m_positiona;
      ::user::tab *                          m_ptab;
      index                                  m_iTab;


      tab_drop_target_window(::user::tab * ptab, index iTab);
      virtual ~tab_drop_target_window();


      //virtual bool get_translucency(::user::e_translucency & etranslucency, ::user::e_element eelement, style_context * pcontext) override;

      virtual void install_message_routing(::message::sender * pinterface) override;

      virtual void _001OnDraw(::draw2d::graphics * pgraphics) override;

      DECL_GEN_SIGNAL(_001OnLButtonUp);

      virtual bool has_pending_graphical_update() override;

   };

} // namespace user
