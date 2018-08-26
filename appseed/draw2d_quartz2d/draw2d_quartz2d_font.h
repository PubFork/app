#pragma once


namespace draw2d_quartz2d
{
   
   
   class CLASS_DECL_DRAW2D_QUARTZ2D font :
      virtual public ::draw2d::font
   {
   public:
   
      class metrics
      {
      public:
         
         
         CGFloat ascent;
         CGFloat descent;
         CGFloat leading;
         CGFloat width;
         
         // mode, brush color, pen color
         isomap < CGTextDrawingMode, colorrefmap < colorrefmap < CTLineRef > > > m_map;

         
         metrics() {}
         ~metrics() {}
         
         void get(CGFloat * pascent, CGFloat * pdescent, CGFloat * pleading, CGFloat * pwidth);
         
         void align(double & x, double & y, double wAlign, UINT nFormat);
         
      };
      
      string_map < metrics >  m_mapMetrics;
      CTFontRef               m_font;
      CTFontDescriptorRef     m_fontD;
      CFStringRef             m_fontName;
      
      
      font(::aura::application * papp);
      virtual ~font();
      
      
   
      virtual bool destroy() override;
      
      virtual void * get_os_data() const;
      
#ifdef DEBUG

      virtual void dump(dump_context & dumpcontext) const;
#endif

      
   };
   
   
} // namespace draw2d_quartz2d



