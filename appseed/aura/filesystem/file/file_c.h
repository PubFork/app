#pragma once


#ifndef WINDOWS

#define _SH_DENYNO 0
#define _SH_DENYWR 0
#define _SH_DENYRW 0

#endif

BEGIN_EXTERN_C

CLASS_DECL_AURA int_bool dir_mk(const char * psz);
CLASS_DECL_AURA int_bool dir_appdata(char * psz, size_t size);
CLASS_DECL_AURA int_bool is_absolute_path(const char * psz);
CLASS_DECL_AURA int_bool file_is_true_dup(const char * path);



#define file_size_t uint64_t
#define file_position_t uint64_t
#define file_offset_t int64_t

CLASS_DECL_AURA int_bool file_path_is_relative_dup(const char * psz);



CLASS_DECL_AURA int_bool file_exists_dup(const char * path);


#ifdef WINDOWS
CLASS_DECL_AURA int_bool read_resource_as_file_dup(const char * pszFile, HINSTANCE hinst, UINT nID, LPCTSTR lpcszType);
#endif
//CLASS_DECL_AURA int_bool is_file_ok(const char * path1, const char * pszTemplate);
CLASS_DECL_AURA int_bool file_put_contents_dup(const char * path, const char * contents, count len);
//CLASS_DECL_AURA int_bool get_temp_file_name_dup(char * szRet, count iBufferSize, const char * pszName, const char * pszExtension);
CLASS_DECL_AURA int_bool get_temp_file_name_template(char * szRet, count iBufferSize, const char * pszName, const char * pszExtension, const char * pszTemplate);
CLASS_DECL_AURA uint64_t file_length_dup(const char * path);



CLASS_DECL_AURA int_bool file_is_equal_path_dup(const char * pszPath1, const char * pszPath2);


CLASS_DECL_AURA int_bool file_copy_dup(const char * pszDup, const char * pszSrc, int_bool bOverwrite);


CLASS_DECL_AURA void _init_file_dup();

CLASS_DECL_AURA FILE * fopen_dup(const char *path, const char *attrs, int iShare);
CLASS_DECL_AURA int32_t fprintf_dup(FILE *fp, const char *s, ...);
CLASS_DECL_AURA int32_t fclose_dup(FILE *fp);
CLASS_DECL_AURA int32_t feof_dup(FILE *fp);
CLASS_DECL_AURA file_position_t fseek_dup(FILE *str, file_offset_t offset, int32_t origin);
CLASS_DECL_AURA long ftell_dup(FILE *fp);
CLASS_DECL_AURA size_t fread_dup(void *buffer, size_t size, size_t count, FILE *str);
CLASS_DECL_AURA size_t fwrite_dup(const void *buffer, size_t size, size_t count, FILE *str);
CLASS_DECL_AURA char *fgets_dup(char *str, int32_t n, FILE *s);
CLASS_DECL_AURA int32_t fgetc_dup(FILE *s);
CLASS_DECL_AURA int32_t ungetc_dup(int32_t c,FILE *s);
CLASS_DECL_AURA int32_t ferror_dup(FILE *s);
CLASS_DECL_AURA int32_t fflush_dup(FILE *s);
CLASS_DECL_AURA uint64_t flen_dup(FILE *s);


#ifdef WINDOWS
CLASS_DECL_AURA FILE *_wfopen_dup(const unichar *path, const unichar *attrs, int iShare);
CLASS_DECL_AURA int32_t fwprintf_dup(FILE *fp, const unichar *s, ...);
CLASS_DECL_AURA unichar *fgetws_dup(unichar *str, int32_t n, FILE *s);
CLASS_DECL_AURA wint_t fgetwc_dup(FILE *s);
CLASS_DECL_AURA wint_t ungetwc_dup(wint_t w, FILE *s);
#endif


CLASS_DECL_AURA uint64_t fsize_dup(FILE * f);

CLASS_DECL_AURA int_bool ensure_file_size_handle(HANDLE h,uint64_t iSize);
CLASS_DECL_AURA int_bool ensure_file_size_fd(int32_t fd,size_t iSize);
CLASS_DECL_AURA int_bool ensure_file_size(FILE * file,size_t iSize);

END_EXTERN_C



//   #pragma once



//typedef uint64_t  file_size_t;
//typedef uint64_t  file_position_t;
//typedef int64_t   file_offset_t;





CLASS_DECL_AURA int_bool file_exists_dup(const char * path1);

#ifdef WINDOWS
CLASS_DECL_AURA int_bool read_resource_as_file_dup(const char * pszFile, HINSTANCE hinst, UINT nID, LPCTSTR lpcszType);
#endif

//CLASS_DECL_AURA int_bool is_file_ok(const char * path1, const char * pszTemplate);
CLASS_DECL_AURA int_bool file_put_contents_dup(const char * path, const char * contents, count len);
//CLASS_DECL_AURA int_bool get_temp_file_name_dup(char * szRet, count iBufferSize, const char * pszName, const char * pszExtension);
CLASS_DECL_AURA int_bool get_temp_file_name_template(char * szRet, count iBufferSize, const char * pszName, const char * pszExtension, const char * pszTemplate);
CLASS_DECL_AURA uint64_t file_length_dup(const char * path);



CLASS_DECL_AURA int_bool file_is_equal_path(const char * pszPath1, const char * pszPath2);


BEGIN_EXTERN_C




CLASS_DECL_AURA FILE * fopen_dup(const char *path, const char *attrs, int iShare);
CLASS_DECL_AURA int32_t fprintf_dup(FILE *fp, const char *s, ...);
CLASS_DECL_AURA int32_t fclose_dup(FILE *fp);
CLASS_DECL_AURA int32_t feof_dup(FILE *fp);
CLASS_DECL_AURA file_position_t fseek_dup(FILE *str, file_offset_t offset, int32_t origin);
CLASS_DECL_AURA long ftell_dup(FILE *fp);
CLASS_DECL_AURA size_t fread_dup(void *buffer, size_t size, size_t count, FILE *str);
CLASS_DECL_AURA size_t fwrite_dup(const void *buffer, size_t size, size_t count, FILE *str);
CLASS_DECL_AURA char *fgets_dup(char *str, int32_t n, FILE *s);
CLASS_DECL_AURA int32_t fgetc_dup(FILE *s);
CLASS_DECL_AURA int32_t ungetc_dup(int32_t c,FILE *s);
CLASS_DECL_AURA int32_t ferror_dup(FILE *s);
CLASS_DECL_AURA int32_t fflush_dup(FILE *s);


//#ifdef WINDOWS
//CLASS_DECL_AURA FILE *_wfopen_dup(const unichar *path, const unichar *attrs, int iShare);
//CLASS_DECL_AURA int32_t fwprintf_dup(FILE *fp, const unichar *s, ...);
//CLASS_DECL_AURA unichar *fgetws_dup(unichar *str, int32_t n, FILE *s);
//CLASS_DECL_AURA wint_t fgetwc_dup(FILE *s);
//CLASS_DECL_AURA wint_t ungetwc_dup(wint_t w, FILE *s);
//#endif


CLASS_DECL_AURA uint64_t fsize_dup(FILE * fp);


END_EXTERN_C



#ifdef __cplusplus


namespace primitive
{


   class memory_base;


} // namespace primitive


CLASS_DECL_AURA bool file_put_contents_dup(const char * path, const ::primitive::memory_base & memory);
CLASS_DECL_AURA int_bool file_put_contents_dup(const char * path, const char * contents);
CLASS_DECL_AURA bool file_get_memory_dup(::primitive::memory_base & memory, const char * path);


CLASS_DECL_AURA uint64_t fsize_dup(HANDLE h);



template < typename N > class numeric_array;

typedef CLASS_DECL_AURA numeric_array < uint32_t > uint_array;

template < typename Type,typename RawType = Type >

class string_array;
typedef string_array < string > stringa;


CLASS_DECL_AURA string file_title_dup(const char * path);
CLASS_DECL_AURA string file_name_dup(const char * path);


CLASS_DECL_AURA string file_get_mozilla_firefox_plugin_container_path();

#endif


CLASS_DECL_AURA int_bool file_set_length(const char * pszName, size_t iSize);


CLASS_DECL_AURA int_bool file_move_dup(const char * lpszNewName,const char * lpszOldName);
CLASS_DECL_AURA int_bool file_delete_dup(const char * lpszFileName);



#ifdef __cplusplus

CLASS_DECL_AURA bool file_save_stra(const char * pszName, const stringa & stra);
CLASS_DECL_AURA bool file_load_stra(const char * pszName, stringa & stra, bool bAddEmpty = true);


#endif


