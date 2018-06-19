#pragma once




namespace file
{


   class string_file;


   typedef sp(string_file) string_file_sp;


   class CLASS_DECL_AURA string_file :
      virtual public ::file::file
   {
   public:

      string         m_str;
      strsize        m_iPos;

      string_file();
      string_file(::aura::application * papp);
      string_file(const string & str);
      string_file(const string_file & str);
      virtual ~string_file();


      using ::file::reader::read;
      virtual memory_size_t read(void *lpBuf, memory_size_t nCount);
      void read(istream & istream);


      using ::file::writer::write;
      virtual void write(const void *lpBuf, memory_size_t nCount);
      void write(ostream & ostream);

      ::string str() const;

      virtual void flush();

      virtual void close();

      bool is_empty() const
      {

         return m_str.is_empty();

      }




      file_size_t get_length() const
      {
         return m_str.get_length();
      }


      virtual file_position_t get_position() const;

      void destroy();
      //void alloc(strsize iSize);

      //void alloc_up(strsize iAtLeast);

      void set(const char * psz,strsize len);

      void set(const string & str)
      {
         set(str, str.length());
      }


      void append(const char * psz,strsize len);

      void append(const string & str)
      {
         append(str, str.length());
      }



      operator const char *() const
      {
         return m_str;
      }

      string & to_string(string &str) const
      {

         str = m_str;

         return str;

      }

      string_file & operator += (const string & str)
      {
         append(str);
         return *this;
      }

      string_file & operator = (const string & str)
      {
         set(str);
         return *this;
      }

   };


} // namespace file



