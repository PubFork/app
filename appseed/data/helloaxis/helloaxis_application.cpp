#include "framework.h"
int my_main(::aura::application * papp);

namespace helloaxis
{


   application::application() :
      m_mutexAiFont(this)
   {

      m_strAppName = "app/helloaxis";
      m_strLibraryName = "app/helloaxis";
      m_strBaseSupportId = "ca2_flag";
      m_bLicense = false;

      m_etype = type_normal;

      m_strHelloMultiverseDefault = "Hello Multiverse!!";
      m_strAlternateHelloMultiverseDefault = "Hello!!";

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


   bool application::init_instance()
   {

      ::core::session * pcoression = m_papp->m_psession;

      if (!::axis::application::init_instance())
      {

         return false;

      }

      string str = handler()->m_varTopicQuery["helloaxis"];

      if (str.has_char())
      {

         m_strHelloMultiverse = str;

      }

      set_local_data_key_modifier();



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

      fork([&]()
      {
         my_main(this);
      }
          );

   }





   int64_t application::add_ref()
   {

      return ::object::add_ref();

   }

   int64_t application::dec_ref()
   {

      return ::object::dec_ref();

   }

   void application::paint(HWND hwnd, HDC hdc)
   {
      ::draw2d::graphics_sp g(allocer());

      g->Attach(hdc);

      paint(hwnd, g);

   }

   void application::paint(HWND hwnd, ::draw2d::graphics * pgraphics)
   {
      rect rcClient;
      ::GetClientRect(hwnd, rcClient);
      ::draw2d::brush_sp br(allocer());

      br->create_solid(ARGB(255, 255, 0, 0));
      pgraphics->SelectObject(br);
      pgraphics->FillEllipse(rcClient);
   }

} // namespace helloaxis




extern "C"
::aura::library * app_helloaxis_get_new_library(::aura::application * papp)
{

   return new ::aura::single_application_library < ::helloaxis::application >(papp, "app/helloaxis");

}




