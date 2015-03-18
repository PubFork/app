#pragma once


/////////////////////////////////////////////////////////////////////////////
// STDIO file implementation


namespace linux
{


   class stdio_file :
      virtual public ::linux::file,
      virtual public ::file::text_buffer
   {
   public:


      FILE* m_pStream;    // stdio FILE
      // m_hFile from aura class is _fileno(m_pStream)



      stdio_file(sp(::aura::application) papp);
      virtual ~stdio_file();

      virtual void write_string(const char * lpsz);
      virtual char * read_string(char * lpsz, UINT nMax);
      virtual bool read_string(string & rString);


      void dump(dump_context & dumpcontext) const;
      virtual file_position get_position() const;
      virtual cres open(const ::file::path & lpszFileName, UINT nOpenFlags);
      virtual ::primitive::memory_size read(void * lpBuf, ::primitive::memory_size nCount);
      virtual void write(const void * lpBuf, ::primitive::memory_size nCount);
      virtual file_position seek(file_offset lOff, ::file::e_seek nFrom);
      virtual void Abort();
      virtual void Flush();
      virtual void close();
      virtual file_size get_length() const;

      // Unsupported APIs
      virtual sp(::file::stream_buffer) Duplicate() const;
      virtual void LockRange(file_position dwPos, file_size dwCount);
      virtual void UnlockRange(file_position dwPos, file_size dwCount);


   };



} // namespace linux


