#include "framework.h"


namespace zip
{

   class Util;

}


namespace file
{


   namespace dir
   {


      application::application(::aura::application * papp) :
         object(papp)
      {
      }


      application::~application()
      {

      }


      //stringa application::locale_schema_matter(string & strLocale, const string & strStyle)
      //{

      //   return m_papp->m_psystem->m_spdir->locale_schema_matter(get_app(), strLocale, strStyle);

      //}


      //stringa application::locale_schema_matter(string & strLocale, const string & strStyle, const string & pathRoot, const ::file::path & pathDomain)
      //{

      //   return m_papp->m_psystem->m_spdir->locale_schema_matter(get_app(), strLocale, strStyle, pathRoot, pathDomain);

      //}


      string application::matter(const ::file::patha & patha, bool bDir)
      {

         return m_papp->m_psystem->m_spdir->matter(get_app(), patha, bDir);

      }


      string application::matter(const ::file::path & path, bool bDir)
      {

         return m_papp->m_psystem->m_spdir->matter(get_app(), path, bDir);

      }


      void application::matter_ls(const ::file::path & str,::file::patha & stra)
      {
         m_papp->m_psystem->m_spdir->matter_ls(get_app(), str, stra);
      }

      void application::matter_ls_file(const ::file::path & str,::file::patha & stra)
      {
         m_papp->m_psystem->m_spdir->matter_ls_file(get_app(), str, stra);
      }


      ::file::path application::matter_file(const ::file::path & lpcsz,  bool bDir)
      {

         string strPath = m_papp->m_psystem->m_spdir->matter(get_app(), lpcsz, bDir);

         return strPath;

      }


      ::file::path application::userquicklaunch()
      {

         return m_papp->m_psystem->m_spdir->userquicklaunch(get_app());

      }


      ::file::path application::userprograms()
      {

         return m_papp->m_psystem->m_spdir->userprograms(get_app());

      }


      ::file::listing & application::ls(listing & listing)
      {

         return m_papp->m_psystem->m_spdir.m_p->ls(m_papp, listing);

      }

      ::file::listing & application::ls_relative_name(listing & listing)
      {

         return m_papp->m_psystem->m_spdir.m_p->ls_relative_name(m_papp, listing);

      }


      bool application::has_subdir(const ::file::path & lpcsz)
      {

         return m_papp->m_psystem->m_spdir.m_p->has_subdir(m_papp, lpcsz);

      }


      bool application::is(const ::file::path & lpcsz)
      {

         return m_papp->m_psystem->m_spdir.m_p->is(lpcsz, m_papp);

      }


      bool application::is_inside(const ::file::path & lpcszDir,const ::file::path & lpcszPath)
      {

         return m_papp->m_psystem->m_spdir.m_p->is_inside(lpcszDir, lpcszPath, m_papp);

      }


      bool application::is_inside_time(const ::file::path & lpcsz)
      {
         return m_papp->m_psystem->m_spdir.m_p->is_inside_time(lpcsz, m_papp);
      }


      ::file::listing & application::root_ones(::file::listing & listing)
      {
         return m_papp->m_psystem->m_spdir.m_p->root_ones(listing, m_papp);
      }


      bool application::mk(const ::file::path & path)
      {

         if (path.is_empty())
         {

            return true;

         }

         return m_papp->m_psystem->m_spdir.m_p->mk(path, m_papp);

      }


      bool application::rm(const ::file::path & path,bool bRecursive)
      {

         return m_papp->m_psystem->m_spdir.m_p->rm(m_papp, path, bRecursive);

      }


      ::file::path application::pathfind(const string & pszEnv, const string & pszTopic, const string & pszMode)
      {

         return m_papp->m_psystem->m_spdir->pathfind(pszEnv, pszTopic, pszMode, m_papp);

      }


      ::file::path application::dropbox()
      {

         return m_papp->m_psystem->m_spdir->dropbox(m_papp);

      }


   } // namespace dir


} // namespace file


