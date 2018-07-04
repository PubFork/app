#include "framework.h"


serialize::serialize(::aura::application * papp) :
   ::object(papp)
{

   m_iVersion = 0;

}


serialize::~serialize()
{


}


void serialize::write(void * p, memory_size_t s)
{

   m_spfile->write(p, s);

}


memory_size_t serialize::read(void * p, memory_size_t s)
{

   return m_spfile->read(p, s);

}


void serialize::stream(void * p, memory_size_t s)
{

   if (m_bStoring)
   {

      write(p, s);

   }
   else
   {

      memory_size_t iRead = read(p, s);

      if (iRead != s)
      {

         throw io_exception(get_app());

      }

   }

}

void serialize::stream(serializable & serializable)
{

   serializable.stream(*this);

}


bool serialize::is_version(index i)
{

   return i <= m_iVersion;

}



void serializable::stream(serialize & serialize)
{

   if (serialize.m_bStoring)
   {

      serialize << *this;

   }
   else
   {

      serialize >> *this;

   }

}


void serialize::stream_file(::file::path path, ::serializable & serializable)
{

   if (path.is_empty())
   {

      throw io_exception(get_app(), "link path is empty");

   }

   ::serialize serialize(get_app());

   serialize.m_bStoring = m_bStoring;

   UINT nOpenFlags;

   if (m_bStoring)
   {

      nOpenFlags = ::file::type_binary | ::file::mode_write | ::file::mode_create | ::file::mode_truncate | ::file::defer_create_directory | ::file::share_exclusive;

   }
   else
   {

      nOpenFlags = ::file::type_binary | ::file::mode_read | ::file::share_deny_write;

   }

   serialize.m_spfile = Application.file().get_file(path, nOpenFlags);

   serialize(serializable);

}


void serialize::stream_link(serializable & serializable)
{

   string strLink;

   if (m_bStoring)
   {

      strLink = serializable.oprop("read_only_link");

      bool bReadOnly = strLink.has_char();

      operator()(bReadOnly);

      if (bReadOnly)
      {

         if (m_bStoring)
         {

            return;

         }

      }
      else
      {

         strLink = serializable.oprop("link");

         if (strLink.is_empty())
         {

            throw io_exception(get_app(), "link property is missing");

         }

      }

      operator()(strLink);

   }
   else
   {

      bool bReadOnly;

      string strLink;

      operator()(bReadOnly);

      operator()(strLink);

      if (bReadOnly)
      {

         serializable.oprop("read_only_link") = strLink;

      }
      else
      {

         serializable.oprop("link") = strLink;

      }

   }

   ::file::path path = get_link_path(strLink);

   if (path.is_empty())
   {

      oprop("failed_link").stra().add(strLink);

      return;

   }

   try
   {

      stream_file(path, serializable);

   }
   catch (...)
   {

      oprop("failed_link").stra().add(strLink);

   }

}


::file::path serialize::get_link_path(string strLink)
{

   return "";

}



//namespace file
//{
//
//
//   serialize::serialize(::aura::application * papp) :
//      ::object(papp),
//      ::serialize(papp)
//   {
//
//
//   }
//
//
//   serialize::~serialize()
//   {
//
//   }
//
//
//   void serialize::operator()(void * p, memory_size_t s)
//   {
//
//      if (m_bStoring)
//      {
//
//         m_pfile->write(p, s);
//
//      }
//      else
//      {
//
//         memory_size_t iRead = m_pfile->read(p, s);
//
//         if (iRead != s)
//         {
//
//            throw io_exception(get_app());
//
//         }
//
//      }
//
//   }
//
//
//} // namespace file
//
//
//
