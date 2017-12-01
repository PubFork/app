#include "framework.h"


namespace aura
{


   department::department(application * papp):
      object(papp)
   {

   }


   department::~department()
   {

   }


   // designed to be in constructors, so should
   // not contain advanced initialization as the
   // papp application pointer may be incompletely
   // initialized specially its virtual functions.
   void department::construct(::aura::application * papp)
   {

      set_app(papp);

   }


   void department::connect_to_application_signal()
   {

      m_pauraapp->add_route(this,&department::on_application_message);

   }


   bool department::process_init()
   {

      return true;

   }


   bool department::init()
   {

      return true;

   }


   bool department::init1()
   {

      return true;

   }


   bool department::init2()
   {

      return true;

   }


   bool department::init3()
   {

      return true;

   }

   bool department::init_instance()
   {

      return true;

   }


   void department::term_instance()
   {

   }


   void department::term()
   {

   }

   void department::term3()
   {

   }

   void department::term2()
   {

   }

   void department::term1()
   {

   }

   void department::on_application_message(::message::message * pobj)
   {

      SCAST_PTR(::aura::application_message,papplicationsignal,pobj);

      try
      {
         if(papplicationsignal->m_esignal == ::aura::application_message_process_init)
         {

            papplicationsignal->m_bOk = process_init();

         }
         else if(papplicationsignal->m_esignal == ::aura::application_message_init)
         {

            papplicationsignal->m_bOk = init();

         }
         else if(papplicationsignal->m_esignal == ::aura::application_message_init1)
         {

            papplicationsignal->m_bOk = init1();

         }
         else if(papplicationsignal->m_esignal == ::aura::application_message_init2)
         {

            papplicationsignal->m_bOk = init2();

         }
         else if(papplicationsignal->m_esignal == ::aura::application_message_init3)
         {

            papplicationsignal->m_bOk = init3();

         }
         else if(papplicationsignal->m_esignal == ::aura::application_message_init_instance)
         {

            papplicationsignal->m_bOk = init_instance();

         }
         else if(papplicationsignal->m_esignal == ::aura::application_message_term_instance)
         {

            term_instance();

            papplicationsignal->m_bOk = true;

         }
         else if(papplicationsignal->m_esignal == ::aura::application_message_term3)
         {

            term3();

            papplicationsignal->m_bOk = true;

         }
         else if(papplicationsignal->m_esignal == ::aura::application_message_term2)
         {

            term2();

            papplicationsignal->m_bOk = true;

         }
         else if(papplicationsignal->m_esignal == ::aura::application_message_term1)
         {

            term1();

            papplicationsignal->m_bOk = true;

         }
         else if(papplicationsignal->m_esignal == ::aura::application_message_process_term)
         {

            term();

            papplicationsignal->m_bOk = true;

         }

      }
      catch(...)
      {

         papplicationsignal->m_bOk = false;

      }

   }







} // namespace aura


