#pragma once


namespace userex
{


   class CLASS_DECL_CORE top_edit_view :
      virtual public ::user::show < ::user::plain_edit >
   {
   public:


      top_view * m_ptopview;


      top_edit_view(::aura::application * papp);
      virtual ~top_edit_view();

      virtual void _001OnAfterChangeText(::action::context actioncontext) override;

      void on_update(::user::impact * pSender, LPARAM lHint, object* phint) override;

      virtual void install_message_routing(::message::sender * psender) override;

      DECL_GEN_SIGNAL(_001OnCreate);

      bool keyboard_focus_is_focusable() override;

      //virtual int64_t add_ref();

      //virtual int64_t dec_ref();

      bool IsWindowVisible() override;

   };


} // namespace userex




