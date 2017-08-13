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
   
   string strFirst(pszFileName);
   
   string strExtra;
   
   stringa stra;
   
   // TODO : stringa::_001Explode
   stra.explode(":", strFirst);
   
   if(stra.get_count() > 1)
   {
      
      strFirst = stra[0];
      
      strExtra = stra.implode(":", 1);
      
   }
   
   // TODO processs strFirst properly
   strFirst.trim();
   
   // TODO processs strExtra properly
   strExtra.trim();
   
   if(::aura::system::g_p != NULL)
   {
      
      if(strFirst.has_char())
      {
      
         macos_on_open_file(strFirst, strExtra);
         
      }
    
      return 0;
      
   }
   
   int32_t nReturnCode = 0;
   
   ::aura::system * psystem;
   
   psystem = create_aura_system();
      
   ::set_thread(psystem);
      
   ::command::command * pcommand = new ::command::command;
      
   pcommand->m_strCommandLine = g_pszCommandLine;
   
   if(strFirst.has_char())
   {
   
      pcommand->m_straFile.add(strFirst);
      
   }
   
   if(strExtra.has_char())
   {
      
      pcommand->m_strExtra = strExtra;
      
   }
   
   
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






