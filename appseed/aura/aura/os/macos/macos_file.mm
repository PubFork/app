//
//  macos_file.m
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 03/05/18.
//

#include <CoreFoundation/CoreFoundation.h>

void ns_create_alias(const char * pszTarget, const char * pszSource)
{
   NSString * strTarget = [[NSString alloc]initWithUTF8String:pszTarget];
   NSString * strSource = [[NSString alloc]initWithUTF8String:pszSource];
   
   [[NSFileManager defaultManager ] createSymbolicLinkAtPath: strTarget withDestinationPath: strSource error:nil];
}


const char * ns_user_local_folder(NSSearchPathDirectory e)
{
   
   NSArray < NSURL * > * pa = [[NSFileManager defaultManager ] URLsForDirectory:e inDomains:NSLocalDomainMask| NSUserDomainMask];
   
   if(pa == NULL || [pa count] <= 0)
   {
      
      return NULL;
      
   }
   
   return ns_string([[pa objectAtIndex:0] path]);
   
}



const char * ns_user_local_desktop_folder()
{
   
   return ns_user_local_folder(NSDesktopDirectory);
   
}


const char * ns_user_local_documents_folder()
{
   
   return ns_user_local_folder(NSDocumentDirectory);
   
}

const char * ns_user_local_downloads_folder()
{
   
   return ns_user_local_folder(NSDownloadsDirectory);
   
}
const char * ns_user_local_music_folder()
{
   
   return ns_user_local_folder(NSMusicDirectory);
   
}


const char * ns_user_local_image_folder()
{
   
   return ns_user_local_folder(NSPicturesDirectory);
   
}

const char * ns_user_local_video_folder()
{
   
   return ns_user_local_folder(NSMoviesDirectory);
   
}


