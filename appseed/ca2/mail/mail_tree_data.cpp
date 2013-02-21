#include "framework.h"


namespace mail
{


   tree_data::tree_data(::ca::application * papp) :
      ca(papp),
      gen::tree_data(papp)
   {
   }


   ::gen::tree_item_data * tree_data::on_allocate_item()
   {
      return new ::mail::tree_item();
   }

   void tree_data::on_delete_item(::gen::tree_item_data * pitem)
   {
      delete (::mail::tree_item *) pitem;
   }


} // namespace mail


