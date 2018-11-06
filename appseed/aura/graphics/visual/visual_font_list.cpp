#include "framework.h"

#include <math.h>

#define BOX 0
#define BOX_SEL 1
#define BOX_HOVER 2


namespace visual
{


   font_list_item::font_list_item()
   {

   }


   font_list_item::~font_list_item()
   {

   }


   font_list::font_list(::aura::application * papp) :
      object(papp)
   {

      m_pevLayoutReady = NULL;
      m_iLayoutId = -1;
      m_rectMargin = rect(5, 5, 5, 5);
      m_iSel = -1;
      m_iHover = -1;

      defer_create_mutex();

      m_dwaFg.add(ARGB(255, 80, 80, 80));
      m_dwaFg.add(ARGB(255, 45, 45, 45));
      m_dwaFg.add(ARGB(255, 255, 255, 255));

      m_dwaBg.add(ARGB(0, 0, 0, 0));
      m_dwaBg.add(ARGB(128, 128, 200, 152));
      m_dwaBg.add(ARGB(128, 80, 80, 80));

      m_etype = type_single_column;

   }


   font_list::~font_list()
   {


   }


   void font_list::update()
   {

      try
      {

         synch_lock sl(m_pmutex);

         if (m_pfontenumeration.is_null())
         {

            System.visual().fonts().defer_create_font_enumeration();

            m_pfontenumeration = System.visual().fonts().m_pfontenumeration;

         }

         m_pitema = m_pfontenumeration->m_pitema;

      }
      catch (...)
      {

      }

   }


   void font_list::_001OnDrawWide(::draw2d::graphics * pgraphics)
   {

      synch_lock sl(m_pmutex);

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      for (int i = 0; i < m_itema.get_count(); i++)
      {

         if (m_itema[i].is_null())
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

         text_box * pbox = &m_itema[i]->m_box[iBox];

         if (!pbox->m_bOk)
         {

            pbox->update(this, iBox, m_itema[i]->m_strSample);

         }

         pgraphics->draw(pbox->m_rect, pbox->m_dib->get_graphics());

      }

      if (m_iSel >= 0)
      {

         text_box * pbox = &m_itema[m_iSel]->m_box[BOX_SEL];

         if (!pbox->m_bOk)
         {

            pbox->update(this, BOX_SEL, m_itema[m_iSel]->m_strSample);

         }

         pgraphics->draw(pbox->m_rect, pbox->m_dib->get_graphics());

      }

      if (m_iHover >= 0 && m_iHover != m_iSel)
      {

         text_box * pbox = &m_itema[m_iHover]->m_box[BOX_HOVER];

         if (!pbox->m_bOk)
         {

            pbox->update(this, BOX_HOVER, m_itema[m_iHover]->m_strSample);

         }

         pgraphics->draw(pbox->m_rect, pbox->m_dib->get_graphics());

      }

   }


   void font_list::_001OnDrawSingleColumn(::draw2d::graphics * pgraphics)
   {

      synch_lock sl(m_pmutex);

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      for (int i = 0; i < m_itema.get_count(); i++)
      {

         if (m_itema[i] == NULL)
         {

            continue;

         }

         int iBox;
         iBox = BOX;


         text_box * pbox = &m_itema[i]->m_box[iBox];


         rect r = pbox->m_rect;

         r.right = r.left + m_size.cx;

         if (!pbox->m_bOk)
         {

            pbox->update(this, iBox, m_itema[i]->m_strSample);

         }
         if (i == m_iSel)
         {

            if (i == m_iHover)
            {

               pgraphics->fill_solid_rect(r, _001GetColor(::user::color_background_selected_hover));

            }
            else
            {

               pgraphics->fill_solid_rect(r, _001GetColor(::user::color_background_selected));

            }

         }
         else if (i == m_iHover)
         {

            COLORREF cr = _001GetColor(::user::color_background_hover);
            int iA = argb_get_a_value(cr);
            pgraphics->fill_solid_rect(r, cr);
            //pgraphics->fill_solid_rect(r, ARGB(255,0, 0, 0));

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


   void font_list::_001OnDraw(::draw2d::graphics * pgraphics)
   {

      synch_lock sl(m_pmutex);

      if (m_etype == type_wide)
      {

         _001OnDrawWide(pgraphics);

      }
      else
      {

         _001OnDrawSingleColumn(pgraphics);

      }

   }


   void font_list::start_layout()
   {

      index iCount;

      int iBaseSize = 18;

      bool bFork = true;

      int_array iaSize;

      {

         synch_lock sl(m_pmutex);

         if (m_rectClient.area() <= 0 && m_etype != type_single_column)
         {

            return;

         }

         if (m_itema.get_count() == m_pitema->get_count()
               && m_iLayoutId == m_pfontenumeration->m_iUpdateId
               && (m_etype == type_single_column ||
                   m_rectClient == m_rectLayout))
         {

            return;

         }

         if (m_bOnLayout)
         {

            if (m_pthreadDelayedLayout.is_null())
            {

               m_pthreadDelayedLayout = fork([this]()
               {

                  Sleep(300);

                  {

                     synch_lock sl(m_pmutex);

                     m_pthreadDelayedLayout.release();

                  }

                  start_layout();

               });

            }

            return;

         }

         m_bOnLayout = true;

         m_rectLayout = m_rectClient;

         m_iLayoutId = m_pfontenumeration->m_iUpdateId;

         iCount = m_pitema->get_count();

         m_itema.set_size(iCount);

         output_debug_string("Middle");

         m_iUpdated = 0;

         output_debug_string("End");

         if (m_etype == type_wide)
         {

            iBaseSize = ((m_rectClient.height() / 10) / 4) * 4;

            iBaseSize = MAX(18, MIN(iBaseSize, 80));

         }
         else
         {

            iBaseSize = 18;

         }

         if (m_etype == type_wide)
         {

            int i = 18;

            int iAddUp = 12;

            iaSize.add(iBaseSize * 18 / 42);

            iaSize.add(iBaseSize * 30 / 42);

            iaSize.add(iBaseSize * 42 / 42);

         }
         else
         {

            iaSize.add(18);

         }

         if (m_iLayoutId == m_pfontenumeration->m_iUpdateId
               && iBaseSize == m_iBaseSizeLayout)
         {

            bFork = false;

         }
         else
         {

            output_debug_string("It would do extra unneeded fork with just this condition.");

         }

         if (m_iLayoutId == m_pfontenumeration->m_iUpdateId
               && iaSize == m_iaSizeLayout)
         {

            bFork = false;

         }

      }

      if (!bFork)
      {

         _on_end_layout();

         return;

      }

      m_iBaseSizeLayout = iBaseSize;

      m_iaSizeLayout = iaSize;

      fork_count_end_pred(this, iCount, [this, iBaseSize, iaSize](index iOrder, index i, index iCount, index iScan)
      {

         ::draw2d::graphics_sp g(allocer());

         g->CreateCompatibleDC(NULL);

         ::draw2d::graphics * pgraphics = g;

         string strText = m_strTextLayout;

         size s;

         rect r;

         sp(font_list_item) pitem;

         for (; i < iCount; i += iScan)
         {

            {

               pitem = canew(font_list_item());

               {

                  synch_lock sl(m_pmutex);

                  pitem->m_strFont     = m_pitema->ptr_at(i)->m_strFile;

                  pitem->m_strName     = m_pitema->ptr_at(i)->m_strName;

                  pitem->m_echarseta   = m_pitema->ptr_at(i)->m_echarseta;

               }

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

                  pbox->m_font->m_echarseta = pitem->m_echarseta;

                  if (j == 0)
                  {

                     strText = m_strTextLayout;

                     if (strText.is_empty() ||
                           (pbox->m_font->get_char_set(pgraphics) != ::draw2d::font::char_set_ansi
                            && pbox->m_font->get_char_set(pgraphics) != ::draw2d::font::char_set_default))
                     {

                        strText = ::draw2d::font::get_sample_text(pbox->m_font->m_echarset);

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

                        ::draw2d::font::e_char_set echarsetFound = pbox->m_font->get_char_set(pgraphics);

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

                        pbox->m_font->m_echarset = echarsetFound;

                     }

                     pitem->m_strSample = strText;

                  }
                  else
                  {

                     pbox->m_font->m_echarset = pitem->m_box[j - 1].m_font->m_echarset;

                     s = pgraphics->GetTextExtent(pitem->m_strSample);

                  }

                  s.cx += m_rectMargin.left + m_rectMargin.right;

                  s.cy += m_rectMargin.top + m_rectMargin.bottom;

                  pbox->m_size = s;

                  pbox->m_bOk = false;

                  {

                     synch_lock sl(m_pmutex);

                     m_itema[i] = pitem;

                     m_iUpdated++;

                     _on_end_layout();

                     //for (auto * pui : m_uiptra)
                     //{

                     //   try
                     //   {

                     //      pui->set_need_layout();

                     //   }
                     //   catch (...)
                     //   {

                     //   }

                     //}

                  }

               }

            }

         }

      },

      [this]()
      {

         _on_end_layout();

      });

   }


   void font_list::_on_end_layout()
   {

      synch_lock sl(m_pmutex);

      try
      {

         on_layout();

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

         if (m_pevLayoutReady != NULL)
         {

            try
            {

               m_pevLayoutReady->set_event();

            }
            catch (...)

            {


            }

            m_pevLayoutReady = NULL;

         }

      }
      catch (...)
      {


      }

      m_bOnLayout = false;

   }


   void font_list::on_layout()
   {

      synch_lock sl(m_pmutex);

      if (m_etype == type_wide)
      {

         return on_layout_wide();

      }
      else
      {

         return on_layout_single_column();

      }

   }


   void font_list::on_layout_wide()
   {

      synch_lock sl(m_pmutex);

      string strText = m_strTextLayout;

      size s;

      int x = 0;

      int y = 0;

      int h = 0;

      int hExtra = 0;

      int nextx;

      m_size.cx = m_rectClient.width();

      for (int i = 0; i < m_itema.get_count(); i++)
      {

         font_list_item * pitem = m_itema[i];

         if (pitem == NULL)
         {

            m_size.cy = y + hExtra + 5;

            return;

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

      m_size.cy = y + hExtra + 5;


   }


   void font_list::on_layout_single_column()
   {

      synch_lock sl(m_pmutex);

      string strText = m_strTextLayout;

      size s;

      int h = 0;

      m_size.cx = 0;

      int xSingleColumn = 0;
      int ySingleColumn = 0;

      for (int i = 0; i < m_itema.get_count(); i++)
      {

         font_list_item * pitem = m_itema[i];

         if (pitem == NULL)
         {

            m_size.cy = ySingleColumn;

            return;

         }

         size & s = pitem->m_box[0].m_size;

         rect & r = pitem->m_box[0].m_rect;



         pitem->m_box[0].m_rect.left = xSingleColumn;
         pitem->m_box[0].m_rect.top = ySingleColumn;
         pitem->m_box[0].m_rect.right = xSingleColumn + s.cx;
         pitem->m_box[0].m_rect.bottom = ySingleColumn + s.cy;

         m_size.cx = MAX(m_size.cx, pitem->m_box[0].m_rect.right + 4);

         ySingleColumn += s.cy;

         h = MAX(h, s.cy);

      }

      m_size.cy = ySingleColumn;

   }



   index font_list::hit_test(point pt)
   {

      synch_lock sl(m_pmutex);

      if (m_etype == type_wide)
      {

         return hit_test_wide(pt);

      }
      else
      {

         return hit_test_single_column(pt);

      }

      return -1;

   }


   index font_list::hit_test_wide(point pt)
   {

      synch_lock sl(m_pmutex);

      for (index i = 0; i < m_itema.get_size(); i++)
      {

         if (m_itema[i] == NULL)
         {

            continue;

         }


         if (m_itema[i]->m_box[BOX].m_rect.contains(pt))
         {

            return i;
         }

      }

      return -1;

   }


   index font_list::hit_test_single_column(point pt)
   {

      synch_lock sl(m_pmutex);

      for (index i = 0; i < m_itema.get_size(); i++)
      {

         if (m_itema[i] == NULL)
         {

            continue;

         }

         rect r(m_itema[i]->m_box[BOX].m_rect);

         r.right = r.left + m_size.cx;

         if (r.contains(pt))
         {

            return i;
         }

      }

      return -1;

   }


   index font_list::find_name(string str)
   {

      synch_lock sl(m_pmutex);

      return m_itema.pred_find_first([&](font_list_item *pitem)
      {

         return pitem != NULL && pitem->m_strName.compare_ci(str) == 0;

      });

   }


   void font_list::layout(bool bSynch)
   {

      update();

      if (!bSynch)
      {

         start_layout();

         return;

      }

      manual_reset_event ev(get_app());

      m_pevLayoutReady = &ev;

      ev.ResetEvent();

      start_layout();

      ev.wait(seconds(30));

      m_pevLayoutReady = NULL;


   }


} // namespace user



