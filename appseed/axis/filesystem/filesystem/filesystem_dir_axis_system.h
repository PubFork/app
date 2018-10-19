#pragma once


#ifdef WINDOWSEX

#include "aura/node/windows/windows_dir.h"

#endif


namespace zip
{


   class Util;


}


namespace file
{


   namespace dir
   {


      namespace axis
      {


         class CLASS_DECL_AXIS system:
            virtual public ::file::dir::system
         {
         public:


            system(::aura::application * papp);
            virtual ~system();


            virtual ::file::listing & ls(::aura::application * papp,listing & listing) override;
            virtual ::file::listing & ls_relative_name(::aura::application * papp, listing & listing) override;

            virtual bool  is_impl(const ::file::path & str, ::aura::application * papp, bool bOptional, bool bNoCache) override;

            virtual bool  is_cached(bool & bIs,const ::file::path & lpcsz,::aura::application * papp) override;

            virtual bool  name_is(const ::file::path & str,::aura::application * papp) override;

            virtual ::file::path get_api_cc() override;


         };


      } // namespace axis


   } // namespace dir


} // namespace file



