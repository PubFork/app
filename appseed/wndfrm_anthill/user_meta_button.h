#pragma once


namespace user
{


   class CLASS_DECL_APP_WNDFRM_ANTHILL meta_button :
      virtual public ::user::wndfrm::frame::control_box_button
   {
   public:


      ::draw2d::region_sp                 m_spregion;
      ::draw2d::pen_sp                    m_pen;
      ::draw2d::brush_sp                  m_brush;


      meta_button(::aura::application * papp);
      virtual ~meta_button();


      virtual index hit_test(point point, ::user::e_element & eelement) override;

      virtual void _001OnNcDraw(::draw2d::graphics * pgraphics) override;
      virtual void _001OnDraw(::draw2d::graphics * pgraphics)override;

      virtual void install_message_routing(::message::sender *pinterface) override;

      virtual void _001OnClip(::draw2d::graphics * pgraphics) override;

      DECL_GEN_SIGNAL(_001OnShowWindow);
      virtual void on_layout() override;



      virtual bool keyboard_focus_is_focusable() override;

   };



} // namespace user




