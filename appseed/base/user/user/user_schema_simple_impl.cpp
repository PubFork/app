//#include "framework.h" // from "base/user/user.h"
//#include "base/user/user.h"


namespace user
{


   schema_simple_impl::schema_simple_impl(::aura::application * papp)  :
      object(papp)
   {

<<<<<<< HEAD
      m_etranslucency      = translucency_underfined;
=======
      m_etranslucency      = translucency_undefined;
>>>>>>> feature/stringa_001Explode

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

<<<<<<< HEAD
      if(m_etranslucency == translucency_underfined)
=======
      if(m_etranslucency == translucency_undefined)
>>>>>>> feature/stringa_001Explode
         return false;

      etranslucency = m_etranslucency;

      return true;

   }
   
   
   bool schema_simple_impl::prepare_menu_button(::user::menu_item * pitem)
   {
      
      if(!::user::style::prepare_menu_button(pitem))
      {
         
         return false;
         
      }
      
      sp(::user::button) pbutton = pitem->m_pui;
      
      if(pbutton->m_id == "close")
      {
         
         pbutton->m_pschema = m_pschemaSysMenuCloseButton;
         
         pbutton->resize_to_fit();
         
         pbutton->set_stock_icon(stock_icon_close);
         
         return true;
         
      }
      else
      {
         
         pbutton->m_pschema = m_pschemaItemButton;
         
         int cx = pbutton->width();
         
         int cy = pbutton->height();
         
         pbutton->m_pitem = pitem;
         
         pbutton->m_rectCheckBox.left = m_rectItemMargin.left;
         pbutton->m_rectCheckBox.top = m_rectItemMargin.top;
         pbutton->m_rectCheckBox.bottom = cy - m_rectItemMargin.bottom;
         pbutton->m_rectCheckBox.right = puiButton->m_rectCheckBox.left + m_iCheckBoxSize;
         
         pbutton->m_rectText.left = puiButton->m_rectCheckBox.right + m_iElementPadding;
         pbutton->m_rectText.top = m_rectItemMargin.top;
         pbutton->m_rectText.bottom = cy - m_rectItemMargin.bottom;
         pbutton->m_rectText.right = cx - m_rectItemMargin.right;
         
      }
      
      return true;
      
   }



} // namespace user











