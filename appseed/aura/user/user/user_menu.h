#pragma once


namespace user
{


   class menu_item;


   class CLASS_DECL_AURA menu :
      virtual public ::user::interaction
   {
   public:


      size                                   m_sizeMinimum;
      menu *                                 m_pmenuParent;
      sp(menu_item)                          m_pitem;
      ::user::interaction *                  m_puiParent;
      ::user::interaction *                  m_puiNotify;
      HMENU                                  m_hmenu;
      bool                                   m_bOwnItem;
      size                                   m_size;
      int32_t                                m_iCheckBoxSize;
      bool                                   m_bAutoDelete;
      int32_t                                m_iHeaderHeight;
      ::user::menu_item                      m_itemClose;
      id                                     m_idSubMenu;
      int32_t                                m_iHoverSubMenu;
      uint32_t                               m_dwOut;
      sp(menu)                               m_psubmenu;
      id                                     m_idTimerMenu;
      point                                  m_ptTrack;
      point                                  m_ptPositionHint;
      int                                    m_iFlags;
      bool                                   m_bPositionHint;
      bool                                   m_bInline;
      bool                                   m_bMenuOk;
      menu_item *                            m_pmenuitemSub;
      int_array                              m_iaColumnWidth;
      int_array                              m_iaColumnHeight;
      bool                                   m_bCloseButton;



      menu();
      menu(::aura::application * papp);
      menu(::aura::application * papp, ::user::menu_item * pitem);
      virtual ~menu();


      virtual size get_window_minimum_size();

      virtual int64_t add_ref() override
      {

         return ::object::add_ref();

      }

      virtual int64_t dec_ref() override
      {

         return ::object::dec_ref();

      }

      virtual ::user::interaction * get_target_window();

      ::user::menu_item * GetSubMenu(int32_t i);

      virtual void layout_menu(point pt);

      virtual void hint_flags(int iFlags);
      virtual void hint_position(point pt);
      virtual void hints(int iFlags, point pt);

      virtual bool create_menu(::user::interaction * puiNotify = NULL, ::user::interaction * puiParent = NULL);
      virtual bool create_inline_menu(::user::interaction * puiNotify = NULL, ::user::interaction * puiParent = NULL);
      virtual bool track_popup_menu(::user::interaction * puiNotify = NULL, ::user::interaction * puiParent = NULL);

      void _001OnTimer(::timer * ptimer) override;

      void _001OnDraw(::draw2d::graphics * pgraphics) override;

      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnDestroy);
      DECL_GEN_SIGNAL(_001OnNcActivate);
      DECL_GEN_SIGNAL(_001OnNcCalcSize);
      DECL_GEN_SIGNAL(_001OnEnable);
      DECL_GEN_SIGNAL(_001OnShowWindow);
      DECL_GEN_SIGNAL(_001OnClose);
      DECL_GEN_SIGNAL(_001OnMouseActivate);
      DECL_GEN_SIGNAL(_001OnActivate);
      DECL_GEN_SIGNAL(_001OnNcCreate);


      virtual void on_control_event(::user::control_event * pevent) override;

      bool pre_create_window(::user::create_struct& cs) override;

      virtual void install_message_routing(::message::sender * pinterface) override;

      sp(::user::menu_item) get_item();

      sp(::user::menu_item) get_item(::user::interaction * pui);

      //virtual bool get_color(COLORREF & cr,::user::e_color ecolor, style_context * pcontext) override;
      //virtual bool get_translucency(::user::e_translucency & etranslucency, ::user::e_element eelement, style_context * pcontext) override;
      virtual bool has_pending_graphical_update() override;

      virtual bool create_menu(const stringa & straCommand, const stringa & straCommandTitle);

      virtual void destroy_menu();

      virtual bool load_menu(::xml::node * pnode);

      virtual bool load_xml_menu(const char * pszMatter);

      virtual bool load_xml_string_menu(const char * pszString);

      virtual void update_command(menu_item * pitemParent);

      void calc_size(menu_item * pitem, ::draw2d::graphics * pgraphics, int32_t & iMaxWidth, int32_t & iMaxHeight);
      void layout_buttons(menu_item * pitem, int32_t iMaxWidth, LPRECT lprect, LPCRECT lpcrectBound);


      virtual void defer_close();

      virtual ::user::menu_interaction * create_menu_button(::user::menu_item * pitem) override;


   };


} // namespace user



