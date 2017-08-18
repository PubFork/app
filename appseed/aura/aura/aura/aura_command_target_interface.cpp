#include "framework.h"


bool command_target_interface::_001SendCommand(id id)
{
   
   ::user::command msg(id);

   msg.m_pcommandtargetSource = this;
   
   return _001OnCmdMsg(&msg);

}


bool command_target_interface::_001SendUpdateCmdUi(command_ui * pcommandui)
{
   
   ::user::command msg(pcommandui);
   
   msg.m_pcommandtargetSource = this;

   return _001OnCmdMsg(&msg);

}


bool command_target_interface::_001OnCmdMsg(::user::command * pcommand)
{

   if(pcommand->m_etype == ::user::command::type_command)
   {

      probe_command_ui cmdui(get_app());

      cmdui.m_id = pcommand->m_id;

      if(on_simple_update(&cmdui))
      {
         if(!cmdui.m_bEnabled)
            return false;
      }

      if(on_simple_action(pcommand->m_id))
         return true;

   }
   else
   {

      if(on_simple_update(pcommand->m_pcommandui))
         return true;

      if(_001HasCommandHandler(pcommand->m_pcommandui->m_id))
      {
         pcommand->m_pcommandui->Enable();
         return true;
      }

   }

   return false;

}

command_target_interface::command_signalid::~command_signalid()
{
}

command_target_interface::command_signalrange::~command_signalrange()
{
}

command_target_interface::command_target_interface()
{
}

command_target_interface::command_target_interface(::aura::application * papp)
   : object(papp)
{
}

bool command_target_interface::on_simple_action(id id)
{
   
   ::dispatch::signal_item_ptr_array signalptra;

   get_command_signal_array(::user::command::type_command,signalptra,id);

   bool bOk = false;

   for(int32_t i = 0; i < signalptra.get_size(); i++)
   {

      ::user::command command(signalptra[i]->m_psignal);

      command.m_id = id;

      signalptra[i]->m_psignal->emit(&command);

      if (command.m_bRet)
      {

         bOk = true;

      }

   }

   return bOk;

}

bool command_target_interface::_001HasCommandHandler(id id)
{

   ::dispatch::signal_item_ptr_array signalptra;

   get_command_signal_array(::user::command::type_command,signalptra,id);

   return signalptra.get_size() > 0;

}


bool command_target_interface::on_simple_update(command_ui * pcommandui)
{
   
   ::dispatch::signal_item_ptr_array signalptra;
   
   get_command_signal_array(::user::command::type_command_ui,signalptra,pcommandui->m_id);
   
   bool bOk = false;
   
   for(int32_t i = 0; i < signalptra.get_size(); i++)
   {
      
      pcommandui->reset(signalptra[i]->m_psignal);
      
      signalptra[i]->m_psignal->emit(pcommandui);
      
      if(pcommandui->m_bRet)
      {
         
         bOk = true;
         
      }
      
   }
   
   return bOk;

}



void command_target_interface::get_command_signal_array(::user::command::e_type etype,::dispatch::signal_item_ptr_array & signalptra,id id)
{
   command_signalid signalid;
   signalid.m_id = id;
   // collect all signals with the specified command id (pszId)
   for(int32_t i = 0; i < m_signalidaCommand.get_size(); i++)
   {
      class signalid * pid = m_signalidaCommand[i];
      if(pid->matches(&signalid))
      {
         if(etype == ::user::command::type_command)
         {
            m_dispatchCommand.m_signala.GetSignalsById(signalptra,&signalid);
         }
         else if(etype == ::user::command::type_command_ui)
         {
            m_dispatchUpdateCmdUi.m_signala.GetSignalsById(signalptra,&signalid);
         }
         else
         {
            ASSERT(FALSE);
         }
      }
   }
}

void command_target_interface::install_message_handling(::message::dispatch * pdispatch)
{

   UNREFERENCED_PARAMETER(pdispatch);

}








































