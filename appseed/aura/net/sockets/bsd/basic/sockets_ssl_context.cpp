//
//  sockets_ssl_context.cpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 06/01/18.
//

#include "sockets_ssl_context.h"

namespace sockets
{
   
      ssl_context::ssl_context():
#ifdef HAVE_OPENSSL
      m_iSslCtxRetry(0)
      , m_ssl_ctx(NULL)
      , m_ssl_session(NULL)
      , m_ssl_method(NULL)
      , m_ssl(NULL)
      , m_sbio(NULL)
#endif

      {
         
      }
      
      
      ssl_context::~ssl_context()
      {
         
      }
   
} // namespace sockets

