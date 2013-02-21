#include "framework.h"


namespace ca
{


   namespace file
   {


      application::application()
      {
      }

      void application::copy(const char * pszNew, const char * pszOld, bool bFailIfExists, e_extract eextract)
      {
         return m_papp->m_psystem->m_spfile->copy(pszNew, pszOld, bFailIfExists, eextract, m_papp);
      }

      void application::trash_that_is_not_trash(const char * psz)
      {
         return m_papp->m_psystem->m_spfile->trash_that_is_not_trash(psz, m_papp);
      }

      void application::trash_that_is_not_trash(stringa & stra)
      {
         return m_papp->m_psystem->m_spfile->trash_that_is_not_trash(stra, m_papp);
      }

      void application::replace(const char * pszContext, const char * pszFind, const char * pszReplace)
      {
         return m_papp->m_psystem->m_spfile->replace(pszContext, pszFind, pszReplace, m_papp);
      }

      bool application::exists(const char * pszPath)
      {

         if(gen::str::begins_ci(pszPath, "uifs://"))
         {
            return AppUser(m_papp).m_pifs->file_exists(pszPath);
         }

         return m_papp->m_psystem->m_spfile->exists(pszPath, m_papp);

      }


      bool application::exists(const string & strPath)
      {

         if(gen::str::begins_ci_iws(strPath, "uifs://"))
         {
            fontopus::user & user = AppUser(m_papp);
            return user.m_pifs->file_exists(strPath);
         }

         return m_papp->m_psystem->m_spfile->exists(strPath, m_papp);

      }

      bool application::exists(const var & var)
      {

         const string & strPath = var.get_string();

         if(gen::str::begins_ci_iws(strPath, "uifs://"))
         {
            return AppUser(m_papp).m_pifs->file_exists(strPath);
         }

         return m_papp->m_psystem->m_spfile->exists(strPath, m_papp);

      }

      string application::time(const char * pszBasePath, int32_t iDepth, const char * pszPrefix, const char * pszSuffix)
      {
         return m_papp->m_psystem->m_spfile->time(m_papp, pszBasePath, iDepth, pszPrefix, pszSuffix);
      }

      string application::time_square(const char * pszPrefix, const char * pszSuffix)
      {
         return m_papp->m_psystem->m_spfile->time_square(m_papp, pszPrefix, pszSuffix);
      }

      string application::time_log(const char * pszId)
      {
         return m_papp->m_psystem->m_spfile->time_log(m_papp, pszId);
      }

      gen::filesp application::time_square_file(const char * pszPrefix, const char * pszSuffix)
      {
         return m_papp->m_psystem->m_spfile->time_square_file(m_papp, pszPrefix, pszSuffix);
      }

      ::gen::filesp application::get(const char * name)
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

      void application::as_memory(var varFile, primitive::memory & mem)
      {
         return m_papp->m_psystem->m_spfile->as_memory(varFile, mem, m_papp);
      }

      void application::lines(stringa & stra, var varFile)
      {
         return m_papp->m_psystem->m_spfile->lines(stra, varFile, m_papp);
      }

      bool application::put_contents(var varFile, const void * pvoidContents, count count)
      {
         return m_papp->m_psystem->m_spfile->put_contents(varFile, pvoidContents, count, m_papp);
      }

      bool application::put_contents(var varFile, const char * lpcszContents)
      {
         return m_papp->m_psystem->m_spfile->put_contents(varFile, lpcszContents, m_papp);
      }

      bool application::put_contents(var varFile, gen::file & file)
      {
         return m_papp->m_psystem->m_spfile->put_contents(varFile, file, m_papp);
      }

      bool application::put_contents(var varFile, primitive::memory & mem)
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


      gen::filesp application::friendly_get_file(var varFile, UINT nOpenFlags)
      {
         try
         {
            return get_file(varFile, nOpenFlags);
         }
         catch(...)
         {
            return ::ca::null();
         }
      }

      gen::filesp application::get_file(var varFile, UINT nOpenFlags)
      {

         gen::filesp spfile;

         string strPath;

         if(varFile.get_type() == var::type_string)
         {

            strPath = varFile;

            strPath.trim("\"'");

         }
         else if(varFile.get_type() == var::type_propset)
         {

            if(varFile.has_property("url"))
            {

               strPath = varFile["url"];

               strPath.trim("\"'");

            }

         }

         if(varFile.get_type() == var::type_propset && varFile.propset()["file"].ca2 < ::gen::file >() != NULL)
         {

            spfile(varFile.propset()["file"].ca2 < ::gen::file >());

         }
         else if(gen::str::find_ci(".zip:", strPath) >= 0)
         {

            zip::InFile * pinfile = new zip::InFile(get_app());

            if(pinfile != NULL)
            {

               if(!pinfile->unzip_open(strPath, 0))
               {

                  delete pinfile;

                  pinfile = NULL;

               }

            }

            spfile(pinfile);

         }
         else if(gen::str::begins(strPath, "http://matter.ca2.cc/") || gen::str::begins(strPath, "https://matter.ca2.cc/"))
         {

            string strFile(strPath);
            if(gen::str::ends(strPath, "en_us_international.xml"))
            {
               TRACE("Debug Here");
            }

            if(gen::str::ends(strPath, "text_select.xml"))
            {
               TRACE("Debug Here");
            }

            if(gen::str::ends(strPath, "arialuni.ttf"))
            {
               TRACE("Debug Here : arialuni.ttf");
            }

            strFile.replace("://", "_\\");
            strFile = System.dir().appdata("cache/" + strFile + ".local_copy");


            if(m_papp->m_pappThis->m_file.exists(strFile))
            {

               spfile.create(m_papp);

               try
               {

                  if(spfile->open(strFile, nOpenFlags))
                  {
                     TRACE("from_exist_cache:\"" + strPath + "\"");
                     return spfile;

                  }
               }
               catch(...)
               {

               }

               try
               {

                  spfile.destroy();

               }
               catch(...)
               {
               }

            }

            var varQuery;

            varQuery["disable_ca2_sessid"] = true;

            if(m_papp->m_pappThis->m_http.exists(strPath, &varQuery))
            {

               spfile(new sockets::http::file(get_app()));

               if(!spfile->open(strPath, nOpenFlags))
               {

                  spfile.destroy();

               }
               else
               {

                  try
                  {

                     System.file().output(m_papp, strFile, &System.compress(), &::ca4::compress::null, *spfile.m_p);

                  }
                  catch(...)
                  {
                  }


                  spfile->seek_to_begin();

               }

            }


         }
         else if(gen::str::begins(strPath, "http://") || gen::str::begins(strPath, "https://"))
         {

            spfile(new sockets::http::file(get_app()));

            if(!spfile->open(strPath, nOpenFlags))
            {

               spfile.destroy();

            }

         }
         else if(gen::str::begins(strPath, "ifs://") || gen::str::begins(strPath, "uifs://"))
         {

            if(&AppUser(m_papp) == NULL)
            {

               spfile = ::ca::null();

            }
            else
            {

               spfile = AppUser(m_papp).m_pifs->get_file(varFile, nOpenFlags);

            }

         }
         else if(gen::str::begins(strPath, "fs://"))
         {

            if(&Session == NULL)
            {

               spfile = ::ca::null();

            }
            else
            {

               spfile = Session.m_prfs->get_file(varFile, nOpenFlags);

            }

         }
         else if(gen::str::begins_eat_ci(strPath, "matter://"))
         {

            ::ca::application * papp = NULL;

            if(System.url().get_server("matter://" + strPath) == m_papp->m_pappThis->m_strAppName)
            {

               strPath = System.url().get_object("matter://" + strPath).Mid(1);

               spfile.create(m_papp);

               if(!spfile->open(App(m_papp).dir().matter(strPath), nOpenFlags))
               {

                  spfile.destroy();

               }

            }
            else if(&Session != NULL && Session.m_mapApplication.Lookup(System.url().get_server("matter://" + strPath), papp) && App(m_papp).m_strAppName.has_char())
            {

               spfile = App(papp).file().get_file("matter://" + strPath, nOpenFlags);

            }
            else
            {

               spfile = get_file(App(m_papp).dir().matter(strPath), nOpenFlags);

            }

         }
         else
         {

            if(strPath.is_empty())
            {
               TRACE("planebase::application::get_file file with empty name!!");
               return spfile;
            }

            spfile.create(m_papp);

            if(!spfile->open(strPath, nOpenFlags))
            {

               spfile.destroy();

            }

         }

         if(spfile.is_null())
         {

            throw gen::file_exception(m_papp, ::gen::file_exception::none, -1, strPath);

         }

         return spfile;

      }

      ::gen::byte_stream application::get_byte_stream(var varFile, UINT nOpenFlags)
      {

         return ::gen::byte_stream(get_file(varFile, nOpenFlags));

      }


   } // namespace file


} // namespace ca2



