#include "framework.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>


int_bool file_exists_raw(const char * path1)
{

#ifdef WINDOWS

   uint32_t dwFileAttributes = GetFileAttributesA(path1);

   if (dwFileAttributes == INVALID_FILE_ATTRIBUTES || (dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
      return FALSE;

   return TRUE;

#else


   // dedicaverse stat -> Sir And Arthur - Cesar Serenato

   struct stat st;

   if(stat(path1, &st))
      return false;

   if((st.st_mode & S_IFDIR))
      return false;

   return true;

#endif

}

void file_put_contents_raw(const char * path, const char * psz)
{

   FILE * f = fopen(path, "wb");

   if (f == NULL)
      return;

   ::count iSize = strlen(psz);

   ::count iRead = fwrite(psz, 1, iSize, f);

   fclose(f);

}

void file_add_contents_raw(const char * path, const char * psz)
{

   FILE * f = fopen(path, "ab");

   if (f == NULL)
      return;

   ::count iSize = strlen(psz);

   ::count iRead = fwrite(psz, 1, iSize, f);

   fclose(f);

}


void file_beg_contents_raw(const char * path, const char * psz)
{

   FILE * f = fopen(path, "rb+");

   long lLen;

   lLen = (long) ( strlen(psz));

   fseek(f, lLen, SEEK_END);

   long lEnd = ftell(f);

   long lSize = 1024 * 1024;

   char * buf = (char *) malloc(lSize);

   long lRemain = lEnd - lLen;

   while (lRemain > 0)
   {

      fseek(f, lEnd - lRemain - lLen, SEEK_SET);

      fread(buf, 1, MIN(lRemain, lSize), f);

      fseek(f, lEnd - lRemain, SEEK_SET);

      fwrite(buf, 1, MIN(lRemain, lSize), f);

      lRemain -= MIN(lRemain, lSize);

   }

   free(buf);

   fseek(f, 0, SEEK_SET);

   auto lRead = fwrite(psz, 1, lLen, f);

   if (lRead != lLen)
   {

      output_debug_string("file_beg_contents_raw: error writing to file.");

   }

   fclose(f);

}


uint64_t file_length_raw(const char * path)
{

#ifdef WINDOWS
   struct _stat st;
   ::_stat(path, &st);
   return st.st_size;

#else
   struct stat st;
   ::stat(path, &st);
   return st.st_size;

#endif

}
