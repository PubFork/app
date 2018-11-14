#pragma once


struct FIBITMAP;


namespace visual
{

   namespace image
   {

      enum e_format
      {
         format_png,
         format_bmp,
         format_gif,
         format_jpeg,
      };

   } // namespace image

   class CLASS_DECL_AURA save_image
   {
   public:


      image::e_format         m_eformat;
      int                     m_iQuality;
      int                     m_iDpi;

      save_image();

   };

   
   enum e_load
   {
      
      load_none,
      load_going_to_load,
      load_fail,
      load_ok,
      
   };

   
   enum e_disposal
   {
      disposal_undefined = 0,
      disposal_none = 1,
      disposal_background = 2,
      disposal_previous = 3
   };


   class CLASS_DECL_AURA dib_sp :
      public ::draw2d::dib_sp
   {
   public:


      class pointer :
         virtual public ::object
      {
      public:


         rect                 m_rect;
         ::draw2d::dib_sp     m_dib;
         DWORD                m_dwTime;
         e_disposal           m_edisposal;
         COLORREF             m_crTransparent;
         bool                 m_bTransparent;
         bool                 m_bLocalPalette;

         pointer();
         virtual ~pointer();


         virtual bool to(::draw2d::graphics * pgraphics);

      };


      class array :
         virtual public spa(pointer)
      {
      public:


         DWORD                m_dwStart;
         DWORD                m_dwTotal;
         unsigned int         m_uiLoopCount; // 0 - infinite loop
         unsigned int         m_uiLoop;
         int                  m_iTransparentIndex;
         bool                 m_bTransparent;
         COLORREF             m_crTransparent;
         COLORREF             m_crBack;
         BYTE                 m_backgroundIndex;
         ::size               m_sizeLogical;
         ::size               m_size;
         index                m_iLastFrame;
         bool                 m_bStart;
         ::draw2d::dib_sp     m_dibCompose;
         ::array <COLORREF>   m_cra;


         array(::aura::application * papp);
         virtual ~array();


         class size & size() { return m_size; }
         const class size & size() const { return m_size; }

         class rect rect(point pt = ::null_point()) { return ::rect(pt, m_size); }
         const class rect rect(point pt = ::null_point()) const { return ::rect(pt, m_size); }

      };


      sp(array)            m_sparray;
      e_load               m_eload;
      double               m_dSpeed;


      dib_sp();
      dib_sp(const ::aura::allocatorsp & allocer);
      ~dib_sp();

      virtual bool dispose_current_frame();
      virtual bool overlay_frame(int iFrame);
      virtual void defer_update();



      virtual bool load_from_file(var varFile, bool bCache = true, bool bCreateHelperMaps = false);
      virtual bool load_from_matter(const char * pszMatter,bool bCache = true, bool bCreateHelperMaps = false);
      virtual bool read_from_file(::file::file_sp  pfile);


      virtual bool load_matter_icon(stringa & straMatter, string strIcon);


      virtual bool load_thumbnail(var varFile, int w, int h);


      virtual bool save_to_file(var varFile, save_image * psaveimage = NULL);
      virtual bool write_to_file(var  varFile, save_image * psaveimage = NULL);


      inline dib_sp & operator = (::draw2d::dib * p)
      {

         ::draw2d::dib_sp::operator=(p);

         return *this;

      }


      inline dib_sp & operator = (const dib_sp & dib)
      {

         if (this != &dib)
         {

            ::draw2d::dib_sp::operator=(dib.m_p);

            m_sparray = dib.m_sparray;

            m_eload = dib.m_eload;

            m_dSpeed = dib.m_dSpeed;

         }

         return *this;

      }


//#ifndef  WINDOWS
//      virtual bool from(::draw2d::graphics * pgraphics, FIBITMAP * pfibitmap, bool bUnloadFI);
//#endif

   };


} // namespace visual


CLASS_DECL_AURA void draw_freetype_bitmap(::draw2d::dib * m_p,int32_t dx,int32_t dy,void * pftbitmap,int x,int y);
CLASS_DECL_AURA void draw_freetype_bitmap(::draw2d::dib * m_p,int32_t dx,int32_t dy,void * pftbitmap,int x,int y,byte a,byte r,byte g,byte b);












