#include "framework.h"


namespace user
{


   tree_window::tree_window(::aura::application * papp) :
      object(papp),
      ::user::interaction(papp),
      ::user::tree(papp)
   {
   }

   tree_window::~tree_window()
   {
   }

   void tree_window::install_message_routing(::message::sender * pinterface)
   {


      ::user::interaction::install_message_routing(pinterface);
      ::user::tree::install_message_routing(pinterface);


   }


} // namespace user


