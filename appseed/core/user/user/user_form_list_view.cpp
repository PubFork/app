#include "framework.h"


namespace user
{


   form_list_view::form_list_view()
   {

   }


   form_list_view::~form_list_view()
   {

   }


   void form_list_view::install_message_routing(::message::sender * psender)
   {

      ::user::form_view::install_message_routing(psender);
      ::user::form_list::install_message_routing(psender);

   }


   void form_list_view::on_update(::user::impact * pSender,LPARAM lHint,object* phint)
   {

      ::user::form_view::on_update(pSender, lHint, phint);

      ::user::list_view::on_update(pSender, lHint, phint);


      if(phint != NULL)
      {
         
         ::user::form_update_hint * puh = dynamic_cast <::user::form_update_hint *> (phint);

         if(puh != NULL)
         {

            if(puh->m_etype == ::user::form_update_hint::type_browse)
            {

               if(!puh->m_strForm.is_empty())
               {

                  string str;

                  str = Application.dir().matter(puh->m_strForm);

                  if(get_document()->on_open_document(str))
                  {

                     m_strPath = puh->m_strForm;

                  }

               }

            }
            else if(puh->m_etype == ::user::form_update_hint::type_get_form_view)
            {

               puh->m_pform = this;

            }
         }
         else
         {
            //html_view_update_hint * puh = dynamic_cast < html_view_update_hint * > (phint);
            //if(puh != NULL)
            //{
            //   if(puh->m_etype == html_view_update_hint::type_document_complete)
            //   {
            //      for(int32_t i = 0; i < get_html_data()->m_propertyset.m_propertya.get_count(); i++)
            //      {
            //         html::elemental * pelemental = get_html_data()->get_element_by_id(get_html_data()->m_propertyset.m_propertya[i]->name());
            //         if(pelemental != NULL)
            //         {
            //            pelemental->set_string(get_html_data()->m_propertyset.m_propertya[i]->get_string(), ::action::source_data);
            //         }
            //      }
            //   }

            //   {

            //      sp(::draw2d::graphics) dc(allocer());

            //      dc->CreateCompatibleDC(NULL);

            //      get_html_data()->implement(dc);

            //   }
            //   
            //}

         }

      }

      if(m_pcallback != NULL)
      {

         m_pcallback->on_update(this,pSender,lHint,phint);

      }

   }



   bool form_list_view::pre_create_window(::user::create_struct & createstruct)
   {

      if (!::user::list_view::pre_create_window(createstruct))
      {

         return false;

      }

      return true;

   }

   
   void form_list_view::_001OnDraw(::draw2d::graphics * pgraphics)
   {

      ::user::list_view::_001OnDraw(pgraphics);

   }


   void form_list_view::_001OnTimer(::timer * ptimer)
   {

      ::user::list_view::_001OnTimer(ptimer);

      ::user::form_view::_001OnTimer(ptimer);

   }

   void form_list_view::set_viewport_offset(int x, int y)
   {

      ::user::list_view::set_viewport_offset(x, y);

   }

   ::point form_list_view::get_viewport_offset()
   {

      return ::user::list_view::get_viewport_offset();

   }

   ::size form_list_view::get_total_size()
   {

      return ::user::list_view::get_total_size();

   }



} // namespace user







