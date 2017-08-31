#pragma once


namespace windows
{


   class CLASS_DECL_AURA command :
      public ::command::command
   {
   public:


      HINSTANCE      m_hInstance;
      HINSTANCE      m_hPrevInstance;
      int32_t        m_nCmdShow;


   };


} // namespace windows

