#pragma once


#include "user_key_enum.h"


namespace user
{

   class CLASS_DECL_AURA key :
      public ::message::base
   {
      public:

         int               m_iCode;
         uint_ptr          m_nChar;
         uint_ptr          m_nScanCode;
         UINT              m_nRepCnt;
         UINT              m_nFlags;
         bool              m_bExt;

         ::user::e_key     m_ekey;

         string            m_strText;

         //key();
         key(::aura::application * papp);
         key(const ::user::key & key);

         void copy_this(const key & key);

   };


} // namespace user


