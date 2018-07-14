//   Creator : El Barto (ef00@luc.ac.be)
//   Location : http://www.luc.ac.be/~ef00/ebgfx
//   Date : 09-04-98
//////////////////////////////////////////////////////////////////////
#include "framework.h"
//#include "draw2d.h"
//#include <math.h>
#include <stdio.h>
#include "nanosvg.h"
#include "nanosvgrast.h"

#include "aura/graphics/graphics_double_pass_scale.h"

/*
byte byte_clip(double d);


inline byte byte_clip(double d)
{
   if(d >= 255.0)
      return 255;
   if(d <= 0.0)
      return 0;
   return (byte) d;
}

inline byte byte_clip(int i)
{
   return MIN(255, MAX(0, i));
}
*/

#define byte_clip(i)  ((byte) (((i) < 0) ? 0 : (((i)> 255) ? 255 : i)))


namespace draw2d
{

   //   Creator : El Barto (ef00@luc.ac.be)
   //   Location : http://www.luc.ac.be/~ef00/ebgfx
   //   Date : 09-04-98
   //////////////////////////////////////////////////////////////////////


   float dib::Cosines[360];
   float dib::Sines[360];

   int64_t dib::CosN[360]; // * 1 << 31
   int64_t dib::SinN[360];

   int64_t dib::Cos10N[10]; // until 10 degress
   int64_t dib::Sin10N[10]; // more precision * 1 << 34

   double dib::dPi;


   dib::dib()
   {

      draw2d_dib_common_construct();

   }



   dib::~dib()
   {

   }


   void dib::draw2d_dib_common_construct()
   {

      m_pcolorref = NULL;
      m_dIsotropicRate = 1.0;
      m_size = ::size(0, 0);
      m_sizeAlloc = ::size(0, 0);
      m_iScan = 0;
      m_bMapped = false;
      m_descriptor.m_etype = type_complex;
      m_descriptor.m_cr = 0;
      m_descriptor.m_size = ::size(0, 0);
      m_bReduced = false;
      m_pt = point(0, 0);
      m_dFontFactor = 1.0;
      m_ealphamode = ::draw2d::alpha_mode_blend;
      m_bOwn = true;
      m_memoryMap.allocate(0);
      m_emipmap = mipmap_none;
      m_pathCache.Empty();

   }


   ::draw2d::graphics * dib::get_graphics() const
   {

      ::exception::throw_interface_only(get_app());

      return NULL;

   }


   ::draw2d::bitmap_sp dib::get_bitmap() const
   {

      ::exception::throw_interface_only(get_app());

      return NULL;

   }


   ::draw2d::bitmap_sp dib::detach_bitmap()
   {

      ::exception::throw_interface_only(get_app());

      return NULL;

   }


   void dib::construct(i32 cx, i32 cy)
   {

      UNREFERENCED_PARAMETER(cx);
      UNREFERENCED_PARAMETER(cy);

      ::exception::throw_interface_only(get_app());

   }


   COLORREF * dib::get_data() const
   {

      map();

      return m_pcolorref;

   }


   bool dib::realize(::draw2d::graphics * pgraphics) const
   {

      UNREFERENCED_PARAMETER(pgraphics);

      return true;

   }


   bool dib::unrealize() const
   {

      return true;

   }


   bool dib::is_realized() const
   {

      return true;

   }


   bool dib::defer_realize(::draw2d::graphics * pgraphics) const
   {

      if (is_realized())
         return true;

      return realize(pgraphics);

   }


   bool dib::create(class size size)
   {

      return create(size.cx, size.cy);

   }


   bool dib::create(i32 width, i32 height)
   {

      return create(::size(width, height));

   }


   bool dib::host(COLORREF * pcolorref, int iScan, i32 width, i32 height)
   {
      // callers should be able to deal with graphics backend that doesn't support "hosting" portions of RAM
      return false;

   }

   bool dib::dc_select(bool bSelect)
   {

      UNREFERENCED_PARAMETER(bSelect);

      ::exception::throw_interface_only(get_app());

      return false;

   }


   bool dib::create(::draw2d::graphics * pgraphics)
   {

      ::draw2d::bitmap & bitmap = *pgraphics->get_current_bitmap();

      if (is_null_ref(bitmap))
      {

         return false;

      }

      ::exception::throw_not_implemented(get_app());

      return false;

   }

   ::count dib::get_dib_count()
   {

      ::count c = 1;

      ::draw2d::dib * pdib = this;

      while (pdib->m_pnext.is_set())
      {

         c++;

         pdib = pdib->m_pnext;

      }

      return c;

   }

   ::draw2d::dib * dib::get_dib(index i)
   {

      ::draw2d::dib * pdib = this;

      while (i > 0)
      {

         if (pdib->m_pnext.is_null())
         {

            return NULL;

         }

         i--;

         pdib = pdib->m_pnext;

      }

      return pdib;


   }


   bool dib::create_isotropic(::draw2d::dib * pdib)
   {

      int cx = (int) (pdib->m_dIsotropicRate * m_size.cx);

      int cy = (int) (pdib->m_dIsotropicRate * m_size.cy);

      pdib->create(cx, cy);

      if (::multithreading::priority() == ::multithreading::priority_idle)
      {

         map();

         C2PassScale < CBlackmanFilter > scale(1.0);

         scale.Scale(
         pdib->m_pcolorref,
         pdib->m_size.cx,
         pdib->m_size.cy,
         pdib->m_iScan,
         m_pcolorref,
         m_size.cx,
         m_size.cy,
         m_iScan
         );

      }
      else
      {

         pdib->get_graphics()->SetStretchBltMode(HALFTONE);

         pdib->get_graphics()->StretchBlt(0, 0, cx, cy, get_graphics(), 0, 0, m_size.cx, m_size.cy);

      }

      pdib->set_mipmap(m_emipmap);

      return true;

   }


   bool dib::create_isotropic(double_array & daRate, ::multithreading::e_priority epriority)
   {

      daRate.sort(false);

      m_pnext.release();

      ::draw2d::dib * pdibLast = this;

      spa(dib) diba;

      for (const double & dRate : daRate)
      {

         pdibLast->m_pnext.alloc(allocer());

         pdibLast = pdibLast->m_pnext;

         pdibLast->m_dIsotropicRate = dRate;

         diba.add(pdibLast);

      }

      fork_count_end(get_app(), diba.get_count(),
                     [&](index i)
      {

         create_isotropic(diba[i]);

      }, 0, epriority);

      return true;

   }


   void dib::defer_save_to_cache()
   {

      if (m_pathCache.has_char())
      {

         ::file::path pathDib = m_pathCache;

         m_pathCache.Empty();

         sp(dib) pthis = this;

         fork([pthis, pathDib]()
         {

            sp(dib) pdib = pthis;

            pdib->save_to_dib(pathDib);

         });

      }

   }


   bool dib::load_from_dib(const ::file::path & pathDib)
   {

      ::file::file_sp file = Session.file().get_file(pathDib, ::file::mode_read | ::file::share_deny_write | ::file::type_binary);

      if (file.is_null())
      {

         return false;

      }

      destroy();

      ::reader reader(file);

      reader(this);

      if (reader.fail() || m_pcolorref == NULL || m_size.area() <= 0)
      {

         return false;

      }

      return true;

   }


   void dib::save_to_dib(const ::file::path & pathDib)
   {

      try
      {

         ::file::file_sp file = Application.file().get_file(pathDib, ::file::mode_create | ::file::mode_write | ::file::type_binary | ::file::defer_create_directory);

         if (file.is_set())
         {

            ::writer writer(file);

            writer(this);

         }

      }
      catch (...)
      {

      }

   }


   bool dib::destroy()
   {

      m_pnext.release();

      return true;

   }


   bool dib::detach(::draw2d::dib * pdib)
   {

      m_pcolorref       = pdib->m_pcolorref;
      m_size            = pdib->m_size;
      m_sizeAlloc       = pdib->m_sizeAlloc;
      m_iScan           = pdib->m_iScan;
      m_bMapped         = pdib->m_bMapped;
      m_descriptor      = pdib->m_descriptor;
      m_bReduced        = pdib->m_bReduced;
      m_pt              = pdib->m_pt;
      m_dFontFactor     = pdib->m_dFontFactor;
      m_ealphamode      = pdib->m_ealphamode;
      m_bOwn            = pdib->m_bOwn;
      m_memoryMap       = pdib->m_memoryMap;
      m_emipmap         = pdib->m_emipmap;
      m_pathCache       = pdib->m_pathCache;

      pdib->draw2d_dib_common_construct();

      return true;

   }


   bool dib::to(::draw2d::graphics * pgraphics)
   {

      return to(pgraphics, null_point(), size());

   }


   bool dib::to(::draw2d::graphics * pgraphics, point pt)
   {

      return to(pgraphics, pt, size());

   }


   bool dib::to(::draw2d::graphics * pgraphics, class size size)
   {

      return to(pgraphics, null_point(), size);

   }


   bool dib::to(::draw2d::graphics * pgraphics, const RECT & rect)
   {

      return to(pgraphics, ::top_left(rect), ::size(rect));

   }


   bool dib::to(::draw2d::graphics * pgraphics, point pt, class size size)
   {

      return to(pgraphics, pt, size, point(0, 0));

   }


   bool dib::to(::draw2d::graphics * pgraphics, point pt, class size size, point ptSrc)
   {


      UNREFERENCED_PARAMETER(pgraphics);
      UNREFERENCED_PARAMETER(pt);
      UNREFERENCED_PARAMETER(size);
      UNREFERENCED_PARAMETER(ptSrc);
      ::exception::throw_interface_only(get_app());

      return false;

   }


   //bool dib::from(::draw2d::dib * pdib)
   //{

   //   if(!create(pdib->size()))
   //      return false;

   //   map();
   //   pdib->map();
   //   try
   //   {
   //      memcpy(get_data(), pdib->get_data(), (size_t) (sizeof(COLORREF) * area()));
   //   }
   //   catch(...)
   //   {
   //      return false;
   //   }
   //   return true;
   //}


   bool dib::from(::draw2d::graphics * pgraphics)
   {

      UNREFERENCED_PARAMETER(pgraphics);

      ::exception::throw_interface_only(get_app());

      return false;

   }


   bool dib::from(point ptDst, ::draw2d::graphics * pgraphics, point ptSrc, class size size)
   {
      return get_graphics()->from(ptDst, size, pgraphics, ptSrc, SRCCOPY) != FALSE;
   }

   bool dib::from(point ptDst, ::draw2d::dib * pdibSrc, point ptSrc, class size size)
   {

      dib * pdibDst = this;

      if (
      (!pdibDst->m_bMapped && !pdibSrc->m_bMapped)
      ||
      (
      !(pdibDst->m_bMapped && pdibSrc->m_bMapped)
      &&
      (
      (pdibDst->m_bMapped && !pdibDst->get_graphics()->prefer_mapped_dib_on_mix())
      ||
      (pdibSrc->m_bMapped && !pdibSrc->get_graphics()->prefer_mapped_dib_on_mix())
      )
      )
      )
      {

         get_graphics()->set_alpha_mode(m_ealphamode);

         return get_graphics()->draw(ptDst, size, pdibSrc->get_graphics(), ptSrc);

      }

      pdibDst->map();

      pdibSrc->map();

      ptDst += m_pt;

      if (ptSrc.x < 0)
      {
         ptDst.x -= ptSrc.x;
         ptSrc.x = 0;
      }

      if (ptSrc.y < 0)
      {
         ptDst.y -= ptSrc.y;
         ptSrc.y = 0;
      }

      if (ptDst.x < 0)
      {
         size.cx += ptDst.x;
         ptDst.x = 0;
      }

      if (size.cx < 0)
         return true;

      if (ptDst.y < 0)
      {
         size.cy += ptDst.y;
         ptDst.y = 0;
      }

      if (size.cy < 0)
         return true;

      int xEnd = MIN(size.cx, MIN(pdibSrc->m_size.cx - ptSrc.x, pdibDst->m_size.cx - ptDst.x));

      int yEnd = MIN(size.cy, MIN(pdibSrc->m_size.cy - ptSrc.y, pdibDst->m_size.cy - ptDst.y));

      if (xEnd < 0)
         return false;

      if (yEnd < 0)
         return false;

      i32 scanDst = pdibDst->m_iScan;

      i32 scanSrc = pdibSrc->m_iScan;

      byte * pdst = &((byte *)pdibDst->m_pcolorref)[scanDst * ptDst.y + ptDst.x * sizeof(COLORREF)];

      byte * psrc = &((byte *)pdibSrc->m_pcolorref)[scanSrc * ptSrc.y + ptSrc.x * sizeof(COLORREF)];

      COLORREF * pdst2;

      COLORREF * psrc2;

      for (int y = 0; y < yEnd; y++)
      {

         pdst2 = (COLORREF *)&pdst[scanDst * y];

         psrc2 = (COLORREF *)&psrc[scanSrc * y];

         memcpy(pdst2, psrc2, xEnd * 4);
         //for(int x = 0; x < xEnd; x++)
         //{

         //   *pdst2 = *psrc2;

         //   pdst2++;

         //   psrc2++;

         //}
         //pdst2 += xEnd;
         //psrc2 += xEnd;

      }

      return true;

   }

   bool dib::from(point ptDst, ::draw2d::dib * pdibSrc, point ptSrc, class size size, byte bA)
   {

      dib * pdibDst = this;


      pdibDst->map();

      pdibSrc->map();

      ptDst += m_pt;

      if (ptSrc.x < 0)
      {
         ptDst.x -= ptSrc.x;
         ptSrc.x = 0;
      }

      if (ptSrc.y < 0)
      {
         ptDst.y -= ptSrc.y;
         ptSrc.y = 0;
      }

      if (ptDst.x < 0)
      {
         size.cx += ptDst.x;
         ptDst.x = 0;
      }

      if (size.cx < 0)
         return true;

      if (ptDst.y < 0)
      {
         size.cy += ptDst.y;
         ptDst.y = 0;
      }

      if (size.cy < 0)
         return true;

      int xEnd = MIN(size.cx, MIN(pdibSrc->m_size.cx - ptSrc.x, pdibDst->m_size.cx - ptDst.x));

      int yEnd = MIN(size.cy, MIN(pdibSrc->m_size.cy - ptSrc.y, pdibDst->m_size.cy - ptDst.y));

      if (xEnd < 0)
         return false;

      if (yEnd < 0)
         return false;

      i32 scanDst = pdibDst->m_iScan;

      i32 scanSrc = pdibSrc->m_iScan;

      byte * pdst = &((byte *)pdibDst->m_pcolorref)[scanDst * ptDst.y + ptDst.x * sizeof(COLORREF)];

      byte * psrc = &((byte *)pdibSrc->m_pcolorref)[scanSrc * ptSrc.y + ptSrc.x * sizeof(COLORREF)];

      byte * pdst2;

      byte * psrc2;

      for (int y = 0; y < yEnd; y++)
      {

         pdst2 = &pdst[scanDst * y];

         psrc2 = &psrc[scanSrc * y];

         //memcpy(pdst2, psrc2, xEnd * 4);
         for (int x = 0; x < xEnd; x++)
         {

            pdst2[0] = (psrc2[0] * bA) >> 8;
            pdst2[1] = (psrc2[1] * bA) >> 8;
            pdst2[2] = (psrc2[2] * bA) >> 8;
            pdst2[3] = (psrc2[3] * bA) >> 8;

            pdst2 += 4;

            psrc2 += 4;

         }
         //pdst2 += xEnd;
         //psrc2 += xEnd;

      }

      return true;

   }


   bool dib::blend2(point ptDst, ::draw2d::dib * pdibSrc, point ptSrc, class size size, byte bA)
   {

      dib * pdibDst = this;

      pdibDst->map();

      pdibSrc->map();

      ptDst += m_pt;

      if (ptSrc.x < 0)
      {
         ptDst.x -= ptSrc.x;
         ptSrc.x = 0;
      }

      if (ptSrc.y < 0)
      {
         ptDst.y -= ptSrc.y;
         ptSrc.y = 0;
      }

      if (ptDst.x < 0)
      {
         size.cx += ptDst.x;
         ptDst.x = 0;
      }

      if (size.cx < 0)
         return true;

      if (ptDst.y < 0)
      {
         size.cy += ptDst.y;
         ptDst.y = 0;
      }

      if (size.cy < 0)
         return true;

      int xEnd = MIN(size.cx, MIN(pdibSrc->m_size.cx - ptSrc.x, pdibDst->m_size.cx - ptDst.x));

      int yEnd = MIN(size.cy, MIN(pdibSrc->m_size.cy - ptSrc.y, pdibDst->m_size.cy - ptDst.y));

      if (xEnd < 0)
         return false;

      if (yEnd < 0)
         return false;

      i32 scanDst = pdibDst->m_iScan;

      i32 scanSrc = pdibSrc->m_iScan;

      byte * pdst = &((byte *)pdibDst->m_pcolorref)[scanDst * ptDst.y + ptDst.x * sizeof(COLORREF)];

      byte * psrc = &((byte *)pdibSrc->m_pcolorref)[scanSrc * ptSrc.y + ptSrc.x * sizeof(COLORREF)];

      byte * pdst2;

      byte * psrc2;

      if (bA == 0)
      {

      }
      else if (bA == 255)
      {

         for (int y = 0; y < yEnd; y++)
         {

            pdst2 = &pdst[scanDst * y];

            psrc2 = &psrc[scanSrc * y];

            for (int x = 0; x < xEnd; x++)
            {

               int  aDst = pdst2[3];

               int  aSrc = psrc2[3];

               if (aDst == 0)
               {

               }
               else if (aSrc == 0)
               {

                  *((COLORREF *)pdst2) = 0;

               }
               else
               {

                  int r = pdst2[0];
                  int g = pdst2[1];
                  int b = pdst2[2];

                  r = (r << 8) / aDst;
                  g = (g << 8) / aDst;
                  b = (b << 8) / aDst;

                  int a = aSrc * aDst;

                  pdst2[0] = (r * a) >> 16;
                  pdst2[1] = (g * a) >> 16;
                  pdst2[2] = (b * a) >> 16;
                  pdst2[3] = a >> 8;

               }

               pdst2 += 4;

               psrc2 += 4;

            }

         }

      }
      else
      {
         for (int y = 0; y < yEnd; y++)
         {

            pdst2 = &pdst[scanDst * y];

            psrc2 = &psrc[scanSrc * y];

            //memcpy(pdst2, psrc2, xEnd * 4);
            for (int x = 0; x < xEnd; x++)
            {

               //*pdst2 = *psrc2;

               //pdst2[0] = (psrc2[0] + (pdst2[0] * (255 - psrc2[3])) / 255);
               //pdst2[1] = (psrc2[1] + (pdst2[1] * (255 - psrc2[3])) / 255);
               //pdst2[2] = (psrc2[2] + (pdst2[2] * (255 - psrc2[3])) / 255);
               //pdst2[3] = (psrc2[3] + (pdst2[3] * (255 - psrc2[3])) / 255);
               //byte acomplement = (~psrc2[3] * bA) >> 8;
               //pdst2[0] = psrc2[0] + ((pdst2[0] * (acomplement)) >> 8);
               //pdst2[1] = psrc2[1] + ((pdst2[1] * (acomplement)) >> 8);
               //pdst2[2] = psrc2[2] + ((pdst2[2] * (acomplement)) >> 8);
               //pdst2[3] = psrc2[3] + ((pdst2[3] * (acomplement)) >> 8);
               byte acomplement = (~psrc2[3] * bA) >> 8;
               pdst2[0] = clip_byte(((psrc2[0] * bA) + (pdst2[0] * acomplement)) >> 8);
               pdst2[1] = clip_byte(((psrc2[1] * bA) + (pdst2[1] * acomplement)) >> 8);
               pdst2[2] = clip_byte(((psrc2[2] * bA) + (pdst2[2] * acomplement)) >> 8);
               pdst2[3] = clip_byte(((psrc2[3] * bA) + (pdst2[3] * acomplement)) >> 8);



               pdst2 += 4;

               psrc2 += 4;

            }
            //pdst2 += xEnd;
            //psrc2 += xEnd;

         }

      }

      return true;

   }

   bool dib::blend(point ptDst, ::draw2d::dib * pdibSrc, point ptSrc, class size size)
   {

      return blend(ptDst, pdibSrc, ptSrc, size, 255);

   }


   bool dib::blend(point ptDst, ::draw2d::dib * pdibSrc, point ptSrc, class size size, byte bA)
   {

      dib * pdibDst = this;


      pdibDst->map();

      pdibSrc->map();

      ptDst += m_pt;

      if (ptSrc.x < 0)
      {
         ptDst.x -= ptSrc.x;
         ptSrc.x = 0;
      }

      if (ptSrc.y < 0)
      {
         ptDst.y -= ptSrc.y;
         ptSrc.y = 0;
      }

      if (ptDst.x < 0)
      {
         size.cx += ptDst.x;
         ptDst.x = 0;
      }

      if (size.cx < 0)
         return true;

      if (ptDst.y < 0)
      {
         size.cy += ptDst.y;
         ptDst.y = 0;
      }

      if (size.cy < 0)
         return true;

      int xEnd = MIN(size.cx, MIN(pdibSrc->m_size.cx - ptSrc.x, pdibDst->m_size.cx - ptDst.x));

      int yEnd = MIN(size.cy, MIN(pdibSrc->m_size.cy - ptSrc.y, pdibDst->m_size.cy - ptDst.y));

      if (xEnd < 0)
         return false;

      if (yEnd < 0)
         return false;

      i32 scanDst = pdibDst->m_iScan;

      i32 scanSrc = pdibSrc->m_iScan;


      byte * pdst2;

      byte * psrc2;

#ifdef APPLEOS
      byte * pdst = &((byte *)pdibDst->m_pcolorref)[scanDst * (pdibDst->m_size.cy - ptDst.y - yEnd) + ptDst.x * sizeof(COLORREF)];

      byte * psrc = &((byte *)pdibSrc->m_pcolorref)[scanSrc * (pdibSrc->m_size.cy - ptSrc.y - yEnd) + ptSrc.x * sizeof(COLORREF)];

#else

      byte * pdst = &((byte *)pdibDst->m_pcolorref)[scanDst * ptDst.y + ptDst.x * sizeof(COLORREF)];

      byte * psrc = &((byte *)pdibSrc->m_pcolorref)[scanSrc *  ptSrc.y + ptSrc.x * sizeof(COLORREF)];

#endif

      bool bFontListBlend = true;

      if (bFontListBlend)
      {

         if (bA == 0)
         {

         }
         else if (bA == 255)
         {

            for (int y = 0; y < yEnd; y++)
            {

               pdst2 = &pdst[scanDst * y];

               psrc2 = &psrc[scanSrc * y];

               //memcpy(pdst2, psrc2, xEnd * 4);
               for (int x = 0; x < xEnd; x++)
               {

                  //*pdst2 = *psrc2;

                  //pdst2[0] = (psrc2[0] + (pdst2[0] * (255 - psrc2[3])) / 255);
                  //pdst2[1] = (psrc2[1] + (pdst2[1] * (255 - psrc2[3])) / 255);
                  //pdst2[2] = (psrc2[2] + (pdst2[2] * (255 - psrc2[3])) / 255);
                  //pdst2[3] = (psrc2[3] + (pdst2[3] * (255 - psrc2[3])) / 255);
                  byte acomplement = ~psrc2[3];
                  pdst2[0] = psrc2[0] + ((pdst2[0] * (acomplement)) >> 8);
                  pdst2[1] = psrc2[1] + ((pdst2[1] * (acomplement)) >> 8);
                  pdst2[2] = psrc2[2] + ((pdst2[2] * (acomplement)) >> 8);
                  pdst2[3] = psrc2[3] + ((pdst2[3] * (acomplement)) >> 8);



                  pdst2 += 4;

                  psrc2 += 4;

               }
               //pdst2 += xEnd;
               //psrc2 += xEnd;

            }
         }
         else
         {
            for (int y = 0; y < yEnd; y++)
            {

               pdst2 = &pdst[scanDst * y];

               psrc2 = &psrc[scanSrc * y];

               //memcpy(pdst2, psrc2, xEnd * 4);
               for (int x = 0; x < xEnd; x++)
               {

                  //*pdst2 = *psrc2;

                  //pdst2[0] = (psrc2[0] + (pdst2[0] * (255 - psrc2[3])) / 255);
                  //pdst2[1] = (psrc2[1] + (pdst2[1] * (255 - psrc2[3])) / 255);
                  //pdst2[2] = (psrc2[2] + (pdst2[2] * (255 - psrc2[3])) / 255);
                  //pdst2[3] = (psrc2[3] + (pdst2[3] * (255 - psrc2[3])) / 255);
                  //byte acomplement = (~psrc2[3] * bA) >> 8;
                  //pdst2[0] = psrc2[0] + ((pdst2[0] * (acomplement)) >> 8);
                  //pdst2[1] = psrc2[1] + ((pdst2[1] * (acomplement)) >> 8);
                  //pdst2[2] = psrc2[2] + ((pdst2[2] * (acomplement)) >> 8);
                  //pdst2[3] = psrc2[3] + ((pdst2[3] * (acomplement)) >> 8);
                  byte acomplement = (~psrc2[3] * bA) >> 8;
                  pdst2[0] = clip_byte(((psrc2[0] * bA) + (pdst2[0] * acomplement)) >> 8);
                  pdst2[1] = clip_byte(((psrc2[1] * bA) + (pdst2[1] * acomplement)) >> 8);
                  pdst2[2] = clip_byte(((psrc2[2] * bA) + (pdst2[2] * acomplement)) >> 8);
                  pdst2[3] = clip_byte(((psrc2[3] * bA) + (pdst2[3] * acomplement)) >> 8);



                  pdst2 += 4;

                  psrc2 += 4;

               }
               //pdst2 += xEnd;
               //psrc2 += xEnd;

            }

         }

         // bFontListData

      }
      else
      {

         // !bFontListData
         // bBouncingBall...

         if (bA == 0)
         {

         }
         else if (bA == 255)
         {

            for (int y = 0; y < yEnd; y++)
            {

               pdst2 = &pdst[scanDst * y];

               psrc2 = &psrc[scanSrc * y];

               //memcpy(pdst2, psrc2, xEnd * 4);
               for (int x = 0; x < xEnd; x++)
               {

                  //*pdst2 = *psrc2;

                  //pdst2[0] = (psrc2[0] + (pdst2[0] * (255 - psrc2[3])) / 255);
                  //pdst2[1] = (psrc2[1] + (pdst2[1] * (255 - psrc2[3])) / 255);
                  //pdst2[2] = (psrc2[2] + (pdst2[2] * (255 - psrc2[3])) / 255);
                  //pdst2[3] = (psrc2[3] + (pdst2[3] * (255 - psrc2[3])) / 255);
                  byte a = pdst2[3];
                  byte alpha = psrc2[3];
                  if (a == 0)
                  {

                  }
                  else if(alpha == 0)
                  {

                     *((COLORREF *)pdst2) = 0;

                  }
                  else
                  {

                     //int d0 = pdst2[0] * 255 / a;
                     //int d1 = pdst2[1] * 255 / a;
                     //int d2 = pdst2[2] * 255 / a;

                     //int s0 = psrc2[0] * 255 / alpha;
                     //int s1 = psrc2[1] * 255 / alpha;
                     //int s2 = psrc2[2] * 255 / alpha;

                     //d0 = ((s0 * a) + (d0 * alpha)) >> 8;
                     //d1 = ((s1 * a) + (d1 * alpha)) >> 8;
                     //d2 = ((s2 * a) + (d2 * alpha)) >> 8;
                     //pdst2[3] = ((psrc2[3] * a) + (pdst2[3] * alpha)) >> 8;

                     //pdst[0] = (d0 * pdst2[3]) >> 8;
                     //pdst[1] = (d1 * pdst2[3]) >> 8;
                     //pdst[2] = (d2 * pdst2[3]) >> 8;

                     //pdst2[0] = psrc2[0] + ((pdst2[0] * (acomplement)) >> 8);
                     //pdst2[1] = psrc2[1] + ((pdst2[1] * (acomplement)) >> 8);
                     //pdst2[2] = psrc2[2] + ((pdst2[2] * (acomplement)) >> 8);
                     //pdst2[3] = psrc2[3] + ((pdst2[3] * (acomplement)) >> 8);

                     pdst2[0] = (pdst2[0] * alpha) >> 8;
                     pdst2[1] = (pdst2[1] * alpha) >> 8;
                     pdst2[2] = (pdst2[2] * alpha) >> 8;
                     pdst2[3] = (pdst2[3] * alpha) >> 8;
                  }



                  pdst2 += 4;

                  psrc2 += 4;

               }
               //pdst2 += xEnd;
               //psrc2 += xEnd;

            }
         }
         else
         {
            for (int y = 0; y < yEnd; y++)
            {

               pdst2 = &pdst[scanDst * y];

               psrc2 = &psrc[scanSrc * y];

               //memcpy(pdst2, psrc2, xEnd * 4);
               for (int x = 0; x < xEnd; x++)
               {

                  //*pdst2 = *psrc2;

                  //pdst2[0] = (psrc2[0] + (pdst2[0] * (255 - psrc2[3])) / 255);
                  //pdst2[1] = (psrc2[1] + (pdst2[1] * (255 - psrc2[3])) / 255);
                  //pdst2[2] = (psrc2[2] + (pdst2[2] * (255 - psrc2[3])) / 255);
                  //pdst2[3] = (psrc2[3] + (pdst2[3] * (255 - psrc2[3])) / 255);
                  //byte acomplement = (~psrc2[3] * bA) >> 8;
                  //pdst2[0] = psrc2[0] + ((pdst2[0] * (acomplement)) >> 8);
                  //pdst2[1] = psrc2[1] + ((pdst2[1] * (acomplement)) >> 8);
                  //pdst2[2] = psrc2[2] + ((pdst2[2] * (acomplement)) >> 8);
                  //pdst2[3] = psrc2[3] + ((pdst2[3] * (acomplement)) >> 8);
                  byte acomplement = (~psrc2[3] * bA) >> 8;
                  pdst2[0] = clip_byte(((psrc2[0] * bA) + (pdst2[0] * acomplement)) >> 8);
                  pdst2[1] = clip_byte(((psrc2[1] * bA) + (pdst2[1] * acomplement)) >> 8);
                  pdst2[2] = clip_byte(((psrc2[2] * bA) + (pdst2[2] * acomplement)) >> 8);
                  pdst2[3] = clip_byte(((psrc2[3] * bA) + (pdst2[3] * acomplement)) >> 8);



                  pdst2 += 4;

                  psrc2 += 4;

               }
               //pdst2 += xEnd;
               //psrc2 += xEnd;

            }

         }

      }

      return true;

   }


   bool dib::precision_blend(point ptDst, ::draw2d::dib * pdibSrc, point ptSrc, class size size)
   {

      return precision_blend(ptDst, pdibSrc, ptSrc, size, 255);

   }


   bool dib::precision_blend(point ptDst, ::draw2d::dib * pdibSrc, point ptSrc, class size size, byte bA)
   {

      dib * pdibDst = this;


      pdibDst->map();

      pdibSrc->map();

      ptDst += m_pt;

      if (ptSrc.x < 0)
      {
         ptDst.x -= ptSrc.x;
         ptSrc.x = 0;
      }

      if (ptSrc.y < 0)
      {
         ptDst.y -= ptSrc.y;
         ptSrc.y = 0;
      }

      if (ptDst.x < 0)
      {
         size.cx += ptDst.x;
         ptDst.x = 0;
      }

      if (size.cx < 0)
         return true;

      if (ptDst.y < 0)
      {
         size.cy += ptDst.y;
         ptDst.y = 0;
      }

      if (size.cy < 0)
         return true;

      int xEnd = MIN(size.cx, MIN(pdibSrc->m_size.cx - ptSrc.x, pdibDst->m_size.cx - ptDst.x));

      int yEnd = MIN(size.cy, MIN(pdibSrc->m_size.cy - ptSrc.y, pdibDst->m_size.cy - ptDst.y));

      if (xEnd < 0)
         return false;

      if (yEnd < 0)
         return false;

      i32 scanDst = pdibDst->m_iScan;

      i32 scanSrc = pdibSrc->m_iScan;

      byte * pdst = &((byte *)pdibDst->m_pcolorref)[scanDst * ptDst.y + ptDst.x * sizeof(COLORREF)];

      byte * psrc = &((byte *)pdibSrc->m_pcolorref)[scanSrc * ptSrc.y + ptSrc.x * sizeof(COLORREF)];

      byte * pdst2;

      byte * psrc2;

      if (bA == 0)
      {

      }
      else if (bA == 255)
      {

         for (int y = 0; y < yEnd; y++)
         {

            pdst2 = &pdst[scanDst * y];

            psrc2 = &psrc[scanSrc * y];

            //memcpy(pdst2, psrc2, xEnd * 4);
            for (int x = 0; x < xEnd; x++)
            {

               //*pdst2 = *psrc2;

               //pdst2[0] = (psrc2[0] + (pdst2[0] * (255 - psrc2[3])) / 255);
               //pdst2[1] = (psrc2[1] + (pdst2[1] * (255 - psrc2[3])) / 255);
               //pdst2[2] = (psrc2[2] + (pdst2[2] * (255 - psrc2[3])) / 255);
               //pdst2[3] = (psrc2[3] + (pdst2[3] * (255 - psrc2[3])) / 255);
               byte acomplement = ~psrc2[3];
               pdst2[0] = psrc2[0] + ((pdst2[0] * (acomplement)) / 255);
               pdst2[1] = psrc2[1] + ((pdst2[1] * (acomplement)) / 255);
               pdst2[2] = psrc2[2] + ((pdst2[2] * (acomplement)) / 255);
               pdst2[3] = psrc2[3] + ((pdst2[3] * (acomplement)) / 255);



               pdst2 += 4;

               psrc2 += 4;

            }
            //pdst2 += xEnd;
            //psrc2 += xEnd;

         }
      }
      else
      {
         for (int y = 0; y < yEnd; y++)
         {

            pdst2 = &pdst[scanDst * y];

            psrc2 = &psrc[scanSrc * y];

            //memcpy(pdst2, psrc2, xEnd * 4);
            for (int x = 0; x < xEnd; x++)
            {

               //*pdst2 = *psrc2;

               //pdst2[0] = (psrc2[0] + (pdst2[0] * (255 - psrc2[3])) / 255);
               //pdst2[1] = (psrc2[1] + (pdst2[1] * (255 - psrc2[3])) / 255);
               //pdst2[2] = (psrc2[2] + (pdst2[2] * (255 - psrc2[3])) / 255);
               //pdst2[3] = (psrc2[3] + (pdst2[3] * (255 - psrc2[3])) / 255);
               //byte acomplement = (~psrc2[3] * bA) >> 8;
               //pdst2[0] = psrc2[0] + ((pdst2[0] * (acomplement)) >> 8);
               //pdst2[1] = psrc2[1] + ((pdst2[1] * (acomplement)) >> 8);
               //pdst2[2] = psrc2[2] + ((pdst2[2] * (acomplement)) >> 8);
               //pdst2[3] = psrc2[3] + ((pdst2[3] * (acomplement)) >> 8);
               byte acomplement = (~psrc2[3] * bA) / 255;
               pdst2[0] = clip_byte(((psrc2[0] * bA) + (pdst2[0] * acomplement)) / 255);
               pdst2[1] = clip_byte(((psrc2[1] * bA) + (pdst2[1] * acomplement)) / 255);
               pdst2[2] = clip_byte(((psrc2[2] * bA) + (pdst2[2] * acomplement)) / 255);
               pdst2[3] = clip_byte(((psrc2[3] * bA) + (pdst2[3] * acomplement)) / 255);



               pdst2 += 4;

               psrc2 += 4;

            }
            //pdst2 += xEnd;
            //psrc2 += xEnd;

         }

      }

      return true;

   }




   void thread_tool::run()
   {

      if (m_eop == op_blend)
      {

         if (m_bA == 0)
         {
         }
         else if (m_bA == 255)
         {
            int y = m_y;
            int yEnd = m_yEnd;
            int x = m_x;
            int xEnd = m_xEnd;
            int xEnd1 = m_xEnd - 7;
            int ySkip = m_ySkip;

            byte * pdst = m_pdst2;
            byte * psrc = m_psrc2;
            byte * pdst2;
            byte * psrc2;
            byte * pdst3;
            byte * psrc3;
            byte * src_opacity; // xmetrix, xmxstudio contribution
            byte * src_transparency; // unicorn, zjrosen contribution
            int w = m_w;
            byte * psrcOpacity = m_psrcOpacity; // Currently living in Milky Way, but minding of a place I don't remember
            byte * psrcTransparency = m_psrcTransparency; // Stacie, Dylan, Tectuma (Kevin) and Matt contribution
#define DIB_BLEND_ZERO_BLOCK_SIZE_EIGHTH 64
#define DIB_BLEND_ZERO_BLOCK_SIZE 256
            COLORREF craZero[DIB_BLEND_ZERO_BLOCK_SIZE];

            ZERO(craZero);

            int scanDst = m_scanDst;
            int scanSrc = m_scanSrc;

            if (psrcOpacity != NULL && psrcTransparency != NULL)
            {

               for (; y < yEnd; y += ySkip)
               {

                  pdst2 = &pdst[scanDst * y];

                  psrc2 = &psrc[scanSrc * y];

                  src_opacity = &psrcOpacity[w * y];

                  src_transparency = &psrcTransparency[w * y];

                  pdst3 = pdst2;

                  psrc3 = psrc2;
                  //int x2;
                  int x = 0;
                  int x1 = -1;
                  for (; x < xEnd; x++)
                  {

                     if (src_transparency[x])
                     {
                        if (x1 >= 0)
                        {
                           memcpy(&((COLORREF *)pdst3)[x1], &((COLORREF *)psrc3)[x1], (x - x1) * sizeof(COLORREF));
                           x1 = -1;
                        }

                        x += src_transparency[x]-1;
                        pdst2 = &pdst3[x << 2];
                        psrc2 = &psrc3[x << 2];

                     }
                     else if (src_opacity[x])
                     {

                        if (x1 < 0)
                        {
                           x1 = x;
                        }
                        x += src_opacity[x]-1;
                        pdst2 = &pdst3[x << 2];
                        psrc2 = &psrc3[x << 2];
                        // dst <= src
                     }
                     else
                     {
                        if (pdst2[3] == 0)
                        {
                           if (x1 < 0)
                           {
                              x1 = x;
                           }
                           // dst <= src
                        }
                        else
                        {
                           if (x1 >= 0)
                           {
                              memcpy(&((COLORREF *)pdst3)[x1], &((COLORREF *)psrc3)[x1], (x - x1) * sizeof(COLORREF));
                              x1 = -1;
                           }
                           byte bA2 = (byte)~(byte)psrc2[3];
                           pdst2[0] = psrc2[0] + ((pdst2[0] * bA2) >> 8);
                           pdst2[1] = psrc2[1] + ((pdst2[1] * bA2) >> 8);
                           pdst2[2] = psrc2[2] + ((pdst2[2] * bA2) >> 8);
                           pdst2[3] = psrc2[3] + ((pdst2[3] * bA2) >> 8);

                        }

                     }

                     pdst2 += 4;

                     psrc2 += 4;

                  }
                  if (x1 >= 0)
                  {
                     memcpy(&((COLORREF *)pdst3)[x1], &((COLORREF *)psrc3)[x1], (x - x1) * sizeof(COLORREF));
                     x1 = -1;
                  }
                  //pdst2 += xEnd;
                  //psrc2 += xEnd;

               }
            }
            else
            {

               //byte * pBound1;
               //byte * pBound8;
               //byte * pBound;
               //byte * pEnd8;
               for (; y < yEnd; y += ySkip)
               {

                  pdst2 = &pdst[scanDst * y];

                  psrc2 = &psrc[scanSrc * y];

                  pdst3 = pdst2;

                  psrc3 = psrc2;
                  //int x2;
                  int x = 0;
                  int x1 = -1;
                  //int xDistanceToBoundary1;
                  //int xDistanceToBoundary8;
                  int xEnd8;
                  for (; x < xEnd; x++)
                  {

restart:
                     ;

                     byte bA2 = psrc2[3];
                     if (bA2 == 0)
                     {
                        if (x1 >= 0)
                        {
                           memcpy(&((COLORREF *)pdst3)[x1], &((COLORREF *)psrc3)[x1], (x - x1) * sizeof(COLORREF));
                           x1 = -1;
                        }

#if 0
                        //if (0)
                        {

                           pBound = psrc3 + (xEnd << 2);
                           xDistanceToBoundary8 = (((int_ptr)psrc2) % (DIB_BLEND_ZERO_BLOCK_SIZE_EIGHTH * 4));
                           xDistanceToBoundary1 = (((int_ptr)psrc2) % (DIB_BLEND_ZERO_BLOCK_SIZE * 4));
                           pBound8 = MIN(pBound, psrc2 + DIB_BLEND_ZERO_BLOCK_SIZE_EIGHTH * 4 - xDistanceToBoundary8);
                           pBound1 = MIN(pBound, psrc2 + DIB_BLEND_ZERO_BLOCK_SIZE * 4 - xDistanceToBoundary1);

                           if (xDistanceToBoundary8 > 0)
                           {

                              while (psrc2 < pBound && psrc2[3] == 0)
                              {

                                 psrc2+=4;

                              }

                              if (psrc2 >= pBound)
                              {
                                 break;
                              }

                              if (psrc2[3] != 0)
                              {

                                 x = (psrc2 - psrc3) >> 2;

                                 pdst2 = &pdst3[x << 2];

                                 goto restart;

                              }

                              // boundary is zero

                           }
                           else
                           {

                              pBound8 = psrc2;

                              // boundary is zero

                           }


                           if (psrc2 == pBound8 && psrc2 != pBound1)
                           {

                              pEnd8 = MIN(pBound, pBound1);
                              while (psrc2 + DIB_BLEND_ZERO_BLOCK_SIZE_EIGHTH * 4 <= pEnd8
                                     && memcmp(psrc2, craZero, DIB_BLEND_ZERO_BLOCK_SIZE_EIGHTH * 4) == 0)
                              {

                                 psrc2 += DIB_BLEND_ZERO_BLOCK_SIZE_EIGHTH * 4;

                              }

                              if (psrc2 >= pBound)
                              {

                                 break;

                              }

                              if (psrc2[3] != 0)
                              {

                                 x = (psrc2 - psrc3) >> 2;

                                 pdst2 = &pdst3[x << 2];

                                 goto restart;

                              }

                              // boundary is zero

                           }
                           else
                           {

                              pBound1 = psrc2;

                           }

                           if (psrc2 == pBound1)
                           {

                              while (psrc2 + DIB_BLEND_ZERO_BLOCK_SIZE * 4 <= pBound
                                     && memcmp(psrc2, craZero, DIB_BLEND_ZERO_BLOCK_SIZE *4) == 0)
                              {

                                 psrc2 += DIB_BLEND_ZERO_BLOCK_SIZE * 4;

                              }

                              if (psrc2 >= pBound)
                              {
                                 break;
                              }

                              if (psrc2[3] != 0)
                              {

                                 x = (psrc2 - psrc3) >> 2;

                                 pdst2 = &pdst3[x << 2];

                                 goto restart;

                              }

                              // boundary is zero

                           }

                           while (psrc2 < pBound && psrc2[3] == 0)
                           {

                              psrc2+=4;

                           }


                           if (psrc2 >= pBound)
                           {
                              break;
                           }

                           x = (psrc2 - psrc3) >> 2;

                           pdst2 = &pdst3[x << 2];

                           if (psrc2[3] != 0)
                           {

                              goto restart;

                           }

                        }
#else

//if (0)
                        {

                           int xDistanceToBoundary8 = (((int_ptr)psrc2) % (DIB_BLEND_ZERO_BLOCK_SIZE_EIGHTH * 4)) / 4;
                           int xDistanceToBoundary1 = (((int_ptr)psrc2) % (DIB_BLEND_ZERO_BLOCK_SIZE * 4)) / 4;
                           int xBoundary8 = MIN(xEnd, x + DIB_BLEND_ZERO_BLOCK_SIZE_EIGHTH - xDistanceToBoundary8);
                           int xBoundary1 = MIN(xEnd, x + DIB_BLEND_ZERO_BLOCK_SIZE - xDistanceToBoundary1);

                           if (xDistanceToBoundary8 > 0)
                           {

                              while (x < xBoundary8 && !(((COLORREF *)psrc3)[x] & 0xff000000))
                              {

                                 x++;

                              }

                              if (x >= xEnd)
                              {
                                 break;
                              }

                              if (((COLORREF *)psrc3)[x] & 0xff000000)
                              {

                                 pdst2 = &pdst3[x << 2];

                                 psrc2 = &psrc3[x << 2];

                                 goto restart;

                              }

                              // boundary is zero

                           }
                           else
                           {

                              xBoundary8 = x;

                              // boundary is zero

                           }


                           if (x == xBoundary8 && x != xBoundary1)
                           {

                              xEnd8 = MIN(xEnd, xBoundary1);
                              while (x + DIB_BLEND_ZERO_BLOCK_SIZE_EIGHTH <= xEnd8
                                     && memcmp(&(((COLORREF *)psrc3)[x]), craZero, DIB_BLEND_ZERO_BLOCK_SIZE_EIGHTH * 4) == 0)
                              {

                                 x += DIB_BLEND_ZERO_BLOCK_SIZE_EIGHTH;

                              }

                              if (x >= xEnd)
                              {

                                 break;

                              }

                              if (((COLORREF *)psrc3)[x] & 0xff000000)
                              {

                                 pdst2 = &pdst3[x << 2];

                                 psrc2 = &psrc3[x << 2];

                                 goto restart;

                              }

                              // boundary is zero

                           }
                           else
                           {

                              xBoundary1 = x;

                           }

                           if (x == xBoundary1)
                           {

                              while (x + DIB_BLEND_ZERO_BLOCK_SIZE <= xEnd
                                     && memcmp(&(((COLORREF *)psrc3)[x]), craZero, sizeof(craZero)) == 0)
                              {

                                 x += DIB_BLEND_ZERO_BLOCK_SIZE;

                              }

                              if (x >= xEnd)
                              {

                                 break;

                              }

                              if (((COLORREF *)psrc3)[x] & 0xff000000)
                              {

                                 pdst2 = &pdst3[x << 2];

                                 psrc2 = &psrc3[x << 2];

                                 goto restart;

                              }

                              // boundary is zero

                           }

                           while (x < xEnd && !(((COLORREF *)psrc3)[x] & 0xff000000))
                           {

                              x++;

                           }

                           if (x >= xEnd)
                           {
                              break;
                           }

                           pdst2 = &pdst3[x << 2];

                           psrc2 = &psrc3[x << 2];

                           if (((COLORREF *)psrc3)[x] & 0xff000000)
                           {

                              goto restart;

                           }

                        }

#endif

                     }
                     else if (bA2 == 255)
                     {

                        if (x1 < 0)
                        {
                           x1 = x;
                        }
                        // dst <= src
                     }
                     else
                     {
                        if (pdst2[3] == 0)
                        {
                           if (x1 < 0)
                           {
                              x1 = x;
                           }
                           // dst <= src
                        }
                        else
                        {
                           if (x1 >= 0)
                           {
                              memcpy(&((COLORREF *)pdst3)[x1], &((COLORREF *)psrc3)[x1], (x - x1) * sizeof(COLORREF));
                              x1 = -1;
                           }
                           bA2 = (byte)~bA2;
                           pdst2[0] = psrc2[0] + ((pdst2[0] * bA2) >> 8);
                           pdst2[1] = psrc2[1] + ((pdst2[1] * bA2) >> 8);
                           pdst2[2] = psrc2[2] + ((pdst2[2] * bA2) >> 8);
                           pdst2[3] = psrc2[3] + ((pdst2[3] * bA2) >> 8);

                        }

                     }

                     pdst2 += 4;

                     psrc2 += 4;

                  }
                  if (x1 >= 0)
                  {
                     memcpy(&((COLORREF *)pdst3)[x1], &((COLORREF *)psrc3)[x1], (x - x1) * sizeof(COLORREF));
                     x1 = -1;
                  }
                  //pdst2 += xEnd;
                  //psrc2 += xEnd;

               }

            }
         }

         else
         {
            //return;
            byte bA = m_bA;
            int y = m_y;
            int yEnd = m_yEnd;
            int x = m_x;
            int xEnd = m_xEnd;
            int xEnd1 = m_xEnd - 7;
            int ySkip = m_ySkip;
            //byte * src_opacity; // xmetrix, xmxstudio contribution
            byte * src_transparency; // unicorn, zjrosen contribution
            int w = m_w;
            byte * psrcOpacity = m_psrcOpacity; // Currently living in Milky Way, but minding of a place I don't remember
            byte * psrcTransparency = m_psrcTransparency; // Stacie, Dylan, Tectuma (Kevin) and Matt contribution

            byte * pdst = m_pdst2;
            byte * psrc = m_psrc2;
            byte * pdst2;
            byte * psrc2;
            byte * pdst3;
            byte * psrc3;

            int scanDst = m_scanDst;
            int scanSrc = m_scanSrc;

            if (psrcTransparency != NULL)
            {

               for (; y < yEnd; y += ySkip)
               {

                  pdst2 = &pdst[scanDst * y];

                  psrc2 = &psrc[scanSrc * y];
//                  src_opacity = &psrcOpacity[w * y];

                  src_transparency = &psrcTransparency[w * y];

                  pdst3 = pdst2;

                  psrc3 = psrc2;

                  int x = 0;
                  for (; x < xEnd; x++)
                  {

                     byte bA2 = psrc2[3];
                     if (src_transparency[x])
                     {
                        x += src_transparency[x] - 1;
                        pdst2 = &pdst3[x << 2];
                        psrc2 = &psrc3[x << 2];
                     }
                     else if (pdst2[3] == 0)
                     {
                        pdst2[0] = (psrc2[0] * bA) >> 8;
                        pdst2[1] = (psrc2[1] * bA) >> 8;
                        pdst2[2] = (psrc2[2] * bA) >> 8;
                        pdst2[3] = (psrc2[3] * bA) >> 8;
                     }
                     else
                     {

                        byte bA3 = ((uint16_t)~((uint16_t)bA2 * (uint16_t)bA)) >> 8;
                        pdst2[0] = (psrc2[0] * bA + pdst2[0] * bA3) >> 8;
                        pdst2[1] = (psrc2[1] * bA + pdst2[1] * bA3) >> 8;
                        pdst2[2] = (psrc2[2] * bA + pdst2[2] * bA3) >> 8;
                        pdst2[3] = (psrc2[3] * bA + pdst2[3] * bA3) >> 8;

                     }

                     pdst2 += 4;

                     psrc2 += 4;

                  }

               }

            }
            else
            {

               for (; y < yEnd; y += ySkip)
               {

                  pdst2 = &pdst[scanDst * y];

                  psrc2 = &psrc[scanSrc * y];

                  pdst3 = pdst2;

                  psrc3 = psrc2;

                  int x = 0;
                  for (; x < xEnd; x++)
                  {

                     byte bA2 = psrc2[3];
                     if (bA2 == 0)
                     {
                     }
                     else if (pdst2[3] == 0)
                     {
                        pdst2[0] = (psrc2[0] * bA) >> 8;
                        pdst2[1] = (psrc2[1] * bA) >> 8;
                        pdst2[2] = (psrc2[2] * bA) >> 8;
                        pdst2[3] = (psrc2[3] * bA) >> 8;
                     }
                     else
                     {

                        byte bA3 = ((uint16_t)~((uint16_t)bA2 * (uint16_t)bA)) >> 8;
                        pdst2[0] = (psrc2[0] * bA + pdst2[0] * bA3) >> 8;
                        pdst2[1] = (psrc2[1] * bA + pdst2[1] * bA3) >> 8;
                        pdst2[2] = (psrc2[2] * bA + pdst2[2] * bA3) >> 8;
                        pdst2[3] = (psrc2[3] * bA + pdst2[3] * bA3) >> 8;

                     }

                     pdst2 += 4;

                     psrc2 += 4;

                  }

               }


            }
         }


      }

   }


   bool dib::fork_blend(point ptDst, ::draw2d::dib * pdibSrc, point ptSrc, class size size)
   {

      return fork_blend(ptDst, pdibSrc, ptSrc, size, 255);

   }


   bool dib::fork_blend(point ptDst, ::draw2d::dib * pdibSrc, point ptSrc, class size size, byte bA)
   {

      if (bA == 0)
      {


         return true;

      }

      dib * pdibDst = this;


      pdibDst->map();

      pdibSrc->map();

      ptDst += m_pt;

      if (ptSrc.x < 0)
      {
         ptDst.x -= ptSrc.x;
         ptSrc.x = 0;
      }

      if (ptSrc.y < 0)
      {
         ptDst.y -= ptSrc.y;
         ptSrc.y = 0;
      }

      if (ptDst.x < 0)
      {
         size.cx += ptDst.x;
         ptSrc.x -= ptDst.x;
         ptDst.x = 0;
      }

      if (size.cx < 0)
         return true;

      if (ptDst.y < 0)
      {
         size.cy += ptDst.y;
         ptSrc.y -= ptDst.y;
         ptDst.y = 0;
      }

      if (size.cy < 0)
         return true;

      int xEnd = MIN(size.cx, MIN(pdibSrc->m_size.cx - ptSrc.x, pdibDst->m_size.cx - ptDst.x));

      int yEnd = MIN(size.cy, MIN(pdibSrc->m_size.cy - ptSrc.y, pdibDst->m_size.cy - ptDst.y));

      if (xEnd <= 0)
         return false;

      if (yEnd <= 0)
         return false;

      i32 scanDst = pdibDst->m_iScan;

      i32 scanSrc = pdibSrc->m_iScan;

      byte * pdst = &((byte *)pdibDst->m_pcolorref)[scanDst * ptDst.y + ptDst.x * sizeof(COLORREF)];

      byte * psrc = &((byte *)pdibSrc->m_pcolorref)[scanSrc * ptSrc.y + ptSrc.x * sizeof(COLORREF)];

      //byte * pdst5; // dst opacity map if available // opacity map does not make sense for dibs that change

      byte * psrcOpacity; // src opacity map if available

      byte * psrcTransparency; // src transparency map if available

      //if (pdibDst->m_memoryOpacity.size() == pdibDst->area())
      //{

      //   pdst5 = pdibDst->m_memoryOpacity.get_data();

      //}
      //else
      //{

      //   pdst5 = NULL;

      //}

      if (pdibSrc->m_memoryMap.size() == pdibSrc->area() * 2)
      {

         psrcOpacity = &pdibSrc->m_memoryMap.get_data()[pdibSrc->m_size.cx * ptSrc.y + ptSrc.x];

      }
      else
      {

         psrcOpacity = NULL;

      }

      if (pdibSrc->m_memoryMap.size() == pdibSrc->area() * 2)
      {

         psrcTransparency = &pdibSrc->m_memoryMap.get_data()[pdibSrc->area() + pdibSrc->m_size.cx * ptSrc.y + ptSrc.x];

      }
      else
      {

         psrcTransparency = NULL;

      }

      //byte * pdst2;

      //byte * psrc2;

      auto  pset = ::get_thread_toolset(::thread::tool_draw2d);

      if (pset->nok())
      {

         return blend(ptDst, pdibSrc, ptSrc, size, bA);

      }

      int y = 0;

      pset->prepare(yEnd);

      for(sp(::draw2d::thread_tool) ptool : *pset)
      {

         ptool->m_eop = thread_tool::op_blend;

         ptool->m_w = pdibSrc->m_size.cx;

         ptool->m_h = pdibSrc->m_size.cy;

         ptool->m_ySkip = (int) (pset->get_count());

         ptool->m_y = y;

         ptool->m_yEnd = yEnd;

         ptool->m_bA = bA;

         ptool->m_x = 0;

         ptool->m_xEnd = xEnd;

         ptool->m_pdst2 = pdst;

         ptool->m_psrc2 = psrc;

         ptool->m_psrcOpacity = psrcOpacity;

         ptool->m_psrcTransparency = psrcTransparency;

         ptool->m_scanSrc = scanSrc;

         ptool->m_scanDst = scanDst;

         y++;

      }

      (*pset)();

      return true;

   }

   bool dib::from_ignore_alpha(point ptDst, ::draw2d::dib * pdib, point ptSrc, class size size)
   {

      if (ptDst.x < 0)
      {
         size.cx += ptDst.x;
         ptDst.x = 0;
      }

      if (size.cx < 0)
         return true;

      if (ptDst.y < 0)
      {
         size.cy += ptDst.y;
         ptDst.y = 0;
      }

      if (size.cy < 0)
         return true;

      int xEnd = MIN(size.cx, MIN(pdib->m_size.cx - ptSrc.x, m_size.cx - ptDst.x));

      int yEnd = MIN(size.cy, MIN(pdib->m_size.cy - ptSrc.y, m_size.cy - ptDst.y));

      if (xEnd < 0)
         return false;

      if (yEnd < 0)
         return false;

      i32 s1 = m_iScan / sizeof(COLORREF);

      i32 s2 = pdib->m_iScan / sizeof(COLORREF);

      COLORREF * pdst = &m_pcolorref[s1 * ptDst.y] + ptDst.x;

      COLORREF * psrc = &pdib->m_pcolorref[s2 * ptSrc.y] + ptSrc.x;

      COLORREF * pdst2;

      COLORREF * psrc2;

      int i = 0;

      for (int y = 0; y < yEnd; y++)
      {

         pdst2 = &pdst[s1 * y];

         psrc2 = &psrc[s2 * y];

         for (int x = 0; x < xEnd; x++)
         {

            if (argb_get_a_value(*psrc2) == 0)
            {
               i++;
            }
            else
            {
               *pdst2 = *psrc2;
            }

            pdst2++;

            psrc2++;

         }

      }

      return true;

   }


   bool dib::blend(point ptDst, ::draw2d::dib * pdibSrc, point ptSrc, ::draw2d::dib * pdibAlf, point ptDstAlf, class size size)
   {

      dib * pdibDst = this;

      pdibDst->map();
      pdibSrc->map();
      pdibAlf->map();

      if (ptSrc.x < 0)
      {
         ptDst.x -= ptSrc.x;
         ptDstAlf.x -= ptSrc.x;
         ptSrc.x = 0;
      }

      if (ptSrc.y < 0)
      {
         ptDst.y -= ptSrc.y;
         ptDstAlf.y -= ptSrc.y;
         ptSrc.y = 0;
      }

      if (ptDst.x < 0)
      {
         size.cx += ptDst.x;
         ptDst.x = 0;
      }

      if (size.cx < 0)
         return true;

      if (ptDst.y < 0)
      {
         size.cy += ptDst.y;
         ptDst.y = 0;
      }

      if (size.cy < 0)
         return true;

      int xEnd = MIN(size.cx, MIN(pdibSrc->m_size.cx - ptSrc.x, pdibDst->m_size.cx - ptDst.x));

      int yEnd = MIN(size.cy, MIN(pdibSrc->m_size.cy - ptSrc.y, pdibDst->m_size.cy - ptDst.y));

      if (xEnd < 0)
         return false;

      if (yEnd < 0)
         return false;


      if (ptDstAlf.x < 0)
      {
      }

      i32 scanDst = pdibDst->m_iScan;

      i32 scanSrc = pdibSrc->m_iScan;

      i32 scanAlf = pdibAlf->m_iScan;

      byte * pdst = &((byte *)pdibDst->m_pcolorref)[scanDst * ptDst.y + ptDst.x * sizeof(COLORREF)];

      byte * psrc = &((byte *)pdibSrc->m_pcolorref)[scanSrc * ptSrc.y + ptSrc.x * sizeof(COLORREF)];

      byte * palf = &((byte *)pdibAlf->m_pcolorref)[-scanAlf * ptDstAlf.y - ptDstAlf.x * sizeof(COLORREF)] + 3;

      byte * pdst2;

      byte * psrc2;

      byte * palf2;

      int x1;
      int x2;
      int y1;
      int y2;

      x1 = ptDstAlf.x;
      x2 = pdibAlf->m_size.cx + x1;
      y1 = ptDstAlf.y;
      y2 = pdibAlf->m_size.cy + y1;


      //int a;

      for (int y = 0; y < yEnd; y++)
      {

         pdst2 = (byte *)&pdst[scanDst * y];

         psrc2 = (byte *)&psrc[scanSrc * y];

         palf2 = (byte *)&palf[scanAlf * y];

         for (int x = 0; x < xEnd; x++)
         {

            if (psrc2[3] > 0)
            {
//               if (false && x >= x1 && x < x2 && y >= y1 && y < y2)
//               {
//
//                  a = (*palf2 * psrc2[3]) / 255;
//                  a = psrc2[3];
//                  //a = (int) (byte) sqrt((float) (*palf2 * psrc2[3]));
//                  pdst2[3] = (BYTE)MAX(a, pdst2[3]);
//                  //pdst2[3] = (BYTE)((((int)psrc2[3] - (int)pdst2[3]) * a + ((int)pdst2[3] * 255)) / 255);
//                  pdst2[3] = (BYTE)(MAX(psrc2[3], pdst2[3]));
//
//                  //                  if (a > 0)
//                  {
//
//                     pdst2[0] = (BYTE)((((int)psrc2[0] - (int)pdst2[0]) * a + ((int)pdst2[0] * 255)) / 255);
//                     pdst2[1] = (BYTE)((((int)psrc2[1] - (int)pdst2[1]) * a + ((int)pdst2[1] * 255)) / 255);
//                     pdst2[2] = (BYTE)((((int)psrc2[2] - (int)pdst2[2]) * a + ((int)pdst2[2] * 255)) / 255);
//
//                  }
//
//               }
//               else
               {

                  //pdst2[3] = (BYTE)(MAX(psrc2[3], pdst2[3]));
                  //pdst2[3] = (BYTE)((((int)psrc2[3] - (int)pdst2[3]) * (int)psrc2[3] + ((int)pdst2[3] * 255)) / 255);
                  //pdst2[0] = (BYTE)((((int)psrc2[0] - (int)pdst2[0]) * (int)psrc2[3] + ((int)pdst2[0] * 255)) / 255);
                  //pdst2[1] = (BYTE)((((int)psrc2[1] - (int)pdst2[1]) * (int)psrc2[3] + ((int)pdst2[1] * 255)) / 255);
                  //pdst2[2] = (BYTE)((((int)psrc2[2] - (int)pdst2[2]) * (int)psrc2[3] + ((int)pdst2[2] * 255)) / 255);
                  pdst2[3] = (BYTE)(MAX(((((int)psrc2[3] - (int)pdst2[3]) * (int)psrc2[3] + ((int)pdst2[3] * 255)) / 255), pdst2[3]));
                  pdst2[0] = (BYTE)((((int)psrc2[0] - (int)pdst2[0]) * (int)psrc2[3] + ((int)pdst2[0] * 255)) / 255);
                  pdst2[1] = (BYTE)((((int)psrc2[1] - (int)pdst2[1]) * (int)psrc2[3] + ((int)pdst2[1] * 255)) / 255);
                  pdst2[2] = (BYTE)((((int)psrc2[2] - (int)pdst2[2]) * (int)psrc2[3] + ((int)pdst2[2] * 255)) / 255);

               }
            }


            pdst2 += 4;

            psrc2 += 4;

            palf2 += 4;


         }

      }

      return true;

   }

   /*
   bool dib::blend(point ptDst,::draw2d::dib * pdibSrc, point ptSrc, class size size)
   {

      dib * pdibDst = this;

      pdibDst->map();
      pdibSrc->map();


      if (ptSrc.x < 0)
      {
         ptDst.x -= ptSrc.x;
         ptSrc.x = 0;
      }

      if (ptSrc.y < 0)
      {
         ptDst.y -= ptSrc.y;
         ptSrc.y = 0;
      }

      if (ptDst.x < 0)
      {
         size.cx += ptDst.x;
         ptDst.x = 0;
      }

      if (size.cx < 0)
         return true;

      if (ptDst.y < 0)
      {
         size.cy += ptDst.y;
         ptDst.y = 0;
      }

      if (size.cy < 0)
         return true;

      int xEnd = MIN(size.cx, MIN(pdibSrc->m_size.cx - ptSrc.x, pdibDst->m_size.cx - ptDst.x));

      int yEnd = MIN(size.cy, MIN(pdibSrc->m_size.cy - ptSrc.y, pdibDst->m_size.cy - ptDst.y));

      if (xEnd < 0)
         return false;

      if (yEnd < 0)
         return false;



      i32 scanDst = pdibDst->m_iScan;

      i32 scanSrc = pdibSrc->m_iScan;

   #ifdef APPLEOS

      byte * pdst = &((byte *)pdibDst->m_pcolorref)[scanDst * (pdibDst->m_size.cy - ptDst.y - 1) + ptDst.x * sizeof(COLORREF)] + 3;

      byte * psrc = &((byte *)pdibSrc->m_pcolorref)[scanSrc * (pdibSrc->m_size.cy - ptSrc.y - 1) + ptSrc.x * sizeof(COLORREF)] + 3;

   #else

      byte * pdst = &((byte *)pdibDst->m_pcolorref)[scanDst * ptDst.y + ptDst.x * sizeof(COLORREF)] + 3;

      byte * psrc = &((byte *)pdibSrc->m_pcolorref)[scanSrc * ptSrc.y + ptSrc.x * sizeof(COLORREF)] + 3;

   #endif

      byte * pdst2;

      byte * psrc2;

      pdibDst->div_alpha(ptDst, ::size(xEnd, yEnd));
      pdibSrc->div_alpha(ptSrc, ::size(xEnd, yEnd));


      for (int y = 0; y < yEnd; y++)
      {

   #ifdef APPLEOS

         pdst2 = (byte *) &pdst[scanDst * (-y)];

         psrc2 = (byte *) &psrc[scanSrc * (-y)];

   #else

         pdst2 = (byte *) &pdst[scanDst * y];

         psrc2 = (byte *) &psrc[scanSrc * y];

   #endif

         for (int x = 0; x < xEnd; x++)
         {

            *pdst2 = *psrc2 * *pdst2 / 255;

            pdst2+=4;

            psrc2+=4;

         }

      }
      pdibDst->mult_alpha(ptDst, ::size(xEnd, yEnd));
      pdibSrc->mult_alpha(ptSrc, ::size(xEnd, yEnd));

      return true;

   }
   */

   void dib::set(i32 R, i32 G, i32 B)
   {
      int64_t size = scan_area();

      COLORREF * pcr = get_data();

      if (pcr == NULL)
      {

         return;

      }

#ifdef WINDOWS
      ::sort::swap(&R, &B);
#endif

      for (i32 i = 0; i < size; i++)
      {
         ((byte *)pcr)[0] = R;
         ((byte *)pcr)[1] = G;
         ((byte *)pcr)[2] = B;
         pcr++;
      }

   }

   /*   void dib::Fill ( i32 R, i32 G, i32 B )
      {
         COLORREF color=RGB ( B, G, R );
         int64_t size = area();

         COLORREF * pcr;

         int64_t iSize32 = size / 32;
         i32 i;
         for (i=0; i < iSize32; i+=32 )
         {
            pcr = &get_data()[i];
            pcr[0] = color;
            pcr[1] = color;
            pcr[2] = color;
            pcr[3] = color;
            pcr[4] = color;
            pcr[5] = color;
            pcr[6] = color;
            pcr[7] = color;
            pcr[8] = color;
            pcr[9] = color;
            pcr[10] = color;
            pcr[11] = color;
            pcr[12] = color;
            pcr[13] = color;
            pcr[14] = color;
            pcr[15] = color;
            pcr[16] = color;
            pcr[17] = color;
            pcr[18] = color;
            pcr[19] = color;
            pcr[20] = color;
            pcr[21] = color;
            pcr[22] = color;
            pcr[23] = color;
            pcr[24] = color;
            pcr[25] = color;
            pcr[26] = color;
            pcr[27] = color;
            pcr[28] = color;
            pcr[29] = color;
            pcr[30] = color;
            pcr[31] = color;
         }

         for (i=0; i<size; i++ )
         {
            get_data()[i]=color;
         }
      }
      */


   bool dib::flip_vertical(::draw2d::dib * pdib)
   {

      if (!create(pdib->m_size))
      {

         return false;

      }

      int w = m_size.cx;

      int h = m_size.cy;

      int sw = w * 4;

      int dsw = m_iScan / 4;

      int ssw = pdib->m_iScan / 4;

      for (index y = 0; y < h; y++)
      {

         memcpy(&m_pcolorref[y * dsw], &pdib->m_pcolorref[(h - y - 1) * ssw], sw);

      }

      return true;

   }


   bool dib::flip_horizontal(::draw2d::dib * pdib)
   {

      if (!create(pdib->m_size))
      {

         return false;

      }

      int half = -1;

      int dsw = m_iScan / 4;

      int ssw = pdib->m_iScan / 4;

      int w = m_size.cx;

      for (index y = 0; y < pdib->m_size.cy; y++)
      {

         for (index x = 0; x < w; x++)
         {

            m_pcolorref[y * dsw + x] = pdib->m_pcolorref[y * ssw + w - x - 1];

         }

      }

      return true;

   }

   void dib::flipx(::draw2d::dib * pdib)
   {

      flip_horizontal(pdib);

   }

   void dib::flipy(::draw2d::dib * pdib)
   {

      flip_vertical(pdib);

   }

   dib & dib::flipx()
   {

      flipx(dynamic_cast < dib * > (clone()));

      return *this;

   }

   dib & dib::flipy()
   {

      flipy(dynamic_cast < dib * > (clone()));

      return *this;

   }

   void dib::ToAlpha(i32 i)
   {
      BYTE *dst = (BYTE*)get_data();
      int64_t size = scan_area();

      while (size--)
      {
         dst[3] = dst[i];
         dst += 4;
      }
   }


   void dib::from_alpha()
   {

      BYTE *dst = (BYTE*)get_data();

      int64_t size = scan_area();

      while (size--)
      {
         dst[0] = dst[3];
         dst[1] = dst[3];
         dst[2] = dst[3];
         dst += 4;
      }

   }


   void dib::mult_alpha(::draw2d::dib * pdib, bool bPreserveAlpha)
   {
      UNREFERENCED_PARAMETER(pdib);
      UNREFERENCED_PARAMETER(bPreserveAlpha);

      BYTE *dst = (BYTE*)get_data();
      int64_t size = scan_area();


      // >> 8 instead of / 255 subsequent alpha_blend operations say thanks on true_blend because (255) * (1/254) + (255) * (254/255) > 255


      while (size >= 8)
      {
         dst[0] = LOBYTE(((i32)dst[0] * (i32)dst[3]) >> 8);
         dst[1] = LOBYTE(((i32)dst[1] * (i32)dst[3]) >> 8);
         dst[2] = LOBYTE(((i32)dst[2] * (i32)dst[3]) >> 8);

         dst[4 + 0] = LOBYTE(((i32)dst[4 + 0] * (i32)dst[4 + 3]) >> 8);
         dst[4 + 1] = LOBYTE(((i32)dst[4 + 1] * (i32)dst[4 + 3]) >> 8);
         dst[4 + 2] = LOBYTE(((i32)dst[4 + 2] * (i32)dst[4 + 3]) >> 8);

         dst[8 + 0] = LOBYTE(((i32)dst[8 + 0] * (i32)dst[8 + 3]) >> 8);
         dst[8 + 1] = LOBYTE(((i32)dst[8 + 1] * (i32)dst[8 + 3]) >> 8);
         dst[8 + 2] = LOBYTE(((i32)dst[8 + 2] * (i32)dst[8 + 3]) >> 8);

         dst[12 + 0] = LOBYTE(((i32)dst[12 + 0] * (i32)dst[12 + 3]) >> 8);
         dst[12 + 1] = LOBYTE(((i32)dst[12 + 1] * (i32)dst[12 + 3]) >> 8);
         dst[12 + 2] = LOBYTE(((i32)dst[12 + 2] * (i32)dst[12 + 3]) >> 8);

         dst[16 + 0] = LOBYTE(((i32)dst[16 + 0] * (i32)dst[16 + 3]) >> 8);
         dst[16 + 1] = LOBYTE(((i32)dst[16 + 1] * (i32)dst[16 + 3]) >> 8);
         dst[16 + 2] = LOBYTE(((i32)dst[16 + 2] * (i32)dst[16 + 3]) >> 8);

         dst[20 + 0] = LOBYTE(((i32)dst[20 + 0] * (i32)dst[20 + 3]) >> 8);
         dst[20 + 1] = LOBYTE(((i32)dst[20 + 1] * (i32)dst[20 + 3]) >> 8);
         dst[20 + 2] = LOBYTE(((i32)dst[20 + 2] * (i32)dst[20 + 3]) >> 8);

         dst[24 + 0] = LOBYTE(((i32)dst[24 + 0] * (i32)dst[24 + 3]) >> 8);
         dst[24 + 1] = LOBYTE(((i32)dst[24 + 1] * (i32)dst[24 + 3]) >> 8);
         dst[24 + 2] = LOBYTE(((i32)dst[24 + 2] * (i32)dst[24 + 3]) >> 8);

         dst[28 + 0] = LOBYTE(((i32)dst[28 + 0] * (i32)dst[28 + 3]) >> 8);
         dst[28 + 1] = LOBYTE(((i32)dst[28 + 1] * (i32)dst[28 + 3]) >> 8);
         dst[28 + 2] = LOBYTE(((i32)dst[28 + 2] * (i32)dst[28 + 3]) >> 8);

         dst += 4 * 8;
         size -= 8;
      }
      while (size--)
      {
         dst[0] = LOBYTE(((i32)dst[0] * (i32)dst[3]) >> 8);
         dst[1] = LOBYTE(((i32)dst[1] * (i32)dst[3]) >> 8);
         dst[2] = LOBYTE(((i32)dst[2] * (i32)dst[3]) >> 8);
         dst += 4;
      }
   }


#define byte_clip2(i) (i)
   void dib::mult_alpha()
   {
      map();

      BYTE *dst = (BYTE*)get_data();
      int64_t size = scan_area();


      //  / 255 instead of / 255 subsequent alpha_blend operations say thanks on true_blend because (255) * (1/254) + (255) * (254/255) > 255


      while (size >= 8)
      {
         dst[0] = byte_clip2(((i32)dst[0] * (i32)dst[3]) / 255);
         dst[1] = byte_clip2(((i32)dst[1] * (i32)dst[3]) / 255);
         dst[2] = byte_clip2(((i32)dst[2] * (i32)dst[3]) / 255);

         dst[4 + 0] = byte_clip2(((i32)dst[4 + 0] * (i32)dst[4 + 3]) / 255);
         dst[4 + 1] = byte_clip2(((i32)dst[4 + 1] * (i32)dst[4 + 3]) / 255);
         dst[4 + 2] = byte_clip2(((i32)dst[4 + 2] * (i32)dst[4 + 3]) / 255);

         dst[8 + 0] = byte_clip2(((i32)dst[8 + 0] * (i32)dst[8 + 3]) / 255);
         dst[8 + 1] = byte_clip2(((i32)dst[8 + 1] * (i32)dst[8 + 3]) / 255);
         dst[8 + 2] = byte_clip2(((i32)dst[8 + 2] * (i32)dst[8 + 3]) / 255);

         dst[12 + 0] = byte_clip2(((i32)dst[12 + 0] * (i32)dst[12 + 3]) / 255);
         dst[12 + 1] = byte_clip2(((i32)dst[12 + 1] * (i32)dst[12 + 3]) / 255);
         dst[12 + 2] = byte_clip2(((i32)dst[12 + 2] * (i32)dst[12 + 3]) / 255);

         dst[16 + 0] = byte_clip2(((i32)dst[16 + 0] * (i32)dst[16 + 3]) / 255);
         dst[16 + 1] = byte_clip2(((i32)dst[16 + 1] * (i32)dst[16 + 3]) / 255);
         dst[16 + 2] = byte_clip2(((i32)dst[16 + 2] * (i32)dst[16 + 3]) / 255);

         dst[20 + 0] = byte_clip2(((i32)dst[20 + 0] * (i32)dst[20 + 3]) / 255);
         dst[20 + 1] = byte_clip2(((i32)dst[20 + 1] * (i32)dst[20 + 3]) / 255);
         dst[20 + 2] = byte_clip2(((i32)dst[20 + 2] * (i32)dst[20 + 3]) / 255);

         dst[24 + 0] = byte_clip2(((i32)dst[24 + 0] * (i32)dst[24 + 3]) / 255);
         dst[24 + 1] = byte_clip2(((i32)dst[24 + 1] * (i32)dst[24 + 3]) / 255);
         dst[24 + 2] = byte_clip2(((i32)dst[24 + 2] * (i32)dst[24 + 3]) / 255);

         dst[28 + 0] = byte_clip2(((i32)dst[28 + 0] * (i32)dst[28 + 3]) / 255);
         dst[28 + 1] = byte_clip2(((i32)dst[28 + 1] * (i32)dst[28 + 3]) / 255);
         dst[28 + 2] = byte_clip2(((i32)dst[28 + 2] * (i32)dst[28 + 3]) / 255);

         dst += 4 * 8;
         size -= 8;
      }
      while (size--)
      {
         dst[0] = byte_clip2(((i32)dst[0] * (i32)dst[3]) / 255);
         dst[1] = byte_clip2(((i32)dst[1] * (i32)dst[3]) / 255);
         dst[2] = byte_clip2(((i32)dst[2] * (i32)dst[3]) / 255);
         dst += 4;
      }
   }


   void dib::mult_alpha_fast()
   {
      map();

      BYTE *dst = (BYTE*)get_data();
      int64_t size = scan_area();


      //  >> 2 instead of >> 2 subsequent alpha_blend operations say thanks on true_blend because (255) * (1/254) + (255) * (254/255) > 255


      while (size--)
      {
         if (dst[3] == 0)
         {
            *((COLORREF*)dst) = 0;
         }
         else if (dst[3] != 255)
         {
            dst[0] = byte_clip2(((i32)dst[0] * (i32)dst[3]) >> 8);
            dst[1] = byte_clip2(((i32)dst[1] * (i32)dst[3]) >> 8);
            dst[2] = byte_clip2(((i32)dst[2] * (i32)dst[3]) >> 8);
         }
         dst += 4;
      }
   }


   void dib::mult_alpha(point ptDst, ::size size)
   {

      dib * pdibDst = this;

      pdibDst->map();

      if (ptDst.x < 0)
      {
         size.cx += ptDst.x;
         ptDst.x = 0;
      }

      if (size.cx < 0)
         return;

      if (ptDst.y < 0)
      {
         size.cy += ptDst.y;
         ptDst.y = 0;
      }

      if (size.cy < 0)
         return;

      int xEnd = MIN(size.cx, pdibDst->m_size.cx - ptDst.x);

      int yEnd = MIN(size.cy, pdibDst->m_size.cy - ptDst.y);

      if (xEnd < 0)
         return;

      if (yEnd < 0)
         return;

      i32 scanDst = pdibDst->m_iScan;

#ifdef APPLEOS

      byte * pdst = &((byte *)pdibDst->m_pcolorref)[scanDst * (m_size.cy - ptDst.y - 1) + ptDst.x * sizeof(COLORREF)];

#else

      byte * pdst = &((byte *)pdibDst->m_pcolorref)[scanDst * ptDst.y + ptDst.x * sizeof(COLORREF)];

#endif

      byte * pdst2;

      for (int y = 0; y < yEnd; y++)
      {

#ifdef APPLEOS

         pdst2 = (byte *)&pdst[scanDst * (-y)];

#else

         pdst2 = (byte *)&pdst[scanDst * y];

#endif

         for (int x = 0; x < xEnd; x++)
         {

            pdst2[0] = byte_clip(((i32)pdst2[0] * (i32)pdst2[3]) / 255);
            pdst2[1] = byte_clip(((i32)pdst2[1] * (i32)pdst2[3]) / 255);
            pdst2[2] = byte_clip(((i32)pdst2[2] * (i32)pdst2[3]) / 255);

            pdst2 += 4;

         }

      }

   }

   int64_t dib::scan_area()
   {

      return m_iScan * m_size.cy / sizeof(COLORREF);

   }

   bool dib::load_thumbnail(const char * psz)
   {

      return false;

   }

   void dib::div_alpha()
   {
      map();

      BYTE *dst = (BYTE*)get_data();
      int64_t size = scan_area();


      // >> 8 instead of / 255 subsequent alpha_blend operations say thanks on true_blend because (255) * (1/254) + (255) * (254/255) > 255


      /*      while (size >= 8)
            {
               dst[0] = LOBYTE(((i32)dst[0] * (i32)dst[3])>> 8);
               dst[1] = LOBYTE(((i32)dst[1] * (i32)dst[3])>> 8);
               dst[2] = LOBYTE(((i32)dst[2] * (i32)dst[3])>> 8);

               dst[4+0] = LOBYTE(((i32)dst[4+0] * (i32)dst[4+3])>> 8);
               dst[4+1] = LOBYTE(((i32)dst[4+1] * (i32)dst[4+3])>> 8);
               dst[4+2] = LOBYTE(((i32)dst[4+2] * (i32)dst[4+3])>> 8);

               dst[8+0] = LOBYTE(((i32)dst[8+0] * (i32)dst[8+3])>> 8);
               dst[8+1] = LOBYTE(((i32)dst[8+1] * (i32)dst[8+3])>> 8);
               dst[8+2] = LOBYTE(((i32)dst[8+2] * (i32)dst[8+3])>> 8);

               dst[12+0] = LOBYTE(((i32)dst[12+0] * (i32)dst[12+3])>> 8);
               dst[12+1] = LOBYTE(((i32)dst[12+1] * (i32)dst[12+3])>> 8);
               dst[12+2] = LOBYTE(((i32)dst[12+2] * (i32)dst[12+3])>> 8);

               dst[16+0] = LOBYTE(((i32)dst[16+0] * (i32)dst[16+3])>> 8);
               dst[16+1] = LOBYTE(((i32)dst[16+1] * (i32)dst[16+3])>> 8);
               dst[16+2] = LOBYTE(((i32)dst[16+2] * (i32)dst[16+3])>> 8);

               dst[20+0] = LOBYTE(((i32)dst[20+0] * (i32)dst[20+3])>> 8);
               dst[20+1] = LOBYTE(((i32)dst[20+1] * (i32)dst[20+3])>> 8);
               dst[20+2] = LOBYTE(((i32)dst[20+2] * (i32)dst[20+3])>> 8);

               dst[24+0] = LOBYTE(((i32)dst[24+0] * (i32)dst[24+3])>> 8);
               dst[24+1] = LOBYTE(((i32)dst[24+1] * (i32)dst[24+3])>> 8);
               dst[24+2] = LOBYTE(((i32)dst[24+2] * (i32)dst[24+3])>> 8);

               dst[28+0] = LOBYTE(((i32)dst[28+0] * (i32)dst[28+3])>> 8);
               dst[28+1] = LOBYTE(((i32)dst[28+1] * (i32)dst[28+3])>> 8);
               dst[28+2] = LOBYTE(((i32)dst[28+2] * (i32)dst[28+3])>> 8);

               dst += 4 * 8;
               size -= 8;
            }*/
      while (size--)
      {
         if (dst[3] == 0)
         {
            dst[0] = 0;
            dst[1] = 0;
            dst[2] = 0;
         }
         else
         {
            dst[0] = byte_clip((i32)dst[0] * 255 / (i32)dst[3]);
            dst[1] = byte_clip((i32)dst[1] * 255 / (i32)dst[3]);
            dst[2] = byte_clip((i32)dst[2] * 255 / (i32)dst[3]);
         }

         dst += 4;

      }

   }

   void dib::div_alpha(point ptDst, ::size size)
   {

      dib * pdibDst = this;

      pdibDst->map();

      if (ptDst.x < 0)
      {
         size.cx += ptDst.x;
         ptDst.x = 0;
      }

      if (size.cx < 0)
         return;

      if (ptDst.y < 0)
      {
         size.cy += ptDst.y;
         ptDst.y = 0;
      }

      if (size.cy < 0)
         return;

      int xEnd = MIN(size.cx, pdibDst->m_size.cx - ptDst.x);

      int yEnd = MIN(size.cy, pdibDst->m_size.cy - ptDst.y);

      if (xEnd < 0)
         return;

      if (yEnd < 0)
         return;

      i32 scanDst = pdibDst->m_iScan;

#ifdef APPLEOS

      byte * pdst = &((byte *)pdibDst->m_pcolorref)[scanDst * (m_size.cy - ptDst.y - 1) + ptDst.x * sizeof(COLORREF)];

#else

      byte * pdst = &((byte *)pdibDst->m_pcolorref)[scanDst * ptDst.y + ptDst.x * sizeof(COLORREF)];

#endif

      byte * pdst2;

      for (int y = 0; y < yEnd; y++)
      {

#ifdef APPLEOS

         pdst2 = (byte *)&pdst[scanDst * (-y)];

#else

         pdst2 = (byte *)&pdst[scanDst * y];

#endif

         for (int x = 0; x < xEnd; x++)
         {

            if (pdst2[3] == 0)
            {
               pdst2[0] = 0;
               pdst2[1] = 0;
               pdst2[2] = 0;
            }
            else
            {
               pdst2[0] = byte_clip((i32)pdst2[0] * 255 / (i32)pdst2[3]);
               pdst2[1] = byte_clip((i32)pdst2[1] * 255 / (i32)pdst2[3]);
               pdst2[2] = byte_clip((i32)pdst2[2] * 255 / (i32)pdst2[3]);
            }

            pdst2 += 4;

         }

      }

   }

   void dib::Map(i32 ToRgb, i32 FromRgb)
   {
      byte * dst = (byte *)get_data();
      int64_t size = scan_area();

      while (size--)
      {
         *dst = (byte)(*dst == FromRgb ? ToRgb : *dst);
         dst += 4;
      }
   }


   void dib::ToAlphaAndFill(i32 i, COLORREF cr)
   {
      BYTE *dst = (BYTE*)get_data();
      int64_t size = scan_area();

      BYTE uchB = rgba_get_b(cr);
      BYTE uchG = rgba_get_g(cr);
      BYTE uchR = rgba_get_r(cr);

      while (size--)
      {
         dst[3] = dst[i];
         dst[0] = uchB;
         dst[1] = uchG;
         dst[2] = uchR;
         dst += 4;
      }
   }

   void dib::GrayToARGB(COLORREF cr)
   {
      BYTE *dst = (BYTE*)get_data();
      int64_t size = scan_area();

      uint32_t dwB = rgba_get_b(cr);
      uint32_t dwG = rgba_get_g(cr);
      uint32_t dwR = rgba_get_r(cr);

      while (size-- > 0)
      {
         dst[3] = dst[0];
         dst[0] = (BYTE)(((dwB * dst[3]) / 256) & 0xff);
         dst[1] = (BYTE)(((dwG * dst[3]) / 256) & 0xff);
         dst[2] = (BYTE)(((dwR * dst[3]) / 256) & 0xff);
         dst += 4;
      }
   }


   void dib::BitBlt(dib *pdib, i32 op)
   {
      if (op == 123) // zero dest RGB, invert alpha, and OR src RGB
      {

         //COLORREF _colorref = RGB ( 0, 0, 0 ) | (255 << 24);
         //COLORREF colorrefa[2];
         //colorrefa[0] = _colorref;
         //colorrefa[1] = _colorref;

         //COLORREF _colorrefN = RGB ( 255, 255, 255) | (0 << 24);
         //COLORREF colorrefaN[2];
         //colorrefaN[0] = _colorrefN;

         //colorrefaN[1] = _colorrefN;

         //int64_t isize = area();
         //LPDWORD lpbitsSrc= (LPDWORD) pdib->get_data();
         //LPDWORD lpbitsDest= (LPDWORD) get_data();

         //memcpy(lpbitsDest, lpbitsSrc, (size_t) (isize * sizeof(COLORREF)));

         from(pdib);

      }

   }

   void dib::BitBlt(int cxParam, int cyParam, dib *pdib, i32 op)
   {

      map();

      pdib->map();

      if (op == 1 && m_size == pdib->m_size && pdib->m_iScan == m_iScan) // op == 1 indicates can ignore cxParam and cyParam and perform full memcpy
      {

         if (cyParam <= 0)
            return;

         cyParam = MIN(cyParam, MIN(pdib->m_size.cy, m_size.cy));

#if defined(APPLEOS)

         memcpy(&m_pcolorref[m_iScan / 4 * (pdib->m_size.cy - cyParam)], &pdib->m_pcolorref[m_iScan / 4 * (pdib->m_size.cy - cyParam)], cyParam * m_iScan);

#else

         memcpy(m_pcolorref, pdib->m_pcolorref, cyParam * m_iScan);

#endif

      }
      else if (op == 0 || op == 1)
      {

         if (cxParam <= 0)
            return;

         if (cyParam <= 0)
            return;

         cxParam = MIN(cxParam, MIN(pdib->m_size.cx, m_size.cx));

         cyParam = MIN(cyParam, MIN(pdib->m_size.cy, m_size.cy));

         int iStrideSrc = pdib->m_iScan;

         if (iStrideSrc <= 0)
         {

            iStrideSrc = cxParam * sizeof(COLORREF);

         }

         if (m_iScan == iStrideSrc && m_iScan == pdib->m_iScan)
         {

            memcpy(m_pcolorref, pdib->m_pcolorref, cyParam * m_iScan);

         }
         else
         {

            int wsrc = iStrideSrc / sizeof(COLORREF);
            int wdst = m_iScan / sizeof(COLORREF);
            int cw = MIN(cxParam, m_size.cx) * sizeof(COLORREF);

            int h = MIN(cyParam, m_size.cy);


            COLORREF * psrc = pdib->m_pcolorref;
            COLORREF * pdst = m_pcolorref;

            for (int i = 0; i < h; i++)
            {

               memcpy(pdst, psrc, cw);

               pdst += wdst;

               psrc += wsrc;

            }

         }

      }

   }

   void dib::Invert()
   {
      int64_t size = scan_area();
      LPBYTE lpb = (LPBYTE)get_data();
      for (i32 i = 0; i < size; i++)
      {
         lpb[0] = 255 - lpb[0];
         lpb[1] = 255 - lpb[1];
         lpb[2] = 255 - lpb[2];
         lpb += 4;
      }
   }

   void dib::channel_invert(visual::rgba::echannel echannel)
   {
      int64_t size = scan_area();
      LPBYTE lpb = (LPBYTE)get_data();
      lpb += ((i32)echannel) % 4;
      for (i32 i = 0; i < size; i++)
      {
         *lpb = 255 - *lpb;
         lpb += 4;
      }
   }

   void dib::channel_multiply(visual::rgba::echannel echannel, double dRate, bool bIfAlphaIgnorePreDivPosMult)
   {
      if (dRate < 0)
         return;
      //#ifdef __APPLE__
      if (!bIfAlphaIgnorePreDivPosMult && echannel == visual::rgba::channel_alpha)
      {
         div_alpha();
      }
      //#endif
      int64_t size = scan_area();
      LPBYTE lpb = (LPBYTE)get_data();
      lpb += ((i32)echannel) % 4;
      i32 iDiv = 256 * 256;
      i32 iMul = (i32)(dRate * ((double)iDiv));
      i32 iRes;
      for (int64_t i = 0; i < size; i++)
      {
         iRes = *lpb * iMul / iDiv;
         *lpb = (byte)(iRes > 255 ? 255 : iRes);
         lpb += 4;
      }
      //#ifdef __APPLE__
      if (!bIfAlphaIgnorePreDivPosMult && echannel == visual::rgba::channel_alpha)
      {
         mult_alpha();
      }
      //#endif
   }

   void dib::channel_multiply(visual::rgba::echannel echannel, ::draw2d::dib * pdib, bool bIfAlphaIgnorePreDivPosMult)
   {

      //      int64_t size = area();

      map();

      pdib->map();
      if (!bIfAlphaIgnorePreDivPosMult && echannel == visual::rgba::channel_alpha)
      {
         div_alpha();
      }

      LPBYTE lpb1 = (LPBYTE)get_data();

      LPBYTE lpb2 = (LPBYTE)pdib->get_data();

      lpb1 += ((i32)echannel) % 4;

      lpb2 += ((i32)echannel) % 4;

      for (i32 y = 0; y < m_size.cy; y++)
      {

         LPBYTE lpb1_2 = lpb1 + (m_iScan * y);

         LPBYTE lpb2_2 = lpb2 + (pdib->m_iScan * y);

         for (i32 x = 0; x < m_size.cx; x++)
         {

            int i = (BYTE)(((uint32_t)*lpb1_2 * (uint32_t)*lpb2_2) / 255);
            *lpb2 = i;

            lpb1_2 += 4;

            lpb2_2 += 4;

         }

      }
      if (!bIfAlphaIgnorePreDivPosMult && echannel == visual::rgba::channel_alpha)
      {
         mult_alpha();
      }

   }


   void dib::channel_darken(visual::rgba::echannel echannel, ::draw2d::dib * pdib)
   {
      int64_t size = scan_area();
      LPBYTE lpb1 = (LPBYTE)get_data();
      LPBYTE lpb2 = (LPBYTE)pdib->get_data();
      lpb1 += ((i32)echannel) % 4;
      lpb2 += ((i32)echannel) % 4;
      for (int64_t i = 0; i < size; i++)
      {
         *lpb1 = *lpb1 < *lpb2 ? *lpb1 : *lpb2;
         lpb1 += 4;
         lpb2 += 4;
      }
   }

   void dib::channel_lighten(visual::rgba::echannel echannel, ::draw2d::dib * pdib)
   {
      int64_t size = scan_area();
      LPBYTE lpb1 = (LPBYTE)get_data();
      LPBYTE lpb2 = (LPBYTE)pdib->get_data();
      lpb1 += ((i32)echannel) % 4;
      lpb2 += ((i32)echannel) % 4;
      for (int64_t i = 0; i < size; i++)
      {
         *lpb1 = *lpb1 > *lpb2 ? *lpb1 : *lpb2;
         lpb1 += 4;
         lpb2 += 4;
      }
   }

   void dib::channel_from(visual::rgba::echannel echannel, ::draw2d::dib * pdib)
   {
      map();
      pdib->map();
      int64_t size = m_iScan * m_size.cy / sizeof(COLORREF);
      int64_t size64 = size / 64;
      LPBYTE lpb1 = (LPBYTE)get_data();
      LPBYTE lpb2 = (LPBYTE)pdib->get_data();
      lpb1 += ((i32)echannel) % 4;
      lpb2 += ((i32)echannel) % 4;
      int64_t i = 0;
      for (; i < size64; i++)
      {
         lpb1[4 * 0] = lpb2[4 * 0];
         lpb1[4 * 1] = lpb2[4 * 1];
         lpb1[4 * 2] = lpb2[4 * 2];
         lpb1[4 * 3] = lpb2[4 * 3];
         lpb1[4 * 4] = lpb2[4 * 4];
         lpb1[4 * 5] = lpb2[4 * 5];
         lpb1[4 * 6] = lpb2[4 * 6];
         lpb1[4 * 7] = lpb2[4 * 7];
         lpb1[4 * 8] = lpb2[4 * 8];
         lpb1[4 * 9] = lpb2[4 * 9];
         lpb1[4 * 10] = lpb2[4 * 10];
         lpb1[4 * 11] = lpb2[4 * 11];
         lpb1[4 * 12] = lpb2[4 * 12];
         lpb1[4 * 13] = lpb2[4 * 13];
         lpb1[4 * 14] = lpb2[4 * 14];
         lpb1[4 * 15] = lpb2[4 * 15];
         lpb1[4 * 16] = lpb2[4 * 16];
         lpb1[4 * 17] = lpb2[4 * 17];
         lpb1[4 * 18] = lpb2[4 * 18];
         lpb1[4 * 19] = lpb2[4 * 19];
         lpb1[4 * 20] = lpb2[4 * 20];
         lpb1[4 * 21] = lpb2[4 * 21];
         lpb1[4 * 22] = lpb2[4 * 22];
         lpb1[4 * 23] = lpb2[4 * 23];
         lpb1[4 * 24] = lpb2[4 * 24];
         lpb1[4 * 25] = lpb2[4 * 25];
         lpb1[4 * 26] = lpb2[4 * 26];
         lpb1[4 * 27] = lpb2[4 * 27];
         lpb1[4 * 28] = lpb2[4 * 28];
         lpb1[4 * 29] = lpb2[4 * 29];
         lpb1[4 * 30] = lpb2[4 * 30];
         lpb1[4 * 31] = lpb2[4 * 31];

         lpb1[4 * 32] = lpb2[4 * 32];
         lpb1[4 * 33] = lpb2[4 * 33];
         lpb1[4 * 34] = lpb2[4 * 34];
         lpb1[4 * 35] = lpb2[4 * 35];
         lpb1[4 * 36] = lpb2[4 * 36];
         lpb1[4 * 37] = lpb2[4 * 37];
         lpb1[4 * 38] = lpb2[4 * 38];
         lpb1[4 * 39] = lpb2[4 * 39];
         lpb1[4 * 40] = lpb2[4 * 40];
         lpb1[4 * 41] = lpb2[4 * 41];
         lpb1[4 * 42] = lpb2[4 * 42];
         lpb1[4 * 43] = lpb2[4 * 43];
         lpb1[4 * 44] = lpb2[4 * 44];
         lpb1[4 * 45] = lpb2[4 * 45];
         lpb1[4 * 46] = lpb2[4 * 46];
         lpb1[4 * 47] = lpb2[4 * 47];
         lpb1[4 * 48] = lpb2[4 * 48];
         lpb1[4 * 49] = lpb2[4 * 49];
         lpb1[4 * 50] = lpb2[4 * 50];
         lpb1[4 * 51] = lpb2[4 * 51];
         lpb1[4 * 52] = lpb2[4 * 52];
         lpb1[4 * 53] = lpb2[4 * 53];
         lpb1[4 * 54] = lpb2[4 * 54];
         lpb1[4 * 55] = lpb2[4 * 55];
         lpb1[4 * 56] = lpb2[4 * 56];
         lpb1[4 * 57] = lpb2[4 * 57];
         lpb1[4 * 58] = lpb2[4 * 58];
         lpb1[4 * 59] = lpb2[4 * 59];
         lpb1[4 * 60] = lpb2[4 * 60];
         lpb1[4 * 61] = lpb2[4 * 61];
         lpb1[4 * 62] = lpb2[4 * 62];
         lpb1[4 * 63] = lpb2[4 * 63];

         lpb1 += 4 * 64;
         lpb2 += 4 * 64;
      }
      i *= 64;
      for (; i < size; i++)
      {
         *lpb1 = *lpb2;
         lpb1 += 4;
         lpb2 += 4;
      }
   }


   void dib::channel_from(visual::rgba::echannel echannel, ::draw2d::dib * pdib, LPCRECT lpcrect)
   {

      map();

      pdib->map();

      class rect r;

      if (!r.intersect(rect(), lpcrect))
      {

         return;

      }

      if (!r.intersect(pdib->rect(), lpcrect))
      {

         return;

      }

      LPBYTE lpb1 = ((LPBYTE)get_data()) + (r.left * sizeof(COLORREF) + r.top * m_iScan);

      LPBYTE lpb2 = ((LPBYTE)pdib->get_data()) + (r.left * sizeof(COLORREF) + r.top * pdib->m_iScan);

      lpb1 += ((i32)echannel) % 4;

      lpb2 += ((i32)echannel) % 4;

      int h = r.height();

      int w = r.width();

      for (int i = 0; i < h; i++)
      {

         LPBYTE lpb1_2 = lpb1;

         LPBYTE lpb2_2 = lpb2;

         for (int j = 0; j < w; j++)
         {

            *lpb1_2 = *lpb2_2;

            lpb1_2 += 4;

            lpb2_2 += 4;

         }

         lpb1 += m_iScan;

         lpb2 += pdib->m_iScan;

      }

   }



   void dib::channel_multiply(visual::rgba::echannel echannel, ::draw2d::dib * pdib, LPCRECT lpcrect, bool bIfAlphaIgnorePreDivPosMult)
   {

      map();

      pdib->map();

      class rect r;

      if (!r.intersect(rect(), lpcrect))
      {

         return;

      }

      if (!r.intersect(pdib->rect(), lpcrect))
      {

         return;

      }

      if (!bIfAlphaIgnorePreDivPosMult && echannel == visual::rgba::channel_alpha)
      {

         div_alpha(r.top_left(), r.get_size());

      }

#ifdef APPLEOS

      LPBYTE lpb1 = ((LPBYTE)get_data()) + (r.left * sizeof(COLORREF) + (m_size.cy - r.top - 1) * m_iScan);

      LPBYTE lpb2 = ((LPBYTE)pdib->get_data()) + (r.left * sizeof(COLORREF) + (pdib->m_size.cy - r.top - 1) * pdib->m_iScan);

#else

      LPBYTE lpb1 = ((LPBYTE)get_data()) + (r.left * sizeof(COLORREF) + r.top * m_iScan);

      LPBYTE lpb2 = ((LPBYTE)pdib->get_data()) + (r.left * sizeof(COLORREF) + r.top * pdib->m_iScan);

#endif

      lpb1 += ((i32)echannel) % 4;

      lpb2 += ((i32)echannel) % 4;

      int h = r.height();

      int w = r.width();

      for (int i = 0; i < h; i++)
      {

         LPBYTE lpb1_2 = lpb1;

         LPBYTE lpb2_2 = lpb2;

         for (int j = 0; j < w; j++)
         {

            *lpb1_2 = *lpb2_2 * *lpb1_2 / 255;

            lpb1_2 += 4;

            lpb2_2 += 4;

         }

#ifdef APPLEOS

         lpb1 -= m_iScan;

         lpb2 -= pdib->m_iScan;

#else

         lpb1 += m_iScan;

         lpb2 += pdib->m_iScan;

#endif

      }

      if (!bIfAlphaIgnorePreDivPosMult && echannel == visual::rgba::channel_alpha)
      {

         mult_alpha(r.top_left(), r.get_size());

      }

   }


   void dib::FillGlass(i32 R, i32 G, i32 B, i32 A)
   {
      BYTE *dst = (BYTE*)get_data();
      int64_t size = scan_area();

      while (size--)
      {
         dst[0] = (BYTE)(((B - dst[0])*A + (dst[0] << 8)) >> 8);
         dst[1] = (BYTE)(((G - dst[1])*A + (dst[1] << 8)) >> 8);
         dst[2] = (BYTE)(((R - dst[2])*A + (dst[2] << 8)) >> 8);
         dst += 4;
      }
   }

   void dib::FillStippledGlass(i32 R, i32 G, i32 B)
   {
      COLORREF color = RGB(B, G, R);
      i32 w = m_size.cx;
      i32 h = m_size.cy;

      for (i32 j = 0; j < w; j++)
      {
         for (i32 i = 0; i < h; i++)
         {
            get_data()[j*w + i] = ((i + j) & 0x1) ? get_data()[j*w + i] : color;
         }
      }
   }

   bool dib::to(dib * pdib) const
   {

      if (pdib == NULL)
         return false;

      return pdib->from(this);

      //if (area() <= 0)
      //   return;

      //// If DibSize Wrong Re-create dib
      //if(dib->m_size != size())
      //   dib->create(size());

      //// do copy

      //map();

      //dib->map();

      //if (get_data() == NULL || dib->get_data() == NULL)
      //   return;

      //memcpy ( dib->get_data(), get_data(), (size_t) area() * sizeof(COLORREF) );


   }


   bool dib::from(const dib * dib)
   {

      if (size() != dib->m_size)
      {

         create(dib->size());

      }

      //dib->defer_realize(dib->get_graphics());
      //defer_realize(dib->get_graphics());

      map();
      ((::draw2d::dib *) dib)->map();
      // If DibSize Wrong Re-create dib
      // do Paste

      if (m_iScan == dib->m_iScan)
      {
         memcpy(get_data(), dib->get_data(), m_size.cy * m_iScan);
      }
      else
      {

         int iScan = MIN(m_iScan, dib->m_iScan);

         for (int i = 0; i < m_size.cy; i++)
         {
            memcpy(&((byte *)get_data())[m_iScan * i], &((byte *)dib->get_data())[dib->m_iScan * i], iScan);
         }

      }

      return true;

   }


   bool dib::bitmap_blend(::draw2d::graphics * pgraphics, LPCRECT lpcrect)
   {

      return pgraphics->draw(lpcrect, get_graphics()) != FALSE;

   }


   bool dib::color_blend(COLORREF cr, BYTE bAlpha)
   {

      BYTE *dst = (BYTE*)get_data();
      int64_t size = scan_area();

      uint32_t dwB = rgba_get_b(cr);
      uint32_t dwG = rgba_get_g(cr);
      uint32_t dwR = rgba_get_r(cr);

      uint32_t dwB_ = dwB << 8;
      uint32_t dwG_ = dwG << 8;
      uint32_t dwR_ = dwR << 8;

      while (size--)
      {
         dst[0] = (BYTE)(((dst[0] - dwB)*bAlpha + dwB_) >> 8);
         dst[1] = (BYTE)(((dst[1] - dwG)*bAlpha + dwG_) >> 8);
         dst[2] = (BYTE)(((dst[2] - dwG)*bAlpha + dwR_) >> 8);
         dst += 4;
      }
      return true;
   }

   bool dib::op(string str)
   {

      if (str == "horz-swap")
      {

         // half width
         int hx = m_size.cx / 2;
         // aligned scan
         int as = m_iScan / sizeof(COLORREF);

         for (index i = 0; i < m_size.cy; i++)
         {
            for (index j = 0; j < hx; j++)
            {
               swap(m_pcolorref[i * as + j], m_pcolorref[i * as + m_size.cx - j]);
            }
         }

         return true;
      }


      return false;

   }


   void dib::Blend(dib * dib, i32 A)
   {
      if (m_size != dib->m_size)
         return;

      BYTE *src = (BYTE*)dib->get_data();
      BYTE *dst = (BYTE*)get_data();
      int64_t size = scan_area();

      while (size--)
      {
         dst[0] = (BYTE)(((src[0] - dst[0])*A + (dst[0] << 8)) >> 8);
         dst[1] = (BYTE)(((src[1] - dst[1])*A + (dst[1] << 8)) >> 8);
         dst[2] = (BYTE)(((src[2] - dst[2])*A + (dst[2] << 8)) >> 8);
         dst += 4;
         src += 4;
      }
   }

   bool dib::Blend(dib *pDib, dib *DibA, i32 A)
   {
      if (m_size != pDib->m_size ||
            m_size != DibA->size())
         return false;

      BYTE *src = (BYTE*)pDib->get_data();
      BYTE *dst = (BYTE*)get_data();
      BYTE *alf = (BYTE*)DibA->get_data();
      int64_t size = scan_area();

      A = 2 - A;

      while (size--)
      {
         dst[0] = (BYTE)(((src[0] - dst[0])*alf[A] + (dst[0] << 8)) >> 8);
         dst[1] = (BYTE)(((src[1] - dst[1])*alf[A] + (dst[1] << 8)) >> 8);
         dst[2] = (BYTE)(((src[2] - dst[2])*alf[A] + (dst[2] << 8)) >> 8);
         dst += 4;
         src += 4;
         alf += 4;
      }

      return true;
   }


   bool dib::Blend(dib *pDib, dib *DibA)
   {
      if (m_size != pDib->m_size ||
            m_size != DibA->size())
         return false;

      map();
      pDib->map();
      DibA->map();

      BYTE *src = (BYTE*)pDib->get_data();
      BYTE *dst = (BYTE*)get_data();
      BYTE *alf = ((BYTE*)DibA->get_data()) + 3;
      int64_t size = scan_area();

      while (size--)
      {
         dst[0] = (BYTE)(((src[0] - dst[0])* (*alf) + (dst[0] << 8)) >> 8);
         dst[1] = (BYTE)(((src[1] - dst[1])* (*alf) + (dst[1] << 8)) >> 8);
         dst[2] = (BYTE)(((src[2] - dst[2])* (*alf) + (dst[2] << 8)) >> 8);
         dst += 4;
         src += 4;
         alf += 4;
      }

      return true;
   }



   bool dib::blend(dib * pdib, dib * pdibRate)
   {
      if (m_size != pdib->m_size ||
            m_size != pdibRate->size())
         return false;

      BYTE *src = (BYTE*)pdib->get_data();
      BYTE *dst = (BYTE*)get_data();
      BYTE *alf = (BYTE*)pdibRate->get_data();
      int64_t size = scan_area();

      while (size >= 2)
      {
         dst[00] = (BYTE)(((((i32)src[00] - (i32)dst[00]) * (i32)alf[00]) + (i32)dst[00] * (i32)255) / 255);
         dst[01] = (BYTE)(((((i32)src[01] - (i32)dst[01]) * (i32)alf[01]) + (i32)dst[01] * (i32)255) / 255);
         dst[02] = (BYTE)(((((i32)src[02] - (i32)dst[02]) * (i32)alf[02]) + (i32)dst[02] * (i32)255) / 255);
         dst[03] = (BYTE)(((((i32)src[03] - (i32)dst[03]) * (i32)alf[03]) + (i32)dst[03] * (i32)255) / 255);
         dst[04] = (BYTE)(((((i32)src[04] - (i32)dst[04]) * (i32)alf[04]) + (i32)dst[04] * (i32)255) / 255);
         dst[05] = (BYTE)(((((i32)src[05] - (i32)dst[05]) * (i32)alf[05]) + (i32)dst[05] * (i32)255) / 255);
         dst[06] = (BYTE)(((((i32)src[06] - (i32)dst[06]) * (i32)alf[06]) + (i32)dst[06] * (i32)255) / 255);
         dst[07] = (BYTE)(((((i32)src[07] - (i32)dst[07]) * (i32)alf[07]) + (i32)dst[07] * (i32)255) / 255);
         dst += 4 * 2;
         src += 4 * 2;
         alf += 4 * 2;
         size -= 2;
      }
      while (size > 0)
      {
         dst[00] = (BYTE)(((((i32)src[00] - (i32)dst[00]) * (i32)alf[00]) + (i32)dst[00] * (i32)255) / 255);
         dst[01] = (BYTE)(((((i32)src[01] - (i32)dst[01]) * (i32)alf[01]) + (i32)dst[01] * (i32)255) / 255);
         dst[02] = (BYTE)(((((i32)src[02] - (i32)dst[02]) * (i32)alf[02]) + (i32)dst[02] * (i32)255) / 255);
         dst[03] = (BYTE)(((((i32)src[03] - (i32)dst[03]) * (i32)alf[03]) + (i32)dst[03] * (i32)255) / 255);
         dst += 4;
         src += 4;
         alf += 4;
         size--;
      }

      return true;
   }

   void dib::Darken(dib *dib)
   {
      if (size() != dib->m_size)
         return;

      BYTE *src = (BYTE*)dib->get_data();
      BYTE *dst = (BYTE*)get_data();
      int64_t size = scan_area();

      while (size--)
      {
         dst[0] = (BYTE)((src[0] < dst[0]) ? src[0] : dst[0]);
         dst[1] = (BYTE)((src[1] < dst[1]) ? src[1] : dst[1]);
         dst[2] = (BYTE)((src[2] < dst[2]) ? src[2] : dst[2]);
         dst += 4;
         src += 4;
      }
   }

   void dib::Difference(dib *dib)
   {
      if (size() != dib->m_size)
         return;

      BYTE *src = (BYTE*)dib->get_data();
      BYTE *dst = (BYTE*)get_data();
      int64_t size = scan_area();

      while (size--)
      {
         i32 Difference;
         Difference = src[0] - dst[0];
         dst[0] = (BYTE)((Difference < 0) ? -Difference : Difference);
         Difference = src[1] - dst[1];
         dst[1] = (BYTE)((Difference < 0) ? -Difference : Difference);
         Difference = src[2] - dst[2];
         dst[2] = (BYTE)((Difference < 0) ? -Difference : Difference);
         dst += 4;
         src += 4;
      }
   }

   void dib::Lighten(dib *dib)
   {
      if (size() != dib->m_size)
         return;

      BYTE *src = (BYTE*)dib->get_data();
      BYTE *dst = (BYTE*)get_data();
      int64_t size = scan_area();

      while (size--)
      {
         dst[0] = (BYTE)((src[0] > dst[0]) ? src[0] : dst[0]);
         dst[1] = (BYTE)((src[1] > dst[1]) ? src[1] : dst[1]);
         dst[2] = (BYTE)((src[2] > dst[2]) ? src[2] : dst[2]);
         dst += 4;
         src += 4;
      }
   }

   /// centered on 0.
   /// > 0 lighter (safe)
   /// < 0 darker (non safe)
   void dib::lighten(double dRate)
   {
      BYTE *dst = (BYTE*)get_data();
      int64_t size = scan_area();

      while (size--)
      {
         dst[0] += (BYTE) ((dst[3] - dst[0]) * dRate);
         dst[1] += (BYTE) ((dst[3] - dst[1]) * dRate);
         dst[2] += (BYTE) ((dst[3] - dst[2]) * dRate);
         dst += 4;
      }

   }

   void dib::Multiply(dib *dib)
   {
      if (size() != dib->m_size)
         return;

      BYTE *src = (BYTE*)dib->get_data();
      BYTE *dst = (BYTE*)get_data();
      int64_t size = scan_area();

      while (size--)
      {
         dst[0] = (BYTE)(((src[0])*(dst[0])) >> 8);
         dst[1] = (BYTE)(((src[1])*(dst[1])) >> 8);
         dst[2] = (BYTE)(((src[2])*(dst[2])) >> 8);
         dst += 4;
         src += 4;
      }
   }

   void dib::Screen(dib *dib)
   {
      if (size() != dib->m_size)
         return;

      BYTE *src = (BYTE*)dib->get_data();
      BYTE *dst = (BYTE*)get_data();
      int64_t size = scan_area();

      while (size--)
      {
         dst[0] = (BYTE)(255 - (((255 - src[0])*(255 - dst[0])) >> 8));
         dst[1] = (BYTE)(255 - (((255 - src[1])*(255 - dst[1])) >> 8));
         dst[2] = (BYTE)(255 - (((255 - src[2])*(255 - dst[2])) >> 8));
         dst += 4;
         src += 4;
      }
   }

   //////////////////////////////////////////////////////////////////////
   // rectangle Functions
   //////////////////////////////////////////////////////////////////////

   void dib::copy(dib *dib, i32 x, i32 y)
   {
      // Clip Rect
      i32 px = (x >= 0) ? x : 0;
      i32 py = (y >= 0) ? y : 0;
      i32 dx = ((x + dib->m_size.cx) < m_size.cx) ? dib->m_size.cx : m_size.cx - x;
      i32 dy = ((y + dib->m_size.cy) < m_size.cy) ? dib->m_size.cy : m_size.cy - y;
      dx = (x >= 0) ? dx : dx + x;
      dy = (y >= 0) ? dy : dy + y;

      // If Nothing to copy return
      if ((dx <= 0) || (dy <= 0))
         return;
      // If DibSize Wrong Re-create dib
      if ((dx != dib->m_size.cx) || (dy != dib->m_size.cy))
         dib->create(dx, dy);

      map();
      dib->map();

      // Prepare buffer Addresses
      COLORREF *src = get_data() + (py*m_size.cx) + px;
      COLORREF *dst = dib->get_data();

      // Do copy
      while (dy--)
      {
         for (i32 i = 0; i < dx; i++)
            dst[i] = src[i];
         src += m_size.cx;
         dst += dib->m_size.cx;
      }

   }

   void dib::PasteRect(dib *dib, i32 x, i32 y)
   {
      // Clip Rect
      i32 px = (x >= 0) ? x : 0;
      i32 py = (y >= 0) ? y : 0;
      i32 dx = ((x + dib->m_size.cx) < m_size.cx) ? dib->m_size.cx : m_size.cx - x;
      i32 dy = ((y + dib->m_size.cy) < m_size.cy) ? dib->m_size.cy : m_size.cy - y;
      dx = (x >= 0) ? dx : dx + x;
      dy = (y >= 0) ? dy : dy + y;

      // If Nothing to Paste return
      if ((dx <= 0) || (dy <= 0))
         return;

      // Prepare buffer Addresses
      COLORREF *src = dib->get_data() + ((py - y)*dib->m_size.cx) + px - x;
      COLORREF *dst = get_data() + (py*m_size.cx) + px;

      // Do Paste
      while (dy--)
      {
         for (i32 i = 0; i < dx; i++)
            dst[i] = src[i];
         src += dib->m_size.cx;
         dst += m_size.cx;
      }
   }

   void dib::fill_rect(LPCRECT lpcrect, i32 R, i32 G, i32 B)
   {
      i32 x = lpcrect->left;
      i32 y = lpcrect->top;
      i32 w = ::width(lpcrect);
      i32 h = ::height(lpcrect);
      // Clip Rect
      i32 px = (x >= 0) ? x : 0;
      i32 py = (y >= 0) ? y : 0;
      i32 dx = ((x + w) < m_size.cx) ? w : m_size.cx - x;
      i32 dy = ((y + h) < m_size.cy) ? h : m_size.cy - y;
      dx = (x >= 0) ? dx : dx + x;
      dy = (y >= 0) ? dy : dy + y;

      // If Nothing to Fill return
      if ((dx <= 0) || (dy <= 0))
         return;

      map();

      COLORREF *dst = get_data() + (py*m_size.cx) + px;

      while (dy--)
      {

         for (i32 i = 0; i < dx; i++)
         {

            ((byte *)&dst[i])[0] = R;
            ((byte *)&dst[i])[1] = G;
            ((byte *)&dst[i])[2] = B;

         }

         dst += m_iScan / sizeof(COLORREF);

      }

   }


   void dib::fill_rect(LPCRECT lpcrect, COLORREF cr)
   {

      if (m_bMapped)
      {

         i32 x = lpcrect->left;
         i32 y = lpcrect->top;
         i32 w = ::width(lpcrect);
         i32 h = ::height(lpcrect);
         // Clip Rect
         i32 px = x;
         if (w < 0)
         {
            px += w;
            w = -w;
         }

         px = (px >= 0) ? px : 0;
         i32 py = y;
         if (h < 0)
         {
            py += h;
            h = -h;
         }
         py = (py >= 0) ? py : 0;
         i32 dx;
         dx = ((px + w) < m_size.cx) ? w : m_size.cx - px;
         i32 dy;
         dy = ((py + h) < m_size.cy) ? h : m_size.cy - py;
         dx = (px >= 0) ? dx : dx + x;
         dy = (py >= 0) ? dy : dy + y;

         // If Nothing to Fill return
         if ((dx <= 0) || (dy <= 0))
            return;

         // Prepare buffer Address
         COLORREF *dst = get_data() + (py*m_size.cx) + px;

         while (dy--)
         {

            for (i32 i = 0; i < dx; i++)
            {

               dst[i] = cr;

            }

            dst += m_iScan / sizeof(COLORREF);

         }

      }
      else
      {

         ::draw2d::e_alpha_mode emodeOld = get_graphics()->m_ealphamode;

         if (get_graphics()->m_ealphamode != ::draw2d::alpha_mode_set)
         {

            get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

         }

         get_graphics()->fill_solid_rect(lpcrect, cr);

         if (get_graphics()->m_ealphamode != emodeOld)
         {

            get_graphics()->set_alpha_mode(emodeOld);

         }

      }

   }


   void dib::fill_glass_rect(LPCRECT lpcrect, i32 R, i32 G, i32 B, i32 A)
   {

      i32 x = lpcrect->left;
      i32 y = lpcrect->top;
      i32 w = ::width(lpcrect);
      i32 h = ::height(lpcrect);

      // Clip Rect
      i32 px = (x >= 0) ? x : 0;
      i32 py = (y >= 0) ? y : 0;
      i32 dx = ((x + w) < m_size.cx) ? w : m_size.cx - x;
      i32 dy = ((y + h) < m_size.cy) ? h : m_size.cy - y;
      dx = (x >= 0) ? dx : dx + x;
      dy = (y >= 0) ? dy : dy + y;

      // If Nothing to FillGlass return
      if ((dx <= 0) || (dy <= 0))
         return;

      // Prepare buffer Address
      BYTE *dst = (BYTE *)get_data() + ((py*m_size.cx) + px) * 4;

      // Do FillGlass
      while (dy--)
      {
         for (i32 i = 0; i < dx; i++)
         {
            dst[0] = (BYTE)(((B - dst[0])*A + (dst[0] << 8)) >> 8);
            dst[1] = (BYTE)(((G - dst[1])*A + (dst[1] << 8)) >> 8);
            dst[2] = (BYTE)(((R - dst[2])*A + (dst[2] << 8)) >> 8);
            dst += 4;
         }

         dst += (m_size.cx - dx) << 2;

      }

   }


   void dib::fill_stippled_glass_rect(LPCRECT lpcrect, i32 R, i32 G, i32 B)
   {

      i32 x = lpcrect->left;
      i32 y = lpcrect->top;
      i32 w = ::width(lpcrect);
      i32 h = ::height(lpcrect);

      // Clip Rect
      i32 px = (x >= 0) ? x : 0;
      i32 py = (y >= 0) ? y : 0;
      i32 dx = ((x + w) < m_size.cx) ? w : m_size.cx - x;
      i32 dy = ((y + h) < m_size.cy) ? h : m_size.cy - y;
      dx = (x >= 0) ? dx : dx + x;
      dy = (y >= 0) ? dy : dy + y;

      // If Nothing to FillStippledGlass return
      if ((dx <= 0) || (dy <= 0))
         return;

      // Prepare buffer Address
      COLORREF *dst = get_data() + (py*m_size.cx) + px;
      COLORREF color = RGB(B, G, R);

      // Do FillStippledGlass
      for (i32 j = 0; j < dy; j++)
      {
         for (i32 i = 0; i < dx; i++)
         {
            dst[i] = ((i + j) & 0x1) ? dst[i] : color;
         }
         dst += m_size.cx;
      }
   }

   void dib::BlendRect(dib *dib, i32 x, i32 y, i32 A)
   {
      // Clip Rect
      i32 px = (x >= 0) ? x : 0;
      i32 py = (y >= 0) ? y : 0;
      i32 dx = ((x + dib->m_size.cx) < m_size.cx) ? dib->m_size.cx : m_size.cx - x;
      i32 dy = ((y + dib->m_size.cy) < m_size.cy) ? dib->m_size.cy : m_size.cy - y;
      dx = (x >= 0) ? dx : dx + x;
      dy = (y >= 0) ? dy : dy + y;

      // If Nothing to Blend return
      if ((dx <= 0) || (dy <= 0))
         return;

      // Prepare buffer Addresses
      BYTE *src = (BYTE *)dib->get_data() + (((py - y)*dib->m_size.cx) + px - x) * 4;
      BYTE *dst = (BYTE *)get_data() + ((py*m_size.cx) + px) * 4;

      // Do Blend
      while (dy--)
      {
         for (i32 i = 0; i < dx; i++)
         {
            dst[0] = (BYTE)(((src[0] - dst[0])*A + (dst[0] << 8)) >> 8);
            dst[1] = (BYTE)(((src[1] - dst[1])*A + (dst[1] << 8)) >> 8);
            dst[2] = (BYTE)(((src[2] - dst[2])*A + (dst[2] << 8)) >> 8);
            dst += 4;
            src += 4;
         }
         dst += (m_size.cx - dx) << 2;
         src += (dib->m_size.cx - dx) << 2;
      }
   }

   void dib::DarkenRect(dib *dib, i32 x, i32 y)
   {
      // Clip Rect
      i32 px = (x >= 0) ? x : 0;
      i32 py = (y >= 0) ? y : 0;
      i32 dx = ((x + dib->m_size.cx) < m_size.cx) ? dib->m_size.cx : m_size.cx - x;
      i32 dy = ((y + dib->m_size.cy) < m_size.cy) ? dib->m_size.cy : m_size.cy - y;
      dx = (x >= 0) ? dx : dx + x;
      dy = (y >= 0) ? dy : dy + y;

      // If Nothing to Darken return
      if ((dx <= 0) || (dy <= 0))
         return;

      // Prepare buffer Addresses
      BYTE *src = (BYTE *)dib->get_data() + (((py - y)*dib->m_size.cx) + px - x) * 4;
      BYTE *dst = (BYTE *)get_data() + ((py*m_size.cx) + px) * 4;

      // Do Darken
      while (dy--)
      {
         for (i32 i = 0; i < dx; i++)
         {
            dst[0] = (BYTE)((src[0] < dst[0]) ? src[0] : dst[0]);
            dst[1] = (BYTE)((src[1] < dst[1]) ? src[1] : dst[1]);
            dst[2] = (BYTE)((src[2] < dst[2]) ? src[2] : dst[2]);
            dst += 4;
            src += 4;
         }
         dst += (m_size.cx - dx) << 2;
         src += (dib->m_size.cx - dx) << 2;
      }
   }

   void dib::DifferenceRect(dib *dib, i32 x, i32 y)
   {
      // Clip Rect
      i32 px = (x >= 0) ? x : 0;
      i32 py = (y >= 0) ? y : 0;
      i32 dx = ((x + dib->m_size.cx) < m_size.cx) ? dib->m_size.cx : m_size.cx - x;
      i32 dy = ((y + dib->m_size.cy) < m_size.cy) ? dib->m_size.cy : m_size.cy - y;
      dx = (x >= 0) ? dx : dx + x;
      dy = (y >= 0) ? dy : dy + y;

      // If Nothing to Difference return
      if ((dx <= 0) || (dy <= 0))
         return;

      // Prepare buffer Addresses
      BYTE *src = (BYTE *)dib->get_data() + (((py - y)*dib->m_size.cx) + px - x) * 4;
      BYTE *dst = (BYTE *)get_data() + ((py*m_size.cx) + px) * 4;

      // Do Difference
      while (dy--)
      {
         for (i32 i = 0; i < dx; i++)
         {
            i32 Difference;
            Difference = src[0] - dst[0];
            dst[0] = (BYTE)((Difference < 0) ? -Difference : Difference);
            Difference = src[1] - dst[1];
            dst[1] = (BYTE)((Difference < 0) ? -Difference : Difference);
            Difference = src[2] - dst[2];
            dst[2] = (BYTE)((Difference < 0) ? -Difference : Difference);
            dst += 4;
            src += 4;
         }
         dst += (m_size.cx - dx) << 2;
         src += (dib->m_size.cx - dx) << 2;
      }
   }

   void dib::LightenRect(dib *dib, i32 x, i32 y)
   {
      // Clip Rect
      i32 px = (x >= 0) ? x : 0;
      i32 py = (y >= 0) ? y : 0;
      i32 dx = ((x + dib->m_size.cx) < m_size.cx) ? dib->m_size.cx : m_size.cx - x;
      i32 dy = ((y + dib->m_size.cy) < m_size.cy) ? dib->m_size.cy : m_size.cy - y;
      dx = (x >= 0) ? dx : dx + x;
      dy = (y >= 0) ? dy : dy + y;

      // If Nothing to Lighten return
      if ((dx <= 0) || (dy <= 0))
         return;

      // Prepare buffer Addresses
      BYTE *src = (BYTE *)dib->get_data() + (((py - y)*dib->m_size.cx) + px - x) * 4;
      BYTE *dst = (BYTE *)get_data() + ((py*m_size.cx) + px) * 4;

      // Do Lighten
      while (dy--)
      {
         for (i32 i = 0; i < dx; i++)
         {
            dst[0] = (BYTE)((src[0] > dst[0]) ? src[0] : dst[0]);
            dst[1] = (BYTE)((src[1] > dst[1]) ? src[1] : dst[1]);
            dst[2] = (BYTE)((src[2] > dst[2]) ? src[2] : dst[2]);
            dst += 4;
            src += 4;
         }
         dst += (m_size.cx - dx) << 2;
         src += (dib->m_size.cx - dx) << 2;
      }
   }

   void dib::MultiplyRect(dib *dib, i32 x, i32 y)
   {
      // Clip Rect
      i32 px = (x >= 0) ? x : 0;
      i32 py = (y >= 0) ? y : 0;
      i32 dx = ((x + dib->m_size.cx) < m_size.cx) ? dib->m_size.cx : m_size.cx - x;
      i32 dy = ((y + dib->m_size.cy) < m_size.cy) ? dib->m_size.cy : m_size.cy - y;
      dx = (x >= 0) ? dx : dx + x;
      dy = (y >= 0) ? dy : dy + y;

      // If Nothing to Multiply return
      if ((dx <= 0) || (dy <= 0))
         return;

      // Prepare buffer Addresses
      BYTE *src = (BYTE *)dib->get_data() + (((py - y)*dib->m_size.cx) + px - x) * 4;
      BYTE *dst = (BYTE *)get_data() + ((py*m_size.cx) + px) * 4;

      // Do Multiply
      while (dy--)
      {
         for (i32 i = 0; i < dx; i++)
         {
            dst[0] = (BYTE)(((src[0])*(dst[0])) >> 8);
            dst[1] = (BYTE)(((src[1])*(dst[1])) >> 8);
            dst[2] = (BYTE)(((src[2])*(dst[2])) >> 8);
            dst += 4;
            src += 4;
         }
         dst += (m_size.cx - dx) << 2;
         src += (dib->m_size.cx - dx) << 2;
      }
   }

   void dib::ScreenRect(dib *dib, i32 x, i32 y)
   {
      // Clip Rect
      i32 px = (x >= 0) ? x : 0;
      i32 py = (y >= 0) ? y : 0;
      i32 dx = ((x + dib->m_size.cx) < m_size.cx) ? dib->m_size.cx : m_size.cx - x;
      i32 dy = ((y + dib->m_size.cy) < m_size.cy) ? dib->m_size.cy : m_size.cy - y;
      dx = (x >= 0) ? dx : dx + x;
      dy = (y >= 0) ? dy : dy + y;

      // If Nothing to Screen return
      if ((dx <= 0) || (dy <= 0))
         return;

      // Prepare buffer Addresses
      BYTE *src = (BYTE *)dib->get_data() + (((py - y)*dib->m_size.cx) + px - x) * 4;
      BYTE *dst = (BYTE *)get_data() + ((py*m_size.cx) + px) * 4;

      // Do Screen
      while (dy--)
      {
         for (i32 i = 0; i < dx; i++)
         {
            dst[0] = (BYTE)(255 - (((255 - src[0])*(255 - dst[0])) >> 8));
            dst[1] = (BYTE)(255 - (((255 - src[1])*(255 - dst[1])) >> 8));
            dst[2] = (BYTE)(255 - (((255 - src[2])*(255 - dst[2])) >> 8));
            dst += 4;
            src += 4;
         }
         dst += (m_size.cx - dx) << 2;
         src += (dib->m_size.cx - dx) << 2;
      }
   }

   //////////////////////////////////////////////////////////////////////
   // Line Functions
   //////////////////////////////////////////////////////////////////////

   /*void dib::Line ( i32 x1, i32 y1, i32 x2, i32 y2, i32 R, i32 G, i32 B )
   {
   i32 dx, dy, k1, k2, d, x, y;
   COLORREF color=RGB ( B, G, R );

   dx=x2-x1;
   dy=y2-y1;
   d=(dy<<1)-dx;
   k1=dy<<1;
   k2=(dy-dx)<<1;
   x=x1;
   y=y1;

   get_data()[y*m_size.cx+x]=color;
   while (x<dx)
   {
   if (d<=0)
   {
   d+=k1;
   x++;
   }
   else
   {
   d+=k2;
   x++;
   y++;
   }
   get_data()[y*m_size.cx+x]=color;
   }
   }*/


   void dib::horizontal_line(i32 y, i32 R, i32 G, i32 B, i32 A, i32 x1, i32 x2)
   {
      map();
      if (m_size.cx == 0)
         return;
      x1 %= m_size.cx;
      x2 %= m_size.cx;
      if (x2 < 0)
         x2 += m_size.cx;
      if (x1 < 0)
         x1 += m_size.cx;
      COLORREF color = RGB(B, G, R) | (A << 24);

#ifdef APPLEOS

      COLORREF * pdata = get_data() + (m_size.cy - y - 1) * (m_iScan / sizeof(COLORREF));

#else

      COLORREF * pdata = get_data() + y * (m_iScan / sizeof(COLORREF));

#endif

      for (i32 x = x1; x <= x2; x++)
      {

         *pdata = color;

         pdata++;

      }

   }


   void dib::Line(i32 x1, i32 y1, i32 x2, i32 y2, i32 R, i32 G, i32 B)
   {
      i32 d, x, y, core, ay, sx, sy, dx, dy;
      COLORREF color = RGB(B, G, R);

      dx = x2 - x1;
      core = abs(dx) << 1;
      sx = (dx < 0) ? -1 : 1;
      dy = y2 - y1;
      ay = abs(dy) << 1;
      sy = (dy < 0) ? -1 : 1;
      x = x1;
      y = y1;

      if (core > ay)
      {
         d = ay - (core >> 1);
         while (x != x2)
         {
            get_data()[y*(m_iScan / sizeof(COLORREF)) + x] = color;
            if (d >= 0)
            {
               y += sy;
               d -= core;
            }
            x += sx;
            d += ay;
         }
      }
      else
      {
         d = core - (ay >> 1);
         while (y != y2)
         {
            get_data()[y*(m_iScan / sizeof(COLORREF)) + x] = color;
            if (d >= 0)
            {
               x += sx;
               d -= ay;
            }
            y += sy;
            d += core;
         }
      }
   }

   void dib::LineGlass(i32 x1, i32 y1, i32 x2, i32 y2, i32 R, i32 G, i32 B, i32 A)
   {
      i32 d, x, y, core, ay, sx, sy, dx, dy;
      //      COLORREF color=RGB ( B, G, R );
      BYTE *dst = (BYTE *)get_data();

      dx = x2 - x1;
      core = abs(dx) << 1;
      sx = (dx < 0) ? -1 : 1;
      dy = y2 - y1;
      ay = abs(dy) << 1;
      sy = (dy < 0) ? -1 : 1;
      x = x1;
      y = y1;

      if (core > ay)
      {
         d = ay - (core >> 1);
         while (x != x2)
         {
            dst[(y*(m_iScan / sizeof(COLORREF)) + x) << 2] = (BYTE)(((B - dst[(y*(m_iScan / sizeof(COLORREF)) + x) << 2])*A + (dst[(y*(m_iScan / sizeof(COLORREF)) + x) << 2] << 8)) >> 8);
            dst[((y*(m_iScan / sizeof(COLORREF)) + x) << 2) + 1] = (BYTE)(((G - dst[((y*(m_iScan / sizeof(COLORREF)) + x) << 2) + 1])*A + (dst[((y*(m_iScan / sizeof(COLORREF)) + x) << 2) + 1] << 8)) >> 8);
            dst[((y*(m_iScan / sizeof(COLORREF)) + x) << 2) + 2] = (BYTE)(((R - dst[((y*(m_iScan / sizeof(COLORREF)) + x) << 2) + 2])*A + (dst[((y*(m_iScan / sizeof(COLORREF)) + x) << 2) + 2] << 8)) >> 8);
            if (d >= 0)
            {
               y += sy;
               d -= core;
            }
            x += sx;
            d += ay;
         }
      }
      else
      {
         d = core - (ay >> 1);
         while (y != y2)
         {
            dst[(y*(m_iScan / sizeof(COLORREF)) + x) << 2] = (BYTE)(((B - dst[(y*(m_iScan / sizeof(COLORREF)) + x) << 2])*A + (dst[(y*(m_iScan / sizeof(COLORREF)) + x) << 2] << 8)) >> 8);
            dst[((y*(m_iScan / sizeof(COLORREF)) + x) << 2) + 1] = (BYTE)(((G - dst[((y*(m_iScan / sizeof(COLORREF)) + x) << 2) + 1])*A + (dst[((y*(m_iScan / sizeof(COLORREF)) + x) << 2) + 1] << 8)) >> 8);
            dst[((y*(m_iScan / sizeof(COLORREF)) + x) << 2) + 2] = (BYTE)(((R - dst[((y*(m_iScan / sizeof(COLORREF)) + x) << 2) + 2])*A + (dst[((y*(m_iScan / sizeof(COLORREF)) + x) << 2) + 2] << 8)) >> 8);
            if (d >= 0)
            {
               x += sx;
               d -= ay;
            }
            y += sy;
            d += core;
         }
      }
   }

   void dib::Mask(COLORREF crMask, COLORREF crInMask, COLORREF crOutMask)
   {
      COLORREF crFind = RGB(rgba_get_b(crMask), rgba_get_g(crMask), rgba_get_r(crMask));
      COLORREF crSet = RGB(rgba_get_b(crInMask), rgba_get_g(crInMask), rgba_get_r(crInMask));
      COLORREF crUnset = RGB(rgba_get_b(crOutMask), rgba_get_g(crOutMask), rgba_get_r(crOutMask));

      int64_t size = scan_area();

      for (i32 i = 0; i < size; i++)
         if (get_data()[i] == crFind)
            get_data()[i] = crSet;
         else
            get_data()[i] = crUnset;

   }

   void dib::transparent_color(color color)
   {
      COLORREF crFind = color.get_rgb();
      int64_t iSize = scan_area();

      for (i32 i = 0; i < iSize; i++)
         if ((get_data()[i] & 0x00ffffff) == crFind)
            ((LPBYTE)&get_data()[i])[3] = 255;
         else
            ((LPBYTE)&get_data()[i])[3] = 0;
   }

   void dib::channel_mask(uchar uchFind, uchar uchSet, uchar uchUnset, visual::rgba::echannel echannel)
   {
      i32 size = (m_iScan / sizeof(COLORREF)) * m_size.cy;
      uchar * puch = (uchar *)get_data();
      puch += ((i32)echannel) % 4;

      for (i32 i = 0; i < size; i++)
      {
         if (*puch == uchFind)
            *puch = uchSet;
         else
            *puch = uchUnset;
         puch += 4;
      }
   }

   uint32_t dib::GetPixel(i32 x, i32 y)
   {
      uint32_t dw = *(get_data() + x + (m_size.cy - y - 1) * (m_iScan / sizeof(COLORREF)));
      int iA = rgba_get_a(dw);
      if (iA == 0)
      {
         return RGB(rgba_get_b(dw), rgba_get_g(dw), rgba_get_r(dw));
      }
      else
      {
         return ARGB(iA, rgba_get_b(dw) * 255 / iA, rgba_get_g(dw) * 255 / iA, rgba_get_r(dw) * 255 / iA);
      }
   }

   // too slow for animation on AMD XP gen_hon.
   // TOP SUGGESTION:
   // The gradient can´t have more then 256 levels of the most bright color
   // (white). So creating a radial fill of radius 256 and then using fasting
   // stretching algorithms is much faster than calculating radial fill.
   void dib::RadialFill(BYTE alpha, BYTE red, BYTE green, BYTE blue, i32 xCenter, i32 yCenter, i32 iRadius)
   {
      if (iRadius == 0)
         return;
      /*if(version == 0)
      {

      i32 iR = iRadius - 1;

      i32 xL = xCenter - iR;
      i32 xU = xCenter + iR;
      i32 yL = yCenter - iR;
      i32 yU = yCenter + iR;


      if(xL < 0) xL = 0;
      if(xU >= m_Size.(m_iScan / sizeof(COLORREF))) xU = m_Size.(m_iScan / sizeof(COLORREF)) - 1;
      if(yL < 0) yL = 0;
      if(yU >= m_Size.m_size.cy) yU = m_Size.m_size.cy - 1;


      BYTE *dst = ((BYTE*)(get_data() + xL + yL * m_Size.(m_iScan / sizeof(COLORREF))));
      uint32_t dwAdd = ((m_Size.(m_iScan / sizeof(COLORREF)) - 1 - xU) + xL) * 4;
      i32 size=m_Size.(m_iScan / sizeof(COLORREF))*m_Size.m_size.cy;
      double iLevel;

      i32 dx, dy;
      i32 dx0, dy0;
      i32 dx1, dy1;
      i32 dx2, dy2;
      i32 dx3, dy3;
      i32 dx4, dy4;
      i32 dx5, dy5;
      i32 dx6, dy6;
      i32 dx7, dy7;
      i32 dx8, dy8;
      i32 dx9, dy9;
      i32 dxA, dyA;
      i32 dxB, dyB;
      i32 dxC, dyC;
      i32 dxD, dyD;
      i32 dxE, dyE;
      i32 dxF, dyF;

      unsigned long dr;
      unsigned long dq;
      unsigned long dr0, dq0;
      unsigned long dr1, dq1;
      unsigned long dr2, dq2;
      unsigned long dr3, dq3;
      unsigned long dr4, dq4;
      unsigned long dr5, dq5;
      unsigned long dr6, dq6;
      unsigned long dr7, dq7;
      unsigned long dr8, dq8;
      unsigned long dr9, dq9;
      unsigned long drA, dqA;
      unsigned long drB, dqB;
      unsigned long drC, dqC;
      unsigned long drD, dqD;
      unsigned long drE, dqE;
      unsigned long drF, dqF;
      i32 x, y;

      {
      for(y = yL; y <= yU; y++)
      {
      for(x = xL; x <= xU; x++)
      {
      dx = abs(x - xCenter);
      dy = abs(y - yCenter);
      isqrt((dx * dx) + (dy * dy), &dr, &dq);
      if(dr < iRadius)
      {
      iLevel = 1.0 - dr * 1.0 / iRadius;
      dst[0] = blue  * iLevel;
      dst[1] = green * iLevel;
      dst[2] = red   * iLevel;
      }
      dst += 4;
      }
      dst += dwAdd;
      }
      }
      }
      else if(version == 1)*/
      {

         LPBYTE lpbAlloc = (LPBYTE)malloc(iRadius * iRadius);
         LPBYTE lpb = lpbAlloc;


         i32 x, y;
         i32 b;

         //         i32 r2 = iRadius * iRadius;

         for (y = 0; y < iRadius; y++)
         {
            for (x = y; x < iRadius; x++)
            {
               b = (i32)(sqrt((double)(x * x) + (y * y)) * 255 / iRadius);
               if (b > 255)
                  b = 0;
               else
                  b = 255 - b;


               lpb[x + y * iRadius] = (byte)b;
               lpb[y + x * iRadius] = (byte)b;
            }
         }


         i32 iR = iRadius - 1;

         i32 xL = xCenter - iR;
         i32 xU = xCenter + iR;
         i32 yL = yCenter - iR;
         i32 yU = yCenter + iR;


         if (xL < 0) xL = 0;
         if (xU >= m_size.cx) xU = m_size.cx - 1;
         if (yL < 0) yL = 0;
         if (yU >= m_size.cy) yU = m_size.cy - 1;


         BYTE *dst = ((BYTE*)(get_data() + xL + yL * (m_iScan / sizeof(COLORREF))));
         uint32_t dwAdd = (((m_iScan / sizeof(COLORREF)) - 1 - xU) + xL) * 4;
         //         int64_t size = area();

         i32 dx, dy;

         // Top Left

         for (y = yL; y <= yU; y++)
         {
            for (x = xL; x <= xU; x++)
            {
               dx = abs(x - xCenter);
               dy = abs(y - yCenter);
               b = lpb[dx + dy * iRadius];
               dst[0] = byte(blue     * b / 255);
               dst[1] = byte(green    * b / 255);
               dst[2] = byte(red      * b / 255);
               dst[3] = byte(alpha    * b / 255);
               dst += 4;
            }
            dst += dwAdd;
         }

         free(lpbAlloc);
      }
   }


   void dib::RadialFill(
   BYTE alpha1, BYTE red1, BYTE green1, BYTE blue1,
   BYTE alpha2, BYTE red2, BYTE green2, BYTE blue2,
   i32 xCenter, i32 yCenter, i32 iRadius)
   {
      if (iRadius == 0)
         return;

      map();
      /*if(version == 0)
      {

      i32 iR = iRadius - 1;

      i32 xL = xCenter - iR;
      i32 xU = xCenter + iR;
      i32 yL = yCenter - iR;
      i32 yU = yCenter + iR;


      if(xL < 0) xL = 0;
      if(xU >= m_Size.(m_iScan / sizeof(COLORREF))) xU = m_Size.(m_iScan / sizeof(COLORREF)) - 1;
      if(yL < 0) yL = 0;
      if(yU >= m_Size.m_size.cy) yU = m_Size.m_size.cy - 1;


      BYTE *dst = ((BYTE*)(get_data() + xL + yL * m_Size.(m_iScan / sizeof(COLORREF))));
      uint32_t dwAdd = ((m_Size.(m_iScan / sizeof(COLORREF)) - 1 - xU) + xL) * 4;
      i32 size=m_Size.(m_iScan / sizeof(COLORREF))*m_Size.m_size.cy;
      double iLevel;

      i32 dx, dy;
      i32 dx0, dy0;
      i32 dx1, dy1;
      i32 dx2, dy2;
      i32 dx3, dy3;
      i32 dx4, dy4;
      i32 dx5, dy5;
      i32 dx6, dy6;
      i32 dx7, dy7;
      i32 dx8, dy8;
      i32 dx9, dy9;
      i32 dxA, dyA;
      i32 dxB, dyB;
      i32 dxC, dyC;
      i32 dxD, dyD;
      i32 dxE, dyE;
      i32 dxF, dyF;

      unsigned long dr;
      unsigned long dq;
      unsigned long dr0, dq0;
      unsigned long dr1, dq1;
      unsigned long dr2, dq2;
      unsigned long dr3, dq3;
      unsigned long dr4, dq4;
      unsigned long dr5, dq5;
      unsigned long dr6, dq6;
      unsigned long dr7, dq7;
      unsigned long dr8, dq8;
      unsigned long dr9, dq9;
      unsigned long drA, dqA;
      unsigned long drB, dqB;
      unsigned long drC, dqC;
      unsigned long drD, dqD;
      unsigned long drE, dqE;
      unsigned long drF, dqF;
      i32 x, y;

      {
      for(y = yL; y <= yU; y++)
      {
      for(x = xL; x <= xU; x++)
      {
      dx = abs(x - xCenter);
      dy = abs(y - yCenter);
      isqrt((dx * dx) + (dy * dy), &dr, &dq);
      if(dr < iRadius)
      {
      iLevel = 1.0 - dr * 1.0 / iRadius;
      dst[0] = blue  * iLevel;
      dst[1] = green * iLevel;
      dst[2] = red   * iLevel;
      }
      dst += 4;
      }
      dst += dwAdd;
      }
      }
      }
      else if(version == 1)*/
      {

         //         memory mem;
         //
         //         mem.allocate((iRadius * iRadius) + 4);
         //
         //         LPBYTE lpbAlloc = mem.get_data();
         //
         //         LPBYTE lpb = lpbAlloc;
         //
         //
         //         i32 x, y;
         //         i32 b;
         //
         ////         i32 r2 = iRadius * iRadius;
         //
         //         for(y = 0; y < iRadius; y++)
         //         {
         //            for(x = y; x < iRadius; x++)
         //            {
         //
         //               b = (i32) (sqrt((double) (x * x) + (y * y)) * 255 / iRadius);
         //
         //               if(b > 255)
         //                  b = 255;
         //
         //
         //               lpb[x + y * iRadius] = (byte) b;
         //               lpb[y + x * iRadius] = (byte) b;
         //            }
         //         }


         i32 iR = iRadius;

         i32 xL = xCenter - iR;
         i32 xU = xCenter + iR;
         i32 yL = yCenter - iR;
         i32 yU = yCenter + iR;


         if (xL < 0) xL = 0;
         if (xU > m_size.cx) xU = m_size.cx;
         if (yL < 0) yL = 0;
         if (yU > m_size.cy) yU = m_size.cy;


         BYTE *dst = ((BYTE*)(get_data() + xL + yL * (m_iScan / sizeof(COLORREF))));
         uint32_t dwAdd = (((m_iScan / sizeof(COLORREF)) - xU) + xL) * 4;
         //         int64_t size = area();

         double dx, dy;

         double dRadius = 255.0 / (double)iRadius;

         BYTE bComp;

         int b;

         // Top Left

         int y;
         int x;

         for (y = yL; y < yU; y++)
         {
            for (x = xL; x < xU; x++)
            {
               dx = abs(x - xCenter);
               dy = abs(y - yCenter);
               b = (int)(sqrt((dx * dx) + (dy * dy)) * dRadius);

               if (b > 255)
               {
                  b = 255;
               }

               bComp = 255 - b;
               dst[0] = byte(((blue1  * bComp) + (blue2  * b)) / 255);
               dst[1] = byte(((green1 * bComp) + (green2 * b)) / 255);
               dst[2] = byte(((red1   * bComp) + (red2   * b)) / 255);
               dst[3] = byte(((alpha1 * bComp) + (alpha2 * b)) / 255);
               dst += 4;
            }
            dst += dwAdd;
         }

      }
   }



   void dib::SetIconMask(::visual::icon * picon, i32 cx, i32 cy)
   {

//      _throw(todo(get_app()));
//
//      // xxx todo create(m_size.cx, m_size.cy);
//
//      if (m_size.cx <= 0 || m_size.cy <= 0)
//         return;
//
//
//
//
//      // White blend dib
//      dib dib1;
//
//      _throw(todo(get_app()));
//
//      // xxx todo dib1.create(m_size.cx, m_size.cy);
//
//      dib1.Fill(0, 255, 255, 255);
//
//#ifdef METROWIN
//
//      ::exception::throw_not_implemented(get_app());
//
//#else
//
//      dib1.get_graphics()->DrawIcon(
//         0, 0,
//         picon,
//         m_size.cx, m_size.cy,
//         0,
//         NULL,
//         DI_IMAGE | DI_MASK);
//
//#endif
//
//      // Black blend dib
//      ::draw2d::dib_sp spdib2(allocer());
//
//
//      _throw(todo(get_app()));
//
//      // xxx todo spdib2->create(m_size.cx, m_size.cy);
//      spdib2->Fill(0, 0, 0, 0);
//
//#ifdef METROWIN
//
//      ::exception::throw_not_implemented(get_app());
//
//#else
//
//      spdib2->get_graphics()->DrawIcon(
//         0, 0,
//         picon,
//         m_size.cx, m_size.cy,
//         0,
//         NULL,
//         DI_IMAGE | DI_MASK);
//
//#endif
//
//      // Mask dib
//      dib dibM;
//      _throw(todo(get_app()));
//
//      // xxx todo dibM.create(m_size.cx, m_size.cy);
//
//#ifdef METROWIN
//
//      ::exception::throw_not_implemented(get_app());
//
//#else
//
//      dibM.get_graphics()->DrawIcon(
//         0, 0,
//         picon,
//         m_size.cx, m_size.cy,
//         0,
//         NULL,
//         DI_MASK);
//
//#endif
//
//      BYTE * r1 = (BYTE*)dib1.get_data();
//      BYTE * r2 = (BYTE*)spdib2->get_data();
//      BYTE * srcM = (BYTE*)dibM.get_data();
//      BYTE * dest = (BYTE*)get_data();
//      i32 iSize = m_size.cx*m_size.cy;
//
//      BYTE b;
//      BYTE bMax;
//      while (iSize-- > 0)
//      {
//         if (srcM[0] == 255)
//         {
//            bMax = 0;
//         }
//         else
//         {
//            bMax = 0;
//            b = (BYTE)(r1[0] - r2[0]);
//            bMax = MAX(b, bMax);
//            b = (BYTE)(r1[1] - r2[1]);
//            bMax = MAX(b, bMax);
//            b = (BYTE)(r1[2] - r2[2]);
//            bMax = MAX(b, bMax);
//            bMax = 255 - bMax;
//         }
//         dest[0] = bMax;
//         dest[1] = bMax;
//         dest[2] = bMax;
//         dest += 4;
//         srcM += 4;
//         r1 += 4;
//         r2 += 4;
//      }
//


   }


   bool dib::rotate(dib * pdib, double dAngle)
   {

      double o = dAngle * pi() / 180.0;

      int a = (int)(::fabs((double)pdib->m_size.cx * ::sin(o)) + ::fabs((double)pdib->m_size.cy * ::cos(o)));

      int b = (int)(::fabs((double)pdib->m_size.cx * ::cos(o)) + ::fabs((double)pdib->m_size.cy * ::sin(o)));

      if (!create(b, a))
      {

         return false;

      }

      rotate(pdib, dAngle, 1.0);

      return true;

   }

   void dib::rotate(dib * pdib, double dAngle, double dScale)
   {

      i32 l = MAX(m_size.cx, m_size.cy);

      i32 jmax = MIN(l, m_size.cy / 2);

      i32 jmin = -jmax;

      i32 imax = MIN(l, m_size.cx / 2);

      i32 imin = -imax;

      int xoff = pdib->m_size.cx / 2;

      int yoff = pdib->m_size.cy / 2;

      double o = dAngle * pi() / 180.0;

      int ioff = m_size.cx / 2;

      int joff = m_size.cy / 2;

      int dsw = m_iScan / sizeof(COLORREF);

      int ssw = pdib->m_iScan / sizeof(COLORREF);

      double dCos = ::cos(dAngle * pi() / 180.0) * dScale;

      double dSin = ::sin(dAngle * pi() / 180.0) * dScale;

      int x;

      int y;

      for (i32 j = jmin; j < jmax; j++)
      {

         for (i32 i = imin; i < imax; i++)
         {

            x = (i32)fabs((dCos * i - dSin * j) + xoff);

            y = (i32)fabs((dSin * i + dCos * j) + yoff);

            x %= pdib->m_size.cx;

            y %= pdib->m_size.cy;

            m_pcolorref[(j + joff) * dsw + (i + ioff)] = pdib->m_pcolorref[y * ssw + x];

         }

      }
   }


   void dib::Rotate034(dib * pdib, double dAngle, double dScale)
   {

      i32 l = MAX(m_size.cx, m_size.cy);


      i32 jmax = MIN(l, m_size.cy / 2);
      i32 jmin = -jmax;
      i32 imax = MIN(l, m_size.cx / 2);
      i32 imin = -imax;


      if ((m_size.cy % 2) == 1)
         jmax++;

      if ((m_size.cx % 2) == 1)
         imax++;

      i32 joff = m_size.cy / 2;
      i32 ioff = m_size.cx / 2;

      int stride_unit = m_iScan / sizeof(COLORREF);
      i32 k = 0;
      double dCos = ::cos(dAngle * pi() / 180.0) * dScale;
      double dSin = ::sin(dAngle * pi() / 180.0) * dScale;
      i32 cx1 = m_size.cx - 1;
      i32 cy1 = m_size.cy - 1;
      for (i32 j = jmin; j < jmax; j++)
      {
         for (i32 i = imin; i < imax; i++)
         {
            i32 x, y;

            // A Combination of a 2d Translation/rotation/Scale Matrix
            //x=abs((i32(dCos * i - dSin * j) + ioff) % m_size.cx);
            //y=abs((i32(dSin * i + dCos * j) + joff) % m_size.cy);

            x = (i32)fabs((dCos * i - dSin * j) + ioff);
            y = (i32)fabs((dSin * i + dCos * j) + joff);

            if ((x / m_size.cx) % 2 == 0)
            {
               x %= m_size.cx;
            }
            else
            {
               x = cx1 - (x % m_size.cx);
            }

            if ((y / m_size.cy) % 2 == 0)
            {
               y %= m_size.cy;
            }
            else
            {
               y = cy1 - (y % m_size.cy);
            }



            get_data()[(j + joff)*stride_unit + (i + ioff)] =
            pdib->get_data()[y * stride_unit + x];
            k++;
         }
      }
   }


   void dib::rotate(dib * pdib, LPCRECT lpcrect, double dAngle, double dScale)
   {

      i32 l = MAX(m_size.cx, m_size.cy);

      i32 jmax = MIN(l, m_size.cy / 2);
      i32 jmin = -jmax;
      i32 imax = MIN(l, m_size.cx / 2);
      i32 imin = -imax;

      i32 joff = m_size.cy / 2 + lpcrect->left;
      i32 ioff = m_size.cx / 2 + lpcrect->top;
      int stride_unit = m_iScan / sizeof(COLORREF);
      //i32 iAngle = iStep % 360;
      //i32 iAngle = iStep;
      //i32 iAngle = 1;
      //i32 k = 0;

      /*     for ( i32 j=jmin; j<jmax; j++ )
      {
      for ( i32 i=imin; i<imax; i++ )
      {
      i32 x, y;

      // A Combination of a 2d Translation/rotation/Scale Matrix
      x=i32(cos10(i, iAngle) - sin10(j, iAngle)) + ioff;
      y=i32(sin10(i, iAngle) + cos10(j, iAngle)) + joff;
      get_data()[(j+joff)*m_size.cx+(i+ioff)]=
      spdib->get_data()[abs(y%m_size.cy)*m_size.cx+abs(x%m_size.cx)];
      //k++;
      }
      (j+joff)*m_size.cx+(i+ioff)
      }*/

      i32 k = 0;
      double dCos = ::cos(dAngle * pi() / 180.0) * dScale;
      double dSin = ::sin(dAngle * pi() / 180.0) * dScale;
      i32 cx1 = m_size.cx - 1;
      i32 cy1 = m_size.cy - 1;
      for (i32 j = jmin; j < jmax; j++)
      {
         for (i32 i = imin; i < imax; i++)
         {
            i32 x, y;

            // A Combination of a 2d Translation/rotation/Scale Matrix
            //x=abs((i32(dCos * i - dSin * j) + ioff) % m_size.cx);
            //y=abs((i32(dSin * i + dCos * j) + joff) % m_size.cy);

            x = (i32)fabs((dCos * i - dSin * j) + ioff);
            y = (i32)fabs((dSin * i + dCos * j) + joff);

            if ((x / m_size.cx) % 2 == 0)
            {
               x %= m_size.cx;
            }
            else
            {
               x = cx1 - (x % m_size.cx);
            }

            if ((y / m_size.cy) % 2 == 0)
            {
               y %= m_size.cy;
            }
            else
            {
               y = cy1 - (y % m_size.cy);
            }

            get_data()[(j + joff)*stride_unit + (i + ioff)] =  pdib->get_data()[y * stride_unit + x];

            k++;

         }

      }

   }


   bool dib::rotate90(dib * pdib)
   {

      if (!create(pdib->m_size.cy, pdib->m_size.cx))
      {

         return false;

      }

      map();

      pdib->map();

      i32 cx = pdib->m_size.cx;

      i32 cy = pdib->m_size.cy;

      int s = m_iScan / sizeof(COLORREF);

      int srcS = pdib->m_iScan / sizeof(COLORREF);

      for (i32 i = 0; i < cx; i++)
      {

         for (i32 j = 0; j < cy; j++)
         {

            m_pcolorref[i * s + j] = pdib->m_pcolorref[(cy - j - 1) * srcS + i];

         }

      }

      return true;

   }


   bool dib::rotate180(dib * pdib)
   {

      if (!create(pdib->m_size.cx, pdib->m_size.cy))
      {

         return false;

      }

      map();

      pdib->map();

      i32 cx = m_size.cx;

      i32 cy = m_size.cy;

      int s = m_iScan / sizeof(COLORREF);

      int srcS = pdib->m_iScan / sizeof(COLORREF);

      for (i32 i = 0; i < cy; i++)
      {

         for (i32 j = 0; j < cx; j++)
         {

            m_pcolorref[(cy - i - 1) * s + (cx - j - 1)] = pdib->m_pcolorref[i * srcS + j];

         }

      }

      return true;

   }


   bool dib::rotate270(dib * pdib)
   {

      if (!create(pdib->m_size.cy, pdib->m_size.cx))
      {

         return false;

      }

      map();

      pdib->map();

      i32 cx = pdib->m_size.cx;

      i32 cy = pdib->m_size.cy;

      int s = m_iScan / sizeof(COLORREF);

      int srcS = pdib->m_iScan / sizeof(COLORREF);

      for (i32 i = 0; i < cx; i++)
      {

         for (i32 j = 0; j < cy; j++)
         {

            m_pcolorref[i * s + j] = pdib->m_pcolorref[j * srcS + (cx - i - 1)];

         }

      }

      return true;

   }


   bool dib::rotate90()
   {

      sp(dib) pdib = clone();

      return rotate90(pdib);

   }


   bool dib::rotate180()
   {

      sp(dib) pdib = clone();

      return rotate180(pdib);

   }


   bool dib::rotate270()
   {

      sp(dib) pdib = clone();

      return rotate270(pdib);

   }


   bool dib::rotate90flipx(dib * pdib)
   {

      if (!create(pdib->m_size.cy, pdib->m_size.cx))
      {

         return false;

      }

      map();

      pdib->map();

      i32 cx = pdib->m_size.cx;

      i32 cy = pdib->m_size.cy;

      int s = m_iScan / sizeof(COLORREF);

      int srcS = pdib->m_iScan / sizeof(COLORREF);

      for (i32 i = 0; i < cx; i++)
      {

         for (i32 j = 0; j < cy; j++)
         {

            m_pcolorref[i * s + j] = pdib->m_pcolorref[j * srcS + i];

         }

      }

      return true;

   }


   bool dib::rotate180flipx(dib * pdib)
   {

      if (!create(pdib->m_size.cx, pdib->m_size.cy))
      {

         return false;

      }

      map();

      pdib->map();

      i32 cx = m_size.cx;

      i32 cy = m_size.cy;

      int s = m_iScan / sizeof(COLORREF);

      int srcS = pdib->m_iScan / sizeof(COLORREF);

      for (i32 i = 0; i < cy; i++)
      {

         for (i32 j = 0; j < cx; j++)
         {

            m_pcolorref[i * s + j] = pdib->m_pcolorref[(cy - i - 1) * srcS + j];

         }

      }

      return true;

   }


   bool dib::rotate270flipx(dib * pdib)
   {

      if (!create(pdib->m_size.cy, pdib->m_size.cx))
      {

         return false;

      }

      map();

      pdib->map();

      i32 cx = pdib->m_size.cx;

      i32 cy = pdib->m_size.cy;

      int s = m_iScan / sizeof(COLORREF);

      int srcS = pdib->m_iScan / sizeof(COLORREF);

      for (i32 i = 0; i < cx; i++)
      {

         for (i32 j = 0; j < cy; j++)
         {

            m_pcolorref[i * s + j] = pdib->m_pcolorref[(cy - j - 1) * srcS + (cx - i - 1)];

         }

      }

      return true;

   }


   bool dib::rotate90flipx()
   {

      sp(dib) pdib = clone();

      return rotate90flipx(pdib);

   }


   bool dib::rotate180flipx()
   {

      sp(dib) pdib = clone();

      return rotate180flipx(pdib);

   }

   bool dib::rotate270flipx()
   {

      sp(dib) pdib = clone();

      return rotate270flipx(pdib);

   }


   void dib::FillByte(uchar uch)
   {

      map();

      if (area() <= 0 || get_data() == NULL)
         return;

      int iScan = m_iScan;

      int iHeight = get_size().cy;

      if (iScan <= 0 || iHeight <= 0)
         return;

      memset(get_data(), uch, (memory_size_t)(iScan * iHeight));

   }

   void dib::Fill(COLORREF cr)
   {

      if (m_bMapped)
      {

         int64_t size = scan_area();

         byte a = argb_get_a_value(cr);
         byte r = argb_get_r_value(cr);
         byte g = argb_get_g_value(cr);
         byte b = argb_get_b_value(cr);

         if (a == r && a == g && a == b)
         {

            memset(m_pcolorref, a, m_iScan * m_size.cy);

            return;

         }

         COLORREF * pcr = m_pcolorref;

         #pragma omp parallel for
         for (int64_t i = 0; i < size; i++)
            pcr[i] = cr;

      }
      else if(get_graphics() != NULL)
      {

         get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

         get_graphics()->fill_solid_rect(rect(), cr);

      }

   }


   COLORREF dib::make_colorref(i32 a, i32 r, i32 g, i32 b)
   {

      return ARGB(a, b, g, r);

   }


   void dib::Fill(i32 a, i32 r, i32 g, i32 b)
   {

      if (a == r && a == g && a == b)
      {

         FillByte(a);

      }
      else
      {

         COLORREF color = make_colorref(a, r, g, b);

         Fill(color);

      }

   }


   COLORREF dib::GetAverageColor()
   {

      map();

      int64_t iRLine;

      int64_t iGLine;

      int64_t iBLine;

      int64_t iDiv = m_size.cx * m_size.cy;

      if (iDiv > 0)
      {

         iRLine = 0;

         iGLine = 0;

         iBLine = 0;

         for (i32 y = 0; y < m_size.cy; y++)
         {

            LPBYTE lpb = ((LPBYTE)get_data()) + m_iScan * y;

            for (i32 x = 0; x < m_size.cx; x++)
            {

               iRLine += lpb[2];

               iGLine += lpb[1];

               iBLine += lpb[0];

               lpb += 4;

            }

         }

         i32 iR = (i32)(iRLine / iDiv);

         i32 iG = (i32)(iGLine / iDiv);

         i32 iB = (i32)(iBLine / iDiv);

         return RGB(iR, iG, iB);

      }
      else
      {

         return 0;

      }

   }


   COLORREF dib::GetAverageOpaqueColor()
   {
      map();
      double dR = 0.0;
      double dG = 0.0;
      double dB = 0.0;
      i32 iRLine;
      i32 iGLine;
      i32 iBLine;
      double dDiv = m_size.cx * m_size.cy;
      if (dDiv > 0)
      {

         for (i32 y = 0; y < m_size.cy; y++)
         {
            iRLine = 0;
            iGLine = 0;
            iBLine = 0;
            LPBYTE lpb = ((LPBYTE)get_data()) + m_iScan * y;
            for (i32 x = 0; x < m_size.cx; x++)
            {
               if (lpb[3] == 255)
               {

                  iRLine += lpb[2];
                  iGLine += lpb[1];
                  iBLine += lpb[0];

               }
               lpb += 4;
            }
            dR += iRLine / dDiv;
            dG += iGLine / dDiv;
            dB += iBLine / dDiv;
         }
         i32 iR = (i32)dR;
         i32 iG = (i32)dG;
         i32 iB = (i32)dB;
         return RGB(iR, iG, iB);
      }
      else
      {
         return 0;
      }

   }


   void dib::do_xor(dib * pdib)
   {
      if (m_size.cx != pdib->m_size.cx
            || m_size.cy != pdib->m_size.cy)
      {
         return;
      }
      i32 iCount = m_size.cx * m_size.cy;
      LPDWORD lpd1 = (LPDWORD)get_data();
      LPDWORD lpd2 = (LPDWORD)pdib->get_data();
      for (i32 i = 0; i < iCount; i++)
      {
         *lpd1 = *lpd1 ^ *lpd2;
         lpd1++;
         lpd2++;
      }
   }

   void dib::create_frame(::size size, i32 iFrameCount)
   {
      i32 iSliceCount = (i32)sqrt((double)iFrameCount);
      i32 iFrameWidth = size.cx / iSliceCount;
      i32 iFrameHeight = size.cy / iSliceCount;
      create(iFrameWidth, iFrameHeight);
   }

   void dib::set_frame1(void * lpdata, i32 iFrame, i32 iFrameCount)
   {
      i32 iSliceCount = (i32)sqrt((double)iFrameCount);
      if (iSliceCount == 0)
         iSliceCount = 1;
      i32 iFrameWidth = m_size.cx / iSliceCount;
      i32 iFrameHeight = m_size.cy / iSliceCount;
      i32 iX = iFrame % iSliceCount;
      i32 iY = iFrame / iSliceCount;
      COLORREF * lpDest = &get_data()[iFrameWidth * iX + iY * iFrameHeight * m_size.cx];
      COLORREF * lpSrc = (COLORREF *)lpdata;
      COLORREF * lpDestLine;
      for (i32 y = 0; y < iFrameHeight; y++)
      {
         lpDestLine = &lpDest[y * m_size.cx];
         for (i32 x = 0; x < iFrameWidth; x++)
         {
            *lpDestLine = *lpSrc;
            lpDestLine++;
            lpSrc++;
         }
      }
   }

   void dib::set_frame2(void * lpdata, i32 iFrame, i32 iFrameCount)
   {
      i32 iSliceCount = (i32)sqrt((double)iFrameCount);
      if (iSliceCount == 0)
         iSliceCount = 1;
      i32 iFrameWidth = m_size.cx / iSliceCount;
      i32 iFrameHeight = m_size.cy / iSliceCount;
      i32 iX = iFrame % iSliceCount;
      i32 iY = iFrame / iSliceCount;
      COLORREF * lpDest = &get_data()[iFrameWidth * iX + iY * iFrameHeight * m_size.cx];
      COLORREF * lpSrc = (COLORREF *)lpdata;
      COLORREF * lpDestLine;
      for (i32 y = iFrameHeight - 1; y >= 0; y--)
      {
         lpDestLine = &lpDest[y * m_size.cx];
         for (i32 x = 0; x < iFrameWidth; x++)
         {
            *lpDestLine = *lpSrc;
            lpDestLine++;
            lpSrc++;
         }
      }
   }

   void dib::xor_dib_frame2(void * lpdata, i32 iFrame, i32 iFrameCount)
   {
      i32 iSliceCount = (i32)sqrt((double)iFrameCount);
      if (iSliceCount == 0)
         iSliceCount = 1;
      i32 iFrameWidth = m_size.cx / iSliceCount;
      i32 iFrameHeight = m_size.cy / iSliceCount;
      i32 iX = iFrame % iSliceCount;
      i32 iY = iFrame / iSliceCount;
      COLORREF * lpDest = &get_data()[iFrameWidth * iX + iY * iFrameHeight * m_size.cx];
      COLORREF * lpSrc = (COLORREF *)lpdata;
      COLORREF * lpDestLine;
      for (i32 y = iFrameHeight - 1; y >= 0; y--)
      {
         lpDestLine = &lpDest[y * m_size.cx];
         for (i32 x = 0; x < iFrameWidth; x++)
         {
            *lpDestLine ^= *lpSrc;
            lpDestLine++;
            lpSrc++;
         }
      }
   }

   void dib::get_frame(void * lpdata, i32 iFrame, i32 iFrameCount)
   {
      i32 iSliceCount = (i32)sqrt((double)iFrameCount);
      i32 iFrameWidth = m_size.cx / iSliceCount;
      i32 iFrameHeight = m_size.cy / iSliceCount;
      i32 iX = iFrame % iSliceCount;
      i32 iY = iFrame / iSliceCount;
      COLORREF * lpSrc = &get_data()[iFrameWidth * iX + iY * iFrameHeight *  m_size.cx];
      COLORREF * lpDest = (COLORREF *)lpdata;
      COLORREF * lpSrcLine;
      for (i32 y = 0; y < iFrameHeight; y++)
      {
         lpSrcLine = &lpSrc[y * m_size.cx];
         for (i32 x = 0; x < iFrameWidth; x++)
         {
            *lpDest = *lpSrcLine;
            lpDest++;
            lpSrcLine++;
         }
      }
   }

   bool dib::is_rgb_black()
   {
      i32 iSize = m_size.cx * m_size.cy;
      COLORREF * lp = get_data();
      for (i32 i = 0; i < iSize; i++)
      {
         if ((*lp & 0x00FFFFFF) != 0)
            return false;
         lp++;
      }
      return true;
   }

   void dib::DivideRGB(i32 iDivide)
   {
      if (iDivide == 0)
      {
         return;
      }
      i32 iCount = m_size.cx * m_size.cy;
      LPBYTE lp = ((LPBYTE)get_data());
      i32 i = 0;
      i32 iCount1 = iCount - iCount % 8;
      for (; i < iCount1; i++)
      {
         lp[0] /= (byte)iDivide;
         lp[1] /= (byte)iDivide;
         lp[2] /= (byte)iDivide;

         lp[4] /= (byte)iDivide;
         lp[5] /= (byte)iDivide;
         lp[6] /= (byte)iDivide;

         lp[8] /= (byte)iDivide;
         lp[9] /= (byte)iDivide;
         lp[10] /= (byte)iDivide;

         lp[12] /= (byte)iDivide;
         lp[13] /= (byte)iDivide;
         lp[14] /= (byte)iDivide;

         lp[16] /= (byte)iDivide;
         lp[17] /= (byte)iDivide;
         lp[28] /= (byte)iDivide;

         lp[20] /= (byte)iDivide;
         lp[21] /= (byte)iDivide;
         lp[22] /= (byte)iDivide;

         lp[24] /= (byte)iDivide;
         lp[25] /= (byte)iDivide;
         lp[26] /= (byte)iDivide;

         lp[28] /= (byte)iDivide;
         lp[29] /= (byte)iDivide;
         lp[30] /= (byte)iDivide;

         lp += 4 * 8;
      }
      for (; i < iCount; i++)
      {
         lp[0] /= (byte)iDivide;
         lp[1] /= (byte)iDivide;
         lp[2] /= (byte)iDivide;
         lp += 4;
      }
   }

   void dib::DivideARGB(i32 iDivide)
   {
      if (iDivide == 0)
      {
         return;
      }
      i32 iCount = m_size.cx * m_size.cy;
      LPBYTE lp = ((LPBYTE)get_data());
      for (i32 i = 0; i < iCount; i++)
      {
         lp[0] /= (byte)iDivide;
         lp[1] /= (byte)iDivide;
         lp[2] /= (byte)iDivide;
         lp[3] /= (byte)iDivide;
         lp += 4;
      }
   }

   void dib::DivideA(i32 iDivide)
   {
      if (iDivide == 0)
      {
         return;
      }
      i32 iCount = m_size.cx * m_size.cy;
      LPBYTE lp = ((LPBYTE)get_data());
      for (i32 i = 0; i < iCount; i++)
      {
         lp[3] /= (byte)iDivide;
         lp += 4;
      }
   }


   void dib::stretch_dib(dib * pdib)
   {

      get_graphics()->StretchBlt(0, 0,
                                 m_size.cx,
                                 m_size.cy,
                                 pdib->get_graphics(),
                                 0, 0,
                                 pdib->m_size.cx,
                                 pdib->m_size.cy,
                                 SRCCOPY);

   }


   void dib::set_mipmap(e_mipmap emipmap)
   {

      if (m_emipmap == emipmap)
      {

         return;

      }

      if (emipmap != mipmap_none)
      {

         _set_mipmap(emipmap);

      }

   }


   void dib::_set_mipmap(e_mipmap emipmap)
   {

      ASSERT(emipmap != mipmap_none);

      ::draw2d::dib_sp dib(allocer());

      dib->detach(this);

      double cx = dib->m_size.cx;

      double cy = dib->m_size.cy;

      if (emipmap == mipmap_isotropic)
      {

         double newcx = cx + cx / 2.0 - 1.0;

         double newcy = cy;

         if (!create((i32)newcx, (i32)newcy))
         {

            throw resource_exception(get_app());

         }

         get_graphics()->SetStretchBltMode(HALFTONE);

         int x = dib->m_size.cx;

         int y = 0;

         get_graphics()->BitBlt(0, 0, (i32) cx, (i32) cy, dib->get_graphics());

         while (cx >= 1.0 && cy >= 1.0)
         {

            cx /= 2.0;

            cy /= 2.0;

            if (::multithreading::priority() == ::multithreading::priority_idle)
            {

               map();

               C2PassScale < CBlackmanFilter > scale(1.0);

               scale.Scale(
               &m_pcolorref[x + y * m_iScan / sizeof(COLORREF)],
               (UINT) cx,
               (UINT)cy,
               m_iScan,
               dib->m_pcolorref,
               dib->m_size.cx,
               dib->m_size.cy,
               dib->m_iScan
               );

            }
            else
            {

               get_graphics()->StretchBlt(x, y, (i32) cx, (i32) cy, dib->get_graphics(), 0, 0, dib->m_size.cx, dib->m_size.cy);

            }

            y += (i32) cy;

         }

         m_emipmap = mipmap_isotropic;

      }
      else
      {

         double newcx = cx * 2.0 - 1.0;

         double newcy = cy * 2.0 - 1.0;

         if (!create((i32)newcx, (i32) newcy))
         {

            throw resource_exception(get_app());

         }

         int dx;

         int x = 0;

         int xPrevious;
         int yPrevious;
         int cxPrevious;
         int cyPrevious;

         xPrevious = 0;
         cxPrevious = dib->m_size.cx;
         ::draw2d::dib * pdib = dib;

         for (dx = (i32) cx; dx > 0; x += dx, dx /= 2)
         {

            yPrevious = 0;
            cyPrevious = dib->m_size.cy;

            for (int y = 0, dy = (i32) cy; dy > 0; y += dy, dy /= 2)
            {

               if (::multithreading::priority() == ::multithreading::priority_idle)
               {

                  map();

                  C2PassScale < CBlackmanFilter > scale(1.0);

                  scale.Scale(
                  &m_pcolorref[x + y * m_iScan / sizeof(COLORREF)],
                  dx,
                  dy,
                  m_iScan,
                  &pdib->m_pcolorref[xPrevious + yPrevious * pdib->m_iScan / sizeof(COLORREF)],
                  cxPrevious,
                  cyPrevious,
                  pdib->m_iScan
                  );

                  yPrevious = y;
                  cyPrevious = dy;
                  pdib = this;

               }
               else
               {

                  get_graphics()->StretchBlt(x, y, dx, dy, dib->get_graphics(), 0, 0, dib->m_size.cx, dib->m_size.cy);

               }

            }

            xPrevious = x;
            cxPrevious = dx;

         }

         m_emipmap = mipmap_anisotropic;

      }

      m_size = dib->m_size;

   }


   void dib::SetViewportOrg(point pt)
   {

      m_pt = pt;

      if (!m_bMapped)
      {

         get_graphics()->SetViewportOrg(pt);

      }

   }

   void dib::create_helper_map()
   {

      index a;

      a = (index)(area());

      index jNextBoundary;
      index jStart;
      byte * pdata = (byte *)m_pcolorref;

      if (pdata == NULL)
      {

         return;

      }

      index w = m_size.cx;
      index sw = w * sizeof(COLORREF);

      {

         m_memoryMap.allocate(a * 2);
         m_memoryMap.set(0);
         byte * opacity = m_memoryMap.get_data();

         for (index i = 0; i < m_size.cy; i++)
         {

            for (index j = 0; j < sw; j += 4)
            {

               if (pdata[i*m_iScan + j + 3] == 255)
               {
                  jStart = j;
                  jNextBoundary = MIN(j + 960, sw);
                  for (j += 4; j < jNextBoundary; j += 4)
                  {
                     if (pdata[i*m_iScan + j + 3] != 255)
                     {
                        break;
                     }
                  }

                  j-=4;

                  index c = (j - jStart) >> 2;

                  index m = j >> 2;

                  byte n = 1;

                  while (c >= 0)
                  {

                     opacity[(int)(i * w + m)] = n;

                     m--;

                     n++;

                     c--;

                  }

               }

            }

         }

      }

      {

         byte * transparency = m_memoryMap.get_data() + a;

         for (index i = 0; i < m_size.cy; i++)
         {

            for (index j = 0; j < sw; j += 4)
            {

               if (pdata[i * m_iScan + j + 3] == 0)
               {

                  jStart = j;

                  jNextBoundary = MIN(j + 960, sw);

                  for (j += 4; j < jNextBoundary; j += 4)
                  {

                     if (pdata[i * m_iScan + j + 3] != 0)
                     {

                        break;

                     }

                  }

                  j -= 4;

                  index c = (j - jStart) >> 2;

                  index m = j >> 2;

                  byte n = 1;

                  while (c >= 0)
                  {

                     transparency[(index)(i * w + m)] = n;

                     m--;

                     n++;

                     c--;

                  }

               }

            }

         }

      }

   }


   void dib::set_font_factor(double dFactor)
   {

      m_dFontFactor = dFactor;

      if (!m_bMapped)
      {

         get_graphics()->m_dFontFactor = dFactor;

      }

   }

   void dib::set_alpha_mode(e_alpha_mode emode)
   {

      m_ealphamode = emode;

      if (!m_bMapped)
      {

         get_graphics()->set_alpha_mode(emode);

      }

   }


   i32 dib::cos(i32 i, i32 iAngle)
   {

      UNREFERENCED_PARAMETER(i);
      UNREFERENCED_PARAMETER(iAngle);

      ::exception::throw_interface_only(get_app());

      return 0;

   }


   i32 dib::sin(i32 i, i32 iAngle)
   {

      UNREFERENCED_PARAMETER(i);
      UNREFERENCED_PARAMETER(iAngle);

      ::exception::throw_interface_only(get_app());

      return 0;

   }


   i32 dib::cos10(i32 i, i32 iAngle)
   {

      UNREFERENCED_PARAMETER(i);
      UNREFERENCED_PARAMETER(iAngle);

      ::exception::throw_interface_only(get_app());

      return 0;

   }


   i32 dib::sin10(i32 i, i32 iAngle)
   {

      UNREFERENCED_PARAMETER(i);
      UNREFERENCED_PARAMETER(iAngle);

      ::exception::throw_interface_only(get_app());

      return 0;

   }

   /*   i32 dib::m_size.cx
      {
         ::exception::throw_interface_only(get_app());
      }

      i32 dib::m_size.cy
      {
         ::exception::throw_interface_only(get_app());
      }

      int64_t dib::area()
      {
         return ((int64_t) m_size.cx) * ((int64_t)m_size.cy);
      }

      size dib::m_size
      {
         return size64(m_size.cx, m_size.cy);
      }*/


   double dib::pi() const
   {

      return atan(1.0)*4.0;

   }


   void dib::fill_channel(i32 intensity, visual::rgba::echannel echannel)
   {
      map();
      i32 offset = ((i32)echannel) % 4;
      int64_t size = scan_area();

      COLORREF * pcr = (COLORREF *) &((byte *)m_pcolorref)[offset];

      BYTE * pb;

      int64_t iSize32 = size / 32;
      i32 i;
      for (i = 0; i < iSize32; i += 32)
      {
         pb = (byte *)&pcr[i];
         pb[0 * 4] = (byte)intensity;
         pb[1 * 4] = (byte)intensity;
         pb[2 * 4] = (byte)intensity;
         pb[3 * 4] = (byte)intensity;
         pb[4 * 4] = (byte)intensity;
         pb[5 * 4] = (byte)intensity;
         pb[6 * 4] = (byte)intensity;
         pb[7 * 4] = (byte)intensity;
         pb[8 * 4] = (byte)intensity;
         pb[9 * 4] = (byte)intensity;
         pb[10 * 4] = (byte)intensity;
         pb[11 * 4] = (byte)intensity;
         pb[12 * 4] = (byte)intensity;
         pb[13 * 4] = (byte)intensity;
         pb[14 * 4] = (byte)intensity;
         pb[15 * 4] = (byte)intensity;
         pb[16 * 4] = (byte)intensity;
         pb[17 * 4] = (byte)intensity;
         pb[18 * 4] = (byte)intensity;
         pb[19 * 4] = (byte)intensity;
         pb[20 * 4] = (byte)intensity;
         pb[21 * 4] = (byte)intensity;
         pb[22 * 4] = (byte)intensity;
         pb[23 * 4] = (byte)intensity;
         pb[24 * 4] = (byte)intensity;
         pb[25 * 4] = (byte)intensity;
         pb[26 * 4] = (byte)intensity;
         pb[27 * 4] = (byte)intensity;
         pb[28 * 4] = (byte)intensity;
         pb[29 * 4] = (byte)intensity;
         pb[30 * 4] = (byte)intensity;
         pb[31 * 4] = (byte)intensity;
      }

      for (i = 0; i < size; i++)
      {
         *((BYTE *)&pcr[i]) = (byte)intensity;
      }
   }

   void dib::white_fill_channel(i32 intensity, visual::rgba::echannel echannel)
   {
      map();
      i32 offset = ((i32)echannel) % 4;
      int64_t size = scan_area();

      COLORREF * pcr = (COLORREF *) &((byte *)m_pcolorref)[offset];

      //      BYTE * pb;

      int64_t iSize32 = size / 32;
      i32 i;
      //      for (i=0; i < iSize32; i+=32 )
      //      {
      //         pb = (byte *) &pcr[i];
      //         pb[0 * 4] = (byte) intensity;
      //         pb[1 * 4] = (byte) intensity;
      //         pb[2 * 4] = (byte) intensity;
      //         pb[3 * 4] = (byte) intensity;
      //         pb[4 * 4] = (byte) intensity;
      //         pb[5 * 4] = (byte) intensity;
      //         pb[6 * 4] = (byte) intensity;
      //         pb[7 * 4] = (byte) intensity;
      //         pb[8 * 4] = (byte) intensity;
      //         pb[9 * 4] = (byte) intensity;
      //         pb[10 * 4] = (byte) intensity;
      //         pb[11 * 4] = (byte) intensity;
      //         pb[12 * 4] = (byte) intensity;
      //         pb[13 * 4] = (byte) intensity;
      //         pb[14 * 4] = (byte) intensity;
      //         pb[15 * 4] = (byte) intensity;
      //         pb[16 * 4] = (byte) intensity;
      //         pb[17 * 4] = (byte) intensity;
      //         pb[18 * 4] = (byte) intensity;
      //         pb[19 * 4] = (byte) intensity;
      //         pb[20 * 4] = (byte) intensity;
      //         pb[21 * 4] = (byte) intensity;
      //         pb[22 * 4] = (byte) intensity;
      //         pb[23 * 4] = (byte) intensity;
      //         pb[24 * 4] = (byte) intensity;
      //         pb[25 * 4] = (byte) intensity;
      //         pb[26 * 4] = (byte) intensity;
      //         pb[27 * 4] = (byte) intensity;
      //         pb[28 * 4] = (byte) intensity;
      //         pb[29 * 4] = (byte) intensity;
      //         pb[30 * 4] = (byte) intensity;
      //         pb[31 * 4] = (byte) intensity;
      //      }


      for (i = 0; i < size; i++)
      {

         *((BYTE *)&pcr) = (byte)(((int)intensity * (int)*((BYTE *)&pcr)) / 255);

         pcr++;

      }

   }



   void dib::channel_copy(visual::rgba::echannel echannelDst, visual::rgba::echannel echannelSrc)
   {

      map();

      echannelDst = (visual::rgba::echannel) (((i32)echannelDst) % 4);
      echannelSrc = (visual::rgba::echannel) (((i32)echannelSrc) % 4);

      if (echannelDst == echannelSrc)
         return;

      byte * pdataDst = (byte *)get_data() + ((i32)echannelDst);

      byte * pdataSrc = (byte *)get_data() + ((i32)echannelSrc);

      for (i32 y = 0; y < m_size.cy; y++)
      {

         byte * pdst = &pdataDst[m_iScan * y];

         byte * psrc = &pdataSrc[m_iScan * y];

         for (i32 x = 0; x < m_size.cx; x++)
         {

            *pdst = *psrc;

            pdst += 4;

            psrc += 4;

         }
      }
   }

   void dib::channel_copy(visual::rgba::echannel echannelDst, visual::rgba::echannel echannelSrc, draw2d::dib * pdib)
   {

      if (m_size != pdib->size())
         return;

      map();

      if (m_pcolorref == NULL)
         return;

      pdib->map();

      if (pdib->m_pcolorref == NULL)
         return;

      echannelDst = (visual::rgba::echannel) (((i32)echannelDst) % 4);
      echannelSrc = (visual::rgba::echannel) (((i32)echannelSrc) % 4);

      byte * pdataDst = (byte *)get_data() + ((i32)echannelDst);

      byte * pdataSrc = (byte *)pdib->get_data() + ((i32)echannelSrc);

      for (i32 y = 0; y < m_size.cy; y++)
      {

         byte * pdst = &pdataDst[m_iScan * y];

         byte * psrc = &pdataSrc[pdib->m_iScan * y];

         for (i32 x = 0; x < m_size.cx; x++)
         {

            *pdst = *psrc;

            pdst += 4;

            psrc += 4;

         }
      }
   }


   void dib::io(stream & serialize)
   {

      if (m_psetObject != NULL)
      {

         if (m_psetObject->has_property("read_only_link")
               || m_psetObject->has_property("link"))
         {


            serialize.stream_link(*this);


            return;

         }

      }

      if(serialize.is_storing())
      {

         serialize((i32&)m_size.cx);

         serialize((i32&)m_size.cy);

         serialize((i32&)m_sizeAlloc.cx);

         serialize((i32&)m_sizeAlloc.cy);

         serialize((i32&)m_iScan);

         serialize((i32&)m_emipmap);

         if (area() <= 0)
         {

            return;

         }


         map();

         serialize.write(m_pcolorref, m_iScan * m_size.cy);

      }
      else
      {

         i32 width;
         serialize((i32&)width);
         if (serialize.fail())
            return;

         i32 height;
         serialize((i32&)height);
         if (serialize.fail())
            return;

         i32 widthAlloc;
         serialize((i32&)widthAlloc);
         if (serialize.fail())
            return;

         i32 heightAlloc;
         serialize((i32&)heightAlloc);
         if (serialize.fail())
            return;

         i32 iScan;
         serialize((i32&)iScan);
         if (serialize.fail())
            return;

         i32 iMipmap;
         serialize((i32&)iMipmap);
         if (serialize.fail())
            return;

         if (width <= 0)
         {
            serialize.setstate(::file::badbit);
            return;
         }
         if (height <= 0)
         {
            serialize.setstate(::file::badbit);
            return;
         }
         if (widthAlloc <= 0)
         {
            serialize.setstate(::file::badbit);
            return;
         }
         if (heightAlloc <= 0)
         {
            serialize.setstate(::file::badbit);
            return;
         }
         if (iScan <= 0)
         {
            serialize.setstate(::file::badbit);
            return;
         }
         if (widthAlloc < width)
         {
            serialize.setstate(::file::badbit);
            return;
         }
         if (heightAlloc < height)
         {
            serialize.setstate(::file::badbit);
            return;
         }
         if (iScan < widthAlloc / sizeof(COLORREF))
         {
            serialize.setstate(::file::badbit);
            return;
         }
         if (!create(widthAlloc, heightAlloc))
            _throw(simple_exception(get_app(), "dib::read"));
         map();
         if (iScan == m_iScan)
         {
            serialize.read(get_data(), iScan * m_size.cy);
         }
         else
         {
            memory mem;
            mem.allocate(iScan * m_size.cy);
            size_t s = serialize.read(mem.get_data(), iScan * m_size.cy);
            if ((i32) s / iScan < height)
            {
               serialize.setstate(::file::badbit);
               return;
            }
            ::draw2d::copy_colorref(width, height, get_data(), m_iScan, (COLORREF *)mem.get_data(), iScan);

         }

         m_size.cx = width;
         m_size.cy = height;

      }

   }




   void dib::tint(::draw2d::dib * pdib, i32 R, i32 G, i32 B)
   {

      if (!create(pdib->m_size))
      {

         return;

      }

      map();

      BYTE *src = (BYTE*)pdib->m_pcolorref;
      BYTE *dst = (BYTE*)m_pcolorref;
      int64_t size = scan_area();

      BYTE uchB = (byte)R;
      BYTE uchG = (byte)G;
      BYTE uchR = (byte)B;

      //      i32 i = 0;;


      //while (size > 16)
      //{
      //   //dst[3] = dst[i];
      //   dst[0] = (uchB * src[3]) >> 8;
      //   dst[1] = (uchG * src[3]) >> 8;
      //   dst[2] = (uchR * src[3]) >> 8;
      //   dst[3] = src[3];

      //   dst[4] = (uchB * src[7]) >> 8;
      //   dst[5] = (uchG * src[7]) >> 8;
      //   dst[6] = (uchR * src[7]) >> 8;
      //   dst[7] = src[7];

      //   dst[8] = (uchB * src[11]) >> 8;
      //   dst[9] = (uchG * src[11]) >> 8;
      //   dst[10] = (uchR * src[11]) >> 8;
      //   dst[11] = src[11];

      //   dst[12] = (uchB * src[15]) >> 8;
      //   dst[13] = (uchG * src[15]) >> 8;
      //   dst[14] = (uchR * src[15]) >> 8;
      //   dst[15] = src[15];

      //   dst[16] = (uchB * src[19]) >> 8;
      //   dst[17] = (uchG * src[19]) >> 8;
      //   dst[18] = (uchR * src[19]) >> 8;
      //   dst[19] = src[19];

      //   dst[20] = (uchB * src[23]) >> 8;
      //   dst[21] = (uchG * src[23]) >> 8;
      //   dst[22] = (uchR * src[23]) >> 8;
      //   dst[23] = src[23];

      //   dst[24] = (uchB * src[27]) >> 8;
      //   dst[25] = (uchG * src[27]) >> 8;
      //   dst[26] = (uchR * src[27]) >> 8;
      //   dst[27] = src[27];

      //   dst[28] = (uchB * src[31]) >> 8;
      //   dst[29] = (uchG * src[31]) >> 8;
      //   dst[30] = (uchR * src[31]) >> 8;
      //   dst[31] = src[31];

      //   dst[32] = (uchB * src[35]) >> 8;
      //   dst[33] = (uchG * src[35]) >> 8;
      //   dst[34] = (uchR * src[35]) >> 8;
      //   dst[35] = src[35];

      //   dst[36] = (uchB * src[39]) >> 8;
      //   dst[37] = (uchG * src[39]) >> 8;
      //   dst[38] = (uchR * src[39]) >> 8;
      //   dst[39] = src[39];

      //   dst[40] = (uchB * src[43]) >> 8;
      //   dst[41] = (uchG * src[43]) >> 8;
      //   dst[42] = (uchR * src[43]) >> 8;
      //   dst[43] = src[43];

      //   dst[44] = (uchB * src[47]) >> 8;
      //   dst[45] = (uchG * src[47]) >> 8;
      //   dst[46] = (uchR * src[47]) >> 8;
      //   dst[47] = src[47];

      //   dst[48] = (uchB * src[51]) >> 8;
      //   dst[49] = (uchG * src[51]) >> 8;
      //   dst[50] = (uchR * src[51]) >> 8;
      //   dst[51] = src[51];

      //   dst[52] = (uchB * src[55]) >> 8;
      //   dst[53] = (uchG * src[55]) >> 8;
      //   dst[54] = (uchR * src[55]) >> 8;
      //   dst[55] = src[55];

      //   dst[56] = (uchB * src[59]) >> 8;
      //   dst[57] = (uchG * src[59]) >> 8;
      //   dst[58] = (uchR * src[59]) >> 8;
      //   dst[59] = src[59];

      //   dst[60] = (uchB * src[63]) >> 8;
      //   dst[61] = (uchG * src[63]) >> 8;
      //   dst[62] = (uchR * src[63]) >> 8;
      //   dst[63] = src[63];

      //   dst += 4 * 16;
      //   src += 4 * 16;
      //   size -= 16;
      //}
      //byte tableR[256];
      //byte tableG[256];
      //byte tableB[256];
      //for (index i = 0; i < 255; i++)
      //{
      //   tableR[i] = (uchR * i) >> 8;
      //   tableG[i] = (uchG * i) >> 8;
      //   tableB[i] = (uchB * i) >> 8;
      //}
      //while (size > 0)
      //{
      //   dst[0] = tableR[src[3]];
      //   dst[1] = tableG[src[3]];
      //   dst[2] = tableB[src[3]];
      //   dst += 4;
      //   src += 4;
      //   size--;
      //}

      COLORREF o = ARGB(255, uchR, uchG, uchB);

      while (size > 0)
      {

         byte bA = src[3];

         if (bA == 0)
         {

            *((COLORREF *)dst) = 0;

         }
         else if (bA == 255)
         {

            *((COLORREF *)dst) = o;

         }
         else
         {
            dst[0] = (uchB * bA) >> 8;
            dst[1] = (uchG * bA) >> 8;
            dst[2] = (uchR * bA) >> 8;
            dst[3] = bA;
         }

         dst += 4;
         src += 4;
         size--;
      }

   }

   void dib::saturation(double dRate)
   {

      map();

      BYTE *dst = (BYTE*)m_pcolorref;
      int64_t size = scan_area();

      int iDiv = 255 * 255;
      int iMul = (int)(dRate * (double)iDiv);

      //      i32 i = 0;;

      while (size > 0)
      {
         //dst[3] = dst[i];
         int iMax = MAX(MAX(dst[0], dst[1]), dst[2]);
         int iMin = MIN(MIN(dst[0], dst[1]), dst[2]);
         int iMid = (iMax + iMin) / 2;
         dst[0] = ((dst[0] - iMid) * iMul / iDiv) + iMid;
         dst[1] = ((dst[1] - iMid) * iMul / iDiv) + iMid;
         dst[2] = ((dst[2] - iMid) * iMul / iDiv) + iMid;
         dst += 4;
         size--;
      }

   }



   void dib::set_rgb_pre_alpha(i32 R, i32 G, i32 B, i32 A)
   {

      map();

      BYTE *dst = (BYTE*)m_pcolorref;
      int64_t size = scan_area();

      BYTE uchB = (byte)R;
      BYTE uchG = (byte)G;
      BYTE uchR = (byte)B;

      //      i32 i = 0;;

      while (size > 0)
      {
         //dst[3] = dst[i];
         dst[0] = ((int)uchB * (int)dst[3] * A) >> 16;
         dst[1] = ((int)uchG * (int)dst[3] * A) >> 16;
         dst[2] = ((int)uchR * (int)dst[3] * A) >> 16;
         dst[3] = ((int)dst[3] * A) >> 8;
         dst += 4;
         size--;
      }

      while (size > 16)
      {
         //dst[3] = dst[i];
         dst[0] = (uchB * dst[3] * A) >> 16;
         dst[1] = (uchG * dst[3] * A) >> 16;
         dst[2] = (uchR * dst[3] * A) >> 16;
         dst[3] = (dst[3] * A) >> 8;

         dst[4] = (uchB * dst[7] * A) >> 16;
         dst[5] = (uchG * dst[7] * A) >> 16;
         dst[6] = (uchR * dst[7] * A) >> 16;
         dst[7] = (dst[7] * A) >> 8;

         dst[8] = (uchB * dst[11] * A) >> 16;
         dst[9] = (uchG * dst[11] * A) >> 16;
         dst[10] = (uchR * dst[11] * A) >> 16;
         dst[11] = (dst[11] * A) >> 8;

         dst[12] = (uchB * dst[15] * A) >> 16;
         dst[13] = (uchG * dst[15] * A) >> 16;
         dst[14] = (uchR * dst[15] * A) >> 16;
         dst[15] = (dst[15] * A) >> 8;

         dst[16] = (uchB * dst[19] * A) >> 16;
         dst[17] = (uchG * dst[19] * A) >> 16;
         dst[18] = (uchR * dst[19] * A) >> 16;
         dst[19] = (dst[19] * A) >> 8;

         dst[20] = (uchB * dst[23] * A) >> 16;
         dst[21] = (uchG * dst[23] * A) >> 16;
         dst[22] = (uchR * dst[23] * A) >> 16;
         dst[23] = (dst[23] * A) >> 8;

         dst[24] = (uchB * dst[27] * A) >> 16;
         dst[25] = (uchG * dst[27] * A) >> 16;
         dst[26] = (uchR * dst[27] * A) >> 16;
         dst[27] = (dst[27] * A) >> 8;

         dst[28] = (uchB * dst[31] * A) >> 16;
         dst[29] = (uchG * dst[31] * A) >> 16;
         dst[30] = (uchR * dst[31] * A) >> 16;
         dst[31] = (dst[31] * A) >> 8;

         dst[32] = (uchB * dst[35] * A) >> 16;
         dst[33] = (uchG * dst[35] * A) >> 16;
         dst[34] = (uchR * dst[35] * A) >> 16;
         dst[35] = (dst[35] * A) >> 8;

         dst[36] = (uchB * dst[39] * A) >> 16;
         dst[37] = (uchG * dst[39] * A) >> 16;
         dst[38] = (uchR * dst[39] * A) >> 16;
         dst[39] = (dst[39] * A) >> 8;

         dst[40] = (uchB * dst[43] * A) >> 16;
         dst[41] = (uchG * dst[43] * A) >> 16;
         dst[42] = (uchR * dst[43] * A) >> 16;
         dst[43] = (dst[43] * A) >> 8;

         dst[44] = (uchB * dst[47] * A) >> 16;
         dst[45] = (uchG * dst[47] * A) >> 16;
         dst[46] = (uchR * dst[47] * A) >> 16;
         dst[47] = (dst[47] * A) >> 8;

         dst[48] = (uchB * dst[51] * A) >> 16;
         dst[49] = (uchG * dst[51] * A) >> 16;
         dst[50] = (uchR * dst[51] * A) >> 16;
         dst[51] = (dst[51] * A) >> 8;

         dst[52] = (uchB * dst[55] * A) >> 16;
         dst[53] = (uchG * dst[55] * A) >> 16;
         dst[54] = (uchR * dst[55] * A) >> 16;
         dst[55] = (dst[55] * A) >> 8;

         dst[56] = (uchB * dst[59] * A) >> 16;
         dst[57] = (uchG * dst[59] * A) >> 16;
         dst[58] = (uchR * dst[59] * A) >> 16;
         dst[59] = (dst[59] * A) >> 8;

         dst[60] = (uchB * dst[63] * A) >> 16;
         dst[61] = (uchG * dst[63] * A) >> 16;
         dst[62] = (uchR * dst[63] * A) >> 16;
         dst[63] = (dst[63] * A) >> 8;

         dst += 4 * 16;
         size -= 16;
      }

   }

   void dib::set_rgb(COLORREF cr)
   {

      set_rgb(argb_get_r_value(cr), argb_get_g_value(cr), argb_get_b_value(cr));


   }

   void dib::set_rgb(i32 R, i32 G, i32 B)
   {

      set(R, G, B);

      return;

      //      map();
      //
      //      BYTE *dst=(BYTE*)m_pcolorref;
      //      int64_t size = scan_area();
      //
      //      BYTE uchB = (byte) R;
      //      BYTE uchG = (byte) G;
      //      BYTE uchR = (byte) B;
      //
      ////      i32 i = 0;;
      //
      //
      //      while ( size-- )
      //      {
      //         //dst[3] = dst[i];
      //         dst[0] = uchB;
      //         dst[1] = uchG;
      //         dst[2] = uchR;
      //         dst+=4;
      //      }
      //
      //
      //      /*      COLORREF color = RGB(B, G, R);
      //            int64_t size = area();
      //
      //            COLORREF * pcr;
      //
      //            int64_t iSize32 = size / 32;
      //            i32 i;
      //            for (i = 0; i < iSize32; i += 32)
      //            {
      //               pcr = &m_pcolorref[i];
      //               pcr[0] = color;
      //               pcr[1] = color;
      //               pcr[2] = color;
      //               pcr[3] = color;
      //               pcr[4] = color;
      //               pcr[5] = color;
      //               pcr[6] = color;
      //               pcr[7] = color;
      //               pcr[8] = color;
      //               pcr[9] = color;
      //               pcr[10] = color;
      //               pcr[11] = color;
      //               pcr[12] = color;
      //               pcr[13] = color;
      //               pcr[14] = color;
      //               pcr[15] = color;
      //               pcr[16] = color;
      //               pcr[17] = color;
      //               pcr[18] = color;
      //               pcr[19] = color;
      //               pcr[20] = color;
      //               pcr[21] = color;
      //               pcr[22] = color;
      //               pcr[23] = color;
      //               pcr[24] = color;
      //               pcr[25] = color;
      //               pcr[26] = color;
      //               pcr[27] = color;
      //               pcr[28] = color;
      //               pcr[29] = color;
      //               pcr[30] = color;
      //               pcr[31] = color;
      //            }
      //
      //            for (i = 0; i<size; i++)
      //            {
      //               m_pcolorref[i] = color;
      //            }*/
      //
   }

   bool dib::rgb_from(::draw2d::dib * pdib)
   {
      if (!create(pdib->size()))
         return false;
      try
      {
         byte * puchSrc = (byte *)get_data();
         byte * puchDst = (byte *)pdib->get_data();
         int64_t iArea = pdib->scan_area();
         while (iArea > 0)
         {
            *puchDst++ = *puchSrc++;
            *puchDst++ = *puchSrc++;
            *puchDst++ = *puchSrc++;
            puchDst++;
            puchSrc++;
            iArea--;
         }
      }
      catch (...)
      {
         return false;
      }
      return true;
   }


   bool dib::pixelate(i32 iSize)
   {

      if (iSize <= 1)
         return true;



      i32 w = m_size.cx;
      i32 h = m_size.cy;
      i32 s = m_iScan / sizeof(COLORREF);

      i32 xCount = w / iSize;
      i32 yCount = h / iSize;



      i32 iDiv;
      i32 iDiv2;

      i32 a;
      i32 r;
      i32 g;
      i32 b;
      i32 a2;
      i32 r2;
      i32 g2;
      i32 b2;
      //bool bFirst;
      COLORREF * pdata = get_data();
      i32 x1;
      i32 y1;
      for (i32 x = 0; x < xCount; x++)
      {
         x1 = x * iSize;
         for (i32 y = 0; y < yCount; y++)
         {
            y1 = y * iSize;
            a = 0;
            r = 0;
            g = 0;
            b = 0;
            a2 = 0;
            r2 = 0;
            g2 = 0;
            b2 = 0;
            iDiv = 0;
            iDiv2 = 0;
            //bFirst = true;
            for (i32 i = 0; i < iSize; i++)
            {
               for (i32 j = 0; j < iSize; j++)
               {
                  COLORREF cr = pdata[x1 + i + (y1 + j) * s];
                  a += argb_get_a_value(cr);
                  r += argb_get_r_value(cr);
                  g += argb_get_g_value(cr);
                  b += argb_get_b_value(cr);
                  iDiv++;
                  if (iDiv >= 64)
                  {
                     a2 = (a2 * iDiv2 + a / iDiv) / (iDiv2 + 1);
                     r2 = (r2 * iDiv2 + r / iDiv) / (iDiv2 + 1);
                     g2 = (g2 * iDiv2 + g / iDiv) / (iDiv2 + 1);
                     b2 = (b2 * iDiv2 + b / iDiv) / (iDiv2 + 1);
                     a = 0;
                     r = 0;
                     g = 0;
                     b = 0;
                     iDiv = 0;
                     iDiv2++;
                  }
               }
            }
            if (iDiv > 0)
            {
               a2 = (a2 * iDiv2 + a / iDiv) / (iDiv2 + 1);
               r2 = (r2 * iDiv2 + r / iDiv) / (iDiv2 + 1);
               g2 = (g2 * iDiv2 + g / iDiv) / (iDiv2 + 1);
               b2 = (b2 * iDiv2 + b / iDiv) / (iDiv2 + 1);
            }
            COLORREF cr = ARGB(a2, r2, g2, b2);
            for (i32 i = 0; i < iSize; i++)
            {
               for (i32 j = 0; j < iSize; j++)
               {
                  pdata[x1 + i + (y1 + j) * s] = cr;
               }
            }
         }

      }


      if (w % iSize != 0)
      {
         i32 x = xCount;
         i32 x1 = x * iSize;
         i32 iMax = w - xCount * iSize;
         for (i32 y = 0; y < yCount; y++)
         {
            y1 = y * iSize;
            a = 0;
            r = 0;
            g = 0;
            b = 0;
            a2 = 0;
            r2 = 0;
            g2 = 0;
            b2 = 0;
            iDiv = 0;
            iDiv2 = 0;
            //bFirst = true;
            for (i32 i = 0; i < iMax; i++)
            {
               for (i32 j = 0; j < iSize; j++)
               {
                  COLORREF cr = pdata[x1 + i + (y1 + j) * w];
                  a += argb_get_a_value(cr);
                  r += argb_get_r_value(cr);
                  g += argb_get_g_value(cr);
                  b += argb_get_b_value(cr);
                  iDiv++;
                  if (iDiv >= 64)
                  {
                     a2 = (a2 * iDiv2 + a / iDiv) / (iDiv2 + 1);
                     r2 = (r2 * iDiv2 + r / iDiv) / (iDiv2 + 1);
                     g2 = (g2 * iDiv2 + g / iDiv) / (iDiv2 + 1);
                     b2 = (b2 * iDiv2 + b / iDiv) / (iDiv2 + 1);
                     a = 0;
                     r = 0;
                     g = 0;
                     b = 0;
                     iDiv = 0;
                     iDiv2++;
                  }
               }
            }
            if (iDiv > 0)
            {
               a2 = (a2 * iDiv2 + a / iDiv) / (iDiv2 + 1);
               r2 = (r2 * iDiv2 + r / iDiv) / (iDiv2 + 1);
               g2 = (g2 * iDiv2 + g / iDiv) / (iDiv2 + 1);
               b2 = (b2 * iDiv2 + b / iDiv) / (iDiv2 + 1);
            }
            COLORREF cr = ARGB(a2, r2, g2, b2);
            for (i32 i = 0; i < iMax; i++)
            {
               for (i32 j = 0; j < iSize; j++)
               {
                  pdata[x1 + i + (y1 + j) * w] = cr;
               }
            }
         }

      }

      if (h % iSize != 0)
      {
         i32 y = yCount;
         i32 y1 = y * iSize;
         i32 jMax = h - yCount * iSize;
         for (i32 x = 0; x < xCount; x++)
         {
            x1 = x * iSize;
            a = 0;
            r = 0;
            g = 0;
            b = 0;
            a2 = 0;
            r2 = 0;
            g2 = 0;
            b2 = 0;
            iDiv = 0;
            iDiv2 = 0;
            //bFirst = true;
            for (i32 i = 0; i < iSize; i++)
            {
               for (i32 j = 0; j < jMax; j++)
               {
                  COLORREF cr = pdata[x1 + i + (y1 + j) * w];
                  a += argb_get_a_value(cr);
                  r += argb_get_r_value(cr);
                  g += argb_get_g_value(cr);
                  b += argb_get_b_value(cr);
                  iDiv++;
                  if (iDiv >= 64)
                  {
                     a2 = (a2 * iDiv2 + a / iDiv) / (iDiv2 + 1);
                     r2 = (r2 * iDiv2 + r / iDiv) / (iDiv2 + 1);
                     g2 = (g2 * iDiv2 + g / iDiv) / (iDiv2 + 1);
                     b2 = (b2 * iDiv2 + b / iDiv) / (iDiv2 + 1);
                     a = 0;
                     r = 0;
                     g = 0;
                     b = 0;
                     iDiv = 0;
                     iDiv2++;
                  }
               }
            }
            if (iDiv > 0)
            {
               a2 = (a2 * iDiv2 + a / iDiv) / (iDiv2 + 1);
               r2 = (r2 * iDiv2 + r / iDiv) / (iDiv2 + 1);
               g2 = (g2 * iDiv2 + g / iDiv) / (iDiv2 + 1);
               b2 = (b2 * iDiv2 + b / iDiv) / (iDiv2 + 1);
            }
            COLORREF cr = ARGB(a2, r2, g2, b2);
            for (i32 i = 0; i < iSize; i++)
            {
               for (i32 j = 0; j < jMax; j++)
               {
                  pdata[x1 + i + (y1 + j) * w] = cr;
               }
            }
         }

      }

      if (w % iSize != 0)
      {
         i32 x = xCount;
         i32 x1 = x * iSize;
         i32 iMax = w - xCount * iSize;
         i32 y = yCount;
         i32 y1 = y * iSize;
         i32 jMax = h - yCount * iSize;
         x1 = x * iSize;
         a = 0;
         r = 0;
         g = 0;
         b = 0;
         a2 = 0;
         r2 = 0;
         g2 = 0;
         b2 = 0;
         iDiv = 0;
         iDiv2 = 0;
         //bFirst = true;
         for (i32 i = 0; i < iMax; i++)
         {
            for (i32 j = 0; j < jMax; j++)
            {
               COLORREF cr = pdata[x1 + i + (y1 + j) * w];
               a += argb_get_a_value(cr);
               r += argb_get_r_value(cr);
               g += argb_get_g_value(cr);
               b += argb_get_b_value(cr);
               iDiv++;
               if (iDiv >= 64)
               {
                  a2 = (a2 * iDiv2 + a / iDiv) / (iDiv2 + 1);
                  r2 = (r2 * iDiv2 + r / iDiv) / (iDiv2 + 1);
                  g2 = (g2 * iDiv2 + g / iDiv) / (iDiv2 + 1);
                  b2 = (b2 * iDiv2 + b / iDiv) / (iDiv2 + 1);
                  a = 0;
                  r = 0;
                  g = 0;
                  b = 0;
                  iDiv = 0;
                  iDiv2++;
               }
            }
         }
         if (iDiv > 0)
         {
            a2 = (a2 * iDiv2 + a / iDiv) / (iDiv2 + 1);
            r2 = (r2 * iDiv2 + r / iDiv) / (iDiv2 + 1);
            g2 = (g2 * iDiv2 + g / iDiv) / (iDiv2 + 1);
            b2 = (b2 * iDiv2 + b / iDiv) / (iDiv2 + 1);
         }
         COLORREF cr = ARGB(a2, r2, g2, b2);
         for (i32 i = 0; i < iMax; i++)
         {
            for (i32 j = 0; j < jMax; j++)
            {
               pdata[x1 + i + (y1 + j) * w] = cr;
            }
         }
      }

      return true;

   }


   void dib::rate_rgb(int iMul, int iDiv)
   {
      map();
      try
      {
         byte * puch = (byte *)get_data();
         int64_t iArea = scan_area();
         while (iArea > 0)
         {
            puch[0] = MAX(0, MIN(255, puch[0] * iMul / iDiv));
            puch[1] = MAX(0, MIN(255, puch[1] * iMul / iDiv));
            puch[2] = MAX(0, MIN(255, puch[2] * iMul / iDiv));
            puch += 4;
            iArea--;
         }
      }
      catch (...)
      {
      }
   }


   void dib::map(bool bApplyAlphaTransform) const
   {

      ((dib *) this)->m_bMapped = true;

      UNREFERENCED_PARAMETER(bApplyAlphaTransform);

   }


   void dib::unmap() const
   {
      ((dib *) this)->m_bMapped = false;
   }


   void dib::set_mapped()
   {

      m_bMapped = false;

   }

   //
   //   bool dib::update_window(::aura::draw_interface * pwnd,::message::message * pobj,bool bTransferBuffer)
   //   {
   //
   //      UNREFERENCED_PARAMETER(pwnd);
   //      UNREFERENCED_PARAMETER(pobj);
   //
   //      // default implementation does nothing, dib should be now updated (before calling update interaction_impl)
   //      // and ready to be queried if post queried
   //
   ////      ::exception::throw_interface_only(get_app());
   //
   //
   //      return true;
   //
   //   }


   //bool dib::print_window(::aura::draw_interface * pwnd,::message::message * pobj)
   //{

   //   UNREFERENCED_PARAMETER(pwnd);
   //   UNREFERENCED_PARAMETER(pobj);

   //   ::exception::throw_interface_only(get_app());

   //   return false;

   //}



   void dib::gradient_fill(COLORREF clr1, COLORREF clr2, POINT pt1, POINT pt2)
   {

      double dx = pt2.x - pt1.x;

      double dy = pt1.y - pt2.y;

      if (dx == 0.0 && dy == 0.0)
      {
         Fill(
         byte_clip(argb_get_a_value(clr1) * 0.5 + argb_get_a_value(clr2) * 0.5),
         byte_clip(argb_get_r_value(clr1) * 0.5 + argb_get_r_value(clr2) * 0.5),
         byte_clip(argb_get_g_value(clr1) * 0.5 + argb_get_g_value(clr2) * 0.5),
         byte_clip(argb_get_b_value(clr1) * 0.5 + argb_get_b_value(clr2) * 0.5));
      }
      else if (dx == 0.0)
      {

         gradient_horizontal_fill(clr1, clr2, pt1.y, pt2.y);

      }
      else if (dy == 0.0)
      {

         gradient_vertical_fill(clr1, clr2, pt1.x, pt2.x);

      }
      else
      {

         //         int x1 = MIN(pt1.x, pt2.x);

         //       int x2 = MAX(pt1.x, pt2.x);

         //     int y1 = MIN(pt1.y, pt2.y);

         //   int y2 = MAX(pt1.y, pt2.y);

         //         int top = y1;
         //
         //       int left = x1;
         //
         //       int right = m_size.cx - x2;
         //
         //  int bottom = m_size.cy - y2;

         int dim = MAX(m_size.cx, m_size.cy);

         double angle = atan2(dy, dx);

         ::draw2d::dib_sp dib(allocer());

         if (fabs(dx) > fabs(dy))
         {

            double sin = ::sin(angle);

            dib->create((i32)(dim / sin), (i32)(dim / sin));

            dib->gradient_horizontal_fill(clr1, clr2, pt1.y, pt2.y);

            dib->rotate(this, -angle, 1.0);

         }
         else
         {

            double cos = ::cos(angle);

            dib->create((i32)(dim / cos), (i32)(dim / cos));

            dib->gradient_vertical_fill(clr1, clr2, pt1.x, pt2.x);

            dib->rotate(this, System.math().GetPi() - angle, 1.0);

         }

      }


   }

   void dib::gradient_horizontal_fill(COLORREF clr1, COLORREF clr2, int start, int end)
   {

      if (end < start)
      {
         ::sort::swap(&start, &end);
         ::sort::swap(&clr1, &clr2);
      }

      end = MIN(end, m_size.cy - 1);
      COLORREF clr = clr1;
      byte * pb = (byte *)m_pcolorref;
      COLORREF * pdata;
      int line = 0;
      for (; line < start; line++)
      {
         pdata = (COLORREF *)&pb[m_iScan * line];
         for (int row = 0; row < m_size.cx; row++)
         {
            *pdata = clr;
            pdata++;
         }
      }
      double d;
      for (; line < end; line++)
      {

         d = ((double)(line - start)) / ((double)(end - start));

         clr = ARGB(
               byte_clip(argb_get_a_value(clr1) * (1.0 - d) + argb_get_a_value(clr2) * d),
               byte_clip(argb_get_r_value(clr1) * (1.0 - d) + argb_get_r_value(clr2) * d),
               byte_clip(argb_get_g_value(clr1) * (1.0 - d) + argb_get_g_value(clr2) * d),
               byte_clip(argb_get_b_value(clr1) * (1.0 - d) + argb_get_b_value(clr2) * d));

         pdata = (COLORREF *)&pb[m_iScan * line];
         for (int row = 0; row < m_size.cx; row++)
         {
            *pdata = clr;
            pdata++;
         }
      }
      clr = clr2;
      for (; line < m_size.cy; line++)
      {
         pdata = (COLORREF *)&pb[m_iScan * line];
         for (int row = 0; row < m_size.cx; row++)
         {
            *pdata = clr;
            pdata++;
         }
      }
   }

   void dib::gradient_vertical_fill(COLORREF clr1, COLORREF clr2, int start, int end)
   {

      if (end < start)
      {
         ::sort::swap(&start, &end);
         ::sort::swap(&clr1, &clr2);
      }

      end = MIN(end, m_size.cx - 1);
      COLORREF clr = clr1;
      byte * pb = (byte *)m_pcolorref;
      COLORREF * pdata;
      int row = 0;
      for (; row < start; row++)
      {
         pdata = (COLORREF *)&pb[sizeof(COLORREF) * row];
         for (int line = 0; line < m_size.cy; line++)
         {
            *pdata = clr;
            pdata += m_iScan;
         }
      }
      double d;
      for (; row < end; row++)
      {

         d = ((double)(row - start)) / ((double)(end - start));

         clr = ARGB(
               byte_clip(argb_get_a_value(clr1) * (1.0 - d) + argb_get_a_value(clr2) * d),
               byte_clip(argb_get_r_value(clr1) * (1.0 - d) + argb_get_r_value(clr2) * d),
               byte_clip(argb_get_g_value(clr1) * (1.0 - d) + argb_get_g_value(clr2) * d),
               byte_clip(argb_get_b_value(clr1) * (1.0 - d) + argb_get_b_value(clr2) * d));

         pdata = (COLORREF *)&pb[sizeof(COLORREF) * row];
         for (int line = 0; line < m_size.cx; line++)
         {
            *pdata = clr;
            pdata += m_iScan;
         }
      }
      clr = clr2;
      for (; row < m_size.cx; row++)
      {
         pdata = (COLORREF *)&pb[sizeof(COLORREF) * row];
         for (int line = 0; line < m_size.cx; line++)
         {
            *pdata = clr;
            pdata += m_iScan;
         }
      }
   }

   void dib::gradient_horizontal_fill(COLORREF clr1, COLORREF clr2)
   {
      gradient_horizontal_fill(clr1, clr2, 0, m_size.cy - 1);
   }

   void dib::gradient_vertical_fill(COLORREF clr1, COLORREF clr2)
   {
      gradient_vertical_fill(clr1, clr2, 0, m_size.cx - 1);
   }


   void dib::static_initialize()
   {
      double dCos;
      double dSin;
      double d32 = (1U << 31);
      dPi = atan(1.0) * 4.0;;
      i32 i;
      for (i = 0; i < 360; i++)
      {
         dCos = ::cos(i / 180.0*dPi);
         dSin = ::sin(i / 180.0*dPi);
         Cosines[i] = float(dCos);
         Sines[i] = float(dSin);
         CosN[i] = (int64_t)(dCos * d32);
         SinN[i] = (int64_t)(dSin * d32);
      }
      d32 = (1U << 31);
      d32 *= 8;
      for (i = 0; i < 10; i++)
      {
         dCos = ::cos(i / 180.0*dPi);
         dSin = ::sin(i / 180.0*dPi);
         Cos10N[i] = (int64_t)(dCos * d32);
         Sin10N[i] = (int64_t)(dSin * d32);
      }

   }


   void dib::invert_rgb(LPCRECT lpcrect)
   {

      int s = m_iScan;

      int left;
      int right;
      int top;
      int bottom;

      if (lpcrect == NULL)
      {

         left = 0;

         right = m_size.cx;

         top = 0;

         bottom = m_size.cy;

      }
      else
      {

         left = MIN(MAX(0, lpcrect->left), m_size.cx);

         right = MIN(MAX(0, lpcrect->right), m_size.cx);

         top = MIN(MAX(0, lpcrect->top), m_size.cy);

         bottom = MIN(MAX(0, lpcrect->bottom), m_size.cy);

      }

      int start = left * 4 + top * s;

      for (int y = top; y < bottom; y++, start += s)
      {

         byte * pb = &((byte *)m_pcolorref)[start];

         for (int x = left; x < right; x++, pb += 4)
         {

            pb[0] = ~pb[0];
            pb[1] = ~pb[1];
            pb[2] = ~pb[2];

         }

      }


   }


   bool dib::create_circle(::draw2d::dib * pdib, int diameter)
   {

      if (!create(diameter, diameter))
      {

         return false;

      }

      if (pdib == NULL || pdib->area() <= 0)
      {

         Fill(255, 0, 0, 0);

      }
      else
      {

         get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

         get_graphics()->StretchBlt(0, 0, diameter, diameter, pdib->get_graphics(), 0, 0, pdib->m_size.cx, pdib->m_size.cy, SRCCOPY);

      }

      ::size s = m_size;

      COLORREF * pcolorref = m_pcolorref;

      int iScan = m_iScan;

      int wscan = iScan / sizeof(COLORREF);

      double r = diameter / 2.0;

      double dBorder = 1.0;

      double rmin = r - dBorder;

      double rmax = r;

      int crA;

      COLORREF * pcolorref2;

      for (int y = 0; y < s.cx; y++)
      {

         pcolorref2 = &pcolorref[y * wscan];

         for (int x = 0; x < s.cx; x++)
         {

            double dx = x;

            double dy = y;

            double distance = sqrt((dx - r) * (dx - r) + (dy - r) * (dy - r));

            crA = (int)((rmin - distance) * 255.0 / dBorder);

            crA = MAX(MIN(crA, 255), 0);

            *pcolorref2 = (*pcolorref2 & 0x00ffffff) | (crA << 24);

            pcolorref2++;

         }

      }

      return true;

   }


   bool dib::create_framed_square(::draw2d::dib * pdib, int inner, int outer, COLORREF cr)
   {

      if (!create(inner + outer * 2, inner + outer * 2))
      {

         return false;

      }

      Fill(cr);

      get_graphics()->StretchBlt(outer, outer, inner, inner, pdib->get_graphics(), 0, 0, pdib->m_size.cx, pdib->m_size.cy, SRCCOPY);

      return true;

   }


   void dib_copy(dib * pdibthis, dib *pdib)
   {

      pdibthis->from(pdib);

   }


   void dib_alloc(::aura::application * papp, dib * & pdib)
   {

      App(papp).alloc(pdib);

   }


   void dib_create(dib * pdib, int w, int h)
   {

      pdib->create(w, h);

   }


   unsigned int * dib_get_data(dib * pdib)
   {

      return (unsigned int *)pdib->m_pcolorref;

   }


   graphics * dib_get_graphics(dib * pdib)
   {

      if (pdib == NULL)
      {

         return NULL;

      }

      return pdib->get_graphics();

   }

   dib & dib::operator = (const dib & dib)
   {

      if (this != &dib)
      {

         from(&dib);

      }

      return *this;

   }


   ::size dib::get_size() const
   {

      //      if(m_iHeight >= 0)
      //      {
      //
      //         return ::size(m_size.cx, m_iHeight);
      //
      //      }
      //      else
      {

         return m_size;

      }

   }

   void dib::nanosvg(NSVGimage *image)
   {

      NSVGrasterizer *rast = NULL;
      unsigned char* img = NULL;
      int w, h;

      w = (int)m_size.cx;
      h = (int)m_size.cy;
      COLORREF * pdata = NULL;
      int iScan = 0;
      rast = nsvgCreateRasterizer();
      if (rast == NULL)
      {
         printf("Could not init rasterizer.\n");
         goto error;
      }
      Fill(0);
      {
#ifdef __APPLE__
         memory m;
         m.allocate(w * h * 4);
         m.zero();
         pdata = (COLORREF *)m.get_data();
         iScan = w * 4;
#else
         pdata = m_pcolorref;
         iScan = m_iScan;
#endif

         nsvgRasterize(rast, image, 0, 0, 1, (unsigned char *)pdata, w, h, iScan);

#ifdef __APPLE__
         int wscan = m_iScan / 4;
         index i = 0;
         index j = h - 1;
         for (; i < h; i++, j--)
         {
            memcpy(&m_pcolorref[wscan * i], &pdata[w * j], iScan);
         }
#endif
      }

error:
      nsvgDeleteRasterizer(rast);

   }



   void dib::nanosvg(string str)
   {

      NSVGimage *image = NULL;

      image = nsvgParse((char *)(const char *)str, "px", 96.0f);

      if (image == NULL)
      {

         printf("Could not open SVG image.\n");

         goto error;

      }

      nanosvg(image);

error:

      nsvgDelete(image);

   }

   void dib::create_nanosvg(string str)
   {

      NSVGimage *image = NULL;

      image = nsvgParse((char *)(const char *)str, "px", 96.0f);

      if (image == NULL)
      {

         printf("Could not open SVG image.\n");

         goto error;

      }

      if (!create((int)image->width, (int)image->height))
      {

         printf("Could not open SVG image (Dib creation failed).\n");

         goto error;

      }

      map();

      nanosvg(image);

error:

      nsvgDelete(image);

   }


   inline static byte clampAndConvert(double v)
   {
      if (v < 0)
         return 0;
      if (v > 255)
         return 255;
      return (byte)(v);
   }

   //// exepcts a string and returns an object
   //
   //inline void rgbToHSL(int &h, double &s, double &l, byte &br, byte & bg, byte &bb)
   //{

   //   double r = br / 255.0;
   //   double g = bg / 255.0;
   //   double b = bb / 255.0;

   //   double cMax = MAX(r, MAX(g, b));
   //   double cMin = MIN(r, MIN(g, b));
   //   double delta = cMax - cMin;
   //   l = (cMax + cMin) / 2.0;
   //   h = 0.0;
   //   s = 0.0;

   //   if (delta == 0)
   //   {
   //      h = 0;
   //   }
   //   else if (cMax == r)
   //   {
   //      h = 60.0 * fmod(((g - b) / delta), 6.0);
   //   }
   //   else if (cMax == g)
   //   {
   //      h = 60.0 * (((b - r) / delta) + 2.0);
   //   }
   //   else
   //   {
   //      h = 60.0 * (((r - g) / delta) + 4.0);
   //   }

   //   if (delta == 0)
   //   {
   //      s = 0;
   //   }
   //   else
   //   {
   //      s = (delta / (1.0 - fabs(2.0 * l - 1.0)));
   //   }

   //}

   //// expects an object and returns a string
   //inline void hslToRGB(byte & br, byte & bg, byte & bb, int h, double s, double l)
   //{
   //
   //   int c = (1.0 - fabs(2.0 * l - 1.0)) * s;
   //   double x = c * (1.0 - fabs(fmod((h / 60.0), 2.0) - 1.0));
   //   double m = l - c / 2.0;

   //   double r;
   //   double g;
   //   double b;

   //   if (h < 60) {
   //      r = c;
   //      g = x;
   //      b = 0;
   //   }
   //   else if (h < 120) {
   //      r = x;
   //      g = c;
   //      b = 0;
   //   }
   //   else if (h < 180) {
   //      r = 0;
   //      g = c;
   //      b = x;
   //   }
   //   else if (h < 240) {
   //      r = 0;
   //      g = x;
   //      b = c;
   //   }
   //   else if (h < 300) {
   //      r = x;
   //      g = 0;
   //      b = c;
   //   }
   //   else {
   //      r = c;
   //      g = 0;
   //      b = x;
   //   }

   //   r = normalize_rgb_value(r, m);
   //   g = normalize_rgb_value(g, m);
   //   b = normalize_rgb_value(b, m);

   //   return rgbToHex(r, g, b);
   //}

   //void changeHue(byte & r, byte & g, byte & b, byte degree)
   //{
   //
   //   int h;
   //   int s;
   //   int l;
   //
   //   rgbToHSL(h, s, l, r, g, b);
   //
   //   h += degree;

   //   if (h > 360)
   //   {
   //      h -= 360;
   //   }
   //   else if (h < 0)
   //   {
   //      h += 360;
   //   }
   //
   //   hslToRGB(r, g, b, h, s, l);

   //}

   void dib::hue_offset(double dRadians)
   {

      if (dRadians >= 0.0)
      {

         dRadians = fmod(dRadians, 3.1415 * 2.0);

      }
      else
      {

         dRadians = (3.1415 * 2.0) - fmod(-dRadians, 3.1415 * 2.0);

      }

      //http://stackoverflow.com/questions/8507885/shift-hue-of-an-rgb-color
      //http://stackoverflow.com/users/630989/jacob-eggers
      double U = ::cos(dRadians);
      double W = ::sin(dRadians);


      BYTE *dst = (BYTE*)get_data();

      int64_t size = scan_area();


      while (size--)
      {
         double oldr = dst[0];
         double oldg = dst[1];
         double oldb = dst[2];
         dst[0] = clampAndConvert((.299 + .701*U + .168*W)*oldr
                                  + (.587 - .587*U + .330*W)*oldg
                                  + (.114 - .114*U - .497*W)*oldb);
         dst[1] = clampAndConvert((.299 - .299*U - .328*W)*oldr
                                  + (.587 + .413*U + .035*W)*oldg
                                  + (.114 - .114*U + .292*W)*oldb);
         dst[2] = clampAndConvert((.299 - .3*U + 1.25*W)*oldr
                                  + (.587 - .588*U - 1.05*W)*oldg
                                  + (.114 + .886*U - .203*W)*oldb);
         dst += 4;
      }


   }

   void dib::on_load_image()
   {

      if (oprop("exif_orientation").i32() > 0)
      {

         on_exif_orientation();

      }

   }


   void dib::on_exif_orientation()
   {

      e_rotate_flip erotateflip = exif_orientation_rotate_flip(oprop("exif_orientation").i32());

      if (erotateflip == rotate_90_flip_none)
      {

         rotate90();

      }
      else if (erotateflip == rotate_180_flip_none)
      {

         rotate180();

      }
      else if (erotateflip == rotate_270_flip_none)
      {

         rotate270();

      }
      else if (erotateflip == rotate_none_flip_x)
      {

         flipx();

      }
      else if (erotateflip == rotate_90_flip_x)
      {

         rotate90flipx();

      }
      else if (erotateflip == rotate_180_flip_x)
      {

         rotate180flipx();

      }
      else if (erotateflip == rotate_270_flip_x)
      {

         rotate270flipx();

      }

   }


} // namespace draw2d




