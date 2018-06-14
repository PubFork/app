#include "framework.h"
#include "zip_unzip.h"


void * zip_filefuncdef_malloc();
void zip_filefuncdef_set_file(void * pvoid, ::file::file * pfile);



namespace zip
{


   file::file(::aura::application * papp) :
      ::object(papp)
   {
      m_bOwnFile                 = false;
      m_pvoidFileFuncDef = zip_filefuncdef_malloc();
      m_pfUnzip = NULL;
      m_pfZip = NULL;
   }

   file::~file()
   {
      if(m_pfUnzip != NULL)
      {
         unzClose(m_pfUnzip);
      }
      if(m_pfZip != NULL)
      {
         zipClose(m_pfZip, NULL);
      }

      free(m_pvoidFileFuncDef);

   }

   bool file::unzip_open(const char * lpcwsz)
   {

      m_bOwnFile = true;

      ::file::file_sp spfile(allocer());

      try
      {
         if(spfile->open(lpcwsz, ::file::mode_read | ::file::type_binary).failed())
         {

            return false;

         }

      }
      catch(exception::exception * pe)
      {

         pe->Delete();

         return false;

      }
      catch(...)
      {

         return false;

      }

      return unzip_open(spfile);

   }


   bool file::unzip_open(::file::file_sp pfile, int iBufferLevel)
   {
      if (iBufferLevel >= 2)
      {
         m_pbuffile1 = new ::file::buffered_file(get_app(), pfile, 1024 * 32);
         m_pbuffile2 = new ::file::buffered_file(get_app(), m_pbuffile1, 1024 * 32);
      }
      else if (iBufferLevel == 1)
      {
         m_pbuffile1 = NULL;
         m_pbuffile2 = new ::file::buffered_file(get_app(), pfile, 1024 * 32);
      }
      else
      {
         // good option if pfile is memory file?
         m_pbuffile2 = pfile;

      }

      m_pbuffile2->seek_to_begin();

      m_pfile = m_pbuffile2;

      zip_filefuncdef_set_file(m_pvoidFileFuncDef, m_pfile);

      m_pfUnzip = api::unzip_open(this);

      return true;

   }


   bool file::zip_open(const char * lpcwsz)
   {
      m_bOwnFile = true;
      ::file::file_sp spfile(allocer());
      try
      {
         if(spfile->open(lpcwsz, ::file::mode_read_write | ::file::type_binary | ::file::mode_create | ::file::defer_create_directory).failed())
         {
            return false;
         }
      }
      catch(exception::exception * pe)
      {
         pe->Delete();
         return false;
      }
      catch(...)
      {
         return false;
      }
      return zip_open(spfile);
   }


   bool file::zip_open(::file::file_sp pfile)
   {

      m_pbuffile1 = new ::file::buffered_file(get_app(), pfile, 1024 * 256);

      m_pbuffile2 = new ::file::buffered_file(get_app(), m_pbuffile1, 1024 * 256);

      m_pbuffile2->seek_to_begin();

      m_pfile = m_pbuffile2;

      zip_filefuncdef_set_file(m_pvoidFileFuncDef, m_pfile);

      m_pfZip = api::zip_open(this);

      return true;

   }


   void  file::write_to_file(::file::file_sp  pfileOut, const unichar * lpcsz)
   {

      string str;

      ::str::international::unicode_to_utf8(str, lpcsz);

      str.replace("\\", "/");
      if(unzLocateFile(m_pfUnzip, str, 1) != UNZ_OK)
         return;
      BYTE buf[1024];
      int32_t iRead;
      if(unzOpenCurrentFile(m_pfUnzip) != UNZ_OK)
         return;

      while((iRead = unzReadCurrentFile(m_pfUnzip, buf, sizeof(buf))) > 0)
      {
         pfileOut->write(buf, iRead);
      }
      if(unzCloseCurrentFile(m_pfUnzip) != UNZ_OK)
         return;
   }


} // namespace zip


//BEGIN_EXTERN_C
//
//
//voidpf fileopen_file_func (voidpf opaque, const char* filename, int32_t mode)
//{
//   UNREFERENCED_PARAMETER(mode);
//   UNREFERENCED_PARAMETER(filename);
//   ::zip::file * pzipfile = (::zip::file *) opaque;
//   ::file::file_sp  pfile = pzipfile->m_pfile;
//   return (voidpf) pfile;
//}
//uint_ptr  fileread_file_func (voidpf opaque, voidpf stream, void * buf, uint_ptr size)
//{
//   return (uint_ptr)((::zip::file *) opaque)->m_pfile.m_p->read(buf,size);
//}
//uint_ptr  filewrite_file_func (voidpf opaque, voidpf stream, const void * buf, uint_ptr size)
//{
//   UNREFERENCED_PARAMETER(stream);
//   ::zip::file * pzipfile = (::zip::file *) opaque;
//   ::file::file_sp  pfile = pzipfile->m_pfile;
//   pfile->write(buf, size);
//   return size;
//}
//long   filetell_file_func (voidpf opaque, voidpf stream)
//{
//   UNREFERENCED_PARAMETER(stream);
//   ::zip::file * pzipfile = (::zip::file *) opaque;
//   ::file::file_sp  pfile = pzipfile->m_pfile;
//   return (long) pfile->get_position();
//}
//
//long   fileseek_file_func (voidpf opaque, voidpf stream, uint_ptr offset, int32_t origin)
//{
//   UNREFERENCED_PARAMETER(stream);
//   ::zip::file * pzipfile = (::zip::file *) opaque;
//   ::file::file_sp  pfile = pzipfile->m_pfile;
//   if(pfile->seek(offset, (::file::e_seek) origin) == 0xffffffff)
//      return -1;
//   else
//      return 0;
//
//}
//
//int32_t    fileclose_file_func (voidpf opaque, voidpf stream)
//{
//   UNREFERENCED_PARAMETER(opaque);
//   UNREFERENCED_PARAMETER(stream);
////      ::zip::file * pzipfile = (::zip::file *) opaque;
////      ::file::file_sp  pfile = pzipfile->m_pfile;
//   return 1;
//}
//
//int32_t c_zip_file_testerror_file_func (voidpf opaque, voidpf stream)
//{
//   UNREFERENCED_PARAMETER(opaque);
//   UNREFERENCED_PARAMETER(stream);
////      ::zip::file * pzipfile = (::zip::file *) opaque;
////      ::file::file_sp  pfile = pzipfile->m_pfile;
//   //return spfile->IsValid() ? 0 : 1;
//   return 0;
//}
//
//END_EXTERN_C
//





BEGIN_EXTERN_C


voidpf c_zip_file_open_file_func (voidpf opaque, const char* filename, int32_t mode)
{
   UNREFERENCED_PARAMETER(mode);
   UNREFERENCED_PARAMETER(filename);
   ::file::file * pfile = (::file::file *) opaque;
   return (voidpf) pfile;
}
uint_ptr  c_zip_file_read_file_func (voidpf opaque, voidpf stream, void * buf, uint_ptr size)
{
   return (uint_ptr)((::file::file *) opaque)->read(buf,size);
}
uint_ptr  c_zip_file_write_file_func (voidpf opaque, voidpf stream, const void * buf, uint_ptr size)
{
   UNREFERENCED_PARAMETER(stream);
   ::file::file * pfile = (::file::file *) opaque;
   pfile->write(buf, size);
   return size;
}
long   c_zip_file_tell_file_func (voidpf opaque, voidpf stream)
{
   UNREFERENCED_PARAMETER(stream);
   ::file::file * pfile = (::file::file *) opaque;
   return (long) pfile->get_position();
}

long   c_zip_file_seek_file_func (voidpf opaque, voidpf stream, uint_ptr offset, int32_t origin)
{
   UNREFERENCED_PARAMETER(stream);
   ::file::file * pfile = (::file::file *) opaque;
   if(pfile->seek(offset, (::file::e_seek) origin) == 0xffffffff)
      return -1;
   else
      return 0;

}

int32_t    c_zip_file_close_file_func (voidpf opaque, voidpf stream)
{
   UNREFERENCED_PARAMETER(opaque);
   UNREFERENCED_PARAMETER(stream);
//      ::zip::file * pzipfile = (::zip::file *) opaque;
//      ::file::file_sp  pfile = pzipfile->m_pfile;
   return 1;
}

int32_t c_zip_file_testerror_file_func (voidpf opaque, voidpf stream)
{
   UNREFERENCED_PARAMETER(opaque);
   UNREFERENCED_PARAMETER(stream);
//      ::zip::file * pzipfile = (::zip::file *) opaque;
//      ::file::file_sp  pfile = pzipfile->m_pfile;
   //return spfile->IsValid() ? 0 : 1;
   return 0;
}

END_EXTERN_C






void * zip_filefuncdef_malloc()
{

   zlib_filefunc_def_s * p = (zlib_filefunc_def_s *)malloc(sizeof(zlib_filefunc_def_s));

   p->zopen_file = &c_zip_file_open_file_func;
   p->zread_file = &c_zip_file_read_file_func;
   p->zwrite_file = &c_zip_file_write_file_func;
   p->ztell_file = &c_zip_file_tell_file_func;
   p->zseek_file = &c_zip_file_seek_file_func;
   p->zclose_file = &c_zip_file_close_file_func;
   p->zerror_file = &c_zip_file_testerror_file_func;

   return p;

}



void zip_filefuncdef_set_file(void * pvoid, ::file::file * pfile)
{

   zlib_filefunc_def_s * p = (zlib_filefunc_def_s *)pvoid;

   p->opaque = (voidpf)pfile;

}


