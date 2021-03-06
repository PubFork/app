#pragma once


namespace fs
{


// fs::interface - file system interface


   class CLASS_DECL_AXIS data :
      virtual public ::data::data,
      virtual public ::file::listing_provider
   {
   public:

      
      data(::aura::application * papp);


      // optional if ls_dir is implemented
      virtual bool has_subdir(const ::file::path & pszPath);
      virtual ::file::listing & ls(::file::listing & listing);
      virtual ::file::listing & ls_relative_name(::file::listing & listing);
      virtual int is_dir(const ::file::path & pszPath);
      virtual ::file::listing & root_ones(::file::listing & listing);
      //virtual void get_ascendants_path(const ::file::path & pszPath,::file::patha & stra);
      //virtual void get_ascendants_name(const ::file::path & lpcsz,::file::patha & straParam);
      //virtual string eat_end_level(const ::file::path & pszPath,int32_t iCount);


      virtual bool tree_show_subdir(const ::file::path & pszPath);


      //virtual string file_name(const char * pszPath);
      //virtual string dir_path(const char * psz1, const char * psz2);

      virtual bool file_exists(const ::file::path & pszPath);
      virtual var file_length(const ::file::path & pszPath);


      virtual bool file_move(const ::file::path & pszDst,const ::file::path & pszSrc);

      virtual ::file::file_sp get_file(const ::file::path & path,UINT nOpenFlags,cres * pfesp);


      virtual bool fast_has_subdir(const ::file::path & pszPath);

      virtual sp(data) path_data(const ::file::path & psz);
      virtual sp(data) node_path_data(const ::file::path & psz);


      virtual bool is_link(const ::file::path & psz);

      virtual bool is_zero_latency(const ::file::path & psz);


      virtual ::file::listing & perform_file_listing(::file::listing & listing) override;
      virtual ::file::listing & perform_file_relative_name_listing(::file::listing & listing) override;


   };


} // namespace fs








