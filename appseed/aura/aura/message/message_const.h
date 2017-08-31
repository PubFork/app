#pragma once

enum e_simple_command
{

   simple_command_none,
   simple_command_load_window_rect,
   simple_command_update_frame_title,
   simple_command_set_edit_file,
   simple_command_layout,
   simple_command_full_screen

};


namespace message
{


   enum e_type
   {

      type_null,
      type_message,
      type_id,
      type_command,
      type_command_probe,
      type_application,
      type_http,
      type_html,
      type_language,
      type_reflect_id,
      type_user,
      type_attribute,
      type_user_simple_command,


   };


} // namespace message





