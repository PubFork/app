#include "framework.h"


namespace file
{


   plain_text_stream::plain_text_stream()
   {
   }

   plain_text_stream::plain_text_stream(file * pwriter)
   {
      m_spfile = pwriter;
   }

//   plain_text_stream::plain_text_stream(const ostream & ostream)
//   {
//      m_spfile = ostream.m_spfile;
//   }

   plain_text_stream::~plain_text_stream()
   {

   }

   void plain_text_stream:: write (bool b)
   {
      if(b)
         raw_print("true");
      else
         raw_print("false");
   }

   void plain_text_stream:: write (char ch)
   {
      m_spfile->write(&ch, sizeof(ch)); // treat as char - character

   }

   void plain_text_stream:: write (uchar uch)
   {
      write ((uint32_t) uch);
   }

   void plain_text_stream:: write (int16_t i)
   {
      write ((int32_t) i);
   }

   void plain_text_stream:: write (uint16_t ui)
   {
      write ((uint32_t) ui);
   }
#ifdef WINDOWS
   void plain_text_stream:: write (unichar wch)
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


   void plain_text_stream:: write (int32_t i)
   {

      print_number(::str::from(i));

   }


   void plain_text_stream:: write (uint32_t ui)
   {

      print_number(::str::from(ui));

   }


   void plain_text_stream:: write (int64_t i)
   {

      print_number(::str::from(i));

   }

   void plain_text_stream:: write (uint64_t ui)
   {

      print_number(::str::from(ui));

   }


   void plain_text_stream:: write (float f)
   {

      string str;

      str.Format("%f", f);

      print_number(str);

   }


   void plain_text_stream:: write (double d)
   {

      string str;

      str.Format("%f", d);

      print_number(::str::from(d));

   }


   void plain_text_stream:: write (const RECT & rect)
   {

      m_estrflag = (e_str_flag)((int)m_estrflag  & ~(int)str_flag_ifnumberparenthesizeandspace);
      write (rect.left);
      write (rect.top);
      write (rect.right);
      write (rect.bottom);

   }


   void plain_text_stream:: write(LPCRECT lpcrect)
   {

      write(*lpcrect);

   }


   void plain_text_stream:: write (const SIZE & size)
   {

      m_estrflag = (e_str_flag)((int)m_estrflag  & ~(int)str_flag_ifnumberparenthesizeandspace);
      write (size.cx);
      write (size.cy);

   }


   void plain_text_stream:: write (const sp(type) info)
   {

      raw_print(info->friendly_name());

   }


   void plain_text_stream::write(const std_type_info & info)
   {

      raw_print(demangle(info.name()));


   }


   void plain_text_stream:: write (const char * psz)
   {

      if (psz == NULL)
      {

         return;

      }

      write(psz, strlen(psz));

   }


   string plain_text_stream::get_location() const
   {

      return "<unknown plain_text_stream location>";

   }


   void plain_text_stream::raw_print(const string & str)
   {

      write(str.c_str(), str.size());

      m_estrflag = (e_str_flag) ((int)m_estrflag  & ~(int)str_flag_ifnumberparenthesize);

   }

//   ostream & plain_text_stream::operator = (const ostream & ostream)
//   {
//
//      return ostream::operator = (ostream);
//
//   }

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
