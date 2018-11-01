#include "framework.h"


#ifdef MACOS

void set_cursor_dib(void * dib, int xHotSpot, int yHotSpot);

void SetCursor(void * pnscursor);

void * CreateAlphaCursor(void * dib, int xHotSpot, int yHotSpot);

#elif defined(LINUX)

void SetCursor(oswindow window, HCURSOR hcursor);

HCURSOR CreateAlphaCursor(oswindow window, ::draw2d::dib * dib, int xHotSpot, int yHotSpot);

#endif


namespace visual
{

   cursor::cursor(::aura::application * papp) :
      object(papp),
      m_dib(allocer())
   {

#if defined(WINDOWSEX) || defined(MACOS)

      m_hcursor = NULL;

#endif

   }


   bool cursor::to(::draw2d::graphics * pgraphics, point pt)
   {

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      return pgraphics->draw(pt - m_szHotspotOffset, m_dib->m_size, m_dib->get_graphics(), null_point());

   }


   bool cursor::set_current(::user::interaction * pui, ::aura::session * psession)
   {

      synch_lock sl(psession->m_pmutex);

#if defined(MACOS) || defined(WINDOWSEX)

      ::SetCursor(get_HCURSOR());

#else

      if(::is_null(pui))
      {

         return false;

      }

      ::SetCursor(pui->get_handle(), get_HCURSOR(pui));

#endif

      //psession->m_pcursorCursor = this;

      return true;

   }


   bool cursor::reset(::user::interaction * pui, ::aura::session * psession)
   {

      synch_lock sl(psession->m_pmutex);

#if defined(MACOS) || defined(WINDOWSEX)

      ::SetCursor(NULL);

#else

      if(::is_null(pui))
      {

         return false;

      }

      ::SetCursor(pui->get_handle(), NULL);

#endif

      return true;

   }

#ifdef WINDOWSEX

   bool cursor::initialize_system_default()
   {

      const char * psz;

      if (m_ecursor == cursor_arrow)
      {

         psz = IDC_ARROW;

      }
      else if (m_ecursor == cursor_size_top || m_ecursor == cursor_size_bottom)
      {

         psz = IDC_SIZENS;

      }
      else if (m_ecursor == cursor_size_left || m_ecursor == cursor_size_right)
      {

         psz = IDC_SIZEWE;

      }
      else if (m_ecursor == cursor_size_top_left || m_ecursor == cursor_size_bottom_right)
      {

         psz = IDC_SIZENWSE;

      }
      else if (m_ecursor == cursor_size_top_right || m_ecursor == cursor_size_bottom_left)
      {

         psz = IDC_SIZENESW;

      }
      else if (m_ecursor == cursor_text_select)
      {

         psz = IDC_IBEAM;

      }
      else if (m_ecursor == cursor_hand)
      {

         psz = IDC_HAND;

      }
      else
      {

         return false;

      }

      m_hcursor = LoadCursor(NULL, psz);

      if (m_hcursor == NULL)
      {

         return false;

      }

      return true;

   }
#else
   bool cursor::initialize_system_default()
   {

      return true;

   }

#endif


   HCURSOR cursor::get_HCURSOR(::user::interaction * pui)
   {

      if(m_hcursor == NULL)
      {

      #ifdef LINUX

         if(::is_null(pui))
         {

            return NULL;

         }

         m_hcursor = ::CreateAlphaCursor(pui->get_handle(), m_dib,m_szHotspotOffset.cx,m_szHotspotOffset.cy);

      #else

         m_hcursor = ::CreateAlphaCursor(m_dib,m_szHotspotOffset.cx,m_szHotspotOffset.cy);

      #endif

      }

      return m_hcursor;

   }


   void cursor_alloc(::aura::application * papp,cursor * & pdib,int xHotspot,int yHotspot)
   {

      pdib = new cursor(papp);

      pdib->m_szHotspotOffset.cx = xHotspot;
      pdib->m_szHotspotOffset.cy = yHotspot;

   }


   ::draw2d::dib * cursor_get_dib(cursor * pcursor)
   {

      return pcursor->m_dib;

   }


} // namespace visual










