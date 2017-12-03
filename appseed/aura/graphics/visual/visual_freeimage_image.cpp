#include "framework.h"

#include <stdio.h>

#include "FreeImage.h"


FIBITMAP * freeimage_from_dib(::draw2d::dib * pdib)
{

   if (pdib == NULL)
      return NULL;

   if (pdib->area() <= 0)
      return NULL;

   FIBITMAP * fi;

   //   if(bm.bmBitsPixel == 32)
   {
      fi = FreeImage_AllocateT(FIT_BITMAP, pdib->m_size.cx, pdib->m_size.cy, 32);
   }
   // else
   {
      //  fi = FreeImage_Allocate(bm.bmWidth,bm.bmHeight,bm.bmBitsPixel);
   }
   // The GetDIBits function clears the biClrUsed and biClrImportant BITMAPINFO members (dont't know why)
   // So we save these infos below. This is needed for palettized images only.
   int32_t nColors = FreeImage_GetColorsUsed(fi);
   //HDC hdc = ::CreateCompatibleDC(NULL);

   int iWidth;
   int iHeight;
   COLORREF * pcolorref;
   int iStrideDst;

   iWidth = FreeImage_GetWidth(fi);

   iHeight = FreeImage_GetHeight(fi);

   pcolorref = (COLORREF *)FreeImage_GetBits(fi);

   if (FreeImage_GetInfo(fi)->bmiHeader.biSizeImage <= 0)
   {

      iStrideDst = iWidth * sizeof(COLORREF);

   }
   else
   {

      iStrideDst = FreeImage_GetInfo(fi)->bmiHeader.biSizeImage / iHeight;

   }

   COLORREF * pdst = pcolorref;

   COLORREF * psrc = pdib->m_pcolorref;

#if  defined(VSNORD)

   int iStrideSrc = pdib->m_iScan;

   for (index y = 0; y < pdib->m_size.cy; y++)
   {

      byte * pbDst = ((byte *)pdst) + ((pdib->m_size.cy - y - 1) * iStrideDst);

      byte * pbSrc = (byte *)psrc + (y * iStrideSrc);

      for (index x = 0; x < pdib->m_size.cx; x++)
      {

         pbDst[0] = pbSrc[2];

         pbDst[1] = pbSrc[1];

         pbDst[2] = pbSrc[0];

         pbDst[3] = pbSrc[3];

         pbDst += 4;

         pbSrc += 4;

      }

   }

#elif defined(APPLEOS)

   byte * pbDst = (byte *)pdst;

   byte * pbSrc = (byte *)psrc;

   ::count c = (count)pdib->area();

   while (c-- > 0)
   {

      pbDst[0] = pbSrc[2];

      pbDst[1] = pbSrc[1];

      pbDst[2] = pbSrc[0];

      pbDst[3] = pbSrc[3];

      pbDst += 4;

      pbSrc += 4;

   }

   /*

   byte * pbDst;

   byte * pbSrc;

   for(int i = 0; i < pdib->m_size.cy; i++)
   {

   pbDst = &((byte *) pdib->m_pcolorref)[pdib->m_iScan * (pdib->m_size.cy - i - 1)];

   pbSrc = &((byte *) pdata)[pbi->bmiHeader.biWidth * sizeof(COLORREF) * i];

   for(int j = 0; j < pdib->m_size.cx; j++)
   {

   pbDst[0] = pbSrc[2];

   pbDst[1] = pbSrc[1];

   pbDst[2] = pbSrc[0];

   pbDst[3] = pbSrc[3];

   pbDst += 4;

   pbSrc += 4;

   }

   }*/

#else

   int iStrideSrc = pdib->m_iScan;

   for (int i = 0; i < pdib->m_size.cy; i++)
   {

      memcpy(
      &((byte *)pdst)[iStrideDst * (pdib->m_size.cy - i - 1)],
      &((byte *)psrc)[iStrideSrc * i],
      iStrideDst);

   }
#endif

   //GetDIBits(hdc,(HBITMAP)hbitmap,0,FreeImage_GetHeight(fi),FreeImage_GetBits(fi),FreeImage_GetInfo(fi),DIB_RGB_COLORS);

   //::DeleteDC(hdc);

   //pbitmap->ReleaseHBITMAP(hbitmap);

   // restore BITMAPINFO members
   FreeImage_GetInfoHeader(fi)->biClrUsed = nColors;
   FreeImage_GetInfoHeader(fi)->biClrImportant = nColors;
   return fi;


}


bool dib_from_freeimage(::draw2d::dib * pdib, FIBITMAP *pfibitmap)
{

   if (pdib == NULL)
   {

      return false;

   }

   if (pfibitmap == NULL)
   {

      return false;

   }

   FIBITMAP * pimage32 = FreeImage_ConvertTo32Bits(pfibitmap);

   if (pimage32 == NULL)
   {

      return false;

   }

   int w = FreeImage_GetWidth(pimage32);

   int h = FreeImage_GetHeight(pimage32);

   if (!pdib->create(w, h))
   {

      return false;

   }

   void * pdata = FreeImage_GetBits(pimage32);

   int iSrcScan = FreeImage_GetPitch(pimage32);

   int iLineSize = w * sizeof(COLORREF);

   pdib->map();

#if defined(ANDROID)

   for (index y = 0; y < pdib->m_size.cy; y++)
   {

      byte * pbDst = ((byte *)pdib->m_pcolorref) + ((pdib->m_size.cy - y - 1) * pdib->m_iScan);

      byte * pbSrc = (byte *)pdata + (y * iSrcScan);

      for (index x = 0; x < pdib->m_size.cx; x++)
      {

         pbDst[0] = pbSrc[2];

         pbDst[1] = pbSrc[1];

         pbDst[2] = pbSrc[0];

         pbDst[3] = pbSrc[3];

         pbDst += 4;

         pbSrc += 4;

      }

   }

#elif defined(APPLEOS)

   byte * pbDst = (byte *)pdib->m_pcolorref;

   byte * pbSrc = (byte *)pdata;

   ::count c = (count)pdib->area();

   while (c-- > 0)
   {

      pbDst[0] = pbSrc[2];

      pbDst[1] = pbSrc[1];

      pbDst[2] = pbSrc[0];

      pbDst[3] = pbSrc[3];

      pbDst += 4;

      pbSrc += 4;

   }


#else

   for (int i = 0; i < pdib->m_size.cy; i++)
   {

      memcpy(
      &((byte *)pdib->m_pcolorref)[pdib->m_iScan * (h - i - 1)],
      &((byte *)pdata)[iSrcScan * i],
      iLineSize);

   }

#endif

   pdib->mult_alpha_fast();

   FreeImage_Unload(pimage32);

   return true;

}


//#include "visual_FreeImageFileProc.h"

/*uint32_t ___ReadProc    (void *buffer, uint32_t size, uint32_t count, fi_handle handle)
{
   uint32_t dwRead;
   if(ReadFile(handle, buffer, count * size, &dwRead, NULL))
   {
      return count;
   }
   else
   {
      return --count;
   }

}
uint32_t ___WriteProc   (void *buffer, uint32_t size, uint32_t count, fi_handle handle)
{
   uint32_t dwWritten;
   if(WriteFile(handle, buffer, count * size, &dwWritten, NULL))
   {
      return count;
   }
   else
   {
      return --count;
   }
}
int32_t      ___SeekProc    (fi_handle handle, long offset, int32_t origin)
{
   if(origin == SEEK_SET)
      origin = FILE_BEGIN;
   else if(origin == SEEK_CUR)
      origin = FILE_CURRENT;
   else if(origin == SEEK_END)
      origin = FILE_END;
   if(SetFilePointer(handle, offset, NULL, origin) == 0xFFFFFFFF)
      return -1;
   else
      return 0;
}
long     ___TellProc    (fi_handle handle)
{
   return SetFilePointer(handle, 0, NULL, SEEK_CUR);
}

uint32_t __ReadProc (void *buffer, uint32_t size, uint32_t count, fi_handle handle)
{
   uint32_t dwRead;
   if(ReadFile(handle, buffer, count * size, &dwRead, NULL))
   {
      return count;
   }
   else
   {
      return --count;
   }

}
uint32_t __WriteProc (void *buffer, uint32_t size, uint32_t count, fi_handle handle)
{
   uint32_t dwWritten;
   if(WriteFile(handle, buffer, count * size, &dwWritten, NULL))
   {
      return count;
   }
   else
   {
      return --count;
   }
}
int32_t __SeekProc (fi_handle handle, long offset, int32_t origin)
{
   if(origin == SEEK_SET)
      origin = FILE_BEGIN;
   else if(origin == SEEK_CUR)
      origin = FILE_CURRENT;
   else if(origin == SEEK_END)
      origin = FILE_END;
   if(SetFilePointer(handle, offset, NULL, origin) == 0xFFFFFFFF)
      return -1;
   else
      return 0;
}
long __TellProc (fi_handle handle)
{
   return SetFilePointer(handle, 0, NULL, SEEK_CUR);
}*/

//#ifndef WINDOWS
//
//#define DLL_CALLCONV
//
//#endif


unsigned DLL_CALLCONV  __ReadProc2 (void *buffer, unsigned size, unsigned count, fi_handle handle)
{

   memory_size_t dwRead;

   ::file::file *  pfile = (::file::file * ) handle;

   DWORD dwTotal = count * size;

   dwRead = pfile->read(buffer, dwTotal);

   if(dwRead == dwTotal)
   {

      return count;

   }
   else
   {

      return dwRead / size;

   }

}


unsigned DLL_CALLCONV __WriteProc2(void *buffer, unsigned size, unsigned count, fi_handle handle)
{

   ::file::file *  pfile = (::file::file * ) handle;

   try
   {

      pfile->write(buffer, count * size);

   }
   catch(...)
   {

      return 0;

   }

   return count;

}


int DLL_CALLCONV __SeekProc2(fi_handle handle, long offset, int origin)
{

   ::file::file *  pfile = (::file::file * ) handle;

   if (origin == SEEK_SET)
   {

      origin = ::file::seek_begin;

   }
   else if (origin == SEEK_CUR)
   {

      origin = ::file::seek_current;

   }
   else if (origin == SEEK_END)
   {

      origin = ::file::seek_end;

   }

   try
   {

      pfile->seek(offset, (::file::e_seek) origin);

   }
   catch(...)
   {

      return -1;

   }

   return 0;

}


long DLL_CALLCONV __TellProc2(fi_handle handle)
{

   ::file::file *  pfile = (::file::file * ) handle;

   return (long) pfile->get_position();

}



//static uint32_t _stdcall  __ReadProc3 (void *buffer, uint32_t size, uint32_t count, fi_handle handle);
//static uint32_t _stdcall __WriteProc3 (void *buffer, uint32_t size, uint32_t count, fi_handle handle);
//static int32_t _stdcall __SeekProc3 (fi_handle handle, long offset, int32_t origin);
//static long _stdcall __TellProc3 (fi_handle handle);


uint32_t _stdcall  ___Ex1File__ReadProc (void *buffer, uint32_t size, uint32_t count, fi_handle handle)
{

   memory_size_t dwRead;

   ::file::file_sp  pfile = (::file::file * ) handle;

   if((dwRead = pfile->read(buffer, count * size)))
   {

      return count;

   }
   else
   {

      return --count;

   }

}


uint32_t _stdcall ___Ex1File__WriteProc(void *buffer, uint32_t size, uint32_t count, fi_handle handle)
{

   ::file::file_sp  pfile = (::file::file * ) handle;

   try
   {

      pfile->write(buffer, count * size);

   }
   catch(...)
   {

      return --count;

   }

   return count;

}


int32_t _stdcall ___Ex1File__SeekProc(fi_handle handle, long offset, int32_t origin)
{

   ::file::file_sp  pfile = (::file::file * ) handle;

   if (origin == SEEK_SET)
   {

      origin = ::file::seek_begin;

   }
   else if (origin == SEEK_CUR)
   {

      origin = ::file::seek_current;

   }
   else if (origin == SEEK_END)
   {

      origin = ::file::seek_end;

   }

   if (pfile->seek(offset, (::file::e_seek) origin) == 0xFFFFFFFF)
   {

      return -1;

   }
   else
   {

      return 0;

   }

}


long _stdcall ___Ex1File__TellProc(fi_handle handle)
{

   ::file::file_sp  pfile = (::file::file * ) handle;

   return (long) pfile->get_position();

}



namespace visual
{


   void free_FreeImage(FIBITMAP * pfibitmap)
   {

#ifdef METROWIN

      _throw(todo(get_app()));

#else
      FreeImage_Unload(pfibitmap);
#endif
   }


}

   bool imaging::_save_image(::file::file * pfile, ::draw2d::dib * pdib, ::visual::save_image * psaveimage)
   {
   if(pdib == NULL)
   {
   return false;
   }
      ::visual::save_image saveimageDefault;
      if (psaveimage == NULL)
         psaveimage = &saveimageDefault;
      //#ifdef WINDOWS

      //    return windows_write_dib_to_file(pfile, m_p, psaveimage, m_p->get_app());

      //#else


      bool bOk = false;

      bool b8 = false;
      bool b24 = false;
      int iFreeImageSave = 0;
      FREE_IMAGE_FORMAT eformat = (FREE_IMAGE_FORMAT)0;
      string strFile;
      switch (psaveimage->m_eformat)
      {
      case ::visual::image::format_png:
         eformat = FreeImage_GetFIFFromFormat("PNG");
         strFile = "foo.png";
         break;
      case ::visual::image::format_bmp:
         eformat = FIF_BMP;
         strFile = "foo.bmp";
         break;
      case ::visual::image::format_gif:
         b8 = true;
         eformat = FIF_GIF;
         strFile = "foo.gif";
         break;
      case ::visual::image::format_jpeg:
         b24 = true;
         eformat = FreeImage_GetFIFFromFormat("JPEG");
         strFile = "foo.jpg";
         if (psaveimage->m_iQuality > 80)
         {
            iFreeImageSave |= JPEG_QUALITYSUPERB;
         }
         else if (psaveimage->m_iQuality > 67)
         {
            iFreeImageSave |= JPEG_QUALITYGOOD;
         }
         else if (psaveimage->m_iQuality > 33)
         {
            iFreeImageSave |= JPEG_QUALITYNORMAL;
         }
         else if (psaveimage->m_iQuality > 15)
         {
            iFreeImageSave |= JPEG_QUALITYAVERAGE;
         }
         else
         {
            iFreeImageSave |= JPEG_QUALITYBAD;
         }
         break;
      default:
         return false;
      }

      eformat = FreeImage_GetFIFFromFilename(strFile);


      FIMEMORY * pfm1 = FreeImage_OpenMemory();
      FIBITMAP * pfi7 = freeimage_from_dib(pdib);
      FIBITMAP * pfi8 = NULL;
      bool bConv;
      if (b8)
      {
         pfi8 = FreeImage_ConvertTo8Bits(pfi7);
         bConv = true;
      }
      else if (b24)
      {
         pfi8 = FreeImage_ConvertTo24Bits(pfi7);
         bConv = true;
      }
      else
      {
         //FreeImage_SetTransparent(pfi8,true);
         pfi8 = pfi7;
         bConv = false;
      }

      bOk = FreeImage_SaveToMemory(eformat, pfi8, pfm1, iFreeImageSave) != FALSE;

      BYTE * pbData = NULL;
      DWORD dwSize = 0;
      if (bOk)
         bOk = FreeImage_AcquireMemory(pfm1, &pbData, &dwSize) != FALSE;
      if (bOk)
      {
         try
         {
            pfile->write(pbData, dwSize);
         }
         catch (...)
         {
            bOk = false;
         }
      }

      FreeImage_CloseMemory(pfm1);
      if (bConv)
      {
         FreeImage_Unload(pfi8);
      }
      FreeImage_Unload(pfi7);



      return bOk != FALSE;

      //#endif

   }


   /*FIBITMAP * imaging::LoadImageFile(CArchive & ar)
   {
   ASSERT(!ar.IsStoring());

   return LoadImageFile(ar.GetFile());

   }
   */
   /*HBITMAP imaging::LoadBitmap(
   const char * lpszType,
   const char * lpszId)
   {
   ::exception::throw_not_implemented(get_app());

   ::memory_file file(get_app());

   ::core::Resource resource;

   if(!resource.ReadResource(*file.get_memory(), (UINT) MAKEINTRESOURCE(lpszId), lpszType))
   return false;

   file.seek_to_begin();

   ::file::file_sp  pfile = &file;

   FreeImageIO io;
   io.read_proc   = ___Ex1File__ReadProc;
   io.seek_proc   = ___Ex1File__SeekProc;
   io.tell_proc   = ___Ex1File__TellProc;
   io.write_proc  = ___Ex1File__WriteProc;

   FREE_IMAGE_FORMAT format;
   format = FreeImage_GetFileTypeFromHandle(&io, pfile ,16);
   FIBITMAP *pfi = NULL;
   if(true)
   {
   pfi = FreeImage_LoadFromHandle(format, &io, pfile);
   }

   if(pfi == NULL)
   return NULL;

   BITMAPINFO * pbi = FreeImage_GetInfo(pfi);
   void * pData = FreeImage_GetBits(pfi);


   HDC hdcSource = CreateDC(
   "DISPLAY",
   NULL,
   NULL,
   NULL);

   HBITMAP hBitmapSource = ::CreateCompatibleBitmap(
   hdcSource,
   pbi->bmiHeader.biWidth,
   pbi->bmiHeader.biHeight);

   if(pbi->bmiHeader.biHeight != SetDIBits(
   hdcSource,
   hBitmapSource,
   0,
   pbi->bmiHeader.biHeight,
   pData,
   pbi,
   DIB_RGB_COLORS))
   {
   FreeImage_Unload(pfi);
   DeleteDC(hdcSource);
   delete_object(hBitmapSource);
   return NULL;
   }

   FreeImage_Unload(pfi);
   DeleteDC(hdcSource);

   return hBitmapSource;
   */
   //}
   //*/


   //#endif // WINDOWSEX





//bool imaging::load_image(::draw2d::dib & dib, var varFile, ::aura::application * papp)
//{
//
//   ::memory_file memfile(get_app());
//
//   System.file().as_memory(varFile, *memfile.get_memory(), papp);
//
//   if (memfile.get_size() <= 0)
//      return false;
//
//   return load_image(dib, &memfile);
//
//}


//bool imaging::save_png(const char * lpcszFile, draw2d::dib & dib)
//{
//
//   auto * fi = freeimage_from_dib(&dib);
//
//   if (fi == NULL)
//   {
//
//      return false;
//
//   }
//
//   bool bOk = false;
//
//   if (FreeImage_Save(FreeImage_GetFIFFromFormat("PNG"), fi, lpcszFile, 0))
//   {
//
//      bOk = true;
//
//   }
//
//   FreeImage_Unload(fi);
//
//   return bOk;
//
//}
//
//
::draw2d::bitmap_sp freeimage_to_hbitmap(FIBITMAP * pfibitmap, ::aura::application * papp)
{

   if (pfibitmap == NULL)
   {

      return NULL;

   }

   ::draw2d::dib_sp dib(papp->allocer());

   if (!dib_from_freeimage(dib, pfibitmap))
   {

      return NULL;

   }

   return dib->detach_bitmap();

}


//::draw2d::bitmap_sp di_bitmap_from_freeimage(::draw2d::graphics * pgraphics, FIBITMAP * pFreeImage)
//{
//
//#ifdef WINDOWSEX
//
//   ::draw2d::bitmap_sp bitmap(pgraphics->get_app());
//
//   if (!bitmap->CreateDIBitmap(pgraphics, FreeImage_GetInfoHeader(pFreeImage), CBM_INIT, FreeImage_GetBits(pFreeImage), FreeImage_GetInfo(pFreeImage), DIB_RGB_COLORS))
//   {
//
//      TRACELASTERROR();
//
//      return NULL;
//
//   }
//
//   return bitmap;
//
//#else
//
//   _throw(todo(pgraphics->get_app()));
//
//#endif
//
//   return NULL;
//
//}


::draw2d::bitmap_sp bitmap_from_freeimage(::draw2d::graphics * pgraphics, FIBITMAP * pfibitmap)
{

   ::visual::dib_sp dib(pgraphics->allocer());

   dib_from_freeimage(dib, pfibitmap);

   return dib->detach_bitmap();

}


bool imaging::_load_image(::draw2d::dib * pdib, ::file::file *  pfile)
{

   if (pfile == NULL)
   {

      return false;

   }

   if (is_null(pdib))
   {

      return false;

   }

   FreeImageIO io;

   io.read_proc = __ReadProc2;

   io.seek_proc = __SeekProc2;

   io.tell_proc = __TellProc2;

   io.write_proc = __WriteProc2;

   FIBITMAP * pfibitmap = NULL;

   try
   {

      pfile->seek_to_begin();

      FREE_IMAGE_FORMAT format;

      format = FreeImage_GetFileTypeFromHandle(&io, (::file::file *)pfile);

      pfile->seek_to_begin();

      pfibitmap = FreeImage_LoadFromHandle(format, &io, (::file::file *)pfile);

   }
   catch (...)
   {

   }

   if (pfibitmap == NULL)
   {

      return false;

   }

   int iExifOrientation = -1;

   bool bOrientation = false;

   FITAG *tag = NULL;

   FIMETADATA *mdhandle = FreeImage_FindFirstMetadata(FIMD_EXIF_MAIN, pfibitmap, &tag);

   if (mdhandle)
   {

      do
      {

         if (!_stricmp(FreeImage_GetTagKey(tag), "orientation"))
         {

            bOrientation = true;

            auto type = FreeImage_GetTagType(tag);

            if (type == FIDT_SHORT)
            {

               auto value = FreeImage_GetTagValue(tag);

               iExifOrientation = *((unsigned short*)value);

            }

         }

         if (bOrientation)
         {

            break;

         }

      }

      while (FreeImage_FindNextMetadata(mdhandle, &tag));

      FreeImage_FindCloseMetadata(mdhandle);

   }

   if(!dib_from_freeimage(pdib, pfibitmap))
   {

      FreeImage_Unload(pfibitmap);

      return false;

   }

   FreeImage_Unload(pfibitmap);

   if (iExifOrientation >= 0)
   {

      ::draw2d::dib_sp dib2(allocer());

      //double dPiQuarter = ::atan(1.0);

      //double dPi = dPiQuarter * 4.0;

      // http://sylvana.net/jpegcrop/exif_orientation.html
      //1) transform = "";;
      //2) transform = "-flip horizontal";;
      //3) transform = "-rotate 180";;
      //4) transform = "-flip vertical";;
      //5) transform = "-transpose";;
      //6) transform = "-rotate 90";;
      //7) transform = "-transverse";;
      //8) transform = "-rotate 270";;
      //*) transform = "";;
      switch (iExifOrientation)
      {
      case 2:
         dib2->flip_horizontal(pdib);
         pdib->from(dib2);
         break;
      case 3:
         dib2->rotate(pdib, 180.0);
         pdib->from(dib2);
         break;
      case 4:
         dib2->flip_vertical(pdib);
         pdib->from(dib2);
         break;
      case 5:
         dib2->flip_horizontal(pdib);
         pdib->rotate(dib2, -270.0);
         break;
      case 6:
         dib2->rotate(pdib, -90.0);
         pdib->from(dib2);
         break;
      case 7:
         dib2->flip_horizontal(pdib);
         pdib->rotate(dib2, -90.0);
         break;
      case 8:
         dib2->rotate(pdib, -270.0);
         pdib->from(dib2);
         break;
      case 1:
      default:
         break;

      }

   }


   return true;


}





void os_init_imaging()
{

   FreeImage_Initialise(FALSE);

}


void os_term_imaging()
{

   FreeImage_DeInitialise();


}

