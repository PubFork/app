#include "framework.h"

//
//  core_static_start
//

aura_level auralevelCore(::aura_level::level_core, &defer_core_init);

namespace core
{



   namespace static_start
   {


      CLASS_DECL_CORE void init()
      {


         #ifdef LINUX


            ::user::initialize_edesktop();


         #endif


      }














































      CLASS_DECL_CORE void term()
      {




      }



   } // namespace static_start


} // namespace base





