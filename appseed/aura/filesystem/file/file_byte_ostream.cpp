#include "framework.h"




namespace file
{


   int get_arbitrary_length(uint64_t ui);




   // string serialization code
   // string format:
   //      UNICODE strings are always prefixed by 0xff, 0xfffe
   //      if < 0xff chars: len:BYTE, char chars
   //      if >= 0xff characters: 0xff, len:WORD, char chars
   //      if >= 0xfffe characters: 0xff, 0xffff, len:uint32_t, TCHARs

   void byte_stream:: write (string & string)
   {
      if (string.get_length() < 255)
      {
         *this << (byte)         string.get_length();
      }
      else if (string.get_length() < 0xfffe)
      {
         *this << (byte)         0xff;
         *this << (uint16_t)     string.get_length();
      }
      else
      {
         *this << (byte)         0xff;
         *this << (uint16_t)     0xffff;
         *this << (uint32_t)     string.get_length();
      }

      m_spfile->write((const char *) string, string.get_length());

   }





   byte_stream::byte_stream()
   {
      m_b64bit = false;
   }

   byte_stream::byte_stream(file * pfile) :
      serialize(pfile)
   {
      m_b64bit = false;
   }

//   byte_stream::byte_stream(const  ostream & os) :
//      ostream(os)
//   {
//      m_b64bit = false;
//   }

   byte_stream::~byte_stream()
   {

   }

   void byte_stream:: write (bool b)
   {

      oblt(b);

   }

   void byte_stream:: write (char ch)
   {

      oblt(ch);

   }

   void byte_stream:: write (uchar uch)
   {

      oblt(uch);

   }

   
   void byte_stream:: write (int16_t i)
   {
      
      oblt(i);

   }

   void byte_stream:: write (u16 ui)
   {
      oblt(ui);

   }
#ifdef WINDOWS
   void byte_stream:: write (unichar wch)
   {
      oblt(wch);

   }
#endif
//   void byte_stream:: write (int32_t i)
//   {
//      write(i);
//
//   }
//
//   void byte_stream:: write (uint32_t ui)
//   {
//      write(ui);
//
//   }
//
//   void byte_stream:: write (int64_t i)
//   {
//      write(i);
//
//   }
//
//   void byte_stream:: write (uint64_t ui)
//   {
//      write(ui);
//
//   }



   void byte_stream::write(i32 i)
   {

      oblt(i);

   }

   void byte_stream::write(u32 ui)
   {

      oblt(ui);

   }

//   int get_arbitrary_length(uint64_t ui)
//   {
//
//      if(ui == 0)
//      {
//         return 0;
//      }
//      else if(ui < (1UL << 8))
//      {
//         return 1;
//      }
//      else if(ui < (1UL << 16))
//      {
//         return 2;
//      }
//      else if(ui < (1UL << 24))
//      {
//         return 3;
//      }
//      else if(ui < (1ULL << 32))
//      {
//         return 4;
//      }
//      else if(ui < (1ULL << 40))
//      {
//         return 5;
//      }
//      else if(ui < (1ULL << 48))
//      {
//         return 6;
//      }
//      else if(ui < (1ULL << 56))
//      {
//         return 7;
//      }
//      else
//      {
//         return 8;
//      }
//
//   }

//   void byte_stream::write(uint64_t ui, int signal)
//   {
//
//      // 0 bit is 0 for 0 version
//
//      // 0 version first byte reserved
//      // 1 bit is signal
//      // 2-7 bit length in bytes of the arbitrary always positive integer signal by signal bit above
//
//      if(signal != 0)
//         signal = 1;
//
//      int len = get_arbitrary_length(ui);
//
//      byte b = (signal << 6) | (len & 0x3f);
//
//      m_spfile->write(&b, sizeof(b));
//
//      m_spfile->write(&ui, len);
//
//   }

   void byte_stream::write(i64 i)
   {

//      if(i < 0)
//      {
//         write(-i, 1);
//      }
//      else
//      {
//         write(i, 0);
//      }
      
      oblt(i);

   }

   void byte_stream::write(u64 ui)
   {

      //write(ui, 0);
      
      oblt(ui);

   }

   void byte_stream:: write (float f)
   {
//      m_spfile->write(&f, sizeof(f));
      
      oblt(f);

   }

   void byte_stream:: write (double d)
   {
      //m_spfile->write(&d, sizeof(d));
      
      oblt(d);

   }

   void byte_stream:: write (RECT & rect)
   {
//      m_spfile->write(&rect.left,     sizeof(rect.left));
//      m_spfile->write(&rect.top,      sizeof(rect.top));
//      m_spfile->write(&rect.right,    sizeof(rect.right));
//      m_spfile->write(&rect.bottom,   sizeof(rect.bottom));
      
      oblt(rect);

   }

   void byte_stream:: write(LPRECT lpcrect)
   {

      oblt(*lpcrect);

   }

   void byte_stream:: write (SIZE & size)
   {
      //m_spfile->write(&size.cx,     sizeof(size.cx));
      //m_spfile->write(&size.cy,     sizeof(size.cy));
      oblt(size);

   }

   void byte_stream:: write (sp(type) & info)
   {
//      strsize iLen = strlen(info->name());
  //    m_spfile->write(&iLen, sizeof(iLen));
    //  m_spfile->write(info->name(), iLen);
      //iLen = strlen(info->friendly_name());
      //m_spfile->write(&iLen, sizeof(iLen));
      //m_spfile->write(info->friendly_name(), iLen);
      
      string str = info->m_id;
      
      write(str);

   }


   void byte_stream:: write (const char * psz)
   {

      m_spfile->write(psz, strlen(psz));

   }


   void byte_stream:: write (id & id)
   {

      bool bNull = id.is_null();

      operator << (bNull);

      if(!bNull)
      {
         string str = id.m_psz;
         *this << str;
      }

   }


   string byte_stream::get_location() const
   {

      return "<unknown byte_stream location>";

   }


//   ostream & byte_stream::operator = (const ostream & ostream)
//   {
//
//      return serialize::operator = (ostream);
//
//   }


   void byte_stream::write_from_hex(const char * psz, strsize iLen)
   {

      //memory memory(get_app());

      //memory.from_hex(psz);

      //write(memory.get_data(), memory.get_size());

      serialize::write_from_hex(psz,iLen < 0 ? strlen(psz) + iLen + 1 : iLen);

   }


   void byte_stream::write_from_hex(const string & str)
   {

      serialize::write_from_hex(str,str.get_length());

   }


} // namespace file



