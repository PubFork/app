#include "framework.h"

CLASS_DECL_AURA string & get_command_line_string()
{

   return ::app_core::s_pappcore->m_strCommandLine;

}



CLASS_DECL_AURA string get_command_line_dup()
{

   return get_command_line_string();

}


BEGIN_EXTERN_C


CLASS_DECL_AURA void set_command_line_dup(const char * psz)
{

   get_command_line_string() = psz;

   ::file::path path = ::dir::system() / "echo";

   string strAppId = get_command_line_param(psz, "app");

   if(strAppId.has_char())
   {

      path /= strAppId;

      file_put_contents_dup(path, get_command_line_string());

   }

}


CLASS_DECL_AURA void get_command_line_dup(char * psz, int iBuffer)
{

   strncpy(psz, get_command_line_dup(), iBuffer);

}


END_EXTERN_C




