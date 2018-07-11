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
      serialize::operator << (uch);
      return *this;
   }

   stream2 & stream2::operator << (uint16_t ui)
   {
      serialize::operator << (ui);
      return *this;
   }

   stream2 & stream2::operator << (int32_t i)
   {
      serialize::operator << (i);
      return *this;
   }

   stream2 & stream2::operator << (uint32_t ui)
   {
      serialize::operator << (ui);
      return *this;
   }

   stream2 & stream2::operator << (RECT & rect)
   {
      serialize::operator << (rect);
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



