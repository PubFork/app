#pragma once


#include "aura/net/sockets/bsd/basic/sockets_socket_handler.h"


namespace netserver
{


   class CLASS_DECL_AURA socket_handler :
      virtual public ::sockets::socket_handler
   {
   public:


      socket_handler(::aura::application * papp);


   };


} // namespace netserver


