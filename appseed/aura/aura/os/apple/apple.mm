//
//  apple.m
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 04/01/18. with tbs in <3
//

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


