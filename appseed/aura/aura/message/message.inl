#pragma once


#define MSG_TYPE_LINK(emessagetype, psender, preceiver, phandler) \
   psender->add_route(preceiver, phandler, ::message::id((::message::e_type)(emessagetype)))

#define IGUI_MSG_LINK(int_message, psender, preceiver, phandler) \
   psender->add_route(preceiver, phandler, ::message::id(::id((int_ptr) (int_message)), ::message::type_message))

/*

#define USER_MESSAGE_LINK(emessageenum, psender, preceiver, phandler) \
   IGUI_MSG_LINK(::message::emessageenum, psender, preceiver, phandler)

*/

#define SCAST_MSG(tcast) \
   ::message::tcast * p##tcast = dynamic_cast < ::message::tcast * > (pmessage);



