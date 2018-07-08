#pragma once


namespace userex
{


   class CLASS_DECL_CORE color_view :
      virtual public ::user::impact
   {
   public:

      bool                             m_bLButtonPressed;
      ::user::plain_edit_view          m_editRed;
      ::user::plain_edit_view          m_editGreen;
      ::user::plain_edit_view          m_editBlue;
      ::user::plain_edit_view          m_editHex;

      ::draw2d::dib_sp                 m_dibTemplate;
      ::draw2d::dib_sp                 m_dib;
      ::draw2d::dib_sp                 m_dibLuminance;

      color::hls                       m_hls;

      rect                             m_rectColors;


      color_view(::aura::application * papp);
      virtual ~color_view();


      virtual void assert_valid() const;

      virtual void dump(dump_context & dumpcontext) const;

      virtual void install_message_routing(::message::sender * psender) override;

      virtual void on_update(::user::impact * pSender, LPARAM lHint, object* pHint);

      virtual void on_control_event(::user::control_event * pevent);

      virtual void _001OnDraw(::draw2d::graphics * pgraphics) override;

      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnMouseMove);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);

      virtual void on_layout() override;

      virtual void on_mouse(point pt);
      virtual void rebuild_luminance();

      virtual color get_color();
      virtual void set_COLORREF(COLORREF cr);

   };


} // namespace userex




