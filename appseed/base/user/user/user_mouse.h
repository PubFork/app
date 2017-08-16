//
//  user_mouse.hpp
//  base
//
//  Created by Camilo Sasuke Tsumanuma on 14/08/17.
//
//
#pragma once


namespace user
{
   
   class CLASS_DECL_BASE mouse
   {
   public:
      uint_ptr                m_nFlags;
      point                   m_pt;
      point                   m_ptDesired;
      bool                    m_bTranslated;
      ::visual::e_cursor      m_ecursor;
      ::visual::cursor *      m_pcursor;
      
      
      virtual unsigned int get_message()
      {
         return 0;
      }
      
   };
   
   
} // namespace user

