#pragma once


class CLASS_DECL_CORE simple_tree_view :
   virtual public ::user::impact,
   virtual public ::user::tree
{
public:

   
   simple_tree_view(::aura::application * papp);   
   virtual ~simple_tree_view();

   virtual void install_message_routing(::message::sender * pinterface) override;


   DECL_GEN_SIGNAL(_001OnCreate);

   virtual void on_update(::user::impact * pSender,LPARAM lHint,::object* pHint) override;
   

   virtual void assert_valid() const override;
   virtual void dump(dump_context & dumpcontext) const override;


};
