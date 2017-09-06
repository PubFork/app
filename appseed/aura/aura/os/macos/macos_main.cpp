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


uint32_t __start_system_with_file(const char ** pszaFile, int iCount);


uint32_t __start_system_with_file(const char * pszFileName)
{
   
   if(pszFileName == NULL)
   {
      
      return __start_system_with_file(NULL, 0);
      
   }
   
   const char ** psza = (const char **) malloc(sizeof(const char **) * 1);
   
   psza[0] = strdup(pszFileName);
   
   return __start_system_with_file(psza, 1);
   
}

uint32_t __start_system_with_file(const char ** pszaFile, int iCount)
{
   
   string strExtra;
   
   if(::aura::system::g_p != NULL)
   {
      
      if(pszaFile != NULL)
      {
      
         macos_on_open_file(pszaFile, iCount, strExtra);
         
      }
    
      return 0;
      
   }
   
   var varFile;
   
   {
      
      stringa stra;
      
      stra.c_add((char **) pszaFile, iCount);
      
      varFile = stra;
      
   }
   
   int32_t nReturnCode = 0;
   
   ::aura::system * psystem;
   
   psystem = create_aura_system();
      
   ::set_thread(psystem);
      
   ::command::command * pcommand = new ::command::command;
      
   pcommand->m_strCommandLine = get_command_line_dup();
   
   pcommand->m_varFile = varFile;
      
   psystem->startup_command(pcommand);
      
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






