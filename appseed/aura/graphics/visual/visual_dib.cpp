#include "framework.h"

#ifdef WINDOWS
#include <wincodec.h>
#include <ShCore.h>
//#elif defined(METROWIN)
//#include <ShCore.h>
#endif


#include "freeimage/Source/FreeImage.h"

////#include "ft2build.h"


////#include FT_FREETYPE_H



namespace visual
{

   dib_sp::pointer::pointer()
   {

      m_dwTime = 0;

   }

   dib_sp::pointer::~pointer()
   {


   }


   dib_sp::array::array(::aura::application * papp) :
      object(papp)
   {

      m_uiLoop = 0;
      m_uiLoopCount = 0;
      m_bStart = false;
      m_iLastFrame = -1;

   }

   dib_sp::array::~array()
   {

   }




   dib_sp::dib_sp()
   {
      m_eload = load_none;
      m_dSpeed = 1.0;


   }


   dib_sp::dib_sp(const ::aura::allocatorsp & allocer) :
      ::draw2d::dib_sp(allocer)
   {
      m_eload = load_none;
      m_dSpeed = 1.0;


   }


   dib_sp::~dib_sp()
   {
      if (m_sparray.is_set())
      {

         if (m_sparray->pred_find_first([&](auto & i) { return i->m_dib.m_p == m_p; }) >= 0)
         {
            m_p = NULL;
         }

      }
   }

   bool dib_sp::load_thumbnail(var varFile, int w, int h)
   {

#ifdef WINDOWS

      if (!m_p->create(w, h))
      {
         return false;
      }

      if (!m_p->load_thumbnail(varFile))
      {

         return false;

      }


      return true;

#else

      todo(get_app());

      return false;

#endif


   }

   bool dib_sp::load_from_file(var varFile, bool bCache, bool bCreateHelperMaps)
   {

      if (varFile.is_empty())
      {

         m_eload = load_fail;

         return false;

      }

      if (varFile.get_file_path().extension().compare_ci("svg") == 0
            || varFile.get_file_path().find_ci(".svg?") > 0)
      {

         m_p->create_nanosvg(App(m_p->m_pauraapp).file().as_string(varFile));

         m_eload = load_ok;

         if (bCreateHelperMaps)
         {

            m_p->create_helper_map();

         }

         return true;

      }

      if (varFile.get_file_path().extension().compare_ci("gif") == 0
            || varFile.get_file_path().find_ci(".gif?") > 0)
      {

         m_sparray = canew(array(m_p->m_pauraapp));

         if (!Sys(m_p->m_pauraapp).visual().imaging().load_from_file(m_sparray, varFile, bCache))
         {

            m_sparray.release();

            m_eload = load_fail;

            return false;

         }

         if (!m_p->create(m_sparray->m_size))
         {

            m_sparray.release();

            m_eload = load_fail;

            return false;

         }

         if (bCreateHelperMaps)
         {

            for (auto & p : *m_sparray)
            {

               p->m_dib->create_helper_map();

            }

         }


         m_eload = load_ok;

         return true;

      }

      if (!Sys(m_p->m_pauraapp).visual().imaging().load_from_file(m_p, varFile, bCache))
      {

         m_eload = load_fail;

         return false;

      }

      if (bCreateHelperMaps)
      {

         m_p->create_helper_map();

      }

      m_eload = load_ok;

      return true;

   }


   bool dib_sp::load_from_matter(const char * pszMatter, bool bCache, bool bCreateHelperMaps)
   {

      ::file::path path = m_p->m_pauraapp->dir().matter(pszMatter);

      if (!Sys(m_p->m_pauraapp).visual().imaging().load_from_file(m_p, path, bCache))
      {

         m_eload = load_fail;

         return false;

      }

      if (bCreateHelperMaps)
      {

         m_p->create_helper_map();

      }

      m_eload = load_ok;

      return true;

   }


   bool dib_sp::read_from_file(::file::file_sp spfile)
   {

      if (!Sys(m_p->m_pauraapp).visual().imaging().LoadImageFromFile(m_p, spfile))
      {

         m_eload = load_fail;

         return false;

      }

      m_eload = load_ok;

      return true;

   }


   bool dib_sp::save_to_file(var varFile, save_image * psaveimage)
   {
      ::file::file_sp spfile;
      spfile = Sess(m_p->m_pauraapp).file().get_file(varFile, ::file::mode_create | ::file::share_deny_write | ::file::mode_write | ::file::type_binary | ::file::defer_create_directory);
      if (spfile.is_null())
         return false;
      return write_to_file(spfile, psaveimage);
   }




   save_image::save_image()
   {
      m_eformat = ::visual::image::format_png;
      m_iQuality = 100;
   }


#ifndef  WINDOWS

   bool dib_sp::from(class draw2d::graphics * pgraphics, struct FIBITMAP * pfi, bool bUnload)
   {

      return Sys(m_p->m_pauraapp).visual().imaging().from(m_p, pgraphics, pfi, bUnload);

   }

#endif

   /*::size dib_sp::size()
   {

      if (m_sparray.is_set() && m_sparray->get_count() > 0 && m_sparray->m_dwTotal > 0)
      {

         return m_sparray->m_size;

      }

      return m_p->size();

   }*/

   void dib_sp::defer_update()
   {
      if (m_sparray.is_set() && m_sparray->get_count() > 0 && m_sparray->m_dwTotal > 0)
      {

         //if (!m_p->create(m_sparray->m_size))
         //{

         // return false;

         //}
         if (!m_sparray->m_bStart)
         {
            m_sparray->m_bStart = true;

            m_sparray->m_dwStart = get_tick_count();
         }

         DWORD dwTime = (DWORD) (((double)(get_tick_count()) - m_sparray->m_dwStart)  * m_dSpeed);

         UINT uiLoop = dwTime / m_sparray->m_dwTotal;

         if (uiLoop > m_sparray->m_uiLoop)
         {

            m_sparray->m_uiLoop = uiLoop;

            m_sparray->m_iLastFrame = -1;

         }

         index iCurrentFrame = 0;

         if (m_sparray->m_uiLoopCount == 0 || m_sparray->m_uiLoop < m_sparray->m_uiLoopCount)
         {

            dwTime %= m_sparray->m_dwTotal;

            DWORD dwT = 0;

            for (index i = 0; i < m_sparray->get_count(); i++)
            {

               dwT += m_sparray->element_at(i)->m_dwTime;

               if (dwTime < dwT)
               {

                  iCurrentFrame = i;

                  break;

               }

            }

         }

         /*    for (index iFrame = m_sparray->m_iLastFrame + 1; iFrame <= iCurrentFrame; iFrame++)
             {

                if (m_sparray->element_at(iFrame).m_dwTime <= 0)
                {
                   output_debug_string("0 delay frame");
                }
                else
                {

                   dispose_current_frame();
                   overlay_frame(iFrame);
                }

                m_sparray->m_iLastFrame = iFrame;

             }


         */

         if (m_sparray->m_iLastFrame != iCurrentFrame)
         {

            m_sparray->m_iLastFrame = iCurrentFrame;

            m_p = m_sparray->element_at(iCurrentFrame)->m_dib.m_p;

         }

      }

   }

   bool dib_sp::pointer::to(::draw2d::graphics * pgraphics)
   {


      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      if (!m_dib->to(pgraphics, m_rect.top_left(), m_rect.size()))
      {

         return false;

      }

      return true;

   }

   bool dib_sp::dispose_current_frame()
   {

      if (m_sparray->m_dibCompose.is_null())
      {

         m_sparray->m_dibCompose.alloc(m_p->allocer());

      }

      m_sparray->m_dibCompose->create(m_sparray->m_size);

      if (m_sparray->m_iLastFrame < 0)
      {

         // Draw background and increase loop count
         m_sparray->m_dibCompose->Fill(m_sparray->m_crBack);

         return false;

      }

      //bool bOk = true;


      switch (m_sparray->element_at(m_sparray->m_iLastFrame)->m_edisposal)
      {
      case dib_sp::pointer::disposal_undefined:
      case dib_sp::pointer::disposal_none:
         // We simply draw on the previous frames. Do nothing here.
         break;
      case dib_sp::pointer::disposal_background:
      {
         // Dispose background
         // Clear the area covered by the current raw frame with background color
         m_sparray->m_dibCompose->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);
         COLORREF crBack = m_sparray->m_crBack;
         //byte bAlpha = argb_get_a_value(crBack);

         m_sparray->m_dibCompose->get_graphics()->FillSolidRect(m_sparray->element_at(m_sparray->m_iLastFrame)->m_rect, crBack);
      }
      break;
      case dib_sp::pointer::disposal_previous:
         // Dispose previous
         // We restore the previous composed frame first
         //hr = RestoreSavedFrame();
         break;
      default:
         // Invalid disposal method
         return false;
      }

      return true;
   }

   bool dib_sp::overlay_frame(int iFrame)
   {

      //// If starting a new animation loop
      //if (iFrame <= 0)
      //{

      //}

      // Produce the next frame
      if (!m_sparray->element_at(iFrame)->to(m_sparray->m_dibCompose->get_graphics()))
      {

         return false;

      }

      m_p->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

      m_p->get_graphics()->BitBlt(0, 0, m_p->m_size.cx, m_p->m_size.cy,
                                  m_sparray->m_dibCompose->get_graphics());




      return true;

   }


} // namespace visual


#if 0


CLASS_DECL_AURA void draw_freetype_bitmap(::draw2d::dib * m_p, int32_t dx, int32_t dy, void * pftbitmap, int xParam, int yParam)
{

   FT_Bitmap * bitmap = (FT_Bitmap *)pftbitmap;
   FT_Int x = (FT_Int)xParam;
   FT_Int y = (FT_Int)yParam;

   FT_Int  i, j, p, q;
   FT_Int  x_max = x + bitmap->width;
   FT_Int  y_max = y + bitmap->rows;

   m_p->map();

   for (i = x, p = 0; i < x_max; i++, p++)
   {
      for (j = y, q = 0; j < y_max; j++, q++)
      {
         if (i < 0 || j < 0 || i >= m_p->m_size.cx || j >= m_p->m_size.cy)
            continue;

         int32_t a = bitmap->buffer[q * bitmap->width + p];

         *((COLORREF *)&((byte *)m_p->get_data())[(dy + j) * m_p->m_iScan + (dx + i) * 4]) = ARGB(a, 0, 0, 0);

      }
   }

}


CLASS_DECL_AURA void draw_freetype_bitmap(::draw2d::dib * m_p, int32_t dx, int32_t dy, void * pftbitmap, int xParam, int yParam, byte aParam, byte r, byte g, byte b)
{

   FT_Bitmap * bitmap = (FT_Bitmap *)pftbitmap;
   FT_Int x = (FT_Int)xParam;
   FT_Int y = (FT_Int)yParam;

   FT_Int  i, j, p, q;
   FT_Int  x_max = x + bitmap->width;
   FT_Int  y_max = y + bitmap->rows;

   m_p->map();

   for (i = x, p = 0; i < x_max; i++, p++)
   {
      for (j = y, q = 0; j < y_max; j++, q++)
      {
         if (i < 0 || j < 0 || i >= m_p->m_size.cx || j >= m_p->m_size.cy)
            continue;

         int32_t a = bitmap->buffer[q * bitmap->width + p];

         if (a > 0)
         {

            *((COLORREF *)&((byte *)m_p->get_data())[(dy + j) * m_p->m_iScan + (dx + i) * 4]) = ARGB(a * aParam / 255, r, g, b);

         }
         else
         {

            *((COLORREF *)&((byte *)m_p->get_data())[(dy + j) * m_p->m_iScan + (dx + i) * 4]) = 0;

         }

      }
   }

}

#endif




bool windows_write_dib_to_file(::file::file_sp pfile, ::draw2d::dib * pdib, ::visual::save_image * psaveimage, ::aura::application * papp)
{

#ifdef METROWIN

   Windows::Storage::Streams::InMemoryRandomAccessStream ^ randomAccessStream = ref new Windows::Storage::Streams::InMemoryRandomAccessStream();

   //::wait(randomAccessStream->WriteAsync(get_os_buffer()));

   comptr < IStream > pstream;

   ::CreateStreamOverRandomAccessStream(randomAccessStream, IID_PPV_ARGS(&pstream.get()));

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
      hr = piFactory->CreateStream(&piStream.get());
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
         hr = piFactory->CreateEncoder(GUID_ContainerFormatBmp, NULL, &piEncoder.get());
         break;
      case ::visual::image::format_gif:
         hr = piFactory->CreateEncoder(GUID_ContainerFormatGif, NULL, &piEncoder.get());
         break;
      case ::visual::image::format_jpeg:
         hr = piFactory->CreateEncoder(GUID_ContainerFormatJpeg, NULL, &piEncoder.get());
         break;
      case ::visual::image::format_png:
         hr = piFactory->CreateEncoder(GUID_ContainerFormatPng, NULL, &piEncoder.get());
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
      hr = piEncoder->CreateNewFrame(&piBitmapFrame.get(), &pPropertybag.get());
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
                    &pbitmap.get()
                 );
         }

         comptr<IWICFormatConverter> pconverter;

         if (SUCCEEDED(hr))
         {

            hr = piFactory->CreateFormatConverter(&pconverter.get());

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

      pstream->Read(mem.get_data(), (ULONG) MIN(ul, mem.get_size()), &ulRead);

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


