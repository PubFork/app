#include "framework.h"


namespace calculator
{

   application::application()
   {
   }

   application::~application()
   {
   }


   bool application::init_instance()
   {

      if (!::asphere::application::init_instance())
      {

         return false;

      }

      return true;

   }


} // namespace calculator



