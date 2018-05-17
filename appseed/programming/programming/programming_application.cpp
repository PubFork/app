#include "framework.h"


namespace programming
{


   application::application() :
      m_semCompiler(this, MAX(1, ::get_processor_count()), MAX(1, ::get_processor_count()))
   {

      //

   }


   application::~application()
   {

   }


   void application::on_application_signal(::message::message * pobj)
   {

      SCAST_PTR(::aura::application_message, psignal, pobj);

      if (psignal->m_esignal == ::aura::application_message_process_init)
      {

      }
      else if (psignal->m_esignal == ::aura::application_message_init1)
      {

      }
      else  if (psignal->m_esignal == ::aura::application_message_term_instance)
      {

      }

   }


   void application::on_request(::create * pcreate)
   {


      if (pcreate->m_spCommandLine->m_varQuery.has_property("introj"))
      {

         ::introjection::compiler *  pcompiler = canew(::introjection::compiler(this));

         bool bNew;

         sp(::aura::library) lib = pcompiler->compile(::dir::system() / "config\\xmpp_resident\\room\\ca2@livecoding.tv\\xmpp_bot.cpp", bNew);

         if (lib->m_pca2library == NULL)
         {

            return;


         }

         sp(object) p = lib->create_object(get_app(), "plugin", this);

         if (p.is_null())
            return;

///         m_p = p.cast < plugin >();

      }



   }


} // namespace programming


#ifdef MACOS
int get_processor_count()
{
   return 1;
}
#endif





































