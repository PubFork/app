#include "framework.h"


namespace user
{


   LONG style_coord::get_pixel(::draw2d::graphics * pgraphics, e_orientation eorientation)
   {

      return (LONG) get_dimension(pgraphics, eorientation);

   }


   double style_coord::get_dimension(::draw2d::graphics * pgraphics, e_orientation eorientation)
   {

      if (m_eunit == ::draw2d::unit_em)
      {

         if (pgraphics == NULL)
         {

            throw simple_exception(::get_app(), "no graphics context supplied");

         }
         else if (pgraphics->m_spfont.is_set())
         {

            return m_d * pgraphics->m_spfont->get_pixel_font_height(pgraphics);

         }
         else
         {

            throw simple_exception(::get_app(), "no font is selected");

         }

      }
      else if (m_eunit == ::draw2d::unit_point)
      {

         if (pgraphics == NULL)
         {

            throw simple_exception(::get_app(), "no graphics context supplied");

         }
         else if (eorientation == orientation_horizontal)
         {

            return m_d * pgraphics->get_dpix() / 72.0;

         }
         else
         {

            return m_d * pgraphics->get_dpiy() / 72.0;

         }

      }

      return m_d;

   }


   void style_coord::set_pixel(double d)
   {

      set(d, ::draw2d::unit_pixel);

   }


   void style_coord::set_point(double d)
   {

      set(d, ::draw2d::unit_point);

   }


   void style_coord::set(double d, ::draw2d::e_unit eunit)
   {

      m_eunit = eunit;

      m_d = d;

   }


} // namespace user



