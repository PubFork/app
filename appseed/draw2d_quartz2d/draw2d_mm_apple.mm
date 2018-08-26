//
//  draw2d_mm_apple.m
//  draw2d_quartz2d
//
//  Created by Camilo Sasuke Tsumanuma on 25/08/18.
//  Copyright © 2018 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#import <Foundation/Foundation.h>

#ifdef MACOS
#import <AppKit/AppKit.h>
#else
#import <UIKit/UIKit.h>
#endif

#ifdef MACOS
#define kCTFontWeightUltraLight NSFontWeightUltraLight
#define kCTFontWeightThin NSFontWeightThin
#define kCTFontWeightLight NSFontWeightLight
#define kCTFontWeightRegular NSFontWeightRegular
#define kCTFontWeightMedium NSFontWeightMedium
#define kCTFontWeightSemibold NSFontWeightSemibold
#define kCTFontWeightBold NSFontWeightBold
#define kCTFontWeightHeavy NSFontWeightHeavy
#define kCTFontWeightBlack NSFontWeightBlack
#else
#define kCTFontWeightUltraLight UIFontWeightUltraLight
#define kCTFontWeightThin UIFontWeightThin
#define kCTFontWeightLight UIFontWeightLight
#define kCTFontWeightRegular UIFontWeightRegular
#define kCTFontWeightMedium UIFontWeightMedium
#define kCTFontWeightSemibold UIFontWeightSemibold
#define kCTFontWeightBold UIFontWeightBold
#define kCTFontWeightHeavy UIFontWeightHeavy
#define kCTFontWeightBlack UIFontWeightBlack
#endif

//#define FW_THIN             100
//#define FW_EXTRALIGHT       200
//#define FW_LIGHT            300
//#define FW_NORMAL           400
//#define FW_MEDIUM           500
//#define FW_SEMIBOLD         600
//#define FW_BOLD             700
//#define FW_EXTRABOLD        800
//#define FW_HEAVY            900


CGFloat nsfont_get_ctweight(int iWeight)
{
   
   float fCoreTextWeight = kCTFontWeightRegular;
   
   if (iWeight < FontSelectionValue(150))
   {
      
      fCoreTextWeight = kCTFontWeightUltraLight;
      
   }
   else if (iWeight < FontSelectionValue(250))
   {
      
      fCoreTextWeight = kCTFontWeightThin;
      
   }
   else if (iWeight < FontSelectionValue(350))
   {

      fCoreTextWeight = kCTFontWeightLight;
      
   }
   else if (iWeight < FontSelectionValue(450))
   {

      fCoreTextWeight = kCTFontWeightRegular;
      
   }
   else if (iWeight < FontSelectionValue(550))
   {

      fCoreTextWeight = kCTFontWeightMedium;
      
   }
   else if (iWeight < FontSelectionValue(650))
   {

      fCoreTextWeight = kCTFontWeightSemibold;
      
   }
   else if (iWeight < FontSelectionValue(750))
   {
      
      fCoreTextWeight = kCTFontWeightBold;
      
   }
   else if (iWeight < FontSelectionValue(850))
   {

      fCoreTextWeight = kCTFontWeightHeavy;
      
   }
   else
   {

      fCoreTextWeight = kCTFontWeightBlack;
      
   }

   return fCoreTextWeight;

}
