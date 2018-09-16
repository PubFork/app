#include "framework.h"
//#include <math.h>





namespace user
{


   font_list::font_list()
   {

      font_list_common_construct();

   }


   font_list::font_list(::aura::application * papp) :
      object(papp),
      ::user::combo_list(papp),
      ::user::interaction(papp)
   {

      font_list_common_construct();

   }


   void font_list::font_list_common_construct()
   {

      m_strView = "font_sel";
      m_layout.m_puserstyle = this;
      m_econtroltype = control_type_list;
      m_scrolldataVert.m_bScrollEnable = true;

   }


   font_list::~font_list()
   {

      try
      {

         if(m_pfontlist.is_set())
         {

            m_pfontlist->m_uiptra.remove(this);

         }

      }
      catch (...)
      {

      }

   }


   void font_list::install_message_routing(::message::sender * psender)
   {

      ::user::box::install_message_routing(psender);

      IGUI_MSG_LINK(WM_CREATE, psender, this, &font_list::_001OnCreate);
      IGUI_MSG_LINK(WM_LBUTTONDOWN, psender, this, &font_list::_001OnLButtonDown);
      IGUI_MSG_LINK(WM_MOUSEMOVE, psender, this, &font_list::_001OnMouseMove);

   }


   void font_list::_001OnCreate(::message::message * pobj)
   {

      SCAST_PTR(::message::create, pcreate, pobj);

      pcreate->previous();

      if (pcreate->m_bRet)
         return;

      attach_visual_font_list(Session.m_pfontlist);

      update_data(false);

      SetTimer(timer_update_font, 10 * 1000, NULL);

      set_window_text("Font");

   }


   bool font_list::update_data(bool bSaveAndValidate)
   {

      if (bSaveAndValidate)
      {

      }
      else
      {

         if (m_pfontlist.is_set())
         {

            m_pfontlist->update();

            m_pfontlist->defer_update_layout(&m_layout);

         }

      }

      return true;

   }


   void font_list::_001OnTimer(::timer * ptimer)
   {

      if (ptimer->m_nIDEvent == timer_update_font)
      {

         update_data(false);

      }

      ::user::combo_list::_001OnTimer(ptimer);

   }


   void font_list::_001OnLButtonDown(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      point pt = pmouse->m_pt;

      ScreenToClient(&pt);

      index iSel = hit_test(pt);

      if (iSel != m_pfontlist->m_iSel)
      {

         m_pfontlist->m_iSel = (index) (iSel);

         ::user::control_event ev;

         ev.m_puie = this;

         ev.m_eevent = ::user::event_after_change_cur_sel;

         ev.m_actioncontext = ::action::source_user;

         ev.m_iItem = iSel;

         ev.m_id = m_strView;

         on_control_event(&ev);

         pmouse->set_lresult(0);

         pmouse->m_bRet = true;

      }

   }


   void font_list::_001OnMouseMove(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      point pt = pmouse->m_pt;

      ScreenToClient(&pt);

      auto iHover = hit_test(pt);

      if (m_pfontlist->m_iHover != iHover)
      {

         m_pfontlist->m_iHover = iHover;

         ::user::control_event ev;

         ev.m_puie = this;

         ev.m_eevent = ::user::event_after_change_cur_hover;

         ev.m_actioncontext = ::action::source_user;

         ev.m_id = m_strView;

         on_control_event(&ev);

         set_need_redraw();

      }

   }


   void font_list::on_update(::user::impact * pSender, LPARAM lHint, object* phint)
   {

      if (lHint == 0)
      {

      }
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(lHint);
      UNREFERENCED_PARAMETER(phint);

   }


   void font_list::_001OnNcDraw(::draw2d::graphics * pgraphics)
   {

      ::user::control::_001OnNcDraw(pgraphics);

   }


   void font_list::_001OnDraw(::draw2d::graphics * pgraphics)
   {

      if (m_pfontlist == NULL)
      {

         return;

      }

      synch_lock sl(m_pfontlist->m_pmutex);

      if (m_pfontlist->m_strText != m_pfontlist->m_strTextLayout)
      {

         m_pfontlist->m_strTextLayout = m_pfontlist->m_strText;

         on_layout();

      }

      m_pfontlist->_001OnDraw(pgraphics, &m_layout);

   }


   void font_list::attach_visual_font_list(::visual::font_list * pdata)
   {

      m_pfontlist = pdata;

      pdata->m_uiptra.add(this);

   }


   void font_list::query_full_size(LPSIZE lpsize)
   {

      m_pfontlist->on_layout(&m_layout);

      *lpsize = m_layout.m_size + ::size(
                GetSystemMetrics(SM_CXVSCROLL),
                GetSystemMetrics(SM_CYHSCROLL));

   }


   void font_list::on_layout()
   {

      rect rectClient;

      GetClientRect(rectClient);

      if (rectClient.area() <= 0)
      {

         return;

      }

      if (m_pfontlist.is_null())
      {

         return;

      }

      synch_lock sl(m_pfontlist->m_pmutex);

      ::rect rectFontList;

      GetClientRect(rectFontList);

      rectFontList.right -= GetSystemMetrics(SM_CXVSCROLL);

      m_pfontlist->m_rectClient = rectFontList;

      m_pfontlist->defer_update_layout(&m_layout);

      m_sizeTotal = m_layout.m_size -
                    ::size(
                    ::GetSystemMetrics(SM_CXVSCROLL),
                    ::GetSystemMetrics(SM_CYHSCROLL));

      ::user::control::on_layout();

   }


   string font_list::get_cur_sel_face_name()
   {

      auto iSel = get_cur_sel();

      if (iSel < 0)
      {

         return "";

      }

      return m_layout[iSel]->m_strFont;

   }


   string font_list::get_cur_hover_face_name()
   {

      auto iHover = get_cur_hover();

      if (iHover < 0)
      {

         return "";

      }

      return m_layout[iHover]->m_strFont;

   }


   index font_list::get_cur_sel()
   {

      if (m_pfontlist->m_iSel < 0)
      {

         return -1;

      }

      if (m_pfontlist->m_iSel >= m_layout.get_count())
      {

         return -1;

      }

      return m_pfontlist->m_iSel;

   }


   index font_list::get_cur_hover()
   {

      if (m_pfontlist->m_iHover < 0)
      {

         return -1;

      }

      if (m_pfontlist->m_iHover >= m_layout.get_count())
      {

         return -1;

      }

      return m_pfontlist->m_iHover;

   }


   index font_list::hit_test(point pt)
   {

      pt += m_ptScrollPassword1;

      return m_pfontlist->hit_test(pt, &m_layout);

   }


   bool font_list::set_sel_by_name(string str)
   {

      index iSel = m_pfontlist->find_name(str, &m_layout);

      if (iSel < 0)
         return false;

      m_pfontlist->m_iSel = iSel;

      return true;

   }


} // namespace user


