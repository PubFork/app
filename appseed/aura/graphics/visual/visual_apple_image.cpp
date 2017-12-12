//
//  visual_apple_image.cpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 21/10/17. Thomas Boregaard Soerensen <3
//

#include "framework.h"


CFDataRef CopyImagePixels(CGImageRef inImage);


void * get_png_image_data(unsigned long & size, CGImageRef image);
void * get_jpeg_image_data(unsigned long & size, CGImageRef image);


bool imaging::_save_image(::file::file * pfile, ::draw2d::dib * pdib, ::visual::save_image * psaveimage)
{
   
   if(pdib == NULL)
   {
      
      return NULL;
      
   }
   
   unsigned long size;
   
   ::aura::malloc < COLORREF * > pdst;
   
   pdst.alloc(pdib->m_iScan * pdib->m_size.cy);
   
   if(pdst == NULL)
   {
      
      return NULL;
      
   }
   
   ::draw2d::_001ProperCopyColorref(
                                    pdib->m_size.cx,
                                    pdib->m_size.cy, pdst, pdib->m_iScan, pdib->m_pcolorref, pdib->m_iScan);
   
   CGColorSpaceRef colorspace = CGColorSpaceCreateDeviceRGB();
   
   CGContextRef context = CGBitmapContextCreate(
                                                pdst,
                                                pdib->m_size.cx,
                                                pdib->m_size.cy, 8,
                                                pdib->m_iScan, colorspace, kCGImageAlphaPremultipliedLast);
   
   CGColorSpaceRelease(colorspace);
   
   if(context == NULL)
   {
      
      return false;
      
      
   }
   
   CGImageRef cgimage = CGBitmapContextCreateImage(context);
   
   ::aura::malloc < COLORREF * > p;
   
   switch (psaveimage == NULL ? ::visual::image::format_png : psaveimage->m_eformat)
   {
      case ::visual::image::format_jpeg:
      {
         
         p = get_jpeg_image_data(size, cgimage);
         
      }
         break;
      default:
      {
         
         p = get_png_image_data(size, cgimage);
         
      }
         
   }
   
   CGImageRelease(cgimage);
   
   CGContextRelease(context);
   
   pfile->write(p, size);
   
   return true;
   
}


   
void * get_dib(int & w, int & h, int & iScan, const void * pdata, unsigned long size);

bool imaging::_load_image(::draw2d::dib * pdib, ::file::file * pfile)
{
   
   memory m;
   
   Application.file().as_memory(pfile, m);
   
   int w = 0;
   
   int h = 0;
   
   int iScan = 0;
   
   ::aura::malloc < COLORREF * > pcolorref;
   
   pcolorref = get_dib(w, h, iScan, m.get_data(), m.get_size());
   
   if(pcolorref == NULL)
   {
    
      return false;
      
   }
   
   try
   {
      
      if(!pdib->create(w, h))
      {
         
         return false;
         
      }

      ::draw2d::_001ProperCopyColorref(w, h, pdib->m_pcolorref, pdib->m_iScan, pcolorref, iScan);
      
   }
   catch(...)
   {
      
      return false;
      
   }
   
//#if 1 // check premultiplied
//
//   byte * p = (byte *) pdib->m_pcolorref;
//
//   size_t s = iScan * h / sizeof(COLORREF);
//
//   while(s> 0)
//   {
//      if(p[0] > p[3] || p[1] > p[3] || p[2] > p[3])
//      {
//         output_debug_string("probably not premultiplied");
//      }
   //p+=4;
//      s--;
//   }
//
//#endif
   
   byte * p = (byte *) pdib->m_pcolorref;
   
   size_t s = iScan * h/ sizeof(COLORREF);
   
   while(s> 0)
   {
//      if(p[0] > p[3] || p[1] > p[3] || p[2] > p[3])
//      {
//         output_debug_string("probably not premultiplied");
//      }
      p[0] = p[0] * p[3] / 255;
      p[1] = p[1] * p[3] / 255;
      p[2] = p[2] * p[3] / 255;
      p+=4;
      s--;
   }

   return true;
   
   
}


