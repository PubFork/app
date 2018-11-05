#pragma once


namespace file
{


   class CLASS_DECL_AURA file_stream:
      virtual public stream
   {
   public:


      file_stream();
      file_stream(const char * lpszFileName,uint32_t nOpenFlags,::aura::application * papp = ::get_app());
      file_stream(file * preader);
//      file_stream(const file_stream & preader);
      virtual ~file_stream();


      void open(const ::file::path & lpszFileName,uint32_t nOpenFlags,::aura::application * papp = ::get_app());


   };


} // namespace file


