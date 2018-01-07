//
//  visual_apple_image_mm.m
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 25/10/17.
//

#import <Foundation/Foundation.h>

void * get_dib(int & width, int & height, int & iScan, CGImageRef image);

CFDataRef CopyImagePixels(CGImageRef inImage)
{
   
   return CGDataProviderCopyData(CGImageGetDataProvider(inImage));
   
}


void * get_dib(int & width, int & height, int & iScan, NSImage * pimage);

void * get_dib(int & width, int & height, int & iScan, const void * pdata, unsigned long size)
{
   
   NSData * data = [NSData dataWithBytes:pdata length:size];
   
   if(data == nil)
   {
      
      return NULL;
      
   }
   
   NSImage * image = [[NSImage alloc] initWithData: data];
   
   return get_dib(width, height, iScan, image);
   
}


void * get_dib(int & width, int & height, int & iScan, NSImage * image)
{
   
   CGImageRef inputCGImage = [image CGImageForProposedRect:NULL context:NULL hints:NULL];
   
   return get_dib(width, height, iScan, inputCGImage);
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


