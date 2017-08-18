#pragma once


class command_target_interface;


namespace user
{


   class CLASS_DECL_AURA command:
      public object
   {
   public:


      enum e_type
      {
         type_command,
         type_command_ui
      };

      ::command_target_interface *                 m_pcommandtargetSource;
      ::command_ui  *                              m_pcommandui;
      id                                           m_id;
      e_type                                       m_etype;
      ref_array < ::command_target >               m_commandtargetptraHandle;


      command();
      command(id id);
      command(::command_ui * pcommandui);


      bool handle(::command_target * pcommandtarget);
      bool is_handled(::command_target * pcommandtarget);


   };


} // namespace aura

















