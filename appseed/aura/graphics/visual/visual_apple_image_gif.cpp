//
//  visual_apple_image_gif.cpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 21/10/17.
//



#include "framework.h"
//#include "fiasco_finder.h"


#include <math.h>



//void cra_from_quada(array < COLORREF > & cra, RGBQUAD * pquad, int iCount);

bool gif_load_frame(::draw2d::dib * pdibCompose, ::visual::dib_sp::array * pdiba, ::visual::dib_sp::pointer * pointer, int uFrameIndex, byte * ba, int iScan, array < COLORREF > & cra, int transparentIndex);

bool freeimage_load_diba_frame(::draw2d::dib * pdibCompose, ::visual::dib_sp::array * pdiba, int iFrame, FIBITMAP * pfi, ::aura::application * papp);

//bool dib_from_wicbitmapsource(::draw2d::dib & dib, IWICBitmapSource * piConverter, IWICImagingFactory * piFactory);
//
//
//COLORREF metadata_GetBackgroundColor(IWICMetadataQueryReader *pMetadataQueryReader, IWICBitmapDecoder * piDecoder, IWICImagingFactory * piFactory)
//{
//
//   DWORD dwBGColor;
//   BYTE backgroundIndex = 0;
//   WICColor rgColors[256];
//   UINT cColorsCopied = 0;
//   PROPVARIANT propVariant;
//   PropVariantInit(&propVariant);
//   ::windows::comptr < IWICPalette > pWicPalette;
//
//   COLORREF crBk = 0;
//
//   // If we have a global palette, get the palette and background color
//   HRESULT hr = pMetadataQueryReader->GetMetadataByName(L"/logscrdesc/GlobalColorTableFlag", &propVariant);
//   if (SUCCEEDED(hr))
//   {
//      hr = (propVariant.vt != VT_BOOL || !propVariant.boolVal) ? E_FAIL : S_OK;
//      PropVariantClear(&propVariant);
//   }
//
//   if (SUCCEEDED(hr))
//   {
//      // Background color index
//      hr = pMetadataQueryReader->GetMetadataByName(L"/logscrdesc/BackgroundColorIndex", &propVariant);
//      if (SUCCEEDED(hr))
//      {
//         hr = (propVariant.vt != VT_UI1) ? E_FAIL : S_OK;
//         if (SUCCEEDED(hr))
//         {
//            backgroundIndex = propVariant.bVal;
//         }
//         PropVariantClear(&propVariant);
//      }
//   }
//
//   // Get the color from the palette
//   if (SUCCEEDED(hr))
//   {
//      hr = piFactory->CreatePalette(&pWicPalette);
//   }
//
//   if (SUCCEEDED(hr))
//   {
//      // Get the global palette
//      hr = piDecoder->CopyPalette(pWicPalette);
//   }
//
//   if (SUCCEEDED(hr))
//   {
//      hr = pWicPalette->GetColors(
//                                  ARRAYSIZE(rgColors),
//                                  rgColors,
//                                  &cColorsCopied);
//   }
//
//   if (SUCCEEDED(hr))
//   {
//      // Check whether background color is outside range
//      hr = (backgroundIndex >= cColorsCopied) ? E_FAIL : S_OK;
//   }
//
//   if (SUCCEEDED(hr))
//   {
//      // Get the color in ARGB format
//      dwBGColor = rgColors[backgroundIndex];
//
//      // The background color is in ARGB format, and we want to
//      // extract the alpha value and convert it to float
//      crBk = dwBGColor;
//   }
//
//   return crBk;
//
//}


bool freeimage_load_diba_from_file(::visual::dib_sp::array * pdiba, ::file::file_sp pfile, ::aura::application * papp)
{
   
   //defer_co_initialize_ex(false);
   
//   windows::comptr < IWICImagingFactory > piFactory;
//
//   HRESULT hr = piFactory.CoCreateInstance(CLSID_WICImagingFactory);
//
//   if (hr != S_OK) return false;
//
//   windows::comptr < IWICStream > piStream;
//
//   hr = piFactory->CreateStream(&piStream);
//
//   if (hr != S_OK) return false;
//
//   memory m;
//
//   m.allocate(pfile->get_length());
//
//   pfile->read(m.get_data(), m.get_size());
//
//   hr = piStream->InitializeFromMemory(m.get_data(), m.get_size());
//
//   if (hr != S_OK)
//   {
//
//      return false;
//
//   }
//
//   windows::comptr < IWICBitmapDecoder > piDecoder;
//
//   hr = piFactory->CreateDecoderFromStream(piStream, 0, WICDecodeMetadataCacheOnLoad, &piDecoder); // jpeg,png:OK, bmp:88982f50のエラーになる, iconもエラー
//
//   if (hr != S_OK)
//   {
//
//      return false;
//
//   }
//
//   UINT cFrames = 0;
//
//   hr = piDecoder->GetFrameCount(&cFrames);
//
//   if (hr != S_OK)
//   {
//
//      return false;
//
//   }
//
//   ::windows::comptr < IWICMetadataQueryReader > piMetadataQueryReader;
//
//   // Create a MetadataQueryReader from the decoder
//   hr =piDecoder->GetMetadataQueryReader(&piMetadataQueryReader);
//
//   if (hr != S_OK)
//   {
//
//      return false;
//
//   }
//   PROPVARIANT propValue;
//   PropVariantInit(&propValue);
//
//   // Get global frame size
//   // Get width
//   hr = piMetadataQueryReader->GetMetadataByName(
//                                                 L"/logscrdesc/Width",
//                                                 &propValue);
//
//   if (hr != S_OK)
//   {
//
//      return false;
//
//   }
//
//   hr = (propValue.vt == VT_UI2 ? S_OK : E_FAIL);
//
//   if (hr != S_OK)
//   {
//
//      return false;
//
//   }
//
//   pdiba->m_size.cx = propValue.uiVal;
//   PropVariantClear(&propValue);
//
//   // Get height
//   hr = piMetadataQueryReader->GetMetadataByName(
//                                                 L"/logscrdesc/Height",
//                                                 &propValue);
//   if (hr != S_OK)
//   {
//
//      return false;
//
//   }
//
//   hr = (propValue.vt == VT_UI2 ? S_OK : E_FAIL);
//   if (hr != S_OK)
//   {
//
//      return false;
//
//   }
//   pdiba->m_size.cy = propValue.uiVal;
//   PropVariantClear(&propValue);
   
   
   
//   // Get background color
//   pdiba->m_crBack = metadata_GetBackgroundColor(piMetadataQueryReader, piDecoder, piFactory);
//
//   ::draw2d::dib_sp dibCompose(papp->allocer());
//
//
//   for (index uFrameIndex = 0; uFrameIndex < cFrames; uFrameIndex++)
//   {
//
//      ::visual::dib_sp::pointer * p = canew(::visual::dib_sp::pointer);
//
//      pdiba->add(p);
//
//      p->m_dib.alloc(papp->allocer());
//
//      {
//
//         ::windows::comptr<IWICFormatConverter> pConverter;
//         ::windows::comptr<IWICBitmapFrameDecode> pWicFrame;
//         ::windows::comptr<IWICMetadataQueryReader > pFrameMetadataQueryReader;
//
//         PROPVARIANT propValue;
//         PropVariantInit(&propValue);
//
//         // Retrieve the current frame
//         HRESULT hr = piDecoder->GetFrame(uFrameIndex, &pWicFrame);
//         if (SUCCEEDED(hr))
//         {
//            // Format convert to 32bppPBGRA which D2D expects
//            hr = piFactory->CreateFormatConverter(&pConverter);
//         }
//
//         if (SUCCEEDED(hr))
//         {
//            hr = pConverter->Initialize(
//                                        pWicFrame,
//                                        GUID_WICPixelFormat32bppPBGRA,
//                                        WICBitmapDitherTypeNone,
//                                        nullptr,
//                                        0.f,
//                                        WICBitmapPaletteTypeCustom);
//         }
//
//         if (SUCCEEDED(hr))
//         {
//
//            hr = dib_from_wicbitmapsource(*p->m_dib.m_p, pConverter, piFactory) ? S_OK : E_FAIL;
//
//         }
//
//         if (SUCCEEDED(hr))
//         {
//            // Get Metadata Query Reader from the frame
//            hr = pWicFrame->GetMetadataQueryReader(&pFrameMetadataQueryReader);
//         }
//
//         // Get the Metadata for the current frame
//         if (SUCCEEDED(hr))
//         {
//            hr = pFrameMetadataQueryReader->GetMetadataByName(L"/imgdesc/Left", &propValue);
//            if (SUCCEEDED(hr))
//            {
//               hr = (propValue.vt == VT_UI2 ? S_OK : E_FAIL);
//               if (SUCCEEDED(hr))
//               {
//                  p->m_rect.left = static_cast<float>(propValue.uiVal);
//               }
//               PropVariantClear(&propValue);
//            }
//         }
//
//         if (SUCCEEDED(hr))
//         {
//            hr = pFrameMetadataQueryReader->GetMetadataByName(L"/imgdesc/Top", &propValue);
//            if (SUCCEEDED(hr))
//            {
//               hr = (propValue.vt == VT_UI2 ? S_OK : E_FAIL);
//               if (SUCCEEDED(hr))
//               {
//                  p->m_rect.top = static_cast<float>(propValue.uiVal);
//               }
//               PropVariantClear(&propValue);
//            }
//         }
//
//         if (SUCCEEDED(hr))
//         {
//            hr = pFrameMetadataQueryReader->GetMetadataByName(L"/imgdesc/Width", &propValue);
//            if (SUCCEEDED(hr))
//            {
//               hr = (propValue.vt == VT_UI2 ? S_OK : E_FAIL);
//               if (SUCCEEDED(hr))
//               {
//                  p->m_rect.right = static_cast<float>(propValue.uiVal) + p->m_rect.left;
//               }
//               PropVariantClear(&propValue);
//            }
//         }
//
//         if (SUCCEEDED(hr))
//         {
//            hr = pFrameMetadataQueryReader->GetMetadataByName(L"/imgdesc/Height", &propValue);
//            if (SUCCEEDED(hr))
//            {
//               hr = (propValue.vt == VT_UI2 ? S_OK : E_FAIL);
//               if (SUCCEEDED(hr))
//               {
//                  p->m_rect.bottom = static_cast<float>(propValue.uiVal) + p->m_rect.top;
//               }
//               PropVariantClear(&propValue);
//            }
//         }
//
//         if (SUCCEEDED(hr))
//         {
//            // Get delay from the optional Graphic Control Extension
//            if (SUCCEEDED(pFrameMetadataQueryReader->GetMetadataByName(
//                                                                       L"/grctlext/Delay",
//                                                                       &propValue)))
//            {
//               hr = (propValue.vt == VT_UI2 ? S_OK : E_FAIL);
//               if (SUCCEEDED(hr))
//               {
//                  // Convert the delay retrieved in 10 ms units to a delay in 1 ms units
//                  UINT uiDelay;
//                  hr = UIntMult(propValue.uiVal, 10, &uiDelay);
//                  p->m_dwTime = uiDelay;
//               }
//               PropVariantClear(&propValue);
//            }
//            else
//            {
//               // Failed to get delay from graphic control extension. Possibly a
//               // single frame image (non-animated gif)
//               p->m_dwTime = 0;
//            }
//
//            if (SUCCEEDED(hr))
//            {
//               // Insert an artificial delay to ensure rendering for gif with very small
//               // or 0 delay.  This delay number is picked to match with most browsers'
//               // gif display speed.
//               //
//               // This will defeat the purpose of using zero delay intermediate frames in
//               // order to preserve compatibility. If this is removed, the zero delay
//               // intermediate frames will not be visible.
//               if (p->m_dwTime < 90)
//               {
//                  p->m_dwTime = 90;
//               }
//            }
//         }
//
//         if (SUCCEEDED(hr))
//         {
//            int iDisposal = -1;
//            if (SUCCEEDED(pFrameMetadataQueryReader->GetMetadataByName(
//                                                                       L"/grctlext/Disposal",
//                                                                       &propValue)))
//            {
//               hr = (propValue.vt == VT_UI1) ? S_OK : E_FAIL;
//               if (SUCCEEDED(hr))
//               {
//                  iDisposal = propValue.bVal;
//               }
//            }
//            else
//            {
//               // Failed to get the disposal method, use default. Possibly a
//               // non-animated gif.
//               //iDisposal
//            }
//
//            switch (iDisposal)
//            {
//               case 0:
//                  p->m_edisposal = ::visual::dib_sp::pointer::disposal_undefined;
//                  break;
//               case 1:
//                  p->m_edisposal = ::visual::dib_sp::pointer::disposal_none;
//                  break;
//               case 2:
//                  p->m_edisposal = ::visual::dib_sp::pointer::disposal_background;
//                  break;
//               case 3:
//                  p->m_edisposal = ::visual::dib_sp::pointer::disposal_previous;
//                  break;
//               default:
//                  p->m_edisposal = ::visual::dib_sp::pointer::disposal_undefined;
//                  break;
//            }
//
//         }
//
//         PropVariantClear(&propValue);
//
//      }
//
//      if (uFrameIndex > 0 && pdiba->element_at(uFrameIndex - 1)->m_edisposal == ::visual::dib_sp::pointer::disposal_background)
//      {
//
//         dibCompose->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);
//
//         COLORREF crBack = pdiba->m_crBack;
//
//         byte bAlpha = argb_get_a_value(crBack);
//
//         if (bAlpha == 0)
//         {
//
//            crBack = 0;
//
//         }
//         else
//         {
//
//            output_debug_string("non zero alpha");
//
//         }
//
//         ::rect r = pdiba->element_at(uFrameIndex - 1)->m_rect;
//
//         dibCompose->get_graphics()->FillSolidRect(r, crBack);
//
//      }
//
//      //pdibCompose->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);
//
//      ::point pt = p->m_rect.top_left();
//
//      ::size sz = p->m_rect.size();
//
//      if (uFrameIndex <= 0)
//      {
//
//         dibCompose->create(pdiba->m_size);
//
//      }
//
//      dibCompose->precision_blend(pt, p->m_dib, ::null_point(), sz);
//
//      p->m_dib->from(dibCompose);
//
//      p->m_dib->create_helper_map();
//
//
//      pdiba->m_dwTotal += p->m_dwTime;
//
//   }
   
   
   //return SUCCEEDED(hr);
   
}








//void cra_from_quada(array < COLORREF > & cra, RGBQUAD * pquad, int iCount)
//{
//   
//   cra.set_size(iCount);
//   
//   for (index i = 0; i < iCount; i++)
//   {
//      
//#if defined(ANDROID) && defined(__arm__)
//      cra[i] = ARGB(255, pquad[i].rgbRed, pquad[i].rgbGreen, pquad[i].rgbBlue);
//#else
//      cra[i] = ARGB(255, pquad[i].rgbBlue, pquad[i].rgbGreen, pquad[i].rgbRed);
//#endif
//      
//      if (cra[i] == ARGB(255, 255, 255, 255))
//      {
//         
//         output_debug_string("completely white");
//         
//      }
//      
//   }
//   
//}




bool windows_write_dib_to_file(::file::file_sp, ::draw2d::dib * pdib, ::visual::save_image * psaveimage, ::aura::application * papp);
bool windows_load_dib_from_file(::draw2d::dib * pdib, ::file::file_sp, ::aura::application * papp);




//#ifdef WINDOWS

/******************************************************************
 *                                                                 *
 *  DemoApp::GetBackgroundColor()                                  *
 *                                                                 *
 *  Reads and stores the background color for gif.                 *
 *                                                                 *
 ******************************************************************/


//bool windows_load_dib_from_frame(
//                                 comptr< IWICBitmapFrameDecode> & pframe,
//                                 ::draw2d::dib * pdib,
//                                 IWICImagingFactory * piFactory,
//                                 IWICBitmapDecoder * piDecoder,
//                                 int iFrame)
//{
//
//   try
//   {
//
//      HRESULT hr = piDecoder->GetFrame(iFrame, &pframe.get());
//
//      WICPixelFormatGUID px;
//      ZERO(px);
//      if (pframe == NULL)
//      {
//         return false;
//      }
//      if (FAILED(hr))
//      {
//         return false;
//      }
//
//      hr = pframe->GetPixelFormat(&px);
//      if (FAILED(hr))
//      {
//         return false;
//      }
//
//
//
//      if (px == GUID_WICPixelFormat32bppBGRA)
//      {
//         UINT width = 0;
//         UINT height = 0;
//
//         pframe->GetSize(&width, &height);
//         pdib->create(width, height);
//         pdib->map();
//         hr = pframe->CopyPixels(NULL, pdib->m_iScan, pdib->m_iScan * height, (BYTE *)pdib->m_pcolorref);
//#ifdef METROWIN
//         pdib->mult_alpha();
//#endif
//
//      }
//      else
//      {
//
//         comptr<IWICFormatConverter> pbitmap;
//
//         if (SUCCEEDED(hr))
//         {
//
//            hr = piFactory->CreateFormatConverter(&pbitmap.get());
//
//         }
//
//
//
//         px = GUID_WICPixelFormat32bppBGRA;
//
//         if (SUCCEEDED(hr))
//         {
//
//            hr = pbitmap->Initialize(pframe, px, WICBitmapDitherTypeNone, NULL, 0.f, WICBitmapPaletteTypeCustom);
//         }
//
//         //Step 4: Create render target and D2D bitmap from IWICBitmapSource
//         UINT width = 0;
//         UINT height = 0;
//         if (SUCCEEDED(hr))
//         {
//            hr = pbitmap->GetSize(&width, &height);
//         }
//
//         pdib->create(width, height);
//
//         pdib->map();
//
//         hr = pbitmap->CopyPixels(NULL, pdib->m_iScan, pdib->m_iScan * height, (BYTE *)pdib->m_pcolorref);
//
//
//      }
//
//
//
//   }
//   catch (...)
//   {
//      return false;
//   }
//
//   return true;
//
//}
//
//// rgColors[256]
//HRESULT windows_GetBackgroundColor(WICColor *rgColors, int *piSize, ::visual::dib_sp::array * pdiba,
//
//                                   IWICImagingFactory * piFactory, IWICBitmapDecoder * piDecoder, IWICMetadataQueryReader *pMetadataQueryReader)
//{
//   DWORD dwBGColor;
//   UINT cColorsCopied = 0;
//   PROPVARIANT propVariant;
//   PropVariantInit(&propVariant);
//   comptr <IWICPalette> pWicPalette;
//
//   pdiba->m_backgroundIndex = 0;
//
//   // If we have a global palette, get the palette and background color
//   HRESULT hr = pMetadataQueryReader->GetMetadataByName(
//                                                        L"/logscrdesc/GlobalColorTableFlag",
//                                                        &propVariant);
//   if (SUCCEEDED(hr))
//   {
//      hr = (propVariant.vt != VT_BOOL || !propVariant.boolVal) ? E_FAIL : S_OK;
//      PropVariantClear(&propVariant);
//   }
//
//   if (SUCCEEDED(hr))
//   {
//      // Background color index
//      hr = pMetadataQueryReader->GetMetadataByName(
//                                                   L"/logscrdesc/BackgroundColorIndex",
//                                                   &propVariant);
//      if (SUCCEEDED(hr))
//      {
//         hr = (propVariant.vt != VT_UI1) ? E_FAIL : S_OK;
//         if (SUCCEEDED(hr))
//         {
//            pdiba->m_backgroundIndex = propVariant.bVal;
//         }
//         PropVariantClear(&propVariant);
//      }
//   }
//
//   // Get the color from the palette
//   if (SUCCEEDED(hr))
//   {
//      hr = piFactory->CreatePalette(&pWicPalette.get());
//   }
//
//   if (SUCCEEDED(hr))
//   {
//      // Get the global palette
//      hr = piDecoder->CopyPalette(pWicPalette);
//   }
//
//
//   if (SUCCEEDED(hr))
//   {
//      hr = pWicPalette->GetColors(
//                                  *piSize,
//                                  rgColors,
//                                  &cColorsCopied);
//      *piSize = cColorsCopied;
//   }
//
//   if (SUCCEEDED(hr))
//   {
//      pdiba->m_cra.set_size(cColorsCopied);
//      for (UINT ui = 0; ui < cColorsCopied; ui++)
//      {
//         pdiba->m_cra[ui] = rgColors[ui];
//      }
//      // Check whether background color is outside range
//      hr = (pdiba->m_backgroundIndex >= cColorsCopied) ? E_FAIL : S_OK;
//   }
//
//   if (SUCCEEDED(hr))
//   {
//
//      dwBGColor = pdiba->m_cra[pdiba->m_backgroundIndex];
//
//      pdiba->m_crBack = dwBGColor;
//
//   }
//
//   return hr;
//
//}
//
//
//#define unequal(a, b, n) ((a - n < b && b < a + n) || (b - n < a && a < b + n))
//
//
//HRESULT windows_GetRawFrame(
//                            WICColor *rgColors, int iUsed,
//                            ::draw2d::dib * pdibCompose,
//                            ::visual::dib_sp::array * pdiba,
//                            IWICImagingFactory * piFactory,
//                            IWICBitmapDecoder * piDecoder,
//                            UINT uFrameIndex)
//{
//
//   sp(::visual::dib_sp::pointer) pointer = pdiba->element_at(uFrameIndex);
//
//   comptr < IWICBitmapFrameDecode >    pframe;
//
//   comptr < IWICMetadataQueryReader >  pFrameMetadataQueryReader;
//
//   PROPVARIANT propValue;
//
//   PropVariantInit(&propValue);
//
//   // Retrieve the current frame
//   HRESULT hr = piDecoder->GetFrame(uFrameIndex, &pframe.get());
//
//   comptr < IWICFormatConverter > pbitmap;
//
//   if (SUCCEEDED(hr))
//   {
//
//      hr = piFactory->CreateFormatConverter(&pbitmap.get());
//
//   }
//
//   if (SUCCEEDED(hr))
//   {
//
//      hr = pbitmap->Initialize(
//                               pframe,
//                               GUID_WICPixelFormat8bppIndexed,
//                               WICBitmapDitherTypeNone,
//                               nullptr,
//                               0.f,
//                               WICBitmapPaletteTypeCustom);
//
//   }
//
//   UINT width = 0;
//
//   UINT height = 0;
//
//   if (SUCCEEDED(hr))
//   {
//
//      hr = pbitmap->GetSize(&width, &height);
//
//   }
//
//   pointer->m_dib->create(width, height);
//
//   pointer->m_dib->map();
//
//   byte_array ba;
//
//   ba.allocate((memory_size_t)pointer->m_dib->area());
//
//   hr = pbitmap->CopyPixels(NULL, pointer->m_dib->m_size.cx, (UINT)ba.get_size(), (BYTE *)ba.get_data());
//
//   if (FAILED(hr))
//   {
//
//      return false;
//
//   }
//
//   hr = pframe->GetMetadataQueryReader(&pFrameMetadataQueryReader.get());
//
//   if (SUCCEEDED(hr))
//   {
//
//      hr = pFrameMetadataQueryReader->GetMetadataByName(L"/imgdesc/Left", &propValue);
//
//      if (SUCCEEDED(hr))
//      {
//
//         hr = (propValue.vt == VT_UI2 ? S_OK : E_FAIL);
//
//         if (SUCCEEDED(hr))
//         {
//
//            pointer->m_rect.left = propValue.uiVal;
//
//         }
//
//         PropVariantClear(&propValue);
//
//      }
//
//   }
//
//   if (SUCCEEDED(hr))
//   {
//
//      hr = pFrameMetadataQueryReader->GetMetadataByName(L"/imgdesc/Top", &propValue);
//
//      if (SUCCEEDED(hr))
//      {
//
//         hr = (propValue.vt == VT_UI2 ? S_OK : E_FAIL);
//
//         if (SUCCEEDED(hr))
//         {
//
//            pointer->m_rect.top = propValue.uiVal;
//
//         }
//
//         PropVariantClear(&propValue);
//
//      }
//
//   }
//
//   if (SUCCEEDED(hr))
//   {
//
//      hr = pFrameMetadataQueryReader->GetMetadataByName(L"/imgdesc/Width", &propValue);
//
//      if (SUCCEEDED(hr))
//      {
//
//         hr = (propValue.vt == VT_UI2 ? S_OK : E_FAIL);
//
//         if (SUCCEEDED(hr))
//         {
//
//            pointer->m_rect.right = propValue.uiVal + pointer->m_rect.left;
//
//         }
//
//         PropVariantClear(&propValue);
//
//      }
//
//   }
//
//   if (SUCCEEDED(hr))
//   {
//
//      hr = pFrameMetadataQueryReader->GetMetadataByName(L"/imgdesc/Height", &propValue);
//
//      if (SUCCEEDED(hr))
//      {
//
//         hr = (propValue.vt == VT_UI2 ? S_OK : E_FAIL);
//
//         if (SUCCEEDED(hr))
//         {
//
//            pointer->m_rect.bottom = propValue.uiVal + pointer->m_rect.top;
//
//         }
//
//         PropVariantClear(&propValue);
//
//      }
//
//   }
//
//   if (SUCCEEDED(hr))
//   {
//
//      // Get delay from the optional Graphic Control Extension
//      if (SUCCEEDED(pFrameMetadataQueryReader->GetMetadataByName(
//                                                                 L"/grctlext/Delay",
//                                                                 &propValue)))
//      {
//
//         hr = (propValue.vt == VT_UI2 ? S_OK : E_FAIL);
//
//         if (SUCCEEDED(hr))
//         {
//
//            UINT ui;
//
//            // Convert the delay retrieved in 10 ms units to a delay in 1 ms units
//            hr = UIntMult(propValue.uiVal, 10, &ui);
//
//            pointer->m_dwTime = ui;
//
//         }
//
//         PropVariantClear(&propValue);
//
//      }
//      else
//      {
//
//         // Failed to get delay from graphic control extension. Possibly a
//         // single frame image (non-animated gif)
//         pointer->m_dwTime = 0;
//
//      }
//
//      if (pointer->m_dwTime <= 0)
//      {
//
//         output_debug_string("0 delay");
//
//      }
//
//      if (SUCCEEDED(hr))
//      {
//         // Insert an artificial delay to ensure rendering for gif with very small
//         // or 0 delay.  This delay number is picked to match with most browsers'
//         // gif display speed.
//         //
//         // This will defeat the purpose of using zero delay intermediate frames in
//         // order to preserve compatibility. If this is removed, the zero delay
//         // intermediate frames will not be visible.
//         //if (pointer.m_dwTime < 90)
//         {
//            // pointer.m_dwTime = 90;
//         }
//
//      }
//
//   }
//
//   if (SUCCEEDED(hr))
//   {
//
//      if (SUCCEEDED(pFrameMetadataQueryReader->GetMetadataByName(
//                                                                 L"/grctlext/Disposal",
//                                                                 &propValue)))
//      {
//
//         hr = (propValue.vt == VT_UI1) ? S_OK : E_FAIL;
//
//         if (SUCCEEDED(hr))
//         {
//
//            pointer->m_edisposal = (::visual::dib_sp::pointer::e_disposal) propValue.bVal;
//
//         }
//
//      }
//      else
//      {
//
//         // Failed to get the disposal method, use default. Possibly a
//         // non-animated gif.
//         pointer->m_edisposal = ::visual::dib_sp::pointer::disposal_undefined;
//
//      }
//
//   }
//
//   int transparentIndex = -1;
//
//   hr = S_OK;
//
//   if (SUCCEEDED(hr))
//   {
//
//      hr = pFrameMetadataQueryReader->GetMetadataByName(
//                                                        L"/grctlext/TransparencyFlag",
//                                                        &propValue);
//
//      if (SUCCEEDED(hr))
//      {
//
//         hr = (propValue.vt != VT_BOOL) ? E_FAIL : S_OK;
//
//         if (SUCCEEDED(hr))
//         {
//
//            pointer->m_bTransparent = propValue.boolVal != FALSE;
//
//         }
//
//         PropVariantClear(&propValue);
//
//      }
//
//   }
//
//   if (pointer->m_bTransparent)
//   {
//
//      if (SUCCEEDED(hr))
//      {
//
//         hr = pFrameMetadataQueryReader->GetMetadataByName(
//                                                           L"/grctlext/TransparentColorIndex",
//                                                           &propValue);
//
//         if (SUCCEEDED(hr))
//         {
//
//            hr = (propValue.vt != VT_UI1) ? E_FAIL : S_OK;
//
//            if (SUCCEEDED(hr))
//            {
//
//               transparentIndex = propValue.bVal;
//
//            }
//
//            PropVariantClear(&propValue);
//
//         }
//
//      }
//
//   }
//
//   if (SUCCEEDED(hr) && pointer->m_bTransparent)
//   {
//
//      hr = (transparentIndex >= pdiba->m_cra.get_count()) ? E_FAIL : S_OK;
//
//   }
//
//   if (SUCCEEDED(hr))
//   {
//
//      pointer->m_crTransparent = pdiba->m_cra[transparentIndex];
//
//   }
//   else
//   {
//
//      pointer->m_crTransparent = ARGB(255, 255, 255, 255);
//
//   }
//
//   array < COLORREF > cra;
//
//   cra_from_quada(cra, (RGBQUAD *) rgColors, iUsed);
//
//   if (uFrameIndex == 0)
//   {
//
//      if (transparentIndex >= 0)
//      {
//
//         pdibCompose->Fill(0);
//
//      }
//      else
//      {
//
//         pdibCompose->Fill(pdiba->m_crBack);
//
//
//      }
//
//   }
//
//   if (!gif_load_frame(pdibCompose, pdiba, pointer, uFrameIndex, (byte *)ba.get_data(), width, cra, transparentIndex))
//   {
//
//      return false;
//
//   }
//
//   return true;


//}


bool windows_load_diba_from_file(::visual::dib_sp::array * pdiba, ::file::file_sp pfile, ::aura::application * papp)
{
   
   throw new todo(papp);
//   if (!defer_co_initialize_ex(false))
  //    return false;
   
   
   
//   file_size_t iSize = pfile->get_length();
//   
//   memory mem(papp);
//   
//   mem.allocate((memory_size_t)iSize);
//   
//   pfile->read(mem.get_data(), (memory_size_t)iSize);
   
//   try
//   {
//      
//      comptr<IStream> pstream = mem.CreateIStream();
//      
//      comptr < IWICImagingFactory > piFactory = NULL;
//      
//      comptr< IWICBitmapDecoder > decoder;
//      
//      comptr<IWICMetadataQueryReader> pMetadataQueryReader;
//      
//      HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory,
//                                    (LPVOID*)&piFactory);
//      
//      if (FAILED(hr))
//      {
//         
//         return false;
//         
//      }
//      
//      hr = piFactory->CreateDecoderFromStream(pstream, NULL, WICDecodeMetadataCacheOnDemand, &decoder.get());
//      
//      if (FAILED(hr))
//      {
//         
//         return false;
//         
//      }
//      
//      PROPVARIANT propValue;
//      
//      PropVariantInit(&propValue);
//      
//      
//      UINT cFrames;
//      
//      // Get the frame count
//      hr = decoder->GetFrameCount(&cFrames);
//      if (FAILED(hr))
//      {
//         
//         return false;
//         
//      }
//      
//      // Create a MetadataQueryReader from the decoder
//      hr = decoder->GetMetadataQueryReader(&pMetadataQueryReader.get());
//      
//      
//      if (FAILED(hr))
//      {
//         
//         return false;
//         
//      }
//      WICColor rgColors[256];
//      
//      int iUsed = 256;
//      
//      // Get background color
//      if (FAILED(windows_GetBackgroundColor(rgColors, &iUsed, pdiba, piFactory, decoder, pMetadataQueryReader)))
//      {
//         // Default to transparent if failed to get the color
//         pdiba->m_crBack = 0;
//         
//      }
//      
//      // Get global frame size
//      // Get width
//      hr = pMetadataQueryReader->GetMetadataByName(
//                                                   L"/logscrdesc/Width",
//                                                   &propValue);
//      if (SUCCEEDED(hr))
//      {
//         hr = (propValue.vt == VT_UI2 ? S_OK : E_FAIL);
//         if (SUCCEEDED(hr))
//         {
//            pdiba->m_sizeLogical.cx = propValue.uiVal;
//         }
//         PropVariantClear(&propValue);
//      }
//      
//      // Get height
//      hr = pMetadataQueryReader->GetMetadataByName(
//                                                   L"/logscrdesc/Height",
//                                                   &propValue);
//      if (SUCCEEDED(hr))
//      {
//         hr = (propValue.vt == VT_UI2 ? S_OK : E_FAIL);
//         if (SUCCEEDED(hr))
//         {
//            pdiba->m_sizeLogical.cy = propValue.uiVal;
//         }
//         PropVariantClear(&propValue);
//      }
//      
//      // Get pixel aspect ratio
//      hr = pMetadataQueryReader->GetMetadataByName(
//                                                   L"/logscrdesc/PixelAspectRatio",
//                                                   &propValue);
//      if (SUCCEEDED(hr))
//      {
//         hr = (propValue.vt == VT_UI1 ? S_OK : E_FAIL);
//         if (SUCCEEDED(hr))
//         {
//            UINT uPixelAspRatio = propValue.bVal;
//            
//            if (uPixelAspRatio != 0)
//            {
//               // Need to calculate the ratio. The value in uPixelAspRatio
//               // allows specifying widest pixel 4:1 to the tallest pixel of
//               // 1:4 in increments of 1/64th
//               float pixelAspRatio = (uPixelAspRatio + 15.f) / 64.f;
//               
//               // Calculate the image width and height in pixel based on the
//               // pixel aspect ratio. Only shrink the image.
//               if (pixelAspRatio > 1.f)
//               {
//                  pdiba->m_size.cx = pdiba->m_sizeLogical.cx;
//                  pdiba->m_size.cy = static_cast<unsigned int>(pdiba->m_sizeLogical.cy / pixelAspRatio);
//               }
//               else
//               {
//                  pdiba->m_size.cx = static_cast<unsigned int>(pdiba->m_sizeLogical.cx * pixelAspRatio);
//                  pdiba->m_size.cy = pdiba->m_sizeLogical.cy;
//               }
//            }
//            else
//            {
//               // The value is 0, so its ratio is 1
//               pdiba->m_size = pdiba->m_sizeLogical;
//            }
//         }
//         PropVariantClear(&propValue);
//         
//         // Get looping information
//         if (SUCCEEDED(hr))
//         {
//            // First check to see if the application block in the Application Extension
//            // contains "NETSCAPE2.0" and "ANIMEXTS1.0", which indicates the gif animation
//            // has looping information associated with it.
//            //
//            // If we fail to get the looping information, loop the animation infinitely.
//            if (SUCCEEDED(pMetadataQueryReader->GetMetadataByName(
//                                                                  L"/appext/application",
//                                                                  &propValue)) &&
//                propValue.vt == (VT_UI1 | VT_VECTOR) &&
//                propValue.caub.cElems == 11 &&  // Length of the application block
//                (!memcmp(propValue.caub.pElems, "NETSCAPE2.0", propValue.caub.cElems) ||
//                 !memcmp(propValue.caub.pElems, "ANIMEXTS1.0", propValue.caub.cElems)))
//            {
//               PropVariantClear(&propValue);
//               
//               hr = pMetadataQueryReader->GetMetadataByName(L"/appext/data", &propValue);
//               if (SUCCEEDED(hr))
//               {
//                  //  The data is in the following format:
//                  //  byte 0: extsize (must be > 1)
//                  //  byte 1: loopType (1 == animated gif)
//                  //  byte 2: loop count (least significant byte)
//                  //  byte 3: loop count (most significant byte)
//                  //  byte 4: set to zero
//                  if (propValue.vt == (VT_UI1 | VT_VECTOR) &&
//                      propValue.caub.cElems >= 4 &&
//                      propValue.caub.pElems[0] > 0 &&
//                      propValue.caub.pElems[1] == 1)
//                  {
//                     pdiba->m_uiLoopCount = MAKEWORD(propValue.caub.pElems[2],
//                                                     propValue.caub.pElems[3]);
//                     
//                     // If the total loop count is not zero, we then have a loop count
//                     // If it is 0, then we repeat infinitely
//                     //if (pdiba->m_uiLoopCount == 0)
//                     //{
//                     //   pdiba->m_iLoop = -1;
//                     //}
//                  }
//               }
//            }
//         }
//         
//      }
//      
//      
//      
//      PropVariantClear(&propValue);
//      
//      
//      
//      pdiba->set_size(cFrames);
//      
//      pdiba->m_dwTotal = 0;
//      
//      ::draw2d::dib_sp dibCompose(papp->allocer());
//      
//      dibCompose->create(pdiba->m_size);
//      
//      for (UINT ui = 0; ui < cFrames; ui++)
//      {
//         
//         pdiba->element_at(ui) = canew(::visual::dib_sp::pointer());
//         
//         pdiba->element_at(ui)->m_dib.alloc(papp->allocer());
//         
//         windows_GetRawFrame(rgColors, iUsed,dibCompose, pdiba, piFactory, decoder, (UINT)ui);
//         
//         pdiba->m_dwTotal += pdiba->element_at(ui)->m_dwTime;
//         
//      }
//      
//   }
//   catch (...)
//   {
//      
//      return false;
//      
//   }
   
   return true;
}



bool windows_load_dib_from_file(::draw2d::dib * pdib, ::file::file_sp pfile, ::aura::application * papp)
{
   
//   if (!defer_co_initialize_ex(false))
//      return false;
   
   file_size_t iSize = pfile->get_length();
   
   memory mem(papp);
   
   mem.allocate((memory_size_t)iSize);
   
   pfile->read(mem.get_data(), (memory_size_t)iSize);
   
//   try
//   {
//      
//      comptr<IStream> pstream = mem.CreateIStream();
//      comptr < IWICImagingFactory > piFactory = NULL;
//      
//      comptr< IWICBitmapDecoder > decoder;
//      HRESULT hr = CoCreateInstance(
//                                    CLSID_WICImagingFactory,
//                                    NULL,
//                                    CLSCTX_INPROC_SERVER,
//                                    IID_IWICImagingFactory,
//                                    (LPVOID*)&piFactory);
//      
//      if (SUCCEEDED(hr))
//      {
//         
//         hr = piFactory->CreateDecoderFromStream(pstream, NULL, WICDecodeMetadataCacheOnDemand, &decoder.get());
//      }
//      
//      //if(SUCCEEDED(hr))
//      //{
//      
//      //   hr = decoder->Initialize(pstream,WICDecodeMetadataCacheOnDemand);
//      
//      //}
//      
//      comptr< IWICBitmapFrameDecode> pframe;
//      
//      if (!windows_load_dib_from_frame(pframe, pdib, piFactory, decoder, 0))
//      {
//         
//         return false;
//         
//      }
//      
//   }
//   catch (...)
//   {
//      return false;
//   }
   return true;
   
}

#ifdef METROWIN

bool windows_load_dib_from_file(::draw2d::dib * pdib, Windows::Storage::Streams::IRandomAccessStream ^stream, ::aura::application * papp)
{
   
   if (!defer_co_initialize_ex(true))
      return false;
   
   try
   {
      
      comptr < IStream > pstream;
      
      ::CreateStreamOverRandomAccessStream(stream, IID_PPV_ARGS(&pstream.get()));
      
      comptr < IWICImagingFactory > piFactory = NULL;
      
      comptr< IWICBitmapDecoder > decoder;
      HRESULT hr = CoCreateInstance(
                                    CLSID_WICImagingFactory,
                                    NULL,
                                    CLSCTX_INPROC_SERVER,
                                    IID_IWICImagingFactory,
                                    (LPVOID*)&piFactory);
      
      if (SUCCEEDED(hr))
      {
         
         hr = piFactory->CreateDecoderFromStream(pstream, NULL, WICDecodeMetadataCacheOnDemand, &decoder.get());
      }
      
      //if(SUCCEEDED(hr))
      //{
      
      //   hr = decoder->Initialize(pstream,WICDecodeMetadataCacheOnDemand);
      
      //}
      
      comptr< IWICBitmapFrameDecode> pframe;
      
      if (!windows_load_dib_from_frame(pframe, pdib, piFactory, decoder, 0))
      {
         
         return false;
         
      }
      
   }
   catch (...)
   {
      return false;
   }
   //DWORD dw2 =::get_tick_count();
   //TRACE("InPath %d ms\n",dw2 - dw1);
   //dwLast = dw2;
   
   //memfile.Truncate(0);
   
   //}
   return true;
   
}

#endif
