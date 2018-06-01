#pragma once

namespace str
{


   CLASS_DECL_AURA bool x_contains(string str, string strFind);
   CLASS_DECL_AURA bool x_find(stringa & stra, string str);
   CLASS_DECL_AURA void x_left_remove(string & str, string strFind);


} // namespace str

inline int trailingBytesForUTF8(char ch)
{

   if(ch == 0)
   {
      return -1;
   }
   else if (ch >= 1 && ch <= 127)
   {
      return 0;
   }
   else if (ch >= -128 && ch <= -65)
   {
      return 0;
   }
   else if (ch >= -64 && ch <=-33)
   {
      return 1;
   }
   else if (ch >= -32 && ch <= -17)
   {
      return 2;
   }
   else if (ch >= -16 && ch <= -9)
   {
      return 3;
   }
   else if (ch >= -8 && ch <= -5)
   {
      return 4;
   }
   else if (ch >= -4 && ch <= -1)
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

