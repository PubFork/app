#include "framework.h"
#include "aura/node/ansios/ansios.h"
#include "linux.h"
#include "aura/aura/os/linux/linux_user_impl.h"



namespace linux
{

   namespace aura
   {


      factory_exchange::factory_exchange(sp(::aura::application) papp) :
         ::object(papp)
      {

               // axis will put things in the axis, (at least in this case... :-)
         System.factory().creatable_small    < ::linux::file_system   >(System.type_info < ::file::system              >(),1);
         System.factory().creatable_small    < ::linux::dir           >(System.type_info < ::file::dir::system         >(),1);


         System.factory().cloneable_large <stdio_file             >  (System. type_info < ::file::text_file        > ());
         System.factory().cloneable_large < file                  >  (System. type_info < ::file::binary_file      > (), true);
         System.factory().cloneable_large < file                  >  (System. type_info < ::file::file      > (), true);
         //System.factory().cloneable < application                 >  (System. type_info < ::aura::application        > (), 1);
         System.factory().creatable_large < ::thread              >  (System. type_info < ::thread                   > ());
         System.factory().creatable < os                          >  (System. type_info < ::aura::os                 > (), 1);
         System.factory().creatable < ::ansios::process           >  (System. type_info < ::process::process         > (), 1);
         System.factory().creatable < ::ansios::pipe              >  (System. type_info < ::process::pipe            > (), 1);
         System.factory().creatable < console                     >  (System. type_info < ::console::window          > (), 1);
         System.factory().cloneable_large < window_xlib                 >  (System.type_info <window_graphics                > ());
         System.factory().creatable_large < interaction_impl      >  (System. type_info < ::user::interaction_impl > ());

      }


      factory_exchange::~factory_exchange()
      {

      }


   } // namespace aura


} // namespace win


void __node_aura_factory_exchange(::aura::application * papp)
{

   ::linux::aura::factory_exchange factoryexchange(papp);

}




