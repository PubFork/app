#include "framework.h" // from "aura/net/net_sockets.h"
#include "aura/net/net_sockets.h"


namespace sockets
{


   base_socket_handler::pool_socket::pool_socket(base_socket_handler& h, base_socket * src) :
      object(h.get_app()),
      base_socket(h),
      socket(h)
   {
      CopyConnection(src);
      SetIsClient();
   }

   base_socket_handler::pool_socket::~pool_socket()
   {

   }


   void base_socket_handler::pool_socket::OnRead()
   {
#ifdef DEBUG
      log("OnRead", 0, "data on hibernating socket", ::aura::log::level_fatal);
#endif
      SetCloseAndDelete();
      SetLost();
   }

   void base_socket_handler::pool_socket::OnOptions(int, int, int, SOCKET)
   {

   }


#ifdef DEBUG
   base_socket_handler::base_socket_handler(::aura::application * papp, logger * plogger) :
      ::object(papp),
      m_splogger(plogger)
   {

   }
#else
   base_socket_handler::base_socket_handler(::aura::application * papp) :
      ::object(papp)
   {

   }
#endif

   base_socket_handler::~base_socket_handler()
   {

   }

#ifdef DEBUG
   void base_socket_handler::set_logger(logger * plogger)
   {

      m_splogger = plogger;

   }

   void base_socket_handler::log(base_socket * psocket, const string & strUser, int iError,const string & strSystem, ::aura::log::e_level elevel)
   {

#ifdef ANDROID

      string strLog;

      strLog.Format("%s - %s [%d]", strUser, strSystem, iError);

      output_debug_string(strLog);

#endif

      if(m_splogger.is_null())
      {
         TRACE("%s - %s [%d]", strUser, strSystem, iError);
         return;
      }

      m_splogger->log(this, psocket, strUser, iError, strSystem, elevel);

   }
#endif


} // namespace sockets




