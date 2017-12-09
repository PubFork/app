#include "framework.h"


namespace filemanager
{


   folder_list_view::folder_list_view(::aura::application * papp):
      object(papp),
      simple_list_view(papp)
   {

      m_bRecursive = true;

   }


   folder_list_view::~folder_list_view()
   {

   }


   void folder_list_view::install_message_routing(::message::sender * psender)
   {

      ::filemanager::impact::install_message_routing(psender);
      ::simple_list_view::install_message_routing(psender);

   }


   void folder_list_view::initialize(string strDataKeyModifier,bool bRecursive)
   {

      set_data_key_modifier(strDataKeyModifier);

      m_bRecursive = bRecursive;

      _001UpdateColumns();

      _001OnUpdateItemCount();

      if(bRecursive)
      {

         sp(folder_list_data) pdata = canew(folder_list_data(get_app()));

         SetDataInterface(pdata);

         pdata->set_data_key_modifier(strDataKeyModifier);

         pdata->initialize_data_client(&Application.dataserver());

      }
      else
      {

         sp(databaseuser::data_key_mesh_data) pdata = canew(databaseuser::data_key_mesh_data(get_app()));

         SetDataInterface(pdata);

         pdata->set_data_key_modifier(strDataKeyModifier);

         pdata->initialize_data_client(&Application.dataserver());

      }

      fork([&]()
      {

         _001OnUpdateItemCount();

      });

   }


   string folder_list_view::calc_data_id()
   {

      return ::database::client::calc_data_id() + "." + m_strDataKeyModifier;

   }


   void folder_list_view::_001InsertColumns()
   {

      ::user::list_column column;

      column.m_iWidth               = 400;
      column.m_iSubItem             = 0;
      _001AddColumn(column);

      if(m_bRecursive)
      {

         column.m_iWidth               = 80;
         column.m_iSubItem             = 0;
         _001AddColumn(column);

      }

   }


   bool folder_list_view::add_unique(const stringa & stra)
   {

      if(m_bRecursive)
         _throw(simple_exception(get_app(), "incorrect usage of this class object"));

      if(stra.get_size() == 0)
         return true;

      sp(databaseuser::data_key_mesh_data) pdata = m_pmeshdata.cast <databaseuser::data_key_mesh_data >();

      if(!pdata->add_unique(stra))
         return false;

      _001OnUpdateItemCount();

      return true;

   }


   bool folder_list_view::add_unique(const stringa & stra,bool_array & baRecursive)
   {

      if(!m_bRecursive)
         _throw(simple_exception(get_app(), "incorrect usage of this class object"));

      if(stra.get_size() == 0)
         return true;

      sp(folder_list_data) pdata = m_pmeshdata.cast <folder_list_data> ();

      if(!pdata->add_unique(stra,baRecursive))
         return false;

      _001OnUpdateItemCount();

      return true;

   }


   bool folder_list_view::remove(const stringa & stra)
   {

      if (stra.get_size() == 0)
      {

         return true;

      }

      if(m_bRecursive)
      {

         sp(folder_list_data) pdata = m_pmeshdata.cast <folder_list_data >();

         if(!pdata->remove(stra))
            return false;

      }
      else
      {

         sp(databaseuser::data_key_mesh_data) pdata = m_psimplemeshdata.cast <databaseuser::data_key_mesh_data > ();

         if(!pdata->remove(stra))
            return false;

      }

      _001OnUpdateItemCount();

      return true;

   }


   void folder_list_view::GetSel(stringa & stra)
   {

      if(m_bRecursive)
      {

         sp(folder_list_data) pdata = m_pmeshdata.cast <folder_list_data >();
         pdata->GetSel(this,stra);

      }
      else
      {

         sp(databaseuser::data_key_mesh_data) pdata = m_psimplemeshdata.cast <databaseuser::data_key_mesh_data >();
         pdata->GetSel(this,stra);

      }

   }


   void folder_list_view::on_update(::user::impact * pSender,LPARAM lHint,object* phint)
   {

      ::filemanager::impact::on_update(pSender,lHint,phint);

      if(phint != NULL)
      {

         if(base_class < update_hint >::bases(phint))
         {

            update_hint * puh = (update_hint *)phint;

            if(puh->is_type_of(update_hint::TypeInitialize))
            {

               if(get_filemanager_data()->m_bPassBk)
               {

                  ::user::list::m_bBackgroundBypass = true;

               }

               initialize(get_filemanager_data()->m_id,get_filemanager_data()->m_bEnableRecursiveFolderSelectionList);

            }

         }

      }

   }


} // namespace filemanager
