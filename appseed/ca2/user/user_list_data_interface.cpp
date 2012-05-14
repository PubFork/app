#include "framework.h"

namespace user
{

   list_data::list_data(::ca::application * papp) :
      ca(papp),
      ::ca::data(papp)
   {
   }

   list_data::~list_data()
   {
   }


   void list_data::_001GetItemImage(::user::list_item * pitem)
   {
      pitem->m_bOk = false;
   }

   void list_data::_001GetGroupText(::user::list_item * pitem)
   {
      pitem->m_bOk = false;
   }

   void list_data::_001GetGroupImage(::user::list_item * pitem)
   {
      pitem->m_bOk = false;
   }

   count list_data::_001GetGroupCount()
   {
      return -1;
   }

   ::count list_data::_001GetGroupMetaItemCount(index iGroup)
   {
      UNREFERENCED_PARAMETER(iGroup);
      return 0;
   }

} // namespace user