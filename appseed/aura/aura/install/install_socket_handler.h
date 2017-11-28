#pragma once


#include "aura/net/netserver/netserver_socket_handler.h"


namespace install
{


   class CLASS_DECL_AURA socket_handler :
      virtual public ::netserver::socket_handler
   {
   public:


      socket_handler(::aura::application * papp);


   };


} // namespace install



