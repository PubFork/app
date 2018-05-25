#pragma once


namespace user
{


   class CLASS_DECL_AURA style_rect
   {
   public:


      style_coord   left;
      style_coord   top;
      style_coord   right;
      style_coord   bottom;


      void get_rect(LPRECT lprect, ::draw2d::graphics * pgraphics);
      void set_rect(LPCRECT lpcrect);
      void set_pixel_rect_coord(double l, double t, double r, double b);
      void set_pixel_rect_dim(double l, double t, double w, double h);
      void set_pixel_rect(rectd r);
      void set_point_rect_coord(double l, double t, double r, double b);
      void set_point_rect_dim(double l, double t, double w, double h);
      void set_point_rect(rectd r);
      void set_rect_coord(double l, double t, double r, double b, ::draw2d::e_unit eunit = ::draw2d::unit_em);
      void set_rect_dim(double l, double t, double w, double h, ::draw2d::e_unit eunit = ::draw2d::unit_em);
      void set_rect(rectd d, ::draw2d::e_unit eunit = ::draw2d::unit_em);


   };


} // namespace user



