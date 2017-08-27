#include "framework.h"


namespace userex
{


   pane_view::pane_view(::aura::application * papp) :
      object(papp)
   {

   }


   pane_view::~pane_view()
   {

   }


   void pane_view::on_command_probe(::user::command * pcommand)
   {

      for(int32_t i = 0; i < m_menua.get_size(); i++)
      {

         if(pcommand->m_id == ::message::id(m_menua[i]->m_id, ::message::type_command_probe))
         {

            pcommand->Enable(TRUE);

            pcommand->m_bRet = true;

            return;

         }

      }

      ::user::impact::on_command_probe(pcommand);

   }


   void pane_view::on_command(::user::command * pcommand)
   {

      for(int32_t i = 0; i < m_menua.get_size(); i++)
      {

         if(pcommand->m_id == ::message::id(m_menua[i]->m_id, ::message::type_command))
         {
            
            // show_view where??

            pcommand->m_bRet = true;

            return;

         }

      }
      
      ::user::impact::on_command(pcommand);

   }


   void pane_view::on_create_view(::user::view_creator_data * pcreatordata)
   {
      for(int32_t i = 0; i < m_menua.get_size(); i++)
      {
         if(pcreatordata->m_id == m_menua[i]->m_id)
         {
            //create_context cc;
            //cc.m_pCurrentDoc = get_document();
            //cc.m_typeinfoNewView = System.type_info < ::user::menu_list_view > ();

            sp(::user::impact) pview = create_view < ::user::impact > ();
            if(pview != NULL)
            {
//               sp(::user::menu_list_view) pmenuview = (sp(::user::menu_list_view)) pview;
   /* xxx           xml::node node(get_app());
               node.load(Application.file().as_string(Application.dir().matter(
                  "mplite_popup_lyricview.xml")));
               pmenuview->LoadMenu(&node);*/
               pcreatordata->m_pwnd = pview;
            }
            break;
         }
      }
   }

   void pane_view::set_new_pane_info(id id, const char * pszMatter)
   {
      set_menu_info(id, pszMatter, "new_pane");
   }

   void pane_view::set_menu_info(id id, const char * pszMatter, class id idCommand)
   {

      sp(menu) pmenu;

      for(int32_t i = 0; i < m_menua.get_size(); i++)
      {

         if(m_menua[i]->m_id == id)
         {

            pmenu = m_menua[i];

            break;

         }

      }

      if(pmenu.is_null())
      {

         pmenu = new menu;

         pmenu->m_id = id;

         m_menua.add(pmenu);

      }

      pmenu->m_strMatter = pszMatter;

      pmenu->m_id = idCommand;

   }


} // namespace userex




