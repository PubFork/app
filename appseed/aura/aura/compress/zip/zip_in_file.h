#pragma once


namespace zip
{


   class file;


   class CLASS_DECL_AURA in_file:
      public ::file::binary_file,
      virtual public ::file::listing_provider
   {
      public:


         enum e_mode
         {

            mode_undefined,
            mode_zip,
            mode_unzip

         };

         enum BufferCommand
         {

            bufferRead,
            bufferWrite,
            bufferCommit,
            bufferCheck

         };


         unz_file_info        m_fi;
         string               m_strFileName;
         uint64_t             m_iPosition;
         stringa              m_straPath;
         spa(::zip::file)     m_filea;
         spa(::zip::in_file)  m_infilea;
         stringa              m_straPrefix;
         e_mode               m_emode;
         string               m_strZipFile;


         in_file(::aura::application * papp);
         virtual ~in_file();


#ifdef DEBUG
         virtual void assert_valid() const override;
         virtual void dump(dump_context & dumpcontext) const override;
#endif




         virtual file_position_t get_position() const override;

         virtual bool zip_open(const char *,UINT);
         virtual bool zip_open(::zip::file * pzfile,const char * lpcszFileName);

         virtual bool unzip_open(::file::file * pfile, int iBufferLevel = 2);
         virtual bool unzip_open(::zip::file * pzfile,const char * lpcszFileName);
         virtual bool unzip_open(const char *,UINT);

         virtual bool locate(const char * pszFileName);

         virtual void add_file(const ::file::path & pszDir,const ::file::path & pszRelative);

         bool dump(::file::file_sp pfile);

         virtual ::file::file_sp Duplicate() const override;

         ::zip::file * get_zip_file();
         const ::zip::file * get_zip_file() const;

         virtual file_position_t seek(file_offset_t lOff,::file::e_seek nFrom) override;
         virtual void set_length(file_size_t dwNewLen) override;
         virtual file_size_t get_length() const override;

         using ::file::file::read;
         virtual memory_size_t read(void * lpBuf,memory_size_t nCount) override;

         using ::file::file::write;
         virtual void write(const void * lpBuf,memory_size_t nCount) override;

         virtual void LockRange(file_position_t dwPos,file_size_t dwCount) override;
         virtual void UnlockRange(file_position_t dwPos,file_size_t dwCount) override;

         virtual void Abort() override;
         virtual void flush() override;
         virtual void close() override;

         virtual ::file::listing & ls(::file::listing & listing);
         virtual ::file::listing & ls_relative_name(::file::listing & listing);

         virtual bool IsOpened() override;
         virtual uint64_t GetBufferPtr(UINT nCommand,uint64_t nCount = 0,void ** ppBufStart = NULL,void ** ppBufMax = NULL) override;

         virtual ::file::listing & perform_file_listing(::file::listing & listing) override;
         virtual ::file::listing & perform_file_relative_name_listing(::file::listing & listing) override;

      private:

         using ::file::binary_file::open;


   };


} // namespace zip












