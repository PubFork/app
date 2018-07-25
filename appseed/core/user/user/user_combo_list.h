#pragma once


namespace user
{


   class combo_box;
   namespace wndfrm
   {
      namespace frame
      {
         class WorkSet;
      }
   }


   class CLASS_DECL_CORE combo_list :
      virtual public ::user::control
   {
   public:


      bool                                m_bMovingComboBox;
      bool                                m_bComboList;
      combo_box *                         m_pcombo;
      index                               m_iHover;
      int                                 m_iBorder;
      //::draw2d::font_sp                   m_spfont;

      ::user::interaction *               m_puiDeactivateTogether;
      ::user::wndfrm::frame::WorkSet *    m_puiDeactivateTogetherSet;


      combo_list();
      combo_list(::aura::application * papp);
      virtual ~combo_list();


      virtual void install_message_routing(::message::sender * psender) override;

      virtual void _001OnDraw(::draw2d::graphics * pgraphics) override;

      //virtual void _001OnDrawVerisimple(::draw2d::graphics * pgraphics);
      //virtual void _001OnDrawSimply(::draw2d::graphics * pgraphics);

      //virtual void _002OnDrawVerisimple(::draw2d::graphics * pgraphics);
      virtual void _001OnDrawComboList(::draw2d::graphics * pgraphics);

      virtual void query_full_size(LPSIZE lpsize);

      virtual int32_t _001GetItemHeight() const;

      bool pre_create_window(::user::create_struct & cs) override;


      using ::user::control::GetClientRect;
      virtual bool GetClientRect(RECT64 * lprect) override;


      DECL_GEN_SIGNAL(_001OnShowWindow);
      DECL_GEN_SIGNAL(_001OnSetFocus);
      DECL_GEN_SIGNAL(_001OnKillFocus);
      DECL_GEN_SIGNAL(_001OnClose);
      DECL_GEN_SIGNAL(_001OnActivate);
      DECL_GEN_SIGNAL(_001OnMouseActivate);
      DECL_GEN_SIGNAL(_001OnKeyDown);
      DECL_GEN_SIGNAL(_001OnKeyUp);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnMButtonDown);
      DECL_GEN_SIGNAL(_001OnRButtonDown);
      DECL_GEN_SIGNAL(_001OnMouseMove);


      virtual index hit_test(point pt, e_element & eelement) override;


      virtual bool keyboard_focus_is_focusable() override;
      virtual bool keyboard_focus_OnKillFocus() override;


      virtual bool ShowWindow(int nCmdShow) override;

      virtual bool has_pending_graphical_update() override;


      void on_drop_down(rect rectWindow, size sizeFull);


      //virtual bool get_font(::draw2d::font_sp & spfont, e_font efont, ::user::interaction * pui) override;


   };


} //  namespace user



