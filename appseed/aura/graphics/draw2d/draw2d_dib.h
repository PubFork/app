#pragma once


struct NSVGimage;


namespace draw2d
{

   enum e_mipmap
   {

      mipmap_none,
      mipmap_isotropic, // 3x original size (a bit more or less if there are scan adjustments)
      mipmap_anisotropic, // 4x original size (a bit more or less if there are scan adjustments)

   };

   //////////////////////////////////////////////////////////////////////
   //   Creator : El Barto (ef00@luc.ac.be)
   //   Location : http://www.luc.ac.be/~ef00/ebgfx
   //   Date : 09-04-98
   //////////////////////////////////////////////////////////////////////


   class CLASS_DECL_AURA dib :
      virtual public ::object
   {
   public:




      enum e_type
      {

         type_complex,
         type_plain_color

      };


      class descriptor
      {
      public:

         e_type            m_etype;
         COLORREF          m_cr;
         class size        m_size;

         bool operator == (const descriptor & d) const
         {

            if(m_etype != d.m_etype)
               return false;

            if(m_size != d.m_size)
               return false;

            switch(m_etype)
            {
            case type_plain_color:
               return m_cr == d.m_cr;
            default:
               return true;
            };

         }

         bool operator != (const descriptor & d) const
         {
            return !operator ==(d);
         }

      };

      double                     m_dIsotropicRate;
      ::file::path               m_pathCache;
      COLORREF *                 m_pcolorref;
      class ::size               m_size;
      class ::size               m_sizeAlloc;
      i32                        m_iScan;
      bool                       m_bMapped; // optionally used by implementation
      descriptor                 m_descriptor;
      bool                       m_bReduced; // optionally used by implementation
      point                      m_pt;
      double                     m_dFontFactor;
      e_alpha_mode               m_ealphamode;
      bool                       m_bOwn;
      memory                     m_memoryMap;
      e_mipmap                   m_emipmap;
      sp(::draw2d::dib)          m_pnext;
      bool                       m_bColorMatrix;
      ::draw2d::color_matrix     m_colormatrix;



      static float Cosines[360];
      static float Sines[360];
      static int64_t CosN[360]; // * 1 << 31
      static int64_t SinN[360];
      static int64_t Cos10N[10]; // until 10 degress
      static int64_t Sin10N[10]; // more precision * 1 << 34
      static double dPi;


      dib();
      virtual ~dib();


      void draw2d_dib_common_construct();


      virtual ::draw2d::graphics * get_graphics() const; // is semantically const (besides may not be implementationly constant)
      virtual ::draw2d::bitmap_sp get_bitmap() const; // is semantically const (besides may not be implementationly constant)
      virtual ::draw2d::bitmap_sp detach_bitmap();

      inline ::draw2d::graphics * g() const { return get_graphics(); }

      virtual ::count get_dib_count();
      virtual ::draw2d::dib * get_dib(index i);

      virtual COLORREF * get_data() const;

      virtual void set_mipmap(e_mipmap emipmap);
      virtual void _set_mipmap(e_mipmap emipmap);

      //virtual bool add_next(double dRate);
      virtual bool create_isotropic(::draw2d::dib * pdib);
      virtual bool create_isotropic(double_array & daRate, ::multithreading::e_priority epriority);

      virtual void SetViewportOrg(point pt);
      virtual void set_font_factor(double dFactor);
      virtual void set_alpha_mode(e_alpha_mode e_alpha_mode);


      virtual void create_helper_map();

      virtual void on_load_image();
      virtual void on_exif_orientation();

      virtual void construct(i32 cx, i32 cy);

      virtual void stretch_dib(dib * pdib);

      virtual ::size get_size() const;

      class size & size() { return m_size; }
      const class size & size() const { return m_size; }

      class ::rect rect(point pt = ::null_point()) { return ::rect(pt, m_size); }
      const class rect rect(point pt = ::null_point()) const { return ::rect(pt, m_size); }


      void rate_rgb(int iMul,int iDiv);
      virtual bool dc_select(bool bSelect = true);

      virtual COLORREF GetAverageColor();
      virtual COLORREF GetAverageOpaqueColor();
      virtual bool blend(dib * pdib, dib * pdibRate);
      virtual bool Blend(dib *pdib, dib * pdibA, i32 A);
      virtual bool Blend(dib *pdib, dib * pdibA);
      virtual bool blend(point ptDst, ::draw2d::dib * pdibSrc, point ptSrc, ::draw2d::dib * pdibAlf, point ptDstAlf, class size size);
      virtual bool precision_blend(point ptDst, ::draw2d::dib * pdibAlf, point ptAlf, class size size);
      virtual bool precision_blend(point ptDst, ::draw2d::dib * pdibAlf, point ptAlf, class size size, byte bA);
      virtual bool blend(point ptDst, ::draw2d::dib * pdibAlf, point ptAlf, class size size);
      virtual bool blend(point ptDst, ::draw2d::dib * pdibAlf, point ptAlf, class size size, byte bA);
      virtual bool blend2(point ptDst, ::draw2d::dib * pdibSrc, point ptSrc, class size size, byte bA);
      virtual bool fork_blend(point ptDst, ::draw2d::dib * pdibAlf, point ptAlf, class size size);
      virtual bool fork_blend(point ptDst, ::draw2d::dib * pdibAlf, point ptAlf, class size size, byte bA);
      virtual bool bitmap_blend(::draw2d::graphics * pgraphics, LPCRECT lprect);
      virtual bool color_blend(COLORREF cr, BYTE bAlpha);
      virtual void BitBlt(dib * pdib, i32 op);
      virtual void BitBlt(int cxParam, int cyParam, dib * pdib,i32 op);
      virtual i32 cos(i32 i, i32 iAngle);
      virtual i32 sin(i32 i, i32 iAngle);
      virtual i32 cos10(i32 i, i32 iAngle);
      virtual i32 sin10(i32 i, i32 iAngle);

      virtual void hue_offset(double dRate);

      virtual void map(bool bApplyAlphaTransform = true) const; // some implementations may requrire to map to m_pcolorref before manipulate it
      virtual void unmap() const; // some implementations may require to unmap from m_pcolorref to update *os* bitmap
      virtual void set_mapped();

      virtual bool flip_vertical(::draw2d::dib * pdib);
      virtual bool flip_horizontal(::draw2d::dib * pdib);
      virtual void flipx(::draw2d::dib * pdib);
      virtual void flipy(::draw2d::dib * pdib);
      virtual dib & flipx();
      virtual dib & flipy();

      virtual bool is_rgb_black();
      virtual void do_xor(dib * pdib);

      virtual void ToAlpha(i32 i);
      virtual void ToAlphaAndFill(i32 i, COLORREF cr);
      virtual void GrayToARGB(COLORREF cr);

      virtual void from_alpha();
      virtual void mult_alpha(::draw2d::dib * pdibWork, bool bPreserveAlpha = true);

      virtual void mult_alpha();
      virtual void mult_alpha_fast();
      virtual void div_alpha();

      virtual void mult_alpha(point pt, ::size sz);
      virtual void div_alpha(point pt, ::size sz);

      virtual void rotate(dib * pdib, LPCRECT lpcrect, double dAngle, double dScale);
      virtual void rotate(dib * pdib, double dAngle, double dScale);
      virtual bool rotate(dib * pdib, double dAngle);
      virtual void Rotate034(dib * pdib, double dAngle, double dScale);

      virtual bool rotate90(dib * pdib);
      virtual bool rotate180(dib * pdib);
      virtual bool rotate270(dib * pdib);
      virtual bool rotate90();
      virtual bool rotate180();
      virtual bool rotate270();
      virtual bool rotate90flipx(dib * pdib);
      virtual bool rotate180flipx(dib * pdib);
      virtual bool rotate270flipx(dib * pdib);
      virtual bool rotate90flipx();
      virtual bool rotate180flipx();
      virtual bool rotate270flipx();


      virtual void set_rgb(COLORREF cr);
      virtual void set_rgb(i32 R, i32 G, i32 B);
      virtual void tint(::draw2d::dib * pdib, i32 R, i32 G, i32 B);
      virtual void set_rgb_pre_alpha(i32 R, i32 G, i32 B, i32 A);
      virtual bool rgb_from(::draw2d::dib * pdib);


      virtual void saturation(double dRate);


      virtual void SetIconMask(::visual::icon * picon, i32 cx, i32 cy);
      virtual void RadialFill(BYTE a, BYTE r, BYTE g, BYTE b, i32 x, i32 y, i32 iRadius);
      virtual void RadialFill(
      BYTE a1, BYTE r1, BYTE g1, BYTE b1, // center colors
      BYTE a2, BYTE r2, BYTE g2, BYTE b2, // border colors
      i32 x, i32 y, i32 iRadius);

      virtual void gradient_fill(COLORREF clr1, COLORREF clr2, POINT pt1, POINT pt2);
      virtual void gradient_horizontal_fill(COLORREF clr1, COLORREF clr2, int start, int end);
      virtual void gradient_vertical_fill(COLORREF clr1, COLORREF clr2, int start, int end);
      virtual void gradient_horizontal_fill(COLORREF clr1, COLORREF clr2);
      virtual void gradient_vertical_fill(COLORREF clr1, COLORREF clr2);

      inline COLORREF pixel(int x, int y)
      {
         return ::draw2d::get_pixel(m_pcolorref, m_iScan, m_size.cy, x, y);
      }

      virtual uint32_t GetPixel(i32 x, i32 y);
      virtual void Mask(COLORREF crMask, COLORREF crInMask, COLORREF crOutMask);
      virtual void channel_mask(BYTE uchFind, BYTE uchSet, BYTE uchUnset, visual::rgba::echannel echannel);
      virtual void transparent_color(color color);

      virtual bool create(class size);
      virtual bool create(i32 iWidth, i32 iHeight);
      virtual bool host(COLORREF * pcolorref, int iScan, i32 iWidth, i32 iHeight);
      virtual bool create(::draw2d::graphics * pgraphics);
      virtual bool destroy();
      virtual bool detach(::draw2d::dib * pdib);

      // realization is semantically const
      // dib keeps an image and image will be the same,
      // besides the way the Device Context associated with the dib (m_spgraphics)
      // interprets or deals with it, may change
      virtual bool realize(::draw2d::graphics * pgraphics) const;
      virtual bool unrealize() const;
      virtual bool is_realized() const;
      virtual bool defer_realize(::draw2d::graphics * pgraphics) const;

      virtual void DivideRGB(i32 iDivide);
      virtual void DivideARGB(i32 iDivide);
      virtual void DivideA(i32 iDivide);

      virtual bool to(dib * pdib) const;
      virtual bool from(const ::draw2d::dib * pdib);
      virtual bool from(::draw2d::graphics * pgraphics);
      virtual bool from(point ptDst, ::draw2d::graphics * pgraphics, point ptSrc, class size size);
      virtual bool from(point ptDst, ::draw2d::dib * pdc, point ptSrc, class size size);
      virtual bool from(point ptDst, ::draw2d::dib * pdc, point ptSrc, class size size, byte bA);
      //virtual bool blend(point ptDst, ::draw2d::dib * pdc, point ptSrc, class size size);
      virtual bool from_ignore_alpha(point ptDst, ::draw2d::dib * pdc, point ptSrc, class size size);

      virtual bool to(::draw2d::graphics * pgraphics);
      virtual bool to(::draw2d::graphics * pgraphics, point pt);
      virtual bool to(::draw2d::graphics * pgraphics, class size size);
      virtual bool to(::draw2d::graphics * pgraphics, point pt, class size size);
      virtual bool to(::draw2d::graphics * pgraphics, const RECT & lpcrect);
      virtual bool to(::draw2d::graphics * pgraphics, point pt, class size size, point ptSrc);


      virtual bool pixelate(i32 iSize);



      virtual void fill_channel(i32 C, visual::rgba::echannel echannel);
      virtual void white_fill_channel(i32 C, visual::rgba::echannel echannel);
      virtual void FillByte(uchar uch);
      virtual void Fill(COLORREF level);
      virtual void Fill (i32 A, i32 R, i32 G, i32 B);
//      virtual void Fill(i32 R, i32 G, i32 B);
      virtual void set(i32 R, i32 G, i32 B);
      virtual void FillGlass(i32 R, i32 G, i32 B, i32 A);
      virtual void FillStippledGlass(i32 R, i32 G, i32 B);
      virtual void Invert();
      virtual void channel_invert(visual::rgba::echannel echannel);
      virtual void channel_multiply(visual::rgba::echannel echannel, double dRate, bool bIfAlphaIgnorePreDivPosMult = false);
      virtual void channel_multiply(visual::rgba::echannel echannel, ::draw2d::dib * pdib, bool bIfAlphaIgnorePreDivPosMult = false);
      virtual void channel_lighten(visual::rgba::echannel echannel, ::draw2d::dib * pdib);
      virtual void channel_darken(visual::rgba::echannel echannel, ::draw2d::dib * pdib);
      virtual void channel_from(visual::rgba::echannel echannel, ::draw2d::dib * pdib);
      virtual void channel_multiply(visual::rgba::echannel echannel, ::draw2d::dib * pdib, LPCRECT lpcrect, bool bIfAlphaIgnorePreDivPosMult = false);
      virtual void channel_from(visual::rgba::echannel echannel, ::draw2d::dib * pdib, LPCRECT lpcrect);
      virtual void channel_copy(visual::rgba::echannel echannelDst, visual::rgba::echannel echannelSrc);
      virtual void channel_copy(visual::rgba::echannel echannelDst, visual::rgba::echannel echannelSrc, ::draw2d::dib * pdib);

      virtual void Map (i32 ToRgb, i32 FromRgb);

      virtual void create_nanosvg(string str);
      virtual void nanosvg(NSVGimage * pimage);
      virtual void nanosvg(string str);

      virtual bool op(string str);

      //virtual void from( dib * pdib);

      virtual void Blend(dib * pdib, i32 A);
      virtual void Darken(dib * pdib);
      virtual void Difference(dib * pdib);
      virtual void Lighten(dib * pdib);
      virtual void Multiply(dib * pdib);
      virtual void Screen(dib * pdib);

      virtual void lighten(double dRate);

      virtual void copy(dib * pdib, i32 x, i32 y);
      virtual void PasteRect(dib * pdib, i32 x, i32 y);

      virtual void fill_rect(LPCRECT lpcrect, COLORREF cr);
      virtual void fill_rect(LPCRECT lpcrect, i32 R, i32 G, i32 B);

      virtual void fill_glass_rect(LPCRECT lpcrect, i32 R, i32 G, i32 B, i32 A);
      virtual void fill_stippled_glass_rect(LPCRECT lpcrect, i32 R, i32 G, i32 B);

      virtual void BlendRect(dib * pdib, i32 x, i32 y, i32 A);
      virtual void DarkenRect(dib * pdib, i32 x, i32 y);
      virtual void DifferenceRect(dib * pdib, i32 x, i32 y);
      virtual void LightenRect(dib * pdib, i32 x, i32 y);
      virtual void MultiplyRect(dib * pdib, i32 x, i32 y);
      virtual void ScreenRect(dib * pdib, i32 x, i32 y);

      virtual void horizontal_line(i32 y, i32 R, i32 G, i32 B, i32 A = 0, i32 x1 = 0, i32 x2 = -1);
      virtual void Line(i32 x1, i32 y1, i32 x2, i32 y2, i32 R, i32 G, i32 B);
      virtual void LineGlass(i32 x1, i32 y1, i32 x2, i32 y2, i32 R, i32 G, i32 B, i32 A);

      virtual void create_frame(class size size, i32 iFrameCount);
      virtual void set_frame2(void * lpdata, i32 iFrame, i32 iFrameCount);
      virtual void set_frame1(void * lpdata, i32 iFrame, i32 iFrameCount);
      virtual void get_frame(void * lpdata, i32 iFrame, i32 iFrameCount);
      virtual void xor_dib_frame2(void * lpdata, i32 iFrame, i32 iFrameCount);

      virtual bool create_circle(dib * pdib, int diameter);
      virtual bool create_framed_square(dib * pdib, int inner, int outer, COLORREF cr);


      virtual void invert_rgb(LPCRECT lpcrect);


      //virtual i32 width();
      //virtual i32 height();
      inline int64_t area() const
      {
         return m_size.area();
      }

      virtual double pi() const;

      virtual void io(stream & stream);

      //virtual bool update_window(::aura::draw_interface * pui,::message::message * pobj,bool bTransferBuffer = true);
      //virtual bool print_window(::aura::draw_interface * pui,::message::message * pobj);


      static void static_initialize();

      virtual COLORREF make_colorref(i32 a, i32 r, i32 g, i32 b);

      dib & operator = (const dib & dib);

      virtual int64_t scan_area();

      virtual bool load_thumbnail(const char * pszPath);


      inline void fill_rect_dim(i32 x, i32 y, i32 w, i32 h, COLORREF cr) { return fill_rect(::rect_dim(x, y, w, h), cr); }
      inline void fill_rect_dim(i32 x, i32 y, i32 w, i32 h, i32 R, i32 G, i32 B) { return fill_rect(::rect_dim(x, y, w, h), R, G, B); }
      inline void fill_rect_coord(i32 x1, i32 y1, i32 x2, i32 y2, COLORREF cr) { return fill_rect(::rect(x1, y1, x2, y2), cr); }
      inline void fill_rect_coord(i32 x1, i32 y1, i32 x2, i32 y2, i32 R, i32 G, i32 B) { return fill_rect(::rect(x1, y1, x2, y2), R, G, B); }


      virtual void defer_save_to_cache();

      virtual void save_to_dib(const ::file::path & pathDib);
      virtual bool load_from_dib(const ::file::path & pathDib);

      inline int line(int line)
      {

#ifdef MACOS
         return m_size.cy - line - 1;
#else
         return line;
#endif

      }

   };


   using dib_sp = sp(dib);

   class thread_tool :
      virtual public ::thread_tool
   {
   public:

      enum e_op
      {

         op_blend,

      };

      int m_ySkip;
      int m_y;
      int m_yEnd;
      int m_x;
      int m_xEnd;
      byte * m_pdst2;
      byte * m_psrc2;
      byte * m_pdstOpacity; // opacity map if available
      byte * m_psrcOpacity; // opacity map if available
      byte * m_pdstTransparency; // transparency map if available
      byte * m_psrcTransparency; // transparency map if available
      int m_w;
      int m_h;
      e_op m_eop;
      int m_scanSrc;
      int m_scanDst;
      byte m_bA;



      virtual void run() override;

   };


} // namespace draw2d


template < >
inline UINT HashKey<const ::draw2d::dib::descriptor &>(const ::draw2d::dib::descriptor  & key)
{
   UINT ui = (UINT) key.m_etype;
   if(key.m_etype == ::draw2d::dib::type_plain_color)
   {
      ui |= key.m_cr;
   }
   return ui;
}



namespace draw2d
{

   CLASS_DECL_AURA void dib_copy(dib * pdibthis, dib *pdib);
   CLASS_DECL_AURA void dib_alloc(::aura::application * papp, dib * & pdib);
   CLASS_DECL_AURA void dib_create(dib * pdib, int w, int h);
   CLASS_DECL_AURA unsigned int * dib_get_data(dib * pdib);
   CLASS_DECL_AURA graphics * dib_get_graphics(dib * pdib);


} // namespace draw2d






