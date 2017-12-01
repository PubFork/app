#include "framework.h"


namespace calculator
{

   application::application()
   {
   }

   application::~application()
   {
   }


   bool application::init()
   {

      if (!::asphere::application::init())
      {

         return false;

      }

      return true;

   }


} // namespace calculator



