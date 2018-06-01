#pragma once

namespace str
{


   CLASS_DECL_AURA bool x_contains(string str, string strFind);
   CLASS_DECL_AURA bool x_find(stringa & stra, string str);
   CLASS_DECL_AURA void x_left_remove(string & str, string strFind);


} // namespace str

inline int trailingBytesForUTF8(int i)
{
   if (i <= 0)
      return -1;
   else if (i >= 1 && i <= 191)
   {
      return 0;
   }
   else if (i >= 192 && i <= 223)
   {
      return 1;
   }
   else if (i >= 224 && i <= 239)
   {
      return 2;
   }
   else if (i >= 240 && i <= 247)
   {
      return 3;
   }
   else if (i >= 248 && i <= 251)
   {
      return 4;
   }
   else if (i >= 252 && i <= 255)
   {
      return 5;
   }
   else
   {
      return -1;
   }
   //   (const char)  -1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   //   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   //   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   //   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   //   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   //   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   //   1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
   //   2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, 3,3,3,3,3,3,3,3,4,4,4,4,5,5,5,5
   //};
}

