#pragma once


namespace file
{


   class CLASS_DECL_AURA composite :
      virtual public ::file::file
   {
      public:



         ::file::file_sp      m_spfile;


         composite();
         composite(::file::file_sp  pfile);
         virtual ~composite();


#ifdef DEBUG
         virtual void assert_valid() const override;
         virtual void dump(dump_context & dumpcontext) const override;
#endif



         virtual file_position_t get_position() const override;
         virtual bool GetStatus(file_status& rStatus) const override;
         virtual ::string GetFileName() const override;
         virtual ::string GetFileTitle() const override;
         virtual ::string GetFilePath() const override;
         virtual void SetFilePath(const char * lpszNewName) override;


         virtual cres open(const ::file::path & lpszFileName,UINT nOpenFlags) override;

         //virtual void Rename(const char * lpszOldName, const char * lpszNewName);
         //virtual void remove(const char * lpszFileName);
         //virtual bool GetStatus(const char * lpszFileName, file_status& rStatus);
         //virtual void SetStatus(const char * lpszFileName, const file_status& status);


         virtual ::file::file_sp  Duplicate() const override;

         virtual file_position_t seek(file_offset_t lOff, ::file::e_seek  nFrom) override;
         virtual void set_length(file_size_t dwNewLen) override;
         virtual file_size_t get_length() const override;

         virtual void LockRange(file_position_t dwPos, file_size_t dwCount) override;
         virtual void UnlockRange(file_position_t dwPos, file_size_t dwCount) override;

         virtual void Abort() override;
         virtual void flush() override;
         virtual void close() override;


         virtual memory_size_t read(void *lpBuf, memory_size_t nCount) override;
         virtual void write(const void * lpBuf, memory_size_t nCount) override;
         virtual ::string get_location() const override;


         virtual bool IsOpened() override;

         virtual uint64_t GetBufferPtr(UINT nCommand, uint64_t nCount = 0, void ** ppBufStart = NULL, void ** ppBufMax = NULL) override;


         using ::file::file::write;
         void write(ostream & ostream);


         using ::file::file::read;
         void read(istream & istream);



   };


} // namespace file


