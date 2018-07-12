#include "framework.h"


namespace file
{


   file_stream::file_stream()
   {


   }


   file_stream::file_stream(const char * lpszFileName, uint32_t nOpenFlags, ::aura::application * papp)
   {

      open(lpszFileName, nOpenFlags, papp);

   }


   file_stream::file_stream(file * pfile)
   {

      m_spfile = pfile;

   }


   file_stream::~file_stream()
   {

      close();

   }


   void file_stream::open(const ::file::path & lpszFileName, uint32_t nOpenFlags, ::aura::application * papp)
   {

      m_spfile.release();

      try
      {

         if (papp == NULL)
         {

            m_spfile = canew(::file::stdio_file(lpszFileName, nOpenFlags | ::file::mode_read));

         }
         else
         {

            m_spfile = App(papp).file().get_file(lpszFileName, nOpenFlags | ::file::mode_read);

         }

      }
      catch (...)
      {

      }

      if (m_spfile.is_null())
      {

         setstate(failbit);

      }

   }


} // namespace file



