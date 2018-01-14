//
//  sockets_ssl_context.hpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 06/01/18.
//
#pragma once

#include <openssl/ssl.h>

namespace sockets
{
   
   class CLASS_DECL_AURA ssl_context
   {
   public:

      
      int m_iSslCtxRetry;

      SSL_CTX *m_ssl_ctx; ///< ssl context
      SSL_SESSION * m_ssl_session; ///< ssl session
      const SSL_METHOD * m_ssl_method; ///< ssl method
      SSL *m_ssl; ///< ssl 'socket'
      BIO *m_sbio; ///< ssl bio
      
      
      ssl_context();
      ~ssl_context();

   };
   
} // namespace sockets

