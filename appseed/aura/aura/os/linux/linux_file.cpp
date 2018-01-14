#include "framework.h"




string get_sys_temp_path()
{

   return ::file::path(getenv("HOME")) / ".ca2" / "time";

}
