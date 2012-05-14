#include "framework.h"


namespace html
{

   namespace impl
   {

      input_check_box::input_check_box(data * pdata)
      {
         m_pcheckbox = new ::user::check_box(pdata->get_app());
      }

      input_check_box::~input_check_box()
      {
         delete m_pcheckbox;
      }

      void input_check_box::implement_phase1(data * pdata, ::html::elemental * pelemental)
      {
         if(!m_pcheckbox->IsWindow())
         {
            m_pcheckbox->create(pdata->m_pguie, 100);
            pdata->on_create_interaction(m_pcheckbox);
         }
         elemental::implement_phase1(pdata, pelemental);
         string strValue = pelemental->m_pbase->tag()->get_attr_value("value");
         if(strValue.CompareNoCase("checked") == 0)
         {
            m_pcheckbox->_001SetCheck(check::checked, false);
         }
         else
         {
            m_pcheckbox->_001SetCheck(check::unchecked, false);
         }
         
         m_pcheckbox->m_id = pelemental->m_pbase->tag()->get_attr_value("id");
         m_pcheckbox->m_strName = pelemental->m_pbase->tag()->get_attr_value("name");
         m_pcheckbox->m_id = pelemental->m_pbase->tag()->get_attr_value("id");
         if(pdata->m_pform != NULL
            && pdata->m_pform->m_pcallback != NULL)
         {
            ::user::control_event ev;
            ev.m_puie = m_pcheckbox;
            ev.m_bUser = false;
            ev.m_eevent = ::user::event_initialize_control;
            ev.m_uiEvent = 0;
            pdata->m_pform->m_pcallback->BaseOnControlEvent(pdata->m_pform, &ev);
         }
      }

      void input_check_box::layout_phase3(data * pdata)
      {
         elemental::layout_phase3(pdata);
         point pointBound = get_bound_point();
         m_size.cx = 200;
         m_size.cy = 23;
         m_pt.y += pdata->m_layoutstate.m_cy;
         pdata->m_layoutstate.m_y    = get_y();
         pdata->m_layoutstate.m_cy   = 23;
         pdata->m_layoutstate.m_x    += pdata->m_layoutstate.m_cx;
         pdata->m_layoutstate.m_cx   = 23;
         m_pcheckbox->SetWindowPos(NULL, m_pt.x, m_pt.y, m_size.cx, m_size.cy, SWP_NOREDRAW);
      }

      void input_check_box::_001OnDraw(data * pdata)
      {
         //rect rectWindow;
         //m_pcheckbox->GetWindowRect(rectWindow);
         point ptPreviousViewportOrg = pdata->m_pdc->GetViewportOrg();
         pdata->m_pdc->OffsetViewportOrg(m_pt.x, m_pt.y);
         m_pcheckbox->_001OnDraw(pdata->m_pdc);
         pdata->m_pdc->SetViewportOrg(ptPreviousViewportOrg);
      }

      void input_check_box::on_change_layout(data * pdata)
      {
         UNREFERENCED_PARAMETER(pdata);
         m_pcheckbox->SetWindowPos(NULL, m_pt.x, m_pt.y, m_size.cx, m_size.cy, SWP_NOREDRAW);
      }

   }

}