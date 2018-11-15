//
//  helloaxis_render.cpp
//  app_core_helloaxis
//
//  Created by Camilo Sasuke Tsumanuma on 8/6/15 23:27;24.
//  Copyright (c) 2015 Camilo Sasuke Tsumanuma. All rights reserved.
//


#include "framework.h"
#include <math.h>


namespace helloaxis
{



   render::render(::aura::application * papp) :
      object(papp),
      thread(papp),
      ::helloaura::render(papp)
   {

      //m_bFirst23 = false;
      //m_bFastOnEmpty = true;
      //m_bFast = true;
      //m_dwLastFast = 0;
      //m_dwAnime = 2000;
      //m_dwFastAnime = 500;
      //m_dwLastOk = 0;



      //m_bImageEnable = true;

      //m_bDib1 = false;

      //m_bAlternate = false;

      //m_bLite = true;

      //m_bNewLayout = false;
      //m_bHelloRender = false;
      //m_cxCache1 = 0;
      //m_cyCache1 = 0;

      //m_bVoidTransfer = false;
      //m_bFirstDone = false;

      //m_dMinRadius = 0.0;
      //m_dMaxRadius = 0.0;

      //m_rectClient.null();


      //m_bVoidTransfer = false;

      //m_bFirstDone = true;

      //m_dMinRadius = 1.0;

      //m_dMaxRadius = 2.0;

      //m_bNewLayout = false;

      //m_bHelloRender = true;

      //m_cxCache1 = 0;

      //m_cyCache1 = 0;


   }


   render::~render()
   {

   }



   bool render::initialize_render(string strId)
   {

      return ::helloaura::render::initialize_render(strId);

      //      ::database::client::initialize_data_client(&Application.dataserver());

      //if (Application.m_strAppId == "app-core/flag")
      //{

      //   m_bilboa.add(bilbo("matter://cat.gif"));
      //   m_bilboa.add(bilbo("matter://nanosvg/23.svg"));
      //   m_bilboa.add(bilbo("matter://main/rock_with_a_mask.png"));
      //   m_bilboa.add(bilbo("matter://picachu_by_rondex.png"));
      //   m_bilboa.add(bilbo("matter://totoro_plus_plus.png"));

      //}
      //else if (strId == "switcher")
      //{

      //   m_bilboa.add(bilbo("matter://cat.gif"));
      //   m_bilboa.add(bilbo("matter://picachu_by_rondex.png"));
      //   m_bilboa.add(bilbo("matter://totoro_plus_plus.png"));

      //}
      //else
      //{

      //   m_bilboa.add(bilbo("matter://cat.gif"));
      //   m_bilboa.add(bilbo("matter://nanosvg/23.svg"));
      //   m_bilboa.add(bilbo("matter://main/rock_with_a_mask.png"));

      //}

      //int i = 1;

      //for (auto & bilbo : m_bilboa)
      //{

      //   //m_pview->data_get("bilbo." + bilbo.m_strPath, bilbo.m_bNew);

      //   i++;

      //}

      //defer_update_bilbo();


      //return true;

   }


   int32_t render::run()
   {

      return ::helloaura::render::run();

//      ::multithreading::set_priority(::multithreading::priority_time_critical);
//
////      double dFps = m_pview->get_wnd()->m_pimpl.cast < ::user::interaction_impl >()->m_dFps;
//
//      double dFps = 0.2;
//
//      double dPeriod = 1000.0 / dFps;
//
//      dPeriod = MIN(MAX(1.0, dPeriod), 1000.0);
//
//      //#ifdef WINDOWSEX
//      //
//      //      HANDLE timer;
//      //
//      //      LARGE_INTEGER li = {};
//      //
//      //      timer = CreateWaitableTimer(NULL, TRUE, NULL);
//      //
//      //#endif
//
//      double_array daFrame;
//
//      index iLastFrameId;
//
//      iLastFrameId = (index) (millis_now() / dPeriod);
//
//      index iFrameId;
//
//      while (thread_get_run())
//      {
//
//         try
//         {
//
//            if (m_bHelloRender)
//            {
//
//               full_render();
//
//            }
//
//            double dNow = millis_now();
//
//            double dWait = dPeriod - fmod(dNow + dPeriod / 3.0, dPeriod);
//
//            iFrameId = (index)(dNow / dPeriod);
//
//            ::count cLost = iFrameId - iLastFrameId - 1;
//
//            if (cLost < 0)
//            {
//
//               dWait = dPeriod;
//
//            }
//
//            sleep(millis(dWait));
//
//            iLastFrameId = iFrameId;
//
//            if (m_bHelloRender)
//            {
//
//               for (index i = 0; i < daFrame.get_size(); i++)
//               {
//
//                  if (dNow - daFrame[i] >= 1000.0)
//                  {
//
//                     daFrame.remove_at(i);
//
//                  }
//                  else
//                  {
//
//                     break;
//
//                  }
//
//               }
//
//            }
//
//            m_dRenderFps = double(daFrame.get_size());
//
//            daFrame.add(dNow);
//
//         }
//         catch (...)
//         {
//
//            break;
//
//         }
//
//      }
//
//      return 0;

   }



   void render::helloaura_render_lite_view(::draw2d::graphics * pgraphics)
   {

      return ::helloaura::render::helloaura_render_lite_view(pgraphics);

//      if (m_dibWork->area() <= 0)
//         return;
//
//      ::get_thread()->m_bThreadToolsForIncreasedFps = true;
//
//      rect rectClient = m_rectClient;
//
//      //pgraphics->set_alpha_mode(::draw2d::alpha_mode_set);
//
//      //pgraphics->FillSolidRect(rectClient,ARGB(0, 0, 0, 0));
//
//      //      int32_t iCount = 30;
//
//      ::draw2d::brush_sp brushText(allocer());
//
//      double T = 2.3;
//
////      if (false)
////      {
////
////         T = 2.3;
////
////      }
////      else
//      if (m_bAlternate)
//      {
//
//         T = 1.2;
//
//      }
//      else
//      {
//
//         T = 2.3;
//
//      }
//
//      double t = ::get_tick_count() / 1000.0;
//
//      double w = 2.0 * 3.1415 / T;
//
//      double r = (tri(w * t) + 1.0) / 2.0;
//
//      ::size size;
//
//      string strHelloAXIS;
//
//      {
//
//         synch_lock slText(m_pmutexText);
//
//         strHelloAXIS = get_helloaura().c_str(); // rationale : string allocation fork *for multithreading*
//
//      }
//
//      pgraphics->set_font(m_font);
//
//      size = pgraphics->GetTextExtent(strHelloAXIS);
//
//      m_cxTarget = int (size.cx * 1.2);
//      m_cyTarget = int (size.cy * 1.2);
//
//      if (!m_bFirstDone)
//      {
//
//         if (Session.savings().is_trying_to_save(::aura::resource_display_bandwidth))
//         {
//
//            Sleep(47);
//
//         }
//         else
//         {
//
//            m_cxCache1 = m_cxTarget;
//
//            m_cyCache1 = m_cyTarget;
//
//            {
//
//               synch_lock slDib(&m_mutexDib);
//
//               if (m_dib.initialize(m_cxCache1, m_cyCache1, int (m_dMaxRadius)))
//               {
//
//                  //m_dib->defer_realize(pgraphics);
//
//                  m_dib->Fill(0, 0, 0, 0);
//
//                  m_dib->get_graphics()->set_font(m_font);
//
//                  m_dib->get_graphics()->set_text_rendering_hint(::draw2d::text_rendering_hint_anti_alias);
//
//                  m_dib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);
//
//                  brushText->create_solid(ARGB(255, 255, 255, 255));
//
//                  m_dib->get_graphics()->SelectObject(brushText);
//
//                  m_dib->get_graphics()->text_out((m_cxCache1 - size.cx) / 2, (m_cyCache1 - size.cy) / 2, strHelloAXIS);
//
//                  m_dib->map();
//
//                  Application.imaging().spread(m_dib->get_graphics(), ::null_point(), m_dib->get_size(), m_dib->get_graphics(), null_point(), int (m_dMaxRadius));
//
//                  m_dib.blur();
//
//                  m_dibTemplate->create(m_dib->m_size);
//
//                  m_dibTemplate->Fill(0, 0, 0, 0);
//
//                  m_dibTemplate->channel_copy(visual::rgba::channel_alpha, visual::rgba::channel_green, m_dib);
//
//               }
//
//            }
//
//         }
//
//      }
//
//      {
//
//         synch_lock slText(m_pmutexText);
//
//         if (strHelloAXIS != get_helloaura() || m_cxCache1 != m_cxTarget || m_cyCache1 != m_cyTarget || m_dibTemplate->area() <= 0)
//            return;
//
//      }
//
//
//
//
//      ::color ca;
//
//
////      if (false)
////      {
////
////         double dPeriod = (5000) * 11;
////
////         ca.set_hls(fmod(::get_tick_count(), dPeriod) / dPeriod, 0.49, 0.84);
////
////      }
////      else if (m_bAlternate)
//      if(m_bAlternate)
//      {
//
//         double dPeriod = (5100) * 8;
//
//         ca.set_hls(fmod(::get_tick_count(), dPeriod) / dPeriod, 0.49, 0.84);
//
//      }
//      else
//      {
//
//         double dPeriod = (4900) * 11;
//
//         ca.set_hls(fmod(::get_tick_count(), dPeriod) / dPeriod, 0.23, 0.84);
//
//      }
//
//      if (!Session.savings().is_trying_to_save(::aura::resource_display_bandwidth))
//      {
//
//         //m_dibTemplate->set_rgb_pre_alpha(ca.m_uchR,ca.m_uchG,ca.m_uchB, 84 + 49 + (255 - 84 - 49) * r);
//         //m_dibTemplate->set_rgb_pre_alpha(ca.m_uchR, ca.m_uchG, ca.m_uchB);
//
//         m_dibTemplate2->tint(m_dibTemplate, ca.m_uchR, ca.m_uchG, ca.m_uchB);
//
//      }
//
//      pgraphics->SetStretchBltMode(HALFTONE);
//
//      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);
//
//      Application.imaging().bitmap_blend(pgraphics,
//                                             point((m_rectClient.width() - m_dibTemplate2->m_size.cx) / 2, (m_rectClient.height() - m_dibTemplate2->m_size.cy) / 2)
//                                             , m_dibTemplate2->m_size,
//                                             m_dibTemplate2->get_graphics(), null_point(), byte (128 + (255 - 128) * r));
//
//      //pgraphics->from(rectClient.top_left(),m_dibTemplate, null_point(), rectClient>si);
//
//      pgraphics->set_font(m_font);
//
//      pgraphics->set_text_rendering_hint(::draw2d::text_rendering_hint_anti_alias);
//
//      if (Session.savings().is_trying_to_save(::aura::resource_display_bandwidth))
//      {
//
//         brushText->create_solid(ARGB(255, ca.m_uchR, ca.m_uchG, ca.m_uchB));
//
//      }
//      else
//      {
//
//         if (m_bAlternate)
//         {
//
//            brushText->create_solid(ARGB(255, 184, 184, 177));
//
//         }
//         else
//         {
//
//            brushText->create_solid(ARGB(255, 255, 255, 255));
//
//         }
//
//      }
//
//      pgraphics->SelectObject(brushText);
//
//      //if(!m_bAlternate)
//      {
//
//         pgraphics->text_out((m_rectClient.width() - size.cx) / 2, (m_rectClient.height() - size.cy) / 2, strHelloAXIS);
//
//      }
//      //      pgraphics->FillSolidRect(200,00,100,100,ARGB(128,128,128,255));
//
//      //    pgraphics->FillSolidRect(200,200,100,100,ARGB(128,128,128,0));
//
//      if(!m_bFirstDone)
//      {
//
//         synch_lock slText(m_pmutexText);
//
//         if (strHelloAXIS == get_helloaura() && m_cxCache1 == m_cxTarget && m_cyCache1 == m_cyTarget)
//         {
//
//            m_bFirstDone = true;
//
//         }
//
//      }

   }


   void render::helloaura_render_full_view(::draw2d::graphics * pgraphics)
   {

      ::helloaura::render::helloaura_render_full_view(pgraphics);

//      if (m_dibWork->area() <= 0)
//         return;
//
//      rect rectClient = m_rectClient;
//
//      if (rectClient.area() <= 0)
//         return;
//
//      //      int32_t iCount = 30;
//
//      ::draw2d::brush_sp brushText(allocer());
//
//      double T = 2.3;
//
////      if (false)
////      {
////
////         T = 2.3;
////
////      }
////      else
//      if (m_bAlternate)
//      {
//
//         T = 1.2;
//
//      }
//      else
//      {
//
//         T = 2.3;
//
//      }
//
//      double t = ::get_tick_count() / 1000.0;
//
//      double w = 2.0 * 3.1415 / T;
//
//      double r = (tri(w * t) + 1.0) / 2.0;
//
//      double dBlur = m_dMinRadius + (m_dMaxRadius - m_dMinRadius) * r;
//
//      ::color ca;
//
////      if (false)
////      {
////
////         double dPeriod = (5000) * 11;
////
////         ca.set_hls(fmod(::get_tick_count(), dPeriod) / dPeriod, 0.49, 0.84);
////
////      }
////      else
////
//      if (m_bAlternate)
//      {
//
//         double dPeriod = (5100) * 8;
//
//         ca.set_hls(fmod(::get_tick_count(), dPeriod) / dPeriod, 0.49, 0.84);
//
//      }
//      else
//      {
//
//         double dPeriod = (4900) * 11;
//
//         ca.set_hls(fmod(::get_tick_count(), dPeriod) / dPeriod, 0.23, 0.84);
//
//      }
//
//
//
//      pgraphics->set_font(m_font);
//
//      string strHelloAXIS = get_helloaura();
//
//      ::size size = pgraphics->GetTextExtent(strHelloAXIS);
//
//      m_cxTarget = int(size.cx * 1.2);
//      m_cyTarget = int(size.cy * 1.2);
//
//      {
//
//         synch_lock slDib(&m_mutexDib);
//
//         if (!Session.savings().is_trying_to_save(::aura::resource_display_bandwidth))
//         {
//
//            if (m_dMinRadius > 3.0)
//            {
//
//               m_dib.initialize(m_cxTarget, m_cyTarget, int (dBlur));
//
//            }
//            else
//            {
//
//               m_dib.initialize(m_cxTarget, m_cyTarget, 5);
//
//            }
//
//            m_dib->defer_realize(pgraphics);
//
//            m_dib->Fill(0, 0, 0, 0);
//
//            m_dib->get_graphics()->set_text_rendering_hint(::draw2d::text_rendering_hint_anti_alias);
//
//            m_dib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);
//
//            brushText->create_solid(ARGB(255, 255, 255, 255));
//
//            m_dib->get_graphics()->SelectObject(brushText);
//
//            m_dib->get_graphics()->set_font(m_font);
//
//            m_dib->get_graphics()->text_out((m_rectClient.width() - size.cx) / 2, (m_rectClient.height() - size.cy) / 2, strHelloAXIS);
//
//            if (m_dMinRadius > 3.0)
//            {
//
//               m_dib.blur(m_rectClient.width(), m_rectClient.height());
//
//            }
//            else
//            {
//
//               for (int32_t i = 0; i < dBlur * 2; i++)
//               {
//
//                  m_dib.blur(m_rectClient.width(), m_rectClient.height());
//
//               }
//
//            }
//
//            if (!Session.savings().is_trying_to_save(::aura::resource_display_bandwidth))
//            {
//
//               m_dib->channel_copy(visual::rgba::channel_alpha, visual::rgba::channel_green);
//
//               m_dibTint->tint(m_dib, ca.m_uchR, ca.m_uchG, ca.m_uchB);
//
//            }
//
//         }
//
//         pgraphics->SetStretchBltMode(HALFTONE);
//
//         pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);
//
//         pgraphics->BitBlt(rectClient, m_dibTint->get_graphics());
//
//      }
//
//      pgraphics->set_text_rendering_hint(::draw2d::text_rendering_hint_anti_alias);
//
//      if (Session.savings().is_trying_to_save(::aura::resource_display_bandwidth))
//      {
//
//         brushText->create_solid(ARGB(255, ca.m_uchR, ca.m_uchG, ca.m_uchB));
//
//      }
//      else
//      {
//
//         if (m_bAlternate)
//         {
//
//            brushText->create_solid(ARGB(255, 184, 184, 177));
//
//         }
//         else
//         {
//
//            brushText->create_solid(ARGB(255, 255, 255, 255));
//
//         }
//
//      }
//
//      pgraphics->SelectObject(brushText);
//
//      pgraphics->text_out((m_rectClient.width() - size.cx) / 2, (m_rectClient.height() - size.cy) / 2, strHelloAXIS);
//
//      byte a, R, g, b;
//
//      if (m_bAlternate)
//      {
//         a = 184;
//         R = 177;
//         g = 77;
//         b = 184;
//      }
//      else
//      {
//         a = 184;
//         R = 77;
//         g = 184;
//         b = 84;
//      }
//
//#if 0
//      if (Application.m_iErrorAiFont == 0)
//      {
//
//         synch_lock slAiFont(&Application.m_mutexAiFont);
//
//         FT_Face & face = (FT_Face &)Application.m_faceAi;
//
//         int32_t error;
//
//         error = FT_Set_Char_Size(face,        /* handle to face object */
//                                  0,          /* char_width in 1/64th of points */
//                                  800 * 64,          /* char_height in 1/64th of points */
//                                  72,         /* horizontal device resolution */
//                                  72);         /* vertical device resolution */
//
//         if (error == 0)
//         {
//
//            error = FT_Select_Charmap(face, /* target face object */ FT_ENCODING_UNICODE); /* encoding */
//
//            if (error == 0)
//            {
//
//               int64_t iChar = ::str::ch::uni_index(::str::international::unicode_to_utf8(L"愛"));
//
//               int32_t glyph_index = FT_Get_Char_Index(face, (int32_t)iChar);
//
//               error = FT_Load_Glyph(face, /* handle to face object */ glyph_index, /* glyph index */ FT_LOAD_DEFAULT); /* load flags, see below */
//
//               if (error == 0)
//               {
//
//                  error = FT_Render_Glyph(face->glyph, /* glyph slot */ FT_RENDER_MODE_NORMAL); /* render mode */
//
//                  if (error == 0)
//                  {
//
//                     ::visual::dib_sp &  dib = m_dibAi1;
//
//                     dib->create(face->glyph->bitmap.width, face->glyph->bitmap.rows);
//
//                     dib->realize(pgraphics);
//
//                     draw_freetype_bitmap(dib.m_p, 0, 0, &face->glyph->bitmap, 0, 0, a, R, g, b);
//
//                     pgraphics->SetStretchBltMode(HALFTONE);
//
//                     pgraphics->StretchBlt(0, 0, dib->get_size().cx / 40, dib->get_size().cy / 40, dib->get_graphics(), 0, 0, dib->get_size().cx, dib->get_size().cy, SRCCOPY);
//
//                     pgraphics->StretchBlt(0, m_rectClient.height() - dib->get_size().cy / 40, dib->get_size().cx / 40, dib->get_size().cy / 40, dib->get_graphics(), 0, 0, dib->get_size().cx, dib->get_size().cy, SRCCOPY);
//
//                  }
//
//               }
//
//            }
//
//         }
//
//
//         error = FT_Set_Char_Size(face,        /* handle to face object */
//                                  0,          /* char_width in 1/64th of points */
//                                  640 * 64,          /* char_height in 1/64th of points */
//                                  72,         /* horizontal device resolution */
//                                  72);         /* vertical device resolution */
//
//         if (error == 0)
//         {
//
//            error = FT_Select_Charmap(face, /* target face object */ FT_ENCODING_UNICODE); /* encoding */
//
//            if (error == 0)
//            {
//
//               int64_t iChar = ::str::ch::uni_index(::str::international::unicode_to_utf8(L"愛"));
//
//               int32_t glyph_index = FT_Get_Char_Index(face, (int32_t)iChar);
//
//               error = FT_Load_Glyph(face, /* handle to face object */ glyph_index, /* glyph index */ FT_LOAD_DEFAULT); /* load flags, see below */
//
//               if (error == 0)
//               {
//
//                  error = FT_Render_Glyph(face->glyph, /* glyph slot */ FT_RENDER_MODE_NORMAL); /* render mode */
//
//                  if (error == 0)
//                  {
//
//                     ::visual::dib_sp &  dib = m_dibAi2;
//
//                     dib->create(face->glyph->bitmap.width, face->glyph->bitmap.rows);
//
//                     dib->realize(pgraphics);
//
//                     draw_freetype_bitmap(dib.m_p, 0, 0, &face->glyph->bitmap, 0, 0, a, R, g, b);
//
//                     pgraphics->SetStretchBltMode(HALFTONE);
//
//                     pgraphics->StretchBlt(m_rectClient.width() - dib->get_size().cx / 32, 0, dib->get_size().cx / 32, dib->get_size().cy / 32, dib->get_graphics(), 0, 0, dib->get_size().cx, dib->get_size().cy, SRCCOPY);
//
//                     pgraphics->StretchBlt(m_rectClient.width() - dib->get_size().cx / 32, m_rectClient.height() - dib->get_size().cy / 32, dib->get_size().cx / 32, dib->get_size().cy / 32, dib->get_graphics(), 0, 0, dib->get_size().cx, dib->get_size().cy, SRCCOPY);
//
//                  }
//
//               }
//
//            }
//
//         }
//
//      }
//
//#endif
//
//      if (strHelloAXIS == get_helloaura() && m_rectClient.width() == m_rectClient.width() && m_rectClient.height() == m_rectClient.height())
//      {
//
//         m_bFirstDone = true;
//
//      }
//
   }


   void render::_001OnHelloDraw(::draw2d::graphics * pgraphics)
   {

      ::helloaura::render::_001OnHelloDraw(pgraphics);

      return;

//      rect rectClient;
//
//      rectClient.left = 0;
//      rectClient.top = 0;
//      rectClient.right = m_rectClient.width();
//      rectClient.bottom = m_rectClient.height();
//
//      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);
//      int period = 5000;
//      int border = 2500;
//      int t;
//
//      try
//      {
//
//         if (m_stra23.get_size() > 0 || m_strLast23.has_char() || m_strCurrent23.has_char())
//         {
//
//            if (!m_bFirst23)
//            {
//               m_dw23 = get_tick_count();
//               m_uiCurrent23 = 0;
//               m_strLast23.Empty();
//               m_strCurrent23.Empty();
//               m_bFirst23 = true;
//               t = 0;
//            }
//            else
//            {
//
//               t = (get_tick_count() - m_dw23);
//
//               uint32_t uiCurrent23 = (t) / period;
//
//               t %= period;
//
//               if (m_uiCurrent23 != uiCurrent23)
//               {
//
//                  m_strLast23 = m_strCurrent23;
//
//                  // pulse!!
//                  if (m_stra23.get_size() <= 0)
//                  {
//
//                     m_strCurrent23.Empty();
//
//                  }
//                  else
//                  {
//
//                     m_strCurrent23 = m_stra23[uiCurrent23 % m_stra23.get_size()];
//
//                  }
//
//                  m_uiCurrent23 = uiCurrent23;
//
//               }
//
//            }
//
//            if (t < border && m_strLast23 != m_strCurrent23)
//            {
//
//               byte uchAlpha = 255 * t / border;
//
//               if (m_strLast23.has_char())
//               {
//
//                  synch_lock sl(&m_mutexDib23);
//
//                  auto & dib = dib23(m_strLast23);
//
//                  if (dib.m_eload == ::visual::load_ok)
//                  {
//
//                     dib.defer_update();
//
//                     Application.imaging().bitmap_blend(pgraphics, null_point(), dib->get_size(), dib->get_graphics(), null_point(), 255 - uchAlpha);
//
//                  }
//
//               }
//
//               if (m_strCurrent23.has_char())
//               {
//
//                  synch_lock sl(&m_mutexDib23);
//
//                  auto & dib = dib23(m_strCurrent23);
//
//                  if (dib.m_eload == ::visual::load_ok)
//                  {
//
//                     dib.defer_update();
//
//                     Application.imaging().bitmap_blend(pgraphics, null_point(), dib->get_size(), dib->get_graphics(), null_point(), uchAlpha);
//
//                  }
//
//               }
//
//            }
//            else if (m_strCurrent23.has_char())
//            {
//
//               synch_lock sl(&m_mutexDib23);
//
//               auto & dib = dib23(m_strCurrent23);
//
//               if (dib.m_eload == ::visual::load_ok)
//               {
//
//                  dib.defer_update();
//
//                  pgraphics->BitBlt(0, 0, dib->m_size.cx, dib->m_size.cy, dib->get_graphics(), 0, 0, SRCCOPY);
//
//               }
//
//            }
//
//         }
//
//      }
//      catch (...)
//      {
//
//      }
//
//      if (Application.m_etype == application::type_mili)
//      {
//
//         {
//
//            string strHelloAXIS;
//
//            {
//
//               //synch_lock slText(&m_pview->m_mutexText);
//
//               //strHelloAXIS = m_pview->get_processed_helloaura().c_str();
//
//               strHelloAXIS = "Hello Axis!!";
//
//            }
//
//            if (m_bNewLayout)
//            {
//
//               float fHeight = 100.0;
//
//               ::draw2d::font_sp font(allocer());
//
//               font->create_pixel_font(FONT_SANS, fHeight, FW_BOLD);
//
//               pgraphics->set_font(font);
//
//               pgraphics->set_text_rendering_hint(::draw2d::text_rendering_hint_anti_alias);
//
//               class size size = pgraphics->GetTextExtent(strHelloAXIS);
//
//               double ratey = fHeight * 0.84 / size.cy;
//
//               font->create_pixel_font(FONT_SANS, MIN(m_rectClient.height() * ratey, m_rectClient.width() * size.cy * ratey / size.cx), FW_BOLD);
//
//               m_font = font;
//
//               m_bNewLayout = false;
//
//            }
//
//            ::color ca;
//
//            double dPeriod = (500) * 11;
//
//            ca.set_hls(fmod(::get_tick_count(), dPeriod) / dPeriod, 0.49, 0.84);
//
//            ::draw2d::brush_sp brush(allocer());
//
//            brush->create_solid(ARGB(255, ca.m_uchR, ca.m_uchG, ca.m_uchB));
//
//            pgraphics->SelectObject(brush);
//
//            pgraphics->set_font(m_font);
//
//            pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);
//
//            pgraphics->set_text_rendering_hint(::draw2d::text_rendering_hint_anti_alias);
//
//            ::size size = pgraphics->GetTextExtent(strHelloAXIS);
//
//            pgraphics->text_out((m_rectClient.width() - size.cx) / 2, (m_rectClient.height() - size.cy) / 2, strHelloAXIS);
//
//            return;
//
//         }
//
//      }
//
//      //DWORD dw = get_tick_count();
//
//      if (m_bFast || !m_bFirstDone || ::get_tick_count() - m_dwLastFast < m_dwFastAnime)
//      {
//
////         synch_lock sl1(m_pview->get_wnd()->m_pmutex);
//
//         synch_lock slDraw(&m_mutexDraw);
//
//         if (m_bFast || m_dibFast.is_null())
//         {
//
//            m_bFast = false;
//
//            {
//
//               //synch_lock slText(&m_pview->m_mutexText);
//
//               //helloaura_fast_render(m_pview->get_processed_helloaura());
//               helloaura_fast_render("Hello Axis!!");
//
//            }
//
//            m_bFirstDone = false;
//
//         }
//
//         if (m_bFast || !m_bFirstDone)
//         {
//
//            m_dwLastFast = ::get_tick_count();
//
//         }
//
//         pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);
//
//         pgraphics->BitBlt(null_point(), size(m_rectClient.width(), m_rectClient.height()), m_dibFast->get_graphics());
//
//         //pgraphics->FillSolidRect(400,400,100,100,ARGB(128,0,0,128));
//
////         m_pview->m_bOkPending = true;
//
//         return;
//
//   }

      //if (m_pview->m_bOkPending)
      //{

      //   m_pview->m_bOkPending = false;

      //   m_dwLastOk = ::get_tick_count();

      //}

      //::draw2d::dib * pdib = NULL;

      //::draw2d::dib * pdibFast = m_dibFast;

      //synch_lock sl(&m_mutexDraw);

      //synch_lock slSwap(&m_mutexSwap);

      //pdib = m_dibOut;

      //if (pdib->area() <= 0)
      //   return;

      //pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      //if (::get_tick_count() - m_dwLastOk < m_dwAnime)
      //{

      //   byte uchAlpha;

      //   uchAlpha = byte(MAX(0, MIN(255, (::get_tick_count() - m_dwLastOk) * 255 / m_dwAnime)));

      //   Application.imaging().bitmap_blend(pgraphics, null_point(), pdib->get_size(), pdib->get_graphics(), null_point(), uchAlpha);

      //   Application.imaging().bitmap_blend(pgraphics, null_point(), pdibFast->get_size(), pdibFast->get_graphics(), null_point(), 255 - uchAlpha);

      //}
      //else
      //{

      //   pgraphics->from(null_point(), pdib->get_size(), pdib->get_graphics(), null_point(), SRCCOPY);

      //}

   }


   ::visual::dib_sp & render::dib23(string strImage)
   {
      return ::helloaura::render::dib23(strImage);
      //auto & dib = m_mapDib23[strImage];

      //if (dib.is_null())
      //{

      //   dib.alloc(allocer());

      //}

      //if (dib.m_eload == ::visual::load_none)
      //{

      //   dib.m_eload = ::visual::load_going_to_load;

      //   ::fork(get_app(), [=]()
      //   {

      //      if (!m_mapDib23[strImage].load_from_file(strImage, true, true))
      //      {

      //         _throw(simple_exception(get_app(), "Failed to load \"" + strImage + "\""));

      //      }

      //   });

      //}

      //return dib;

   }


   void render::defer_update_bilbo()
   {

//      synch_lock sl(m_pmutex);
//
//      for (auto & bilbo : m_bilboa)
//      {
//
//         if (bilbo.m_bNew && !bilbo.m_b)
//         {
//
//            m_stra23.add_unique(bilbo.m_strPath);
//
//            bilbo.m_b = true;
//
////            m_pview->data_set("bilbo." + bilbo.m_strPath, bilbo.m_b);
//
//         }
//         else if (!bilbo.m_bNew && bilbo.m_b)
//         {
//
//            m_stra23.remove(bilbo.m_strPath);
//
//            bilbo.m_b = false;
//
////            m_pview->data_set("bilbo." + bilbo.m_strPath, bilbo.m_b);
//
//         }
//
//      }
//
//      for (auto str23 : m_stra23)
//      {
//
//         synch_lock sl(&m_mutexDib23);
//
//         dib23(str23);
//
//      }

      ::helloaura::render::defer_update_bilbo();

   }

   bool render::in_anime()
   {

      return ::helloaura::render::in_anime();

      //if (m_bFast || ::get_tick_count() - m_dwLastFast < m_dwFastAnime)
      //   return true;
      //if (::get_tick_count() - m_dwLastOk < m_dwAnime)
      //   return true;
      //return false;
   }

   void render::helloaura_fast_render(const string & strHelloAXIS)
   {


      ::helloaura::render::helloaura_fast_render(strHelloAXIS);

      return;

//      if (m_rectClient.width() <= 0 || m_rectClient.height() <= 0)
//         return;
//
//      synch_lock slDraw(&m_mutexDraw);
//
//      ::size sizeNew = ::size(m_rectClient.width(), m_rectClient.height());
//
//      bool bNewSize = m_dibFast->m_size.cx != sizeNew.cx || m_dibFast->m_size.cy != sizeNew.cy;
//
//      if (bNewSize)
//      {
//
//         m_dibFast->create(sizeNew);
//
//      }
//
//      m_dibFast->Fill(0, 0, 0, 0);
//
//      ::draw2d::graphics * pgraphics = m_dibFast->get_graphics();
//
//      float fHeight = 100.0;
//
//      ::draw2d::font_sp font(allocer());
//
////      font->create_pixel_font(m_pview->m_strFont, fHeight, FW_BOLD);
//
//      pgraphics->set_font(font);
//
//      pgraphics->set_text_rendering_hint(::draw2d::text_rendering_hint_anti_alias);
//
//      class size size = pgraphics->GetTextExtent(strHelloAXIS);
//
//      double ratey = fHeight * 0.84 / size.cy;
//
////      font->create_pixel_font(m_pview->m_strFont, MIN(m_rectClient.height() * ratey, m_rectClient.width() * size.cy * ratey / size.cx), FW_BOLD);
//
//      m_dMinRadius = MAX(1.0, MIN(m_rectClient.height() * ratey, m_rectClient.width() * size.cy * ratey / size.cx) / 46.0);
//
//      m_dMaxRadius = m_dMinRadius * 2.3;
//
//      m_font = font;
//
//      pgraphics->set_font(m_font);
//
//      size = pgraphics->GetTextExtent(strHelloAXIS);
//
//      ::draw2d::path_sp path(allocer());
//
//      path->m_bFill = false;
//
//      path->add_string((m_rectClient.width() - size.cx) / 2, (m_rectClient.height() - size.cy) / 2, strHelloAXIS, m_font);
//
//      ::draw2d::pen_sp pen(allocer());
//
//      pen->create_solid(1.0, ARGB(255, 84, 90, 80));
//
//      ::draw2d::pen_sp penW(allocer());
//
//      penW->create_solid(3.0, ARGB(84, 255, 255, 255));
//
//      pgraphics->set_alpha_mode(::draw2d::alpha_mode_set);
//
//      //      pgraphics->FillSolidRect((m_rectClient.width() - size.cx) / 2,(m_rectClient.height() - size.cy) / 2, 100, 100, ARGB(255,255,200,240));
//
//      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);
//
//      pgraphics->draw_path(path, penW);
//      pgraphics->draw_path(path, pen);
//      //pgraphics->FillSolidRect(00,00,100,100,ARGB(128,128,0,0));

   }


} // namespace helloaxis



