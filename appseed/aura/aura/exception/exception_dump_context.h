#pragma once

#include "aura/filesystem/file/file_serialize.h"
class CLASS_DECL_AURA dump_context :
   virtual public stream
{
public:

   dump_context(::file::file_sp  pFile = NULL);

// Attributes
   int32_t GetDepth() const;      // 0 => this object, 1 => children objects
   void SetDepth(int32_t nNewDepth);

// Operations
   virtual void write(const char * lpsz) override;
#ifdef WINDOWS
   virtual void write(const unichar * lpsz) override; // automatically thinned
#endif
   virtual void write(string & str) override;
   virtual void write(const void * lp);
   virtual void write(object * pobject) override;
   virtual void write(object & object) override;
   virtual void write(char i) override;
   virtual void write(uchar ui) override;
   virtual void write(i16 i) override;
   virtual void write(u16 ui) override;
   virtual void write(i32 i) override;
   virtual void write(u32 ui) override;
   virtual void write(i64 i) override;
   virtual void write(u64 ui) override;
   dump_context & hex_dump(const i8 i);
   dump_context & hex_dump(const u8 i);
   dump_context & hex_dump(const i16 i);
   dump_context & hex_dump(const u16 i);
   dump_context & hex_dump(const i32 i);
   dump_context & hex_dump(const u32 i);
   dump_context & hex_dump(const i64 i);
   dump_context & hex_dump(const u64 i);
   virtual void  write(const float f) override;
   virtual void  write(const double d) override;
   virtual void  write(const oswindow h);
   virtual void  write(const HDC h);

#ifdef WINDOWS
   virtual void  write(const HMENU h);
   virtual void  write(const HACCEL h);
   virtual void  write(const HFONT h);
#endif

   void hex_dump(const char * lpszLine, BYTE* pby, int32_t nBytes, int32_t nWidth);
   virtual void flush() override;

// Implementation
protected:
   // dump context objects cannot be copied or assigned
   dump_context(const dump_context & graphicsSrc);
   void operator=(const dump_context & graphicsSrc);
   void output_string(const char * lpsz);

   int32_t m_nDepth;

public:
   ::file::file_sp  m_pfile;
};



