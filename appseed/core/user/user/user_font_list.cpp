#include "framework.h"


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
      m_puserstyle = this;
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

      ::user::control::install_message_routing(psender);

      IGUI_MSG_LINK(WM_CREATE, psender, this, &font_list::_001OnCreate);
      IGUI_MSG_LINK(WM_LBUTTONDOWN, psender, this, &font_list::_001OnLButtonDown);
      IGUI_MSG_LINK(WM_MOUSEMOVE, psender, this, &font_list::_001OnMouseMove);
      IGUI_MSG_LINK(WM_CLOSE, psender, this, &font_list::_001OnClose);

   }


   void font_list::_001OnCreate(::message::message * pobj)
   {

      SCAST_PTR(::message::create, pcreate, pobj);

      pcreate->previous();

      if (pcreate->m_bRet)
         return;

      Session.will_use_view_hint("font_sel");

      set_window_text("Font");

   }


   void font_list::set_font_list_type(::visual::font_list::e_type etype)
   {

      if (etype == ::visual::font_list::type_single_column)
      {

         m_pfontlist = Session.get_single_column_font_list();

         m_pfontlist->m_uiptra.add_unique(this);

      }
      else if (etype == ::visual::font_list::type_wide)
      {

         if (m_pfontlist.is_null() || m_pfontlist->m_etype != ::visual::font_list::type_wide)
         {

            m_pfontlist = canew(::visual::font_list(get_app()));

            m_pfontlist->m_etype = ::visual::font_list::type_wide;

         }

         m_pfontlist->m_uiptra.add_unique(this);

      }
      else
      {

         _throw(todo(get_app()));

      }

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

            m_pfontlist->layout(false);

         }

      }

      return true;

   }


   void font_list::_001OnTimer(::timer * ptimer)
   {

      ::user::combo_list::_001OnTimer(ptimer);

   }


   void font_list::_001OnLButtonDown(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      point pt = pmouse->m_pt;

      e_element eelement = element_none;

      index iSel = hit_test(pt, eelement);

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

      e_element eelement = element_none;

      auto iHover = hit_test(pt, eelement);

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

      m_pfontlist->_001OnDraw(pgraphics);

   }


   void font_list::query_full_size(LPSIZE lpsize)
   {

      *lpsize = m_pfontlist->m_size + ::size(
                GetSystemMetrics(SM_CXVSCROLL),
                GetSystemMetrics(SM_CYHSCROLL));

   }


   void font_list::font_list_update_layout()
   {

      synch_lock sl(m_pmutex);

      m_pfontlist->update();

   }




   void font_list::on_layout()
   {

      rect rectFontList;

      GetClientRect(rectFontList);

      if (m_pfontlist.is_null())
      {

         return;

      }

      synch_lock sl(m_pfontlist->m_pmutex);

      rectFontList.right -= GetSystemMetrics(SM_CXVSCROLL);

      m_pfontlist->m_rectClient = rectFontList;

      m_pfontlist->layout(false);

      m_sizeTotal = m_pfontlist->m_size -
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

      synch_lock sl(m_pfontlist->m_pmutex);

      return m_pfontlist->m_itema[iSel]->m_strFont;

   }


   string font_list::get_cur_hover_face_name()
   {

      auto iHover = get_cur_hover();

      if (iHover < 0)
      {

         return "";

      }

      synch_lock sl(m_pfontlist->m_pmutex);

      return m_pfontlist->m_itema[iHover]->m_strFont;

   }


   index font_list::get_cur_sel()
   {

      synch_lock sl(m_pfontlist->m_pmutex);

      if (m_pfontlist->m_iSel < 0)
      {

         return -1;

      }

      if (m_pfontlist->m_iSel >= m_pfontlist->m_itema.get_count())
      {

         return -1;

      }

      return m_pfontlist->m_iSel;

   }


   index font_list::get_cur_hover()
   {

      synch_lock sl(m_pfontlist->m_pmutex);

      if (m_pfontlist->m_iHover < 0)
      {

         return -1;

      }

      if (m_pfontlist->m_iHover >= m_pfontlist->m_itema.get_count())
      {

         return -1;

      }

      return m_pfontlist->m_iHover;

   }


   index font_list::hit_test(point pt, e_element & eelement)
   {

      ScreenToClient(&pt);

      pt += m_ptScrollPassword1;

      index iItem = m_pfontlist->hit_test(pt);

      if(iItem < 0)
      {

         eelement = element_none;

         return iItem;

      }

      eelement = element_item;

      return iItem;

   }


   bool font_list::set_sel_by_name(string str)
   {

      index iSel = m_pfontlist->find_name(str);

      if (iSel < 0)
      {

         return false;

      }

      m_pfontlist->m_iSel = iSel;

      return true;

   }


   void font_list::on_change_combo_sel(index iSel)
   {

      if (m_pfontlist.is_set())
      {

         m_pfontlist->m_iSel = iSel;

      }

   }


   void font_list::_001OnClose(::message::message * pobj)
   {

      pobj->m_bRet = true;

      ShowWindow(SW_HIDE);

   }


} // namespace user


