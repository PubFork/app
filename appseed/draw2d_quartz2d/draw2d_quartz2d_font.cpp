#include "framework.h"


namespace draw2d_quartz2d
{
   
   
   font::font(::aura::application * papp) :
      ::object(papp)
   {
      
      m_font = NULL;
      
      m_fontD = NULL;
      
      m_fontName = NULL;
      
      defer_create_mutex();
      
   }
   
   
   font::~font()
   {
      
      if(m_fontName != NULL)
      {
         
         CFRelease(m_fontName);
         
         m_fontName = NULL;
         
      }
      
      if(m_fontD != NULL)
      {
         
         CFRelease(m_fontD);
         
         m_fontD = NULL;
         
      }
      
      if(m_font != NULL)
      {
      
         CFRelease(m_font);
         
         m_font = NULL;
         
      }

   }
   
   
#ifdef DEBUG

   void font::dump(dump_context & dumpcontext) const
   {
      
      ::draw2d::font::dump(dumpcontext);
      
   }

#endif
   
   void * font::get_os_data() const
   {
      
      throw interface_only_exception(get_app());
      
      return NULL;
      
   }
   
   
   void font::metrics::get(CGFloat * pascent, CGFloat * pdescent, CGFloat * pleading, CGFloat * pwidth)
   {
      
      if(pascent != NULL)
      {
         
         *pascent = ascent;
         
      }
      
      if(pdescent != NULL)
      {
         
         *pdescent = descent;
         
      }
      
      if(pleading != NULL)
      {
         
         *pleading = leading;
         
      }
      
      if(pwidth != NULL)
      {
         
         *pwidth = width;
         
      }
  
   }
   
   
   void font::metrics::align(double & x, double & y, double wAlign, UINT nFormat)
   {
   
      if(nFormat & DT_RIGHT)
      {
      
         x += wAlign - width;
      
      }
      else if(nFormat & DT_CENTER)
      {
      
         x += (wAlign - width) / 2.0;
      
      }
   
      if(nFormat & (DT_BOTTOM | DT_VCENTER))
      {
      
         double cy = -(ascent + descent + leading);
         
         if(leading <= 0)
         {
            
            cy -= descent;
            
         }
         
         if(nFormat & DT_VCENTER)
         {
          
            cy /= 2.0;
            
         }

         y += cy;
         
      }
      
   }

   
} // namespace draw2d_quartz2d





