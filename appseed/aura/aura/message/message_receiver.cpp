#include "framework.h"


namespace message
{


   receiver::receiver()
   {

   }


   receiver::~receiver()
   {

      for (auto psender : m_sendera)
      {

         psender->remove_receiver(this);

      }

   }


   void receiver::install_message_routing(::message::sender * psender)
   {

   }


} // namespace message


