#include "framework.h"


namespace databaseuser
{


   data_key_list_data::data_key_list_data(::ca::application * papp) :
      ca(papp),
      ::user::list_data(papp)
   {
   }

   data_key_list_data::~data_key_list_data()
   {
   }


   void data_key_list_data::_001GetItemText(::user::list_item * pitem)
   {
      stringa stra;
      if(!data_get(::gen::system::idEmpty, ::gen::system::idEmpty, stra))
         return_(pitem->m_bOk, false)
      pitem->m_strText = stra[pitem->m_iItem];
      pitem->m_bOk = true;
   }

   void data_key_list_data::GetSel(::user::list * plist , stringa & stra)
   {
      stringa wstraTotal;
      if(!data_get(::gen::system::idEmpty, ::gen::system::idEmpty, wstraTotal))
         return;
      ::user::list::Range range;
      plist->_001GetSelection(range);
      for(index i = 0; i < range.get_item_count() ; i++)
      {
         ::user::list::ItemRange itemrange = range.ItemAt(i);
         for(index iItem = itemrange.GetLBound(); iItem <= itemrange.GetUBound(); iItem++)
         {
            stra.add(wstraTotal[iItem]);
         }
      }
   }

   count data_key_list_data::_001GetItemCount()
   {
      stringa straTotal;
      if(!data_get(::gen::system::idEmpty, ::gen::system::idEmpty, straTotal))
         return -1;
      return straTotal.get_size();
   }


   bool data_key_list_data::add_unique(const stringa & stra)
   {
      stringa straData;
      data_get(::gen::system::idEmpty, ::gen::system::idEmpty, straData);
      straData.add_unique(stra);
      if(!data_set(::gen::system::idEmpty, ::gen::system::idEmpty, straData))
         return false;
      return true;
   }

   bool data_key_list_data::remove(const stringa & stra)
   {
      stringa straData;
      if(!data_get(::gen::system::idEmpty, ::gen::system::idEmpty, straData))
         return true;
      straData.remove(stra);
      if(!data_set(::gen::system::idEmpty, ::gen::system::idEmpty, straData))
         return false;
      return true;
   }


} // namespace databaseuser



