#include "framework.h"


namespace user
{


   namespace wndfrm
   {


      namespace wndfrm_anthill
      {


         library::library(::aura::application * papp):
            object(papp),
            ::aura::library(papp,0,"")
         {
         }


         library::~library()
         {
         }


         //bool library::is_uinteraction_library()
         //{

         //   return true;

         //}


         sp(::object) library::create_object(::aura::application * papp,const char * pszClass, object * p)
         {

            if(string(pszClass) == "wndfrm")
            {

               return new interaction(papp);

            }
            else if(string(pszClass) == "control_box")
            {

               return new MetaControlBox(papp);

            }
            else if(string(pszClass) == "control_box_button")
            {

               return new ::user::meta_button(papp);

            }
            else if(string(pszClass) == "user_theme")
            {

               return new ::wndfrm_anthill::theme(get_app());

            }
            else
            {

               return NULL;

            }

         }


      } // namespace wndfrm_anthill


   } // namespace wndfrm


} // namespace user


#ifdef CUBE

extern "C"
::aura::library * wndfrm_anthill_get_new_library(::aura::application * papp)
{

   return new ::user::wndfrm::wndfrm_anthill::library(papp);

}


#else


extern "C"
::aura::library * get_new_library(::aura::application * papp)
{
   return new ::user::wndfrm::wndfrm_anthill::library (papp);
}

#endif


