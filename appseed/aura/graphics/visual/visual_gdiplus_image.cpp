#include "framework.h"
#include <wincodec.h>
#ifdef METROWIN
#include <ShCore.h>
#endif


namespace visual
{


   //bool dib_sp::write_to_file(::file::file_sp pfile, save_image * psaveimage)
   //{
   //
   //   save_image saveimageDefault;
   //
   //   if (psaveimage == NULL)
   //      psaveimage = &saveimageDefault;
   //   //#ifdef WINDOWS

   //   //    return windows_write_dib_to_file(pfile, m_p, psaveimage, m_p->get_app());

   //   //#else


   //   bool bOk = false;

   //   bool b8 = false;
   //   bool b24 = false;
   //   int iFreeImageSave = 0;
   //   FREE_IMAGE_FORMAT eformat = (FREE_IMAGE_FORMAT)0;
   //   string strFile;
   //   switch (psaveimage->m_eformat)
   //   {
   //   case ::visual::image::format_png:
   //      eformat = FreeImage_GetFIFFromFormat("PNG");
   //      strFile = "foo.png";
   //      break;
   //   case ::visual::image::format_bmp:
   //      eformat = FIF_BMP;
   //      strFile = "foo.bmp";
   //      break;
   //   case ::visual::image::format_gif:
   //      b8 = true;
   //      eformat = FIF_GIF;
   //      strFile = "foo.gif";
   //      break;
   //   case ::visual::image::format_jpeg:
   //      b24 = true;
   //      eformat = FreeImage_GetFIFFromFormat("JPEG");
   //      strFile = "foo.jpg";
   //      if (psaveimage->m_iQuality > 80)
   //      {
   //         iFreeImageSave |= JPEG_QUALITYSUPERB;
   //      }
   //      else if (psaveimage->m_iQuality > 67)
   //      {
   //         iFreeImageSave |= JPEG_QUALITYGOOD;
   //      }
   //      else if (psaveimage->m_iQuality > 33)
   //      {
   //         iFreeImageSave |= JPEG_QUALITYNORMAL;
   //      }
   //      else if (psaveimage->m_iQuality > 15)
   //      {
   //         iFreeImageSave |= JPEG_QUALITYAVERAGE;
   //      }
   //      else
   //      {
   //         iFreeImageSave |= JPEG_QUALITYBAD;
   //      }
   //      break;
   //   default:
   //      return false;
   //   }

   //   eformat = FreeImage_GetFIFFromFilename(strFile);


   //   FIMEMORY * pfm1 = FreeImage_OpenMemory();
   //   FIBITMAP * pfi7 = App(m_p->m_pauraapp).imaging().dib_to_FI(m_p);
   //   FIBITMAP * pfi8 = NULL;
   //   bool bConv;
   //   if (b8)
   //   {
   //      pfi8 = FreeImage_ConvertTo8Bits(pfi7);
   //      bConv = true;
   //   }
   //   else if (b24)
   //   {
   //      pfi8 = FreeImage_ConvertTo24Bits(pfi7);
   //      bConv = true;
   //   }
   //   else
   //   {
   //      //FreeImage_SetTransparent(pfi8,true);
   //      pfi8 = pfi7;
   //      bConv = false;
   //   }

   //   bOk = FreeImage_SaveToMemory(eformat, pfi8, pfm1, iFreeImageSave) != FALSE;

   //   BYTE * pbData = NULL;
   //   DWORD dwSize = 0;
   //   if (bOk)
   //      bOk = FreeImage_AcquireMemory(pfm1, &pbData, &dwSize) != FALSE;
   //   if (bOk)
   //   {
   //      try
   //      {
   //         pfile->write(pbData, dwSize);
   //      }
   //      catch (...)
   //      {
   //         bOk = false;
   //      }
   //   }

   //   FreeImage_CloseMemory(pfm1);
   //   if (bConv)
   //   {
   //      FreeImage_Unload(pfi8);
   //   }
   //   FreeImage_Unload(pfi7);



   //   return bOk != FALSE;

   //   //#endif

   //}

}


//bool imaging::save_png(const  char * lpcszFile, ::draw2d::dib & dib)
//{
//
//   ::visual::dib_sp d;
//
//   d.::draw2d::dib_sp::operator=(&dib);
//
//   ::visual::save_image saveimage;
//
//   saveimage.m_eformat = ::visual::image::format_png;
//
//   saveimage.m_iQuality = 100;
//
//   return d.save_to_file(lpcszFile, &saveimage);
//
////
////
////#ifdef METROWIN
////
////      throw todo(get_app());
////
////#else
////
////      if (FreeImage_Save(FreeImage_GetFIFFromFormat("PNG"), dib, lpcszFile, 0))
////      {
////         //
////      }
////      if (bUnload)
////      {
////         FreeImage_Unload(dib);
////      }
////#endif
////
//}


//FIBITMAP * imaging::dib_to_FI(::draw2d::dib * pdib)
//{
//
//   if (pdib == NULL)
//      return NULL;
//
//   if (pdib->area() <= 0)
//      return NULL;
//
//   FIBITMAP * fi;
//
//   //   if(bm.bmBitsPixel == 32)
//   {
//      fi = FreeImage_AllocateT(FIT_BITMAP, pdib->m_size.cx, pdib->m_size.cy, 32);
//   }
//   // else
//   {
//      //  fi = FreeImage_Allocate(bm.bmWidth,bm.bmHeight,bm.bmBitsPixel);
//   }
//   // The GetDIBits function clears the biClrUsed and biClrImportant BITMAPINFO members (dont't know why)
//   // So we save these infos below. This is needed for palettized images only.
//   int32_t nColors = FreeImage_GetColorsUsed(fi);
//   //HDC hdc = ::CreateCompatibleDC(NULL);
//
//   int iWidth;
//   int iHeight;
//   COLORREF * pcolorref;
//   int iStrideDst;
//
//   iWidth = FreeImage_GetWidth(fi);
//
//   iHeight = FreeImage_GetHeight(fi);
//
//   pcolorref = (COLORREF *)FreeImage_GetBits(fi);
//
//   if (FreeImage_GetInfo(fi)->bmiHeader.biSizeImage <= 0)
//   {
//
//      iStrideDst = iWidth * sizeof(COLORREF);
//
//   }
//   else
//   {
//
//      iStrideDst = FreeImage_GetInfo(fi)->bmiHeader.biSizeImage / iHeight;
//
//   }
//
//   COLORREF * pdst = pcolorref;
//
//   COLORREF * psrc = pdib->m_pcolorref;
//
//#if  defined(VSNORD)
//
//   int iStrideSrc = pdib->m_iScan;
//
//   for (index y = 0; y < pdib->m_size.cy; y++)
//   {
//
//      byte * pbDst = ((byte *)pdst) + ((pdib->m_size.cy - y - 1) * iStrideDst);
//
//      byte * pbSrc = (byte *)psrc + (y * iStrideSrc);
//
//      for (index x = 0; x < pdib->m_size.cx; x++)
//      {
//
//         pbDst[0] = pbSrc[2];
//
//         pbDst[1] = pbSrc[1];
//
//         pbDst[2] = pbSrc[0];
//
//         pbDst[3] = pbSrc[3];
//
//         pbDst += 4;
//
//         pbSrc += 4;
//
//      }
//
//   }
//
//#elif defined(APPLEOS)
//
//   byte * pbDst = (byte *)pdst;
//
//   byte * pbSrc = (byte *)psrc;
//
//   ::count c = (count)pdib->area();
//
//   while (c-- > 0)
//   {
//
//      pbDst[0] = pbSrc[2];
//
//      pbDst[1] = pbSrc[1];
//
//      pbDst[2] = pbSrc[0];
//
//      pbDst[3] = pbSrc[3];
//
//      pbDst += 4;
//
//      pbSrc += 4;
//
//   }
//
//   /*
//
//   byte * pbDst;
//
//   byte * pbSrc;
//
//   for(int i = 0; i < pdib->m_size.cy; i++)
//   {
//
//   pbDst = &((byte *) pdib->m_pcolorref)[pdib->m_iScan * (pdib->m_size.cy - i - 1)];
//
//   pbSrc = &((byte *) pdata)[pbi->bmiHeader.biWidth * sizeof(COLORREF) * i];
//
//   for(int j = 0; j < pdib->m_size.cx; j++)
//   {
//
//   pbDst[0] = pbSrc[2];
//
//   pbDst[1] = pbSrc[1];
//
//   pbDst[2] = pbSrc[0];
//
//   pbDst[3] = pbSrc[3];
//
//   pbDst += 4;
//
//   pbSrc += 4;
//
//   }
//
//   }*/
//
//#else
//
//   int iStrideSrc = pdib->m_iScan;
//
//   for (int i = 0; i < pdib->m_size.cy; i++)
//   {
//
//      memcpy(
//         &((byte *)pdst)[iStrideDst * (pdib->m_size.cy - i - 1)],
//         &((byte *)psrc)[iStrideSrc * i],
//         iStrideDst);
//
//   }
//#endif
//
//   //GetDIBits(hdc,(HBITMAP)hbitmap,0,FreeImage_GetHeight(fi),FreeImage_GetBits(fi),FreeImage_GetInfo(fi),DIB_RGB_COLORS);
//
//   //::DeleteDC(hdc);
//
//   //pbitmap->ReleaseHBITMAP(hbitmap);
//
//   // restore BITMAPINFO members
//   FreeImage_GetInfoHeader(fi)->biClrUsed = nColors;
//   FreeImage_GetInfoHeader(fi)->biClrImportant = nColors;
//   return fi;
//
//
//}
//
//
//
//::draw2d::bitmap_sp imaging::FItoHBITMAP(FIBITMAP * pfibitmap, bool bUnloadFI)
//{
//
//   if (pfibitmap == NULL)
//      return NULL;
//
//   //   BITMAPINFO * pbi = FreeImage_GetInfo(pfibitmap);
//   // void * pData = FreeImage_GetBits(pfibitmap);
//
//
//   ::draw2d::dib_sp dib(allocer());
//
//   //BITMAPINFO * pi = FreeImage_GetInfo(pFreeImage);
//
//   ::draw2d::graphics_sp spgraphics(allocer());
//   spgraphics->CreateCompatibleDC(NULL);
//
//   if (!from(dib, spgraphics, pfibitmap, false))
//      return NULL;
//
//   return dib->detach_bitmap();
//
//   /*::draw2d::graphics_sp spgraphics(allocer());
//   spgraphics->CreateCompatibleDC(NULL);
//
//   ::draw2d::dib_sp dibSource(get_app());
//   dibSource->create(pbi->bmiHeader.biWidth, pbi->bmiHeader.biHeight);
//
//   dibSource->dc_select(false);
//
//   if(pbi->bmiHeader.biHeight != SetDIBits(
//   (HDC)spgraphics->get_os_data(),
//   (HBITMAP) dibSource->get_bitmap()->get_os_data(),
//   0,
//   pbi->bmiHeader.biHeight,
//   pData,
//   pbi,
//   DIB_RGB_COLORS))
//   {
//   if(bUnloadFI)
//   {
//   FreeImage_Unload(pfibitmap);
//   }
//   return NULL;
//   }
//
//   if(bUnloadFI)
//   {
//   FreeImage_Unload(pfibitmap);
//   }
//   */
//
//   //return dibSource->detach_bitmap();
//}
//
//::draw2d::bitmap_sp imaging::CreateDIBitmap(::draw2d::graphics * pgraphics, FIBITMAP * pFreeImage)
//{
//
//
//#ifdef WINDOWSEX
//   ::draw2d::bitmap_sp bitmap(get_app());
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
//#else
//
//   _throw(todo(get_app()));
//
//#endif
//   return NULL;
//}
//
//
//::draw2d::bitmap_sp imaging::CreateBitmap(::draw2d::graphics * pgraphics, FIBITMAP * pFreeImage)
//{
//   ::visual::dib_sp dib(allocer());
//
//#ifdef METROWIN
//
//   _throw(todo(get_app()));
//
//#else
//
//   //BITMAPINFO * pi = FreeImage_GetInfo(pFreeImage);
//
//
//
//   from(dib, pgraphics, pFreeImage, false);
//
//
//   return dib->detach_bitmap();
//
//#endif
//
//   /*   ::draw2d::bitmap_sp bitmap(get_app());
//   void * pBits = FreeImage_GetBits(pFreeImage);
//   if(!bitmap->CreateDIBitmap(pgraphics,
//   FreeImage_GetInfoHeader(pFreeImage),
//   CBM_INIT,
//   pBits,
//   FreeImage_GetInfo(pFreeImage),
//   DIB_RGB_COLORS))
//   {
//   TRACELASTERROR();
//   return (::draw2d::bitmap *) NULL;
//   }
//
//   //   LPVOID lpBits;
//   //   BITMAPINFO *pbi = FreeImage_GetInfo(pFreeImage);
//   //   HBITMAP hBitmap = ::CreateDIBSection(
//   //      NULL,
//   //      pbi,
//   //      DIB_RGB_COLORS,
//   //      &lpBits,
//   //      NULL,
//   //      0);
//   //   memcpy(lpBits, FreeImage_GetBits(pFreeImage), pbi->bmiHeader.biSize);
//   LPBITMAPINFO pbi = FreeImage_GetInfo(pFreeImage);
//   int32_t iSizeBitsZ = ((pbi->bmiHeader.biWidth * pbi->bmiHeader.biBitCount / 8 + 3) & ~3) * pbi->bmiHeader.biHeight;
//   void * pDataZ = malloc(iSizeBitsZ);
//   if(pbi->bmiHeader.biHeight != GetDIBits(
//   (HDC)pgraphics->get_os_data(),           // handle to device context
//   (HBITMAP)bitmap->get_os_data(),      // handle to bitmap
//   0,   // first scan line to set in destination bitmap
//   FreeImage_GetInfo(pFreeImage)->bmiHeader.biHeight,   // number of scan lines to copy
//   pDataZ,    // address of array for bitmap bits
//   FreeImage_GetInfo(pFreeImage), // address of structure with bitmap data
//   DIB_RGB_COLORS        // RGB or palette index
//   ))
//   {
//   //      int32_t i = 1 +1;
//   TRACELASTERROR();
//   }
//   return bitmap;*/
//}
//
//
//
//bool imaging::from(::draw2d::dib * pdib, ::draw2d::graphics * pgraphics, FIBITMAP *pfibitmap, bool bUnloadFI, ::aura::application * papp)
//{
//
//   if (pfibitmap == NULL)
//      return false;
//
//   if (papp == NULL)
//      papp = get_app();
//
//   BITMAPINFO * pbi = NULL;
//
//   void * pdata = NULL;
//   FIBITMAP * pimage32 = FreeImage_ConvertTo32Bits(pfibitmap);
//
//   if (pimage32 == NULL)
//   {
//
//      return false;
//
//   }
//
//   pbi = FreeImage_GetInfo(pimage32);
//
//   pdata = FreeImage_GetBits(pimage32);
//
//
//   if (!pdib->create(pbi->bmiHeader.biWidth, pbi->bmiHeader.biHeight))
//      return false;
//
//
//   /*   COLORREF * pcolorref = NULL;
//
//   HBITMAP hbitmap = ::CreateDIBSection(NULL, &pdib->m_info, DIB_RGB_COLORS, (void **)&pcolorref, NULL, 0);
//
//   if (hbitmap == NULL)
//   {
//   pdib->Destroy();
//   return false;
//   }
//
//   HDC hdc = ::CreateCompatibleDC(NULL);
//
//   if (pbi->bmiHeader.biHeight != SetDIBits(
//   hdc,
//   hbitmap,
//   0,
//   pbi->bmiHeader.biHeight,
//   pdata,
//   pbi,
//   DIB_RGB_COLORS))
//   {
//   pdib->Destroy();
//   if (bUnloadFI)
//   {
//   FreeImage_Unload(pfibitmap);
//   }
//   return false;
//   }
//   */
//
//   pdib->map();
//
//   //int stride = pbi->bmiHeader.biWidth * sizeof(COLORREF);
//
//   //#if defined(VSNORD) && defined(__arm__)
//#if defined(ANDROID)
//
//   // LITTLE_LIT_LIGHT_LITE_LITLE_ENDIANS!!!!!!!!!!
//
//   //::draw2d::copy_colorref(
//   //   pdib->m_size.cx,
//   //   pdib->m_size.cy,
//   //   pdib->m_pcolorref,
//   //   pdib->m_iScan,
//   //   (COLORREF *)pdata,
//   //   stride);
//
//   int stride = pbi->bmiHeader.biWidth * sizeof(COLORREF);
//
//   for (index y = 0; y < pdib->m_size.cy; y++)
//   {
//
//      byte * pbDst = ((byte *)pdib->m_pcolorref) + ((pdib->m_size.cy - y - 1) * pdib->m_iScan);
//
//      byte * pbSrc = (byte *)pdata + (y * stride);
//
//      for (index x = 0; x < pdib->m_size.cx; x++)
//      {
//
//         pbDst[0] = pbSrc[2];
//
//         pbDst[1] = pbSrc[1];
//
//         pbDst[2] = pbSrc[0];
//
//         pbDst[3] = pbSrc[3];
//
//         pbDst += 4;
//
//         pbSrc += 4;
//
//      }
//
//   }
//
//#elif defined(APPLEOS)
//
//   byte * pbDst = (byte *)pdib->m_pcolorref;
//
//   byte * pbSrc = (byte *)pdata;
//
//   ::count c = (count)pdib->area();
//
//   while (c-- > 0)
//   {
//
//      pbDst[0] = pbSrc[2];
//
//      pbDst[1] = pbSrc[1];
//
//      pbDst[2] = pbSrc[0];
//
//      pbDst[3] = pbSrc[3];
//
//      pbDst += 4;
//
//      pbSrc += 4;
//
//   }
//
//   /*
//
//   byte * pbDst;
//
//   byte * pbSrc;
//
//   for(int i = 0; i < pdib->m_size.cy; i++)
//   {
//
//   pbDst = &((byte *) pdib->m_pcolorref)[pdib->m_iScan * (pdib->m_size.cy - i - 1)];
//
//   pbSrc = &((byte *) pdata)[pbi->bmiHeader.biWidth * sizeof(COLORREF) * i];
//
//   for(int j = 0; j < pdib->m_size.cx; j++)
//   {
//
//   pbDst[0] = pbSrc[2];
//
//   pbDst[1] = pbSrc[1];
//
//   pbDst[2] = pbSrc[0];
//
//   pbDst[3] = pbSrc[3];
//
//   pbDst += 4;
//
//   pbSrc += 4;
//
//   }
//
//   }*/
//
//#else
//   for (int i = 0; i < pdib->m_size.cy; i++)
//   {
//
//      memcpy(
//         &((byte *)pdib->m_pcolorref)[pdib->m_iScan * (pdib->m_size.cy - i - 1)],
//         &((byte *)pdata)[pbi->bmiHeader.biWidth * sizeof(COLORREF) * i],
//         pdib->m_iScan);
//
//   }
//#endif
//
//   //#if defined(LINUX) || defined(VSNORD) || defined(METROWIN)
//   pdib->mult_alpha_fast();
//   //#endif
//
//
//
//   //   RGBQUAD bkcolor;
//   FreeImage_Unload(pimage32);
//   if (bUnloadFI)
//   {
//
//      FreeImage_Unload(pfibitmap);
//
//   }
//
//   return true;
//
//}




bool dib_from_wicbitmapsource(::draw2d::dib * pdib, IWICBitmapSource * piConverter, IWICImagingFactory * piFactory)
{

   comptr < IWICBitmap > piBmp;

   HRESULT hr = piFactory->CreateBitmapFromSource(piConverter, WICBitmapCacheOnLoad, &piBmp);

   if (hr != S_OK)
   {

      return false;

   }

   UINT uiWidth;

   UINT uiHeight;

   hr = piBmp->GetSize(&uiWidth, &uiHeight);

   if (hr != S_OK)
   {

      return false;

   }

   WICRect rc;

   rc.X = 0;
   rc.Y = 0;
   rc.Width = uiWidth;
   rc.Height = uiHeight;

   comptr < IWICBitmapLock > piLock;

   hr = piBmp->Lock(&rc, WICBitmapLockRead, &piLock);

   if (hr != S_OK)
   {

      return false;

   }

   UINT cbStride;

   piLock->GetStride(&cbStride);

   if (hr != S_OK)
   {

      return false;

   }

   UINT uiArea;

   BYTE * pData;

   hr = piLock->GetDataPointer(&uiArea, &pData);

   if (hr != S_OK)
   {

      return false;

   }

   if (!pdib->create(uiWidth, uiHeight))
   {

      return false;

   }

   pdib->map();

   ::draw2d::copy_colorref(uiWidth, uiHeight, pdib->m_pcolorref, pdib->m_iScan, (COLORREF *)pData, cbStride);

   return true;


}


bool imaging::_load_image(::draw2d::dib * pdib, ::file::file * pfile)
{

   if (pdib == NULL)
   {

      return false;

   }

   defer_co_initialize_ex(false);

   comptr < IWICImagingFactory > piFactory;

   HRESULT hr = piFactory.CoCreateInstance(CLSID_WICImagingFactory1);

   if (hr != S_OK) return false;

   comptr < IWICStream > piStream;

   hr = piFactory->CreateStream(&piStream);

   if (hr != S_OK) return false;

   memory m;

   m.allocate((memory_size_t) pfile->get_length());

   pfile->read(m.get_data(), m.get_size());

   hr = piStream->InitializeFromMemory(m.get_data(), (DWORD) m.get_size());

   if (hr != S_OK)
   {

      return false;

   }



   comptr < IWICBitmapDecoder > piDecoder;

   hr = piFactory->CreateDecoderFromStream(piStream, 0, WICDecodeMetadataCacheOnLoad, &piDecoder); // jpeg,png:OK, bmp:88982f50のエラーになる, iconもエラー

   if (hr != S_OK)
   {

      return false;

   }

   comptr < IWICBitmapFrameDecode > piBitmapFrame;

   hr = piDecoder->GetFrame(0, &piBitmapFrame);

   if (hr != S_OK) return false;

   int iOrientation = -1;

   {

      HRESULT hrExif = hr;

      comptr<IWICMetadataQueryReader> pQueryReader;

      if (SUCCEEDED(hrExif))
      {

         hrExif = piBitmapFrame->GetMetadataQueryReader(&pQueryReader);

      }

      if (SUCCEEDED(hrExif))
      {

         PROPVARIANT value;

         PropVariantClear(&value);

         hrExif = pQueryReader->GetMetadataByName(L"/app1/ifd/{ushort=274}", &value);

         if (FAILED(hrExif))
         {

            hrExif = pQueryReader->GetMetadataByName(L"/ifd/{ushort=274}", &value);

         }

         if (SUCCEEDED(hrExif))
         {

            iOrientation = value.uiVal;

         }

         PropVariantClear(&value); // Clear value for new query.

      }

   }

   // Convert the image format to 32bppPBGRA
   // (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
   // http://d.hatena.ne.jp/sugarontop/20141015
   comptr < IWICFormatConverter > piConverter;

   hr = piFactory->CreateFormatConverter(&piConverter);

   if (hr != S_OK) return false;

   hr = piConverter->Initialize(piBitmapFrame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.f, WICBitmapPaletteTypeMedianCut);

   if (hr != S_OK) return false;

   if (!dib_from_wicbitmapsource(pdib, piConverter, piFactory))
   {

      return false;

   }

   pdib->oprop("exif_orientation") = iOrientation;

   return true;

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
/*
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




bool windows_write_dib_to_file(::file::file_sp pfile, ::draw2d::dib * pdib, ::visual::save_image * psaveimage, ::aura::application * papp)
{

#ifdef METROWIN

   Windows::Storage::Streams::InMemoryRandomAccessStream ^ randomAccessStream = ref new Windows::Storage::Streams::InMemoryRandomAccessStream();

   //::wait(randomAccessStream->WriteAsync(get_os_buffer()));

   comptr < IStream > pstream;

   ::CreateStreamOverRandomAccessStream(randomAccessStream, IID_PPV_ARGS(&pstream));

#else

   comptr < IStream > pstream = LIBCALL(shlwapi, SHCreateMemStream)(NULL, NULL);

#endif

   //m_spmemfile->Truncate(0);

   //m_spmemfile->seek_to_begin();

   comptr < IWICImagingFactory > piFactory = NULL;
   comptr < IWICBitmapEncoder > piEncoder = NULL;
   comptr < IWICBitmapFrameEncode > piBitmapFrame = NULL;
   comptr < IPropertyBag2 > pPropertybag = NULL;

   comptr < IWICStream > piStream = NULL;
   UINT uiWidth = pdib->size().cx;
   UINT uiHeight = pdib->size().cy;

   HRESULT hr = CoCreateInstance(
                CLSID_WICImagingFactory,
                NULL,
                CLSCTX_INPROC_SERVER,
                IID_IWICImagingFactory,
                (LPVOID*)&piFactory);

   if (SUCCEEDED(hr))
   {
      hr = piFactory->CreateStream(&piStream);
   }

   if (SUCCEEDED(hr))
   {
      hr = piStream->InitializeFromIStream(pstream);
   }

   if (SUCCEEDED(hr))
   {
      switch (psaveimage->m_eformat)
      {
      case ::visual::image::format_bmp:
         hr = piFactory->CreateEncoder(GUID_ContainerFormatBmp, NULL, &piEncoder);
         break;
      case ::visual::image::format_gif:
         hr = piFactory->CreateEncoder(GUID_ContainerFormatGif, NULL, &piEncoder);
         break;
      case ::visual::image::format_jpeg:
         hr = piFactory->CreateEncoder(GUID_ContainerFormatJpeg, NULL, &piEncoder);
         break;
      case ::visual::image::format_png:
         hr = piFactory->CreateEncoder(GUID_ContainerFormatPng, NULL, &piEncoder);
         break;
      default:
         break;
      }
   }

   if (SUCCEEDED(hr))
   {
      hr = piEncoder->Initialize(piStream, WICBitmapEncoderNoCache);
   }

   if (SUCCEEDED(hr))
   {
      hr = piEncoder->CreateNewFrame(&piBitmapFrame, &pPropertybag);
   }

   if (SUCCEEDED(hr))
   {
      //if(m_bJxr)
      //{
      //   //PROPBAG2 option ={0};
      //   //option.pstrName = L"ImageQuality";
      //   //VARIANT varValue;
      //   //VariantInit(&varValue);
      //   //varValue.vt = VT_R4;
      //   //varValue.fltVal = 0.49f;
      //   PROPBAG2 option ={0};
      //   option.pstrName = L"UseCodecOptions";
      //   VARIANT varValue;
      //   VariantInit(&varValue);
      //   varValue.vt = VT_BOOL;
      //   varValue.boolVal = -1;
      //   if(SUCCEEDED(hr))
      //   {
      //      hr = pPropertybag->Write(1,&option,&varValue);
      //   }
      //   option.pstrName = L"Quality";
      //   VariantInit(&varValue);
      //   varValue.vt = VT_UI1;
      //   varValue.bVal = 184;
      //   if(SUCCEEDED(hr))
      //   {
      //      hr = pPropertybag->Write(1,&option,&varValue);
      //   }
      //   option.pstrName = L"Subsampling";
      //   VariantInit(&varValue);
      //   varValue.vt = VT_UI1;
      //   varValue.bVal = 1;
      //   if(SUCCEEDED(hr))
      //   {
      //      hr = pPropertybag->Write(1,&option,&varValue);
      //   }
      //   option.pstrName = L"Overlap";
      //   VariantInit(&varValue);
      //   varValue.vt = VT_UI1;
      //   varValue.bVal = 2;
      //   if(SUCCEEDED(hr))
      //   {
      //      hr = pPropertybag->Write(1,&option,&varValue);
      //   }
      //   option.pstrName = L"StreamOnly";
      //   VariantInit(&varValue);
      //   varValue.vt = VT_BOOL;
      //   varValue.boolVal = -1;
      //   if(SUCCEEDED(hr))
      //   {
      //      hr = pPropertybag->Write(1,&option,&varValue);
      //   }
      //}
      if (psaveimage->m_eformat == ::visual::image::format_jpeg)
      {
         PROPBAG2 option = { 0 };
         option.pstrName = L"ImageQuality";
         VARIANT varValue;
         VariantInit(&varValue);
         varValue.vt = VT_R4;
         varValue.fltVal = MAX(0.f, MIN(1.f, psaveimage->m_iQuality / 100.0f));
         if (SUCCEEDED(hr))
         {
            hr = pPropertybag->Write(1, &option, &varValue);
         }
      }
      if (SUCCEEDED(hr))
      {
         hr = piBitmapFrame->Initialize(pPropertybag);
      }
   }

   if (SUCCEEDED(hr))
   {
      hr = piBitmapFrame->SetSize(uiWidth, uiHeight);
   }

   WICPixelFormatGUID formatGUID = GUID_WICPixelFormat32bppBGRA;
   if (SUCCEEDED(hr))
   {
      hr = piBitmapFrame->SetPixelFormat(&formatGUID);
   }
   pdib->map();
   if (SUCCEEDED(hr))
   {
      if (IsEqualGUID(formatGUID, GUID_WICPixelFormat32bppBGRA))
      {
         if (SUCCEEDED(hr))
         {
            hr = piBitmapFrame->WritePixels(uiHeight, pdib->m_iScan, uiHeight*pdib->m_iScan, (BYTE *)pdib->m_pcolorref);
         }
      }
      else
      {

         comptr <IWICBitmap> pbitmap;

         if (SUCCEEDED(hr))
         {
            hr = piFactory->CreateBitmapFromMemory(
                 pdib->size().cx,
                 pdib->size().cy,
                 GUID_WICPixelFormat32bppBGRA,
                 pdib->m_iScan,
                 pdib->m_iScan * pdib->size().cy,
                 (BYTE *)pdib->m_pcolorref,
                 &pbitmap
                 );
         }

         comptr<IWICFormatConverter> pconverter;

         if (SUCCEEDED(hr))
         {

            hr = piFactory->CreateFormatConverter(&pconverter);

         }



         if (SUCCEEDED(hr))
         {

            hr = pconverter->Initialize(pbitmap, formatGUID, WICBitmapDitherTypeNone, NULL, 0.f, WICBitmapPaletteTypeCustom);
         }

         //Step 4: Create render target and D2D bitmap from IWICBitmapSource
         //UINT width=0;
         //UINT height=0;
         //if(SUCCEEDED(hr))
         //{
         //   hr = pbitmap->GetSize(&width,&height);
         //}

         //pdib->create(width,height);

         if (SUCCEEDED(hr))
         {
            hr = piBitmapFrame->WriteSource(pconverter, NULL);
         }


         //for(int k = 0; k < height; k++)
         //{
         //   memcpy(&pb[k * iStride],&mem.get_data()[(height - 1 - k) * iStride],iStride);
         //}

      }
   }



   if (SUCCEEDED(hr))
   {
      hr = piBitmapFrame->Commit();
   }

   if (SUCCEEDED(hr))
   {
      hr = piEncoder->Commit();
   }

   //if(piFactory)
   //   piFactory->Release();

   //if(piBitmapFrame)
   //   piBitmapFrame->Release();

   //if(piEncoder)
   //   piEncoder->Release();

   //if(piStream)
   //   piStream->Release();



   STATSTG stg;
   ZERO(stg);
   pstream->Stat(&stg, STATFLAG_NONAME);
   LARGE_INTEGER l;
   l.QuadPart = 0;
   pstream->Seek(l, STREAM_SEEK_SET, NULL);


   memory mem(papp);

   mem.allocate(1024 * 1024);

   ULONG ulPos = 0;
   ULONG ulRead;
   ULONGLONG ul;
   do
   {

      ulRead = 0;

      ul = stg.cbSize.QuadPart - ulPos;

      pstream->Read(mem.get_data(), (ULONG)MIN(ul, mem.get_size()), &ulRead);

      if (ulRead > 0)
      {

         pfile->write(mem.get_data(), ulRead);

         ulPos += ulRead;

      }

   }
   while (ulRead > 0 && stg.cbSize.QuadPart - ulPos > 0);

   //pstream->Release();

   return true;

}


