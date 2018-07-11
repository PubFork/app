#pragma once

#define FIRST_VERSION 0

#include "file_stream.h"
class CLASS_DECL_AURA serialize :
   virtual public ::file::stream
{
public:

   
   memory_size_t           m_gcount;
   index                   m_iVersion;
   property_set *          m_pset;
   
   serialize();
   serialize(serialize && serialize);
   serialize(::file::file * pfile, index iVersion = FIRST_VERSION);
   serialize(::aura::application * papp, index iVersion = FIRST_VERSION);
   virtual ~serialize();
   


   stream & operator = (const stream & stream);

   virtual bool is_stream_null();
   virtual bool is_stream_set();

   virtual void close();

   virtual void * get_internal_data();
   virtual memory_size_t get_internal_data_size() const;
   virtual bool set_internal_data_size(memory_size_t c);
   virtual file_position_t get_position() const;
   inline serialize & operator << (char ch                              ) { write(ch              ); return *this;}
   inline serialize & operator << (uchar uch                            ) { write(uch             ); return *this;}
   inline serialize & operator << (i16 sh                           ) { write(sh              ); return *this;}
   inline serialize & operator << (u16 ui                          ) { write(ui              ); return *this;}
#ifdef WINDOWS
   inline serialize & operator << (unichar wch                          ) { write(wch             ); return *this;}
#endif
   inline serialize & operator << (bool b                               ) { write(b               ); return *this;}
   inline serialize & operator << (i32 i                            ) { write(i               ); return *this;}
   inline serialize & operator << (u32 ui                          ) { write(ui              ); return *this;}
   inline serialize & operator << (i64 i                            ) { write(i               ); return *this;}
   inline serialize & operator << (u64 ui                          ) { write(ui              ); return *this;}
#if defined(APPLEOS)
   inline serialize & operator << (unsigned long ui                     ) { write(ui              ); return *this;}
//   inline serialize & operator << (long long ll                     ) { write(ll              ); return *this;}
#endif
   inline serialize & operator << (float f                              ) { write(f               ); return *this;}
   inline serialize & operator << (double d                             ) { write(d               ); return *this;}
   inline serialize & operator << (RECT & rect                    ) { write(rect            ); return *this;}
   inline serialize & operator << (LPRECT lpcrect                ) { write(lpcrect         ); return *this;}
   inline serialize & operator << (SIZE & size                    ) { write(size            ); return *this;}
   inline serialize & operator << (sp(type) & info                  ) { write(info            ); return *this;}
   inline serialize & operator << (std_type_info & info           ) { write(info            ); return *this;}
   inline serialize & operator << (const char * psz                     ) { write(psz             ); return *this;}
   inline serialize & operator << (id & id                        ) { write(id              ); return *this;}
   inline serialize & operator << (var & var                      ) { write(var             ); return *this;}
   inline serialize & operator << (property & property            ) { write(property        ); return *this;}
   inline serialize & operator << (string & str                   ) { write(str             ); return *this;}
   inline serialize & operator << (object * pobject) { write(pobject             ); return *this;}
   inline serialize & operator << (object & object ) { write(object             ); return *this;}
   inline serialize & operator << (e_str_flag eflag                     ) { m_estrflag = (e_str_flag)((int)m_estrflag | (int)eflag); return *this; }
   inline serialize & operator << (::file::set_width & w)
   { width(w.m_width); return *this; }
   
   
   virtual memory_size_t read(void *lpBuf, memory_size_t nCount);
   virtual void full_read(void *lpBuf, memory_size_t nCount);
   template < typename TYPE >
   void full_fill(TYPE & t)
   {
      full_read(&t, sizeof(t));
   }
   virtual void full_fill(::primitive::memory_base & m);
   
   //stream & operator = (const stream & ostream);
   
   virtual bool is_reader_null();
   virtual bool is_reader_set();
   
   virtual void read_to_hex(string & str, file_position_t iStart = -1, file_position_t iEnd = -1);
   
   
   inline serialize & operator >> (bool            & b               ) { read(b              ); return *this; }
   inline serialize & operator >> (char            & ch              ) { read(ch             ); return *this; }
   inline serialize & operator >> (uchar           & uch             ) { read(uch            ); return *this; }
#ifdef WINDOWS
   inline serialize & operator >> (unichar         & wch             ) { read(wch            ); return *this; }
#endif
   inline serialize & operator >> (i16         & sh              ) { read(sh             ); return *this; }
   inline serialize & operator >> (u16        & ui              ) { read(ui             ); return *this; }
   inline serialize & operator >> (i32         & i               ) { read(i              ); return *this; }
   inline serialize & operator >> (u32        & ui              ) { read(ui             ); return *this; }
   inline serialize & operator >> (i64         & i               ) { read(i              ); return *this; }
   inline serialize & operator >> (u64        & ui              ) { read(ui             ); return *this; }
#ifdef APPLEOS
   inline serialize & operator >> (unsigned long   & ui              ) { read(ui             ); return *this; }
//   inline serialize & operator >> (long long   & ll              ) { read(ll             ); return *this; }
#endif
   inline serialize & operator >> (float           & f               ) { read(f              ); return *this; }
   inline serialize & operator >> (double          & d               ) { read(d              ); return *this; }
   inline serialize & operator >> (LPRECT            lprect          ) { read(lprect         ); return *this; }
   inline serialize & operator >> (SIZE            & size            ) { read(size           ); return *this; }
   inline serialize & operator >> (sp(type)        & info            ) { read(info           ); return *this; }
   inline serialize & operator >> (id              & id              ) { read(id             ); return *this; }
   inline serialize & operator >> (var             & var             ) { read(var            ); return *this; }
   inline serialize & operator >> (property        & property        ) { read(property       ); return *this; }
   inline serialize & operator >> (string          & str             ) { read(str            ); return *this; }
   inline serialize & operator >> (object * pobject) { read(pobject            ); return *this; }
   inline serialize & operator >> (object & object) { read(object            ); return *this; }

   template < typename TYPE >
   void blt(const TYPE & t)
   {
      
      if(is_storing())
      {
      
         write(&t, sizeof(t));
         
      }
      else
      {
         
         memory_size_t s = read(&t, sizeof(t));
         
         if (s != sizeof(t))
         {
            
            setstate(::file::failbit);
            
         }

      }
      
   }
   
   
   virtual void write_from_hex(const void *lpBuf,memory_size_t nCount);
   virtual void write(const void *lpBuf, memory_size_t nCount);
   virtual void write(const void *lpBuf, memory_size_t nCount, memory_size_t * dwWritten);
   template < typename T >
   void full_write(const T & t) { write(&t, sizeof(T)); }
   
   //virtual void read(reader & reader);
   
   //ostream & operator = (const ostream & writer);
   
   virtual bool is_writer_null();
   virtual bool is_writer_set();
   
   //virtual void close();
   
   virtual void flush();
   
   virtual void set_length(file_size_t len);
   
   
   
   //      virtual void write(int32_t i);
   //      virtual void write(uint32_t ui);
   //      virtual void write(int64_t i);
   //      virtual void write(uint64_t ui);
   //      virtual void write(uint64_t ui, int signal);
   
   
   
   virtual void write (char ch);
   virtual void write (uchar uch);
   virtual void write (i16 sh);
   virtual void write (u16 ui);
#ifdef WINDOWS
   virtual void write (unichar wch);
#endif
   virtual void write (bool b);
   virtual void write (i32 i);
   virtual void write (u32 ui);
   virtual void write (i64 i);
   virtual void write (u64 ui);
#if defined(APPLEOS)
   virtual void write (unsigned long ui);
   //virtual void write (long long ll);
#endif
   virtual void write (float f);
   virtual void write (double d);
   virtual void write (RECT & rect);
   virtual void write (LPRECT lpcrect);
   virtual void write (SIZE & size);
   virtual void write (sp(type) & info);
   virtual void write (std_type_info & info);
   virtual void write (const char * psz);
   virtual void write (id & id);
   virtual void write (var & var);
   virtual void write (property & property);
   virtual void write (string & str);
   virtual void write (object * pobject);
   virtual void write (object & object);
   
   inline file_position_t tellp();
   inline serialize & seekp(file_position_t position);
   inline serialize & seekp(file_offset_t offset, ::file::e_seek eseek);
   
   
   serialize & put(char ch);

   //      virtual void read(int32_t & i);
   //      virtual void read(uint32_t & ui);
   //      virtual void read(int64_t & i);
   //      virtual void read(uint64_t & ui);
   
   
   virtual void read (bool & b);
   virtual void read (char & ch);
   virtual void read (uchar & uch);
#ifdef WINDOWS
   virtual void read (unichar & wch);
#endif
   virtual void read (i16 & sh);
   virtual void read (u16 & ui);
   virtual void read (i32 & i);
   virtual void read (u32 & ui);
   virtual void read (i64 & i);
   virtual void read (u64 & ui);
#ifdef APPLEOS
   virtual void read (unsigned long & ui);
   //virtual void read (long long & ui);
#endif
   virtual void read (float & f);
   virtual void read (double & d);
   virtual void read (LPRECT lprect);
   virtual void read (SIZE & size);
   virtual void read (sp(type) & info);
   virtual void read (id & id);
   virtual void read (var & var);
   virtual void read (property & property);
   virtual void read (string & str);
   virtual void read (object * pobject);
   virtual void read (object & object);
   
   virtual serialize & getline(char * sz, strsize n);
   virtual int get();
   virtual int peek();
   
   inline memory_size_t gcount();
   inline file_position_t tellg();
   inline serialize & seekg(file_position_t position);
   inline serialize & seekg(file_offset_t offset, ::file::e_seek eseek);
   
   inline file_size_t get_left();

//   //using ostream::write;
//   virtual void write (char ch);
//   virtual void write (uchar uch);
//   virtual void write (i16 sh);
//   virtual void write (u16 ui);
//#ifdef WINDOWS
//   virtual void write (unichar wch);
//#endif
//#ifdef APPLEOS
//   virtual void write (unsigned long ul);
//#endif
//   virtual void write (bool b);
//   virtual void write (i32 i);
//   virtual void write (u32 ui);
//   virtual void write (i64 i);
//   virtual void write (u64 ui);
//   virtual void write (float f);
//   virtual void write (double d);
//   virtual void write (RECT & rect);
//   virtual void write (LPRECT lpcrect);
//   virtual void write (SIZE & size);
//   virtual void write (sp(type) info);
//   virtual void write (char * psz);
//   virtual void write (id & id);
//   virtual void write (var & var);
//   virtual void write (property & property);
//   virtual void write (string & str);
//   virtual void write (std_type_info & info);

   
   virtual bool is_storing();
   
   
   virtual void load(::file::path path, object & object, UINT nOpenFlags = ::file::type_binary | ::file::mode_read | ::file::share_deny_write);
   
   virtual void save(::file::path path, object & object, UINT nOpenFlags = ::file::type_binary | ::file::mode_write | ::file::mode_truncate | ::file::mode_create | ::file::defer_create_directory | ::file::share_exclusive);
   
   virtual void stream_object(object & object);
   
   virtual void stream_file(::file::path path, ::object & object);
   
   virtual void stream_link(string strLink, object & object);
   
   virtual void stream_link(object & object);
   
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
   void prop_serial(const char * pszName, TYPE & t);
   
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

   template < typename BLOCK_TYPE >
   void oblt(BLOCK_TYPE & t) // block transfer // classes/structures with no virtual members
   {
      write(&t, sizeof(t));
   }

   template < typename BLOCK_TYPE >
   void iblt(BLOCK_TYPE & t) // block transfer // classes/structures with no virtual members
   {
      
      memory_size_t s = read(&t, sizeof(t));
      
      if (s != sizeof(t))
      {
         
         setstate(::file::failbit);
         
      }
      
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
   
   virtual void operator()(::object & object);
   
   virtual void operator()(::object * pserializable);
   
   virtual string get_object_type_id(::object * pelement);
   virtual ::object * create_object_from_type_id(string strType);
   
   //using ostream::operator <<;
   //serialize & operator << (object & serialize);
   
   //using istream::operator >>;
   //serialize & operator >> (object & serialize);
   
   //using byte_stream::write;
   //using byte_stream::read;
   virtual void stream(void * p, memory_size_t s);
   //virtual void write(void * p, memory_size_t s);
   //virtual memory_size_t read(void * p, memory_size_t s);

};





CLASS_DECL_AURA void xml_export(string & strXml, ::xml::exportable & xmlexportable);
CLASS_DECL_AURA void xml_import(::xml::importable & xmlimportable, string & strXml);


//class object;
//struct POINTD;
//
//
//#define FIRST_VERSION 0
//
//
//class CLASS_DECL_AURA serialize :
//virtual public ::file::byte_stream
//{
//public:
//
//
//
//
//
//
//};
//

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






CLASS_DECL_AURA serialize & operator << (serialize & serialize, object & object);


CLASS_DECL_AURA serialize & operator >> (serialize & serialize, object & object);






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



inline ::file::stream & operator << (::file::stream & os, ::file::stream & (*pfnSimpleOutput)(::file::stream &))
{
   return (*pfnSimpleOutput)(os);
}

namespace std
{
   
   
   inline serialize & endl(serialize & os)
   {
      
      os.put('\n');
      
      os.flush();
      
      return os;
      
   }
   
   
} // namespace std

