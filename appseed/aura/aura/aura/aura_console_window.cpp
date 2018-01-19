#include "framework.h"
#include <stdio.h>


void std_out_buffer::write(const void * lpBuf,memory_size_t nCount)
{

   DWORD dw;

   WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), lpBuf, nCount, &dw, NULL);

}



namespace console
{


   void window::redirect_io()
   {

   }


} // namespace console


