//
//  apple.m
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 04/01/18. with tbs in <3
//

#import "NSString+SymlinksAndAliases.h"

char * ns_string(NSString * str)
{
   
   if(str == nil)
   {
      
      return NULL;
      
   }
   
   const char * pszUtf8 = [str UTF8String];
   
   if(pszUtf8 == NULL)
   {
      
      return NULL;
      
   }
   
   return strdup(pszUtf8);
   
   
}



char * mm_ca2_command_line()
{
   
   return ns_string([[NSBundle mainBundle] objectForInfoDictionaryKey:@"ca2_command_line"]);
   
}


char * ns_get_bundle_identifier()
{
   
   return ns_string([[NSBundle mainBundle] bundleIdentifier]);
   
}


char * mm_error_string(OSStatus status)
{
   
   NSError * error = [NSError errorWithDomain:NSOSStatusErrorDomain code: status userInfo: nil];
   
   NSString * strError = [error localizedDescription];
   
   return ns_string(strError);
   
}


char * mm_error_description(OSStatus status)
{
   
   NSError * error = [NSError errorWithDomain:NSOSStatusErrorDomain code: status userInfo: nil];
   
   NSString * strError = [error description];
   
   return ns_string(strError);
   
}







char * ns_realpath(const char * pszPath)
{
   
   NSString * str = [[NSString alloc] initWithUTF8String:pszPath];
   
   NSString * strFullPath = [str stringByResolvingSymlinksAndAliases];
   
   if(strFullPath == nil)
   {
    
      return strdup(pszPath);
      
   }
   
   return ns_string(strFullPath);
   
}


void ns_main_async(dispatch_block_t block)
{
   
   //   dispatch_block_t block = ^{
   //      // Code for the method goes here
   //   };
   //
   
   if ([NSThread isMainThread])
   {
      
      block();
      
   }
   else
   {
      
      dispatch_async(dispatch_get_main_queue(), block);
      
   }
   
}


void ns_main_sync(dispatch_block_t block)
{
   
   //   dispatch_block_t block = ^{
   //      // Code for the method goes here
   //   };
   //
   
   if ([NSThread isMainThread])
   {
      
      block();
      
   }
   else
   {
      
      dispatch_sync(dispatch_get_main_queue(), block);
      
   }
   
}




void main_async_runnable(runnable * prunnable)
{
   
   ns_main_async(^
                 {
                    
                    prunnable->run();
                    
                 });
   
   //[[mmos get] runRunnableOnMainThread: prunnable];
   
}


void main_synch_runnable(runnable * prunnable)
{
   
   ns_main_sync(^
                {
                   
                   prunnable->run();
                   
                });
   
   //[[mmos get] runRunnableOnMainThread: prunnable];
   
}



