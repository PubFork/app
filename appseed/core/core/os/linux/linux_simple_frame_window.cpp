#include "framework.h"
#include "aura/aura/os/linux/linux_user_impl.h"


void simple_frame_window::defer_set_icon()
{


   if (GetParent() == NULL)
   {

      //get_handle()->bamf_set_icon();

      ::file::path strMatter = get_window_default_matter();

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

      ::visual::dib_sp d(allocer());

      if(d.load_matter_icon(straMatter, "icon.png"))
      {

         //get_handle()->set_icon(d);

      }

   }

}

