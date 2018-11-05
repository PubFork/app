#include "framework.h"
//#include "aura/net/net_sockets.h"


namespace file
{


   application::application(::aura::application * papp) :
      object(papp)
   {

   }


   application::~application()
   {

   }

   ::cres application::copy(const ::file::path & pszNew,const ::file::path & pszOld,bool bFailIfExists,e_extract eextract)
   {
      return m_papp->m_psystem->m_spfile->copy(pszNew, pszOld, bFailIfExists, eextract, m_papp);
   }

   ::cres application::move(const ::file::path & pszNew,const ::file::path & pszOld)
   {
      return m_papp->m_psystem->m_spfile->move(pszNew,pszOld,m_papp);
   }

   ::cres application::del(const ::file::path & psz)
   {
      return m_papp->m_psystem->m_spfile->del(psz,m_papp);
   }

   ::cres application::rename(const ::file::path & pszNew,const ::file::path & pszOld)
   {
      return m_papp->m_psystem->m_spfile->rename(pszNew,pszOld,m_papp);
   }

   void application::trash_that_is_not_trash(const ::file::path & psz)
   {
      return m_papp->m_psystem->m_spfile->trash_that_is_not_trash(psz, m_papp);
   }

   void application::trash_that_is_not_trash(::file::patha & stra)
   {
      return m_papp->m_psystem->m_spfile->trash_that_is_not_trash(stra, m_papp);
   }

   ::cres application::replace(const ::file::path & pszContext,const string & pszFind,const string & pszReplace)
   {
      return m_papp->m_psystem->m_spfile->replace(pszContext, pszFind, pszReplace, m_papp);
   }


   bool application::exists(const ::file::path & pszPath)
   {

      return m_papp->m_psystem->m_spfile->exists(pszPath, m_papp);

   }


   bool application::is_file_or_dir(const ::file::path & pszPath, e_type * petype)
   {

      return m_papp->m_psystem->m_spfile->is_file_or_dir(pszPath, NULL, petype, m_papp);

   }


   /*  bool application::exists(const string & strPath)
     {

        return m_papp->m_psystem->m_spfile->exists(strPath, m_papp);

     }

     bool application::exists(const var & var)
     {

        const string & strPath = var.get_string();


        return m_papp->m_psystem->m_spfile->exists(strPath, m_papp);

     }*/


   var application::length(const ::file::path & pszPath)
   {

      return m_papp->m_psystem->m_spfile->length(pszPath, m_papp);

   }


   //var application::length(const string & strPath)
   //{


   //   return m_papp->m_psystem->m_spfile->length(strPath, m_papp);

   //}


   //var application::length(const var & var)
   //{

   //   return m_papp->m_psystem->m_spfile->length(var.get_string(), m_papp);

   //}


   ::file::path application::time(const ::file::path & pszBasePath,int32_t iDepth,const string & pszPrefix,const string & pszSuffix)
   {

      return m_papp->m_psystem->m_spfile->time(m_papp, pszBasePath, iDepth, pszPrefix, pszSuffix);

   }


   ::file::path application::time_square(const string & pszPrefix,const string & pszSuffix)
   {

      return m_papp->m_psystem->m_spfile->time_square(m_papp, pszPrefix, pszSuffix);

   }

   ::file::path application::time_log(const string & pszId)
   {
      return m_papp->m_psystem->m_spfile->time_log(m_papp, pszId);
   }

   ::file::file_sp application::time_square_file(const char * pszPrefix, const char * pszSuffix)
   {
      return m_papp->m_psystem->m_spfile->time_square_file(m_papp, pszPrefix, pszSuffix);
   }

   ::file::file_sp application::get(const ::file::path & name)
   {
      return m_papp->m_psystem->m_spfile->get(name, m_papp);
   }

   var application::as_json(var varFile)
   {
      return m_papp->m_psystem->m_spfile->as_json(varFile, m_papp);
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

   void application::put_lines(var varFile, const stringa & stra)
   {
      return m_papp->m_psystem->m_spfile->put_lines(varFile, stra, m_papp);
   }

   bool application::put_contents(var varFile, const void * pvoidContents, ::count count)
   {
      return m_papp->m_psystem->m_spfile->put_contents(varFile, pvoidContents, count, m_papp);
   }

   bool application::put_contents(var varFile, const char * lpcszContents)
   {
      return m_papp->m_psystem->m_spfile->put_contents(varFile, lpcszContents, m_papp);
   }

   bool application::add_contents(var varFile,const char * lpcszContents)
   {
      return m_papp->m_psystem->m_spfile->add_contents(varFile,lpcszContents,m_papp);
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

   string application::sys_temp(const char * pszName, const char * pszExtension)
   {
      return m_papp->m_psystem->m_spfile->sys_temp(pszName, pszExtension, m_papp);
   }



   ::file::file_sp application::friendly_get_file(var varFile, UINT nOpenFlags, cres * pfesp)
   {
      if(pfesp != NULL)
      {
         ::release(pfesp->m_p);
      }

      try
      {
         return get_file(varFile, nOpenFlags, pfesp);
      }
      catch(...)
      {
         return NULL;
      }
   }

   ::file::file_sp application::get_file(var varFile, UINT nOpenFlags, cres * pfesp)
   {

      return System.file().get_file(varFile, nOpenFlags, pfesp, m_papp);

//      if(pfesp != NULL)
//      {
//
//         ::release(pfesp->m_p);
//
//      }
//
//      ::cres cres;
//
//      ::file::file_sp spfile;
//
//      ::file::path strPath;
//
//      if (varFile.get_type() == var::type_element)
//      {
//
//         spfile = varFile.cast < ::file::file >();
//
//         if (spfile.is_set())
//            return spfile;
//
//      }
//      else if(varFile.get_type() == var::type_string)
//      {
//
//         strPath = varFile;
//
//         strPath = System.defer_process_path(strPath, get_app());
//
////         strPath.trim("\"'");
////
////         if (strPath.begins_ci("appmatter://"))
////         {
////
////            strPath = System.get_matter_cache_path(strPath);
////
////         }
////
////#ifndef METROWIN
////
////         if (::str::begins_eat_ci(strPath, "music://"))
////         {
////
////            strPath = System.dir().music() / strPath;
////
////         }
////
////#endif
//
//      }
//      else if(varFile.get_type() == var::type_stra)
//      {
//
//         if(varFile.stra().get_count() > 0)
//         {
//
//            strPath = varFile.stra()[0];
//
//         }
//
//         strPath.trim("\"'");
//
//      }
//      else if(varFile.get_type() == var::type_propset)
//      {
//
//         if(varFile.has_property("url"))
//         {
//
//            strPath = varFile["url"];
//
//            strPath.trim("\"'");
//
//         }
//
//      }
//
//      if(varFile.get_type() == var::type_propset && varFile.propset()["file"].cast < ::file::binary_file >() != NULL)
//      {
//
//         spfile = varFile.propset()["file"].cast < ::file::binary_file >();
//
//      }
//      //else if(::str::find_file_extension("zip:", strPath) >= 0)
//      //{
//
//      //   /* xxx
//      //   zip::InFile * pinfile = new zip::InFile(get_app());
//
//      //   if(pinfile != NULL)
//      //   {
//
//      //      if(!pinfile->unzip_open(strPath, 0))
//      //      {
//
//      //         delete pinfile;
//
//      //         pinfile = NULL;
//
//      //      }
//
//      //   }
//
//      //   spfile = pinfile;
//
//      //   */
//
//      //}
//      else if(::str::begins_eat_ci(strPath, "matter://"))
//      {
//
//         spfile = get_file(App(m_papp).dir().matter(strPath), nOpenFlags);
//
//      }
//      else
//      {
//
//         if(strPath.is_empty())
//         {
//            TRACE("::application::get_file file with empty name!!");
//            return spfile;
//         }
//
//         if((nOpenFlags & ::file::mode_create) == 0 && !exists(strPath))
//         {
//            TRACE("::application::file does not exist!! : \"%s\"", strPath);
//            return spfile;
//         }
//
//         spfile = Application.alloc(System.type_info < ::file::file > ());
//
//         cres = spfile->open(strPath,nOpenFlags);
//
//      }
//
//      if(cres.failed())
//      {
//
//         spfile.release();
//
//         if(pfesp != NULL)
//         {
//
//            *pfesp = cres;
//
//         }
//
//      }
//
//      return spfile;

   }

   /*   ::stream application::get_byte_stream(var varFile, UINT nOpenFlags)
      {

         return get_file(varFile, nOpenFlags);

      }
      */

   void application::dtf(const ::file::path & pszFile,const ::file::path & pszDir)
   {

      return m_papp->m_psystem->m_spfile->dtf(pszFile,pszDir,m_papp);

   }


   void application::dtf(const ::file::path & pszFile,::file::patha & stra,::file::patha & straRelative)
   {

      return m_papp->m_psystem->m_spfile->dtf(pszFile,stra,m_papp);

   }


   void application::ftd(const ::file::path & pszDir,const ::file::path & pszFile)
   {

      return m_papp->m_psystem->m_spfile->ftd(pszDir,pszFile,m_papp);

   }


   bool application::crypto_set(var varFile,const char * pszData,const char * pszSalt)
   {

      _throw(interface_only_exception(get_app()));

      return false;

   }


   bool application::crypto_get(var varFile,string & str,const char * pszSalt)
   {

      _throw(interface_only_exception(get_app()));

      return false;

   }


   bool application::save(var varFile,::object & o)
   {

      serialize s(get_app());

      s.save(varFile, o);

      return true;

   }


   bool application::load(::object & o,var varFile)
   {

      serialize s(get_app());

      s.load(varFile, o);

      return true;

   }


   bool application::save_lines(var varFile,stringa & stra)
   {

      string str = stra.implode("\n");

      put_contents_utf8(varFile, str);

      return true;

   }


   bool application::load_lines(stringa & stra,var varFile)
   {

      string str = as_string(varFile);

      stra.add_lines(str);

      return true;

   }


   bool application::transfer(const path & pathOut, const path & lpszSource)
   {

      return System.file().transfer(get_app(), pathOut, lpszSource);

   }


   bool application::transfer(const path & pathOut, ::file::file * pfileIn)
   {

      return System.file().transfer(get_app(), pathOut, pfileIn);

   }


   bool application::transfer(const path & pathOut, ::stream & is)
   {

      return System.file().transfer(get_app(), pathOut, is);

   }


   bool application::transfer(file * pfileOut, const path & lpszSource)
   {

      return System.file().transfer(get_app(), pfileOut, lpszSource);

   }


   bool application::transfer(file * pfileOut, ::file::file * pfileIn)
   {

      return System.file().transfer(get_app(), pfileOut, pfileIn);

   }


   bool application::transfer(file * pfileOut, ::stream & is)
   {

      return System.file().transfer(get_app(), pfileOut, is);

   }


   bool application::transfer(::stream & os, const path & lpszSource)
   {

      return System.file().transfer(get_app(), os, lpszSource);

   }


   bool application::transfer(::stream & os, ::file::file * pfileIn)
   {

      return System.file().transfer(get_app(), os, pfileIn);

   }


   bool application::transfer(::stream & os, ::stream & is)
   {

      return System.file().transfer(get_app(), os, is);

   }


   bool application::touch(const ::file::path & path)
   {

      if (!exists(path))
      {

         char ch;

         if (!put_contents(path, &ch, 0))
         {

            return false;

         }

      }

      return true;

   }

   string application::md5(var varFile)
   {
      return m_papp->m_psystem->m_spfile->md5(varFile, m_papp);
   }

   string application::nessie(var varFile)
   {
      return m_papp->m_psystem->m_spfile->nessie(varFile, m_papp);
   }


   ::file::path application::dropbox_info_json()
   {

      return m_papp->m_psystem->m_spfile->dropbox_info_json( m_papp);

   }


} // namespace file










































