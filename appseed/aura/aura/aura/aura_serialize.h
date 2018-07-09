#pragma once


CLASS_DECL_AURA void xml_export(string & strXml, ::xml::exportable & xmlexportable);
CLASS_DECL_AURA void xml_import(::xml::importable & xmlimportable, string & strXml);

class serializable;
struct POINTD;

#define FIRST_VERSION 0


class CLASS_DECL_AURA serialize :
   virtual public ::file::byte_istream,
   virtual public ::file::byte_ostream
{
public:


   index                   m_iVersion;
   property_set *          m_pset;

   serialize(serialize && serialize);
   serialize(::file::file * pfile, index iVersion = FIRST_VERSION);
   serialize(::aura::application * papp, index iVersion = FIRST_VERSION);
   virtual ~serialize();


   virtual bool is_storing();


   virtual void load(::file::path path, serializable & serializable, UINT nOpenFlags = ::file::type_binary | ::file::mode_read | ::file::share_deny_write);

   virtual void save(::file::path path, serializable & serializable, UINT nOpenFlags = ::file::type_binary | ::file::mode_write | ::file::mode_truncate | ::file::mode_create | ::file::defer_create_directory | ::file::share_exclusive);

   virtual void stream_object(serializable & serializable);

   virtual void stream_file(::file::path path, ::serializable & serializable);

   virtual void stream_link(string strLink, serializable & serializable);

   virtual void stream_link(serializable & serializable);

   virtual ::file::path get_link_path(string strLink);

   bool is_version(index i);

   void prop_start(property_set & set)
   {

      m_pset = &set;

      if (!is_storing())
      {

         operator()(*m_pset);


      }

   }


   template < typename TYPE >
   void prop_serial(const char * pszName, TYPE & t)
   {

      if (is_storing())
      {

         m_pset->operator[](pszName) = t;


      }
      else
      {

         t = (TYPE)m_pset->operator[](pszName);

      }

   }

   void prop_end()
   {

      if (is_storing())
      {

         operator()(*m_pset);


      }

      m_pset = NULL;

   }


   template < typename BLOCK_TYPE >
   void blt(BLOCK_TYPE & t) // block transfer // classes/structures with no virtual members
   {
      stream(&t, sizeof(t));
   }

   template < typename ARRAY >
   void stream_array(ARRAY & a)
   {
      if (is_storing())
      {
         ::count c = a.get_count();
         operator()(c);
         for (auto & element : a)
         {
            operator()(element);
         }
      }
      else
      {
         ::count c = 0;
         operator()(c);
         a.set_size(c);
         for (auto & element : a)
         {
            operator()(element);
         }
      }
   }


   template < typename XML_SERIALIZABLE >
   void stream_as_xml(XML_SERIALIZABLE & xmlserializable)
   {

      string strXml;

      if (is_storing())
      {

         xml_export(strXml, xmlserializable);

         operator()(strXml);

      }
      else
      {

         operator()(strXml);

         xml_import(xmlserializable, strXml);

      }

   }

   template < typename SET >
   void stream_set(SET & s)
   {
      if (is_storing())
      {
         ::count c = s.get_count();
         operator()(c);
         for (auto & element : s)
         {
            operator()(element);
         }
      }
      else
      {
         ::count c = 0;
         operator()(c);
         while(c > 0)
         {
            c--;
            typename SET::BASE_TYPE element;
            operator()(element);
            s.add(element);
         }
      }
   }


   template < typename MAP >
   void stream_map(MAP & m)
   {
      if (is_storing())
      {
         ::count c = m.get_count();
         operator()(c);
         for (auto & pair : m)
         {
            operator()(pair.m_element1);
            operator()(pair.m_element2);
         }
      }
      else
      {
         ::count c = 0;
         operator()(c);
         while(c > 0)
         {
            c--;
            typename MAP::BASE_KEY element1;
            typename MAP::BASE_VALUE element2;
            operator()(element1);
            operator()(element2);
            m.set_at(element1, element2);
         }
      }
   }

   template < typename TYPE >
   void stream_array(spa(TYPE) & a)
   {
      if (is_storing())
      {
         ::count c = a.get_count();
         operator()(c);
         for (auto & element : a)
         {
            string strType = get_object_type_id(element);
            operator()(strType);
            operator()(element);
         }
      }
      else
      {
         ::count c = 0;
         operator()(c);
         a.set_size(c);
         for (auto & element : a)
         {
            string strType;
            operator()(strType);
            element = create_object_from_type_id(strType);
            operator()(element);
         }
      }
   }

   template < typename STREAMABLE >
   void operator()(STREAMABLE & streamable)
   {

      if (is_storing())
      {

         *this << streamable;

      }
      else
      {

         *this >> streamable;

      }

   }

   template < typename STREAMABLE >
   void operator()(sp(STREAMABLE) & streamable)
   {

      operator()(*streamable);

   }

   void operator()(serializable & serializable);

   void operator()(serializable * pserializable);

   virtual string get_object_type_id(::object * pelement);
   virtual ::object * create_object_from_type_id(string strType);

   //using ostream::operator <<;
   //serialize & operator << (serializable & serialize);

   //using istream::operator >>;
   //serialize & operator >> (serializable & serialize);

   virtual void stream(void * p, memory_size_t s);
   virtual void write(void * p, memory_size_t s);
   virtual memory_size_t read(void * p, memory_size_t s);


};


class CLASS_DECL_AURA reader :
   virtual public serialize
{
public:


   reader(reader && reader);
   reader(::aura::application * papp, index iVersion = FIRST_VERSION);
   reader(::file::file * pfile, index iVersion = FIRST_VERSION);
   virtual ~reader();


   virtual bool is_storing();


};


class CLASS_DECL_AURA writer :
   virtual public serialize
{
public:


   writer(writer && writer);
   writer(::aura::application * papp, index iVersion = FIRST_VERSION);
   writer(::file::file * pfile, index iVersion = FIRST_VERSION);
   virtual ~writer();


   virtual bool is_storing();


};



class CLASS_DECL_AURA serializable :
   virtual public ::object
{
public:


   virtual void stream(serialize & serialize) = 0;




};


CLASS_DECL_AURA serialize & operator << (serialize & serialize, serializable & serializable);


CLASS_DECL_AURA serialize & operator >> (serialize & serialize, serializable & serializable);






class CLASS_DECL_AURA memory_reader :
   virtual public reader
{
public:


   memory_reader(memory_reader && reader);
   memory_reader(::aura::application * papp, index iVersion = FIRST_VERSION);
   virtual ~memory_reader();


   memory & memory();


};


class CLASS_DECL_AURA memory_writer :
   virtual public writer
{
public:


   memory_writer(memory_writer && writer);
   memory_writer(::aura::application * papp, index iVersion = FIRST_VERSION);
   virtual ~memory_writer();


   memory & memory();


};
