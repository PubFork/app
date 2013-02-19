#include "framework.h"


namespace ca2
{


   namespace user
   {


      user::user()
      {

         //gen::user * papp = dynamic_cast <gen::user *>(System.GetThread()->m_pAppThread);
         //gen::connect(papp->m_signalAppLanguageChange, this, &user::VmsGuiiOnAppLanguage);

         m_pkeyboard = NULL;
         m_pwindowmap = NULL;

      }

      user::~user()
      {
      }



      bool user::initialize1()
      {

         if(!::cubebase::user::initialize1())
            return false;

         return true;

      }


      bool user::initialize()
      {


         if(is_cube())
         {
            System.factory().cloneable_small < int_biunique > ();
            System.factory().creatable_small < ::user::edit_plain_text > ();
            System.factory().cloneable_small < XfplayerViewLine > ();
            System.factory().creatable_small < ::user::place_holder > ();
            System.factory().creatable_small < ::user::place_holder_container > ();
         }

         if(!::cubebase::user::initialize())
            return false;

         return true;
      }

      int32_t user::exit_instance()
      {
         if(is_cube())
         {
            if(m_pwindowmap != NULL)
            {
               delete m_pwindowmap;
               m_pwindowmap = NULL;
            }
         }
         try
         {
            ::visual::user::exit_instance();
         }
         catch(...)
         {
         }
         try
         {
            ::database::user::exit_instance();
         }
         catch(...)
         {
         }
         try
         {
            ::ca4::user::exit_instance();
         }
         catch(...)
         {
         }
         return 0;
      }


      void user::SendMessageToWindows(UINT message, WPARAM wparam, LPARAM lparam)
      {
         ::user::interaction_ptr_array wnda = frames();
         for(int32_t i = 0; i < wnda.get_size(); i++)
         {
            ::user::interaction * pwnd = wnda.element_at(i);
            if(pwnd != NULL && pwnd->IsWindow())
            {
               pwnd->send_message(message, wparam, lparam);
               pwnd->SendMessageToDescendants(message, wparam, lparam);
            }
         }
      }


      int32_t user::GetVisibleFrameCountExcept(::user::interaction * pwndExcept)
      {
         ::user::interaction_ptr_array wnda = frames();
         int32_t iCount = 0;
         for(int32_t i = 0; i < wnda.get_size(); i++)
         {
              ::user::interaction * pwnd = wnda.element_at(i);
              if(pwnd != NULL &&
                  pwnd != pwndExcept &&
                  pwnd->IsWindowVisible())
              {
                  iCount++;
              }
          }
          return iCount;
      }

      int32_t user::GetVisibleTopLevelFrameCountExcept(::user::interaction * pwndExcept)
      {
         ::user::interaction_ptr_array wnda = frames();
         int32_t iCount = 0;
         for(int32_t i = 0; i < wnda.get_size(); i++)
         {
            ::user::interaction * pwnd = wnda.element_at(i);
            if(pwnd != NULL &&
               pwnd != pwndExcept &&
               pwnd->IsWindow() &&
               pwnd->IsWindowVisible() &&
               !(pwnd->GetStyle() & WS_CHILD))
            {
               iCount++;
            }
         }
         return iCount;
      }

      int32_t user::GetVisibleFrameCount()
      {
         ::user::interaction_ptr_array wnda = frames();
         int32_t iCount = 0;
         for(int32_t i = 0; i < wnda.get_size(); i++)
         {
            ::user::interaction * pwnd = wnda.element_at(i);
            if(pwnd != NULL
               && pwnd->IsWindow()
               && pwnd->IsWindowVisible())
            {
               iCount++;
            }
         }
         return iCount;
      }

      void user::VmsGuiiOnAppLanguage(gen::signal_object * pobject)
      {
         SendMessageToWindows(gen::user::APPM_LANGUAGE, 0, (LPARAM) pobject);
      }

      string user::message_box(const char * pszMatter, gen::property_set & propertyset)
      {

         class ::ca8::message_box box(this);

         box.show(pszMatter, &propertyset);

         return box.m_strResponse;

      }



   } // namespace user


} // namespace ca2