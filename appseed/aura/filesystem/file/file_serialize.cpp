#include "framework.h"



serialize::serialize()
{

   m_b64bit = false;

}


serialize::serialize(serialize && serialize) :
   ::object(::move(serialize)),
   stream(::move(serialize))
{

   m_b64bit = serialize.m_b64bit;

}


serialize::serialize(::file::file * pfile, index iVersion) :
   ::object(pfile->get_app()),
   stream(pfile, iVersion)
{

   m_b64bit = false;

}


serialize::serialize(::aura::application * papp, index iVersion) :
   ::object(papp),
   stream(papp, iVersion)
{

}


serialize::~serialize()
{

   close();

}






bool serialize::is_stream_null()
{

   return is_writer_null() && is_reader_null();

}


bool serialize::is_stream_set()
{

   return is_writer_set() || is_reader_set();

}


void serialize::close()
{

   stream::close();

}


file_position_t serialize::get_position() const
{

   return m_spfile->get_position();

}





int get_arbitrary_length(uint64_t ui);




// string serialization code
// string format:
//      UNICODE strings are always prefixed by 0xff, 0xfffe
//      if < 0xff chars: len:BYTE, char chars
//      if >= 0xff characters: 0xff, len:WORD, char chars
//      if >= 0xfffe characters: 0xff, 0xffff, len:uint32_t, TCHARs

void serialize::write(string & string)
{
   if (string.get_length() < 255)
   {
      operator << ((byte) string.get_length());
   }
   else if (string.get_length() < 0xfffe)
   {
      operator << ((byte)0xff);
      operator << ((u16)string.get_length());
   }
   else
   {
      operator << ((byte)0xff);
      operator << ((u16)0xffff);
      operator << ((u32)string.get_length());
   }

   m_spfile->write((const char *)string, string.get_length());

}






void serialize::write(bool b)
{

   oblt(b);

}

void serialize::write(char ch)
{

   oblt(ch);

}

void serialize::write(uchar uch)
{

   oblt(uch);

}


void serialize::write(int16_t i)
{

   oblt(i);

}

void serialize::write(u16 ui)
{
   oblt(ui);

}
#ifdef WINDOWS
void serialize::write(unichar wch)
{
   oblt(wch);

}
#endif
//   void serialize:: write (int32_t i)
//   {
//      write(i);
//
//   }
//
//   void serialize:: write (uint32_t ui)
//   {
//      write(ui);
//
//   }
//
//   void serialize:: write (int64_t i)
//   {
//      write(i);
//
//   }
//
//   void serialize:: write (uint64_t ui)
//   {
//      write(ui);
//
//   }



void serialize::write(i32 i)
{

   oblt(i);

}

void serialize::write(u32 ui)
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

//   void serialize::write(uint64_t ui, int signal)
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

void serialize::write(i64 i)
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

void serialize::write(u64 ui)
{

   //write(ui, 0);

   oblt(ui);

}

void serialize::write(float f)
{
   //      m_spfile->write(&f, sizeof(f));

   oblt(f);

}

void serialize::write(double d)
{
   //m_spfile->write(&d, sizeof(d));

   oblt(d);

}

void serialize::write(RECT & rect)
{
   //      m_spfile->write(&rect.left,     sizeof(rect.left));
   //      m_spfile->write(&rect.top,      sizeof(rect.top));
   //      m_spfile->write(&rect.right,    sizeof(rect.right));
   //      m_spfile->write(&rect.bottom,   sizeof(rect.bottom));

   oblt(rect);

}

void serialize::write(LPRECT lpcrect)
{

   oblt(*lpcrect);

}

void serialize::write(SIZE & size)
{
   //m_spfile->write(&size.cx,     sizeof(size.cx));
   //m_spfile->write(&size.cy,     sizeof(size.cy));
   oblt(size);

}

void serialize::write(sp(type) & info)
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


void serialize::write(const char * psz)
{

   m_spfile->write(psz, strlen(psz));

}


void serialize::write(id & id)
{

   bool bNull = id.is_null();

   operator << (bNull);

   if (!bNull)
   {
      string str = id.m_psz;
      *this << str;
   }

}


//string serialize::get_location() const
//{

//   return "<unknown serialize location>";

//}


//   ostream & serialize::operator = (const ostream & ostream)
//   {
//
//      return serialize::operator = (ostream);
//
//   }


void serialize::write_from_hex(const char * psz, strsize iLen)
{

   //memory memory(get_app());

   //memory.from_hex(psz);

   //write(memory.get_data(), memory.get_size());

   stream::write_from_hex(psz, iLen < 0 ? strlen(psz) + iLen + 1 : iLen);

}


void serialize::write_from_hex(const string & str)
{

   serialize::write_from_hex(str, str.get_length());

}







// return string length or -1 if UNICODE string is found in the archive
__STATIC UINT __read_string_length(serialize & ar)
{
   uint32_t nNewLen;

   // attempt BYTE length first
   byte bLen;
   ar >> bLen;

   if (ar.fail())
   {

      return 0;

   }

   if (bLen < 0xff)
      return bLen;

   // attempt WORD length
   uint16_t wLen;
   ar >> wLen;
   if (wLen == 0xfffe)
   {
      // UNICODE string prefix (length will follow)
      return (UINT)-1;
   }
   else if (wLen == 0xffff)
   {
      // read uint32_t of length
      ar >> nNewLen;
      return (UINT)nNewLen;
   }
   else
      return wLen;
}




int get_arbitrary_length(uint64_t ui);



// FindSignature.cpp
// from 7-zip on 2012-12-23, lunch time
//#include "framework.h"

/*//#include "Common/Buffer.h"

//#include "FindSignature.h"

//#include "../../Common/StreamUtils.h"*/


//   serialize::serialize()
//   {
//   }
//
//   serialize::serialize(file * preader) :
//      istream(preader)
//   {
//
//   }
//
//   serialize::serialize(const istream & is) :
//      istream(is)
//   {
//
//   }
//
//   serialize::~serialize()
//   {
//
//   }

void serialize::read(char & ch)
{

   if (m_spfile->read(&ch, sizeof(ch)) != sizeof(ch))
      _throw(io_exception(get_app(), "serialize::read"));



}


void serialize::read(uchar & uch)
{

   if (fail())
   {

      return;

   }

   if (m_spfile->read(&uch, sizeof(uch)) != sizeof(uch))
   {

      setstate(::file::failbit);

   }

}


void serialize::read(int16_t & i)
{

   blt(i);



}

void serialize::read(uint16_t & ui)
{
   blt(ui);

}
#ifdef WINDOWS
void serialize::read(unichar & wch)
{
   blt(wch);

}
#endif
void serialize::read(bool & b)
{
   blt(b);

}

//   void serialize::read(int32_t & i)
//   {
//      blt(i);
//
//   }
//
//   void serialize::read(uint32_t & ui)
//   {
//      blt(ui);
//
//   }
//
//   void serialize::read(int64_t & i)
//   {
//      blt(i);
//
//   }
//
//   void serialize::read(uint64_t & ui)
//   {
//      blt(ui);
//
//   }

void serialize::read(int32_t & i)
{

   blt(i);

}

void serialize::read(uint32_t & ui)
{

   blt(ui);

}

void serialize::read(int64_t & i)
{

   blt(i);

}

void serialize::read(uint64_t & ui)
{

   blt(ui);

}

//   void serialize::read(void * p, ::count nMax)
//   {
//
//      if(fail())
//         return;
//
//      byte b;
//
//      full_read(&b,sizeof(b));
//
//      if(fail())
//         return;
//
//      if(b == 0)
//      {
//
//         memset(p, 0, nMax);
//
//         return;
//
//      }
//
//      uint64_t uiRead = 0;
//
//      int len = b & 0x3f;
//
//      if(len > (int) sizeof(uiRead) || len > nMax)
//      {
//
//         setstate(failbit);
//
//         return;
//
//      }
//
//      full_read(&uiRead,len);
//
//      if(fail())
//         return;
//
//      if(b & 0x40)
//      {
//
//         int64_t i = - ((int64_t) uiRead);
//
//         memcpy(p, &i, nMax);
//
//      }
//      else
//      {
//
//         memcpy(p, &uiRead, nMax);
//
//      }
//
//   }


void serialize::read(float & f)
{

   blt(f);

}


void serialize::read(double & d)
{

   blt(d);

}

void serialize::read(LPRECT lprect)
{

   blt(*lprect);

}

void serialize::read(SIZE & size)
{

   blt(size);

}


void serialize::read(sp(type) info)
{

   memory m;


   {
      int32_t iLen;
      full_read(&iLen, sizeof(iLen));
      m.allocate(iLen + 1);
      full_fill(m);
      m.get_data()[iLen] = '\0';
      info->m_id = (const char *)m.get_data();
   }
   {
      int32_t iLen;
      full_read(&iLen, sizeof(iLen));
      m.allocate(iLen + 1);
      full_fill(m);
      m.get_data()[iLen] = '\0';
      info->m_idFriendly = (const char *)m.get_data();
   }

}


void serialize::read(id & id)
{

   bool bNull;

   read(bNull);

   if (bNull)
      id.clear();
   else
   {
      string str;

      *this >> str;

      id = str;
   }



}


string serialize::get_location() const
{

   return "<unknown serialize location>";

}


void serialize::full_load(string & str)
{

   if (m_spfile.is_null())
      return;

   sp(seekable) spseekable = m_spfile;

   if (spseekable.is_set())
   {

      spseekable->seek_to_end();

      file_position_t uiLength = spseekable->get_position();

      spseekable->seek_to_begin();

      ::strsize uiCount = ::numeric_info< strsize >::natural(uiLength);

      file_position_t uiPos = 0;

      LPSTR lpstr = str.GetBufferSetLength((strsize)(uiLength + 1));

      while (uiCount > 0)
      {

         memory_size_t uiRead = m_spfile->read(&lpstr[uiPos], (memory_size_t)uiCount);

         uiCount -= uiRead;

         uiPos += uiRead;

      }

      str.ReleaseBuffer((strsize)uiLength);

   }
   else
   {

      ::file::string_file strbuffer;

      ::strsize uiPos = 0;

      memory_size_t uiRead;

      do
      {

         uiRead = m_spfile->read((void *) &((const char *)strbuffer)[uiPos], (memory_size_t)(strbuffer.get_length() - uiPos));

         uiPos += uiRead;

      }
      while (uiRead > 0);

      str = strbuffer.str();

   }

}


void serialize::read(string & string)
{
   int32_t nConvert = 0;   // if we get UNICODE, convert

   UINT nNewLen = __read_string_length(*this);
   if (nNewLen == (UINT)-1)
   {
      nConvert = 1 - nConvert;
      nNewLen = __read_string_length(*this);
      ASSERT(nNewLen != (UINT)-1);
   }

   char * lpBuf;
   // set length of string to new length
   UINT nByteLen = nNewLen;
   nByteLen += nByteLen * nConvert;    // bytes to read
   if (nNewLen == 0)
      lpBuf = string.GetBufferSetLength(0);
   else
      lpBuf = string.GetBufferSetLength((int32_t)nByteLen + nConvert);

   // read in the characters
   if (nNewLen != 0)
   {
      ASSERT(nByteLen != 0);

      // read new data
      if (m_spfile->read(lpBuf, nByteLen) != nByteLen)
      {
         //   ::core::ThrowArchiveException(CArchiveException::endOfFile);
      }

      // convert the data if as necessary
      if (nConvert != 0)
      {
         lpBuf[nNewLen] = '\0';    // must be NUL terminated
         string.ReleaseBuffer();   // don't delete the old data
      }
   }

}



namespace file
{


   byte_stream_memory_file::byte_stream_memory_file(::aura::application * papp) :
      object(papp),
      memory_container(papp),
      memory_file(papp)
   {

      m_spfile = this;

   }


   byte_stream_memory_file::~byte_stream_memory_file()
   {


   }


   file_position_t byte_stream_memory_file::seek(file_offset_t offset, e_seek seekOrigin)
   {

      return memory_file::seek(offset, seekOrigin);

   }


   file_position_t byte_stream_memory_file::get_position() const
   {

      return memory_file::get_position();

   }


   void byte_stream_memory_file::flush()
   {

      memory_file::flush();

   }


   void * byte_stream_memory_file::get_internal_data()
   {

      return memory_file::get_internal_data();

   }


   const void * byte_stream_memory_file::get_internal_data() const
   {

      return memory_file::get_internal_data();

   }


   memory_size_t byte_stream_memory_file::get_internal_data_size() const
   {

      return memory_file::get_internal_data_size();

   }

   bool byte_stream_memory_file::set_internal_data_size(memory_size_t s)
   {

      return memory_file::set_internal_data_size(s);

   }

   void byte_stream_memory_file::write(const void * p, memory_size_t s)
   {

      memory_file::write(p, s);

   }


   memory_size_t byte_stream_memory_file::read(void * p, memory_size_t s)
   {

      return memory_file::read(p, s);

   }


   void byte_stream_memory_file::set_length(file_size_t dwNewLen)
   {

      serialize::set_length(dwNewLen);

   }


   void byte_stream_memory_file::close()
   {

      serialize::close();

   }

} // namespace file



