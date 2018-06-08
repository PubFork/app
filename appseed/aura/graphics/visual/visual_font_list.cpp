#include "framework.h"

#include <math.h>

#define BOX 0
#define BOX_SEL 1
#define BOX_HOVER 2



namespace visual
{


   font_list::font_list(::aura::application * papp) :
      object(papp)
   {

      m_iUpdate = -1;
      m_rectMargin = rect(5, 5, 5, 5);
      m_iSel = -1;
      m_iHover = -1;

      defer_create_mutex();

      m_dwaFg.add(ARGB(255, 80, 80, 80));
      m_dwaFg.add(ARGB(255, 45, 45, 45));
      m_dwaFg.add(ARGB(255, 255, 255, 255));

      m_dwaBg.add(ARGB(0, 0, 0, 0));
      m_dwaBg.add(ARGB(255, 128, 200, 152));
      m_dwaBg.add(ARGB(255, 80, 80, 80));

   }


   font_list::~font_list()
   {


   }

   font_list::text_box::text_box()
   {

      m_bOk = false;

   }


   font_list::text_box::~text_box()
   {

   }


   void font_list ::text_box::update(font_list * pdata, int iBox, string strText)
   {

      m_dib->create(m_size);

      m_dib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

      m_dib->get_graphics()->fill_solid_rect(rect(m_size.cx), pdata->m_dwaBg[iBox]);

      m_dib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);

      m_dib->get_graphics()->selectFont(m_font);

      m_dib->get_graphics()->set_text_color(pdata->m_dwaFg[iBox]);

      m_dib->get_graphics()->text_out(pdata->m_rectMargin.left, pdata->m_rectMargin.top, strText);

      m_bOk = true;

   }


   font_list::item::item()
   {

   }


   font_list::item::~item()
   {

   }


   font_list::layout::layout()
   {

      defer_create_mutex();
      m_iUpdate = -1;
      m_elayout = layout_wide;

   }


   font_list::layout::~layout()
   {


   }


   void font_list::_001OnDrawWide(::draw2d::graphics * pgraphics, layout * playout)
   {

      synch_lock sl(m_pmutex);

      layout & layout = *playout;

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      //rect rectClient = m_rectClient;

      for (int i = 0; i < layout.get_count(); i++)
      {

         if (layout[i] == NULL)
         {

            continue;

         }

         int iBox;

         if (i == m_iSel)
         {
            continue;
            iBox = BOX_SEL;
         }
         else if (i == m_iHover)
         {
            continue;
            iBox = BOX_HOVER;
         }
         else
         {
            iBox = BOX;
         }

         text_box * pbox = &layout[i]->m_box[iBox];

         if (!pbox->m_bOk)
         {

            pbox->update(this, iBox, layout[i]->m_strSample);

         }

         pgraphics->draw(pbox->m_rect, pbox->m_dib->get_graphics());

      }

      if (m_iSel >= 0)
      {

         text_box * pbox = &layout[m_iSel]->m_box[BOX_SEL];

         if (!pbox->m_bOk)
         {

            pbox->update(this, BOX_SEL, layout[m_iSel]->m_strSample);

         }

         pgraphics->draw(pbox->m_rect, pbox->m_dib->get_graphics());

      }

      if (m_iHover >= 0 && m_iHover != m_iSel)
      {

         text_box * pbox = &layout[m_iHover]->m_box[BOX_HOVER];

         if (!pbox->m_bOk)
         {

            pbox->update(this, BOX_HOVER, layout[m_iHover]->m_strSample);

         }

         pgraphics->draw(pbox->m_rect, pbox->m_dib->get_graphics());

      }

   }


   void font_list::_001OnDrawSingleColumn(::draw2d::graphics * pgraphics, layout * playout)
   {

      synch_lock sl(m_pmutex);

      layout & layout = *playout;

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      //rect rectClient = m_rectClient;

      for (int i = 0; i < layout.get_count(); i++)
      {

         if (layout[i] == NULL)
         {

            continue;

         }

         int iBox;
         iBox = BOX;


         text_box * pbox = &layout[i]->m_box[iBox];


         rect r = pbox->m_rect;

         r.right = r.left + playout->m_size.cx;

         if (!pbox->m_bOk)
         {

            pbox->update(this, iBox, layout[i]->m_strSample);

         }
         if (i == m_iSel)
         {

            if (i == m_iHover)
            {

               pgraphics->fill_solid_rect(r, playout->_001GetColor(::user::color_background_selected_hover));

            }
            else
            {

               pgraphics->fill_solid_rect(r, playout->_001GetColor(::user::color_background_selected));

            }

         }
         else if (i == m_iHover)
         {

            pgraphics->fill_solid_rect(r, playout->_001GetColor(::user::color_background_hover));

         }

         pgraphics->draw(pbox->m_rect, pbox->m_dib->get_graphics());

      }

      //if (m_iSel >= 0)
      //{

      //   text_box * pbox = &layout[m_iSel]->m_box[BOX_SEL];

      //   if (!pbox->m_bOk)
      //   {

      //      pbox->update(this, BOX_SEL, layout[m_iSel]->m_strSample);

      //   }

      //   pgraphics->draw(pbox->m_rect, pbox->m_dib->get_graphics());

      //}

      //if (m_iHover >= 0 && m_iHover != m_iSel)
      //{

      //   text_box * pbox = &layout[m_iHover]->m_box[BOX_HOVER];

      //   if (!pbox->m_bOk)
      //   {

      //      pbox->update(this, BOX_HOVER, layout[m_iHover]->m_strSample);

      //   }

      //   pgraphics->draw(pbox->m_rect, pbox->m_dib->get_graphics());

      //}

   }

   void font_list::_001OnDraw(::draw2d::graphics * pgraphics, layout * playout)
   {

      synch_lock sl(m_pmutex);

      if (playout->m_elayout == layout_wide)
      {

         _001OnDrawWide(pgraphics, playout);

      }
      else
      {

         _001OnDrawSingleColumn(pgraphics, playout);

      }


   }


   void font_list::update()
   {

      try
      {

         synch_lock sl(m_pmutex);

         if (m_pfontenumeration.is_null())
         {

            m_pfontenumeration = System.visual().fonts().m_pfontenumeration;

         }

         synch_lock slEnum(m_pfontenumeration->m_pmutex);

         if (::lemon::array::are_all_elements_equal(m_pfontenumeration->m_itema, m_itema))
         {

            return;

         }

         m_itema = m_pfontenumeration->m_itema;

         m_iUpdate++;

      }
      catch (...)
      {


      }

   }


   void font_list::defer_update_layout(layout * playout)
   {

      index iCount;

      {

         synch_lock sl(m_pmutex);

         synch_lock slLayout(playout->m_pmutex);

         if (playout->get_count() == m_itema.get_count() && playout->m_iUpdate == m_iUpdate)
         {

            return;

         }

         playout->m_iUpdate = m_iUpdate;

         iCount = m_itema.get_count();

         playout->set_size(iCount);

         output_debug_string("Middle");

         m_iUpdated = 0;

         output_debug_string("End");

      }

      ::fork_count(get_app(), iCount, [=](index iOrder, index i, index iCount, index iScan)
      {

         layout & layout = *playout;

         ::draw2d::graphics_sp g(allocer());

         g->CreateCompatibleDC(NULL);

         ::draw2d::graphics * pgraphics = g;

         string strText = m_strTextLayout;

         size s;

         rect r;

         int_array iaSize;

         if (layout.m_elayout == layout_wide)
         {

            int i = 18;
            int iAddUp = 12;
            iaSize.add(18);
            iaSize.add(30);
            iaSize.add(42);

         }
         else
         {

            iaSize.add(18);

         }

         for (; i < iCount; i += iScan)
         {

            {

               synch_lock sl(m_pmutex);

               synch_lock slLayout(playout->m_pmutex);

               item * pitem = canew(item());

               layout[i] = pitem;

               pitem->m_strFont = m_itema[i]->m_strFile;

               pitem->m_strName = m_itema[i]->m_strName;

               string str = pitem->m_strFont;

               for (index j = 0; j < iaSize.get_count(); j++)
               {

                  text_box * pbox = &pitem->m_box[j];

                  pbox->m_font.alloc(allocer());

                  pbox->m_dib.alloc(allocer());

                  if (str.compare_ci("GOUDY STOUT") == 0)
                  {

                     output_debug_string("test05");

                  }

                  pbox->m_font->create_pixel_font(str, iaSize[j]);

                  pgraphics->SelectFont(pbox->m_font);

                  pbox->m_font->m_ecs = m_itema[i]->m_ecs;

                  if (j == 0)
                  {

                     strText = m_strTextLayout;

                     if (strText.is_empty() || (pbox->m_font->m_ecs != ::draw2d::font::cs_ansi && pbox->m_font->m_ecs != ::draw2d::font::cs_default))
                     {

                        strText = ::draw2d::font::get_sample_text(pbox->m_font->m_ecs);

                        if (strText.is_empty())
                        {

                           strText = pitem->m_strName;

                        }

                     }

                     s = pgraphics->GetTextExtent(strText);

                     if (strText.has_char() && s.area() <= 0)
                     {

                        string strSample;
                        int maxarea = 0;
                        //::draw2d::font::e_cs ecs;
                        ::draw2d::font::e_cs ecsFound = pbox->m_font->m_ecs;
                        size sSample;


                        if (maxarea <= 0)
                        {

                           strSample = m_strTextLayout;

                           if (strSample.has_char())
                           {

                              sSample = pgraphics->GetTextExtent(strSample);

                              if (sSample.area() > maxarea)
                              {

                                 maxarea = (int)(sSample.area());

                                 strText = strSample;

                                 s = sSample;

                              }

                           }

                        }

                        if (maxarea <= 0)
                        {

                           strSample = pitem->m_strName[i];

                           if (strSample.has_char())
                           {

                              sSample = pgraphics->GetTextExtent(strSample);

                              if (sSample.area() > maxarea)
                              {

                                 maxarea = (int)(sSample.area());

                                 strText = strSample;

                                 s = sSample;

                              }

                           }

                        }

                        pbox->m_font->m_ecs = ecsFound;


                     }
                     pitem->m_strSample = strText;

                  }
                  else
                  {

                     pbox->m_font->m_ecs = pitem->m_box[j - 1].m_font->m_ecs;

                     s = pgraphics->GetTextExtent(pitem->m_strSample);

                  }

                  s.cx += m_rectMargin.left + m_rectMargin.right;
                  s.cy += m_rectMargin.top + m_rectMargin.bottom;

                  pbox->m_size = s;

                  pbox->m_bOk = false;

                  m_iUpdated++;


               }

            }



            for (auto * pui : m_uiptra)
            {

               try
               {

                  pui->set_need_layout();

               }
               catch (...)
               {

               }


            }

         }

      }
                  );



   }


   bool font_list::on_layout(layout * playout)
   {

      synch_lock sl(m_pmutex);

      if (playout->m_elayout == layout_wide)
      {

         return on_layout_wide(playout);

      }
      else
      {

         return on_layout_single_column(playout);

      }

   }


   bool font_list::on_layout_wide(layout * playout)
   {

      layout & layout = *playout;

      string strText = m_strTextLayout;

      size s;

      int x = 0;

      int y = 0;

      int h = 0;

      int hExtra = 0;

      int nextx;

      playout->m_size.cx = m_rectClient.width();

      for (int i = 0; i < layout.get_count(); i++)
      {

         item * pitem = layout[i];

         if (pitem == NULL)
         {

            playout->m_size.cy = y + hExtra + 5;

            return false;

         }

         size & s = pitem->m_box[0].m_size;

         rect & r = pitem->m_box[0].m_rect;

         nextx = x + s.cx;

         if (nextx >= m_rectClient.width())
         {
            x = 0;
            nextx = s.cx;
            y += h;
            h = 0;
            hExtra = 0;
         }

         //pgraphics->text_out(x + m_rectMargin.left,y + m_rectMargin.top,strText);

         r.left = x;
         r.top = y;
         r.right = r.left + s.cx;
         r.bottom = r.top + s.cy;

         x = nextx;

         h = MAX(h, s.cy);

         hExtra = MAX(hExtra, s.cy);

         for (index j = 1; j < 3; j++)
         {

            size & s2 = pitem->m_box[j].m_size;
            rect & r2 = pitem->m_box[j].m_rect;

            int dw = (s2.cx - s.cx) / 2;
            int dh = (s2.cy - s.cy) / 2;

            r2.left = r.left - dw;
            r2.top = r.top - dh;
            r2.right = r2.left + s2.cx;
            r2.bottom = r2.top + s2.cy;

            hExtra = MAX(hExtra, s2.cy);

         }

      }

      playout->m_size.cy = y + hExtra + 5;

      return true;

   }


   bool font_list::on_layout_single_column(layout * playout)
   {

      layout & layout = *playout;

      string strText = m_strTextLayout;

      size s;

      int h = 0;

      int nextx;

      playout->m_size.cx = 0;

      int xSingleColumn = 0;
      int ySingleColumn = 0;

      for (int i = 0; i < layout.get_count(); i++)
      {

         item * pitem = layout[i];

         if (pitem == NULL)
         {

            playout->m_size.cy = ySingleColumn;

            return false;

         }

         size & s = pitem->m_box[0].m_size;

         rect & r = pitem->m_box[0].m_rect;



         pitem->m_box[0].m_rect.left = xSingleColumn;
         pitem->m_box[0].m_rect.top = ySingleColumn;
         pitem->m_box[0].m_rect.right = xSingleColumn + s.cx;
         pitem->m_box[0].m_rect.bottom = ySingleColumn + s.cy;

         playout->m_size.cx = MAX(playout->m_size.cx, pitem->m_box[0].m_rect.right + 4);

         ySingleColumn += s.cy;

         h = MAX(h, s.cy);

      }

      playout->m_size.cy = ySingleColumn;

      return true;

   }



   index font_list::hit_test(point pt, layout * playout)
   {

      synch_lock sl(m_pmutex);

      layout & layout = *playout;

      if (layout.m_elayout == layout_wide)
      {

         return hit_test_wide(pt, playout);

      }
      else
      {

         return hit_test_single_column(pt, playout);

      }

      return -1;

   }


   index font_list::hit_test_wide(point pt, layout * playout)
   {

      layout & layout = *playout;

      for (index i = 0; i < layout.get_size(); i++)
      {

         if (layout[i] == NULL)
         {

            continue;

         }

         //if (i == m_iSel)
         //{
         //   if (layout[i]->m_box[BOX_SEL].m_rect.contains(pt))
         //   {

         //      return i;
         //   }
         //}
         //else if (i == m_iHover)
         //{
         //   if (layout[i]->m_box[BOX_HOVER].m_rect.contains(pt))
         //   {

         //      return i;
         //   }
         //}
         //else
         {
            if (layout[i]->m_box[BOX].m_rect.contains(pt))
            {

               return i;
            }
         }

      }

      return -1;
   }


   index font_list::hit_test_single_column(point pt, layout * playout)
   {

      layout & layout = *playout;

      for (index i = 0; i < layout.get_size(); i++)
      {

         if (layout[i] == NULL)
         {

            continue;

         }

         rect r(layout[i]->m_box[BOX].m_rect);

         r.right = r.left + layout.m_size.cx;

         if (r.contains(pt))
         {

            return i;
         }

      }

      return -1;

   }


   index font_list::find_name(string str, layout * playout)
   {

      layout & layout = *playout;

      return layout.pred_find_first([&](item *pitem)
      {

         return pitem != NULL && pitem->m_strName.compare_ci(str) == 0;

      });

   }



} // namespace user

















