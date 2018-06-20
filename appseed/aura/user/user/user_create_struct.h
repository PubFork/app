#pragma once


namespace user
{


   class CLASS_DECL_AURA create_struct :
#ifdef WINDOWSEX
      public CREATESTRUCTW
#else
      public CREATESTRUCTA
#endif
   {
   public:

      
      create_struct(const create_struct &) = default;
      create_struct(
                    u32 uiExStyle = 0,
                    const char * pszClassName = 0,
                    const char * pszWindowName = 0,
                    u32 uiStyle = 0,
                    ::rect rect = ::null_rect(),
                    LPVOID pvCreateParams = NULL);
      create_struct(LPCRECT lpcrect);

      
      void set_rect(LPCRECT lpcrect);
      void get_rect(LPRECT lprect);
      

   };


} // namespace user


