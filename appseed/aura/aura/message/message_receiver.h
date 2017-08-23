#pragma once


namespace message
{


   class CLASS_DECL_AURA receiver :
      virtual public ::object
   {
   public:

      virtual void install_message_routing(::message::sender * psender);

   };


} // namespace message



