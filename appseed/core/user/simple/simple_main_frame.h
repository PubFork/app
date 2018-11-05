#pragma once


class CLASS_DECL_CORE simple_main_frame :
   virtual public simple_frame_window
{
public:


   bool           m_bPlacing;


   simple_main_frame(::aura::application * papp);
   virtual ~simple_main_frame();


   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;


   virtual void install_message_routing(::message::sender * pinterface);



   DECL_GEN_SIGNAL(_001OnCreate);


};
