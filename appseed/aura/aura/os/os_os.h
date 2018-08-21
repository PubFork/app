//
//  os_os.h
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 05/01/18.
//


#pragma once

// C++ includes

CLASS_DECL_AURA string get_command_line_dup();

CLASS_DECL_AURA string ca2_module_folder_dup();


#if defined(MACOS)


// C++ includes

#include "aura/aura/os/apple/apple_apple.h"
#include "aura/aura/os/macos/macos_macos.h"


#elif defined(APPLE_IOS)


// C++ includes

#include "aura/aura/os/apple/apple_apple.h"
#include "aura/os/ios/ios_ios.h"


#elif defined(LINUX)


// C++ includes

#include "aura/os/linux/linux_linux.h"


#elif defined(METROWIN)


// C++ includes

#include "aura/os/metrowin/metrowin_metrowin.h"


#elif defined(WINDOWSEX)


// C++ includes

#include "aura/os/windows/windows_windows.h"

#elif defined(ANDROID)


// C++ includes

#include "aura/os/android/android_android.h"

#elif defined(SOLARIS)


// C++ includes

#include "aura/os/solaris/solaris_solaris.h"

#elif defined(APPLE_IOS)


// C++ includes

#include "os/ansios/ansios.h"
#include "aura/os/ios/ca_os.h"


#else


#error "Currently not supported operating system"


#endif


template < typename PRED >
inline void pred_Sleep(int iTime, PRED pred)
{

   if(iTime < 100)
   {

      Sleep(100);

   }
   else
   {

      iTime += 99;

      iTime /= 100;

      for(index i = 0; i < iTime; i++)
      {

         Sleep(100);

         if(!pred())
         {

            break;

         }

      }

   }

}




