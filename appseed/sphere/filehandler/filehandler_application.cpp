#include "framework.h"


namespace filehandler
{


   application::application()
   {

      m_ptemplateMenu   = NULL;
      m_ppaneview       = NULL;

   }


   application::~application()
   {
   }


   void application::construct()
   {

      m_strAppName         = "default_file_handler";
      m_strBaseSupportId   = "default_file_handler";
      m_strInstallToken    = "default_file_handler";
      m_bLicense           = false;

   }

   bool application::init_instance()
   {


      System.factory().creatable_small < pane_view >();
      System.factory().creatable_small < document >();
      System.factory().creatable_small < frame >();
      System.factory().creatable_small < view >();

      if(!::asphere::application::init_instance())
         return false;



      ::user::single_document_template* pdoctemplate = new ::user::single_document_template(
      this,
      "html/frame",
      System.type_info < document > (),
      System.type_info < frame > (),       // top level SDI frame::user::interaction_impl
      System.type_info < pane_view > ());
      add_document_template(pdoctemplate);
      m_ptemplateMenu = pdoctemplate;


      return TRUE;
   }


   void application::term_application()
   {

      try
      {

         ::asphere::application::term_application();

      }
      catch(...)
      {

      }

   }


   void application::on_request(::create * pcreate)
   {

      if(m_ppaneview == NULL)
      {

         m_ptemplateMenu->request_create(pcreate);

      }

      if(m_ppaneview != NULL && pcreate->m_spCommandLine->m_varFile.get_type() == var::type_string)
      {

         m_ppaneview->set_cur_tab_by_id("default_file_handler://" + pcreate->m_spCommandLine->m_varFile.get_string());

      }

   }






} // namespace filehandler




