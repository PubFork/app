#pragma once


namespace file
{


   class CLASS_DECL_AURA stream2 :
      virtual public stream
   {
   public:


      stream2();
      stream2(writer * pwriter);
      virtual ~stream2();


      stream2 & operator << (uchar uch);
      stream2 & operator << (u16 ui);
      stream2 & operator << (i32 i);
      stream2 & operator << (u32 ui);
      stream2 & operator << (RECT & rect);
      stream2 & operator << (const char * psz);
      stream2 & operator << (string & str);


   };


} // namespace file



