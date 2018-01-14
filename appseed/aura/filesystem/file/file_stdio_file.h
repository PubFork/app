#pragma once


namespace file
{


   class CLASS_DECL_AURA stdio_file:
      virtual public ::file::file
   {
      public:


         FILE *        m_pfile;


         stdio_file();
         stdio_file(const char * lpszFileName,UINT nOpenFlags);
         virtual ~stdio_file();


         virtual void assert_valid() const override;
         virtual void dump(dump_context & dumpcontext) const override;




         virtual file_position_t get_position() const override;
         virtual bool GetStatus(file_status& rStatus) const override;
         virtual string GetFileName() const override;
         virtual string GetFileTitle() const override;
         virtual string GetFilePath() const override;
         //virtual void SetFilePath(const char * lpszNewName);


         virtual cres open(const ::file::path & lpszFileName,UINT nOpenFlags) override;

         //virtual bool GetStatus(const char * lpszFileName,file_status& rStatus);
         //virtual void SetStatus(const char * lpszFileName,const file_status& status);


         virtual ::file::file_sp  Duplicate() const override;

         virtual file_position_t seek(file_offset_t lOff,::file::e_seek  nFrom) override;
         virtual void set_length(file_size_t dwNewLen) override;
         virtual file_size_t get_length() const override;

         virtual void LockRange(file_position_t dwPos,file_size_t dwCount) override;
         virtual void UnlockRange(file_position_t dwPos,file_size_t dwCount) override;

         virtual void Abort() override;
         virtual void flush() override;
         virtual void close() override;


         virtual memory_size_t read(void *lpBuf,memory_size_t nCount) override;
         virtual void write(const void * lpBuf,memory_size_t nCount) override;
         virtual string get_location() const override;

         virtual bool IsOpened() override;
         virtual bool is_open() override;
         virtual uint64_t GetBufferPtr(UINT nCommand,uint64_t nCount = 0,void ** ppBufStart = NULL,void ** ppBufMax = NULL) override;


         /*using ::file::writer::write;
         void write(ostream & ostream);


         using ::file::reader::read;
         void read(istream & istream);*/


         /*virtual bool read(char * pch);
         virtual bool read(uchar * puch);
         virtual bool peek(char * pch);
         virtual bool peek(uchar * puch);
         virtual bool read(char & ch);
         virtual bool read(uchar & uch);
         virtual bool peek(char & ch);
         virtual bool peek(uchar & uch);
         virtual int sgetc();
         virtual int sbumpc();
         virtual bool read_string(string & str);
         virtual bool full_read_string(string & str);*/


         //void writef(const char *format,...);

         /** Common interface for write used by Tcp and Udp sockets. */
         //      virtual void write(const void *, memory_size_t c);

         /** Common interface for Send used by Tcp and Udp sockets. */
         //virtual void write(const string &);



   };



} // namespace file






