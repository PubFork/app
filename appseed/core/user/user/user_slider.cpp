#include "framework.h"


namespace user
{


   slider::slider(::aura::application * papp):
      object(papp),
      ::user::interaction(papp)
   {


      m_bSlide = false;

   }

   slider::~slider()
   {
   }


   void slider::install_message_routing(::message::sender * psender)
   {
      ::user::interaction::install_message_routing(psender);
      IGUI_MSG_LINK(WM_CREATE,psender,this,&slider::_001OnCreate);
//      //IGUI_MSG_LINK(WM_TIMER,psender,this,&slider::_001OnTimer);
      IGUI_MSG_LINK(WM_LBUTTONDOWN,psender,this,&slider::_001OnLButtonDown);
      IGUI_MSG_LINK(WM_LBUTTONUP,psender,this,&slider::_001OnLButtonUp);
      IGUI_MSG_LINK(WM_MOUSEMOVE,psender,this,&slider::_001OnMouseMove);
   }

   void slider::_001OnCreate(::message::message * pobj)
   {

      pobj->previous();

      UNREFERENCED_PARAMETER(pobj);

   }

   void slider::_001OnTimer(::timer * ptimer)
   {

      ::user::interaction::_001OnTimer(ptimer);


   }


   void slider::_001OnLButtonDown(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse,pmouse,pobj);

      //rect rect;

      //get_slider_rect(rect);

      //point pt(pmouse->m_pt);

      //ScreenToClient(&pt);

      //if(rect.contains(pt))
      //{

      SetCapture();

      m_bSlide = true;

      m_pscalar->set_rate(get_slide_rate(), scalar_slide);

      RedrawWindow();

      pmouse->m_bRet = true;

      pmouse->set_lresult(1);

      //   pmouse->m_bRet = true;

      //   pmouse->set_lresult(1);

      //}

   }

   void slider::_001OnLButtonUp(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse,pmouse,pobj);

      if(m_bSlide)
      {

         ReleaseCapture();

         m_bSlide = false;

         m_pscalar->set_rate(get_slide_rate(), scalar_set);

         RedrawWindow();

         pmouse->m_bRet = true;

         pmouse->set_lresult(1);

      }

   }


   void slider::_001OnMouseMove(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse,pmouse,pobj);

      if(m_bSlide)
      {

         m_pscalar->set_rate(get_slide_rate(), scalar_slide);

         RedrawWindow();

         pmouse->m_bRet = true;

         pmouse->set_lresult(1);

      }

   }



   double slider::get_slide_rate()
   {

      double dScalar = m_pscalar->get_rate();

      point pt;

      Session.get_cursor_pos(&pt);

      ScreenToClient(&pt);

      ::rect r;

      GetClientRect(r);

      if(r.width() != 0)
      {

         dScalar = (double) (pt.x - r.left) / (double) r.width();

      }

      dScalar = MIN(1.0, MAX(0.0, dScalar));

      return dScalar;

   }


   void slider::set_scalar(scalar_base * pscalar)
   {

      m_pscalar = pscalar;

   }


   void slider::set_rate(double dRate)
   {

      if(dRate < 0.0)
         dRate = 0.0;
      else if(dRate > 1.0)
         dRate = 1.0;

      m_pscalar->set_rate(dRate, scalar_set);

      RedrawWindow();

   }


   void slider::_001OnDraw(::draw2d::graphics * pgraphics)
   {



      if(m_bSlide)
      {

         m_dRate = get_slide_rate();

      }
      else
      {

         m_dRate = m_pscalar->get_rate();

      }

      rect rectClient;

      GetClientRect(rectClient);

      class imaging & imaging = Application.imaging();

      byte bAlpha1 = (byte) (128.0* get_alpha());

      imaging.color_blend(pgraphics, rectClient, RGB(250,255,255), bAlpha1);

      rect rect;

      get_slider_rect(rect);

      byte bAlpha = (byte) (220.0* get_alpha());

      pgraphics->draw3d_rect(rect,ARGB(bAlpha / 255,84 + 23,77+23,184+ 23),ARGB(bAlpha,84,77,184));
      rect.deflate(1,1);
      pgraphics->draw3d_rect(rect,ARGB(bAlpha / 255,177 -13- 49,184 -13- 49,200 - 49),ARGB(bAlpha,177-49 - 49,184-49 - 49,200-49));
      rect.deflate(1,1);
      pgraphics->draw3d_rect(rect,ARGB(bAlpha / 255,84+23,77+23,184+23),ARGB(bAlpha,84,77,184));
      rect.deflate(1,1);
      pgraphics->fill_solid_rect(rect,ARGB(bAlpha1,84 + 49,77 + 49,184 + 49));
      //if(m_bSlide)
      //{
      //   pgraphics->move_to(rect.center());
      //   POINT pt;
      //   Session.get_cursor_pos(&pt);
      //   ScreenToClient(&pt);
      //   pgraphics->line_to(pt);
      //}
   }


   void slider::get_slider_rect(rect & rect)
   {

      class rect rectClient;

      GetClientRect(rectClient);

      int32_t iWidth = 16;

      rect.top = rectClient.top;
      rect.bottom = rectClient.bottom;
      rect.left = (LONG)MIN(rectClient.right,m_dRate * (rectClient.width() - iWidth));
      rect.right = (LONG)MIN(rectClient.right,m_dRate * ((rectClient.width() - iWidth)) + iWidth);


   }


} // namespace user























































