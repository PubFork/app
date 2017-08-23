#include "framework.h"


void command_target_interface::_001SendCommand(::user::command * pcommand)
{
   
   pcommand->m_pcommandtargetSource = this;

   pcommand->m_id.m_etype = ::message::type_command;
   
   _001OnCmdMsg(pcommand);

}


bool command_target_interface::_001SendUpdateCommand(::user::command * pcommand)
{
   
   pcommand->m_pcommandtargetSource = this;

   pcommand->m_id.m_etype = ::message::type_command;

   _001OnCmdMsg(pcommand);

}


void command_target_interface::_001OnCmdMsg(::user::command * pcommand)
{

   if(pcommand->m_id.m_etype == ::message::type_command)
   {

      if(on_simple_update(pcommand))
      {
         
         if (!pcommand->m_bEnabled)
         {

            return;

         }

      }

      if (on_simple_action(pcommand))
      {

         return;

      }

   }
   else if (pcommand->m_id.m_etype == ::message::type_command_update)
   {

      if (on_simple_update(pcommand))
      {

         return;

      }

      if (!pcommand->m_bEnableChanged)
      {
       
         if (_001HasCommandHandler(pcommand))
         {

            pcommand->m_bHasCommandHandler = true;

         }

      }

   }
   else
   {

      throw not_implemented(get_app());

   }

}


//command_target_interface::command_signalid::~command_signalid()
//{
//}
//
//command_target_interface::command_signalrange::~command_signalrange()
//{
//}

command_target_interface::command_target_interface()
{
}

command_target_interface::command_target_interface(::aura::application * papp)
   : object(papp)
{
}

void command_target_interface::on_simple_action(::user::command * pcommand)
{
   
   route_message(pcommand);

   //::dispatch::message::sender_item_ptr_array signalptra;

   //get_command_signal_array(::user::command::type_command,signalptra,id);

   //bool bOk = false;

   //for(int32_t i = 0; i < signalptra.get_size(); i++)
   //{

   //   ::user::command command(signalptra[i]->m_psignal);

   //   command.m_id = id;

   //   signalptra[i]->m_psignal->emit(&command);

   //   if (command.m_bRet)
   //   {

   //      bOk = true;

   //   }

   //}

   //return bOk;

}


bool command_target_interface::_001HasCommandHandler(::user::command * pcommand)
{

   synch_lock sl(m_pmutex);

   return m_idroute[pcommand->m_id].has_elements();

}


bool command_target_interface::on_simple_update(command_ui * pcommandui)
{
   
   ::dispatch::message::sender_item_ptr_array signalptra;
   
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



void command_target_interface::get_command_signal_array(::user::command::e_type etype,::dispatch::message::sender_item_ptr_array & signalptra,id id)
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

void command_target_interface::install_message_routing(::message::sender * psender)
{

   UNREFERENCED_PARAMETER(pdispatch);

}








































