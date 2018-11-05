#include "framework.h"


namespace user
{


   namespace wndfrm
   {


      namespace wndfrm_core
      {


         library::library(::aura::application * papp):
            object(papp),
            ::aura::library(papp,0,"")
         {

         }


         library::~library()
         {

         }


         sp(::object) library::create_object(::aura::application * papp,const char * pszClass, object * p)
         {

            if(string(pszClass) == "wndfrm")
            {

               return canew(interaction(papp));

            }
            else if(string(pszClass) == "control_box")
            {

               return canew(MetaControlBox(papp));

            }
            else if(string(pszClass) == "control_box_button")
            {

               return canew(::user::meta_button(papp));

            }
            else if(string(pszClass) == "user_theme")
            {

               return canew(::wndfrm_core::theme(get_app()));

            }
            else
            {

               return NULL;

            }

         }


      } // namespace wndfrm_core


   } // namespace wndfrm


} // namespace user


#if defined(CUBE)

extern "C"
::aura::library * wndfrm_core_get_new_library(::aura::application * papp)
{

   return new ::user::wndfrm::wndfrm_core::library(papp);

}


#else


extern "C"
::aura::library * get_new_library(::aura::application * papp)
{

   return canew(::user::wndfrm::wndfrm_core::library (papp));

}

#endif


