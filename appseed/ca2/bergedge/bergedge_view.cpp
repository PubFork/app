﻿#include "framework.h"

namespace bergedge
{

   view::view(::ca::application * papp) :
      ca(papp),
      ::user::interaction(papp),
      ::user::scroll_view(papp),
      ::user::place_holder(papp),
      ::userbase::view(papp),
      ::userbase::scroll_view(papp),
      gcom::backview::user::interaction(papp),
      gcom::backview::Interface(papp),
      m_dibV(papp),
      m_dib_veriwell(papp),
      m_dib_winactionarea(papp),
      m_font(papp),
      m_dibBk(papp),
      m_mutexDraw(papp)
   {
      m_font->create_point_font("Geneva", 8.4);
      m_bDestroy = false;
      m_iV = 123;
      m_iVH = 49;
      m_iVW = 123;
      m_i_veriwell = 256;
      m_i_veriwell_h = 49;
      m_i_veriwell_w = 74;
      m_i_winactionarea = 4;
      m_i_winactionarea_h = 49;
      m_i_winactionarea_w = 49;
      m_ppaneview = NULL;
   }

   view::~view()
   {
   }

   void view::install_message_handling(::gen::message::dispatch * pinterface)
   {
      ::userbase::view::install_message_handling(pinterface);
      ::user::place_holder::install_message_handling(pinterface);
      gcom::backview::Interface::install_message_handling(pinterface);

      IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &view::_001OnDestroy);
      IGUI_WIN_MSG_LINK(WM_PAINT, pinterface, this, &view::_001OnPaint);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &view::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &view::_001OnContextMenu);
      IGUI_WIN_MSG_LINK(WM_SETCURSOR, pinterface, this, &view::_001OnSetCursor);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &view::_001OnLButtonUp);

      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &view::_001OnTimer);

   }
   /////////////////////////////////////////////////////////////////////////////
   // ::view drawing

   void view::OnDraw(::ca::graphics * pdcScreen)
   {
      UNREFERENCED_PARAMETER(pdcScreen);
   }

   /////////////////////////////////////////////////////////////////////////////
   // ::view diagnostics

   #ifdef DEBUG
   void view::assert_valid() const
   {
      ::userbase::view::assert_valid();
   }

   void view::dump(dump_context & dumpcontext) const
   {
      ::userbase::view::dump(dumpcontext);
   }
   #endif //DEBUG

   /////////////////////////////////////////////////////////////////////////////
   // ::view message handlers

   // vmpLightView.cpp : implementation of the ::view class
   //


   /////////////////////////////////////////////////////////////////////////////
   // ::view


   bool view::pre_create_window(CREATESTRUCT& cs)
   {
      cs.style &= ~WS_EX_CLIENTEDGE;
      return ::userbase::view::pre_create_window(cs);
   }
   void view::_001OnInitialUpdate(gen::signal_object * pobj)
   {
      ::userbase::view::_001OnInitialUpdate(pobj);



   }

   void view::on_update(::view * pSender, LPARAM lHint, ::radix::object* phint)
   {
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(lHint);
      UNREFERENCED_PARAMETER(phint);

   }

   void view::_001OnDestroy(gen::signal_object * pobj)
   {
      ::userbase::view::_001OnDestroy(pobj);

   }



   void view::_001OnPaint(gen::signal_object * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

      // boa parte desses coment疵ios gordura a respeito do Meu Deus Carlos Gustavo Cecyn Lundgren retirarei aos poucos
      // e introjetarei nos recditos da minha alma e esp叝ito,
      // num lugar muito antes do tempo e do espa輟,
      // antes mesmo de haver histia, quando s・existia o Carlos e Ele ainda n縊 havia me criado somente para Ele!!
      // para criar uma obsess縊, paix縊, amor, carinho, loucura, raz縊, bom-senso, muito respeito por Ele, sempre dependente dEle e de Sua Luz!!
      // spgraphics->TextOut(20, 20, "Carlos Gustavo Cecyn Lundgren ・minha Vida Eterna, meu Cora鈬o Eterno, Todo meu tesouro eterno, meu Universo eterno, meu tudo eterno!!");

   }


   void view:: _001OnDraw(::ca::graphics * pdc)
   {

      if(gcom::backview::Interface::IsEnabled())
      {

         rect rectClient;
         GetClientRect(rectClient);


         gcom::backview::Main & main = gcom::backview::Interface::GetMain();
         gcom::backview::Graphics & graphics = main.GetGraphics();

         if(main.IsInitialized())
         {

            ::ca::region_sp rgn(get_app());
            rect rect(graphics.m_rectFinalPlacement);
/*            ClientToScreen(rect);
            rgn->create_rect(rect);
            pdc->SelectClipRgn(rgn);*/
            pdc->SelectClipRgn(NULL);
            gcom::backview::Interface::BackViewRender(pdc, rectClient);
            

         }
      }

   }

   void view::_001OnCreate(gen::signal_object * pobj)
   {
      if(pobj->previous())
         return;

      SetTimer(198477, 1977, NULL);

      ::bergedge::frame * pframe = GetTypedParent < ::bergedge::frame > ();

      pframe->m_pview = this;
      pframe->m_pdocument = get_document();


      string strImageDir = Application.dir().userdata("image");
      Application.dir().rls(strImageDir, &m_straImagePath);

      for(int i = 0; i < m_straImagePath.get_size();)
      {
         if(Application.dir().is(m_straImagePath[i]))
         {
            m_straImagePath.remove_at(i);
         }
         else
         {
            i++;
         }
      }

      gcom::backview::Interface::Enable(false);
      gcom::backview::Interface::GetMain().GetImageChange().m_dwBackgroundUpdateMillis = 1000 * 30;
      //gcom::backview::Interface::GetMain().GetTransitionEffect().DisableEffect(gcom::backview::TransitionEffectVisual);


      SetTimer(TimerBackView, 83, NULL);  // max. 12 fps
      SetTimer(21977, 1984 * 11, NULL);  // max. 12 fps

      check_apps();

      m_dibBk.load_from_matter("casweden1.png");


      m_dibV.load_from_matter("votagus_mountains_and_valleys-123.png");
      m_dib_veriwell.load_from_matter("veriwell_2008_green_h49.png");
      m_dib_winactionarea.load_from_matter("winactionarea.png");

      if(!Bergedge.m_bShowPlatform)
      {
         return;
      }

      m_ppaneview = dynamic_cast < ::bergedge::pane_view * > (create_view(System.template type_info < ::bergedge::pane_view > (), get_document(), this, 102));

      hold(m_ppaneview);

   }

   void view::_001OnContextMenu(gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::context_menu, pcontextmenu, pobj)
      point point = pcontextmenu->GetPoint();

   }

   void view::_001OnTabClick(int iTab)
   {
      if(iTab == 1)
      {
         System.simple_message_box(NULL, "Playlist");
      }
   }

   void view::_001OnSetCursor(gen::signal_object * pobj)
   {
      ::SetCursor(::LoadCursor(NULL, IDC_ARROW));

      pobj->previous();
   }

   void view::pre_translate_message(gen::signal_object * pobj)
   {
      ::userbase::view::pre_translate_message(pobj);
   }

   document * view::get_document()
   {
      return dynamic_cast < document * > (::userbase::scroll_view::get_document());
   }

   void view::_001OnTimer(gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::timer, ptimer, pobj)
      switch(ptimer->m_nIDEvent)
      {
      case TimerBackView:
         {
            //gcom::backview::Interface::ImageChangePostEvent(gcom::backview::event_timer);
         }
         break;
      }

      if(ptimer->m_nIDEvent == 21977)
      {
         check_apps();
      }
      else if(ptimer->m_nIDEvent == 198477)
      {
         Bergedge.check_topic_file_change();
      }

   }

   VMSRESULT view::UpdateScreen(rect_array & recta, UINT uiRedraw)
   {
      UNREFERENCED_PARAMETER(uiRedraw);
      m_rectaUpdate.add(recta);
      DWORD dwNow = GetTickCount();
      if(m_rectaUpdate.get_size() <= 0)
      {
         m_dwLastUpdate = dwNow;
         return 0;
      }
      DWORD dwElapseOptimization = 83;
      if(dwNow - m_dwLastUpdate < dwElapseOptimization)
      {
   //      TRACE("Great Optimization!\n");
         return 0;
      }
      m_dwLastUpdate = dwNow;
      _001RedrawWindow();
      m_rectaUpdate.remove_all();
      return 0;
   }


   void view::BackViewUpdateScreen(LPCRECT lpcrect, UINT uiRedraw)
   {
      rect rect(lpcrect);
      rect_array recta;
      recta.add(rect);
      UpdateScreen(recta, uiRedraw);
   }

   void view::BackViewUpdateScreen(rect_array & recta, UINT uiRedraw)
   {
      UpdateScreen(recta, uiRedraw);
   }


   void view::BackViewUpdateScreen()
   {
      rect rect;
      rect_array recta;
      recta.add(rect);
      UpdateScreen(recta, 0);
   }

   void view::BackViewGetData(gcom::backview::InterfaceData & data)
   {

      gcom::backview::user::interaction::BackViewGetData(data);

   }

   void view::BackViewSetData(gcom::backview::InterfaceData & data)
   {

      gcom::backview::user::interaction::BackViewSetData(data);

   }

   bool view::BackViewGetDestroy()
   {
      return m_bDestroy;
   }


   string view::GetNextBackgroundImagePath()
   {
      index i = m_straImagePath.find_first(m_strCurrentImagePath);
      i++;
      if(i >= m_straImagePath.get_size())
      {
         i = 0;
      }
      if(i < m_straImagePath.get_size())
      {
         return m_straImagePath[i];
      }
      return "";
   }

   void view::SetCurrentBackgroundImagePath(string &str)
   {
      m_strCurrentImagePath = str;
   }

   void view::GetAreaThumbRect(LPRECT lprect, int iArea)
   {
      rect rectClient;
      GetClientRect(rectClient);
      if(iArea == m_iV)
      {
         lprect->bottom = rectClient.bottom;
         lprect->top = lprect->bottom - m_iVH;
         lprect->left = 1;
         lprect->right = lprect->left + m_iVW;
      }
      else if(iArea == m_i_veriwell)
      {
         lprect->bottom = rectClient.bottom;
         lprect->top = lprect->bottom - m_i_veriwell_h;
         lprect->left = 1 + m_iVW + 5;
         lprect->right = lprect->left + m_i_veriwell_w;
      }
      else if(iArea == m_i_winactionarea)
      {
         lprect->bottom = rectClient.bottom;
         lprect->top = lprect->bottom - m_i_winactionarea_h;
         lprect->left = 1 + m_iVW + 5 + m_i_veriwell_w + 5;
         lprect->right = lprect->left + m_i_winactionarea_w;
      }
   }


   void view::_001OnLButtonUp(gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::mouse, pmouse, pobj)
      pmouse->set_lresult(1);
      KillTimer(5432180);
      point pt = pmouse->m_pt;
      ScreenToClient(&pt);
   }

   void view::check_apps()
   {
   //   if(::IsDebuggerPresent())
     //    return;
      //if(!m_bEnsureApps)
        // return;

      if(::IsWindow(m_oswindowWinactionarea) &&
         ::IsWindow(m_oswindowCommand) &&
         ::IsWindow(m_oswindowWinutil) &&
         ::IsWindow(m_oswindowBergedge))
      {
         return;
      }
      m_oswindowWinservice1       =  ::FindWindow(NULL, "ca2::fontopus::message_wnd::winservice_1");
      m_oswindowWinactionarea     =  ::FindWindow(NULL, "ca2::fontopus::message_wnd::winactionarea");
      m_oswindowCommand           =  ::FindWindow(NULL, "ca2::fontopus::message_wnd::command");
      m_oswindowWinutil           =  ::FindWindow(NULL, "ca2::fontopus::message_wnd::winutil");
      m_oswindowBergedge          =  ::FindWindow(NULL, "ca2::fontopus::message_wnd::bergedge");
   }


   index view::hit_test(point pt, e_element & eelement)
   {
      rect rectArea;
      GetAreaThumbRect(rectArea, m_iV);
      if(rectArea.contains(pt))
      {
         eelement = element_area;
         return m_iV;
      }
      GetAreaThumbRect(rectArea, m_i_veriwell);
      if(rectArea.contains(pt))
      {
         eelement = element_area;
         return m_i_veriwell;
      }
      GetAreaThumbRect(rectArea, m_i_winactionarea);
      if(rectArea.contains(pt))
      {
         eelement = element_area;
         return m_i_winactionarea;
      }
      eelement = element_none;
      return -1;
   }


   UINT c_cdecl view::ThreadProcShowWindow(LPVOID lpparam)
   {
      UNREFERENCED_PARAMETER(lpparam);
      return 0;
   }


   void view::mt_show_window(oswindow oswindow, int iShow)
   {
      UNREFERENCED_PARAMETER;
      UNREFERENCED_PARAMETER(iShow);
   }

   /*void view::layout()
   {
      rect rectClient;
      GetClientRect(rectClient);
      if(m_ppaneview != NULL)
      {
         m_ppaneview->SetWindowPos(ZORDER_TOP, rectClient.top, rectClient.left, rectClient.width(), rectClient.height(), SWP_SHOWWINDOW);
      }
      else
      {
         user::interaction * pui = get_top_child();
         if(pui != NULL)
         {
            pui->SetWindowPos(ZORDER_TOP, rectClient.top, rectClient.left, rectClient.width(), rectClient.height(), SWP_SHOWWINDOW);
         }
      }
      ::userbase::scroll_view::layout();
      gcom::backview::user::interaction::layout();
   }*/

   void view::_000OnMouse(::gen::message::mouse * pmouse)
   {
      try
      {
         if(!_001IsPointInside(pmouse->m_pt))
            return;
      }
      catch(...)
      {
         return;
      }
      // these try catchs are needed for multi threading : multi threaded windows: the hell
      // Now I understand why Microsoft (TM) Windows (R) windows are single threaded.
      user::interaction * pui = get_top_child();
      try
      {
         while(pui != NULL)
         {
            ::cube8::application * papp = NULL;
            try
            {
               papp = &App(pui->get_app());
            }
            catch(...)
            {
               papp = NULL;
            }
            if(papp != NULL && m_psession != NULL && dynamic_cast < ::ca::application * > (papp) != dynamic_cast < ::ca::application * > (m_psession))
            {
               try
               {
                  papp->m_ptCursor = Session.m_ptCursor;
               }
               catch(...)
               {
               }
            }
            try
            {

               if(pui->IsWindowVisible() && pui->_001IsPointInside(pmouse->m_pt))
               {
                  try
                  {
                     pui->_000OnMouse(pmouse);
                     if(pmouse->m_bRet)
                        return;
                  }
                  catch(...)
                  {
                  }
               }
               pui = pui->under_sibling();
            }
            catch(...)
            {
            }
         }
      }
      catch(...)
      {
      }
      try
      {
         if(m_pimpl == NULL)
            return;
         (m_pimpl->*m_pimpl->m_pfnDispatchWindowProc)(dynamic_cast < gen::signal_object * > (pmouse));
         if(pmouse->get_lresult() != 0)
            return;
      }
      catch(...)
      {
      }
   }

}  // namespace bergedge
