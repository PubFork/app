#include "framework.h"



compress_zip_is_dir::compress_zip_is_dir(bool bZipIsDir)
{

   m_bZipIsDirPrevious = thread_zip_is_dir();

   thread_set_zip_is_dir(bZipIsDir);

   m_bZipIsDir = thread_zip_is_dir();

}


compress_zip_is_dir::~compress_zip_is_dir()
{

   thread_set_zip_is_dir(m_bZipIsDirPrevious);

}



