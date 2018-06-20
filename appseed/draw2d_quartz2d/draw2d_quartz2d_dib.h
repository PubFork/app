#pragma once

namespace draw2d_quartz2d
{

   //////////////////////////////////////////////////////////////////////
   //   Creator : El Barto (ef00@luc.ac.be)
   //   Location : http://www.luc.ac.be/~ef00/ebgfx
   //   Date : 09-04-98
   //////////////////////////////////////////////////////////////////////

   class CLASS_DECL_DRAW2D_QUARTZ2D dib :
      virtual public ::draw2d::dib
   {
   public:

/*      static float Cosines[360];
      static float Sines[360];
      static int64_t CosN[360]; // * 1 << 31
      static int64_t SinN[360];
      static int64_t Cos10N[10]; // until 10 degress
      static int64_t Sin10N[10]; // more precision * 1 << 34
      static double dPi;*/
      
      //BITMAPINFO                 m_info;
      ::draw2d::bitmap_sp        m_spbitmap;
      ::draw2d::graphics_sp      m_spgraphics;
//      class size               m_size;
 //     bool                       m_bMapped;
      //HBITMAP                  m_hbitmapOriginal;
      
      
      
      
      
      
      
      
      
      dib(sp(::aura::application) papp);
      virtual void construct(int32_t cx, int32_t cy) override;
      virtual ~dib();
      
      
      virtual bool detach(::draw2d::dib * pdib) override;

      
      void map(bool bApplyAlphaTransform = true) const override;
      void unmap() const override;
      
      
      virtual ::draw2d::graphics * get_graphics() const override;
      virtual ::draw2d::bitmap_sp get_bitmap() const override;
      virtual ::draw2d::bitmap_sp detach_bitmap() override;
      
      
      virtual COLORREF * get_data() const override;
      
      void stretch_dib(::draw2d::dib * pdib) override;
      
      bool dc_select(bool bSelect = true) override;
      
      
      
      
      
      bool create(class size size) override;
      bool create(int32_t iWidth, int32_t iHeight) override;
      bool create(::draw2d::graphics * pgraphics) override;
      bool Destroy();
      
      
      
      bool from(point ptDest, ::draw2d::graphics * pgraphics, point pt, class size sz) override;
      bool to(::draw2d::graphics * pgraphics, point pt, class size size, point ptSrc) override;
      
      void SetIconMask(::visual::icon * picon, int32_t cx, int32_t cy) override;
      
      virtual void set_mapped() override;
      
      virtual bool blend(point ptDst, ::draw2d::dib * pdibSrc, point ptSrc, class size size, byte bA) override;
      
      
   };

} // namespace draw2d_quartz2d
