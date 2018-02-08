#pragma once


BEGIN_EXTERN_C

CLASS_DECL_AURA DWORD get_last_error();
CLASS_DECL_AURA void set_last_error(DWORD dw);

END_EXTERN_C


/// Class with static functions to get information about an error.
class CLASS_DECL_AURA c_error
{
public:

   inline static DWORD get_last_error()
   {

      return errno;

   }

   inline static string GetErrorDescription(int iErrorCode = get_last_error())
   {

      return strerror(iErrorCode);

   }

};


#ifdef __WIN32
/// Class with static functions to get information about an error.
class CLASS_DECL_AURA sys_error
{
public:

   static DWORD get_last_error() { return ::get_last_error(); }

   static string GetErrorDescription(int iErrorCode = get_last_error())
   {
      LPVOID lpMsgBuf = NULL;
      FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                    NULL, iErrorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
                    reinterpret_cast<LPTSTR>(&lpMsgBuf), 0, NULL);
      string strErrorDescription;
      if (lpMsgBuf)
      {
         strErrorDescription = reinterpret_cast<LPTSTR>(lpMsgBuf);
         LocalFree(lpMsgBuf);
      }
      return strErrorDescription;
   }
};
#else

class CLASS_DECL_AURA sys_error : public c_error
{
public:

};

#endif


