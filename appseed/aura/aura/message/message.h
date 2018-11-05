#pragma once


namespace message
{

   class message;
   class sender;
   class receiver;

} // namespace message


#define DECL_GEN_SIGNAL(function) void function(::message::message * pobj)


#include "message_const.h"
#include "message_id.h"
#include "message_receiver.h"
#include "message_route.h"
#include "message_message.h"
#include "message_definition.h"
#include "message_sender.h"
#include "message_base.h"
#include "message_simple_command.h"
#include "message.inl"
#include "message_listener_smart_pointer_array.h"


#ifdef WINDOWSEX

#define MESSAGE MSG
#define LPMESSAGE LPMSG

#endif

namespace message
{


   CLASS_DECL_AURA bool is_idle_message(::message::message * pobj);


   CLASS_DECL_AURA bool is_idle_message(MESSAGE* pMsg);


} // namespace message

