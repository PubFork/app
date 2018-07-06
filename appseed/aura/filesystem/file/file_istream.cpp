#include "framework.h"
#include <stdio.h>
#include <stdarg.h>



namespace file
{


   // FindSignature.cpp
   // from 7-zip on 2012-12-23, lunch time
#include "framework.h"

   /*//#include "Common/Buffer.h"

   //#include "FindSignature.h"

   //#include "../../Common/StreamUtils.h"*/


   istream::istream()
   {

      m_gcount = 0;

   }




   istream::istream(file * preader)
   {

      m_spfile = preader;
      m_gcount = 0;

   }

   istream::istream(const istream & istream)
   {

      m_spfile = istream.m_spfile;
      m_gcount = 0;

   }

   istream::~istream()
   {

      close();

   }


   memory_size_t istream::read(void * lpBuf, memory_size_t nCount)
   {

      return m_gcount = m_spfile->read(lpBuf, nCount);

   }

   void istream::full_read(void * lpBuf, memory_size_t nCount)
   {

      if(fail())
      {

         return;

      }


      if(!m_spfile->full_read(lpBuf,nCount))
      {

         setstate(failbit);

         return;

      }



      m_gcount = nCount;

   }


   void istream::full_fill(::primitive::memory_base & m)
   {

      full_read(m.get_data(), m.get_size());

   }

   void istream::read_arbitrary(int32_t & i)
   {


   }

   void istream::read_arbitrary(uint32_t & ui)
   {


   }

   void istream::read_arbitrary(int64_t & i)
   {


   }

   void istream::read_arbitrary(uint64_t & ui)
   {


   }


   void istream::read (bool & b)
   {

      blt(b);

   }


   void istream::read (char & ch)
   {

      blt(ch);

   }


   void istream::read (uchar & uch)
   {

      blt(uch);

   }


#ifdef WINDOWS


   void istream::read (unichar & wch)
   {

      blt(wch);

   }


#endif


   void istream::read (int16_t & sh)
   {

      blt(sh);

   }


   void istream::read (uint16_t & ui)
   {

      blt(ui);

   }


   void istream::read (int32_t & i)
   {

      blt(i);

   }


   void istream::read (uint32_t & ui)
   {

      blt(ui);

   }


   void istream::read (int64_t & i)
   {

      blt(i);

   }


   void istream::read (uint64_t & ui)
   {

      blt(ui);

   }


#ifdef APPLEOS

   void istream::read(unsigned long & ui)
   {

      blt(ui);

   }

#endif


   void istream::read (float & f)
   {

      blt(f);

   }


   void istream::read (double & d)
   {

      blt(d);

   }


   void istream::read (LPRECT lprect)
   {

      blt(*lprect);

   }


   void istream::read (SIZE & size)
   {

      blt(size);

   }


   void istream::read (sp(type) info)
   {

      string str;

      read(str);

      info->m_id = str;

      read(str);

      info->m_idFriendly = str;

      info->m_pfactoryitem = System.factory().m_mapItem[info->m_id];


   }


   void istream::read (id & id)
   {

      UNREFERENCED_PARAMETER(id);

      ::exception::throw_interface_only(get_app());

   }


   void istream::read (var & var)
   {
      UNREFERENCED_PARAMETER(var);
      ::exception::throw_interface_only(get_app());
   }


   void istream::read(property & property)
   {
      UNREFERENCED_PARAMETER(property);
      ::exception::throw_interface_only(get_app());
   }


   void istream::read(string & str)
   {


   }


   int istream::get()
   {
      unsigned char uch;

      if(read(&uch,1) == 1)
         return uch;

      return EOF;

   }


   int istream::peek()
   {
      unsigned char uch;

      if(read(&uch,1) == 1)
      {
         seek(-1,seek_current);
         return uch;
      }

      return EOF;

   }

   istream & istream::getline(char * sz,strsize n)
   {
      int c;
      while(n > 0)
      {
         c = get();
         if(c == EOF)
         {
            break;
         }
         else if(c == '\n')
         {
            c = get();
            if(c != '\r' && c != EOF)
               seek(-1,seek_current);
            break;
         }
         else if(c == '\r')
         {
            c = get();
            if(c != '\n' && c != EOF)
               seek(-1,seek_current);
            break;
         }
         *sz = (char)c;
         sz++;
         n--;
      }

      return *this;

   }


   istream & istream::operator = (const istream & istream)
   {

      m_spfile = istream.m_spfile;

      return *this;

   }


   bool istream::is_reader_null()
   {
      return m_spfile.is_null();
   }

   bool istream::is_reader_set()
   {
      return m_spfile.is_set();
   }


   void istream::read_to_hex(string & str, file_position_t dwStart, file_position_t dwEnd)
   {
      memory memory(get_app());
#if MEMDLEAK
      memory.m_strTag = "memory://member=::file::istream::read_to_hex";
#endif
      if(dwStart == (file_position_t) -1)
      {
         dwStart = tellg();
      }
      else
      {
         seek_from_begin(dwStart);
      }
      memory_position_t uiPos = 0;
      memory_size_t uiRead;
      memory.allocate(1024);

      strsize nCount;

      if (dwEnd == (file_position_t)-1)
      {

         nCount = ::numeric_info< strsize >::max();

      }
      else
      {

         nCount = (strsize)(dwEnd - dwStart);

      }

      while((uiRead = read(&memory.get_data()[uiPos], MIN(memory.get_size() - uiPos, (memory_size_t) nCount))) > 0)
      {
         uiPos += uiRead;
         nCount -= uiRead;
         if(memory.get_size() - uiPos <= 0)
         {
            memory.allocate_add_up(1024 * 1024);
         }
      }
      memory.allocate((memory_size_t) uiPos);
      memory.to_hex(str);
   }




} // namespace file




