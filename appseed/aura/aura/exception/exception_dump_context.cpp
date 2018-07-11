#include "framework.h"
//#include <stdarg.h>

#ifdef LINUX

inline int32_t _stprintf_s(char * pszBuffer, int32_t iBufferLen, const char * pszFormat, ...)
{

   UNREFERENCED_PARAMETER(iBufferLen);

   va_list args;

   va_start (args, pszFormat);

   vsprintf(pszBuffer, pszFormat, args);

   va_end (args);

}

inline size_t lstrlen(const char * psz)
{
   return strlen(psz);
}

#endif


dump_context::dump_context(const dump_context &)
{

}

void dump_context::operator = (const dump_context &)
{

}

int32_t dump_context::GetDepth() const
{
   return m_nDepth;
}

void dump_context::SetDepth(int32_t nNewDepth)
{
   m_nDepth = nNewDepth;
}

void dump_context::output_string(const char * lpsz)
{
   // use C-runtime/output_debug_string when m_pfile is NULL
   if (m_pfile == NULL)
   {

      ::output_debug_string(lpsz);

      return;

   }

   ASSERT( lpsz != NULL );
   if( lpsz == NULL )
      _throw(user_exception(get_app()));
   // otherwise, write the string to the file
#ifdef WINDOWSEX
   m_pfile->write(lpsz, lstrlen(lpsz)*sizeof(char));
#else
   m_pfile->write(lpsz, strlen(lpsz)*sizeof(char));
#endif
}

dump_context::dump_context(::file::file_sp  pFile)
{
   if (pFile)
      ASSERT_VALID(pFile);

   m_pfile = pFile;
   m_nDepth = 0;
}

void dump_context::flush()
{
   if (m_pfile)
      m_pfile->flush();
}

void dump_context::write(const char * lpsz)
{
   if (lpsz == NULL)
   {
      output_string("NULL");
      return *this;
   }

   ASSERT( lpsz != NULL );
   if( lpsz == NULL )
      _throw(user_exception(get_app()));

   if (m_pfile == NULL)
   {
      char szBuffer[512];
      LPSTR lpBuf = szBuffer;
      while (*lpsz != '\0')
      {
         if (lpBuf > szBuffer + _countof(szBuffer) - 3)
         {
            *lpBuf = '\0';
            output_string(szBuffer);
            lpBuf = szBuffer;
         }
         if (*lpsz == '\n')
            *lpBuf++ = '\r';
         *lpBuf++ = *lpsz++;
      }
      *lpBuf = '\0';
      output_string(szBuffer);
      return *this;
   }

   m_pfile->write(lpsz, strlen(lpsz)*sizeof(char));
   
}


void dump_context::write(char i)
{

   string str;

   str.Format("%d", (int32_t) i);

   output_string(str);

}


void dump_context::write(uint8_t ui)
{

   string str;

   str.Format("%u", (int32_t) ui);

   output_string(str);

   return *this;

}

void dump_context::write(int16_t i)
{

   string str;

   str.Format("%d", (int32_t) i);

   output_string(str);

   return *this;

}


void dump_context::write(uint16_t ui)
{

   string str;

   str.Format("%u", (uint16_t) ui);

   output_string(str);

}


void dump_context::write(int32_t i)
{

   string str;

   str.Format("%d", i);

   output_string(str);

}


void dump_context::write(uint32_t ui)
{

   string str;

   str.Format("%u", ui);

   output_string(str);

}


void dump_context::write(int64_t i)
{

   string str;

   str.Format("%l64d", i);

   output_string(str);

}


void dump_context::write(uint64_t ui)
{

   string str;

   str.Format("%l64u", ui);

   output_string(str);

}


dump_context & dump_context::hex_dump(int8_t i)
{

   string str;

   str.Format("0x%02x", (uint32_t) i);

   output_string(str);

}


dump_context & dump_context::hex_dump(uint8_t ui)
{

   string str;

   str.Format("0x%02x", (uint32_t)ui);

   output_string(str);

   return *this;

}


dump_context & dump_context::hex_dump(int16_t i)
{

   string str;

   str.Format("0x%04x", (uint32_t) i);

   output_string(str);

   return *this;

}

dump_context & dump_context::hex_dump(uint16_t ui)
{

   string str;

   str.Format("0x%04x", (uint32_t) ui);

   output_string(str);

   return *this;

}


dump_context & dump_context::hex_dump(int32_t i)
{

   string str;

   str.Format("0x%08x", i);

   output_string(str);

   return *this;
}


dump_context & dump_context::hex_dump(uint32_t ui)
{

   string str;

   str.Format("0x%08x", ui);

   output_string(str);

   return *this;

}


dump_context & dump_context::hex_dump(int64_t i)
{

   string str;

   str.Format("0x%016l64x", i);

   output_string(str);

   return *this;
}


dump_context & dump_context::hex_dump(uint64_t ui)
{

   string str;

   str.Format("0x%016l64x", ui);

   output_string(str);

   return *this;

}


void dump_context::write(object * pobject)
{

   if (pobject == NULL)
   {
      
      *this << "NULL";
      
   }
   else
   {
      
      pobject->dump(*this);

   }
   
   return *this;

}


void dump_context::write(object & object)
{

   write(&object);

}


void dump_context::write(const void * lp)
{

   string str;

   // prefix a pointer with "$" and print in hex
   str.Format("$%p", lp);

   output_string(str);

   return *this;

}


void dump_context::write(oswindow h)
{
   
   write((void *)h);
   
}


void dump_context::write(HDC h)
{
   
   write((void *)h);
   
}


#ifdef WINDOWS


void dump_context::write(HMENU h)
{
   
   write((void *)h);
   
}


void dump_context::write(HACCEL h)
{
   
   write((void *)h);
   
}


void dump_context::write(HFONT h)
{
   
   write((void *)h);
   
}


#endif


/////////////////////////////////////////////////////////////////////////////
// Formatted output

void dump_context::hex_dump(const char * lpszLine, BYTE* pby, int32_t nBytes, int32_t nWidth)
// do a simple hex-dump (8 per line) to a dump_context
//  the "lpszLine" is a string to print at the start of each line
//    (%lx should be used to expand the current address)
{
   ASSERT(nBytes > 0);
   if( nBytes <= 0 )
      _throw(invalid_argument_exception(get_app()));
   ASSERT(nWidth > 0);
   if( nWidth <= 0 )
      _throw(invalid_argument_exception(get_app()));
   ASSERT(__is_valid_string(lpszLine));
   if( lpszLine == NULL )
      _throw(invalid_argument_exception(get_app()));
   ASSERT(__is_valid_address(pby, nBytes, FALSE));
   if( pby == NULL )
      _throw(invalid_argument_exception(get_app()));

   int32_t nRow = 0;
   string str;


   while (nBytes--)
   {

      if (nRow == 0)
      {
         str.Format(lpszLine, pby);
         *this << str;
      }

      str.Format(" %02X", *pby);
      *this << str;

      pby++;

      if (++nRow >= nWidth)
      {
         *this << "\n";
         nRow = 0;
      }
   }
   if (nRow != 0)
      *this << "\n";
}


#ifdef WINDOWS


void dump_context::write(const unichar * lpsz)
{

   if (lpsz == NULL)
   {
      output_string("(NULL)");
      return *this;
   }

   *this << ::str::international::unicode_to_utf8(lpsz);

}


#endif


void dump_context::write(string & str)
{
   
   write((const char *) str.c_str());
   
}


//dump_context & dump_context::operator << (double d )
//{
//   operator <<(::str::from(d));
//   return *this;
//}


