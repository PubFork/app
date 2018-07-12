#include "framework.h"


namespace file
{



   stream2::stream2()
   {
   }

   stream2::stream2(writer * pwriter)
   {

      m_spfile = pwriter;

   }

   stream2::~stream2()
   {
   }





   stream2 & stream2::operator << (uchar uch)
   {
      stream::operator << (uch);
      return *this;
   }

   stream2 & stream2::operator << (uint16_t ui)
   {
      stream::operator << (ui);
      return *this;
   }

   stream2 & stream2::operator << (int32_t i)
   {
      stream::operator << (i);
      return *this;
   }

   stream2 & stream2::operator << (uint32_t ui)
   {
      stream::operator << (ui);
      return *this;
   }

   stream2 & stream2::operator << (RECT & rect)
   {
      stream::operator << (rect);
      return *this;
   }


   stream2 & stream2::operator << (const char * psz)
   {
      write((void *)psz, strlen(psz));
      return *this;
   }

   stream2 & stream2::operator << (string & str)
   {
      operator <<((const char *)str);
      return *this;
   }


} // namespace file



