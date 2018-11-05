#pragma once


namespace userex
{


   class CLASS_DECL_CORE font_view :
      virtual public ::user::split_view
   {
   public:


      top_view *                    m_ptopview;
      ::user::font_list_view *      m_pview;


      font_view(::aura::application * papp);
      virtual ~font_view();


      virtual void install_message_routing(::message::sender * psender) override;

      virtual void assert_valid() const override;

      virtual void dump(dump_context & dumpcontext) const override;

      void on_create_views() override;

      virtual void on_update(::user::impact * pSender, LPARAM lHint, object* pHint) override;

      virtual void on_control_event(::user::control_event * pevent) override;

      virtual void on_layout() override;

      DECL_GEN_SIGNAL(_001OnCreate);

   };


} // namespace userex





