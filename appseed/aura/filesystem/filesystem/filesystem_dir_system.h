#pragma once


namespace file
{


   namespace dir
   {


      class CLASS_DECL_AURA system :
         virtual public ::object,
      //virtual public ::file_watcher::listener_thread
         virtual public ::file_watcher::file_watcher
      {
      public:


         ::zip::util *       m_pziputil;


         //class CLASS_DECL_AURA is_dir :
         //   virtual public sspa(is_dir)
         //{
         //public:

         //   int            m_iIsDir;
         //   uint32_t       m_dwLastCheck;
         //   uint32_t       m_dwError;
         //   string         m_str;
         //   inline const char * c_str()
         //   {
         //      return m_str.c_str();
         //   }

         //};

         //class CLASS_DECL_AURA is_dir_work
         //{
         //public:

         //   char *   m_psz;

         //   inline const char * c_str()
         //   {
         //      return m_psz;
         //   }

         //};


         //class CLASS_DECL_AURA is_dir_map :
         //   virtual public is_dir
         //{
         //public:

         //   critical_section     m_cs;
         //   uint32_t             m_dwTimeOut;

         //   is_dir_map();

         //   bool lookup(const ::file::path & path, bool &bIsDir, uint32_t & dwLastError);
         //   bool lookup(const ::file::path & path, bool &bIsDir, uint32_t & dwLastError, i32 iLastChar);
         //   bool lookup_dynamic(const ::file::path & path, bool &bIsDir, u32 & dwLastError, i32 iLastChar);
         //   bool lookup_small(const ::file::path & path, bool &bIsDir,u32 & dwLastError,i32 iLastChar);
         //   void set(const ::file::path & path,bool bIsDir,uint32_t dwLastError);


         //};


         static system *      g_pthis;
         //is_dir_map           m_isdirmap;
         mutex                m_mutex;
         string               m_strApiCc;

         ::file::path         m_pathCa2Config;
         ::file::path         m_pathCa2Module;
         ::file::path         m_pathModule;
         ::file::path         m_pathHome;
         ::file::path         m_pathInstall;



         system(::aura::application * papp);
         virtual ~system();


         virtual ::file::listing & ls(::aura::application * papp,listing & listing);
         virtual ::file::listing & ls_relative_name(::aura::application * papp, listing & listing);


         virtual bool  is(const ::file::path & lpcsz,::aura::application * papp);

         virtual bool  is_impl(const ::file::path & lpcsz, ::aura::application * papp);

         virtual bool  is_cached(bool & bIs, const ::file::path & lpcsz,::aura::application * papp);

         virtual bool  name_is(const ::file::path & lpcsz,::aura::application * papp);

         virtual bool  is_inside(const ::file::path & lpcszDir,const ::file::path & lpcszPath,::aura::application * papp);
         virtual bool  is_inside_time(const ::file::path & lpcsz,::aura::application * papp);
         virtual ::file::listing & root_ones(::file::listing & listing,::aura::application * papp);
         virtual bool  mk(const ::file::path & lpcsz,::aura::application * papp);
         virtual bool  rm(::aura::application * papp,const ::file::path & psz,bool bRecursive = true);

         //virtual ::file::path name(const ::file::path & psz);

         virtual bool has_subdir(::aura::application * papp,const ::file::path & psz);

         virtual ::file::path time();
         virtual ::file::path stage();
         virtual ::file::path stageapp();
         virtual ::file::path netseed();

         virtual ::file::path install();
         virtual ::file::path config();

         virtual ::file::path home();

         virtual ::file::path module();
         virtual ::file::path ca2module();
         virtual ::file::path time_square(::aura::application * papp);
         virtual ::file::path time_log(const string & strId);


         virtual string locale_schema_matter(::aura::application * papp, const string & strLocale, const string & strSchema, const ::file::path & pathRoot, const ::file::path & pathDomain);
         virtual string matter(const ::file::path & path, bool bDir, const ::file::path & pathRoot, const ::file::path & pathDomain);

         virtual string matter(::aura::application * papp, const ::file::patha & patha, bool bDir = false);
         virtual string matter(::aura::application * papp, ::file::path path, bool bDir = false);

         virtual string matter_from_locator(::aura::application * papp, const ::file::patha & patha, const stringa & straMatterLocator, bool bDir = false);
         virtual string matter_from_locator(::aura::application * papp, ::file::path path, const stringa & straMatterLocator, bool bDir = false);

         virtual ::file::path appmatter(string strApp, ::file::path pathRel);

         virtual void   matter_ls(::aura::application * papp, const ::file::path & str, ::file::patha & stra);
         virtual void   matter_ls_file(::aura::application * papp,const ::file::path & str,::file::patha & stra);

         //virtual ::file::path matter(::aura::application * papp);

         //virtual ::file::path matter_from_locator(::aura::str_context * pcontext,const string & strLocator,const ::file::path & str);
         //virtual void appmatter_locator(::file::path & strRoot,::file::path & strDomain,::aura::application * papp);
         //virtual void appmatter_locator(::file::path & strRoot,::file::path & strDomain,const string & strLibraryName,const string & strAppName);
         //virtual void appmatter_locator(::file::path & strRoot,::file::path & strDomain,const string & strAppName);
         //virtual string appmatter_locator(::aura::application * papp);
         //virtual string appmatter_locator(const string & strLibraryName, const string & strAppName);
         //virtual string appmatter_locator(const string & strAppName);
         //virtual ::file::path base_appmatter_locator(const ::file::path & strBase,const string & strLibraryName,const string & strAppName);
         //virtual ::file::path base_appmatter_locator(const ::file::path & strBase,const string & strAppName);

         virtual ::file::path commonappdata(const char * pszAppId, const char * pszBuild = NULL, const char * pszPlatform = NULL, const char * pszConfiguration = NULL);
         virtual ::file::path commonappdata_locale_schema(const char * pszAppId, const char * pszBuild = NULL, const char * pszPlatform = NULL, const char * pszConfiguration = NULL, const char * pszLocale = NULL, const char * pszSchema = NULL);

         virtual ::file::path trash_that_is_not_trash(const ::file::path & psz);

         virtual ::file::path cache();
         virtual ::file::path appdata();
         virtual ::file::path commonappdata_root();
         virtual ::file::path commonappdata();
         virtual ::file::path element_commonappdata(const string & strElement);

         //virtual ::file::path usersystemappdata(::aura::application * papp,const string & lpcszPrefix);
         //virtual ::file::path userappdata(::aura::application * papp);
         //virtual ::file::path userdata(::aura::application * papp);
         //virtual ::file::path userfolder(::aura::application * papp);
         //virtual ::file::path default_os_user_path_prefix(::aura::application * papp);
         //virtual ::file::path default_userappdata(::aura::application * papp,const string & lpcszPrefix,const string & lpcszLogin);
         //virtual ::file::path default_userdata(::aura::application * papp,const string & lpcszPrefix,const string & lpcszLogin);
         //virtual ::file::path default_userfolder(::aura::application * papp,const string & lpcszPrefix,const string & lpcszLogin);
         virtual ::file::path userquicklaunch(::aura::application * papp);
         virtual ::file::path userprograms(::aura::application * papp);

         virtual ::file::path commonprograms();

         virtual ::file::path pathfind(const string & pszEnv,const string & pszTopic,const string & pszMode,::aura::application * papp);

         virtual bool initialize();

         virtual ::file::path get_api_cc();

         virtual bool update_module_path();

         virtual ::file::path favorites();

         virtual ::file::path desktop();
         virtual ::file::path document();
         virtual ::file::path download();

         virtual ::file::path music();
         virtual ::file::path video();
         virtual ::file::path image();

         virtual ::file::path dropbox(::aura::application * papp);


      };


      typedef smart_pointer < system > system_sp;


   } // namespace dir


} // namespace file
















