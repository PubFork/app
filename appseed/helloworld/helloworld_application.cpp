#include "framework.h"


namespace helloworld
{


   application::application() :
      m_mutexAiFont(this)
   {

      m_ptemplateHelloWorldMain = NULL;
      m_ptemplateHelloWorldView = NULL;
      m_ptemplateHelloWorldSwitcher = NULL;

      m_strAppName = "app/helloworld";
      m_strLibraryName = "app/helloworld";
      m_strBaseSupportId = "ca2_flag";
      m_bLicense = false;

      m_etype = type_normal;

      m_strHelloWorldDefault = "Hello World!!";
      m_strAlternateHelloWorldDefault = "Hello!!";

      m_strHelloWorld = m_strHelloWorldDefault;
      m_strAlternateHelloWorld = m_strAlternateHelloWorldDefault;

      m_iErrorAiFont = -1;

      m_bLoadAiFont = false;

      m_faceAi = NULL; // FT_Face m_faceAi;

      m_bWorldChat = true;



   }


   application::~application()
   {
   }


   bool application::init_instance()
   {

      ::core::session * pcoression = m_papp->m_psession;

      pcoression->use_font_sel();

      System.factory().creatable_small < ::helloworld::document >();
      System.factory().creatable_small < ::helloworld::frame >();
      System.factory().creatable_small < ::helloworld::main_frame >();
      System.factory().creatable_small < ::user::button_view >();
      System.factory().creatable_small < ::helloworld::view >();
      System.factory().creatable_small < ::helloworld::main_view >();
      System.factory().creatable_small < ::helloworld::switcher_view >();
      System.factory().creatable_small < ::helloworld::pane_view >();

      if (!::core::application::init_instance())
      {

         return false;

      }

      string str = handler()->m_varTopicQuery["helloworld"];

      if (str.has_char())
      {

         m_strHelloWorld = str;

      }

      set_local_data_key_modifier();

      ::user::single_document_template* pDocTemplate;


      pDocTemplate = canew(::user::single_document_template(
                              this,
                              "main",
                              System.type_info < document >(),
                              System.type_info < main_frame >(),
                              System.type_info < pane_view >()));
      m_ptemplateHelloWorldMain = pDocTemplate;
      add_document_template(pDocTemplate);


      pDocTemplate = canew(::user::single_document_template(
                              this,
                              "main",
                              System.type_info < document >(),
                              System.type_info < frame >(),
                              System.type_info < main_view >()));
      m_ptemplateHelloWorldView = pDocTemplate;
      add_document_template(pDocTemplate);


      pDocTemplate = canew(::user::single_document_template(
                              this,
                              "switcher",
                              System.type_info < document >(),
                              System.type_info < frame >(),
                              System.type_info < switcher_view >()));
      m_ptemplateHelloWorldSwitcher = pDocTemplate;
      add_document_template(pDocTemplate);


      return true;

   }


   int32_t application::exit_application()
   {

      return ::core::application::exit_application();

   }


   void application::on_request(::create * pcreate)
   {

#if 0

#ifdef DEBUG

      output_debug_string("DEBUG build? (basis)");

      ASSERT(FALSE);

#else

      output_debug_string("RELEASE build? (stage)");

      ASSERT(FALSE);

#endif

#endif

      m_bWorldChat = !handler()->m_varTopicQuery["no_hello_edit"].is_set();

      if (m_ptemplateHelloWorldMain->get_document_count() == 0)
      {

         m_ptemplateHelloWorldMain->request_create(pcreate);

      }

      if (pcreate->m_spCommandLine->m_varFile.has_char())
      {

         m_ptemplateHelloWorldView->request_create(pcreate);

      }

      if (handler()->m_varTopicQuery["wfi_maximize"].is_set())
      {

         pcreate->m_spCommandLine->m_varQuery["document"].cast < document >()->get_typed_view < ::userex::pane_tab_view >()->GetTopLevelFrame()->_001WindowMaximize();

      }

      output_debug_string("\nfinished helloworld::on_request");

   }


   string application::preferred_userschema()
   {

      return "core";

   }


   int64_t application::add_ref()
   {

      return ::object::add_ref();

   }

   int64_t application::dec_ref()
   {

      return ::object::dec_ref();

   }


} // namespace helloworld




extern "C"
::aura::library * app_helloworld_get_new_library(::aura::application * papp)
{

   return new ::aura::single_application_library < ::helloworld::application >(papp, "app/helloworld");

}




