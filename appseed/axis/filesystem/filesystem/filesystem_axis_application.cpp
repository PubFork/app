#include "framework.h"
//#include "axis/net/net_sockets.h"



namespace file
{


   namespace axis
   {


      application::application(::aura::application * papp) :
         ::object(papp),
         ::file::application(papp)
      {

      }


      application::~application()
      {

      }


      cres application::copy(const ::file::path & pszNew, const ::file::path & pszOld, bool bFailIfExists, e_extract eextract)
      {

         return m_papp->m_psystem->m_spfile->copy(pszNew, pszOld, bFailIfExists, eextract, m_papp);

      }


      cres application::move(const ::file::path & pszNew, const ::file::path & pszOld)
      {

         return m_papp->m_psystem->m_spfile->move(pszNew, pszOld, m_papp);

      }


      cres application::del(const ::file::path & psz)
      {

         return m_papp->m_psystem->m_spfile->del(psz, m_papp);

      }


      cres application::rename(const ::file::path & pszNew, const ::file::path & pszOld)
      {

         return m_papp->m_psystem->m_spfile->rename(pszNew, pszOld, m_papp);

      }


      void application::trash_that_is_not_trash(const ::file::path & psz)
      {

         return m_papp->m_psystem->m_spfile->trash_that_is_not_trash(psz, m_papp);

      }


      void application::trash_that_is_not_trash(::file::patha & stra)
      {

         return m_papp->m_psystem->m_spfile->trash_that_is_not_trash(stra, m_papp);

      }


      cres application::replace(const ::file::path & pszContext, const string & pszFind, const string & pszReplace)
      {

         return m_papp->m_psystem->m_spfile->replace(pszContext, pszFind, pszReplace, m_papp);

      }


      bool application::exists(const ::file::path & pszPath)
      {

         if (::str::begins_ci(pszPath, "uifs://"))
         {

            return AppUser(m_papp).m_pifs->file_exists(pszPath);

         }

         if (::str::begins_ci(pszPath, "appmatter://"))
         {

            return m_papp->m_psystem->m_spfile->exists(System.get_matter_cache_path(pszPath), m_papp);

         }

         return m_papp->m_psystem->m_spfile->exists(pszPath, m_papp);

      }


      var application::length(const ::file::path & pszPath)
      {

         if (::str::begins_ci(pszPath, "uifs://"))
         {

            if (::thread_is_fast_path())
            {

               return var::type_null;

            }

            return AppUser(m_papp).m_pifs->file_length(pszPath);

         }

         return m_papp->m_psystem->m_spfile->length(pszPath, m_papp);

      }




      ::file::path application::time(const ::file::path & pszBasePath, int32_t iDepth, const string & pszPrefix, const string & pszSuffix)
      {

         return m_papp->m_psystem->m_spfile->time(m_papp, pszBasePath, iDepth, pszPrefix, pszSuffix);

      }


      ::file::path application::time_square(const string & pszPrefix, const string & pszSuffix)
      {

         return m_papp->m_psystem->m_spfile->time_square(m_papp);

      }


      ::file::path application::time_log(const string & pszId)
      {
         return m_papp->m_psystem->m_spfile->time_log(m_papp, pszId);
      }

      ::file::file_sp application::time_square_file(const string & pszPrefix, const string & pszSuffix)
      {
         return m_papp->m_psystem->m_spfile->time_square_file(m_papp, pszPrefix, pszSuffix);
      }

      ::file::file_sp application::get(const ::file::path & name)
      {
         return m_papp->m_psystem->m_spfile->get(name, m_papp);
      }

      string application::as_string(var varFile)
      {
         return m_papp->m_psystem->m_spfile->as_string(varFile, m_papp);
      }

      string application::as_string(var varFile, var & varQuery)
      {
         return m_papp->m_psystem->m_spfile->as_string(varFile, varQuery, m_papp);
      }

      void application::as_memory(var varFile, memory & mem)
      {
         return m_papp->m_psystem->m_spfile->as_memory(varFile, mem, m_papp);
      }

      void application::lines(stringa & stra, var varFile)
      {
         return m_papp->m_psystem->m_spfile->lines(stra, varFile, m_papp);
      }

      bool application::put_contents(var varFile, const void * pvoidContents, ::count count)
      {
         return m_papp->m_psystem->m_spfile->put_contents(varFile, pvoidContents, count, m_papp);
      }

      bool application::put_contents(var varFile, const char * lpcszContents)
      {
         return m_papp->m_psystem->m_spfile->put_contents(varFile, lpcszContents, m_papp);
      }

      bool application::put_contents(var varFile, ::file::reader & reader)
      {
         return m_papp->m_psystem->m_spfile->put_contents(varFile, reader, m_papp);
      }

      bool application::put_contents(var varFile, memory & mem)
      {
         return m_papp->m_psystem->m_spfile->put_contents(varFile, mem, m_papp);
      }

      bool application::put_contents_utf8(var varFile, const char * lpcszContents)
      {
         return m_papp->m_psystem->m_spfile->put_contents_utf8(varFile, lpcszContents, m_papp);
      }

      string application::sys_temp(const ::file::path & pszName, const string & pszExtension)
      {
         return m_papp->m_psystem->m_spfile->sys_temp(pszName, pszExtension, m_papp);
      }


      void application::dtf(const ::file::path & pszFile, const ::file::path & pszDir)
      {
         return m_papp->m_psystem->m_spfile->dtf(pszFile, pszDir, m_papp);
      }

      void application::dtf(const ::file::path & pszFile, ::file::patha & stra)
      {
         return m_papp->m_psystem->m_spfile->dtf(pszFile, stra, m_papp);
      }

      void application::ftd(const ::file::path & pszDir, const ::file::path & pszFile)
      {
         return m_papp->m_psystem->m_spfile->ftd(pszDir, pszFile, m_papp);
      }


      bool application::crypto_set(var varFile, const char * pszData, const char * pszSalt)
      {

         // attention: operation on System crypto
         return m_papp->m_psystem->m_spcrypto->file_set(varFile, pszData, pszSalt, m_papp);

      }


      bool application::crypto_get(var varFile, string & str, const char * pszSalt)
      {

         // attention: operation on System crypto
         return m_papp->m_psystem->m_spcrypto->file_get(varFile, str, pszSalt, m_papp);

      }


      ::file::file_sp application::friendly_get_file(var varFile, UINT nOpenFlags, cres * pfesp)
      {

         if (pfesp != NULL)
         {

            ::release(pfesp->m_p);

         }

         try
         {

            return get_file(varFile, nOpenFlags, pfesp);

         }
         catch (...)
         {

            return NULL;

         }

      }


      ::file::file_sp application::get_file(var varFile, UINT nOpenFlags, cres * pfesp)
      {

         if (m_papp == NULL)
         {

            return NULL;

         }

         if (m_papp->m_psystem == NULL)
         {

            return NULL;

         }

         if (m_papp->m_psystem->m_spfile.is_null())
         {

            return NULL;

         }

         if (varFile.m_etype == ::var::type_element)
         {

            ::file::file_sp f = varFile.cast < ::file::file >();

            if (f.is_set())
            {

               return f;

            }



         }
         else if (varFile.m_etype == ::var::type_string)
         {

            varFile = System.defer_process_path(varFile.get_file_path(), m_papp);

         }

         ::file::file_sp pfile = m_papp->m_psystem->m_spfile->get_file(varFile,nOpenFlags,pfesp,m_papp);

         if (pfile.is_set())
         {

            return pfile;

         }

         if (m_papp->m_psession != NULL && Sess(m_papp).m_spfsdata.is_set())
         {

            pfile = Sess(m_papp).m_spfsdata->get_file(varFile, nOpenFlags, pfesp);

         }

         return pfile;

      }


   } // namespace axis


} // namespace core



























