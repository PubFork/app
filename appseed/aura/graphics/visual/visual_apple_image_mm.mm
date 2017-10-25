//
//  visual_apple_image_mm.m
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 25/10/17.
//

#import <Foundation/Foundation.h>

//#include <CoreGraphics/CoreGraphics.h>
CFDataRef CopyImagePixels(CGImageRef inImage) {     return CGDataProviderCopyData(CGImageGetDataProvider(inImage)); }

void * get_dib(int & w, int & h, int & iScan, const void * pdata, unsigned long size)
{
   
   NSData * data = [NSData dataWithBytes:pdata length:size];
   
   if(data == nil)
   {
      
      return NULL;
      
   }
   
   NSImage * image = [[NSImage alloc] initWithData: data];
   
   if(image == NULL)
   {
      
      return NULL;
      
   }
   
   CGImageRef cgimage = [image CGImageForProposedRect:NULL context:NULL hints:NULL];
   
   if(cgimage == NULL)
   {
    
      return NULL;
      
   }
   
   w = (int) CGImageGetWidth(cgimage);
   
   h   = (int) CGImageGetHeight(cgimage);
   
   if(w <= 0 || h <= 0)
   {
      
      return NULL;
      
   }
   
   iScan = (int) CGImageGetBytesPerRow(cgimage);
   
   if(iScan <= 0)
   {
    
      return NULL;
      
   }
   
   CFDataRef cfdata = CopyImagePixels(cgimage);
   
   const void * psrc = CFDataGetBytePtr(cfdata);
   
   if(psrc == NULL)
   {
    
      return NULL;
      
   }
   
   void * pdst = malloc(iScan * h);
   
   if(pdst == NULL)
   {
      
      return NULL;
      
   }
   
   memcpy(pdst, psrc, iScan * h);
   
   return pdst;
   
}

void * return_data(unsigned long & size, NSData * data)
{
   if(data == NULL)
   {
      return NULL;
   }
   if([data length] <= 0 || [data bytes] == NULL)
   {
      return NULL;
   }
   void * p = malloc([data length]);
   if(p == NULL)
   {
      return NULL;
   }
   memcpy(p, [data bytes], [data length]);
   size = [data length];
   return p;
}

void * get_png_image_data(unsigned long & size, CGImageRef image)
{
   
   NSBitmapImageRep *imgRep = [[NSBitmapImageRep alloc] initWithCGImage:image];
   NSDictionary *imageProps = [NSDictionary dictionaryWithObject:[NSNumber numberWithFloat:1.0] forKey:NSImageCompressionFactor];

   NSData *data = [imgRep representationUsingType: NSPNGFileType properties: imageProps];
   
   return return_data(size, data);

}


void * get_jpeg_image_data(unsigned long & size, CGImageRef cgimage)
{
   NSImage * image = [[NSImage alloc] initWithCGImage:cgimage size: NSZeroSize];
   NSData *imageData = [image TIFFRepresentation];
   NSBitmapImageRep *imageRep = [NSBitmapImageRep imageRepWithData:imageData];
   NSDictionary *imageProps = [NSDictionary dictionaryWithObject:[NSNumber numberWithFloat:1.0] forKey:NSImageCompressionFactor];
   imageData = [imageRep representationUsingType:NSJPEGFileType properties:imageProps];;
   
   return return_data(size, imageData);
   
}

void * get_jpeg_image_data(unsigned long & size, CGImage image);

