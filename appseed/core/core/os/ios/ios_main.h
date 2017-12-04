//
//  ios_main.hpp
//  core
//
//  Created by Camilo Sasuke Tsumanuma on 21/07/17.
//  Copyright © 2017 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#pragma once


namespace aura
{

   class library;

   class application;

   extern "C"
   typedef class library * (*PFN_GET_NEW_LIBRARY)(::aura::application * papp);


} // namespace aura


extern ::aura::PFN_GET_NEW_LIBRARY g_pfnNewLibrary;


int ios_core_main(int argc, char * argv[]);



extern "C" bool defer_core_init(void);

#define BEG_CORE_APP \
\
int main(int argc, char * argv[]) \
{ \
\
   if(!defer_core_init()) \
{ \
return -1; \
} \
\
   \
    \


#define END_CORE_APP \
   return ios_core_main(argc, argv); \
   \
}

#define DEF_CORE_APP(X) DECL_LIB(X); BEG_CORE_APP REG_LIB(X); END_CORE_APP






