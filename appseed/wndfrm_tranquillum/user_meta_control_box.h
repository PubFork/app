#pragma once


class CLASS_DECL_APP_WNDFRM_TRANQUILLUM MetaControlBox :
   virtual public ::user::wndfrm::frame::control_box
{
public:


   MetaControlBox(::aura::application * papp);
   virtual ~MetaControlBox();


   virtual void _001OnNcDraw(::draw2d::graphics * pgraphics) override;
   virtual void _001OnDraw(::draw2d::graphics * pgraphics) override;

   virtual void install_message_routing(::message::sender *pinterface) override;


   DECL_GEN_SIGNAL(_001OnShowWindow);
   DECL_GEN_SIGNAL(_001OnLButtonDown);
   DECL_GEN_SIGNAL(_001OnLButtonUp);
   void _001OnTimer(::timer * ptimer) override;


};



