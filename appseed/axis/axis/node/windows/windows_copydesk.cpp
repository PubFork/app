#include "framework.h"
//#include "base/user/user.h"
//#include "windows.h"
//#include <shlobj.h>




namespace windows
{


   copydesk::copydesk(::aura::application * papp) :
      ::object(papp),
      ::user::copydesk(papp)
   {

      m_hwnd = NULL;

      defer_create_mutex();

   }

   copydesk::~copydesk()
   {

      ::DestroyWindow(m_hwnd);

   }

   void copydesk::OnClipboardUpdate()
   {

      synch_lock sl(m_pmutex);

      m_cFileCount = -1;
      m_iPriorityTextFormat = -2;
      m_iFilea = -1;
      m_iText = -1;
      m_iDib = -1;

   }


   LRESULT WINAPI copydesk::WindowProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
   {

      if(message == WM_CLIPBOARDUPDATE)
      {

         LONG_PTR l = ::GetWindowLongPtrA(hwnd, GWLP_USERDATA);

         copydesk * pdesk = (copydesk *) l;

         if(pdesk != NULL)
         {

            pdesk->OnClipboardUpdate();

         }

      }

      return DefWindowProc(hwnd, message, wparam, lparam);

   }


   bool copydesk::initialize()
   {

      if (!::user::copydesk::initialize())
         return false;

      synch_lock sl(m_pmutex);

      WNDCLASS wndcls = {};

      string strClass = "ca2_copydesk_windows_message_queue";

      if (!GetClassInfo(System.m_hinstance, strClass, &wndcls))
      {

         wndcls.style = 0;
         wndcls.lpfnWndProc = &copydesk::WindowProc;
         wndcls.cbClsExtra = 0;
         wndcls.cbWndExtra = 0;
         wndcls.hInstance = System.m_hinstance;
         wndcls.hIcon = NULL;
         wndcls.hCursor = NULL;
         wndcls.hbrBackground = NULL;
         wndcls.lpszMenuName = NULL;
         wndcls.lpszClassName = strClass;

         if (!::RegisterClass(&wndcls))
         {

            return false;

         }

      }

      m_hwnd = ::CreateWindowEx(0, strClass, 0, 0, 0, 0, 0, 0, HWND_MESSAGE, 0, 0, NULL);

      if (m_hwnd == NULL)
      {

         return false;

      }

      ::SetWindowLongPtr(m_hwnd, GWLP_USERDATA, (LONG_PTR) this);

      if(!::AddClipboardFormatListener(m_hwnd))
      {

         finalize();

         return false;

      }

      OnClipboardUpdate();

      return true;

   }


   bool copydesk::finalize()
   {

      if(m_hwnd == NULL)
      {

         return true;

      }

      bool bOk1 = ::RemoveClipboardFormatListener(m_hwnd);

      bool bOk2 = ::DestroyWindow(m_hwnd);

      bool bOk3 = ::user::copydesk::finalize();

      return bOk1 && bOk2 && bOk3;

   }


   bool copydesk::_has_filea()
   {

      return _get_file_count();

   }


   HGLOBAL copydesk::hglobal_get_filea(const ::file::patha & patha)
   {

      strsize iLen = 0;

      for (int32_t i = 0; i < patha.get_size(); i++)
      {

         iLen += ::str::international::utf8_to_unicode_count(patha[i]) + 1;

      }

      HGLOBAL hglb = ::GlobalAlloc(GMEM_MOVEABLE, sizeof(DROPFILES) + (iLen + 1) * sizeof(WCHAR));
      LPDROPFILES pDropFiles = (LPDROPFILES) ::GlobalLock(hglb);
      pDropFiles->pFiles = sizeof(DROPFILES);
      pDropFiles->pt.x = pDropFiles->pt.y = 0;
      pDropFiles->fNC = TRUE;
      pDropFiles->fWide = TRUE;

      LPTSTR lpsz = (char *)pDropFiles;
      lpsz += pDropFiles->pFiles;
      unichar * lpwsz = (unichar *)lpsz;

      for (int32_t i = 0; i < patha.get_size(); i++)
      {

         ::count c = ::str::international::utf8_to_unicode_count(patha[i]) + 1;

         ::str::international::utf8_to_unicode(lpwsz, c, patha[i]);

         lpwsz += c;

      }

      *lpwsz = L'\0';

      ::GlobalUnlock(hglb);

      return hglb;

   }


   HGLOBAL copydesk::hglobal_get_wide_text(const string & str)
   {

      ::count c = ::str::international::utf8_to_unicode_count(str) + 1;
      HGLOBAL hglb = ::GlobalAlloc(GMEM_MOVEABLE, c * sizeof(WCHAR));
      unichar * lpwsz = (unichar *) ::GlobalLock(hglb);
      ::str::international::utf8_to_unicode(lpwsz, c, str);
      ::GlobalUnlock(hglb);

      return hglb;

   }


   HGLOBAL copydesk::hglobal_get_utf8_text(const string & str)
   {

      HGLOBAL hglb = ::GlobalAlloc(GMEM_MOVEABLE, sizeof(CHAR) * (str.length() + 1));
      char * lpsz = (char *) ::GlobalLock(hglb);
      strcpy(lpsz, str);
      ::GlobalUnlock(hglb);

      return hglb;

   }


   HGLOBAL copydesk::hglobal_get_dib(::draw2d::dib * pdib)
   {

      DWORD dwWidth, dwHeight;
      BITMAPINFOHEADER bi;
      HCURSOR hAlphaCursor = NULL;

      dwWidth = pdib->m_size.cx;
      dwHeight = pdib->m_size.cy;

      ZeroMemory(&bi, sizeof(BITMAPINFOHEADER));
      bi.biSize = sizeof(BITMAPINFOHEADER);
      bi.biWidth = dwWidth;
      bi.biHeight = -(LONG)dwHeight;
      bi.biPlanes = 1;
      bi.biBitCount = 32;
      bi.biCompression = BI_RGB;
      bi.biSizeImage = pdib->m_iScan * pdib->m_size.cy;

      HGLOBAL hglb = GlobalAlloc(GMEM_MOVEABLE, sizeof(bi) + pdib->m_iScan * pdib->m_size.cy);

      if (hglb == NULL)
      {

         return NULL;

      }

      LPBYTE lp = (LPBYTE) ::GlobalLock(hglb);

      memcpy(lp, &bi, sizeof(bi));
      memcpy(lp + sizeof(bi), pdib->m_pcolorref, pdib->m_iScan * pdib->m_size.cy);
      GlobalUnlock(hglb);

      return hglb;

   }


   int copydesk::_get_priority_text_format()
   {

      if(m_iPriorityTextFormat == -2)
      {

         UINT uiaFormatPriorityList[] =
         {
            CF_UNICODETEXT,
            CF_TEXT
         };

         m_iPriorityTextFormat = ::GetPriorityClipboardFormat(uiaFormatPriorityList, ARRAYSIZE(uiaFormatPriorityList));

      }

      return m_iPriorityTextFormat;

   }


   ::count copydesk::_get_file_count()
   {

      if(m_cFileCount < 0)
      {

         if (!IsClipboardFormatAvailable(CF_HDROP))
         {

            m_cFileCount = 0;

         }
         else
         {

            synch_lock sl(m_pmutex);

            if (!::OpenClipboard(m_hwnd))
            {

               m_cFileCount =  0;

            }
            else
            {

               HDROP hdrop = (HDROP) ::GetClipboardData(CF_HDROP);

               ::count c = 0;

               if (hdrop != NULL)
               {

                  c = ::DragQueryFile(hdrop, 0xFFFFFFFF, NULL, 0);

               }

               ::CloseClipboard();

               m_cFileCount = c;

            }

         }

      }

      return m_cFileCount;

   }


   bool copydesk::_get_filea(::file::patha & patha, e_op & eop)
   {

      ::count c = _get_file_count();

      if (c <= 0)
      {

         return false;

      }

      synch_lock sl(m_pmutex);

      if (!::OpenClipboard(m_hwnd))
      {

         return false;

      }

      HDROP hdrop = (HDROP) ::GetClipboardData(CF_HDROP);

      for (index i = 0; i < c; i++)
      {

         hwstring wstr;

         UINT uiLen = ::DragQueryFileW(hdrop, i, NULL, 0);

         wstr.stralloc(uiLen);

         ::DragQueryFileW(hdrop, i, wstr, wstr.count());

         patha.add(::file::path((const unichar *) wstr));

      }

      ::CloseClipboard();

      return true;

   }


   bool copydesk::_set_filea(const ::file::patha & patha, e_op eop)
   {

      ASSERT(::IsWindow(m_hwnd));

      synch_lock sl(m_pmutex);

      if (!::OpenClipboard(m_hwnd))
      {

         return false;

      }

      EmptyClipboard();

      SetClipboardData(CF_HDROP, hglobal_get_filea(patha));

      SetClipboardData(CF_UNICODETEXT, hglobal_get_wide_text(patha.implode("\r\n")));

      SetClipboardData(CF_TEXT, hglobal_get_utf8_text(patha.implode("\r\n")));

      VERIFY(::CloseClipboard());

      return true;

   }


   bool copydesk::_has_plain_text()
   {

      if(m_iText < 0)
      {

         int iFormat = _get_priority_text_format();

         m_iText = iFormat != 0 && iFormat != -1 ? 1 : 0;

      }

      return m_iText != 0;

   }


   bool copydesk::_set_plain_text(const string & str)
   {

      ASSERT(::IsWindow(m_hwnd));

      synch_lock sl(m_pmutex);

      if (!::OpenClipboard(m_hwnd))
      {

         return false;

      }

      EmptyClipboard();

      SetClipboardData(CF_UNICODETEXT, hglobal_get_wide_text(str));

      SetClipboardData(CF_TEXT, hglobal_get_utf8_text(str));

      ::file::patha patha;

      if (string_to_filea(&patha, str))
      {

         SetClipboardData(CF_TEXT, hglobal_get_filea(patha));

      }

      VERIFY(::CloseClipboard());

      return true;

   }


   bool copydesk::_get_plain_text(string & str)
   {

      int iFormat = _get_priority_text_format();

      if (iFormat == 0 || iFormat == -1)
      {

         return false;

      }

      synch_lock sl(m_pmutex);

      if (!::OpenClipboard(m_hwnd))
      {

         return false;

      }

      HGLOBAL hglb = GetClipboardData(iFormat);

      if (iFormat == CF_UNICODETEXT)
      {

         str = (const unichar *)GlobalLock(hglb);

      }
      else if (iFormat == CF_TEXT)
      {

         str = (char *)GlobalLock(hglb);

      }

      GlobalUnlock(hglb);

      VERIFY(::CloseClipboard());

      return true;

   }


#undef new

   bool copydesk::_has_dib()
   {

      if(m_iDib < 0)
      {

         m_iDib = IsClipboardFormatAvailable(CF_BITMAP) ? 1 : 0;

      }

      return m_iDib != 0;

   }


   bool copydesk::_desk_to_dib(::draw2d::dib * pdib)
   {

      if (!_has_dib())
      {

         return false;

      }

      synch_lock sl(m_pmutex);

      if (!::OpenClipboard(m_hwnd))
      {

         return false;

      }

      bool bOk = false;

      HBITMAP hbitmap = (HBITMAP) ::GetClipboardData(CF_BITMAP);

      if(hbitmap != NULL)
      {


         HDC hdcMem = NULL;

         HGDIOBJ hbitmapOld = NULL;

         try
         {

            BITMAP bm;

            ZERO(bm);

            ::GetObject(hbitmap, sizeof(bm), &bm);

            pdib->create(bm.bmWidth, bm.bmHeight);

            if (pdib->m_size.area() > 0)
            {

               pdib->Fill(0);

               HDC hdc = (HDC)pdib->get_graphics()->get_os_data_ex(1);

               hdcMem = ::CreateCompatibleDC(NULL);

               hbitmapOld = ::SelectObject(hdcMem, hbitmap);

               BITMAPINFO bi;

               bi.bmiHeader.biSize = sizeof(BITMAPINFO);
               bi.bmiHeader.biWidth = bm.bmWidth;
               bi.bmiHeader.biHeight = -bm.bmHeight;
               bi.bmiHeader.biPlanes = 1;
               bi.bmiHeader.biBitCount = 32;
               bi.bmiHeader.biCompression = BI_RGB;
               bi.bmiHeader.biSizeImage = pdib->m_iScan * bm.bmHeight;
               bi.bmiHeader.biXPelsPerMeter = 0;
               bi.bmiHeader.biYPelsPerMeter = 0;
               bi.bmiHeader.biClrUsed = 0;
               bi.bmiHeader.biClrImportant = 0;

               GetDIBits(hdcMem, hbitmap, 0, bm.bmHeight, pdib->m_pcolorref, &bi, DIB_RGB_COLORS);

               pdib->get_graphics()->release_os_data_ex(1, hdc);

            }

         }
         catch (...)
         {

         }

         if (hdcMem != NULL)
         {

            ::SelectObject(hdcMem, hbitmapOld);

            ::DeleteDC(hdcMem);

         }

         ::DeleteObject((HGDIOBJ)hbitmap);

         ::CloseClipboard();

      }

      return bOk;

   }


   bool copydesk::_dib_to_desk(::draw2d::dib * pdib)
   {

      ASSERT(::IsWindow(m_hwnd));

      synch_lock sl(m_pmutex);

      if (!::OpenClipboard(m_hwnd))
      {

         return false;

      }

      EmptyClipboard();


      SetClipboardData(CF_DIB, hglobal_get_dib(pdib));


      VERIFY(::CloseClipboard());

      return true;

   }

#define new AURA_NEW


} // namespace windows



