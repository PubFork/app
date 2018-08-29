#include "framework.h"


extern mutex * g_pmutexLibrary;


namespace aura
{


   const char * psz_empty_app_id = "";


   library::library(::aura::application * papp):
      object(papp)
   {

      m_plibrary = NULL;

      m_bAutoUnload = false;

   }


   library::library(::aura::application * papp,int iDesambig,const char * pszRoot):
      object(papp)
   {

      m_bAutoUnload = false;

      m_plibrary = NULL;

      m_strCa2Name = pszRoot;

      if(pszRoot != NULL)
      {

         m_strRoot = pszRoot;

         if(m_strRoot.find('/') > 0)
         {

            m_strRoot = m_strRoot.substr(0, m_strRoot.find('/'));

         }

      }

   }


   library::~library()
   {

      close();

   }


   bool library::open(const char * pszPath,bool bAutoClose,bool bCa2Path)
   {

      synch_lock sl(g_pmutexLibrary);

      m_strMessage.Empty();

      auto pfn_get_new_library = get_library_factory(pszPath);

      if (pfn_get_new_library != NULL)
      {

         m_strPath = pszPath;

         System.m_mapLibrary[m_strCa2Name] = this;

         return true;

      }

      try
      {

         if(bCa2Path)
         {

            m_plibrary = __node_library_open_ca2(pszPath, m_strMessage);

         }
         else
         {

            m_plibrary = __node_library_open(pszPath, m_strMessage);

         }

         if(m_plibrary == NULL)
         {

            thisfail << m_strMessage;

            return false;

         }

         m_strPath = pszPath;

      }
      catch(...)
      {

         thisexcall << "Failed to open library " << (bCa2Path ? " (ca2 path)" : "") << " with errors " << m_strMessage;

         return false;

      }

      thisend << m_strMessage;

      System.m_mapLibrary[m_strCa2Name] = this;

      return true;

   }


   bool library::open_ca2_library(string strTitle)
   {

      synch_lock sl(g_pmutexLibrary);

      if (m_pca2library.is_set())
      {

         return true;

      }

      ::exception::engine().reset();

      PFN_GET_NEW_LIBRARY pfn_get_new_library = NULL;

      int iPhase = 0;

      try
      {

         pfn_get_new_library = get_library_factory(m_strPath);

         if (pfn_get_new_library == NULL)
         {

            iPhase++;

            if (strTitle.has_char())
            {

               pfn_get_new_library = get < PFN_GET_NEW_LIBRARY >(strTitle + "_get_new_library");

            }

         }

         if (pfn_get_new_library == NULL)
         {

            iPhase++;

            strTitle = m_strPath.title();

            pfn_get_new_library = get < PFN_GET_NEW_LIBRARY >(strTitle + "_get_new_library");

         }

         if (pfn_get_new_library == NULL)
         {

            iPhase++;

            if (::str::begins_eat(strTitle, "lib"))
            {

               pfn_get_new_library = get < PFN_GET_NEW_LIBRARY >(strTitle + "_get_new_library");

            }

         }

         if (pfn_get_new_library == NULL)
         {

            iPhase++;

            pfn_get_new_library = get < PFN_GET_NEW_LIBRARY >("get_new_library");

         }

      }
      catch(...)
      {

         close();

         return false;

      }

      if(pfn_get_new_library == NULL)
      {

         close();

         return false;

      }

      try
      {

         m_pca2library = pfn_get_new_library(get_app());

      }
      catch(...)
      {

         m_pca2library.release();

      }

      if(m_pca2library.is_null())
      {

         close();

         return false;

      }

      m_pca2library->set_app(get_app());

      if (m_pca2library->m_strCa2Name.is_empty())
      {

         m_pca2library->m_strCa2Name = m_strPath.title();

         m_strCa2Name = m_strPath;

      }
      else
      {

         m_strCa2Name = m_pca2library->m_strCa2Name;

      }

      return true;

   }


   library * library::get_ca2_library()
   {

      return m_pca2library;

   }


   string library::get_library_name()
   {

      synch_lock sl(g_pmutexLibrary);

      if(m_pca2library != NULL)
      {

         return m_pca2library->get_library_name();

      }
      else
      {

         string strName(m_strCa2Name);

         string strPrefix(get_root());

#ifdef METROWIN

         //         strPrefix = "m_" + strPrefix;

#endif

         strPrefix.replace("-","_");

         strPrefix += "_";

         ::str::begins_eat_ci(strName,strPrefix);

         return strName;

      }

   }


   void * library::get_os_data()
   {

      return m_plibrary;

   }


   bool library::close()
   {

      synch_lock sl(g_pmutexLibrary);

      try
      {

         bool bOk = true;

         m_pca2library.release();

         if (m_bAutoUnload)
         {

            try
            {

               if (m_plibrary != NULL)
               {

                  bOk = ::__node_library_close(m_plibrary);

                  m_plibrary = NULL;

               }

            }
            catch (...)
            {

               m_plibrary = NULL;

               bOk = false;

            }

         }

         return bOk;

      }
      catch(...)
      {
         return false;
      }

   }


   string library::get_app_id(const char * pszAppName)
   {

      synch_lock sl(g_pmutexLibrary);

      if(!contains_app(pszAppName))
         return "";

      string strPrefix(get_root());

      string strLibraryName(get_library_name());

#if defined(LINUX) || defined(APPLEOS)

      if(strLibraryName == "libca2")
      {

         strLibraryName = "ca2";

      }
      else if(!::str::begins_eat(strLibraryName,"libca2"))
      {

         ::str::begins_eat(strLibraryName,"lib");

      }

#elif defined(METROWIN)

      //      ::str::begins_eat_ci(strLibraryName, "m_");

#endif


      stringa straAppList;

      get_app_list(straAppList);

      strPrefix += "/";

      if(straAppList.get_count() > 1)
      {

         strPrefix += strLibraryName;

         strPrefix += "/";

      }

      return strPrefix + pszAppName;

   }


   string library::get_app_name(const char * pszAppId)
   {

      synch_lock sl(g_pmutexLibrary);

      string strAppName(pszAppId);

      string strPrefix(get_root());

      string strLibraryName(get_library_name());

#if defined(LINUX) || defined(APPLEOS)

      if(strLibraryName == "libca2")
      {

         strLibraryName = "ca2";

      }
      else if(!::str::begins_eat(strLibraryName,"libca2"))
      {

         ::str::begins_eat(strLibraryName,"lib");

      }

#elif defined(METROWIN)

      //      ::str::begins_eat_ci(strLibraryName, "m_");

#endif

      strPrefix += "/";

      strPrefix += strLibraryName;

      strPrefix += "/";

      ::str::begins_eat(strAppName,strPrefix);

      if(!contains_app(strAppName))
      {

         strAppName     = pszAppId;

         strPrefix      = get_root();

         strPrefix += "/";

         ::str::begins_eat(strAppName,strPrefix);

         if(!contains_app(strAppName))
            return "";
      }

      return strAppName;

   }


   sp(::aura::application) library::get_new_application(const char * pszAppId)
   {

      synch_lock sl(g_pmutexLibrary);

      try
      {

         if(get_ca2_library() != NULL)
         {

            string strAppName = get_app_name(pszAppId);

            if(strAppName.is_empty())
               return NULL;

            sp(::aura::application) papp = get_ca2_library()->get_new_application(strAppName);

            if(papp == NULL)
               return NULL;

            papp->m_strLibraryName   = m_strCa2Name;

            return papp;

         }

         return NULL;
      }
      catch(...)
      {
         return NULL;
      }

   }

   void library::get_extension_list(stringa & stra)
   {


   }


   void library::get_app_list(stringa & stra)
   {

      synch_lock sl(g_pmutexLibrary);

      if(get_ca2_library() != NULL)
      {
         try
         {
            get_ca2_library()->get_app_list(stra);
         }
         catch(...)
         {
         }
      }
      else
      {

         string strAppId = m_strCa2Name;

         stra.add(strAppId);

//
//
//         string strPrefix = get_root();
//
//#if defined(LINUX) || defined(APPLEOS)
//
//         ::str::begins_eat(strAppId,"lib");
//
//#elif defined(METROWIN)
//
//         //         strPrefix = "m_" + strPrefix;
//
//#endif
//
//         strPrefix.replace("-","_");
//
//         strPrefix += "_";
//
//         ::str::begins_eat_ci(strAppId,strPrefix);
//
//         //if(::str::begins_eat_ci(strAppId,strPrefix))
//         {
//
//            stra.add(strAppId);
//
//         }

      }

   }


   sp(::object) library::create_object(::aura::application * papp,const char * pszClassId, object * p)
   {

      synch_lock sl(g_pmutexLibrary);

      if(get_ca2_library() == NULL)
         return NULL;

      sp(::object) pobject = get_ca2_library()->create_object(papp, pszClassId, p);

      if (pobject.is_null())
      {

         return NULL;

      }

      pobject->m_ulFlags |= ::object::flag_heap_alloc;

      return pobject;

   }


   bool library::has_object_class(const char * pszClassId)
   {

      synch_lock sl(g_pmutexLibrary);

      if (get_ca2_library() == NULL)
      {

         return false;

      }

      return get_ca2_library()->has_object_class(pszClassId);

   }


   bool library::contains_app(const char * pszAppId)
   {

      synch_lock sl(g_pmutexLibrary);

      stringa stra;

      get_app_list(stra);

      return stra.contains(pszAppId);

   }


   string library::get_root()
   {

      synch_lock sl(g_pmutexLibrary);

      if(m_pca2library != NULL)
      {

         return m_pca2library->m_strRoot;

      }

      return m_strRoot;

   }


   void library::get_create_view_id_list(::array < id > & ida)
   {

      synch_lock sl(g_pmutexLibrary);

      UNREFERENCED_PARAMETER(ida);

   }


   bool library::is_opened()
   {

      synch_lock sl(g_pmutexLibrary);

      return m_plibrary != NULL;

   }


   bool library::is_closed()
   {

      return !is_opened();

   }


   void * library::raw_get(const char * pszEntryName)
   {

      synch_lock sl(g_pmutexLibrary);

      return __node_library_raw_get(m_plibrary,pszEntryName);

   }


} // namespace aura


string_map < sp(::aura::library) > * g_pmapLibCall = NULL;


::aura::library * lib(const char * psz)
{

   if(g_pmapLibCall == NULL)
      return NULL;

   sp(::aura::library) & lib = g_pmapLibCall->operator[](psz);

   if(lib.is_null())
   {
      lib = canew(::aura::library(get_app()));
      lib->open(psz);
   }

   return lib;

}



#if defined(LINUX)

::file::path libfilename(const string & str)
{
   return "lib" + str + ".so";
}

#elif defined(VSNORD)

::file::path libfilename(const string & str)
{
   return "lib" + str + ".so";
}

#elif defined(WINDOWS)

::file::path libfilename(const string & str)
{
   return str + ".dll";
}

#elif defined(APPLEOS)

::file::path libfilename(const string & str)
{
   return "lib" + str + ".dylib";
}

#endif


