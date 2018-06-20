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


