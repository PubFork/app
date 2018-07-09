#include "framework.h"


serialize::serialize(serialize && serialize) :
   ::object(::move(serialize)),
   ::file::istream(::move(serialize)),
   ::file::ostream(::move(serialize)),
   m_iVersion(serialize.m_iVersion)
{

   m_pset = NULL;

}


serialize::serialize(::file::file * pfile, index iVersion) :
   ::object(pfile->get_app())
{

   m_pset = NULL;

   m_spfile = pfile;

   m_iVersion = iVersion;

}


serialize::serialize(::aura::application * papp, index iVersion) :
   ::object(papp)
{

   m_pset = NULL;

   m_iVersion = iVersion;

}


serialize::~serialize()
{


}


bool serialize::is_storing()
{

   return m_spfile->has_write_mode();

}


void serialize::write(void * p, memory_size_t s)
{

   ostream::write(p, s);

}


memory_size_t serialize::read(void * p, memory_size_t s)
{

   return istream::read(p, s);

}


string serialize::get_object_type_id(::object * pelement)
{

   return System.get_type_info(typeid(*pelement))->m_id;

}


::object * serialize::create_object_from_type_id(string strType)
{

   return System.alloc(System.get_type_info((id)strType));
}


void serialize::stream(void * p, memory_size_t s)
{

   if (is_storing())
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

void serialize::stream_object(serializable & serializable)
{

   serializable.stream(*this);

}


void serialize::operator()(serializable & serializable)
{

   stream_object(serializable);

}

void serialize::operator()(serializable * pserializable)
{

   stream_object(*pserializable);

}


//serialize & serialize::operator << (serializable & serialize)
//{
//
//   stream_object(serialize);
//
//   return *this;
//
//}
//
//
//serialize & serialize::operator >> (serializable & serialize)
//{
//
//   stream_object(serialize);
//
//   return *this;
//
//}


bool serialize::is_version(index i)
{

   return i <= m_iVersion;

}



void serializable::stream(::serialize & serialize)
{

}




void serialize::stream_file(::file::path path, ::serializable & serializable)
{

   if (path.is_empty())
   {

      throw io_exception(get_app(), "link path is empty");

   }

   ::serialize serialize(get_app());

   UINT nOpenFlags;

   if (is_storing())
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

   if (is_storing())
   {

      strLink = serializable.oprop("read_only_link");

      bool bReadOnly = strLink.has_char();

      operator()(bReadOnly);

      if (!bReadOnly)
      {

         strLink = serializable.oprop("link");

         //if (strLink.is_empty())
         {

            // throw io_exception(get_app(), "link property is missing");
            //return;

         }

      }

      operator()(strLink);

      if (bReadOnly)
      {

         return;

      }

   }
   else
   {

      bool bReadOnly;

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

   if (strLink.has_char())
   {

      stream_link(strLink, serializable);

   }

}


void serialize::stream_link(string strLink, serializable & serializable)
{

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



void serialize::load(::file::path path, serializable & serializable, UINT nOpenFlags)
{

   ::file::file_sp pfile = Application.file().get_file(path, nOpenFlags);

   if (pfile.is_null())
   {

      return;

   }

   m_spfile = pfile;

   ASSERT(!pfile->has_write_mode());

   if (pfile->has_write_mode())
   {

      return;

   }

   try
   {

      operator()(serializable);

   }
   catch (...)
   {


   }

   m_spfile.release();

}


void serialize::save(::file::path path, serializable & serializable, UINT nOpenFlags)
{

   ::file::file_sp pfile = Application.file().get_file(path, nOpenFlags);

   if (pfile.is_null())
   {

      return;

   }

   m_spfile = pfile;

   ASSERT(pfile->has_write_mode());

   if (!pfile->has_write_mode())
   {

      return;

   }

   try
   {

      operator()(serializable);

   }
   catch (...)
   {


   }

   m_spfile.release();

}


reader::reader(reader && reader) :
   ::object(::move(reader)),
   ::serialize(::move(reader))
{

}


reader::reader(::aura::application * papp, index iVersion) :
   ::object(papp),
   ::serialize(papp, iVersion)
{

}


reader::reader(::file::file * pfile, index iVersion) :
   ::object(pfile->get_app()),
   ::serialize(pfile->get_app(), iVersion)
{

   m_spfile = pfile;

}


reader::~reader()
{

}


bool reader::is_storing()
{

   return false;

}


writer::writer(writer && writer) :
   ::object(::move(writer)),
   ::serialize(::move(writer))
{

}


writer::writer(::aura::application * papp, index iVersion) :
   ::object(papp),
   ::serialize(papp, iVersion)
{

}



writer::writer(::file::file * pfile, index iVersion) :
   ::object(pfile->get_app()),
   ::serialize(pfile->get_app(), iVersion)
{

   m_spfile = pfile;

}


writer::~writer()
{

}



bool writer::is_storing()
{

   return true;

}




CLASS_DECL_AURA serialize & operator << (serialize & serialize, serializable & serializable)
{

   ASSERT(serialize.is_storing());

   serialize.stream_object(serializable);

   return serialize;

}


CLASS_DECL_AURA serialize & operator >> (serialize & serialize, serializable & serializable)
{

   ASSERT(!serialize.is_storing());

   serialize.stream_object(serializable);

   return serialize;

}




memory_reader::memory_reader(memory_reader && reader) :
   object(::move(reader)),
   ::serialize(::move(reader)),
   ::reader(::move(reader))
{


}


memory_reader::memory_reader(::aura::application * papp, index iVersion) :
   object(papp),
   ::serialize(papp, iVersion),
   ::reader(papp, iVersion)
{

   m_spfile = canew(memory_file(papp));

}


memory_reader::~memory_reader()
{

}


memory & memory_reader::memory()
{

   return *m_spfile.cast < ::memory_file >()->get_primitive_memory();

}


memory_writer::memory_writer(memory_writer && reader) :
   object(::move(reader)),
   ::serialize(::move(reader)),
   ::writer(::move(reader))
{


}


memory_writer::memory_writer(::aura::application * papp, index iVersion) :
   object(papp),
   ::serialize(papp, iVersion),
   ::writer(papp, iVersion)
{

   m_spfile = canew(memory_file(papp));

}


memory_writer::~memory_writer()
{

}


memory & memory_writer::memory()
{

   return *m_spfile.cast < ::memory_file >()->get_primitive_memory();

}

