//
//  macos_main.h
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 8/2/15.
//
//

#pragma once



struct main_param
{
   int argc;
   char * *argv;
   
};

uint32_t __run_system_main_param(struct main_param * p);
