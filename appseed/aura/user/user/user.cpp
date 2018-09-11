#include "framework.h"


namespace user
{


   bool is_descendant(::user::interaction * puiParent, ::user::interaction * pui)
      // helper for detecting whether child descendent of parent
      //  (works with owned popups as well)
   {

      if (pui == NULL)
         return false;

      ::user::interaction * puiAscendant = pui;

      do
      {

         puiAscendant = puiAscendant->GetOwner();


         if (puiParent == puiAscendant)
            return true;

      } while (puiAscendant != NULL);


      puiAscendant = pui;

      do
      {

         puiAscendant = puiAscendant->GetParent();


         if (puiParent == puiAscendant)
            return true;

      } while (puiAscendant != NULL);


      return false;

   }


} // namespace user





string get_text(string str)
{

   if(::get_app() == NULL)
   {

      return Sys(::aura::system::g_p).get_text(str);

   }

   return Application.get_text(str);

}
