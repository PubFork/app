#pragma once


namespace message
{

   class message;
   class dispatch;
   class receiver;

} // namespace message


#define DECL_GEN_SIGNAL(function) void function(::message::message * pobj)


#include "message_const.h"
#include "message_id.h"
#include "message_route.h"
#include "message_message.h"
#include "message_definition.h"
#include "message_sender.h"
#include "message_receiver.h"
#include "message_base.h"
#include "message.inl"


namespace message
{




   CLASS_DECL_AURA bool is_idle_message(::message::message * pobj);


   CLASS_DECL_AURA bool is_idle_message(MESSAGE* pMsg);




} // namespace message





