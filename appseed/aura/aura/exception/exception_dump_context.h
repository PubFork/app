#pragma once

#include "aura/filesystem/file/file_serialize.h"
class CLASS_DECL_AURA dump_context :
   virtual public serialize
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
      virtual void write(string & str) override;;
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
      dump_context & hex_dump(int8_t i);
      dump_context & hex_dump(uint8_t i);
      dump_context & hex_dump(int16_t i);
      dump_context & hex_dump(uint16_t i);
      dump_context & hex_dump(int32_t i);
      dump_context & hex_dump(uint32_t i);
      dump_context & hex_dump(int64_t i);
      dump_context & hex_dump(uint64_t i);
      virtual void  write(float f) override;
      virtual void  write(double d) override;
      virtual void  write(oswindow h);
      virtual void  write(HDC h);

#ifdef WINDOWS
      virtual void  write(HMENU h) override;
      virtual void  write(HACCEL h) override;
      virtual void  write(HFONT h) override;
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



