#include "framework.h" // from "base/user/user.h"
//#include "base/user/user.h"


namespace user
{


   control_event::control_event()
   {

      m_bOk          = true;

      m_bRet         = false;

      m_pmessage     = NULL;

      m_puie         = NULL;

      m_ptab         = NULL;

   }


   control_event::~control_event()
   {

   }

   ::user::form * control_event::get_form()
   {

      if (m_puie == NULL)
      {

         return NULL;

      }

      return m_puie->get_form();

   }

   void control_event::Nok()
   {

      m_bOk = false;

      m_bRet = true;

   }

   void control_event::Ret()
   {

      m_bRet = true;

   }

   void control_event::Ok()
   {

      m_bOk = true;

      m_bRet = true;

   }

   //impact * control_event::get_view()
   //{

   //   return dynamic_cast <::user::impact *> (m_puie);

   //}

   //document * control_event::get_document()
   //{

   //   impact * pimpact = get_view();

   //   if(pimpact == NULL)
   //      return NULL;

   //   return pimpact->get_document();

   //}

   //impact_system * control_event::get_impact_system()
   //{

   //   document * pdocument = get_document();

   //   if(pdocument == NULL)
   //      return NULL;

   //   return pdocument->get_document_template();

   //}

   //string control_event::get_impact_matter()
   //{

   //   impact_system * psystem = get_impact_system();

   //   if(psystem == NULL)
   //      return "";

   //   return psystem->m_strMatter;

   //}

} // namespace user




