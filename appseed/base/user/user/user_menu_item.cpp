#include "framework.h"


namespace user
{


   menu_item::menu_item(::aura::application * papp) :
      ::object(papp)
   {

      m_spitema      = canew(menu_item_ptra(this));
      m_iLevel       = 0;
      m_bPopup       = false;

   }


   menu_item::~menu_item()
   {

   }


   bool menu_item::create_menu(const stringa & straCommand, const stringa & straCommandTitle)
   {

      ::count iItemCount = straCommand.get_count();
      
      if(straCommandTitle.get_size() < straCommand.get_size())
         return false;
      
      for(int32_t i = 0; i < iItemCount; i++)
      {
         string strCommand = straCommand[i];
         string strCommandTitle = straCommandTitle[i];
         sp(menu_item) pitemNewChild = canew(menu_item(get_app()));
         pitemNewChild->m_bPopup = false;
         if(strCommand.is_empty())
         {
            pitemNewChild->m_id = "separator";
            m_iSeparatorCount++;
         }
         else
         {
            m_iFullHeightItemCount++;
            pitemNewChild->m_id = strCommand;
            pitemNewChild->m_iLevel = 0;
            pitemNewChild->m_pui->set_window_text(strCommandTitle);
         }
         add_item(pitemNewChild);
      }
      
      return iItemCount > 0;

   }

   bool menu_item::load_menu(::xml::node * pnode)
   {

      m_iSeparatorCount       = 0;
      m_iFullHeightItemCount  = 0;
      
      return load_menu(pnode, m_iLevel);

   }

  
   
   void menu_item::add_item(menu_item * pitem)
   {
      
      m_spitema->add(pitem);
      
   }
   

   bool menu_item::load_menu(::xml::node * pnode, int32_t iLevel)
   {
      
      ::count iItemCount = pnode->get_children_count();
      
      
      m_bPopup = pnode->get_children_count() > 0 && pnode->get_name() == "menubar";
      
      if(pnode->get_name() == "separator")
      {
         
         m_id = "separator";
         
         if(m_pmenu->m_pmenuParent != NULL)
         {
            
            m_pmenu->m_pmenuParent->m_pitem->m_iSeparatorCount++;
            
         }
         
      }
      else
      {
         
         m_iFullHeightItemCount++;
         
         m_id = pnode->attr("id");
         
         string strText;
         
         if(m_bPopup)
         {

         m_iLevel = iLevel + 1;

         strText = pnode->attr("title");

         }
         else
         {

            m_iLevel = iLevel;

            strText = pnode->get_value();

         }

         if (m_pui != NULL)
         {

            m_pui->set_window_text(strText);

         }

         m_strTitle = strText;

      }



      for (int32_t i = 0; i < iItemCount; i++)
      {

         sp(::xml::node) pnodeChild = pnode->child_at(i);

         sp(menu_item) pitemNewChild = canew(menu_item(get_app()));

         pitemNewChild->m_pmenu = m_pmenu;

         pitemNewChild->load_menu(pnodeChild);

         add_item(pitemNewChild);

      }

      return true;

   }


   bool menu_item::create_buttons(menu * pmenu)
   {

      for (int32_t iItem = 0; iItem < m_spitema->get_size(); iItem++)
      {

         menu_item * pitem = m_spitema->element_at(iItem);

         if (pitem->m_pui == NULL)
         {

            pitem->m_pui = m_pmenu->create_menu_button();

         }

         if (pitem->m_pui == NULL)
         {

            return false;

         }

         if (pitem->m_pui->IsWindow())
         {

            pitem->m_pui->DestroyWindow();

         }

         {

            control_descriptor descriptor;

            descriptor.m_puiParent = pmenu;

            descriptor.m_id = pitem->m_id;

            descriptor.m_iItem = iItem;

            if (!pitem->m_pui->create_control(&descriptor))
            {

               return false;

            }

         }

         pitem->m_pui->m_id = pitem->m_id;

         pitem->m_pui->m_pmenuitem = pitem;

         if (!pitem->m_pui->IsWindow())
         {

            return false;

         }

         pitem->m_pmenu = pmenu;

         pitem->m_pui->set_window_text(pitem->m_strTitle);

         if(pmenu->m_bInline)
         {
         
            pitem->create_buttons(pmenu);
            
         }

      }

      return true;

   }

   
   bool menu_item::IsPopup()
   {
         
      return m_spitema.is_set() && m_spitema->get_count() > 0;
         
   }
   
      
   menu_item_ptra::menu_item_ptra(menu_item * pitemParent) :
      ::object(pitemParent->get_app())
   {
         
      m_pitemParent = pitemParent;
         
   }
   
   
   menu_item_ptra::~menu_item_ptra()
   {
         
   }
   
      
   menu_item * menu_item::find(id id)
   {
   
      if(m_spitema.is_null())
      {
            return NULL;
         
      }
      
      return m_spitema->find(id);
   
   }
      
   
   void menu_item::OnAddRef()
   {
   
   }
      
   
   void menu_item::OnRelease()
   {
   
   }
      
   menu_item * menu_item_ptra::find(id id)
   {
   
      menu_item * pitemFind;
      
      for(int32_t i = 0; i < this->get_size(); i++)
      {
      
         menu_item * pitem = element_at(i);
         
         if(pitem->m_id  == id)
         {
         
            return pitem;
            
         }
         
         pitemFind = pitem->find(id);
         
         if(pitemFind != NULL)
         {
            
            return pitemFind;
            
         }
      
      }
      
      return NULL;
   
   }

      

      
} // namespace user
   
