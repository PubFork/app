#include "framework.h"



probe_command_ui::probe_command_ui(::aura::application * papp):
::command_ui(papp)
{

   m_bEnabled        = TRUE;  // assume it is enabled
   m_echeck          = ::check::undefined;
   m_bRadio          = false;
   m_bRadioChanged   = false;

}


void probe_command_ui::Enable(bool bOn,::action::context)
{

   m_bEnabled        = bOn;
   m_bEnableChanged  = true;

}


void probe_command_ui::_001SetCheck(bool bCheck,::action::context context)
{

   ::command_ui::_001SetCheck(bCheck,context);

}


void probe_command_ui::_001SetCheck(check::e_check echeck,::action::context)
{

   m_echeck = echeck;

}


void probe_command_ui::SetRadio(bool bOn,::action::context)
{

   m_bRadio = bOn;
   m_bRadioChanged = true;

}


void probe_command_ui::SetText(const char * lpszText,::action::context)
{

   m_strText = lpszText;

}



