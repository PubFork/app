#pragma once

namespace user
{

   class scroll_info
   {
      public:
         UINT     cbSize;
         UINT     fMask;
         int32_t      nMin;
         int32_t      nMax;
         int32_t      nPage;
         int32_t      nPos;
         int32_t      nTrackPos;
   };


} // namespace user