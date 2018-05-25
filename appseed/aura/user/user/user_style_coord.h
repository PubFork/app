#pragma once


namespace user
{

   class CLASS_DECL_AURA style_coord
   {
   public:


      ::draw2d::e_unit     m_eunit;
      double               m_d;


      LONG get_pixel(::draw2d::graphics * pgraphics, e_orientation eorientation);
      double get_dimension(::draw2d::graphics * pgraphics, e_orientation eorientation);

      void set_pixel(double d);
      void set_point(double d);
      void set(double d, ::draw2d::e_unit eunit = ::draw2d::unit_em);


   };


} // namespace user



