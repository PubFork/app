#include "framework.h"
#include <stdio.h>


void std_out_buffer::write(const void * lpBuf,memory_size_t nCount)
{

   fwrite(lpBuf,1,nCount,stdout);

}



namespace console
{


   void window::redirect_io()
   {

   }


} // namespace console


