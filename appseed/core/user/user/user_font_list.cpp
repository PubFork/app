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
      ::user::interaction(papp)
   {

      font_list_common_construct();

   }


   void font_list::font_list_common_construct()
   {

      m_scrolldataVert.m_bScrollEnable = true;

   }


   font_list::~font_list()
   {

      try
      {

         if(m_pfontlistdata.is_set())
         {

            m_pfontlistdata->m_uiptra.remove(this);

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
      
      attach_font_list_data(Session.m_pfontlistdata);

      SetTimer(timer_update_font, 10 * 1000, NULL);

   }
   

   void font_list::_001OnTimer(::timer * ptimer)
   {

      if (ptimer->m_nIDEvent == timer_update_font)
      {

         if (m_pfontlistdata.is_set())
         {

            m_pfontlistdata->update();

         }

      }

   }
   

   void font_list::_001OnLButtonDown(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      point pt = pmouse->m_pt;

      ScreenToClient(&pt);

      index iSel = hit_test(pt);

      if (iSel != m_pfontlistdata->m_iSel)
      {

         m_pfontlistdata->m_iSel = (index) (iSel);

         ::user::control_event ev;

         ev.m_puie = this;

         ev.m_eevent = ::user::event_after_change_cur_sel;

         ev.m_actioncontext = ::action::source_user;

         BaseOnControlEvent(&ev);

      }

   }
   

   void font_list::_001OnMouseMove(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      point pt = pmouse->m_pt;

      ScreenToClient(&pt);

      auto iHover = hit_test(pt);

      if (m_pfontlistdata->m_iHover != iHover)
      {

         m_pfontlistdata->m_iHover = iHover;

         ::user::control_event ev;
         ev.m_puie = this;
         ev.m_eevent = ::user::event_after_change_cur_hover;
         ev.m_actioncontext = ::action::source_user;

         BaseOnControlEvent(&ev);

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

      if (m_pfontlistdata == NULL)
      {

         return;

      }

      synch_lock sl(m_pfontlistdata->m_pmutex);

      if (m_pfontlistdata->m_strText != m_pfontlistdata->m_strTextLayout)
      {

         m_pfontlistdata->m_strTextLayout = m_pfontlistdata->m_strText;

         on_layout();

      }

      m_pfontlistdata->_001OnDraw(pgraphics);

   }


   void font_list::attach_font_list_data(::visual::font_list_data * pdata)
   {

      m_pfontlistdata = pdata;

      pdata->m_uiptra.add(this);

   }


   void font_list::on_layout()
   {

      rect rectClient;

      GetClientRect(rectClient);

      if (rectClient.area() <= 0)
      {

         return;

      }

      if (m_pfontlistdata.is_null())
      {

         return;

      }

      synch_lock sl(m_pfontlistdata->m_pmutex);

      ::rect rectFontList;

      GetClientRect(rectFontList);

      rectFontList.right -= GetSystemMetrics(SM_CXVSCROLL);

      m_pfontlistdata->m_rectClient = rectFontList;

      m_pfontlistdata->on_layout(&m_sizeTotal);

      ::user::control::on_layout();

   }


   string font_list::get_cur_sel_face_name()
   {

      auto iSel = get_cur_sel();

      if (iSel < 0)
      {

         return "";

      }

      return m_pfontlistdata->m_itemptra[iSel]->m_strFont;

   }


   string font_list::get_cur_hover_face_name()
   {

      auto iHover = get_cur_hover();

      if (iHover < 0)
      {

         return "";

      }

      return m_pfontlistdata->m_itemptra[iHover]->m_strFont;

   }


   index font_list::get_cur_sel()
   {

      if (m_pfontlistdata->m_iSel < 0)
      {

         return -1;

      }

      if (m_pfontlistdata->m_iSel >= m_pfontlistdata->m_itemptra.get_count())
      {

         return -1;

      }

      return m_pfontlistdata->m_iSel;

   }


   index font_list::get_cur_hover()
   {

      if (m_pfontlistdata->m_iHover < 0)
      {

         return -1;

      }

      if (m_pfontlistdata->m_iHover >= m_pfontlistdata->m_itemptra.get_count())
      {

         return -1;

      }

      return m_pfontlistdata->m_iHover;

   }
   

   index font_list::hit_test(point pt)
   {

      pt += m_ptScrollPassword1;

      return m_pfontlistdata->hit_test(pt);

   }


   bool font_list::set_sel_by_name(string str)
   {

      index iSel = m_pfontlistdata->find_name(str);

      if (iSel < 0)
         return false;

      m_pfontlistdata->m_iSel = iSel;

      return true;

   }


   bool font_list::get_color(COLORREF & cr, e_color ecolor, ::user::interaction * pui)
   {

      if (ecolor == color_background)
      {

         cr = ARGB(128, 255, 255, 255);

         return true;

      }

      return control::get_color(cr, ecolor, pui);

   }


} // namespace user


