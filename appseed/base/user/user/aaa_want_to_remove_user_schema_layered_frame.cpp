//#include "framework.h" // from "base/user/user.h"
//#include "base/user/user.h"


namespace user
{


   schema_layered_frame::schema_layered_frame(::aura::application * papp) :
      object(papp)
   {


   }


   bool schema_layered_frame::get_translucency(e_translucency & etranslucency)
   {

      etranslucency = translucency_present;

      return true;

   }


} // namespace user






