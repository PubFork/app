#include "framework.h"


namespace draw2d
{


   e_rotate_flip exif_orientation_rotate_flip(int orientation)
   {
      switch (orientation)
      {
      case 1:
      default:
         return rotate_none_flip_none;
      case 2:
         return rotate_none_flip_x;
      case 3:
         return rotate_180_flip_none;
      case 4:
         return rotate_180_flip_x;
      case 5:
         return rotate_90_flip_x;
      case 6:
         return rotate_90_flip_none;
      case 7:
         return rotate_270_flip_x;
      case 8:
         return rotate_270_flip_none;
      }
   }


} // namespace draw2d



