#include "framework.h"


VOID
WINAPI
output_debug_string_a(
   _In_opt_ LPCSTR lpOutputString
   )
{

   ::output_debug_string(wstring(lpOutputString));

}


typedef WINBASEAPI
VOID
WINAPI
FN_OutputDebugStringA(
   _In_opt_ LPCSTR lpOutputString
   );

typedef FN_OutputDebugStringA * PFN_OutputDebugStringA;

PFN_OutputDebugStringA g_pfnOutputDebugString = ::output_debug_string;

void set_simple_output_debug_string()
{
   g_pfnOutputDebugString = ::output_debug_string;
}

void set_extended_output_debug_string()
{
   g_pfnOutputDebugString = ::output_debug_string_a;
}

void output_debug_string(const char * psz)
{
   g_pfnOutputDebugString(psz);
}


void w_output_debug_string(const unichar * pwsz)
{
   output_debug_string(string(pwsz));
}

