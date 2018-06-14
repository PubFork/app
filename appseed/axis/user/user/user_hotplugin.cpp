#include "framework.h"


namespace hotplugin
{


   CLASS_DECL_AXIS void entry_hall_windows_on_paint(::draw2d::graphics * pgraphics, const RECT & rect, const string & strEntryHallText)
   {

      int h = 33;
      int m = 49 * 2;

      int top;
      int bottom;
      int left;
      int right;

      if (height(rect) < h)
      {
         top = rect.top;
         bottom = rect.bottom;
      }
      else
      {
         top = rect.top + height(rect) / 2 - h / 2;
         bottom = rect.top + height(rect) / 2 + h / 2;
      }

      if (width(rect) < m)
      {
         left = rect.left;
         right = rect.right;
      }
      else
      {

         left = rect.left + MIN(m / 2, width(rect) / 2);
         right = rect.right - MIN(m / 2, width(rect) / 2);

      }

      ::rect rectBar(left, top, right, bottom);

      int w = 284;

      int v = ::get_tick_count() * 484 / 1000;

      int x = v % rectBar.width();

      ::rect rectBrick(left + x, rectBar.top, left + x + w, rectBar.bottom);
      ::rect rectDraw;

      int32_t cx = width(rect);
      int32_t cy = height(rect);
      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      string str(strEntryHallText);

      if (str.is_empty())
      {

         //str = "ca2 plugin for Browsers : Internet Explorer compatible - ActiveX Tecnhology, Mozilla Firefox compatible - NPAPI : Netscape Plugin API";

         str = "Opening...";

      }

      bool bStatic = false;

      if (::str::begins_eat(str, "***"))
      {

         bStatic = true;

      }

      ::draw2d::brush_sp brush(::aura::system::g_p->allocer(), ARGB(184, 49, 49, 49));

      pgraphics->fill_rect(rectBar, brush);

      if (!bStatic)
      {

         ::draw2d::brush_sp brushGreen(::aura::system::g_p->allocer(), ARGB(190, 80, 190, 123));

         if (rectDraw.intersect(rectBar, rectBrick))
         {

            pgraphics->fill_rect(rectDraw, brushGreen);

         }

         rectBrick.offset(-rectBar.width(), 0);

         if (rectDraw.intersect(rectBar, rectBrick))
         {

            pgraphics->fill_rect(rectDraw, brushGreen);

         }

         rectBrick.offset(rectBar.width() * 2, 0);

         if (rectDraw.intersect(rectBar, rectBrick))
         {

            pgraphics->fill_rect(rectDraw, brushGreen);

         }

      }

      ::draw2d::pen_sp pen(pgraphics, 1.0f, ARGB(149, 149, 149, 142));

      pgraphics->draw_rect(rectBar, pen);

      ::draw2d::font_sp f(::aura::system::g_p->allocer());

      f->create_pixel_font("Calibri", 18.0);

      rectBar.left += 4;

      rectBar.top += 5;

      pgraphics->set_text_color(ARGB(184, 255, 255, 255));

      pgraphics->text_out(rectBar.left, rectBar.top, str);

   }


} // namespace hotplugin


