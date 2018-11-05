#include "framework.h"


VOID
WINAPI
output_debug_string_a(
_In_opt_ LPCSTR lpOutputString
)
{

   ::output_debug_string(wstring(lpOutputString));

}

VOID
WINAPI
output_debug_string_w(
_In_opt_ LPCWSTR lpOutputString
)
{

   ::output_debug_string(lpOutputString);

}

typedef WINBASEAPI
VOID
WINAPI
FN_OutputDebugStringA(
_In_opt_ LPCSTR lpOutputString
);

typedef WINBASEAPI
VOID
WINAPI
FN_OutputDebugStringW(
_In_opt_ LPCWSTR lpOutputString
);

typedef FN_OutputDebugStringA * PFN_OutputDebugStringA;

typedef FN_OutputDebugStringW * PFN_OutputDebugStringW;

PFN_OutputDebugStringA g_pfnOutputDebugStringA = ::OutputDebugStringA;

PFN_OutputDebugStringW g_pfnOutputDebugStringW = ::OutputDebugStringW;

void set_simple_output_debug_string_a()
{
   g_pfnOutputDebugStringA = ::OutputDebugStringA;
}

void set_extended_output_debug_string_a()
{
   g_pfnOutputDebugStringA = ::output_debug_string_a;
}

void set_simple_output_debug_string_w()
{
   g_pfnOutputDebugStringW = ::OutputDebugStringW;
}

void set_extended_output_debug_string_w()
{
   g_pfnOutputDebugStringW = ::OutputDebugStringW;
}


void output_debug_string(const char * psz)
{

   g_pfnOutputDebugStringA(psz);

}


void w_output_debug_string(const unichar * pwsz)
{

   g_pfnOutputDebugStringW(pwsz);

}


void output_debug_string(const unichar * pwsz)
{

   g_pfnOutputDebugStringW(pwsz);

}



namespace process
{


   bool set_priority(int32_t priority)
   {

      return (::SetPriorityClass(::GetCurrentProcess(), get_os_priority_class(priority)) != 0);


   }


} // namespace process



::file::path __node_full_file_path(file::path path)
{

   WCHAR wszPath[8192];

   DWORD dw = GetFullPathNameW(L"\\\\?\\"+wstring(path), sizeof(wszPath) / sizeof(WCHAR), wszPath, NULL);

   return wszPath;

}



CLASS_DECL_AURA DWORD get_current_process_id()
{

   return ::GetCurrentProcessId();

}
