#include "framework.h"
//#include "fiasco_finder.h"


#include <math.h>



void cra_from_quada(array < COLORREF > & cra, RGBQUAD * pquad, int iCount);

bool gif_load_frame(::draw2d::dib * pdibCompose, ::visual::dib_sp::array * pdiba, ::visual::dib_sp::pointer * pointer, int uFrameIndex, byte * ba, int iScan, array < COLORREF > & cra, int transparentIndex);

bool freeimage_load_diba_frame(::draw2d::dib * pdibCompose, ::visual::dib_sp::array * pdiba, int iFrame, FIBITMAP * pfi, ::aura::application * papp);

bool freeimage_load_diba_from_file(::visual::dib_sp::array * pdiba, ::file::file_sp pfile, ::aura::application * papp)
{

   throw not_implemented(NULL);

   return false;

}


bool freeimage_load_diba_frame(::draw2d::dib * pdibCompose, ::visual::dib_sp::array * pdiba, int iFrame, FIBITMAP * pfi, ::aura::application * papp)
{


   throw not_implemented(NULL);

   return false;



}




void cra_from_quada(array < COLORREF > & cra, RGBQUAD * pquad, int iCount)
{

   cra.set_size(iCount);

   for (index i = 0; i < iCount; i++)
   {

#if defined(ANDROID) && defined(__arm__)
      cra[i] = ARGB(255, pquad[i].rgbRed, pquad[i].rgbGreen, pquad[i].rgbBlue);
#else
      cra[i] = ARGB(255, pquad[i].rgbBlue, pquad[i].rgbGreen, pquad[i].rgbRed);
#endif

      if (cra[i] == ARGB(255, 255, 255, 255))
      {

         output_debug_string("completely white");

      }

   }

}
