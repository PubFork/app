#include "framework.h"


namespace user
{


   form_callback::form_callback()
   {
      m_pmapform = new ::user::map_form_window;
   }


   form_callback::~form_callback()
   {

      auto * ppair = m_pmapform->PGetFirstAssoc();

      while(ppair != NULL)
      {

         ppair->m_element2->DestroyWindow();

         ppair = m_pmapform->PGetNextAssoc(ppair);

      }

      ::aura::del(m_pmapform);

   }

   void form_callback::on_update(::user::impact * pform,sp(::user::impact) pSender,LPARAM lHint,object* phint)
   {
      UNREFERENCED_PARAMETER(pform);
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(lHint);
      UNREFERENCED_PARAMETER(phint);
   }


   void form_callback::on_control_event(::user::control_event * pevent)
   {

      UNREFERENCED_PARAMETER(pevent);

   }


   void form_callback::OnUser123(WPARAM wparam,LPARAM lparam)
   {
      UNREFERENCED_PARAMETER(wparam);
      UNREFERENCED_PARAMETER(lparam);
   }

   void form_callback::OnBeforeNavigate2(::html::data * pdata,var & varFile,uint32_t nFlags,const char * lpszTargetFrameName,byte_array& baPostedData,const char * lpszHeaders,bool* pbCancel)
   {
      UNREFERENCED_PARAMETER(pdata);
      UNREFERENCED_PARAMETER(varFile);
      UNREFERENCED_PARAMETER(nFlags);
      UNREFERENCED_PARAMETER(lpszTargetFrameName);
      UNREFERENCED_PARAMETER(baPostedData);
      UNREFERENCED_PARAMETER(lpszHeaders);
      UNREFERENCED_PARAMETER(pbCancel);
   }

   void form_callback::_001InitializeFormPreData(::user::form * pform)
   {
      UNREFERENCED_PARAMETER(pform);
   }


   form_control * form_callback::get_form_control(const string & strId)
   {

      return m_pmapform->operator[](strId);

   }

   ::user::document * form_callback::get_form_document(const string & strId)
   {

      auto passoc = m_pmapform->PLookup(strId);

      if(passoc == NULL)
         return NULL;

      sp(::user::impact) pview = passoc->m_element2;

      if(pview.is_null())
         return NULL;

      return pview->get_document();

   }



} // namespace user

