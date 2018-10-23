#pragma once

#ifndef WM_USER
#define WM_USER 0x0400
#endif // WM_USER

#ifndef CLASS_DECL_AURA
#define CLASS_DECL_AURA
#endif // CLASS_DECL_AURA

enum e_message
{

   message_view_update = WM_USER + 18000,
   message_system,
   message_desk,
   message_display_change,
   message_property,
   message_event,
   message_system_event,
   message_simple_command,
   message_set_schema,
   message_post_user,
   message_update_notify_icon,

};




enum e_system_message
{

   system_message_none,
   system_message_command,
   system_message_user,
   system_message_meta,
   system_message_pred,
   system_message_runnable,
   system_message_register_dependent_thread,
   system_message_unregister_dependent_thread,

};


enum e_system_event
{

   system_event_none,
   system_event_wallpaper_change,

};


CLASS_DECL_AURA void c_post_system_event(e_system_event eevent, void * pparam = 0);



