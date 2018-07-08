#include "framework.h"


namespace flag
{

   void dk(::draw2d::graphics * pgraphics, double x, double y, double w, double h)
   {

      COLORREF crDenmarkRoed = ARGB(255, 200, 16, 46);

      double dx = w / 90.0;

      double dy = h / 70.0;

      pgraphics->fill_solid_rect_dim(x+0, y+0, 90.0 * dx, 70.0 * dy, ARGB(255, 255, 255, 255));

      pgraphics->fill_solid_rect_dim(x+0, y+0, 30.0*dx, 30.0*dy, crDenmarkRoed);

      pgraphics->fill_solid_rect_dim(x + 40.0*dx, y, 50 * dx, 30 * dy, crDenmarkRoed);

      pgraphics->fill_solid_rect_dim(x+0, y + 40.0 * dy, 30.0*dx, 30.0 * dy, crDenmarkRoed);

      pgraphics->fill_solid_rect_dim(x + 40.0*dx, y + 40.0 * dy, 50.0* dx, 30.0 * dy, crDenmarkRoed);

   }


   void gay_with_shades_of_grey(::draw2d::dib * pdib)
   {

      ::count w = pdib->m_size.cx;

      ::count h = pdib->m_size.cy;

      color c;

      double dw = w;

      double dh = h;

      double dS;

      UINT uScan;


      //dS = 1.0 - ((double)j / dh);

      uScan = pdib->m_iScan / sizeof(COLORREF);

      COLORREF * pline;

      for (index i = 0; i < w; i++)
      {

         double dR, dG, dB;

         pline = pdib->m_pcolorref + i;

         double dH = (double)i / (double)dw;

         dH *= 6.0;

         double dA = dH - (double)((int32_t)dH);

         if (dH >= 3.0)
         {
            if (dH >= 4.0)
            {
               if (dH >= 5.0)
               {
                  // 5.0
                  // magenta to red
                  dR = 1.0;
                  dG = 0.0;
                  dB = 1.0 - dA;
               }
               else
               {
                  // 4.0
                  // blue to magenta
                  dR = dA;
                  dG = 0.0;
                  dB = 1.0;
               }
            }
            else
            {
               // 3.0
               // cyan to blue
               dR = 0.0;
               dG = 1.0 - dA;
               dB = 1.0;
            }
         }
         else /// if(dH >= 0.0)
         {
            if (dH >= 2.0)
            {
               // 2
               // green to cyan
               dR = 0.0;
               dG = 1.0;
               dB = dA;
            }
            else // (dH >= 0.0 && dH < 2.0)
            {
               if (dH >= 1.0)
               {
                  // 1
                  // yellow to green
                  dR = 1.0 - dA;
                  dG = 1.0;
                  dB = 0.0;
               }
               else // if(dh >= 0 && dH < 1.0);
               {
                  // 0
                  // red to yellow
                  dR = 1.0;
                  dG = dA;
                  dB = 0.0;
               }
            }
         }

         double dL = 0.5;

         for (index j = 0; j < h; j++)
         {



            double dS = 1.0 - ((double) j / dh);

            double dCMin;
            double dCAdd;
            double dSL = dS * dL;
            if (dL >= 0.5)
            {
               dCMin = dL - dS + dSL;
               dCAdd = 2.0 * dS - 2.0 * dSL;
            }
            else
            {
               dCMin = dL - dSL;
               dCAdd = 2.0 * dSL;
            }


            double _dR = (dCMin + dR * dCAdd);
            double _dG = (dCMin + dG * dCAdd);
            double _dB = (dCMin + dB * dCAdd);

            //BYTE uchR = (BYTE)primitive_color_round(m_dR * 255.0);
            //m_uchG = (BYTE)primitive_color_round(m_dG * 255.0);
            //m_uchB = (BYTE)primitive_color_round(m_dB * 255.0);


            *pline = ARGB(255, BYTE(_dB*255.0), BYTE(_dG*255.0), BYTE(_dR*255.0));

            pline+=uScan;

         }


      }


   }

   void shades_of_luminance(::draw2d::dib * pdib, double dH, double dS)
   {

      ::count w = pdib->m_size.cx;

      ::count h = pdib->m_size.cy;

      color c;

      double dw = w;

      double dh = h;

      UINT uScan;


      //dS = 1.0 - ((double)j / dh);

      uScan = pdib->m_iScan / sizeof(COLORREF);

      COLORREF * pline;

      double dR, dG, dB;

      dH *= 6.0;

      double dA = dH - (double)((int32_t)dH);

      if (dH >= 3.0)
      {
         if (dH >= 4.0)
         {
            if (dH >= 5.0)
            {
               // 5.0
               // magenta to red
               dR = 1.0;
               dG = 0.0;
               dB = 1.0 - dA;
            }
            else
            {
               // 4.0
               // blue to magenta
               dR = dA;
               dG = 0.0;
               dB = 1.0;
            }
         }
         else
         {
            // 3.0
            // cyan to blue
            dR = 0.0;
            dG = 1.0 - dA;
            dB = 1.0;
         }
      }
      else /// if(dH >= 0.0)
      {
         if (dH >= 2.0)
         {
            // 2
            // green to cyan
            dR = 0.0;
            dG = 1.0;
            dB = dA;
         }
         else // (dH >= 0.0 && dH < 2.0)
         {
            if (dH >= 1.0)
            {
               // 1
               // yellow to green
               dR = 1.0 - dA;
               dG = 1.0;
               dB = 0.0;
            }
            else // if(dh >= 0 && dH < 1.0);
            {
               // 0
               // red to yellow
               dR = 1.0;
               dG = dA;
               dB = 0.0;
            }
         }
      }

      for (index j = 0; j < h; j++)
      {
         double dL = (double) j / dh;

         //double dS = 1.0 - ((double)j / dh);

         double dCMin;
         double dCAdd;
         double dSL = dS * dL;
         if (dL >= 0.5)
         {
            dCMin = dL - dS + dSL;
            dCAdd = 2.0 * dS - 2.0 * dSL;
         }
         else
         {
            dCMin = dL - dSL;
            dCAdd = 2.0 * dSL;
         }


         double _dR = (dCMin + dR * dCAdd);
         double _dG = (dCMin + dG * dCAdd);
         double _dB = (dCMin + dB * dCAdd);

         //BYTE uchR = (BYTE)primitive_color_round(m_dR * 255.0);
         //m_uchG = (BYTE)primitive_color_round(m_dG * 255.0);
         //m_uchB = (BYTE)primitive_color_round(m_dB * 255.0);

         pline = pdib->m_pcolorref + uScan * j;
         COLORREF cr = ARGB(255, BYTE(_dR*255.0), BYTE(_dG*255.0), BYTE(_dB*255.0));
         for (index i = 0; i < w; i++)
         {

            *pline = cr;




            pline ++;

         }


      }


   }

}

namespace userex
{


   color_view::color_view(::aura::application * papp) :
      ::object(papp),
      m_editRed(papp),
      m_editGreen(papp),
      m_editBlue(papp),
      m_editHex(papp),
      m_dib(allocer()),
      m_dibTemplate(allocer()),
      m_dibLuminance(allocer())
   {

      m_bLButtonPressed = false;

   }


   color_view::~color_view()
   {


   }


   void color_view::assert_valid() const
   {

      ::user::impact::assert_valid();

   }


   void color_view::dump(dump_context & dumpcontext) const
   {

      ::user::impact::dump(dumpcontext);

   }


   void color_view::install_message_routing(::message::sender * psender)
   {

      ::user::impact::install_message_routing(psender);

      IGUI_MSG_LINK(WM_CREATE, psender, this, &color_view::_001OnCreate);
      IGUI_MSG_LINK(WM_MOUSEMOVE, psender, this, &color_view::_001OnMouseMove);
      IGUI_MSG_LINK(WM_LBUTTONDOWN, psender, this, &color_view::_001OnLButtonDown);
      IGUI_MSG_LINK(WM_LBUTTONUP, psender, this, &color_view::_001OnLButtonUp);

      m_dibTemplate->create(2048, 2048);

      ::flag::gay_with_shades_of_grey(m_dibTemplate);

      m_dibLuminance->create(100, 100);

   }


   void color_view::on_update(::user::impact * pSender, LPARAM lHint, object* pHint)
   {

      ::user::impact::on_update(pSender, lHint, pHint);

   }


   void color_view::on_control_event(::user::control_event * pevent)
   {

      ::user::impact::on_control_event(pevent);

   }


   void color_view::_001OnCreate(::message::message * pmessage)
   {

      pmessage->previous();

   }

   color color_view::get_color()
   {

      color color;

      color.set_hls(m_hls);

      return color;

   }

   void color_view::recalc_luminance(point pt)
   {

      if (pt.x >= m_dib->m_size.cx)
         return;
      if (pt.y >= m_dib->m_size.cy)
         return;
      if (pt.x < 0)
         return;
      if (pt.y < 0)
         return;

      COLORREF cr = m_dib->m_pcolorref[pt.x + (m_dib->m_iScan / sizeof(COLORREF)) * pt.y];

      color c(cr);

      color::hls hls;

      c.get_hls(hls);

      m_hls.m_dH = hls.m_dH;

      m_hls.m_dS = hls.m_dS;

      rebuild_luminance();

   }

   void color_view::rebuild_luminance()
   {

      ::flag::shades_of_luminance(m_dibLuminance, m_hls.m_dH, m_hls.m_dS);

   }

   void color_view::_001OnDraw(::draw2d::graphics * pgraphics)
   {
      pgraphics->SetStretchBltMode(HALFTONE);
      pgraphics->draw(rect_dim(0, 0, m_dib->m_size.cx, m_dib->m_size.cy), m_dib->g(), rect_dim(0, 0, m_dib->m_size.cx, m_dib->m_size.cy));
      pgraphics->draw(m_dibLuminance->rect() + ::size(m_dib->m_size.cx, 0), m_dibLuminance->g(), m_dib->rect());
   }

   void color_view::_001OnLButtonDown(::message::message * pmessage)
   {
      SCAST_PTR(::message::mouse, pmouse, pmessage);
      point pt = pmouse->m_pt;
      ScreenToClient(pt);
      recalc_luminance(pt);
      pmouse->m_bRet = true;
      SetCapture();
      m_bLButtonPressed = true;
   }

   void color_view::_001OnLButtonUp(::message::message * pmessage)
   {
      SCAST_PTR(::message::mouse, pmouse, pmessage);
      point pt = pmouse->m_pt;
      ScreenToClient(pt);
      recalc_luminance(pt);
      pmouse->m_bRet = true;
      ReleaseCapture();
      m_bLButtonPressed = false;
   }
   void color_view::_001OnMouseMove(::message::message * pmessage)
   {
      SCAST_PTR(::message::mouse, pmouse, pmessage);

      if (m_bLButtonPressed)
      {
         point pt = pmouse->m_pt;
         ScreenToClient(pt);
         recalc_luminance(pt);
         pmouse->m_bRet = true;
         ReleaseCapture();

      }
   }

   void color_view::on_layout()
   {

      ::user::impact::on_layout();

      rect rectClient;

      GetClientRect(rectClient);

      if (rectClient.area() <= 0)
      {

         return;

      }

      m_dib->create(rectClient.get_size() / 2);

      m_dib->g()->draw(m_dib->rect(), m_dibTemplate->get_graphics(), m_dibTemplate->rect());

      m_dibLuminance->create(rectClient.width() / 4, rectClient.height() / 2);

      rebuild_luminance();

   }


} // namespace userex



