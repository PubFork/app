#pragma once


namespace file
{


   class exception;
   struct file_status;


   class CLASS_DECL_AURA binary_file :
      virtual public ::file::file
   {
   public:


      binary_file();
      virtual ~binary_file();


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;



      virtual file_position_t get_position() const override;
      virtual bool GetStatus(file_status& rStatus) const override;
      virtual string GetFileName() const override;
      virtual string GetFileTitle() const override;
      virtual string GetFilePath() const override;
      virtual void SetFilePath(const char * lpszNewName) override;


      // Operations
      virtual cres open(const ::file::path & lpszFileName,UINT nOpenFlags) override;

      //virtual void Rename(const char * lpszOldName, const char * lpszNewName);
      //virtual void remove(const char * lpszFileName);
      //virtual bool GetStatus(const ::file::path & lpszFileName,file_status& rStatus);
      //virtual void SetStatus(const ::file::path & * lpszFileName,const file_status& status);


      // Overridables
      virtual ::file::file_sp  Duplicate() const override;

      virtual file_position_t seek(file_offset_t lOff, ::file::e_seek  nFrom) override;
      virtual void set_length(file_size_t dwNewLen) override;
      virtual file_size_t get_length() const override;

      virtual void LockRange(file_position_t dwPos, file_size_t dwCount) override;
      virtual void UnlockRange(file_position_t dwPos, file_size_t dwCount) override;

      virtual void Abort() override;
      virtual void flush() override;
      virtual void close() override;


      // io_stream
      virtual memory_size_t read(void *lpBuf, memory_size_t nCount) override;
      virtual void write(const void * lpBuf, memory_size_t nCount) override;
      virtual string get_location() const override;


      virtual bool IsOpened() override;

      virtual uint64_t GetBufferPtr(UINT nCommand, uint64_t nCount = 0, void ** ppBufStart = NULL, void ** ppBufMax = NULL) override;



      using ::file::file::write;
      virtual void write(serialize & ostream) override;


      using ::file::file::read;
      virtual void read(serialize & istream) override;


      //virtual bool read_string(string & str);



   };


   typedef smart_pointer < binary_file > binary_buffer_sp;

   inline void binary_file::SetFilePath(const char * lpszNewName)
   {
      UNREFERENCED_PARAMETER(lpszNewName);
   }



} // namespace file






