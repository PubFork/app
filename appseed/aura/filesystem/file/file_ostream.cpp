#include "framework.h"


//namespace file
//{


   serialize::serialize()
   {
      
      m_gcount = 0;

   }


//   stream::stream(const char * lpszFileName, uint32_t nOpenFlags, ::aura::application * papp)
//   {
//
//      if(papp == NULL)
//      {
//
//         m_spfile = canew(::file::stdio_file(lpszFileName,nOpenFlags | ::file::mode_write));
//
//      }
//      else
//      {
//
//         m_spfile = App(papp).file().get_file(lpszFileName,nOpenFlags | ::file::mode_write);
//
//      }
//
//   }


//   serialize::serialize(file * pwriter)
//   {
//
//      m_spfile     = pwriter;
//
//   }


//   serialize::serialize(const serialize & serialize)
//   {
//
//      m_spfile     = serialize.m_spfile;
//
//   }


   serialize::~serialize()
   {
      close();
   }


   void serialize::write_from_hex(const void *lpBuf,memory_size_t nCount)
   {

      m_spfile->write_from_hex(lpBuf,nCount);

   }


   void serialize::write(const void *lpBuf,memory_size_t nCount)
   {

      m_spfile->write(lpBuf, nCount);

   }

   void serialize::write(const void *lpBuf, memory_size_t nCount, memory_size_t * dwWritten)
   {

      m_spfile->write(lpBuf, nCount, dwWritten);

   }


   void serialize:: write (bool b)
   {

      oblt(b);

   }

   void serialize:: write (char ch)
   {

      oblt(ch);

   }


   void serialize:: write (uchar uch)
   {

      oblt(uch);

   }


   void serialize::write (int16_t i)
   {

      oblt(i);

   }


   void serialize:: write (uint16_t ui)
   {

      oblt(ui);

   }


#ifdef WINDOWS


   void serialize:: write (unichar wch)
   {

      oblt(wch);

   }


#endif


//   void serialize:: write (int32_t i)
//   {
//
//      oblt(i);
//
//   }
//
//
//   void serialize:: write (u32 ui)
//   {
//
//      oblt(ui);
//
//   }
//
//
//   void serialize:: write (i64 i)
//   {
//
//      oblt(i);
//
//   }
//
//   void serialize:: write (u64 ui)
//   {
//
//      oblt(ui);
//
//   }

#ifdef APPLEOS

   void serialize:: write (unsigned long ui)
   {

      oblt(ui);
      
   }

#endif


   void serialize::write(i32 i)
   {

      oblt(i);

   }

   
   void serialize::write(u32 ui)
   {

      oblt(ui);

   }


//   void serialize::write(uint64_t ui, int signal)
//   {
//
//
//   }

   void serialize::write(int64_t i)
   {

      oblt(i);

   }


void serialize::write(uint64_t ui)
   {
      
      oblt(ui);

   }


   void serialize:: write (float f)
   {
      
      oblt(f);

   }


   void serialize:: write (double d)
   {
      
      oblt(d);

   }


   void serialize:: write (RECT & rect)
   {
      
      oblt(rect);

   }


   void serialize:: write(LPRECT lpcrect)
   {
      
      oblt(*lpcrect);
      
   }


   void serialize:: write(SIZE & size)
   {
      
      oblt(size);

   }


   void serialize:: write(sp(type) & info)
   {
      
      string str(info->m_id);
      
      write(str);

   }


   void serialize::write(std_type_info & info)
   {
      
      write(System.get_type_info(info));

   }


   void serialize:: write (const char * psz)
   {

   }


   void serialize:: write (id & id)
   {

   }


   void serialize:: write (var & var)
   {

   }


   void serialize:: write( property & property)
   {

   }


//   serialize & serialize::operator = (const serialize & serialize)
//   {
//
//      m_spfile = serialize.m_spfile;
//
//      return *this;
//
//   }

   void serialize::flush()
   {

      if(m_spfile.is_set())
      {

         m_spfile->flush();

      }

   }


   void serialize::close()
   {

      flush();

      stream::close();

   }


   bool serialize::is_writer_null()
   {

      return m_spfile.is_null();

   }


   bool serialize::is_writer_set()
   {

      return m_spfile.is_set();

   }


   void serialize:: write (string & str)
   {

      write(str.c_str(), str.get_length());

   }

   void serialize::set_length(file_size_t len)
   {

      m_spfile->set_length(len);

   }

   serialize & serialize::put(char ch)
   {
      write(ch);
      return *this;
   }

//} // namespace file




