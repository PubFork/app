#include "framework.h"


namespace user
{


   command::command()
   {

      common_construct();

   }


   command::command(::message::sender * psender) :
      ::message::message(psender)
   {

      common_construct();

   }

   command::command(id id)
   {

      common_construct();
      m_etype                       = type_command;
      m_id.m_etype = ::message::type_command;
      m_id                          = id;
      m_bCheckChanged               = false;
      m_bRadioChanged               = false;

   }


   command::command(::command_ui * pcommandui)
   {

      m_pcommandui                  = NULL;
      m_pcommandtargetSource        = NULL;
      m_etype                       = type_command_ui;
      m_pcommandui                  = pcommandui;
      m_bCheckChanged               = false;
      m_bRadioChanged               = false;

   }

   void command::common_construct()
   {

      m_estate = state_none;
      m_pcommandtargetSource = NULL;
      m_pcommandui = NULL;
      m_iIndex = -1;
      m_iCount = -1;
      m_bEnabled = false;
      m_echeck = ::check::undefined;
      m_bRadio = false;
      m_bRadioChanged = false;
      m_pmenu = NULL;
      m_pmenuChild = NULL;
      m_pmenuParent = NULL;
      m_puiOther = NULL;
      m_bEnableChanged = false;
      m_bHasCommandHandler = false;

   }


   bool command::handle(::command_target * pcommandtarget)
   {
      
      return m_commandtargetptraHandle.add_unique(pcommandtarget);
      
   }
   

   bool command::is_handled(::command_target * pcommandtarget)
   {
      
      return m_commandtargetptraHandle.contains(pcommandtarget);
      
   }



   command::command()
   {

      m_ecommand = command_default;

   }

   command::command(const ::command::command & command)
   {

      operator       = (command);

   }


   command::command(::aura::application * papp) :
      ::object(papp)
   {

      m_ecommand = command_default;

   }

   command::command(::aura::application * papp, e_command ecommand) :
      ::object(papp)
   {

      m_ecommand = ecommand;

   }

   command::~command()
   {

   }


   var command::run()
   {

      return true;

   }


   void command::on_request(::create * pcreate)
   {

      UNREFERENCED_PARAMETER(pcreate);

   }


   string command::get_description()
   {

      return "this is a command that was not described";

   }

   ::command::command & command::operator = (const ::command::command & command)
   {

      if (this == &command)
      {

         return *this;

      }

      ::object::operator = (command);

      m_ecommand = command.m_ecommand;
      m_strCommandLine = command.m_strCommandLine;
      m_varFile = command.m_varFile;

      return *this;

   }


} // namespace user


