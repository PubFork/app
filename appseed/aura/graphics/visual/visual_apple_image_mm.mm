//
//  visual_apple_image_mm.m
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 25/10/17.
//

#import <Foundation/Foundation.h>


void * get_dib(int & w, int & h, int & iScan, const void * pdata, unsigned long size)
{
   
   NSData * data = [[NSData alloc] initWithBytes:pdata length:size];
   
   if(data == nil)
   {
      
      return NULL;
      
   }
   
   NSImage * image = [[NSImage alloc] init: data]);
   
   if(image == NULL)
   {
      
      return NULL;
      
   }
   
   
   return NULL;
   
}
