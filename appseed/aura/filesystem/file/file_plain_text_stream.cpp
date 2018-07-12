#include "framework.h"


namespace file
{


   plain_text_stream::plain_text_stream()
   {

   }


   plain_text_stream::plain_text_stream(file * pfile) :
      stream(pfile)
   {

   }


   plain_text_stream::~plain_text_stream()
   {

   }


   bool plain_text_stream::is_stream_null()
   {

      return is_writer_null() && is_reader_null();

   }


   bool plain_text_stream::is_stream_set()
   {

      return is_writer_set() || is_reader_set();

   }


   void plain_text_stream::close()
   {

      stream::close();

   }


   plain_text_stream_memory_file::plain_text_stream_memory_file(::aura::application * papp) :
      object(papp),
      memory_container(papp),
      memory_file(papp)
   {

      m_spfile = (memory_file *) this;

   }


   plain_text_stream_memory_file::~plain_text_stream_memory_file()
   {


   }


   file_position_t plain_text_stream_memory_file::seek(file_offset_t offset, e_seek seekOrigin)
   {

      return memory_file::seek(offset, seekOrigin);

   }


   file_position_t plain_text_stream_memory_file::get_position() const
   {

      return memory_file::get_position();

   }


   void plain_text_stream_memory_file::flush()
   {

      memory_file::flush();

   }


   void * plain_text_stream_memory_file::get_internal_data()
   {

      return memory_file::get_internal_data();

   }


   const void * plain_text_stream_memory_file::get_internal_data() const
   {

      return memory_file::get_internal_data();

   }


   memory_size_t plain_text_stream_memory_file::get_internal_data_size() const
   {

      return memory_file::get_internal_data_size();

   }

   bool plain_text_stream_memory_file::set_internal_data_size(memory_size_t s)
   {

      return memory_file::set_internal_data_size(s);

   }

   void plain_text_stream_memory_file::write(const void * p, memory_size_t s)
   {

      memory_file::write(p, s);

   }


   memory_size_t plain_text_stream_memory_file::read(void * p, memory_size_t s)
   {

      return memory_file::read(p, s);

   }


   void plain_text_stream_memory_file::set_length(file_size_t dwNewLen)
   {

      memory_file::set_length(dwNewLen);

   }


   void plain_text_stream_memory_file::close()
   {

      plain_text_stream::close();

   }




   // string file


   plain_text_stream_string_file::plain_text_stream_string_file()
   {

      m_spfile = (string_file *) this;

   }


   plain_text_stream_string_file::~plain_text_stream_string_file()
   {

   }

   file_position_t plain_text_stream_string_file::seek(file_offset_t offset, e_seek seekOrigin)
   {

      return string_file::seek(offset, seekOrigin);

   }


   file_position_t plain_text_stream_string_file::get_position() const
   {

      return string_file::get_position();

   }


   void plain_text_stream_string_file::flush()
   {

      string_file::flush();

   }


   void plain_text_stream_string_file::write(const void * p, memory_size_t s)
   {

      string_file::write(p, s);

   }


   memory_size_t plain_text_stream_string_file::read(void * p, memory_size_t s)
   {

      return string_file::read(p, s);

   }

   void plain_text_stream_string_file::set_length(file_size_t dwNewLen)
   {

      plain_text_stream::set_length(dwNewLen);

   }


   void plain_text_stream_string_file::close()
   {

      plain_text_stream::close();

   }




   plain_text_stream_string::plain_text_stream_string()
   {

   }


   plain_text_stream_string::~plain_text_stream_string()
   {

   }


} // namespace file





















namespace file
{


   void plain_text_stream::write(bool b)
   {
      if (b)
         raw_print("true");
      else
         raw_print("false");
   }

   void plain_text_stream::write(char ch)
   {
      m_spfile->write(&ch, sizeof(ch)); // treat as char - character

   }

   void plain_text_stream::write(uchar uch)
   {
      write((uint32_t)uch);
   }

   void plain_text_stream::write(int16_t i)
   {
      write((int32_t)i);
   }

   void plain_text_stream::write(uint16_t ui)
   {
      write((uint32_t)ui);
   }
#ifdef WINDOWS
   void plain_text_stream::write(unichar wch)
   {
      raw_print(::str::uni_to_utf8(wch));
   }
#endif


   void plain_text_stream::print_number(const string & str)
   {

      auto estrflag = m_estrflag;

      if (estrflag & str_flag_ifnumberparenthesize)
      {

         raw_print("(");

      }

      raw_print(str);

      if (estrflag & str_flag_ifnumberparenthesize)
      {

         raw_print(")");

      }

      if (estrflag & str_flag_ifnumberspace)
      {

         raw_print(" ");

      }

   }


   void plain_text_stream::write(int32_t i)
   {

      print_number(::str::from(i));

   }


   void plain_text_stream::write(uint32_t ui)
   {

      print_number(::str::from(ui));

   }


   void plain_text_stream::write(int64_t i)
   {

      print_number(::str::from(i));

   }

   void plain_text_stream::write(uint64_t ui)
   {

      print_number(::str::from(ui));

   }


   void plain_text_stream::write(float f)
   {

      string str;

      str.Format("%f", f);

      print_number(str);

   }


   void plain_text_stream::write(double d)
   {

      string str;

      str.Format("%f", d);

      print_number(::str::from(d));

   }


   void plain_text_stream::write(const RECT & rect)
   {

      m_estrflag = (e_str_flag)((int)m_estrflag  & ~(int)str_flag_ifnumberparenthesizeandspace);
      write(rect.left);
      write(rect.top);
      write(rect.right);
      write(rect.bottom);

   }


   void plain_text_stream::write(LPCRECT lpcrect)
   {

      write(*lpcrect);

   }


   void plain_text_stream::write(const SIZE & size)
   {

      m_estrflag = (e_str_flag)((int)m_estrflag  & ~(int)str_flag_ifnumberparenthesizeandspace);
      write(size.cx);
      write(size.cy);

   }


   void plain_text_stream::write(const sp(type) info)
   {

      raw_print(info->friendly_name());

   }


   void plain_text_stream::write(const std_type_info & info)
   {

      raw_print(demangle(info.name()));


   }


   void plain_text_stream::write(const char * psz)
   {

      if (psz == NULL)
      {

         return;

      }

      write(psz, strlen(psz));

   }


   void plain_text_stream::raw_print(const string & str)
   {

      write(str.c_str(), str.size());

      m_estrflag = (e_str_flag)((int)m_estrflag  & ~(int)str_flag_ifnumberparenthesize);

   }


} // namespace core


void replace_char(char * sz, char ch1, char ch2)
{

   while (*sz)
   {

      if (*sz == ch1)
      {

         *sz = ch2;

      }

      sz++;

   }

}


plain_text_stream_log_line::plain_text_stream_log_line(e_level elevel, const char * pszTag, const char * pszFile, int iLine)
{

   m_elevel = elevel;
   m_strTag = pszTag;
   m_strFile = pszFile;
   m_iLine = iLine;
   m_pfile = canew(::file::string_file);
   m_spfile = m_pfile;

}

plain_text_stream_log_line::~plain_text_stream_log_line()
{

   m_strTag.replace("::", ".");
   m_strTag.replace(":", "_");
   m_strTag.replace("(", "");
   m_strTag.replace(")", "");

   m_pfile->m_str.replace("::", ".");
   m_pfile->m_str.replace(":", "_");

   m_strFile.replace(":", "_");

   ::str::begins_eat_ci(m_pfile->m_str, m_strTag);

   ::trace(m_elevel, m_strTag, m_pfile->m_str, m_strFile, m_iLine);

}











namespace file
{

   void plain_text_stream::read(bool & b)
   {
      m_spfile->read(&b, sizeof(b));

   }

   void plain_text_stream::read(char & ch)
   {
      m_spfile->read(&ch, sizeof(ch));

   }

   void plain_text_stream::read(uchar & uch)
   {
      m_spfile->read(&uch, sizeof(uch));

   }
#ifdef WINDOWS
   void plain_text_stream::read(unichar & wch)
   {
      m_spfile->read(&wch, sizeof(wch));

   }
#endif
   void plain_text_stream::read(int16_t & sh)
   {
      m_spfile->read(&sh, sizeof(sh));

   }

   void plain_text_stream::read(uint16_t & ui)
   {
      m_spfile->read(&ui, sizeof(ui));

   }

   void plain_text_stream::read(int32_t & i)
   {
      uint64_t uiRead = m_spfile->read(&i, sizeof(i));
      if (uiRead != sizeof(i))
         _throw(simple_exception(get_app(), "failed to read int32_t"));

   }

   void plain_text_stream::read(uint32_t & ui)
   {
      uint64_t uiRead = m_spfile->read(&ui, sizeof(ui));
      if (uiRead != sizeof(ui))
         _throw(simple_exception(get_app(), "failed to read uint32_t"));

   }

   void plain_text_stream::read(int64_t & i)
   {
      m_spfile->read(&i, sizeof(i));

   }

   void plain_text_stream::read(uint64_t & ui)
   {
      m_spfile->read(&ui, sizeof(ui));

   }

   void plain_text_stream::read(float & f)
   {
      m_spfile->read(&f, sizeof(f));

   }

   void plain_text_stream::read(double & d)
   {
      m_spfile->read(&d, sizeof(d));

   }

   void plain_text_stream::read(LPRECT lprect)
   {
      m_spfile->read(&lprect->left, sizeof(lprect->left));
      m_spfile->read(&lprect->top, sizeof(lprect->top));
      m_spfile->read(&lprect->right, sizeof(lprect->right));
      m_spfile->read(&lprect->bottom, sizeof(lprect->bottom));

   }

   void plain_text_stream::read(SIZE & size)
   {
      m_spfile->read(&size.cx, sizeof(size.cx));
      m_spfile->read(&size.cy, sizeof(size.cy));

   }

   void plain_text_stream::read(sp(type) info)
   {
      {
         int32_t iLen;
         m_spfile->read(&iLen, sizeof(iLen));
         char * psz = (char *)malloc(iLen + 1);
         m_spfile->read(psz, iLen);
         psz[iLen] = '\0';
         info->m_id = psz;
         free((void *)psz);
      }
      {
         int32_t iLen;
         m_spfile->read(&iLen, sizeof(iLen));
         char * psz = (char *)malloc(iLen + 1);
         m_spfile->read(psz, iLen);
         psz[iLen] = '\0';
         info->m_idFriendly = psz;
         free((void *)psz);
      }

   }


   string plain_text_stream::get_location() const
   {

      return "<unknown plain_text_stream location>";

   }


   //   istream & plain_text_stream::operator = (const istream & istream)
   //   {
   //
   //      return istream::operator = (istream);
   //
   //   }








} // namespace core

