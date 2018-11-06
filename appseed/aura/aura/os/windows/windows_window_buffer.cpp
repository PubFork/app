#include "framework.h"
#include "aura/user/user/user.h"
#include "windows_window_buffer.h"
#include <stdio.h>


#undef REDRAW_HINTING

namespace windows
{


   void window_buffer::on_create_window(::user::interaction_impl * pimpl)
   {

      window_graphics::on_create_window(pimpl);

      //create_window_graphics_(0, 0);

   }


   window_buffer::window_buffer(::aura::application * papp) :
      object(papp),
      window_graphics(papp),
      ::window_buffer(papp)
   {

      m_hbitmap = NULL;
      m_pcolorref = NULL;
      m_hdc = NULL;
      m_hwnd = NULL;


   }


   window_buffer::~window_buffer()
   {

   }


   void window_buffer::create_window_graphics_(int64_t cxParam, int64_t cyParam, int iStrideParam)
   {

      synch_lock sl(m_pmutex);

      destroy_window_graphics_();

      if (m_pimpl == NULL)
      {

         return;

      }

      HWND hwnd = (HWND)m_pimpl->get_os_data();

      if (hwnd == NULL)
      {

         return;

      }

      m_hwnd = hwnd;

      defer_prepare_ipc_copy_();

      int iStride = (int)(cxParam * 4);

      m_hdcScreen = ::GetDCEx(hwnd, NULL, DCX_WINDOW);

      if (m_hdcScreen == NULL)
      {

         // If it has failed to get interaction_impl
         // owned device context, try to get
         // a device context from the cache.
         //m_hdcScreen = ::GetDCEx(interaction_impl,NULL,DCX_CACHE | DCX_CLIPSIBLINGS | DCX_WINDOW);
         m_hdcScreen = ::GetDCEx(hwnd, NULL, DCX_CACHE | DCX_WINDOW);

         // If no device context could be retrieved,
         // nothing can be drawn at the screen.
         // The function failed.
         if (m_hdcScreen == NULL)
            return;

         m_bOwnDC = false;

      }
      else
      {

         m_bOwnDC = true;

      }

      window_graphics::create_window_graphics_(cxParam, cyParam, iStride);

   }


   void window_buffer::destroy_window_graphics_()
   {

      synch_lock sl(m_pmutex);

      if (m_hdcScreen != NULL)
      {

         ::ReleaseDC(m_pimpl->m_oswindow, m_hdcScreen);

         m_hdcScreen = NULL;

      }


      window_graphics::destroy_window_graphics_();

   }




   void window_buffer::create_buffer(int64_t cxParam, int64_t cyParam, int iStrideParam)
   {

      synch_lock sl(m_pmutex);

      destroy_buffer();

      if (m_pimpl == NULL)
      {

         return;

      }


      BITMAPINFO bitmapinfo;

      ZERO(bitmapinfo);

      int iStride = (int)(cxParam * 4);

      m_iScan = iStride;

      bitmapinfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
      bitmapinfo.bmiHeader.biWidth = (LONG)cxParam;
      bitmapinfo.bmiHeader.biHeight = (LONG)-cyParam;
      bitmapinfo.bmiHeader.biPlanes = 1;
      bitmapinfo.bmiHeader.biBitCount = 32;
      bitmapinfo.bmiHeader.biCompression = BI_RGB;
      bitmapinfo.bmiHeader.biSizeImage = (LONG)(cxParam * cyParam * 4);

      m_cx = (int) cxParam;

      m_cy = (int) cyParam;

      m_hbitmap = CreateDIBSection(NULL, &bitmapinfo, DIB_RGB_COLORS, (void **)&m_pcolorref, NULL, 0);

      m_hdc = ::CreateCompatibleDC(NULL);

      m_hbitmapOld = (HBITMAP) ::SelectObject(m_hdc, m_hbitmap);


      window_graphics::create_buffer(cxParam, cyParam, iStride);

   }


   void window_buffer::destroy_buffer()
   {

      synch_lock sl(m_pmutex);

      if (m_hdc != NULL)
      {

         ::SelectObject(m_hdc, m_hbitmapOld);

         ::DeleteDC(m_hdc);

         m_hdc = NULL;

         m_hbitmapOld = NULL;

      }

      if (m_hbitmap != NULL)
      {

         ::DeleteObject(m_hbitmap);

         m_hbitmap = NULL;

         m_pcolorref = NULL;

      }

      window_graphics::destroy_buffer();

   }




   void window_buffer::update_window(::draw2d::dib * pdib)
   {

      single_lock sl(m_pmutex);

      if (pdib == NULL || pdib->area() <= 0)
      {

         return;

      }

      int cx = MIN(pdib->m_size.cx, m_cx);

      int cy = MIN(pdib->m_size.cy, m_cy);

      rect rectWindow = m_pimpl->m_rectParentClient;

      rectWindow.right = rectWindow.left + cx;

      rectWindow.bottom = rectWindow.top + cy;

      sl.lock();

      bool bLayered = (::GetWindowLong(m_pimpl->m_oswindow, GWL_EXSTYLE) & WS_EX_LAYERED) != 0;

      sl.unlock();

      if (!m_bDibIsHostingBuffer)
      {
         try
         {

            ::draw2d::copy_colorref(cx, cy, m_pcolorref, m_iScan, pdib->get_data(), pdib->m_iScan);

         }
         catch (...)
         {

         }
      }

      bool bAsync = false;

      bool bWasVisible = false;

      if (m_pimpl != NULL && m_pimpl->m_pui != NULL)
      {

         bWasVisible = m_pimpl->m_pui->GetStyle() & WS_VISIBLE;

         if (m_rectLast != rectWindow || m_pimpl->m_bZ || m_pimpl->m_bShowFlags || m_pimpl->m_bShowWindow)
            //if (m_rectLast != rectWindow || m_pimpl->m_bZ)
         {

            m_pimpl->m_bOkToUpdateScreen = false;

            m_pimpl->m_pui->post_pred([=]()
            {

               try
               {

                  keep < bool > keepLockWindowUpdate(&m_pimpl->m_pui->m_bLockWindowUpdate, true, false, true);

                  keep < bool > keepIgnoreSizeEvent(&m_pimpl->m_bIgnoreSizeEvent, true, false, true);

                  keep < bool > keepIgnoreMoveEvent(&m_pimpl->m_bIgnoreMoveEvent, true, false, true);

                  keep < bool > keepDisableSaveWindowRect(&m_pimpl->m_pui->m_bEnableSaveWindowRect, false, m_pimpl->m_pui->m_bEnableSaveWindowRect, true);


                  synch_lock sl(m_pimpl->m_pui->m_pmutex);

                  UINT uiFlags;

                  if (bLayered)
                  {

                     uiFlags = SWP_NOREDRAW
                               | SWP_NOCOPYBITS
                               | SWP_NOACTIVATE
                               | SWP_NOOWNERZORDER
                               | SWP_DEFERERASE;

                  }
                  else
                  {

                     //         uiFlags = SWP_FRAMECHANGED | SWP_NOREDRAW;

                     uiFlags = SWP_NOREDRAW
                               | SWP_NOCOPYBITS
                               | SWP_NOACTIVATE
                               | SWP_NOOWNERZORDER
                               | SWP_DEFERERASE;


                  }

                  ::SetWindowPos(m_pimpl->m_oswindow, (m_pimpl->m_bZ ? (HWND)m_pimpl->m_iZ : 0),
                                 rectWindow.left,
                                 rectWindow.top,
                                 rectWindow.width(),
                                 rectWindow.height(),
                                 (m_pimpl->m_bZ ? 0 : SWP_NOZORDER)
                                 | (m_pimpl->m_bShowFlags ? m_pimpl->m_iShowFlags : 0)
                                 | uiFlags);


                  if (bLayered && !m_pimpl->m_bShowWindow)
                  {

                     if (m_pimpl->m_iShowFlags & SWP_SHOWWINDOW)
                     {

                        ::ShowWindow(m_pimpl->m_oswindow, SW_NORMAL);

                        if (bLayered)
                        {

                           m_pimpl->m_pui->ModifyStyle(0, WS_VISIBLE);

                        }

                     }
                     else if (m_pimpl->m_iShowFlags & SWP_HIDEWINDOW)
                     {

                        ::ShowWindow(m_pimpl->m_oswindow, SW_HIDE);

                        if (bLayered)
                        {

                           m_pimpl->m_pui->ModifyStyle(WS_VISIBLE, 0);

                        }

                     }

                  }

                  m_rectLast = rectWindow;

                  m_pimpl->m_bZ = false;

                  m_pimpl->m_bShowFlags = false;

                  m_pimpl->m_bOkToUpdateScreen = true;


                  if (m_pimpl->m_bShowWindow)
                  {

                     ::ShowWindow(m_pimpl->m_oswindow, m_pimpl->m_iShowWindow);

                     if (bLayered && m_pimpl->m_pui != NULL)
                     {

                        try
                        {

                           if (m_pimpl->m_iShowWindow == SW_HIDE && bWasVisible)
                           {

                              m_pimpl->m_pui->ModifyStyle(WS_VISIBLE, 0);

                              m_pimpl->m_pui->send_message(WM_SHOWWINDOW, 0);

                           }
                           else if (m_pimpl->m_iShowWindow != SW_HIDE && !bWasVisible)
                           {

                              m_pimpl->m_pui->ModifyStyle(0, WS_VISIBLE);

                              m_pimpl->m_pui->send_message(WM_SHOWWINDOW, 1);

                           }

                        }
                        catch (...)
                        {


                        }


                        m_pimpl->m_bShowWindow = false;

                        m_pimpl->m_iShowWindow = -1;

                     }

                  }

               }
               catch (...)
               {

               }

               m_pimpl->m_bOkToUpdateScreen = true;

               m_pimpl->m_pui->set_need_redraw();


            });

         }

      }

      if (bAsync)
      {

         return;

      }

      update_window_2(pdib, bLayered, false);

      oswindow oswindowFocus = NULL;

      oswindow oswindowImpl = NULL;

      ::user::interaction_impl * pimplFocus = NULL;

      if (m_pimpl != NULL
            && m_pimpl->m_pui != NULL
            && m_pimpl->m_pui->IsWindowVisible())
      {

         if (Sess(m_pimpl->get_app()).m_pimplPendingSetFocus == m_pimpl)
         {

            Sess(m_pimpl->get_app()).m_pimplPendingSetFocus = NULL;

            oswindowFocus = ::get_focus();

            oswindowImpl = m_pimpl->m_oswindow;

            pimplFocus = oswindow_get(oswindowFocus);

            if (oswindowFocus == oswindowImpl)
            {

               output_debug_string("optimized out a SetFocus");

            }
            else
            {

               m_pimpl->m_pui->post_pred([this]()
               {

                  ::SetFocus(m_pimpl->m_oswindow);

               });

            }

         }

      }


   }


   void window_buffer::update_window_2(::draw2d::dib * pdib, bool bLayered, bool bSetWindowPos)
   {

      single_lock sl(m_pmutex);

      if (pdib == NULL || pdib->area() <= 0)
      {

         return;

      }

      try
      {

         create_window_graphics_(m_cx, m_cy);


         int cx = MIN(pdib->m_size.cx, m_cx);

         int cy = MIN(pdib->m_size.cy, m_cy);

         rect rectWindow = m_pimpl->m_rectParentClient;

         rectWindow.right = rectWindow.left + cx;

         rectWindow.bottom = rectWindow.top + cy;

         //sl.lock();

         //bool bLayered = (::GetWindowLong(m_pimpl->m_oswindow, GWL_EXSTYLE) & WS_EX_LAYERED) != 0;

         //sl.unlock();

         if (!m_bDibIsHostingBuffer)
         {
            try
            {

               ::draw2d::copy_colorref(cx, cy, m_pcolorref, m_iScan, pdib->get_data(), pdib->m_iScan);

            }
            catch (...)
            {

            }
         }

         if (bLayered
               && m_pimpl != NULL
               && m_pimpl->m_pui != NULL
               && m_pimpl->m_pui->IsWindowVisible())
         {

            if (!m_pimpl->m_bOkToUpdateScreen)
            {

               output_debug_string("nok yet to update the screen \n");

               m_pimpl->m_pui->set_need_redraw();

            }
            else
            {

               POINT pt;

               pt.x = rectWindow.left;

               pt.y = rectWindow.top;

               SIZE sz;

               sz.cx = width(&rectWindow);

               sz.cy = height(&rectWindow);

               POINT ptSrc = { 0 };

               BLENDFUNCTION blendPixelFunction = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };

               //::SelectClipRgn(m_hdcScreen, NULL);

               sl.lock();

#ifdef REDRAW_HINTING

               {
                  //HBRUSH h = ::CreateSolidBrush(RGB(255, 240, 155));

                  //rect r;

                  //r.left = 10;
                  //r.right = 20;
                  //r.top = 0;
                  //r.bottom = sz.cy;

                  //::FillRect(m_hdc, &r, h);

                  //::DeleteObject(h);

                  Gdiplus::Graphics g(m_hdc);

                  Gdiplus::Rect r;

                  r.X = 10;
                  r.Width = 10;
                  r.Y = 0;
                  r.Height = sz.cy;

                  Gdiplus::SolidBrush b(Gdiplus::Color(ARGB(255, 155, 240, 255)));

                  g.FillRectangle(&b, r);

               }

#endif

               SelectClipRgn(m_hdcScreen, NULL);

               SelectClipRgn(m_hdc, NULL);

               SetViewportOrgEx(m_hdcScreen, 0, 0, NULL);

               SetViewportOrgEx(m_hdc, 0, 0, NULL);

#ifdef REDRAW_HINTING

               {

                  //HBRUSH h = ::CreateSolidBrush(RGB(180, 200, 255));

                  //rect r;

                  //r.left = 20;
                  //r.right = 30;
                  //r.top = 0;
                  //r.bottom = sz.cy;

                  //::FillRect(m_hdc, &r, h);

                  //::DeleteObject(h);
                  Gdiplus::Graphics g(m_hdc);

                  Gdiplus::Rect r;

                  r.X = 20;
                  r.Width = 10;
                  r.Y = 0;
                  r.Height = sz.cy;

                  Gdiplus::SolidBrush b(Gdiplus::Color(ARGB(255, 255, 210, 170)));

                  g.FillRectangle(&b, r);
               }

#endif

#ifdef DEBUG

               {

                  //HBRUSH h = ::CreateSolidBrush(RGB(180, 200, 255));

                  //rect r;

                  //r.left = 20;
                  //r.right = 30;
                  //r.top = 0;
                  //r.bottom = sz.cy;

                  //::FillRect(m_hdc, &r, h);

                  //::DeleteObject(h);
                  Gdiplus::Graphics g(m_hdc);

                  Gdiplus::Rect r;

                  r.X = 0;
                  r.Y = 0;

                  r.Width = 10;
                  r.Height = 10;

                  Gdiplus::SolidBrush b(Gdiplus::Color(ARGB(128, 255, 180, 170)));

                  g.FillRectangle(&b, r);
               }

#endif

               bool bOk = ::UpdateLayeredWindow(m_pimpl->m_oswindow, m_hdcScreen, &pt, &sz, m_hdc, &ptSrc, RGB(0, 0, 0), &blendPixelFunction, ULW_ALPHA) != FALSE;

#ifdef DEBUG
               HBITMAP b1 = (HBITMAP) ::GetCurrentObject(m_hdc, OBJ_BITMAP);

               if (b1 != m_hbitmap)
               {

                  output_debug_string("damn0");

               }

               BITMAP bmp1;

               ::GetObject(b1, sizeof(BITMAP), &bmp1);

               if (bmp1.bmHeight != sz.cy)
               {

                  output_debug_string("damn1");
               }


               //HBITMAP b2 = (HBITMAP) ::GetCurrentObject(m_hdcScreen, OBJ_BITMAP);

               //BITMAP bmp2;

               //::GetObject(b2, sizeof(BITMAP), &bmp2);

               //if (bmp2.bmHeight != sz.cy)
               //{

               //   output_debug_string("damn2");
               //}

               {

                  rect rClipScreen;

                  int iResult = ::GetClipBox(m_hdcScreen, rClipScreen);

                  if (iResult == ERROR || iResult == NULLREGION)
                  {
                  }
                  else
                  {

                     if (rClipScreen.height() != sz.cy)
                     {

                        output_debug_string("damn2");

                     }

                  }

               }

               {

                  rect rClip;

                  int iResult = ::GetClipBox(m_hdc, rClip);

                  if (iResult == ERROR || iResult == NULLREGION)
                  {
                  }
                  else
                  {

                     if (rClip.height() != sz.cy)
                     {

                        output_debug_string("damn3");

                     }

                  }

               }

               if (!bOk)
               {

                  output_debug_string("UpdateLayeredWindow failed");

               }

#endif

               sl.unlock();

            }

         }
         else
         {

            ::BitBlt(m_hdcScreen, 0, 0, m_cx, m_cy, m_hdc, 0, 0, SRCCOPY);

         }

         if (bSetWindowPos)
         {

            if (m_pimpl->m_pui != NULL)
            {

               m_pimpl->m_pui->on_set_window_pos();

            }

         }


         if (m_pimpl->m_bIpcCopy)
         {

            ipc_copy(cx, cy, pdib->m_pcolorref, pdib->m_iScan);

         }

      }
      catch (...)
      {


      }

      destroy_window_graphics_();

   }


} // namespace windows




