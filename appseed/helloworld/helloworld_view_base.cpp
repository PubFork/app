#include "framework.h"
#include <math.h>


//extern CLASS_DECL_AXIS thread_int_ptr < DWORD_PTR > t_time1;


namespace helloworld
{



   view_base::view_base(::aura::application * papp):
      object(papp),
      m_dibPost(allocer()),
      m_dibTime(allocer()),
      m_dib1(allocer()),
      m_dib2(allocer()),
      m_mutexText(papp),
      m_fontDrawStatus(allocer())
   {
      m_prender = NULL;
      m_fontDrawStatus->create_pixel_font("Arial", 20, 400);
      m_crDrawStatus = ARGB(255, 255, 255, 0);



      m_eeffect                  = effect_none;

      m_dFps                     = 0.0;

   }

   view_base::~view_base()
   {
   }

   void view_base::assert_valid() const
   {
      user::box::assert_valid();
   }

   void view_base::dump(dump_context & dumpcontext) const
   {
      user::box::dump(dumpcontext);
   }

   void view_base::install_message_routing(::message::sender * psender)
   {

      ::user::impact::install_message_routing(psender);

      IGUI_MSG_LINK(WM_CREATE, psender, this, &view_base::_001OnCreate);
      IGUI_MSG_LINK(WM_DESTROY, psender, this, &view_base::_001OnDestroy);

   }


   void view_base::_001OnCreate(::message::message * pobj)
   {

      pobj->previous();

      var v;

      data_get("cur_fps", v);

      m_dFps = v.get_double();

      m_dwRoll = ::get_tick_count();

   }


   void view_base::_001OnDestroy(::message::message * pobj)
   {

      ::multithreading::post_quit_and_wait(m_prender, seconds(15));


   }


   void view_base::defer_check_on_draw_layout()
   {

   }

   void view_base::_001OnNcDraw(::draw2d::graphics * pgraphicsParam)
   {

      ::user::impact::_001OnNcDraw(pgraphicsParam);

   }

   void view_base::_001OnDraw(::draw2d::graphics * pgraphicsParam)
   {

      //uint64_t startTime = get_nanos();

      defer_check_on_draw_layout();

      ::rect rectClient;

      GetClientRect(rectClient);

      if (rectClient.area() <= 0)
         return;

      m_dibPost->create(rectClient.size());

      m_dibPost->Fill(00, 00, 00, 00);

      bool bDraw = true;

      if (bDraw)
      {


         on_draw_image_layer(pgraphicsParam);

         ::draw2d::dib * pdib = m_dibPost;

         _001OnHelloDraw(pdib->get_graphics());

      }


      m_dibTime->create(m_dibPost->get_size());

      m_dibTime->Fill(0, 0, 0, 0);


      int xOffset;

      xOffset = int (m_dibTime->m_size.cx * m_dFps * (double)(::get_tick_count() - m_dwRoll) / 1000.0); // x = v.t; f=fps  1920 * 1FPS * t

      xOffset %= m_dibTime->m_size.cx;

      if (xOffset < 0)
      {

         xOffset += m_dibTime->m_size.cx;

      }

      m_dibTime->from(point(xOffset, 0), m_dibPost, ::null_point(), ::size(m_dibPost->m_size.cx - xOffset, m_dibPost->m_size.cy));
      m_dibTime->from(null_point(), m_dibPost, point(m_dibPost->m_size.cx - xOffset, 0), size(xOffset, m_dibPost->m_size.cy));

      //m_dibPost->from(m_dibTime);
      _001OnPostProcess(m_dibTime->get_graphics());

      ::draw2d::graphics * pdcParam = pgraphicsParam;

      pdcParam->set_alpha_mode(::draw2d::alpha_mode_blend);

      //      m_dibPost->get_graphics()->FillSolidRect(110,110,100,100,ARGB(184,177,184,60));


      /*  m_dwaFrame.add(get_tick_count());

      for (index i = 0; i < m_dwaFrame.get_size();)
      {

         if (get_tick_count() - m_dwaFrame[i] > 1000)
         {
            m_dwaFrame.remove_at(i);
         }
         else
         {
            i++;
         }

      }

      pdcParam->set_text_color(ARGB(255, 255, 255, 0));

      ::draw2d::font_sp f(allocer());

      f->create_point_font("Arial", 20, 800);

      pdcParam->set_font(f);

      pdcParam->TextOutA(0, 0, ::str::from(m_dwaFrame.get_size()));*/


      size s = m_dibTime->get_size();

      ::draw2d::graphics * pgraphics = m_dibTime->get_graphics();

      pdcParam->from(s, pgraphics, SRCCOPY);

      //pdcScreen->FillSolidRect(10,10,100,100,ARGB(184,49,184,60));

      //pdcScreen->Draw3dRect(200,200,100,100,ARGB(255,0,255,0),ARGB(255,0,0,255));
      //uint64_t endTime = get_nanos();

      //uint64_t micros = (endTime - startTime) / 1000;

      //char sz[512];

      //::output_debug_string("view:");
      //::ultoa_dup(sz, micros, 10);
      //::output_debug_string(sz);
      //::output_debug_string(", ");

      //::visual::dib_sp d(allocer());

      //d->create(rectClient.size());

      //d->get_graphics()->BitBlt(rectClient, pdib->get_graphics());

      //d.save_to_file(::dir::system() / "obs.png");


      //pdcParam->set_font(m_fontDrawStatus);

      //pdcParam->set_text_color(m_crDrawStatus);

      //string str1;
      //str1 = "FPS: " + ::str::from((int) get_wnd()->m_pimpl.cast<::user::interaction_impl>()->m_dUpdateScreenFps);
      //m_yDrawStatus = 10;
      //pdcParam->TextOutA(10, m_yDrawStatus, str1);
      //m_yDrawStatus += m_fontDrawStatus->m_dFontSize;
      //if (m_prender != NULL)
      //{
      //
      //   str1 = "Render FPS: " + ::str::from((int) m_prender->m_dRenderFps);
      //   pdcParam->TextOutA(10, m_yDrawStatus, str1);
      //   m_yDrawStatus += m_fontDrawStatus->m_dFontSize;
      //}


   }

   void view_base::on_draw_image_layer(::draw2d::graphics * pgraphics)
   {


   }

   void view_base::_001OnHelloDraw(::draw2d::graphics * pgraphics)
   {


   }

   void view_base::_001OnPostProcess(::draw2d::graphics * pgraphics)
   {

      if (m_eeffect == effect_crt)
      {
         int iFactor = 2;
         int iMult = 1 << iFactor;

         rect rectClient;

         GetClientRect(rectClient);

         size s = rectClient.size();

         size s2(s.cx / iMult, s.cy / iMult);

         m_dib1->create(s2);

         m_dib1->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

         m_dib1->get_graphics()->StretchBlt(0, 0, s2.cx, s2.cy, pgraphics, 0, 0, s.cx, s.cy, SRCCOPY);

         //if (0)
         {

            if (pgraphics->m_pdib != NULL)
            {

               pgraphics->set_alpha_mode(::draw2d::alpha_mode_set);
               pgraphics->StretchBlt(0, 0, s.cx, s.cy, m_dib1->get_graphics(), 0, 0, s2.cx, s2.cy, SRCCOPY);


            }
            else
            {

               m_dib2->create(s);

               m_dib2->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);
               m_dib2->get_graphics()->StretchBlt(0, 0, s.cx, s.cy, m_dib1->get_graphics(), 0, 0, s2.cx, s2.cy, SRCCOPY);


            }


            COLORREF cr;

            byte a, r, g, b, rm, gm, bm;

            ::draw2d::dib * pdib = pgraphics->m_pdib;

            if (pdib == NULL)
            {

               pdib = m_dib2;

            }

            pdib->map();

            int h = (s.cy / 3) * 3;

            int w = (s.cx / 3) * 3;

            int rstride = pdib->m_iScan / sizeof(COLORREF);

            COLORREF * pdata = pdib->m_pcolorref;

            int i1;
            int i2;
            int i3;
            COLORREF cr1;
            COLORREF cr2;
            COLORREF cr3;

            for (int i = 0; i < h; i += 3)
            {
               for (int j = 0; j < w; j += 3)
               {
                  i1 = i * rstride + j;
                  i2 = i1 + rstride;
                  i3 = i2 + rstride;
                  cr = pdata[i1];
                  a = argb_get_a_value(cr);
                  r = argb_get_r_value(cr);
                  g = argb_get_g_value(cr);
                  b = argb_get_b_value(cr);
                  rm = (g + b) / 4;
                  gm = (r + b) / 4;
                  bm = (r + g) / 4;

                  cr1 = REASSEMBLE_ARGB(a, gm, g, gm);
                  cr2 = REASSEMBLE_ARGB(a, bm, bm, b);
                  cr3 = REASSEMBLE_ARGB(a, r, rm, rm);
                  pdata[i1] = cr3;
                  pdata[i1 + 1] = cr1;
                  pdata[i1 + 2] = cr2;
                  pdata[i2] = cr3;
                  pdata[i2 + 1] = cr1;
                  pdata[i2 + 2] = cr2;
                  pdata[i3] = cr3;
                  pdata[i3 + 1] = cr1;
                  pdata[i3 + 2] = cr2;

               }

            }

            if (pgraphics->m_pdib == NULL)
            {

               pgraphics->BitBlt(0, 0, s.cx, s.cy, m_dib2->get_graphics(), 0, 0, SRCCOPY);

            }
            else
            {

               pdib->unmap();

            }

            ::draw2d::pen_sp pen(allocer());

            pen->create_solid(0.5, ARGB(84, 0, 0, 0));

            pgraphics->SelectObject(pen);

            for (int i = 0; i < s.cy; i += 3)
            {

               pgraphics->draw_line(0, i, s.cx, i);

            }

         }


      }




   }










} // namespace helloworld

















