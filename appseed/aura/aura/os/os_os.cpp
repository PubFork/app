#include "framework.h"

//CLASS_DECL_AURA string & get_command_line_string()
//{
//
//   return System.m_pappcore->m_strCommandLine;
//
//}



//CLASS_DECL_AURA string get_command_line_dup()
//{
//
//   return get_command_line_string();
//
//}


//BEGIN_EXTERN_C
//
//
//CLASS_DECL_AURA void set_command_line_dup(const char * psz)
//{
//
//   get_command_line_string() = psz;
//
//   ::file::path pathFolder = ::dir::ca2config() / "program";
//
//   string strAppId = get_command_line_param(psz, "app");
//
//   if (strAppId.has_char())
//   {
//
//      pathFolder /= strAppId;
//
//      ::file::path path = pathFolder / "last_command_line.txt";
//
//      file_put_contents_dup(path, get_command_line_string());
//
//      ::file::path pathExecutable = consume_param(psz, NULL);
//
//      string strAppTitle = executable_title_from_appid(strAppId);
//
//      path = pathFolder / "last_executable.txt";
//
//      if (file_is_equal_path_dup(pathExecutable.title(), strAppTitle))
//      {
//
//         file_put_contents_dup(path, pathExecutable);
//
//      }
//
//   }
//
//}
//
//
//CLASS_DECL_AURA void get_command_line_dup(char * psz, int iBuffer)
//{
//
//   strncpy(psz, get_command_line_dup(), iBuffer);
//
//}
//
//
//END_EXTERN_C
//



