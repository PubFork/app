#include "framework.h"

serialize::serialize()
{
   
   m_gcount = 0;

}

bool serialize::is_stream_null()
{
   //return is_writer_null() && is_reader_null();
   return m_spfile.is_null();
}

bool serialize::is_stream_set()
{
   //return is_writer_set() || is_reader_set();
   return m_spfile.is_set();
}


memory_size_t serialize::read(void * lpBuf, memory_size_t nCount)
{
   
   return m_gcount = m_spfile->read(lpBuf, nCount);
   
}

void serialize::full_read(void * lpBuf, memory_size_t nCount)
{
   
   if(fail())
   {
      
      return;
      
   }
   
   
   if(!m_spfile->full_read(lpBuf,nCount))
   {
      
      setstate(::file::failbit);
      
      return;
      
   }
   
   
   
   m_gcount = nCount;
   
}


void serialize::full_fill(::primitive::memory_base & m)
{
   
   full_read(m.get_data(), m.get_size());
   
}

//void serialize::read(int32_t & i)
//{
//   
//   
//}
//
//void serialize::read(uint32_t & ui)
//{
//   
//   
//}
//
//void serialize::read(int64_t & i)
//{
//   
//   
//}
//
//void serialize::read(uint64_t & ui)
//{
//   
//   
//}


void serialize::read (bool & b)
{
   
   iblt(b);
   
}


void serialize::read (char & ch)
{
   
   iblt(ch);
   
}


void serialize::read (uchar & uch)
{
   
   iblt(uch);
   
}


#ifdef WINDOWS


void serialize::read (unichar & wch)
{
   
   iblt(wch);
   
}


#endif


void serialize::read (int16_t & sh)
{
   
   iblt(sh);
   
}


void serialize::read (uint16_t & ui)
{
   
   iblt(ui);
   
}


void serialize::read (int32_t & i)
{
   
   iblt(i);
   
}


void serialize::read (uint32_t & ui)
{
   
   iblt(ui);
   
}


void serialize::read (int64_t & i)
{
   
   iblt(i);
   
}


void serialize::read (uint64_t & ui)
{
   
   iblt(ui);
   
}


#ifdef APPLEOS

void serialize::read(unsigned long & ui)
{
   
   iblt(ui);
   
}

#endif


void serialize::read (float & f)
{
   
   iblt(f);
   
}


void serialize::read (double & d)
{
   
   iblt(d);
   
}


void serialize::read (LPRECT lprect)
{
   
   iblt(*lprect);
   
}


void serialize::read (SIZE & size)
{
   
   iblt(size);
   
}


void serialize::read (sp(type) & info)
{
   
   string str;
   
   read(str);
   
   info = System.get_type_info((id)str);
   
}


void serialize::read (id & id)
{
   
   UNREFERENCED_PARAMETER(id);
   
   ::exception::throw_interface_only(get_app());
   
}


void serialize::read (var & var)
{
   UNREFERENCED_PARAMETER(var);
   ::exception::throw_interface_only(get_app());
}


void serialize::read(property & property)
{
   UNREFERENCED_PARAMETER(property);
   ::exception::throw_interface_only(get_app());
}


void serialize::read(string & str)
{
   
   
}


int serialize::get()
{
   unsigned char uch;
   
   if(read(&uch,1) == 1)
      return uch;
   
   return EOF;
   
}


int serialize::peek()
{
   unsigned char uch;
   
   if(read(&uch,1) == 1)
   {
      seek(-1,::file::seek_current);
      return uch;
   }
   
   return EOF;
   
}

serialize & serialize::getline(char * sz,strsize n)
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
            seek(-1,::file::seek_current);
         break;
      }
      else if(c == '\r')
      {
         c = get();
         if(c != '\n' && c != EOF)
            seek(-1,::file::seek_current);
         break;
      }
      *sz = (char)c;
      sz++;
      n--;
   }
   
   return *this;
   
}


bool serialize::is_reader_null()
{
   
   return m_spfile.is_null() || !(m_spfile->m_nOpenFlags & ::file::mode_read);
   
}


bool serialize::is_reader_set()
{
   
   return m_spfile.is_set() && (m_spfile->m_nOpenFlags & ::file::mode_read);
   
}


void serialize::read_to_hex(string & str, file_position_t dwStart, file_position_t dwEnd)
{
   memory memory(get_app());
#if MEMDLEAK
   memory.m_strTag = "memory://member=serialize::read_to_hex";
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




