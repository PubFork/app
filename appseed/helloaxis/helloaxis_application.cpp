#include "framework.h"


int main_window(::helloaura::render * prender);


namespace helloaxis
{


   application::application()
   {

      m_strAppName = "app/helloaxis";
      m_strLibraryName = "app/helloaxis";
      m_strBaseSupportId = "ca2_flag";
      m_bLicense = false;

      m_etype = type_normal;

      m_strHelloMultiverseDefault = "Hello Axis!!";
      m_strAlternateHelloMultiverseDefault = "Hi Axis!!";

      m_strHelloMultiverse = m_strHelloMultiverseDefault;
      m_strAlternateHelloMultiverse = m_strAlternateHelloMultiverseDefault;

      m_iErrorAiFont = -1;

      m_bLoadAiFont = false;

      m_faceAi = NULL; // FT_Face m_faceAi;

      m_bMultiverseChat = true;



   }


   application::~application()
   {
   }


   bool application::initialize_application()
   {

      ::core::session * pcoression = m_pauraapp->m_pcoresession;

      if (!::axis::application::initialize_application())
      {

         return false;

      }

      string str = handler()->m_varTopicQuery["helloaxis"];

      if (str.has_char())
      {

         m_strHelloMultiverse = str;

      }

      m_dataid.m_id = m_dataid.m_id + ".local://";



      return true;

   }


   int32_t application::exit_application()
   {

      return ::axis::application::exit_application();

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

      m_bMultiverseChat = !handler()->m_varTopicQuery["no_hello_edit"].is_set();

      output_debug_string("\nfinished helloaxis::on_request");

      m_prender = new ::helloaxis::render(this);

      ::main_window(m_prender);

      System.post_quit();

   }






} // namespace helloaxis




extern "C"
::aura::library * app_helloaxis_get_new_library(::aura::application * papp)
{

   return new ::aura::single_application_library < ::helloaxis::application >(papp, "app/helloaxis");

}




