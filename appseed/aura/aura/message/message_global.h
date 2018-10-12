#pragma once


enum e_message
{

   message_view_update = WM_USER + 18000,
   message_system,
   message_desk,
   message_display_change,
   message_property,
   message_event,
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
   system_message_register_dependent_thread,
   system_message_unregister_dependent_thread,

};




