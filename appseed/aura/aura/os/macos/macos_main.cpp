//
//  macos_main.cpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 8/2/15.
//
//

//
//  main.cpp
//  app
//
//  Created by Camilo Sasuke Tsumanuma on 15/05/14.
//  Copyright (c) 2014 Camilo Sasuke Tsumanuma. All rights reserved.
//



//uint32_t __run_system_main_param(main_param * pparam)
//{
//   
//   string strCommandLine;
//   
//   bool bColon = false;
//   
//   for(int32_t i = 0; i < pparam->argc; i++)
//   {
//      
//      if(i > 0)
//      {
//         
//         strCommandLine += " ";
//         
//      }
//      
//      if(strcmp(pparam->argv[i], ":") == 0)
//      {
//         
//         strCommandLine     += ":";
//         
//         bColon = true;
//         
//      }
//      else if(bColon)
//      {
//         
//         strCommandLine     += pparam->argv[i];
//         
//         
//      }
//      else
//      {
//         
//         strCommandLine     += "\"";
//         
//         strCommandLine     += pparam->argv[i];
//         
//         strCommandLine     += "\"";
//         
//      }
//      
//   }
//   
//   
//   
//   strCommandLine
//   
//   return __run_system_command_line();
//   
//}


uint32_t __start_system(const char * pszFileName)
{
   
   
   if(::aura::system::g_p != NULL)
   {
      
      if(pszFileName != NULL)
      {
      
         macos_on_open_file(pszFileName);
         
      }
    
      return 0;
      
   }
   
   int32_t nReturnCode = 0;
   
   ::aura::system * psystem;
   
   psystem = create_aura_system();
      
   ::set_thread(psystem);
      
   ::aura::main_init_data * pinitmaindata   = new ::aura::main_init_data;
      
   pinitmaindata->m_vssCommandLine          = g_pszCommandLine;
   
   if(pszFileName != NULL)
   {
   
      pinitmaindata->m_straFile.add(pszFileName);
      
   }
   
   psystem->init_main_data(pinitmaindata);
      
   bool bOk = true;
      
   try
   {
         
      if(psystem->begin_synch())
      {
            
         bOk = true;
            
      }
         
   }
   catch(...)
   {
         
   }
      
   try
   {
         
      if(!bOk)
      {
            
         if(psystem->m_iReturnCode == 0)
         {
               
            return -1;
               
         }
            
         return psystem->m_iReturnCode;
            
      }
         
   }
   catch(...)
   {
         
      return -1;
         
   }
      
   return nReturnCode;
   
}






