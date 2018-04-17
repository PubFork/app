#pragma once


CLASS_DECL_AURA string i64toa_dup(int64_t i, int32_t iBase);
CLASS_DECL_AURA string i64toa_dup(int64_t i);

CLASS_DECL_AURA string ui64toa_dup(int64_t i, int32_t iBase);
CLASS_DECL_AURA string ui64toa_dup(int64_t i);


inline string itoa_dup(int64_t i);
inline char * itocat_dup(char * psz, int64_t i);



CLASS_DECL_AURA void ltoa_dup(char * sz, int64_t i, int32_t iBase);
CLASS_DECL_AURA void ultoa_dup(char * sz, uint64_t i, int32_t iBase);


CLASS_DECL_AURA void ltow_dup(unichar * sz, int64_t i, int32_t iBase);
CLASS_DECL_AURA void ultow_dup(unichar * sz, uint64_t i, int32_t iBase);


inline string itoa_dup(i64 i)
{
   char sz[32];
   _i64toa(i, sz, 10);
   return string(sz);
}

inline char * itocat_dup(char * psz, i64 i)
{
   _i64toa(i, psz + strlen(psz), 10);
   return psz;
}


inline string itoa_dup(i32 i)
{
   char sz[16];
   _itoa(i, sz, 10);
   return string(sz);
}

inline char * itocat_dup(char * psz, i32 i)
{
   _itoa(i, psz + strlen(psz), 10);
   return psz;
}
