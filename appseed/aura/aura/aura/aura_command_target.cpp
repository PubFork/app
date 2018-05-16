#include "framework.h"


command_target::command_target()
{

   CommonConstruct();

}


command_target::command_target(::aura::application * papp)
   : object(papp)
{

   CommonConstruct();

}


void command_target::CommonConstruct()
{

}


command_target::~command_target()
{

}


bool command_target::handle(::user::command * pcommand)
{

   return pcommand->handle(this);

}


void command_target::BeginWaitCursor()
{
   Session.DoWaitCursor(1);
}
void command_target::EndWaitCursor()
{
   Session.DoWaitCursor(-1);
}
void command_target::RestoreWaitCursor()
{
   Session.DoWaitCursor(0);
}



void command_target::_001SendCommand(::user::command * pcommand)
{

   pcommand->m_pcommandtargetSource = this;

   {

      SRESTORE(pcommand->m_id.m_emessagetype, ::message::type_command);

      route_command_message(pcommand);

   }

}


void command_target::_001SendCommandProbe(::user::command * pcommand)
{

   pcommand->m_pcommandtargetSource = this;

   {

      SRESTORE(pcommand->m_id.m_emessagetype, ::message::type_command_probe);

      route_command_message(pcommand);

   }

}


void command_target::route_command_message(::user::command * pcommand)
{


   if (pcommand->m_id.m_emessagetype == ::message::type_command)
   {

      pcommand->m_bHasCommandHandler = has_command_handler(pcommand);

      on_command_probe(pcommand);

      if (!pcommand->m_bEnableChanged
            && !pcommand->m_bRadioChanged
            && pcommand->m_echeck == check::undefined
            && !pcommand->m_bHasCommandHandler)
      {

         return;

      }

      on_command(pcommand);

   }
   else if (pcommand->m_id.m_emessagetype == ::message::type_command_probe)
   {

      pcommand->m_bHasCommandHandler = has_command_handler(pcommand);

      on_command_probe(pcommand);

   }
   else if (pcommand->m_id.m_emessagetype == ::message::type_has_command_handler)
   {

      pcommand->m_bHasCommandHandler = has_command_handler(pcommand);

   }
   else
   {

      _throw(not_implemented(get_app()));

   }

}


void command_target::on_command(::user::command * pcommand)
{

   {

      SRESTORE(pcommand->m_id.m_emessagetype, ::message::type_command);

      route_message(pcommand);

   }

}


bool command_target::has_command_handler(::user::command * pcommand)
{

   synch_lock sl(m_pmutexIdRoute);

   SRESTORE(pcommand->m_id.m_emessagetype, ::message::type_command);

   if (m_idaHandledCommands.contains(pcommand->m_id))
   {

      return true;

   }

   return m_idroute[pcommand->m_id].has_elements();

}


void command_target::on_command_probe(::user::command * pcommand)
{

   {

      SRESTORE(pcommand->m_id.m_emessagetype, ::message::type_command_probe);

      route_message(pcommand);

      pcommand->m_bHasCommandHandler = has_command_handler(pcommand);

      pcommand->m_bRet =
      pcommand->m_bEnableChanged
      || pcommand->m_bRadioChanged
      || pcommand->m_echeck != check::undefined;

   }

}




void command_target::install_message_routing(::message::sender * psender)
{

   UNREFERENCED_PARAMETER(psender);

}








































