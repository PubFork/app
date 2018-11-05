//
//  sockets_ssl_context.hpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 06/01/18.
//
#pragma once

#include <openssl/ssl.h>

#include "sockets_ssl_client_context.h"

namespace sockets
{



   class CLASS_DECL_AURA ssl_context
   {
   public:


      int m_iSslCtxRetry;

      sp(ssl_client_context)  m_pclientcontext;
      SSL *m_ssl; ///< ssl 'socket'
      BIO *m_sbio; ///< ssl bio


      ssl_context();
      ~ssl_context();

   };

} // namespace sockets

