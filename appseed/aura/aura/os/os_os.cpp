#include "framework.h"


CLASS_DECL_AURA string & get_command_line_string()
{

   static string g_strCommandLine;

   return g_strCommandLine;

}



CLASS_DECL_AURA string get_command_line_dup()
{

   return get_command_line_string();

}


BEGIN_EXTERN_C


CLASS_DECL_AURA void set_command_line_dup(const char * psz)
{

   get_command_line_string() = psz;

}


CLASS_DECL_AURA void get_command_line_dup(char * psz, int iBuffer)
{

   strncpy(psz, get_command_line_dup(), iBuffer);

}


END_EXTERN_C


