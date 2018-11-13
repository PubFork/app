#pragma once


namespace macos
{
   

   class CLASS_DECL_AURA dir :
      virtual public ::file::dir::system
   {
   public:
      
      
      
       ::file::path            m_strTimeFolder;
       ::file::path            m_strNetSeedFolder;
       
       ::file::path            m_strCa2;
       ::file::path            m_strCommonAppData;
       ::file::path            m_strAppData;
       ::file::path            m_strPrograms;
       ::file::path            m_strCommonPrograms;
       ::file::path            m_strCa2AppData;
      
       dir(::aura::application * papp);
       
       
       //virtual void update_module_path();
       
       
       // rls fetchs should set a meaningful m_iRelative value at each returned path
       virtual ::file::listing & ls(::aura::application * papp, ::file::listing & path) override;
       
       
       virtual bool  is(const ::file::path & path, ::aura::application * papp, bool bOptional = true, bool bNoCache = false) override;
       virtual bool  is_inside(const ::file::path & pathFolder,const ::file::path & path,::aura::application * papp) override;
       virtual bool  is_inside_time(const ::file::path & path,::aura::application * papp) override;
       virtual bool  name_is(const ::file::path & path,::aura::application * papp) override;
       virtual bool  has_subdir(::aura::application * papp, const ::file::path & path) override;
       
       virtual ::file::listing & root_ones(::file::listing & listing,::aura::application * papp) override;
       virtual bool mk(const ::file::path & path,::aura::application * papp) override;
       virtual bool rm(::aura::application * papp, const ::file::path & path, bool bRecursive = true) override;
       
       
       virtual ::file::path name(const ::file::path & path);
       
       virtual ::file::path time() override;
       virtual ::file::path stage() override;
       virtual ::file::path stageapp() override;
       virtual ::file::path netseed() override;
       virtual ::file::path install() override;
//       virtual ::file::path profile();
       
       virtual ::file::path module() override;
       virtual ::file::path ca2module() override;
       virtual ::file::path time_square(::aura::application * papp, const string & strPrefix = cnull, const string & strSuffix = cnull);
       virtual ::file::path time_log();
       
       
       virtual ::file::path trash_that_is_not_trash(const ::file::path & path) override;
       
       
       
       virtual ::file::path appdata() override;
       virtual ::file::path commonappdata_root() override;
       virtual ::file::path commonappdata() override;
       
//       virtual ::file::path usersystemappdata(::aura::application * papp, const char * lpcszPrefix);
//       virtual ::file::path userappdata(::aura::application * papp);
//       virtual ::file::path userdata(::aura::application * papp);
//       //virtual ::file::path userfolder(::aura::application * papp);
//       virtual ::file::path default_os_user_path_prefix(::aura::application * papp);
//       virtual ::file::path default_userappdata(::aura::application * papp,const string & lpcszPrefix,const string & lpcszLogin );
//       virtual ::file::path default_userdata(::aura::application * papp,const string & lpcszPrefix,const string & lpcszLogin);
//       virtual ::file::path default_userfolder(::aura::application * papp,const string & lpcszPrefix,const string & lpcszLogin);
       virtual ::file::path userquicklaunch(::aura::application * papp) override;
       virtual ::file::path userprograms(::aura::application * papp) override;
       
       virtual ::file::path commonprograms() override;
       
       virtual bool initialize() override;
       
      virtual ::file::path home() override;
      virtual ::file::path desktop() override;
      virtual ::file::path document() override;
      virtual ::file::path download() override;
      
      virtual ::file::path music() override;
      virtual ::file::path video() override;
      virtual ::file::path image() override;
      
      
   };
   
   
} // namespace macos








