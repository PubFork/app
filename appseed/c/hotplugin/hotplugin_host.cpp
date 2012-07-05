#include "framework.h"
#include <gdiplus.h>


namespace hotplugin
{


   host::host()
   {

      m_pplugin                  = NULL;
      m_puchMemory               = NULL;
      m_countMemory              = 0;
      m_dProgressRate            = 0.0;
      m_bShowProgress            = false;
      m_bCa2InstallationReady    = false;
      m_bStream                  = false;
      m_pvoidSystem              = NULL;


      m_pcolorref                = NULL;
      m_hfilemapBitmap           = NULL;
      m_hfileBitmap              = INVALID_HANDLE_VALUE;

      m_pbitmap                  = NULL;
      m_pmutexBitmap             = NULL;

   }

   host::~host()
   {
      free_memory();
   }


   bool host::open_url(const char * psz)
   {

      UNREFERENCED_PARAMETER(psz);

      return false;

   }


   bool host::reload_plugin()
   {
      return false;
   }

   vsstring host::get_host_location_url()
   {
      return m_strHostPluginLocation;
   }

   void host::redraw()
   {
   }

   void host::post_message(UINT uiMessage, WPARAM wparam, LPARAM lparam)
   {
   }

   HWND host::get_host_window()
   {
      return NULL;
   }

   void host::get_window_rect(LPRECT lprect)
   {

      if(m_pplugin != NULL)
      {
         
         m_pplugin->get_window_rect(lprect);

      }
      else
      {

         *lprect = m_rect;

      }

   }

   void host::set_window_rect(LPCRECT lpcrect)
   {
      
      
      if(m_pplugin != NULL)
      {

         m_pplugin->set_window_rect(lpcrect);

      }
      else
      {

         m_rect = *lpcrect;

      }

   }

   //bool host::hist(const char * pszUrl);
   //void host::run_start_install(const char * pszRun);




   void host::set_memory(void * puchMemory, count c)
   {
      free_memory();
      m_puchMemory = (byte *) _ca_alloc(c);
      memcpy_dup(m_puchMemory, puchMemory, c);
      m_countMemory = c;
   }

   void host::append_memory(void * puchMemory, count c)
   {
      if(c <= 0)
         return;
      if(m_puchMemory == NULL)
      {
         set_memory(puchMemory, c);
      }
      else
      {
         byte * puchMemoryNew = (byte *) _ca_realloc(m_puchMemory, m_countMemory + c, 0, NULL, 0);
         memcpy_dup(&puchMemoryNew[m_countMemory], puchMemory, c);
         m_countMemory += c;
         m_puchMemory = puchMemoryNew;
      }
   }

   count host::get_memory_length()
   {
      return m_countMemory;
   }

   count host::read_memory(void * puchMemory, count c)
   {
      if(c > m_countMemory)
         c = m_countMemory;
      memcpy_dup(puchMemory, m_puchMemory, c);
      return c;
   }

   void host::free_memory()
   {
      free_memory(&m_puchMemory);
   }

   void host::free_memory(byte ** ppuchMemory)
   {
      if(*ppuchMemory != NULL)
      {
         _ca_free(*ppuchMemory, 0);
      }
      *ppuchMemory = NULL;
   }


   //void host::start_ca2();


   //void host::finalize();

   //bool host::os_native_bergedge_start();

   //int starter_start(const char * pszId);

   int host::start_ca2_system()
   {
      if(m_pplugin != NULL)
      {
         return m_pplugin->start_ca2_system();
      }
      return -1;
   }

   void host::on_paint(HDC hdcWindow, LPCRECT lprect)
   {

      if(m_pplugin != NULL)
      {

         try
         {

            m_pplugin->on_paint(hdcWindow, lprect);

         }
         catch(...)
         {
         }

      }
      else
      {

         plugin::on_paint(hdcWindow, lprect);

      }

   }

#ifdef WINDOWS
   uint_ptr host::message_handler(uint_ptr uiMessage, WPARAM wparam, LPARAM lparam)
   {
      if(m_pplugin != NULL)
      {
         return m_pplugin->message_handler(uiMessage, wparam, lparam);
      }
      return 0;
   }
#else
   int host::message_handler(XEvent * pevent)
   {
      if(m_pplugin != NULL)
      {
         return m_pplugin->message_handler(pevent);
      }
      return 0;
   }
#endif


   void host::set_ready()
   {

      m_bOk = true;

      if(is_ok() && m_pplugin != NULL && m_pplugin->is_ok())
      {

         on_ready();

      }

   }


   void host::on_ready()
   {

      if(m_pplugin != NULL)
      {

         m_pplugin->on_ready();

      }

   }

   bool host::initialize()
   {

      if(m_pplugin != NULL)
      {

         return m_pplugin->initialize();

      }

      return true;

   }

   bool host::finalize()
   {

      if(m_pplugin != NULL)
      {

         plugin * pplugin = m_pplugin;

         m_pplugin = NULL;

         pplugin->finalize();

         return true;

      }

      return true;

   }

   void host::start_plugin()
   {

      //Sleep(15 * 1000);
      //Sleep(15 * 1000);
      //      update_npca2_installed();
      simple_mutex * pmutex = new simple_mutex("Global\\ca2::fontopus::ccvotagus_ca2_spa::7807e510-5579-11dd-ae16-0800200c7784");
      if(::GetLastError() == ERROR_ALREADY_EXISTS)
      {
         m_bRunningSpaAdmin = true;
         delete pmutex;
         return;
      }
      delete pmutex;


      m_pplugin = new spa::plugin();
      m_pplugin->m_phost = this;


   }

   void host::start_ca2()
   {
      if(m_pplugin != NULL)
      {
         m_pplugin->start_ca2();
      }
      else
      {
         ::hotplugin::plugin::start_ca2();
      }
   }

   void host::set_progress_rate(double dRate)
   {
      m_dProgressRate = dRate;
   }

   double host::get_progress_rate()
   {
      if(m_dProgressRate < 0.0)
         return 0.0;
      else if(m_dProgressRate > 1.0)
         return 1.0;
      else
         return m_dProgressRate;
   }

   void host::set_ca2_installation_ready(bool bReady)
   {
      m_bCa2InstallationReady = bReady;
   }

   bool host::is_ca2_installation_ready()
   {
      return m_bCa2InstallationReady;
   }


   int host::starter_start(const char * pszCommandLine)
   {

      return starter_start(pszCommandLine, this);

   }


   int host::starter_start(const char * pszCommandLine, plugin * pplugin)
   {
      set_installing_ca2();
      spa_starter_start * pstart    = new spa_starter_start;
      pstart->m_pplugin             = pplugin;
      pstart->m_strCommandLine      = pszCommandLine;
#ifdef WINDOWS

      ::CreateThread(
         NULL, 
         0, 
         &::_ca2_starter_start, 
         pstart, 
         0, 
         pplugin == NULL ?
NULL : &pplugin->m_nCa2StarterStartThreadID);

#else
      pthread_t * threadId;
      pthread_attr_t  attr;
      int rc = 0;

      if(rc = pthread_attr_init(&attr))
         return -1;

      if(rc = pthread_attr_setstacksize(&attr, 1024 * 1024))
         return -1;

      if(rc = pthread_create(threadId, &attr, (void*(*)(void*))&::_ca2_starter_start,  pstart))
         return -1;
#endif
      return 0;
   }


   void host::deferred_prodevian_redraw()
   {

      if(m_pplugin != NULL)
      {
         m_pplugin->deferred_prodevian_redraw();
      }

   }

   void * host::get_system()
   {

      return m_pvoidSystem;

   }

   void host::set_system(void * pvoidSystem)
   {

      m_pvoidSystem = pvoidSystem;

   }

   void host::set_status(const char * pszStatus)
   {

      ::hotplugin::plugin::set_status(pszStatus);

      if(m_pplugin != NULL)
      {
         m_pplugin->set_status(pszStatus);
      }

   }


   void host::set_bitmap(HDC hdcWindow, LPCRECT lprect)
   {

      ensure_bitmap_data(width(lprect), height(lprect));

      mutex_lock ml(m_pmutexBitmap, true);

      m_sizeBitmap.cx = abs_dup(lprect->right - lprect->left);

      m_sizeBitmap.cy = abs_dup(lprect->bottom - lprect->top);

      try
      {

         HBITMAP hbitmap         = ::CreateBitmap(m_sizeBitmap.cx, m_sizeBitmap.cy, 1, 32, m_pcolorref);

         HDC hdc                 = ::CreateCompatibleDC(NULL);

         HBITMAP hbitmapOld      = (HBITMAP) ::SelectObject(hdc, hbitmap);

         ::BitBlt(hdc, 0, 0, m_sizeBitmap.cx, m_sizeBitmap.cy, hdcWindow, lprect->left, lprect->top, SRCCOPY);

         ::SelectObject(hdc, hbitmapOld);

         ::DeleteDC(hdc);

         ::DeleteObject(hbitmap);

      }
      catch(...)
      {
      }

      return;

   }

   void host::paint_bitmap(HDC hdcWindow, LPCRECT lprect)
   {

      ensure_bitmap_data(width(lprect), height(lprect));

      mutex_lock ml(m_pmutexBitmap, true);

      m_sizeBitmap.cx = abs_dup(lprect->right - lprect->left);

      m_sizeBitmap.cy = abs_dup(lprect->bottom - lprect->top);

      try
      {

         HBITMAP hbitmap         = ::CreateBitmap(m_sizeBitmap.cx, m_sizeBitmap.cy, 1, 32, m_pcolorref);

         HDC hdc                 = ::CreateCompatibleDC(NULL);

         HBITMAP hbitmapOld      = (HBITMAP) ::SelectObject(hdc, hbitmap);

         ::BitBlt(hdcWindow, lprect->left, lprect->top, m_sizeBitmap.cx, m_sizeBitmap.cy,  hdc, 0, 0, SRCCOPY);

         ::SelectObject(hdc, hbitmapOld);

         ::DeleteDC(hdc);

         ::DeleteObject(hbitmap);


      }
      catch(...)
      {
      }

      return;

   }


   void host::blend_bitmap(HDC hdcWindow, LPCRECT lprect)
   {

      ensure_bitmap_data(width(&m_pplugin->m_rect), height(&m_pplugin->m_rect));

      mutex_lock ml(m_pmutexBitmap, true);

      m_sizeBitmap.cx = abs_dup(m_pplugin->m_rect.right - m_pplugin->m_rect.left);
      
      m_sizeBitmap.cy = abs_dup(m_pplugin->m_rect.bottom - m_pplugin->m_rect.top);

      try
      {

         Gdiplus::Bitmap b(m_sizeBitmap.cx, m_sizeBitmap.cy, m_sizeBitmap.cx *4 , PixelFormat32bppARGB, (BYTE *) m_pcolorref);

         Gdiplus::Graphics * pg = new Gdiplus::Graphics(hdcWindow);

         pg->SetCompositingMode(Gdiplus::CompositingModeSourceOver);

         pg->SetCompositingQuality(Gdiplus::CompositingQualityHighQuality);

         pg->DrawImage(&b, lprect->left, lprect->top, lprect->left - m_pplugin->m_rect.left, lprect->top - m_pplugin->m_rect.top,
                           lprect->right - lprect->left, lprect->bottom - lprect->top, Gdiplus::UnitPixel);

         pg->Flush(Gdiplus::FlushIntentionSync);

         delete pg;

         ::GdiFlush();

      }
      catch(...)
      {
      }

      return;

   }

} // namespace hotplugin




