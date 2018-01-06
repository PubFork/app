#include "framework.h"


namespace user
{


   command::command(::aura::application * papp) :
      ::message::base(papp)
   {

      common_construct();

   }


   //command::command(::message::sender * psender) :
   //   ::message::message(psender)
   //{

   //   common_construct();

   //}

   command::command(id id)
   {

      common_construct();
      m_id.m_emessagetype           = ::message::type_command;
      //m_id.m_etype = ::message::type_command;
      m_id                          = id;
      //m_bCheckChanged               = false;
      m_bRadioChanged               = false;

   }


   //command::command(::user::command * pcommand)
   //{

   //   m_pcommand                  = NULL;
   //   m_pcommandtargetSource        = NULL;
   //   m_etype                       = type_::user::command;
   //   m_pcommand                  = pcommand;
   //   m_bCheckChanged               = false;
   //   m_bRadioChanged               = false;

   //}

   void command::common_construct()
   {

      //m_estate = state_none;
      m_pcommandtargetSource = NULL;
      //m_pcommand = NULL;
      m_iIndex = -1;
      m_iCount = -1;
      m_bEnable = false;
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



   //command::command()
   //{

   //   m_ecommand = command_default;

   //}

   //command::command(const ::command::command & command)
   //{

   //   operator       = (command);

   //}


   //command::command(::aura::application * papp) :
   //   ::object(papp)
   //{

   //   m_ecommand = command_default;

   //}

   //command::command(::aura::application * papp, e_command ecommand) :
   //   ::object(papp)
   //{

   //   m_ecommand = ecommand;

   //}

   //command::~command()
   //{

   //}


   //var command::run()
   //{

   //   return true;

   //}


   //void command::on_request(::create * pcreate)
   //{

   //   UNREFERENCED_PARAMETER(pcreate);

   //}


   //string command::get_description()
   //{

   //   return "this is a command that was not described";

   //}

   //::command::command & command::operator = (const ::command::command & command)
   //{

   //   if (this == &command)
   //   {

   //      return *this;

   //   }

   //   ::object::operator = (command);

   //   m_ecommand = command.m_ecommand;
   //   m_strCommandLine = command.m_strCommandLine;
   //   m_varFile = command.m_varFile;

   //   return *this;

   //}

   void command::Enable(bool bOn,::action::context actioncontext)
   {
   
      if(m_pmenu != NULL)
      {
   
         ENSURE(m_iIndex < m_iCount);
   
      }
      
      if(m_puiOther != NULL)
      {
   
         Application.enable_window(m_puiOther, bOn);
   
      }

      m_bEnable = bOn;
   
      m_bEnableChanged = true;
   
   }
   
   void command::_001SetCheck(bool bCheck,::action::context actioncontext)
   {
   
      _001SetCheck((::check::e_check) (bCheck ? ::check::checked : ::check::unchecked),actioncontext);
   
   }
   
   
   void command::_001SetCheck(::check::e_check nCheck,::action::context actioncontext)
   {
   
      if (m_pmenu != NULL)
      {

         ENSURE(m_iIndex < m_iCount);

      }

      if(m_puiOther != NULL)
      {
   
          Application.send_message(m_puiOther,BM_SETCHECK,nCheck);
   
      }

      m_echeck = nCheck;

   }
   
   
   void ::user::command::SetRadio(bool bOn,::action::context actioncontext)
   {
      
      _001SetCheck(bOn,actioncontext);

   }
   
   void ::user::command::SetText(const char * lpszText,::action::context actioncontext)
   {
      
      if (m_pmenu != NULL)
      {

         ENSURE(m_iIndex < m_iCount);

      }

      if (m_puiOther != NULL)
      {

         Application.set_window_text(m_puiOther, lpszText);

      }

      m_strText = lpszText;

   }

   
   void command::do_probe(command_target * ptarget)
   {

      if(m_id.is_empty())
         return;     // ignore invalid IDs
   
      ENSURE_VALID(ptarget);
   
      m_bEnableChanged  = false;

      m_bRadioChanged   = false;

      m_echeck          = ::check::undefined;

      ptarget->_001SendCommandProbe(this);
   
   }
   
   
   

} // namespace user


