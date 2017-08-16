#include "framework.h" // previously aura/user/user.h


namespace aura
{


   void drawable::_001OnDraw(::draw2d::graphics * pgraphics)
   {

      UNREFERENCED_PARAMETER(pgraphics);

   }


   
   void draw_interface::_000OnDraw(::draw2d::graphics * pgraphics)
   {
   }
   
   void draw_interface::_001DeferPaintLayeredWindowBackground(::draw2d::graphics * pgraphics)
   {
   }
   
   void draw_interface::_001OnDeferPaintLayeredWindowBackground(::draw2d::graphics * pgraphics)
   {
   }
   
   bool draw_interface::GetWindowRect(LPRECT lprect)
   {
   
      null_rect(lprect);
      
      return true;
      
   }
   
   bool draw_interface::GetWindowRect(RECT64 * lprect)
   {
    
      null_rect(lprect);
      
      return true;
      
   }
   rect draw_interface::GetWindowRect()
   {
      
      return null_rect();
      
   }
   rect64 draw_interface::GetWindowRect64()
   
   {
      
      return null_rect64();
      
   }
   
   
   ::window_graphics * draw_interface::get_window_graphics()
   {
   
      return NULL;
      
   }
   
   
   
   oswindow draw_interface::get_handle() const
   {
      
      return NULL;
      
   }
   
      bool draw_interface::is_composite()
      {
         return false;
      }
      
      
} // namespace user



