#include "framework.h"





namespace core
{


} // namespace core




#include "framework.h"

#if defined(CUBE) || defined(APPLE_IOS)
extern "C"
::aura::library * core_get_new_library(::aura::application * papp);

#else
#ifndef _WIN32
extern "C"
#endif
::aura::library * get_new_library(::aura::application * papp);
#endif

namespace core
{


   library::library(::aura::application * papp) :
      object(papp),
      ::aura::library(papp, 0, "app"),
      ::aura::single_application_library < application >(papp, "app"),
      ::filehandler::library(papp),
      ::filehandler::menu_library(papp)
   {

   }


   void library::get_app_list(stringa & stra)
   {


      stra.add("fontopus");
      stra.add("netnode");
      stra.add("default_file_handler");

   }


   void library::get_extension_list(stringa & stra)
   {

      stra.add("*");

   }

   void library::get_extension_app(stringa & straApp,const char * pszExtension)
   {

      string strExtension(pszExtension);

      strExtension.make_lower();

      if(strExtension == "*")
      {
         straApp.add_unique("default_file_handler");
      }
      if(strExtension == "mid" || strExtension == "karaoke" || strExtension == "st3")
      {
         straApp.add_unique("mplite");
         straApp.add_unique("vmsp");
      }

   }



} // namespace cube





#if defined(CUBE) || defined(APPLE_IOS)
extern "C"
::aura::library * core_get_new_library(::aura::application * papp)
#else
#ifndef _WIN32
extern "C"
#endif
::aura::library * get_new_library(::aura::application * papp)
#endif
{

   return canew(::core::library(papp));

}
