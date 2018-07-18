#pragma once

#include "file_stream.h"

namespace file
{


   class exception;         // file exception
   class binary_file;
   typedef sp(binary_file) binary_buffer_sp;

   class byte_stream;
   class byte_stream;

   class exception;         // file exception
   class file;
   typedef sp(binary_file) binary_buffer_sp;

   class byte_stream;
   class istream;

} // namespace

class CLASS_DECL_AURA serialize :
   virtual public stream
{
public:


   bool              m_b64bit;
   //memory_size_t     m_gcount;


   serialize();
   serialize(serialize && serialize);
   serialize(::file::file * pfile, index iVersion = FIRST_VERSION);
   serialize(::aura::application * papp, index iVersion = FIRST_VERSION);
   virtual ~serialize();


   //stream & operator = (const stream & stream);

   virtual bool is_stream_null();
   virtual bool is_stream_set();

   virtual void close();

   virtual file_position_t get_position() const;

//      void read(int32_t & i);
//      void read(uint32_t & ui);
//      void read(int64_t & i);
//      void read(uint64_t & ui);

   using stream::read;
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
   virtual void read (float & f);
   virtual void read (double & d);
   virtual void read (LPRECT lprect);
   virtual void read (SIZE & size);
   virtual void read (sp(type) info);
   virtual void read (id & id);
   virtual void read (string & str);

   // read until MSB is not set ignoring this MSB when writing to target
   //void read(void * p, ::count nMax);

   virtual string get_location() const;

   /*
    file_position_t seek(file_offset_t offset, e_seek seekOrigin);
    */

   void full_load(string & str);

   // void write(int32_t i);
   // void write(uint32_t ui);
   // void write(int64_t i);
   // void write(uint64_t ui);
   // void write(uint64_t ui, int signal);

   using stream::write;
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
   virtual void write (float f);
   virtual void write (double d);
   virtual void write (RECT & rect);
   virtual void write (LPRECT lpcrect);
   virtual void write (SIZE & size);
   virtual void write (sp(type) & info);
   virtual void write (const char * psz);
   virtual void write (id & id);
   virtual void write (string & str);

//      virtual string get_location() const;

   //ostream & operator = (const ostream & ostream);

   virtual void write_from_hex(const char * psz, strsize iLen = -1);
   virtual void write_from_hex(const string & str);

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


class CLASS_DECL_AURA memory_reader :
   virtual public reader
{
public:


   memory_reader(memory_reader && reader);
   memory_reader(::aura::application * papp, index iVersion = FIRST_VERSION);
   virtual ~memory_reader();


   memory & get_memory();


};


class CLASS_DECL_AURA memory_writer :
   virtual public writer
{
public:


   memory_writer(memory_writer && writer);
   memory_writer(::aura::application * papp, index iVersion = FIRST_VERSION);
   virtual ~memory_writer();


   memory & get_memory();


};

