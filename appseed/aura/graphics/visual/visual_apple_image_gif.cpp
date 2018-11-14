//
//  visual_apple_image_gif.cpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 21/10/17.
//
#include "framework.h"

#include <ImageIO/ImageIO.h>

#ifdef APPLE_IOS

#import <MobileCoreServices/MobileCoreServices.h>

#endif


void * get_dib(int & width, int & height, int & iScan, CGImageRef image);


bool imaging::apple_load_diba_from_file(::visual::dib_sp::array * pdiba, ::file::file_sp pfile, ::aura::application * papp)

{
   
   memory m;
   
   Application.file().as_memory(pfile, m);
   
   if(m.is_empty())
   {
    
      return false;
      
   }
   
   int w = 0;
   
   int h = 0;
   
   int iScan = 0;
   
   ::aura::malloc < COLORREF * > pcolorref;
   
   CFDataRef data = CFDataCreateWithBytesNoCopy(NULL, m.data(), m.size(), kCFAllocatorNull);
      
   //https://github.com/Flipboard/FLAnimatedImage/blob/master/FLAnimatedImage/FLAnimatedImage.m
      
   if(data == NULL)
   {
      
      return false;
         
   }
   
   CGImageSourceRef imagesource = NULL;
   
   {
   
      CFDictionaryRef   options;
      CFStringRef       keys[2];
      CFTypeRef         values[2];
   
      // Set up options if you want them. The options here are for
      // caching the image in a decoded form and for using floating-point
      // values if the image format supports them.
      keys[0] = kCGImageSourceShouldCache;
      values[0] = (CFTypeRef)kCFBooleanFalse;
   
      // Create the dictionary
      options = CFDictionaryCreate(NULL, (const void **) keys,
                                  (const void **) values, 1,
                                  &kCFTypeDictionaryKeyCallBacks,
                                  &kCFTypeDictionaryValueCallBacks);
   
      // Note: We could leverage `CGImageSourceCreateWithURL` too to add a second initializer `-initWithAnimatedGIFContentsOfURL:`.
      imagesource = CGImageSourceCreateWithData(data, options);
      
      CFRelease(options);
      
   }
      
   // Early return on failure!
   if (imagesource == NULL)
   {
      
      return false;
      
   }
      
   // Early return if not GIF!
   CFStringRef imagesourcetype = CGImageSourceGetType(imagesource);
      
   bool bGif = UTTypeConformsTo(imagesourcetype, kUTTypeGIF);
      
   if (!bGif)
   {
      
      CFRelease(imagesource);
         
      return NULL;
         
   }
      
   // Get `LoopCount`
   // Note: 0 means repeating the animation indefinitely.
   // Image properties example:
   // {
   //     FileSize = 314446;
   //     "{GIF}" = {
   //         HasGlobalColorMap = 1;
   //         LoopCount = 0;
   //     };
   // }
   CFDictionaryRef imageproperties = CGImageSourceCopyProperties(imagesource, NULL);
   
   CFDictionaryRef gifproperties = (CFDictionaryRef) CFDictionaryGetValue(imageproperties, kCGImagePropertyGIFDictionary);
   
   CFNumberRef loopCount = (CFNumberRef) CFDictionaryGetValue(gifproperties, kCGImagePropertyGIFLoopCount);
   
   int iLoopCount;
   
   if(!CFNumberGetValue(loopCount, kCFNumberSInt32Type, &iLoopCount))
   {
      
      iLoopCount = 0;
      
   }
   
   // Iterate through frame images
   size_t imageCount = CGImageSourceGetCount(imagesource);
   
   for (size_t i = 0; i < imageCount; i++)
   {

      CGImageRef image = CGImageSourceCreateImageAtIndex(imagesource, i, NULL);
      
      if(image)
      {
         
         int w = 0;
         
         int h = 0;
         
         int iScan = 0;
         
         ::aura::malloc<COLORREF *> pdata((COLORREF *) get_dib(w, h, iScan, image));
               // Check for valid `frameImage` before parsing its properties as frames can be corrupted (and `frameImage` even `nil` when `frameImageRef` was valid).
         
         sp(::visual::dib_sp::pointer) p = canew(::visual::dib_sp::pointer);
         
         p->m_dib.alloc(papp->allocer());

         if(_load_image(p->m_dib, w, h, iScan, pdata))
         {
            
            p->m_edisposal = ::visual::disposal_none;
            
            p->m_rect.left = 0;
            
            p->m_rect.top = 0;
            
            p->m_rect.right = w;
            
            p->m_rect.bottom = h;
            
            p->m_crTransparent = 0;
            
            p->m_bTransparent = false;
            
            p->m_bLocalPalette = false;
            
            pdiba->m_size.cx = MAX(w, pdiba->m_size.cx);
            
            pdiba->m_size.cy = MAX(h, pdiba->m_size.cy);

            pdiba->add(p);
            
            // Get `DelayTime`
            // Note: It's not in (1/100) of a second like still falsely described in the documentation as per iOS 8 (rdar://19507384) but in seconds stored as `kCFNumberFloat32Type`.
            // Frame properties example:
            // {
            //     ColorModel = RGB;
            //     Depth = 8;
            //     PixelHeight = 960;
            //     PixelWidth = 640;
            //     "{GIF}" = {
            //         DelayTime = "0.4";
            //         UnclampedDelayTime = "0.4";
            //     };
            // }
                  
            CFDictionaryRef frameproperties = CGImageSourceCopyPropertiesAtIndex(imagesource, i, NULL);
            
            CFDictionaryRef gifproperties = (CFDictionaryRef) CFDictionaryGetValue(frameproperties, kCGImagePropertyGIFDictionary);
                  
            // Try to use the unclamped delay time; fall back to the normal delay time.
            CFNumberRef delayTime = (CFNumberRef) CFDictionaryGetValue(gifproperties, kCGImagePropertyGIFUnclampedDelayTime);
            
            double dDelay = 0.0;
            
            if(delayTime == NULL || !CFNumberGetValue(delayTime, kCFNumberFloat64Type, &dDelay))
            {
            
               delayTime = (CFNumberRef) CFDictionaryGetValue(gifproperties, kCGImagePropertyGIFDelayTime);
               
               if(delayTime == NULL || !CFNumberGetValue(delayTime, kCFNumberFloat64Type, &dDelay))
               {
                  
                  dDelay = 0.0;
                  
               }
                  
            }
            
            p->m_dwTime = (DWORD) (dDelay * 1000.0);
            
            if(p->m_dwTime < 90)
            {
               
               p->m_dwTime = 90;
               
            }
            
            p->m_dib->create_helper_map();
            
            pdiba->m_dwTotal += p->m_dwTime;

         }

      }

   }
   
   CFRelease(gifproperties);
   
   CFRelease(imagesource);
   
   CFRelease(imagesourcetype);
   
   return true;
   
}
   


