#pragma once

class object;

namespace str
{


   class CLASS_DECL_AURA base64 :
      virtual public ::object
   {
   protected:


      uchar etable[256];
      uchar dtable[256];


   public:


      base64(::aura::application * papp);
      virtual ~base64();


      void encode(::stream & ostreamBase64, ::stream & istreamBinary);
      string encode(primitive::memory_base & storageBinary);
      string encode(byte * p, ::count ca);
      string encode(const char * psz);
      string encode(::object & object);

      void decode(::stream & ostreamBinary, ::stream & istreamBase64);
      void decode(primitive::memory_base & storageBinary, const char * pszBase64, strsize s = -1);
      string decode(const char * psz);
      void decode(::object & object, const char * pszBase64);


   };


} // namespace str



