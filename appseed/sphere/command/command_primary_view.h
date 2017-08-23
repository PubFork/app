#pragma once


namespace prompt
{


   class CLASS_DECL_SPHERE primary_view :
      public ::user::show < ::user::plain_edit >
   {
   public:


      typedef ::user::show <  ::user::plain_edit > BASE;


      strsize m_iCompromised;


      primary_view(::aura::application * papp);


      virtual void install_message_routing(::message::sender * pinterface);


      virtual void _001OnAfterChangeText(::action::context actioncontext);
      void on_update(::user::impact * pSender, LPARAM lHint, ::object* phint);


      DECL_GEN_SIGNAL(_001OnUpdateEditCopy);
      DECL_GEN_SIGNAL(_001OnEditCopy);
      DECL_GEN_SIGNAL(_001OnUpdateEditPaste);
      DECL_GEN_SIGNAL(_001OnEditPaste);
	   DECL_GEN_SIGNAL(_001OnContextMenu);


   };


} // namespace prompt



