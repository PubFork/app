#include "framework.h"
#include "android.h"


namespace android
{


   namespace axis
   {


      factory_exchange::factory_exchange(::aura::application * papp):
         element(papp)
      {

         System.factory().creatable < window_draw                 >(System. type_info < ::user::window_draw          >(),1);
         System.factory().creatable_large < interaction_impl      >(System. type_info < ::user::interaction_impl     >());
         System.factory().creatable < message_queue               >(System. type_info < ::aura::message_queue        >(),1);
         System.factory().creatable_small < copydesk              >(System. type_info < ::axis::copydesk             >(),1);

      }


      factory_exchange::~factory_exchange()
      {

      }


   } // namespace axis


} // namespace android


extern "C"
void ca2_factory_exchange(::aura::application * papp)
{
   ::android::axis::factory_exchange factoryexchange(papp);
}


