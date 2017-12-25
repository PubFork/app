//
//  visual_apple_image_mm.m
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 25/10/17.
//

#import <Foundation/Foundation.h>

//#include <CoreGraphics/CoreGraphics.h>
CFDataRef CopyImagePixels(CGImageRef inImage) {     return CGDataProviderCopyData(CGImageGetDataProvider(inImage)); }

void * get_dib(int & width, int & height, int & iScan, const void * pdata, unsigned long size)
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
   
   CGImageRef inputCGImage = [image CGImageForProposedRect:NULL context:NULL hints:NULL];
   
   if(inputCGImage == NULL)
   {
    
      return NULL;
      
   }
   
//https://www.raywenderlich.com/69855/image-processing-in-ios-part-1-raw-bitmap-modification
   
   // 1.
   width = (int) CGImageGetWidth(inputCGImage);
   height = (int) CGImageGetHeight(inputCGImage);
   
   // 2.
   NSUInteger bytesPerPixel = 4;
   NSUInteger bytesPerRow = bytesPerPixel * width;
   NSUInteger bitsPerComponent = 8;
   
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
   
   //CGImageRelease(inputCGImage);
   
   /*iScan = (int) CGImageGetBytesPerRow(cgimage);
   
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
   
   */
   
   //return pdst;
   
   return pixels;
   
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

