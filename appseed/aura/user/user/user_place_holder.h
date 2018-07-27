#pragma once


namespace user
{


   class place_holder_container;


   class CLASS_DECL_AURA place_holder :
      virtual public interaction
   {
   public:


      //interaction_spa  m_uiptraHold;


      place_holder(::aura::application * papp);
      virtual ~place_holder();


      sp(place_holder) create_shadow_clone();


      virtual bool create_window(const RECT & rect, ::user::place_holder_container * pcontainer,id id);

      virtual void install_message_routing(::message::sender * psender) override;

      virtual bool can_merge(::user::interaction * pui) override;
      virtual bool merge(::user::interaction * pui) override;
      virtual bool hold(::user::interaction * pui);
      virtual bool unhold(::user::interaction * pui);
      virtual bool is_holding(::user::interaction * pui);

      virtual void on_remove_child(::user::interaction * pui) override;
      virtual void on_hide_child(::user::interaction * pui) override;

      virtual void _001DrawThis(::draw2d::graphics * pgraphics) override;
      virtual void _001OnDraw(::draw2d::graphics * pgraphics) override;
      virtual void _001OnNcDraw(::draw2d::graphics * pgraphics) override;

      DECL_GEN_SIGNAL(_001OnShowWindow);

      virtual void on_layout() override;

      ::user::interaction * get_hold();

      virtual bool is_place_holder() override;

      virtual bool _001IsBackgroundBypass();

      virtual void route_command_message(::user::command * pcommand) override;


   };

   class CLASS_DECL_AURA place_holder_ptra :
      virtual public spa(place_holder)
   {
   public:

      int32_t hold(::user::interaction * pui);
      int32_t unhold(::user::interaction * pui);

   };

} // namespace user
