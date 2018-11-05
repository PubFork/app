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





string __get_text(string str)
{

   ::aura::application * papp = ::get_app();

   if(papp == NULL)
   {

      return Sys(::aura::system::g_p).__get_text(str);

   }

   return Application.__get_text(str);

}


CLASS_DECL_AURA int __c_get_text_length(const char * psz)
{
 
   string str = __get_text(psz);

   return (int) str.get_length();
   
}


CLASS_DECL_AURA void __c_get_text(char * pszText, int iLen, const char * psz)
{

   string str = __get_text(psz);

   iLen = MIN(iLen, (int) str.get_length());

   strncpy(pszText, str, iLen);
   
   pszText[iLen] = '\0';
   
}

