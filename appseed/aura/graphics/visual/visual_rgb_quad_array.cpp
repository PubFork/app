#include "framework.h"


colorref_array::colorref_array()
{

}


colorref_array::~colorref_array()
{

}


void colorref_array::create_web_palette()
{

   // Do nothing
   const uint32_t STANDARD_PALETTE[] = {00,51,102,153,204,255};
   const INT STANDARD_COLOR_SIZE = 6;
//   const INT STANDARD_PALETTE_VAL_DIF = 51;
   allocate(216);
//   uint32_t dwColorMapTable[216] = {0};
   int32_t nColorMapIdx = 0;
   for(int32_t nBlueIdx = 0; nBlueIdx < STANDARD_COLOR_SIZE; ++nBlueIdx)
   {
      for(int32_t nGreenIdx = 0; nGreenIdx < STANDARD_COLOR_SIZE; ++nGreenIdx)
      {
         for(int32_t nRedIdx = 0; nRedIdx < STANDARD_COLOR_SIZE; ++nRedIdx)
         {
            this->element_at(nColorMapIdx) = ARGB(255, (BYTE) STANDARD_PALETTE[nRedIdx],
             (BYTE) STANDARD_PALETTE[nGreenIdx],
               (BYTE) STANDARD_PALETTE[nBlueIdx]);
            ++nColorMapIdx;
         }
      }
   }
}
