#pragma once


namespace sockets
{


   class CLASS_DECL_AURA trace_logger :
   virtual public ::aura::log
   {
      public:


         virtual void sockets_log(base_socket_handler *, base_socket *, const string & strUser, int32_t err, const string & strSystem, ::aura::log::e_level elevel = ::aura::log::level_warning) override;


   };


} // namespace sockets




