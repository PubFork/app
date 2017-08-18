#include "framework.h"

#include <stdio.h>

#ifdef METROWIN

//_flag values (not the ones used by the normal CRT

_FILE __iob[3];

void _init_file()
{
	// STDIN
	//__iob[0]._base = (char *) create_file("C:\\Temp\\pid\\stdin");
   __iob[0]._base = (char *) INVALID_HANDLE_VALUE;
	__iob[0]._flag = _FILE_TEXT;

	// STDOUT
	__iob[1]._base = (char *) INVALID_HANDLE_VALUE;
	__iob[1]._flag = _FILE_TEXT;

	// STDERR
	__iob[2]._base = (char *) INVALID_HANDLE_VALUE;
	__iob[2]._flag = _FILE_TEXT;
}

_FILE *__iob_func_dup() {return (_FILE*)__iob;}

#elif defined(WINDOWS)


//_flag values (not the ones used by the normal CRT

_FILE __iob[3];

void _init_file()
{






FILE *fopen_dup(const char *path, const char *attrs)
{

#if defined(WINDOWS)

   return _wfopen(wstring(path), wstring(attrs));

#elif

   return fopen(path, attrs);

#endif

}



int32_t fclose_dup(FILE *fp)
{


    return fclose(fp);
}

int32_t feof_dup(FILE *fp)
{


    return feof(fp);


}

int32_t fflush_dup(FILE * fp)
{

    return fflush(fp);

}

file_position_t fseek_dup(FILE *fp, file_offset_t offset, int32_t origin)
{


    return fseek(fp, offset, origin);

}

long ftell_dup(FILE *fp)
{


    return ftell(fp);
}

size_t fread_dup(void *buffer, size_t size, size_t count, FILE *str)
{


    return fread(buffer, size, count, str);

}

size_t fwrite_dup(const void *buffer, size_t size, size_t count, FILE *str)
{


    return fwrite(buffer, size, count, str);


}

char *fgets_dup(char *str, int32_t n, FILE *s)
{

    return fgets(str, n, s);


}



int32_t fgetc_dup(FILE *s)
{
	if (s == 0 || feof_dup(s))
		return EOF;

	uchar c;
	fread_dup(&c, 1, sizeof(uchar), s);

	return (int32_t)c;
}

int32_t ungetc_dup(int32_t c, FILE *s)
{
	if (s == 0)
		return EOF;

	fseek_dup(s, -1, SEEK_CUR);

	return (int32_t)c;
}


int32_t ferror_dup(FILE *fp)
{


    return ferror(fp);


}

uint64_t fsize_dup(FILE * fp)
{
   size_t pos = ftell(fp);
   fseek(fp, 0, SEEK_END);
   size_t len = ftell(fp);
   fseek(fp, pos, SEEK_SET);
   return len;
}

uint64_t flen_dup(FILE *str)
{


   return fsize_dup(str);


}



