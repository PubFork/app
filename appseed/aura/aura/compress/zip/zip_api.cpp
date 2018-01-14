#include "framework.h"



namespace zip
{


   api::api()
   {

   }


   api::~api()
   {

   }


   unzFile api::unzip_open(memory_file * pfile)
   {

      unzFile pf = unzOpen2("pad", (zlib_filefunc_def*)pfile->m_pvoidFileFuncDef);

      if(pf == NULL)
         return NULL;

     // m_mapUnzip.set_at(pf, pfile);

      return pf;

   }


   unzFile api::unzip_open (file * pfile)
   {
      unzFile pf = unzOpen2("pad", (zlib_filefunc_def*)pfile->m_pvoidFileFuncDef);
      if(pf == NULL)
         return NULL;

   //   m_mapUnzip.set_at(pf, pfile);

      return pf;

   }

   
   zipFile api::zip_open(file * pfile)
   {
      zipFile pf = zipOpen2("pad", APPEND_STATUS_CREATE, NULL, (zlib_filefunc_def *) pfile->m_pvoidFileFuncDef);
      if(pf == NULL)
         return NULL;

     // m_mapUnzip.set_at(pf, pfile);

      return pf;

   }

} // namespace zip
