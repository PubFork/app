#include "framework.h"


namespace user
{


   void style_rect::get_rect(LPRECT lprect, ::draw2d::graphics * pgraphics)
   {

      lprect->left = left.get_pixel(pgraphics, orientation_horizontal);
      lprect->top = top.get_pixel(pgraphics, orientation_vertical);
      lprect->right = right.get_pixel(pgraphics, orientation_horizontal);
      lprect->bottom = bottom.get_pixel(pgraphics, orientation_vertical);

   }


   void style_rect::set_pixel_rect_coord(double l, double t, double r, double b)
   {

      set_rect_coord(l, t, r, b, ::draw2d::unit_pixel);

   }


   void style_rect::set_pixel_rect_dim(double l, double t, double w, double h)
   {

      set_rect_dim(l, t, w, h, ::draw2d::unit_pixel);

   }


   void style_rect::set_pixel_rect(rectd r)
   {

      set_rect(r, ::draw2d::unit_pixel);

   }


   void style_rect::set_point_rect_coord(double l, double t, double r, double b)
   {

      set_rect_coord(l, t, r, b, ::draw2d::unit_point);

   }


   void style_rect::set_point_rect_dim(double l, double t, double w, double h)
   {

      set_rect_dim(l, t, w, h, ::draw2d::unit_point);

   }


   void style_rect::set_point_rect(rectd r)
   {

      set_rect(r, ::draw2d::unit_point);

   }


   void style_rect::set_rect_coord(double l, double t, double r, double b, ::draw2d::e_unit eunit)
   {

      left.set(l, eunit);
      top.set(t, eunit);
      right.set(r, eunit);
      bottom.set(b, eunit);

   }


   void style_rect::set_rect_dim(double l, double t, double w, double h, ::draw2d::e_unit eunit)
   {

      set_rect_coord(l, t, l + w, t + h, eunit);

   }


   void style_rect::set_rect(rectd r, ::draw2d::e_unit eunit)
   {

      set_rect_coord(r.left, r.top, r.right, r.bottom, eunit);

   }


} // namespace user



