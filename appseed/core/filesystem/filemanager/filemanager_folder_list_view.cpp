#include "framework.h"
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

      _001UpdateColumns();

      _001OnUpdateItemCount();

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
         _throw("incorrect usage of this class object");

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
         _throw("incorrect usage of this class object");

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

      if(stra.get_size() == 0)
         return true;

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


               m_pauraapp = get_app()->m_pcoreapp;
               //           db_server * pcentral = dynamic_cast < db_server * > (&System.m_simpledb.db());
               //         if(pcentral == NULL)
               //          return;
//               string str;
               //             str.Format("&data_source=local&file_list(%s)",get_filemanager_data()->m_strDISection);
               if(get_filemanager_data()->m_bPassBk)
               {
                  ::user::list::m_bBackgroundBypass = true;
               }
               //     m_dataid = str;

               initialize(get_filemanager_data()->m_id,get_filemanager_data()->m_bEnableRecursiveFolderSelectionList);

            }
            //else if(!m_bStatic && puh->is_type_of(update_hint::TypeSynchronizePath))
            //{
            //   if(puh->m_strPath != get_filemanager_item().m_strPath)
            //      return;
            //   if(get_filemanager_data()->m_pholderFileList != NULL)
            //   {
            //      if(get_filemanager_data()->m_pholderFileList->m_uiptraHold.get_size() > 0)
            //      {
            //         get_filemanager_data()->m_pholderFileList->m_uiptraHold[0]->ShowWindow(SW_HIDE);
            //      }
            //      get_filemanager_data()->m_pholderFileList->hold(this);
            //      get_filemanager_data()->m_pholderFileList->on_layout();
            //   }

            //   data_get_DisplayToStrict();
            //   _001OnUpdateItemCount();
            //   /*string str;
            //   if(data_get("sort-" + get_filemanager_item().m_strPath, str))
            //   {
            //   stringa stra;
            //   stra.add_tokens(str, ";", true);
            //   if(stra.get_size() == m_iaDisplayToStrict.get_size())
            //   {
            //   for(int32_t i = 0; i < m_iaDisplayToStrict.get_size(); i++)
            //   {
            //   m_iaDisplayToStrict.set(i, atoi(stra[i]));
            //   }
            //   }
            //   }*/
            //}
            //else if(puh->is_type_of(update_hint::TypeFilter))
            //{
            //   if(puh->m_wstrFilter.is_empty())
            //   {
            //      FilterClose();
            //   }
            //   else
            //   {
            //      FilterBegin();
            //      Filter1(puh->m_wstrFilter);
            //      //                  FilterApply();
            //   }
            //}
            //else if(puh->is_type_of(update_hint::TypeGetActiveViewSelection))
            //{
            //   if(GetParentFrame()->GetActiveView() == (this))
            //   {
            //      GetSelected(puh->m_itemaSelected);
            //   }
            //}
         }
         else if(base_class < form_update_hint > :: bases(phint))
         {
            form_update_hint * puh = dynamic_cast<form_update_hint * > (phint);
            if(puh->m_etype == form_update_hint::type_after_browse)
            {
               if(puh->m_strForm == "filemanager\\replace_name_in_file_system.xhtml")
               {
                  //html::elemental * pelemental = dynamic_cast < html::elemental * > (puh->m_pformview->get_html_data()->get_element_by_name("encontrar"));
                  //html::impl::input_text * pinput = dynamic_cast < html::impl::input_text * > (pelemental->m_pimpl);
                  //sp(::user::interaction) ptext = puh->m_pform->get_child_by_id("encontrar");
                  //range range;
                  //_001GetSelection(range);
                  //if(range.get_item_count() > 0)
                  //{
                  //   ptext->_001SetText(get_fs_mesh_data()->m_itema.get_item(range.ItemAt(0).get_lower_bound()).m_strName,puh->m_actioncontext);
                  //}
               }
            }
            form_update_hint * pmanageruh = dynamic_cast<form_update_hint * > (phint);

            if(pmanageruh != NULL)
            {
               if(!pmanageruh->m_strFind.is_empty())
               {
               }
            }
         }

      }
   }




} // namespace filemanager
