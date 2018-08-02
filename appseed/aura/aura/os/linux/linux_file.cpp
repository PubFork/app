#include "framework.h"




string get_sys_temp_path()
{

   return ::file::path(getenv("HOME")) / ".ca2" / "time";

}



bool __node_further_file_is_equal(const ::file::path &,  const ::file::path &)
{


return false;

}
