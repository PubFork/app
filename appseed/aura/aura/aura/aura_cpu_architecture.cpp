/* CpuArch.c -- CPU specific code
2010-10-26: Igor Pavlov : Public domain */
// from 7-zip on 2010-12-26 Sunday, just after Christmas evening at Music Room
#include "framework.h"


#if !defined(RASPBIAN)

#ifdef WINDOWS
#include <intrin.h>

#elif defined(LINUX)
#include <cpuid.h>
#endif


#ifdef MY_CPU_X86_OR_AMD64

#if (defined(_MSC_VER) && !defined(MY_CPU_AMD64)) || defined(__GNUC__)
#define USE_ASM
#endif

#if defined(USE_ASM) && !defined(MY_CPU_AMD64)
static uint32_t CheckFlag(uint32_t flag)
{
  #ifdef _MSC_VER
  __asm pushfd;
  __asm pop EAX;
  __asm mov EDX, EAX;
  __asm xor EAX, flag;
  __asm push EAX;
  __asm popfd;
  __asm pushfd;
  __asm pop EAX;
  __asm xor EAX, EDX;
  __asm push EDX;
  __asm popfd;
  __asm and flag, EAX;
  #else
  __asm__ __volatile__ (
    "pushf\n\t"
    "pop  %%EAX\n\t"
    "movl %%EAX,%%EDX\n\t"
    "xorl %0,%%EAX\n\t"
    "push %%EAX\n\t"
    "popf\n\t"
    "pushf\n\t"
    "pop  %%EAX\n\t"
    "xorl %%EDX,%%EAX\n\t"
    "push %%EDX\n\t"
    "popf\n\t"
    "andl %%EAX, %0\n\t":
    "=c" (flag) : "c" (flag));
  #endif
  return flag;
}
#define CHECK_CPUID_IS_SUPPORTED if (CheckFlag(1 << 18) == 0 || CheckFlag(1 << 21) == 0) return 0;
#else
#define CHECK_CPUID_IS_SUPPORTED
#endif

static void MyCPUID(uint32_t function, uint32_t *a, uint32_t *b, uint32_t *c, uint32_t *d)
{
  #if defined(USE_ASM) && !defined(WINDOWS) && !defined(LINUX)

  /*#ifdef _MSC_VER

  uint32_t a2, b2, c2, d2;
  __asm xor EBX, EBX;
  __asm xor ECX, ECX;
  __asm xor EDX, EDX;
  __asm mov EAX, function;
  __asm cpuid;
  __asm mov a2, EAX;
  __asm mov b2, EBX;
  __asm mov c2, ECX;
  __asm mov d2, EDX;

  *a = a2;
  *b = b2;
  *c = c2;
  *d = d2;

  #else*/

  //PIC - Position Independent Code
 __asm__ __volatile__ (
    "mov %%ebx, %%edi;"
    "cpuid;"
    "xchgl %%ebx, %%edi;"
    : "=a" (*a) ,
      "=D" (*b) , /* edi */
      "=c" (*c) ,
      "=d" (*d)
    : "0" (function)) ;

/*asm volatile
    ("cpuid" : "=a" (*reg0), "=b" (*reg1), "=c" (*reg2), "=d" (*reg3)
     : "a" (function), "c" (0));*/
  // ECX is set to zero for CPUID function 4

/*  __asm__ __volatile__ (
    "cpuid"
    : "=a" (*a) ,
      "=b" (*b) ,
      "=c" (*c) ,
      "=d" (*d)
    : "0" (function)) ;*/

  //#endif

  #elif defined(LINUX)

  __cpuid(function, *a, *b, *c, *d);

  #else

  int32_t CPUInfo[4];
  __cpuid(CPUInfo, function);
  *a = CPUInfo[0];
  *b = CPUInfo[1];
  *c = CPUInfo[2];
  *d = CPUInfo[3];

  #endif
}

int32_t x86cpuid_CheckAndRead(struct Cx86cpuid *p)
{
  CHECK_CPUID_IS_SUPPORTED
  MyCPUID(0, &p->maxFunc, &p->vendor[0], &p->vendor[2], &p->vendor[1]);
  MyCPUID(1, &p->ver, &p->b, &p->c, &p->d);
  return 1;
}

static uint32_t kVendors[][3] =
{
  { 0x756E6547, 0x49656E69, 0x6C65746E},
  { 0x68747541, 0x69746E65, 0x444D4163},
  { 0x746E6543, 0x48727561, 0x736C7561}
};

int32_t x86cpuid_GetFirm(const struct Cx86cpuid *p)
{
  uint32_t i;
  for (i = 0; i < sizeof(kVendors) / sizeof(kVendors[i]); i++)
  {
    const uint32_t *v = kVendors[i];
    if (v[0] == p->vendor[0] &&
        v[1] == p->vendor[1] &&
        v[2] == p->vendor[2])
      return (int32_t)i;
  }
  return -1;
}

int32_t CPU_Is_InOrder()
{
  struct Cx86cpuid p;
  int32_t firm;
  uint32_t family, model;
  if (!x86cpuid_CheckAndRead(&p))
    return 1;
  family = x86cpuid_GetFamily(&p);
  model = x86cpuid_GetModel(&p);
  firm = x86cpuid_GetFirm(&p);
  switch (firm)
  {
    case CPU_FIRM_INTEL: return (family < 6 || (family == 6 && model == 0x100C));
    case CPU_FIRM_AMD: return (family < 5 || (family == 5 && (model < 6 || model == 0xA)));
    case CPU_FIRM_VIA: return (family < 6 || (family == 6 && model < 0xF));
  }
  return 1;
}

#if !defined(MY_CPU_AMD64) && defined(_WIN32) && !defined(METROWIN)
static int32_t CPU_Sys_Is_SSE_Supported()
{
   return is_windows_2000_or_greater();
}
#define CHECK_SYS_SSE_SUPPORT if (!CPU_Sys_Is_SSE_Supported()) return 0;
#else
#define CHECK_SYS_SSE_SUPPORT
#endif

int32_t CPU_Is_Aes_Supported()
{
  struct Cx86cpuid p;
  CHECK_SYS_SSE_SUPPORT
  if (!x86cpuid_CheckAndRead(&p))
    return 0;
  return (p.c >> 25) & 1;
}
#ifdef WINDOWS
#include <intrin.h>
#endif
BEGIN_EXTERN_C
CLASS_DECL_AURA int cpu_has_avx()
{
   int avxSupported = 0;

   // If Visual Studio 2010 SP1 or later
#if (_MSC_FULL_VER >= 160040219)
   // Checking for AVX requires 3 things:
   // 1) CPUID indicates that the OS uses XSAVE and XRSTORE
   //     instructions (allowing saving YMM registers on context
   //     switch)
   // 2) CPUID indicates support for AVX
   // 3) XGETBV indicates the AVX registers will be saved and
   //     restored on context switch
   //
   // Note that XGETBV is only available on 686 or later CPUs, so
   // the instruction needs to be conditionally run.
   int cpuInfo[4];
   __cpuid(cpuInfo,1);

   bool osUsesXSAVE_XRSTORE = cpuInfo[2] & (1 << 27) || false;
   bool cpuAVXSuport = cpuInfo[2] & (1 << 28) || false;

   if(osUsesXSAVE_XRSTORE && cpuAVXSuport)
   {
      // Check if the OS will save the YMM registers
      unsigned long long xcrFeatureMask = _xgetbv(_XCR_XFEATURE_ENABLED_MASK);
      avxSupported = (xcrFeatureMask & 0x6);
   }
#endif

   return avxSupported;

}
END_EXTERN_C

#endif


#endif


