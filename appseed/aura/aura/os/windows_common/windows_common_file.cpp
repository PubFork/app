#include "framework.h"


::file::path file::app_module()
{

   hwstring hwPath(MAX_PATH * 16);

   if (!GetModuleFileNameW(NULL, hwPath, hwPath.count()))
   {

      return "";

   }

   string strPath;

   strPath = hwPath;

   return strPath;

}
