#include "framework.h"
#include "linux.h"


#include <unistd.h>


namespace linux
{


   namespace axis
   {


      dir::dir(::aura::application * papp) :
         ::object(papp),
         ::file::dir::system(papp),
         ::file_watcher::file_watcher(papp),
         ::file::dir::axis::system(papp),
         ::linux::dir(papp)
      {


      }


      ::file::listing & dir::ls(::aura::application * papp, ::file::listing & listing)
      {


         if(::file::dir::axis::system::ls(papp, listing).succeeded())
         {

            return listing;

         }

         return ::linux::dir::ls(papp,listing);

      }


      bool dir::is(const ::file::path & lpcszPath, ::aura::application * papp, bool bOptional, bool bNoCache)
      {

         if(::linux::dir::is(lpcszPath,papp, bOptional, bNoCache))
         {

            return true;

         }

         if(::file::dir::axis::system::is(lpcszPath, papp))
         {

            return true;

         }

         return false;

      }


      bool dir::name_is(const ::file::path & str, ::aura::application * papp)
      {

         strsize iLast = str.get_length() - 1;

         while(iLast >= 0)
         {
            if(str.m_pszData[iLast] != '\\' && str.m_pszData[iLast] != '/' && str.m_pszData[iLast] != ':')
               break;
            iLast--;
         }
         while(iLast >= 0)
         {
            if(str.m_pszData[iLast] == '\\' || str.m_pszData[iLast] == '/' || str.m_pszData[iLast] == ':')
               break;
            iLast--;
         }
         if(iLast >= 0)
         {
            while(iLast >= 0)
            {
               if(str.m_pszData[iLast] != '\\' && str.m_pszData[iLast] != '/' && str.m_pszData[iLast] != ':')
               {
                  iLast++;
                  break;
               }
               iLast--;
            }
         }
         else
         {
            return true; // assume empty string is root_ones directory
         }

         if(thread_zip_is_dir() && iLast >= 3 && !strnicmp_dup(&((const char *)str)[iLast - 3],".zip",4))
         {

            return true;

         }

         strsize iFind = ::str::find_ci(".zip:", str);

         if(thread_zip_is_dir() && iFind >= 0 && iFind < iLast)
         {

            bool bHasSubFolder;

            bHasSubFolder = m_pziputil->has_sub_folder(papp, str);

            return bHasSubFolder;

         }

         bool bIsDir = ::dir::is(str.Left(iLast));

         return bIsDir;

      }


      bool dir::initialize()
      {

         if(!::linux::dir::initialize())
         {

            return false;

         }

         return true;

      }


   } // namespace axis


} // namespace linux



