#include "framework.h"


void simple_frame_window::defer_set_icon()
{

   if (GetParent() == NULL)
   {

      ::file::path strMatter = get_window_default_matter();
      //http://www.cplusplus.com/forum/general/28470/
      //blackcoder41 (1426)  Sep 12, 2010 at 2:43pm
      //hIconSm = (HICON)LoadImage(NULL, "menu_two.ico", IMAGE_ICON, 16, 16, LR_LOADFROMFILE);

      stringa straMatter;

      if (strMatter.name(0) == "system")
      {

         straMatter.add("main");

         straMatter.add(strMatter);

      }
      else
      {

         straMatter.add(strMatter);

         straMatter.add("main");

      }

      HICON hicon = load_icon(get_app(), straMatter, "icon.ico", 16, 16);

      if (hicon != NULL)
      {

         SendMessage(get_handle(), (UINT)WM_SETICON, ICON_SMALL, (LPARAM)hicon);

      }

      hicon = load_icon(get_app(), straMatter, "icon.ico", 16, 16);

      if (hicon != NULL)
      {

         SendMessage(get_handle(), (UINT)WM_SETICON, ICON_BIG, (LPARAM)hicon);

      }

      if (m_bWindowFrame)
      {

         hicon = load_icon(get_app(), straMatter, "icon.ico", 24, 24);

         if (hicon != NULL)
         {

            ::visual::icon * picon = canew(::visual::icon(get_app(), hicon));

            if (picon != NULL && m_workset.m_pappearance != NULL)
            {

               m_workset.m_pappearance->m_picon = picon;

            }

         }

      }

   }

}

