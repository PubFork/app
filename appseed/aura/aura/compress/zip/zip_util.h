#pragma once


namespace zip
{


   class CLASS_DECL_AURA util
   {
   public:


      util();
      virtual ~util();


      virtual bool ls(::aura::application * papp, ::file::listing & listing);
      virtual bool extract(::aura::application * papp, memory & m, const char * lpszFileName);
      virtual bool extract(::aura::application * papp, const char * lpszFileName, const char * lpszExtractFileName, ::file::e_type * petype = NULL);
      virtual bool extract_all(::aura::application * papp,const char * pszDir,var varFile,stringa * pstraFilter = NULL,bool_array * pbaBeginsFilterEat = NULL);
      virtual bool is_file_or_dir(::aura::application * papp, const char * pszPath, ::file::e_type * petype);
      virtual bool is_unzippable(::aura::application * papp, const char * lpszFileName);
      virtual bool has_sub_folder(::aura::application * papp, const char * lpszFileName);


   };


} // namespace zip



