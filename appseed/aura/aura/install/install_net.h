#pragma once


#include "install_socket.h"
#include "install_socket_handler.h"
#include "install_socket_thread.h"
#include "install_tool.h"
#include "install_bootstrap.h"

namespace install
{
   class net
   {
   public:

      net()
      {

         m_psockethandler = NULL;

      }

      ~net()
      {
         ::aura::del(m_psockethandler);
      }

      sp(::sockets::http_session)      m_phttpsession;
      ::sockets::socket_handler *      m_psockethandler;
      spa(::sockets::http_session)     m_httpsessionptra;


   };

   class install_net
   {
   public:

      install_net()
      {
         m_psockethandler = NULL;
      }
      ~install_net()
      {
         ::aura::del(m_psockethandler);
      }

      ::sockets::socket_handler *         m_psockethandler;
      spa(::sockets::http_session)        m_httpsessionptra;

   };
} // namespace install


