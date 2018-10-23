#pragma once


namespace linux
{


   namespace axis
   {


      class CLASS_DECL_AXIS dir :
         virtual public ::linux::dir,
         virtual public ::file::dir::axis::system
      {
      public:


         string      m_strCa2;


         dir(::aura::application *  papp);


         virtual ::file::listing & ls(::aura::application * app, ::file::listing & listing) override;


         virtual bool is(const ::file::path & path, ::aura::application * papp, bool bOptional = true, bool bNoCache = false) override;
         virtual bool name_is(const ::file::path & path,::aura::application * papp) override;


         virtual bool initialize();


      };


   } // namespace axis


} // namespace linux



