//
//  userex_view_container.cpp
//  app_veriwell_musical_player
//
//  Created by Camilo Sasuke Tsumanuma on 14/07/18.
//  Copyright © 2018 Camilo Sasuke Tsumanuma. All rights reserved.
//
#include "framework.h"


namespace userex
{


   view_container::view_container(::aura::application * papp) :
      ::object(papp)
   {

      m_sizeTabbedFrame.cx = 800;
      m_sizeTabbedFrame.cy = 300;
      m_ptemplateTab = NULL;

   }


   view_container::~view_container()
   {


   }


   void view_container::assert_valid() const
   {

      ::user::impact::assert_valid();

   }


   void view_container::dump(dump_context & dumpcontext) const
   {

      ::user::impact::dump(dumpcontext);

   }


   void view_container::install_message_routing(::message::sender * psender)
   {

      ::user::impact::install_message_routing(psender);

   }


   void view_container::_001DefaultLayoutView(string strView)
   {

      if (m_mapframe[strView] == NULL)
      {

         return;

      }

      rect rect;

      GetClientRect(rect);

      m_mapframe[strView]->SetWindowPos(
      ZORDER_TOP,
      rect.width() / 4,
      0,
      rect.width() / 2,
      rect.height() / 5,
      SWP_SHOWWINDOW);

   }


   sp(::user::impact) view_container::_001GetView(string strView)
   {

      sp(::user::document) pdoc = get_doc(strView);

      if (pdoc.is_null())
      {

         return NULL;

      }
      else
      {

         return pdoc->get_view();

      }

   }

   void view_container::on_update(::user::impact * pSender, LPARAM lHint, ::object* pHint)
   {

      if (base_class <view_update_hint > ::bases(pHint))
      {

         view_update_hint * puh = dynamic_cast <view_update_hint *> (pHint);

         if (puh->m_etype == view_update_hint::type_attach_view)
         {

            sp(::user::impact) pview = _001GetView(puh->m_strView);

            if (pview != NULL)
            {

               sp(::simple_frame_window) pframe = (pview->GetParentFrame());

               if (pframe != NULL)
               {

                  pframe->create_translucency(::user::element_none, ::user::translucency_present);

                  pframe->m_workset.SetAppearanceTransparency(::user::wndfrm::frame::Transparent);

                  pframe->m_pupdowntarget = this;

                  pframe->m_id = "userex::view::" + puh->m_strView;

                  pframe->WfiDown();

               }

            }

         }

      }

   }


   bool view_container::OnUpDownTargetAttach(::user::wndfrm::frame::WorkSetUpDownInterface * pupdown)
   {

      string strId =pupdown->m_id;

      if (str::begins_ci(strId, "userex::view::"))
      {

         tabfy(pupdown);

         return true;

      }

      return false;

   }


   bool view_container::OnUpDownTargetDetach(::user::wndfrm::frame::WorkSetUpDownInterface * pupdown)
   {

      string strId = pupdown->m_id;

      if (str::begins_ci(strId, "userex::view::"))
      {

         if (m_ptemplateTab != NULL)
         {

            sp(::user::document) pdoc = m_ptemplateTab->get_document(0);

            sp(::userex::pane_tab_view) ptabview = pdoc->get_typed_view < ::userex::pane_tab_view >();

            ptabview->remove_tab_by_id(pupdown->m_id);

            sp(::simple_frame_window) pframe = pupdown;

            pframe->m_workset.m_bSizingEnabled = true;

            pframe->m_workset.m_bMovingEnabled = true;

            pframe->SetParent(NULL);

            pframe->WfiRestore(true);

            if (ptabview->get_tab_count() <= 0)
            {

               m_ptemplateTab->close_all_documents(FALSE);

            }

         }

         return true;

      }

      return false;

   }


   void view_container::tabfy(::user::wndfrm::frame::WorkSetUpDownInterface * pupdown)
   {

      bool bCreateTab = false;

      if (m_ptemplateTab == NULL)
      {

         bCreateTab = true;

         m_ptemplateTab = new user::single_document_template(
         get_app(),
         "main",
         System.type_info < ::user::document >(),
         System.type_info < simple_frame_window >(),
         System.type_info < ::userex::pane_tab_view >());

      }

      sp(::user::document) pdoc = m_ptemplateTab->get_document(0);

      if (pdoc == NULL)
      {

         bCreateTab = true;

         pdoc = m_ptemplateTab->open_document_file(::var::type_null, true, this);

      }

      sp(::userex::pane_tab_view) ptabview = pdoc->get_typed_view < ::userex::pane_tab_view >();

      if (ptabview->get_view_creator() == NULL)
      {

         ptabview->set_view_creator(new ::user::view_creator);

      }



      sp(::simple_frame_window) pframe = (pupdown);

      pframe->m_workset.m_bSizingEnabled = false;

      pframe->m_workset.m_bMovingEnabled = false;

      id id = pupdown->m_id;

      ::user::tab_pane * ppane = ptabview->create_pane_by_id(id);

      string strTitle;

      ::user::interaction * pui = dynamic_cast <::user::interaction *> (pupdown);

      if (pui != NULL)
      {

         pui->get_window_text(strTitle);

      }

      if (strTitle.is_empty())
      {

         strTitle = id;

      }

      ppane->set_title(strTitle);

      ::user::view_creator_data * pcreatordata = ptabview->get_impact(id, false);

      pframe->SetParent(pcreatordata->m_pholder);

      ptabview->set_cur_tab_by_id(id);

      pcreatordata->m_pdoc = pframe->GetActiveDocument();

      pframe->set_need_layout();

      pcreatordata->m_pholder->set_need_layout();

      set_need_layout();

   }


   void view_container::on_layout()
   {

      if (m_ptemplateTab != NULL)
      {

         rect rectTab;

         sp(::user::document) pdoc = m_ptemplateTab->get_document(0);

         if (pdoc != NULL)
         {

            sp(::userex::pane_tab_view) ptabview = pdoc->get_typed_view < ::userex::pane_tab_view >();

            if (ptabview != NULL && ptabview->get_pane_count() > 0)
            {

               simple_frame_window * pframe = ptabview->GetTypedParent < simple_frame_window >();

               pframe->SetWindowPos(ZORDER_TOPMOST, 23, 23, 800, 300, SWP_NOZORDER | SWP_SHOWWINDOW);

               ::user::tab_pane * ppane = ptabview->get_pane_by_id(ptabview->get_cur_tab_id());

               if (ppane != NULL)
               {

                  if (ppane->m_pholder != NULL)
                  {

                     if (ppane->m_pholder->m_uiptraChild.has_elements())
                     {

                        if (ppane->m_pholder->m_uiptraChild[0] != NULL)
                        {

                           if (!ppane->m_pholder->m_uiptraChild[0]->IsWindowVisible())
                           {

                              ppane->m_pholder->m_uiptraChild[0]->ShowWindow(SW_SHOW);

                              ppane->m_pholder->m_uiptraChild[0]->set_need_layout();

                           }

                        }

                     }

                  }

               }

               ptabview->GetParentFrame()->GetWindowRect(rectTab);

               ScreenToClient(rectTab);

            }

         }

      }

   }


   bool view_container::attach(sp(::user::document) pdoc, string strView)
   {

      if (m_mapdoc[strView] != NULL)
      {

         detach_doc(strView);

      }

      m_mapdoc[strView] = pdoc;

      view_update_hint uh;

      uh.m_etype = view_update_hint::type_attach_view;

      uh.m_strView = strView;

      get_document()->update_all_views(NULL, 0, &uh);

      return true;

   }


   sp(::user::document) view_container::get_doc(string strView)
   {

      return m_mapdoc[strView];

   }


   sp(::user::document) view_container::detach_doc(string strView)
   {

      sp(::user::document) pdoc = m_mapdoc[strView];

      if (pdoc != NULL)
      {

         view_update_hint uh;

         uh.m_etype = view_update_hint::type_detach_view;

         uh.m_strView = strView;

         get_document()->update_all_views(NULL, 0, &uh);

         m_mapdoc.remove_key(strView);

      }

      return pdoc;

   }


   bool view_container::_001IsCompactMode()
   {

      return false;


   }


   bool view_container::_001AttachView(string strView)
   {

      if(_001IsCompactMode())
      {

         return true;

      }

      sp(::userex::font_view) pview = _001GetView(strView);

      if(pview.is_null())
      {

         return false;

      }

      m_mapframe[strView] = dynamic_cast < simple_frame_window * > (pview->GetParentFrame());

      m_mapframe[strView]->ShowWindow(SW_HIDE);

      _001DefaultLayoutView(strView);

      return true;

   }


   sp(::user::impact) view_container::_001DetachView(string strView)
   {

      sp(::user::impact) pview = _001GetView(strView);

      if (m_mapframe[strView] == NULL)
      {

         return NULL;

      }

      ASSERT(m_mapframe[strView] != NULL);

      m_mapframe[strView] = NULL;

      return pview;

   }


   void view_container::_001OnView(string strView)
   {

      sp(::user::document) pdoc = get_doc(strView);

      if (pdoc.is_null())
      {

         pdoc = Session.userex()->m_mapimpactsystem[strView]->open_document_file();

         ASSERT(pdoc->m_pviewTopic != NULL);

         pdoc->m_pviewTopic->m_puiViewNotify = this;

         string strTitle;

         pdoc->m_pviewTopic->get_window_text(strTitle);

         pdoc->m_pviewTopic->GetTopLevel()->set_window_text(strTitle);

      }

      attach(pdoc, strView);

   }


   view_update_hint::view_update_hint()
   {

      m_etype = type_none;

   }


   view_update_hint::~view_update_hint()
   {


   }


} // namespace userex



