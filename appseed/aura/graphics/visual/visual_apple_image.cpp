//
//  visual_apple_image.cpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 21/10/17. Thomas Boregaard Soerensen <3
//

#include "framework.h"


CFDataRef CopyImagePixels(CGImageRef inImage);


CGImageRef cgimageref_from_dib(void * dib)
{
   
   ::draw2d::dib * pdib = (::draw2d::dib *) dib;
   
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
      
      return NULL;
      
      
   }
   
   CGImageRef cgimage = CGBitmapContextCreateImage(context);
   
   CGContextRelease(context);
   
   return cgimage;
   
}

void ns_set_cursor_cgimageref(CGImageRef image, int cx, int cy, int xHotSpot, int yHotSpot);

void * nscursor_from_cgimageref(CGImageRef image, int cx, int cy, int xHotSpot, int yHotSpot);

void * CreateAlphaCursor(void * dib, int xHotSpot, int yHotSpot)
{
   
   if(dib == NULL)
   {
      
      return NULL;
      
   }
   else
   {
      
#ifdef MACOS
      
      ::draw2d::dib * pdib = (::draw2d::dib *) dib;
      
      return nscursor_from_cgimageref(cgimageref_from_dib(pdib), pdib->m_size.cx, pdib->m_size.cy, xHotSpot, yHotSpot);
#else
      
      return NULL;
      
#endif

   }
   
}

void set_cursor_dib(void * dib, int xHotSpot, int yHotSpot)
{
   
   if(dib == NULL)
   {
   
      #ifdef MACOS
      
      ns_set_cursor_cgimageref(NULL, 0, 0, 0, 0);
      
#endif
      
   }
   else
   {
      
      ::draw2d::dib * pdib = (::draw2d::dib *) dib;
   
#ifdef MACOS
      
      ns_set_cursor_cgimageref(cgimageref_from_dib(pdib), pdib->m_size.cx, pdib->m_size.cy, xHotSpot, yHotSpot);
      
#endif
      
   }
   
}


void * get_png_image_data(unsigned long & size, CGImageRef image);
void * get_jpeg_image_data(unsigned long & size, CGImageRef image);


bool imaging::_save_image(::file::file * pfile, ::draw2d::dib * pdib, ::visual::save_image * psaveimage)
{
   
   if(pdib == NULL)
   {
      
      return NULL;
      
   }
   
   unsigned long size;
   
   CGImageRef cgimage = cgimageref_from_dib(pdib);
   
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
   
   return _load_image(pdib, w, h, iScan, pcolorref);
   
}




void * get_dib(int & width, int & height, int & iScan, CGImageRef inputCGImage)
{
   
   if(inputCGImage == NULL)
   {
      
      return NULL;
      
   }
   
   //https://www.raywenderlich.com/69855/image-processing-in-ios-part-1-raw-bitmap-modification
   // 1.
   width = (int) CGImageGetWidth(inputCGImage);
   height = (int) CGImageGetHeight(inputCGImage);
   
   // 2.
   long bytesPerPixel = 4;
   long bytesPerRow = bytesPerPixel * width;
   long bitsPerComponent = 8;
   
   UInt32 * pixels;
   pixels = (UInt32 *) calloc(height * width, sizeof(UInt32));
   
   // 3.
   CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
   CGContextRef context = CGBitmapContextCreate(pixels, width, height, bitsPerComponent, bytesPerRow, colorSpace, kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);
   
   // 4.
   CGContextDrawImage(context, CGRectMake(0, 0, width, height), inputCGImage);
   
   // 5. Cleanup
   CGColorSpaceRelease(colorSpace);
   
   CGContextRelease(context);
   
   return pixels;
   
}
