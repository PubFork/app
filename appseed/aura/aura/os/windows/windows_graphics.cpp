#include "framework.h"


HICON load_icon(::aura::application * papp, stringa & straMatter, string strIcon, int cx, int cy)
{

   HICON hicon = NULL;

   ::file::path path;

   for (auto & strMatter : straMatter)
   {

      path = strMatter;

      path = App(papp).dir().matter(path / strIcon);

      path = Sys(papp).get_matter_cache_path(path);

      hicon = (HICON)LoadImage(NULL, path, IMAGE_ICON, cx, cy, LR_LOADFROMFILE);

      if (hicon != NULL)
      {

         break;

      }

   }

   return hicon;

}



CLASS_DECL_AURA bool os_init_imaging()
{



   return true;

}


CLASS_DECL_AURA void os_term_imaging()
{

}



