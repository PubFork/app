#include "framework.h"



namespace file
{


   file_stream::file_stream()
   {

   }


   file_stream::file_stream(const char * lpszFileName,uint32_t nOpenFlags,::aura::application * papp)
   {

      open(lpszFileName,nOpenFlags,papp);

   }


   file_stream::file_stream(file * preader)
   {

      m_spfile = preader;

   }

//   file_stream::file_stream(const file_stream & istream)
//   {
//
//      m_spfile = istream.m_spfile;
//
//   }

   file_stream::~file_stream()
   {


   }


} // namespace file









