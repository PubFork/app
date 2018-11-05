#include "framework.h"


::file::path file::app_module()
{

   hwstring hwPath(MAX_PATH * 16);

   if (!GetModuleFileNameW(NULL, hwPath, (DWORD) hwPath.count()))
   {

      return "";

   }

   string strPath;

   strPath = hwPath;

   return strPath;

}


extern "C"
int_bool file_copy_dup(const char * pszNew, const char * pszSrc, int_bool bOverwrite)
{

   string strNew(pszNew);

   if (strNew.get_length() >= MAX_PATH)
   {

      strNew = "\\\\.\\" + strNew;

   }

   string strSrc(pszSrc);

   if (strSrc.get_length() >= MAX_PATH)
   {

      strSrc = "\\\\.\\" + strSrc;

   }

   wstring wstrNew(strNew);

   wstring wstrSrc(strSrc);

   //return ::CopyFileExW(wstrSrc,wstrNew, NULL, NULL, NULL, COPY_FILE_NO_BUFFERING | (bOverwrite ? 0 : COPY_FILE_FAIL_IF_EXISTS)) ? true : false;
   return ::CopyFileExW(wstrSrc, wstrNew, NULL, NULL, NULL, (bOverwrite ? 0 : COPY_FILE_FAIL_IF_EXISTS)) ? true : false;

}









::file::path get_final_path(const ::file::path & path)
{

   wstring wstr(path);

   HANDLE hfile = INVALID_HANDLE_VALUE;

   try
   {

      if (::dir::is(path))
      {

         hfile = create_file(path,
                             GENERIC_READ,          // open for reading
                             FILE_SHARE_READ,       // share for reading
                             NULL,                  // default security
                             OPEN_EXISTING,         // existing file only
                             FILE_ATTRIBUTE_NORMAL, // normal file
                             NULL);                 // no attr. template

      }
      else
      {

         hfile = create_file(path,
                             FILE_LIST_DIRECTORY,          // open for reading
                             FILE_SHARE_READ,       // share for reading
                             NULL,                  // default security
                             OPEN_EXISTING,         // existing file only
                             FILE_ATTRIBUTE_NORMAL, // normal file
                             NULL);                 // no attr. template

      }

      if (hfile == INVALID_HANDLE_VALUE)
      {

         return wstr;

      }

      DWORD dw = GetFinalPathNameByHandleW(hfile, NULL, 0, VOLUME_NAME_DOS);

      if (dw > 0)
      {

         wstring wstr2;

         auto * pwsz = wstr2.alloc(dw + 1);

         dw = GetFinalPathNameByHandleW(hfile, pwsz, dw + 1, VOLUME_NAME_DOS);

         if (dw > 0)
         {

            wstr2.release_buffer();

            wstr = wstr2;

         }

      }

   }
   catch (...)
   {

   }

   ::CloseHandle(hfile);

   return wstr;

}


CLASS_DECL_AURA bool __node_further_file_is_equal(const ::file::path & path1, const ::file::path & path2)
{

   ::file::path pathFull1 = get_final_path(path1);

   ::file::path pathFull2 = get_final_path(path2);

   return pathFull1.has_char() && pathFull1.compare_ci(pathFull2) == 0;

}






