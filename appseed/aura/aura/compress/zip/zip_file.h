#pragma once


namespace zip
{


   class CLASS_DECL_AURA file :
      virtual public ::object
   {
   public:


      ::file::file_sp            m_pfile;
      ::file::file_sp            m_pbuffile1;
      ::file::file_sp            m_pbuffile2;
      void *                     m_pfUnzip;
      void *                     m_pfZip;
      bool                       m_bOwnFile;
      void *                     m_pvoidFileFuncDef;


      file(::aura::application * papp);
      virtual ~file();


      void write_to_file(::file::file_sp  pfile, const unichar * lpcsz);

      bool unzip_open(const char * lpcwsz);
      bool unzip_open(::file::file_sp pfile, int iBufferLevel = 2);

      bool zip_open(const char * lpcwsz);
      bool zip_open(::file::file_sp pfile);


   };


} // namespace zip


BEGIN_EXTERN_C

void *         c_zip_file_open_file_func        (void * opaque, const char* filename, int32_t mode);
uint_ptr       c_zip_file_read_file_func        (void * opaque, void * stream, void * buf, uint_ptr size);
uint_ptr       c_zip_file_write_file_func       (void * opaque, void * stream, const void * buf, uint_ptr size);
long           c_zip_file_tell_file_func        (void * opaque, void * stream);
long           c_zip_file_seek_file_func        (void * opaque, void * stream, uint_ptr offset, int32_t origin);
int32_t        c_zip_file_close_file_func       (void * opaque, void * stream);
int32_t        c_zip_file_testerror_file_func   (void * opaque, void * stream);

END_EXTERN_C



