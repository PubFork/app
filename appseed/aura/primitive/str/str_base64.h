#pragma once

class object;

namespace str
{


   class CLASS_DECL_AURA base64 :
      virtual public ::object
   {
   public:

      enum e_mode
      {

         mode_normal,
         mode_url_safe,
         mode_ex,

      };

   protected:


      uchar etable[3][256];
      uchar dtable[256];


   public:


      base64(::aura::application * papp);
      virtual ~base64();


      void encode(::stream & ostreamBase64, ::stream & istreamBinary, e_mode emode = mode_normal);
      string encode(primitive::memory_base & storageBinary, e_mode emode = mode_normal);
      string encode(byte * p, ::count ca, e_mode emode = mode_normal);
      string encode(const char * psz, e_mode emode = mode_normal);
      string encode(::object & object, e_mode emode = mode_normal);

      bool decode(::stream & ostreamBinary, ::stream & istreamBase64);
      bool decode(primitive::memory_base & storageBinary, const char * pszBase64, strsize s = -1);
      string decode(const char * psz);
      bool decode(::object & object, const char * pszBase64);

      bool is(int iChar);

   };


} // namespace str



