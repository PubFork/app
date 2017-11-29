#include "framework.h"


namespace estamira
{


   application::application()
   {

   }


   application::~application()
   {
   }


   bool application::init_instance()
   {

//      if (!::hellomultiverse::application::init_instance())
//         return false;

      if (!::multimedia::application::init_instance())
         return false;

      return true;

   }


   int32_t application::exit_application()
   {

      return ::multimedia::application::exit_application();

   }



} // namespace estamira




