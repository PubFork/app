#pragma once


namespace userfs
{


   class document;


   class CLASS_DECL_CORE main_view :
      public ::user::split_view
   {
   public:
         
      main_view(::aura::application * papp);
      void install_message_routing(::message::sender * pinterface);
      DECL_GEN_SIGNAL(_001OnCreate);
      void _001OnTimer(::timer * ptimer);


      ::user::document * get_document();

   };


} // namespace userfs



