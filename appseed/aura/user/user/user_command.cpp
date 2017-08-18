#include "framework.h"


namespace user
{


   command::command()
   {

      m_pcommandtargetSource        = NULL;
      m_etype                       = type_command;

   }


   command::command(id id)
   {

      m_pcommandtargetSource        = NULL;
      m_etype                       = type_command;
      m_id                          = id;

   }


   command::command(::command_ui * pcommandui)
   {

      m_pcommandtargetSource        = NULL;
      m_etype                       = type_command_ui;
      m_pcommandui                      = pcommandui;

   }


   bool command::handle(::command_target * pcommandtarget)
   {
      
      return m_commandtargetptraHandle.add_unique(pcommandtarget);
      
   }
   

   bool command::is_handled(::command_target * pcommandtarget)
   {
      
      return m_commandtargetptraHandle.contains(pcommandtarget);
      
   }


} // namespace aura








































