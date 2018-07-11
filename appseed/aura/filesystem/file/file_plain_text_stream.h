#pragma once


#include "file_memory_file.h"
#include "file_string_file.h"


namespace file
{

   class string_file;
   
   
   typedef sp(string_file) string_file_sp;

   class CLASS_DECL_AURA plain_text_stream :
      virtual public ::serialize
   {
   public:


      plain_text_stream();
      plain_text_stream(file * pbuffer);
//      plain_text_stream(const stream & stream);
      virtual ~plain_text_stream();


//      stream & operator = (const stream & stream);

      virtual bool is_stream_null();
      virtual bool is_stream_set();

      virtual void close();

//      plain_text_ostream();
//      plain_text_ostream(file * pwriter);
//      plain_text_ostream(const ostream & ostream);
//      virtual ~plain_text_ostream();
      
      using serialize::write;
      virtual void write (bool b);
      virtual void write (char ch);
      virtual void write (uchar uch);
#ifdef WINDOWS
      virtual void write (unichar wch);
#endif
      virtual void write (int16_t sh);
      virtual void write (uint16_t ui);
      virtual void write (int32_t i);
      virtual void write (uint32_t ui);
      virtual void write (int64_t i);
      virtual void write (uint64_t ui);
      virtual void write (float f);
      virtual void write (double d);
      virtual void write (const RECT & rect);
      virtual void write (LPCRECT lpcrect);
      virtual void write (const SIZE & size);
      virtual void write (const sp(type) info);
      virtual void write (const std_type_info & info);
      virtual void write (const char * psz);
      
      virtual void raw_print(const string & str);
      virtual void print_number(const string & str);
      
      virtual ::string get_location() const;
      
      //ostream & operator = (const ostream & ostream);
      
      operator void * ()
      {
         return this;
      }

      using serialize::read;
      virtual void read (bool & b);
      virtual void read (char & ch);
      virtual void read (uchar & uch);
#ifdef WINDOWS
      virtual void read (unichar & wch);
#endif
      virtual void read (int16_t & sh);
      virtual void read (uint16_t & ui);
      virtual void read (int32_t & i);
      virtual void read (uint32_t & ui);
      virtual void read (int64_t & i);
      virtual void read (uint64_t & ui);
      virtual void read (float & f);
      virtual void read (double & d);
      virtual void read (LPRECT lprect);
      virtual void read (SIZE & size);
      virtual void read (sp(type) info);
      
      //virtual ::string get_location() const;
      
      //istream & operator = (const istream & istream);
      
//      operator void * ()
//      {
//         return this;
//      }


   };


   class CLASS_DECL_AURA plain_text_stream_memory_file :
      virtual public plain_text_stream,
      virtual public memory_file
   {
   public:


      plain_text_stream_memory_file(::aura::application * papp);
      virtual ~plain_text_stream_memory_file();

      virtual file_position_t seek(file_offset_t offset, e_seek seekOrigin);
      virtual file_position_t get_position() const;
      virtual void flush();
      virtual void * get_internal_data();
      virtual const void * get_internal_data() const;
      virtual memory_size_t get_internal_data_size() const;
      virtual bool set_internal_data_size(memory_size_t s);
      virtual void write(const void * p, memory_size_t s);
      virtual memory_size_t read(void * p, memory_size_t s);
      virtual void set_length(file_size_t dwNewLen);
      virtual void close();

   };


   class CLASS_DECL_AURA plain_text_stream_string_file :
      virtual public plain_text_stream,
      virtual public string_file
   {
   public:


      plain_text_stream_string_file();
      virtual ~plain_text_stream_string_file();

      virtual file_position_t seek(file_offset_t offset, e_seek seekOrigin);
      virtual file_position_t get_position() const;
      virtual void flush();
      virtual void write(const void * p, memory_size_t s);
      virtual memory_size_t read(void * p, memory_size_t s);
      virtual void set_length(file_size_t dwNewLen);
      virtual void close();

   };


   class CLASS_DECL_AURA plain_text_stream_string :
      virtual public plain_text_stream_string_file
   {
   public:

      plain_text_stream_string();
      virtual ~plain_text_stream_string();


   };

} // namespace file


using std_string_stream = ::file::plain_text_stream;





class CLASS_DECL_AURA plain_text_stream_log_line :
virtual public ::file::plain_text_stream
{
public:
   
   
   ::file::string_file_sp   m_pfile;
   e_level                    m_elevel;
   string                     m_strTag;
   string                     m_strFile;
   int                        m_iLine;
   
   
   plain_text_stream_log_line(e_level elevel, const char * pszTag, const char * pszFile = NULL, int iLine = -1);
   virtual ~plain_text_stream_log_line();
   
};

