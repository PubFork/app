#include "framework.h"


namespace visual
{


   font_enumeration::font_enumeration(::aura::application * papp) :
      object(papp)
   {

      m_iUpdateId = -1;

   }


   font_enumeration::~font_enumeration()
   {

   }


   bool font_enumeration::check_need_update()
   {

      ::draw2d::graphics_sp g(allocer());

      g->CreateCompatibleDC(NULL);

      sp(::draw2d::font::enum_item_array) pitema;

      pitema = canew(::draw2d::font::enum_item_array);

      g->sorted_fonts(*pitema);

      if (m_pitema.is_set() && ::lemon::array::are_all_elements_equal(*pitema, *m_pitema))
      {

         return false;

      }

      m_pitema = pitema;

      m_iUpdateId++;

      return true;

   }


} // namespace visual



