//#include "framework.h" // from "base/user/user.h"
//#include "base/user/user.h"


namespace user
{


   schema_simple_impl::schema_simple_impl(::aura::application * papp)  :
      object(papp)
   {

      m_etranslucency      = translucency_underfined;

   }


   schema_simple_impl::~schema_simple_impl()
   {

   }


   bool schema_simple_impl::set_color(e_color ecolor,COLORREF cr)
   {

      m_mapColor[ecolor] = cr;

      return true;

   }


   bool schema_simple_impl::get_color(COLORREF & cr, e_color ecolor)
   {

      if (m_mapColor.Lookup(ecolor, cr))
      {

         return true;

      }

      return false;

   }

   bool schema_simple_impl::get_font(::draw2d::font_sp & font, e_font efont, ::user::interaction * pui)
   {

      if(m_pfont.is_null())
         return false;

      font = m_pfont;

      return true;

   }


   bool schema_simple_impl::on_ui_event(e_event eevent, e_object eobject, ::user::interaction * pui)
   {

      return false;

   }

   bool schema_simple_impl::get_translucency(e_translucency & etranslucency)
   {

      if(m_etranslucency == translucency_underfined)
         return false;

      etranslucency = m_etranslucency;

      return true;

   }


} // namespace user











