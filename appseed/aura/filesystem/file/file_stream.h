#pragma once

#define FIRST_VERSION 0



#include "file_seekable.h"
#include "file_writer.h"
#include "file_reader.h"


enum e_str_flag
{

   str_flag_ifnumberspace = 1,
   str_flag_ifnumberparenthesize = 2,
   str_flag_ifnumberparenthesizeandspace = 3,

};


namespace file
{


   class set_width
   {
   public:

      set_width(file_size_t n = 0) { m_width = n; }

      file_size_t m_width;

   };


   enum e_iostate
   {
      goodbit = 0x00,
      eofbit = 0x01,
      failbit = 0x02,
      badbit = 0x04,
      _Hardfail = 0x10
   };


   enum e_open
   {
      mode_read = (i32)0x000001,
      mode_write = (i32)0x000002,
      mode_read_write = (i32)0x000003,
      share_compat = (i32)0x000000,
      share_exclusive = (i32)0x000010,
      share_deny_write = (i32)0x000020,
      share_deny_read = (i32)0x000030,
      share_deny_none = (i32)0x000040,
      mode_no_inherit = (i32)0x000080,
      mode_create = (i32)0x001000,
      mode_no_truncate = (i32)0x002000,
      type_text = (i32)0x004000, // type_text and type_binary are used in
      type_binary = (i32)0x008000, // derived classes only
      defer_create_directory = (i32)0x010000,
      hint_unknown_length_supported = (i32)0x020000,
      mode_truncate = (i32)0x040000,
      no_call_stack = (i32)0x080000,
      no_cache = (i32)0x100000,
      binary = type_binary,
      out = mode_write,
      in = mode_read,
      trunc = mode_truncate
   };


   enum fmtflags
   {
      nofmtflags = 0,
      boolalpha = 0x00000001,
      showbase = 0x00000002,
      showpoint = 0x00000004,
      showpos = 0x00000008,
      skipws = 0x00000010,
      unitbuf = 0x00000020,
      uppercase = 0x00000040,
      dec = 0x00000080,
      hex = 0x00000100,
      oct = 0x00000200,
      fixed = 0x00000400,
      scientific = 0x00000800,
      internal = 0x00001000,
      left = 0x00002000,
      right = 0x00004000,
      adjustfield = left | right | internal,
      basefield = dec | oct | hex,
      floatfield = scientific | fixed
   };

}

class CLASS_DECL_AURA stream :
   virtual public ::file::seekable,
   virtual public ::file::reader,
   virtual public ::file::writer
{
public:

   e_str_flag              m_estrflag;
   ::file::file_sp         m_spfile;
   ::file::e_iostate       m_iostate;
   ::file::fmtflags        m_fmtflags;
   file_size_t             m_width;
   file_size_t             m_precision;
   memory_size_t           m_gcount;
   index                   m_iVersion;
   property_set *          m_pset;

   stream();
   stream(stream && stream);
   stream(::file::file * pfile, index iVersion = FIRST_VERSION);
   stream(::aura::application * papp, index iVersion = FIRST_VERSION);
   // ::stream shouldn't be instantiable, it should be only interface
   // or routing/convenience/helper members/implementations
   virtual ~stream() = 0;



   ::file::fmtflags setf(::file::fmtflags flagsAdd);
   ::file::fmtflags setf(::file::fmtflags flagsAdd, ::file::fmtflags flagsRemove);



   ::file::fmtflags flags() const;


   ::file::fmtflags flags(::file::fmtflags flags);


   ::file::e_iostate rdstate() const
   {
      return m_iostate;
   }

   bool operator ! ()
   {
      return fail();
   }

   bool bad() const
   {
      return (m_iostate & ::file::badbit) != 0;
   }

   bool fail() const
   {
      return ((int) m_iostate & ((int) ::file::badbit | (int) ::file::failbit)) != 0;
   }

   bool eof() const
   {
      return (m_iostate & ::file::eofbit) != 0;
   }

   bool good() const
   {
      return m_iostate == ::file::goodbit;
   }

   void setstate(int state)
   {
      clear((::file::e_iostate) (rdstate() | state));
   }

   void clear(int state = ::file::goodbit)
   {
      m_iostate = (::file::e_iostate) state;
   }

   virtual string GetFilePath() const;

   string fileName() { return GetFilePath(); }

   virtual void close();

   using seekable::seek;
   virtual file_position_t seek(file_offset_t offset, ::file::e_seek eseek);


   file_size_t precision() const;

   file_size_t precision(file_size_t prec);

   file_size_t width() const;

   file_size_t width(file_size_t wide);

   virtual bool is_open() const;


   virtual bool is_stream_null();
   virtual bool is_stream_set();

   virtual void * get_internal_data();
   virtual memory_size_t get_internal_data_size() const;
   virtual bool set_internal_data_size(memory_size_t c);
   virtual file_position_t get_position() const;



   inline stream & operator << (char ch) { write(ch); return *this; }
   inline stream & operator << (uchar uch) { write(uch); return *this; }
   inline stream & operator << (i16 sh) { write(sh); return *this; }
   inline stream & operator << (u16 ui) { write(ui); return *this; }
#ifdef WINDOWS
   inline stream & operator << (unichar wch) { write(wch); return *this; }
#endif
   inline stream & operator << (bool b) { write(b); return *this; }
   inline stream & operator << (i32 i) { write(i); return *this; }
   inline stream & operator << (u32 ui) { write(ui); return *this; }
   inline stream & operator << (i64 i) { write(i); return *this; }
   inline stream & operator << (u64 ui) { write(ui); return *this; }
#if defined(APPLEOS)
   inline stream & operator << (const unsigned long ui) { write(ui); return *this; }
   //   inline stream & operator << (long long ll                     ) { write(ll              ); return *this;}
#endif
   inline stream & operator << (float f) { write(f); return *this; }
   inline stream & operator << (double d) { write(d); return *this; }
   inline stream & operator << (RECT & rect) { write(rect); return *this; }
   inline stream & operator << (LPRECT lpcrect) { write(lpcrect); return *this; }
   inline stream & operator << (SIZE & size) { write(size); return *this; }
   inline stream & operator << (sp(type) & info) { write(info); return *this; }
   inline stream & operator << (std_type_info & info) { write(info); return *this; }
   inline stream & operator << (const char * psz) { write(psz); return *this; }
   inline stream & operator << (id & id) { write(id); return *this; }
   inline stream & operator << (var & var) { write(var); return *this; }
   inline stream & operator << (property & property) { write(property); return *this; }
   inline stream & operator << (string & str) { write(str); return *this; }
   inline stream & operator << (simple_object * pobject) { write(pobject); return *this; }
   inline stream & operator << (simple_object & object) { write(object); return *this; }
   inline stream & operator << (e_str_flag eflag) { m_estrflag = (e_str_flag)((int)m_estrflag | (int)eflag); return *this; }
   inline stream & operator << (::file::set_width & w)
   {
      width(w.m_width); return *this;
   }


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


   inline stream & operator >> (bool            & b) { read(b); return *this; }
   inline stream & operator >> (char            & ch) { read(ch); return *this; }
   inline stream & operator >> (uchar           & uch) { read(uch); return *this; }
#ifdef WINDOWS
   inline stream & operator >> (unichar         & wch) { read(wch); return *this; }
#endif
   inline stream & operator >> (i16         & sh) { read(sh); return *this; }
   inline stream & operator >> (u16        & ui) { read(ui); return *this; }
   inline stream & operator >> (i32         & i) { read(i); return *this; }
   inline stream & operator >> (u32        & ui) { read(ui); return *this; }
   inline stream & operator >> (i64         & i) { read(i); return *this; }
   inline stream & operator >> (u64        & ui) { read(ui); return *this; }
#ifdef APPLEOS
   inline stream & operator >> (unsigned long   & ui) { read(ui); return *this; }
#endif
   inline stream & operator >> (float           & f) { read(f); return *this; }
   inline stream & operator >> (double          & d) { read(d); return *this; }
   inline stream & operator >> (LPRECT            lprect) { read(lprect); return *this; }
   inline stream & operator >> (SIZE            & size) { read(size); return *this; }
   inline stream & operator >> (sp(type)        & info) { read(info); return *this; }
   inline stream & operator >> (id              & id) { read(id); return *this; }
   inline stream & operator >> (var             & var) { read(var); return *this; }
   inline stream & operator >> (property        & property) { read(property); return *this; }
   inline stream & operator >> (string          & str) { read(str); return *this; }
   inline stream & operator >> (simple_object * pobject) { read(pobject); return *this; }
   inline stream & operator >> (simple_object & object) { read(object); return *this; }

   template < typename TYPE >
   void blt(const TYPE & t)
   {

      if (is_storing())
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


   virtual void write_from_hex(const void *lpBuf, memory_size_t nCount);
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





   virtual void write(char ch);
   virtual void write(uchar uch);
   virtual void write(i16 sh);
   virtual void write(u16 ui);
#ifdef WINDOWS
   virtual void write(unichar wch);
#endif
   virtual void write(bool b);
   virtual void write(i32 i);
   virtual void write(u32 ui);
   virtual void write(i64 i);
   virtual void write(u64 ui);
#if defined(APPLEOS)
   virtual void write(unsigned long ui);
   //virtual void write (long long ll);
#endif
   virtual void write(float f);
   virtual void write(double d);
   virtual void write(RECT & rect);
   virtual void write(LPRECT lpcrect);
   virtual void write(SIZE & size);
   virtual void write(sp(type) & info);
   virtual void write(std_type_info & info);
   virtual void write(const char * psz);
#ifdef WINDOWS
   virtual void write(const unichar * wch);
#endif
   virtual void write(id & id);
   virtual void write(var & var);
   virtual void write(property & property);
   virtual void write(string & str);
   virtual void write(simple_object * pobject);
   virtual void write(simple_object & object);

   inline file_position_t tellp();
   inline stream & seekp(file_position_t position);
   inline stream & seekp(file_offset_t offset, ::file::e_seek eseek);


   stream & put(char ch);

   //      virtual void read(int32_t & i);
   //      virtual void read(uint32_t & ui);
   //      virtual void read(int64_t & i);
   //      virtual void read(uint64_t & ui);


   virtual void read(bool & b);
   virtual void read(char & ch);
   virtual void read(uchar & uch);
#ifdef WINDOWS
   virtual void read(unichar & wch);
#endif
   virtual void read(i16 & sh);
   virtual void read(u16 & ui);
   virtual void read(i32 & i);
   virtual void read(u32 & ui);
   virtual void read(i64 & i);
   virtual void read(u64 & ui);
#ifdef APPLEOS
   virtual void read(unsigned long & ui);
   //virtual void read (long long & ui);
#endif
   virtual void read(float & f);
   virtual void read(double & d);
   virtual void read(LPRECT lprect);
   virtual void read(SIZE & size);
   virtual void read(sp(type) & info);
   virtual void read(id & id);
   virtual void read(var & var);
   virtual void read(property & property);
   virtual void read(string & str);
   virtual void read(simple_object * pobject);
   virtual void read(simple_object & object);

   virtual stream & getline(char * sz, strsize n);
   virtual int get();
   virtual int peek();

   inline memory_size_t gcount();
   inline file_position_t tellg();
   inline stream & seekg(file_position_t position);
   inline stream & seekg(file_offset_t offset, ::file::e_seek eseek);

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


   virtual void load(::file::path path, simple_object & object, UINT nOpenFlags = ::file::type_binary | ::file::mode_read | ::file::share_deny_write);

   virtual void save(::file::path path, simple_object & object, UINT nOpenFlags = ::file::type_binary | ::file::mode_write | ::file::mode_truncate | ::file::mode_create | ::file::defer_create_directory | ::file::share_exclusive);

   virtual void load();

   virtual void save();

   virtual void load_file(::file::path path, simple_object & object, UINT nOpenFlags = ::file::type_binary | ::file::mode_read | ::file::share_deny_write);

   virtual void save_file(::file::path path, simple_object & object, UINT nOpenFlags = ::file::type_binary | ::file::mode_write | ::file::mode_truncate | ::file::mode_create | ::file::defer_create_directory | ::file::share_exclusive);

   virtual void load_file();

   virtual void save_file();

   virtual var get_var_file();

   virtual ::file::path get_file_path();

   virtual void stream_object(simple_object & object);

   virtual void stream_file(::file::path path, ::simple_object & object);

   virtual void stream_link(string strLink, ::object & object);

   virtual void stream_link(::object & object);

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
      io(&t, sizeof(t));
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
            if (fail())
               break;
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
            if (fail())
               break;
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
            if (fail())
               break;
         }
      }
      else
      {
         ::count c = 0;
         operator()(c);
         while (c > 0)
         {
            c--;
            typename SET::BASE_TYPE element;
            operator()(element);
            if (fail())
               break;
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
            if (fail())
               break;
            operator()(pair.m_element2);
            if (fail())
               break;
         }
      }
      else
      {
         ::count c = 0;
         operator()(c);
         while (c > 0)
         {
            c--;
            typename MAP::BASE_KEY element1;
            typename MAP::BASE_VALUE element2;
            operator()(element1);
            if (fail())
               break;
            operator()(element2);
            if (fail())
               break;
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
            if (fail())
               break;
            operator()(element);
            if (fail())
               break;
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
            if (fail())
               break;
            element = create_object_from_type_id(strType);
            operator()(element);
            if (fail())
               break;
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

   virtual void operator()(::simple_object & object);

   virtual void operator()(::simple_object * pserializable);

   virtual string get_object_type_id(::object * pelement);
   virtual ::object * create_object_from_type_id(string strType);

   virtual void io(void * p, memory_size_t s);


};










CLASS_DECL_AURA void xml_export(string & strXml, ::xml::exportable & xmlexportable);
CLASS_DECL_AURA void xml_import(::xml::importable & xmlimportable, string & strXml);





inline stream & operator << (stream & os, stream & (*pfnSimpleOutput)(stream &))
{
   return (*pfnSimpleOutput)(os);
}

namespace std
{


   inline stream & endl(stream & os)
   {

      os.put('\n');

      os.flush();

      return os;

   }


} // namespace std

