#include "framework.h"


namespace datetime
{


   file_time::file_time() NOTHROW
   {
      dwLowDateTime = 0;
      dwHighDateTime = 0;
   }

   file_time::file_time(const FILETIME& ft) NOTHROW
   {
      dwLowDateTime = ft.dwLowDateTime;
      dwHighDateTime = ft.dwHighDateTime;
   }

   file_time::file_time(ULONGLONG nTime) NOTHROW
   {
      dwLowDateTime = uint32_t(nTime);
      dwHighDateTime = uint32_t(nTime >> 32);
   }

   file_time& file_time::operator=(const FILETIME& ft) NOTHROW
   {
      dwLowDateTime = ft.dwLowDateTime;
      dwHighDateTime = ft.dwHighDateTime;

      return *this;
   }

   file_time WINAPI file_time::get_current_time() NOTHROW
   {
      file_time ft;
      GetSystemTimeAsFileTime(&ft);
      return ft;
   }

   file_time& file_time::operator+=(file_time_span span) NOTHROW
   {
      SetTime(get_time() + span.GetTimeSpan());

      return *this;
   }

   file_time& file_time::operator-=(file_time_span span) NOTHROW
   {
      SetTime(get_time() - span.GetTimeSpan());

      return *this;
   }

   file_time file_time::operator+(file_time_span span) const NOTHROW
   {
      return(file_time(get_time() + span.GetTimeSpan()));
   }

   file_time file_time::operator-(file_time_span span) const NOTHROW
   {
      return(file_time(get_time() - span.GetTimeSpan()));
   }

   file_time_span file_time::operator-(file_time ft) const NOTHROW
   {
      return(file_time_span(get_time() - ft.get_time()));
   }

   bool file_time::operator==(file_time ft) const NOTHROW
   {
      return(get_time() == ft.get_time());
   }

   bool file_time::operator!=(file_time ft) const NOTHROW
   {
      return(get_time() != ft.get_time());
   }

   bool file_time::operator<(file_time ft) const NOTHROW
   {
      return(get_time() < ft.get_time());
   }

   bool file_time::operator>(file_time ft) const NOTHROW
   {
      return(get_time() > ft.get_time());
   }

   bool file_time::operator<=(file_time ft) const NOTHROW
   {
      return(get_time() <= ft.get_time());
   }

   bool file_time::operator>=(file_time ft) const NOTHROW
   {
      return(get_time() >= ft.get_time());
   }

   ULONGLONG file_time::get_time() const NOTHROW
   {
      return((ULONGLONG(dwHighDateTime) << 32) | dwLowDateTime);
   }

   void file_time::SetTime(ULONGLONG nTime) NOTHROW
   {
      dwLowDateTime = uint32_t(nTime);
      dwHighDateTime = uint32_t(nTime >> 32);
   }

   file_time file_time::UTCToLocal() const NOTHROW
   {
      file_time ftLocal;

      ::FileTimeToLocalFileTime(this,&ftLocal);

      return(ftLocal);
   }

   file_time file_time::LocalToUTC() const NOTHROW
   {
      
      file_time ftUTC;

      ::LocalFileTimeToFileTime(this,&ftUTC);

      return(ftUTC);

   }


   const ULONGLONG file_time::Millisecond = 10000;
   const ULONGLONG file_time::Second = Millisecond * static_cast<ULONGLONG>(1000);
   const ULONGLONG file_time::Minute = Second * static_cast<ULONGLONG>(60);
   const ULONGLONG file_time::Hour = Minute * static_cast<ULONGLONG>(60);
   const ULONGLONG file_time::Day = Hour * static_cast<ULONGLONG>(24);
   const ULONGLONG file_time::Week = Day * static_cast<ULONGLONG>(7);


}













CLASS_DECL_AURA bool file_modified_timeout(const char * path, int iSeconds)
{

   ::file_time filetime = ::get_file_time(path);

   if (filetime.modified_timeout(iSeconds))
   {

      return true;

   }

   return false;

}

FILETIME get_file_time_now()
{

   FILETIME t = {};

   GetSystemTimeAsFileTime(&t);
   
   return t;

}



void get_file_time(const char * psz,file_time & time)
{

   get_file_time(psz,time.creation,time.modified);

}


#ifdef WINDOWSEX


void get_file_time(const char * psz,FILETIME & creation,FILETIME & modified)
{

   HANDLE h = CreateFileW(wstring(psz),GENERIC_READ,FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);

   try
   {
      ZERO(creation);
      ZERO(modified);
      ::GetFileTime(h,&creation,NULL,&modified);
   }
   catch(...)
   {
   }

   ::CloseHandle(h);

}

#elif defined(METROWIN)
void get_file_time(const char * psz,FILETIME & creation,FILETIME & modified)
{

         //::Windows::Storage::StorageFile ^ h = get_os_file(psz,GENERIC_READ,FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
   HANDLE h = create_file(psz, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
   try
   {
      ZERO(creation);
      ZERO(modified);
      ::GetFileTime(h, &creation, NULL, &modified);
   }
   catch (...)
   {
   }

   ::CloseHandle(h);


}

#else

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>



void get_file_time(const char * psz,FILETIME & creation,FILETIME & modified)
{

   struct stat st;

   stat(psz, &st);
   
   creation.dwLowDateTime = LODWORD(st.st_ctime);
   creation.dwHighDateTime = HIDWORD(st.st_ctime);

   modified.dwLowDateTime = LODWORD(st.st_mtime);
   modified.dwHighDateTime = HIDWORD(st.st_mtime);

}


#endif
