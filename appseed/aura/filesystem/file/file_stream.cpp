#include "framework.h"


stream::stream()
{

   m_gcount = 0;
   m_iostate = ::file::goodbit;
   m_fmtflags = ::file::nofmtflags;
   m_precision = 0;
   m_iVersion = FIRST_VERSION;
   m_pset = NULL;

}


stream::stream(stream && stream) :
   ::object(::move(stream)),
   m_spfile(::move(stream.m_spfile))
{

   m_gcount = stream.m_gcount;
   m_iostate = stream.m_iostate;
   m_fmtflags = stream.m_fmtflags;
   m_precision = stream.m_precision;
   m_iVersion = stream.m_iVersion;
   m_pset = stream.m_pset;

   stream.m_pset = NULL;

}


stream::stream(::file::file * pfile, index iVersion) :
   ::object(pfile->get_app())
{

   m_gcount = 0;
   m_iostate = ::file::goodbit;
   m_fmtflags = ::file::nofmtflags;
   m_precision = 0;
   m_iVersion = iVersion;
   m_pset = NULL;

   m_spfile = pfile;

}


stream::stream(::aura::application * papp, index iVersion) :
   ::object(papp)
{

   m_gcount = 0;
   m_iostate = ::file::goodbit;
   m_fmtflags = ::file::nofmtflags;
   m_precision = 0;
   m_iVersion = iVersion;
   m_pset = NULL;

}


stream::~stream()
{

   close();

}




string stream::GetFilePath() const
{

   return m_spfile->GetFilePath();

}


//void stream::close()
//{

//   m_spfile.release();

//}


file_position_t stream::seek(file_offset_t offset, ::file::e_seek eseek)
{

   return m_spfile->seek(offset, eseek);

}


::file::fmtflags stream::setf(::file::fmtflags flagsAdd)
{

   ::file::fmtflags fmtflagsOld = m_fmtflags;

   m_fmtflags = (::file::fmtflags) ((u32) m_fmtflags | (u32) flagsAdd);

   return fmtflagsOld;

}


::file::fmtflags stream::setf(::file::fmtflags flagsAdd, ::file::fmtflags flagsRemove)
{

   ::file::fmtflags fmtflagsOld = m_fmtflags;

   m_fmtflags = (::file::fmtflags) (((u32) m_fmtflags | (u32) flagsAdd) & (~(u32)flagsRemove));

   return fmtflagsOld;

}


::file::fmtflags stream::flags() const
{

   return m_fmtflags;

}


::file::fmtflags stream::flags(::file::fmtflags flags)
{

   return m_fmtflags = flags;

}


file_size_t stream::precision() const
{

   return m_precision;

}

file_size_t stream::precision(file_size_t prec)
{

   return m_precision = prec;

}

file_size_t stream::width() const
{

   return m_width;

}

file_size_t stream::width(file_size_t prec)
{

   return m_width = prec;

}

bool stream::is_open() const
{

   if(m_spfile.is_null())
      return false;

   if(!m_spfile->is_open())
      return false;

   return true;

}



//stream::stream()
//{

//}


//stream::stream(file * pfile):
//   m_spfile(pfile)
//{

//}


//   stream::stream(const stream & stream) :
//      stream(stream)
//   {
//
//   }


//stream::~stream()
//{

//}


//   stream & stream::operator = (const stream & stream)
//   {
//      istream::operator = (stream);
//      ostream::operator = (stream);
//      return *this;
//   }


void stream::close()
{
   //istream::close();
   //ostream::close();

   m_spfile.release();
   //{

   //   flush();

   //   m_spfile->close();

   //   m_spfile.release();

   //}

}




bool stream::is_storing()
{

   return m_spfile->has_write_mode();

}


memory_size_t stream::read(void * lpBuf, memory_size_t nCount)
{

   return m_gcount = m_spfile->read(lpBuf, nCount);

}


string stream::get_object_type_id(::object * pelement)
{

   return System.get_type_info(typeid(*pelement))->m_id;

}


::object * stream::create_object_from_type_id(string strType)
{

   return System.alloc(System.get_type_info((id)strType));
}


void stream::io(void * p, memory_size_t s)
{

   if (is_storing())
   {

      write(p, s);

   }
   else
   {

      memory_size_t iRead = read(p, s);

      if (iRead != s)
      {

         setstate(::file::failbit);

      }

   }

}

void stream::stream_object(simple_object & object)
{

   object.io(*this);

}


void stream::operator()(simple_object & object)
{

   stream_object(object);

}

void stream::operator()(simple_object * pserializable)
{

   stream_object(*pserializable);

}



bool stream::is_version(index i)
{

   return i <= m_iVersion;

}



void simple_object::io(stream & stream)
{

}




void stream::stream_file(::file::path path, ::simple_object & object)
{

   if (path.is_empty())
   {

      throw io_exception(get_app(), "link path is empty");

   }

   serialize stream(get_app());

   UINT nOpenFlags;

   if (is_storing())
   {

      nOpenFlags = ::file::type_binary | ::file::mode_write | ::file::mode_create | ::file::mode_truncate | ::file::defer_create_directory | ::file::share_exclusive;

   }
   else
   {

      nOpenFlags = ::file::type_binary | ::file::mode_read | ::file::share_deny_write;

   }

   stream.m_spfile = Application.file().get_file(path, nOpenFlags);

   stream(object);

}


void stream::stream_link(object & object)
{

   string strLink;

   if (is_storing())
   {

      strLink = object.oprop("read_only_link");

      bool bReadOnly = strLink.has_char();

      operator()(bReadOnly);

      if (!bReadOnly)
      {

         strLink = object.oprop("link");

         //if (strLink.is_empty())
         {

            // throw io_exception(get_app(), "link property is missing");
            //return;

         }

      }

      operator()(strLink);

      if (bReadOnly)
      {

         return;

      }

   }
   else
   {

      bool bReadOnly;

      operator()(bReadOnly);

      operator()(strLink);

      if (bReadOnly)
      {

         object.oprop("read_only_link") = strLink;

      }
      else
      {

         object.oprop("link") = strLink;

      }

   }

   if (strLink.has_char())
   {

      stream_link(strLink, object);

   }

}


void stream::stream_link(string strLink, object & object)
{

   ::file::path path = get_link_path(strLink);

   if (path.is_empty())
   {

      oprop("failed_link").stra().add(strLink);

      return;

   }

   try
   {

      stream_file(path, object);

   }
   catch (...)
   {

      oprop("failed_link").stra().add(strLink);

   }

}

::file::path stream::get_link_path(string strLink)
{

   return "";

}



//namespace file
//{
//
//
//   stream::stream(::aura::application * papp) :
//      ::object(papp),
//      ::stream(papp)
//   {
//
//
//   }
//
//
//   stream::~stream()
//   {
//
//   }
//
//
//   void stream::operator()(void * p, memory_size_t s)
//   {
//
//      if (m_bStoring)
//      {
//
//         m_pfile->write(p, s);
//
//      }
//      else
//      {
//
//         memory_size_t iRead = m_pfile->read(p, s);
//
//         if (iRead != s)
//         {
//
//            throw io_exception(get_app());
//
//         }
//
//      }
//
//   }
//
//
//} // namespace file
//
//
//
void stream::load()
{

   load(get_var_file(), *this);

}

void stream::save()
{

   save(get_var_file(), *this);

}

void stream::load_file()
{

   load(get_file_path(), *this);

}

void stream::save_file()
{

   save(get_file_path(), *this);

}


var stream::get_var_file()
{

   if (oprop("file").is_new())
   {

      oprop("file") = canew(memory_file(get_app()));

   }

   return oprop("file");

}


::file::path stream::get_file_path()
{

   _throw(interface_only_exception(get_app()));

   return "";

}


void stream::load(::file::path path, simple_object & object, UINT nOpenFlags)
{

   ::file::file_sp pfile = Application.file().get_file(path, nOpenFlags);

   if (pfile.is_null())
   {

      return;

   }

   m_spfile = pfile;

   ASSERT(!pfile->has_write_mode());

   if (pfile->has_write_mode())
   {

      return;

   }

   try
   {

      operator()(object);

   }
   catch (...)
   {


   }

   m_spfile.release();

}


void stream::save(::file::path path, simple_object & object, UINT nOpenFlags)
{

   ::file::file_sp pfile = Application.file().get_file(path, nOpenFlags);

   if (pfile.is_null())
   {

      return;

   }

   m_spfile = pfile;

   ASSERT(pfile->has_write_mode());

   if (!pfile->has_write_mode())
   {

      return;

   }

   try
   {

      operator()(object);

   }
   catch (...)
   {


   }

   m_spfile.release();

}


void stream::load_file(::file::path path, simple_object & object, UINT nOpenFlags)
{

   ::file::file_sp pfile = Application.file().get_file(path, nOpenFlags);

   if (pfile.is_null())
   {

      return;

   }

   ASSERT(!pfile->has_write_mode());

   if (pfile->has_write_mode())
   {

      return;

   }

   sp(::memory_file) pmemfile = canew(::memory_file(get_app()));

   oprop("file") = pmemfile;

   pmemfile->full_load(pfile);

   m_spfile = pmemfile;

   try
   {

      operator()(object);

   }
   catch (...)
   {


   }

   m_spfile.release();

   load();


}


void stream::save_file(::file::path path, simple_object & object, UINT nOpenFlags)
{

   ::file::file_sp pfile = Application.file().get_file(path, nOpenFlags);

   if (pfile.is_null())
   {

      return;

   }

   ASSERT(pfile->has_write_mode());

   if (!pfile->has_write_mode())
   {

      return;

   }

   sp(::memory_file) pmemfile = canew(::memory_file(get_app()));

   oprop("file") = pmemfile;

   m_spfile = pmemfile;

   save();

   serialize sdst(pfile);
   serialize ssrc(pmemfile);

   System.file().transfer(sdst, ssrc);

   m_spfile.release();

}


reader::reader(reader && reader) :
   ::object(::move(reader)),
   ::stream(::move(reader))
{

}


reader::reader(::aura::application * papp, index iVersion) :
   ::object(papp),
   ::stream(papp, iVersion)
{

}


reader::reader(::file::file * pfile, index iVersion) :
   ::object(pfile->get_app()),
   ::stream(pfile->get_app(), iVersion)
{

   m_spfile = pfile;

}


reader::~reader()
{

}


bool reader::is_storing()
{

   return false;

}


writer::writer(writer && writer) :
   ::object(::move(writer)),
   ::stream(::move(writer))
{

}


writer::writer(::aura::application * papp, index iVersion) :
   ::object(papp),
   ::stream(papp, iVersion)
{

}



writer::writer(::file::file * pfile, index iVersion) :
   ::object(pfile->get_app()),
   ::stream(pfile->get_app(), iVersion)
{

   m_spfile = pfile;

}


writer::~writer()
{

}



bool writer::is_storing()
{

   return true;

}








memory_reader::memory_reader(memory_reader && reader) :
   object(::move(reader)),
   ::stream(::move(reader)),
   ::reader(::move(reader))
{


}


memory_reader::memory_reader(::aura::application * papp, index iVersion) :
   object(papp),
   ::stream(papp, iVersion),
   ::reader(papp, iVersion)
{

   m_spfile = canew(memory_file(papp));

}


memory_reader::~memory_reader()
{

}


memory & memory_reader::get_memory()
{

   return *m_spfile.cast < ::memory_file >()->get_primitive_memory();

}


memory_writer::memory_writer(memory_writer && reader) :
   object(::move(reader)),
   ::stream(::move(reader)),
   ::writer(::move(reader))
{


}


memory_writer::memory_writer(::aura::application * papp, index iVersion) :
   object(papp),
   ::stream(papp, iVersion),
   ::writer(papp, iVersion)
{

   m_spfile = canew(memory_file(papp));

}


memory_writer::~memory_writer()
{

}


memory & memory_writer::get_memory()
{

   return *m_spfile.cast < ::memory_file >()->get_primitive_memory();

}


bool stream::is_stream_null()
{
   //return is_writer_null() && is_reader_null();
   return m_spfile.is_null();
}

bool stream::is_stream_set()
{
   //return is_writer_set() || is_reader_set();
   return m_spfile.is_set();
}

#include "framework.h"



void stream::write_from_hex(const void *lpBuf, memory_size_t nCount)
{

   m_spfile->write_from_hex(lpBuf, nCount);

}


void stream::write(const void *lpBuf, memory_size_t nCount)
{

   m_spfile->write(lpBuf, nCount);

}

void stream::write(const void *lpBuf, memory_size_t nCount, memory_size_t * dwWritten)
{

   m_spfile->write(lpBuf, nCount, dwWritten);

}


void stream::write(bool b)
{

   oblt(b);

}

void stream::write(char ch)
{

   oblt(ch);

}


void stream::write(uchar uch)
{

   oblt(uch);

}


void stream::write(int16_t i)
{

   oblt(i);

}


void stream::write(uint16_t ui)
{

   oblt(ui);

}


#ifdef WINDOWS


void stream::write(unichar wch)
{

   oblt(wch);

}


#endif


//   void stream:: write (int32_t i)
//   {
//
//      oblt(i);
//
//   }
//
//
//   void stream:: write (u32 ui)
//   {
//
//      oblt(ui);
//
//   }
//
//
//   void stream:: write (i64 i)
//   {
//
//      oblt(i);
//
//   }
//
//   void stream:: write (u64 ui)
//   {
//
//      oblt(ui);
//
//   }

#ifdef APPLEOS

void stream::write(unsigned long ui)
{

   oblt(ui);

}

#endif


void stream::write(i32 i)
{

   oblt(i);

}


void stream::write(u32 ui)
{

   oblt(ui);

}


//   void stream::write(uint64_t ui, int signal)
//   {
//
//
//   }

void stream::write(int64_t i)
{

   oblt(i);

}


void stream::write(uint64_t ui)
{

   oblt(ui);

}


void stream::write(float f)
{

   oblt(f);

}


void stream::write(double d)
{

   oblt(d);

}


void stream::write(RECT & rect)
{

   oblt(rect);

}


void stream::write(LPRECT lpcrect)
{

   oblt(*lpcrect);

}


void stream::write(SIZE & size)
{

   oblt(size);

}


void stream::write(sp(type) & info)
{

   string str(info->m_id);

   write(str);

}


void stream::write(std_type_info & info)
{

   write(System.get_type_info(info));

}


void stream::write(const char * psz)
{

}


#ifdef WINDOWS


void stream::write(const unichar * psz)
{

}


#endif


void stream::write(id & id)
{

}


void stream::write(var & var)
{

   var.io(*this);

}


void stream::write(property & property)
{

}


void stream::flush()
{

   if (m_spfile.is_set())
   {

      m_spfile->flush();

   }

}


bool stream::is_writer_null()
{

   return m_spfile.is_null();

}


bool stream::is_writer_set()
{

   return m_spfile.is_set();

}


void stream::write(string & str)
{

   write(str.c_str(), str.get_length());

}


void stream::write(simple_object * pobject)
{

   pobject->io(*this);

}


void stream::write(simple_object & object)
{

   object.io(*this);

}


void stream::set_length(file_size_t len)
{

   m_spfile->set_length(len);

}

stream & stream::put(char ch)
{
   write(ch);
   return *this;
}

//} // namespace file






void stream::full_read(void * lpBuf, memory_size_t nCount)
{

   if (fail())
   {

      return;

   }


   if (!m_spfile->full_read(lpBuf, nCount))
   {

      setstate(::file::failbit);

      return;

   }



   m_gcount = nCount;

}


void stream::full_fill(::primitive::memory_base & m)
{

   full_read(m.get_data(), m.get_size());

}

//void stream::read(int32_t & i)
//{
//
//
//}
//
//void stream::read(uint32_t & ui)
//{
//
//
//}
//
//void stream::read(int64_t & i)
//{
//
//
//}
//
//void stream::read(uint64_t & ui)
//{
//
//
//}


void stream::read(bool & b)
{

   iblt(b);

}


void stream::read(char & ch)
{

   iblt(ch);

}


void stream::read(uchar & uch)
{

   iblt(uch);

}


#ifdef WINDOWS


void stream::read(unichar & wch)
{

   iblt(wch);

}


#endif


void stream::read(int16_t & sh)
{

   iblt(sh);

}


void stream::read(uint16_t & ui)
{

   iblt(ui);

}


void stream::read(int32_t & i)
{

   iblt(i);

}


void stream::read(uint32_t & ui)
{

   iblt(ui);

}


void stream::read(int64_t & i)
{

   iblt(i);

}


void stream::read(uint64_t & ui)
{

   iblt(ui);

}


#ifdef APPLEOS

void stream::read(unsigned long & ui)
{

   iblt(ui);

}

#endif


void stream::read(float & f)
{

   iblt(f);

}


void stream::read(double & d)
{

   iblt(d);

}


void stream::read(LPRECT lprect)
{

   iblt(*lprect);

}


void stream::read(SIZE & size)
{

   iblt(size);

}


void stream::read(sp(type) & info)
{

   string str;

   read(str);

   info = System.get_type_info((id)str);

}


void stream::read(id & id)
{

   UNREFERENCED_PARAMETER(id);

   ::exception::throw_interface_only(get_app());

}


void stream::read(var & var)
{

   var.io(*this);

}


void stream::read(property & property)
{
   UNREFERENCED_PARAMETER(property);
   ::exception::throw_interface_only(get_app());
}


void stream::read(string & str)
{


}


void stream::read(simple_object * pobject)
{

   pobject->io(*this);

}


void stream::read(simple_object & object)
{

   object.io(*this);

}

void * stream::get_internal_data()
{

   return m_spfile->get_internal_data();

}


memory_size_t stream::get_internal_data_size() const
{

   return m_spfile->get_internal_data_size();

}


bool stream::set_internal_data_size(memory_size_t c)
{

   return m_spfile->set_internal_data_size(c);

}


file_position_t stream::get_position() const
{

   return m_spfile->get_position();

}

int stream::get()
{
   unsigned char uch;

   if (read(&uch, 1) == 1)
      return uch;

   return EOF;

}


int stream::peek()
{
   unsigned char uch;

   if (read(&uch, 1) == 1)
   {
      seek(-1, ::file::seek_current);
      return uch;
   }

   return EOF;

}

stream & stream::getline(char * sz, strsize n)
{
   int c;
   while (n > 0)
   {
      c = get();
      if (c == EOF)
      {
         break;
      }
      else if (c == '\n')
      {
         c = get();
         if (c != '\r' && c != EOF)
            seek(-1, ::file::seek_current);
         break;
      }
      else if (c == '\r')
      {
         c = get();
         if (c != '\n' && c != EOF)
            seek(-1, ::file::seek_current);
         break;
      }
      *sz = (char)c;
      sz++;
      n--;
   }

   return *this;

}


bool stream::is_reader_null()
{

   return m_spfile.is_null() || !(m_spfile->m_nOpenFlags & ::file::mode_read);

}


bool stream::is_reader_set()
{

   return m_spfile.is_set() && (m_spfile->m_nOpenFlags & ::file::mode_read);

}


void stream::read_to_hex(string & str, file_position_t dwStart, file_position_t dwEnd)
{
   memory memory(get_app());
#if MEMDLEAK
   memory.m_strTag = "memory://member=stream::read_to_hex";
#endif
   if (dwStart == (file_position_t)-1)
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

   while ((uiRead = read(&memory.get_data()[uiPos], MIN(memory.get_size() - uiPos, (memory_size_t)nCount))) > 0)
   {
      uiPos += uiRead;
      nCount -= uiRead;
      if (memory.get_size() - uiPos <= 0)
      {
         memory.allocate_add_up(1024 * 1024);
      }
   }
   memory.allocate((memory_size_t)uiPos);
   memory.to_hex(str);
}





