#pragma once

#include "aura/net/sockets/bsd/basic/sockets_socket_handler.h"

#include "aura/net/ftp/ftp_output.h"


class ftpnet
{
public:




   string_map < sp(::ftp::output) > m_mapOutput;
   string_map < sp(::ftp::client_socket) > m_mapClient;
   ::sockets::socket_handler     m_sockethandler;



   ftpnet(::aura::application * papp) :
      m_sockethandler(papp)
   {


   }

   ~ftpnet()
   {


   }

};