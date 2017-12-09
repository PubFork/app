#include "framework.h"
#include "framework.h"




namespace filemanager
{


   folder_selection_list_view::folder_selection_list_view(::aura::application * papp):
      object(papp),
      ::user::split_layout(papp),
      ::user::split_view(papp),
      place_holder_container(papp)
   {

      m_ptree = NULL;
      m_pusertree = NULL;
      m_pdata = NULL;
      m_plistview = NULL;

   }


   folder_selection_list_view::~folder_selection_list_view()
   {

   }


   void folder_selection_list_view::install_message_routing(::message::sender * pinterface)
   {

      ::user::split_view::install_message_routing(pinterface);

   }


   void folder_selection_list_view::on_create_views()
   {

      SetPaneCount(2);

      SetSplitOrientation(orientation_vertical);

      set_position_rate(0, 0.30);

      initialize_split_layout();

      m_pusertree = create_view  < ::user::tree_view >(get_document(), ::null_rect(), get_pane_holder(0));

      if(m_pusertree == NULL)
      {

         System.simple_message_box(NULL,"Could not create folder tree view");

      }

      m_ptree = canew(tree(get_app()));

      if(m_ptree == NULL)
      {

         System.simple_message_box(NULL,"Could not create folder tree");
      }

      m_ptree->m_pmanager = get_filemanager_manager();

      m_pusertree->merge(m_ptree, true);

      m_plistview = create_view < folder_list_view >(get_document(),::null_rect(),get_pane_holder(1));

      if(m_plistview == NULL)
      {

         System.simple_message_box(NULL,"Could not create file list");

      }

   }


   void folder_selection_list_view::browse_sync(::action::context actioncontext)
   {

      update_hint uh;
      uh.set_type(update_hint::TypeSynchronizeFolderSelection);
      uh.m_actioncontext = actioncontext + ::action::source_selection;
      get_document()->update_all_views(NULL,0,&uh);

   }


   void folder_selection_list_view::FolderAdd()
   {

      stringa straSel;

      m_ptree->GetSelectedFilePath(straSel);

      if(m_plistview->m_bRecursive)
      {

         bool_array ba;

         m_plistview->add_unique(straSel,ba);

      }
      else
      {

         m_plistview->add_unique(straSel);

      }

   }

   void folder_selection_list_view::FolderRemove()
   {

      stringa wstraSel;

      m_plistview->GetSel(wstraSel);

      m_plistview->remove(wstraSel);

   }


   void folder_selection_list_view::on_update(user::impact *p, LPARAM l, object * o)
   {

      ::filemanager::impact::on_update(p, l, o);

   }


   void folder_selection_list_view::_001OnAdd(::message::message * pobj)
   {

      FolderAdd();

      if (pobj != NULL)
      {

         pobj->m_bRet = true;

      }

   }


   void folder_selection_list_view::_001OnRemove(::message::message * pobj)
   {

      FolderRemove();

      if (pobj != NULL)
      {

         pobj->m_bRet = true;

      }

   }

   data * folder_selection_list_view::get_filemanager_data()
   {

      return m_pdata;

   }


} // namespace filemanager









