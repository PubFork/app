#pragma once



// Ubuntu apt-get install libx11-dev
// // Ubuntu apt-get install libx11-dev
// // CentOS yum install libX11-devel
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
//#include <X11/Xatom.h>
// // Ubuntu apt-get install libcairo2-dev

#include <glib.h>



CLASS_DECL_AURA int xinerama_get_monitor_count();
CLASS_DECL_AURA int xinerama_get_monitor_rect(index i, LPRECT lprect);
CLASS_DECL_AURA int xinerama_get_screen_size(int& width, int& height);


int best_xinerama_monitor(::user::interaction * pui, LPRECT lprectRet);
int best_xinerama_monitor(::user::interaction * pui, LPCRECT lpcrect, LPRECT lprectRet);


void mapped_net_state_raw(bool add, Display * d, Window w, int iScreen, Atom state1, Atom state2);
void unmapped_net_state_raw(Display * d, Window w, ...);



#include "linux_xdisplay.h"

#include "linux_osdisplay.h"

#include "linux_oswindow.h"

#include "linux_window_cairo.h"

#include "linux_window_xlib.h"

#include "linux_windowing.h"

#ifdef __cplusplus

void set_xcolor(XColor & color, COLORREF cr);

#endif




CLASS_DECL_AURA int32_t oswindow_find_message_only_window(::user::interaction_impl * puibaseMessageWindow);
CLASS_DECL_AURA int32_t oswindow_find(Display * pdisplay, Window window);
CLASS_DECL_AURA int32_t oswindow_find(Window window);
CLASS_DECL_AURA oswindow_data * oswindow_get_message_only_window(::user::interaction_impl * puibaseMessageWindow);
//CLASS_DECL_AURA oswindow_data * oswindow_get(Display * pdisplay, Window window, Visual * pvisual = NULL);
CLASS_DECL_AURA oswindow_data * oswindow_get(Window window);
CLASS_DECL_AURA oswindow oswindow_defer_get(Window w);
CLASS_DECL_AURA bool oswindow_remove(Display * pdisplay, Window window);
CLASS_DECL_AURA bool oswindow_remove_message_only_window(::user::interaction_impl * puibaseMessageOnlyWindow);



//#ifndef HWND_MESSAGE
//#define HWND_MESSAGE ((::oswindow_data *) (int_ptr) 1)
//#










class CLASS_DECL_AURA device_context
{
public:


   ::Display *             m_pdisplay;
   ::Drawable              m_drawable;
   ::GC                    m_gc;
   ::Pixmap                m_pixmap;
   ::Window                m_window;
   int                     m_iDepth;
   int                     m_iScreen;

   point                   m_pt;
   point                   m_ptOffset;

   XFontSet                m_fontset;

   device_context();


};


/*HDC GetDC(oswindow hwnd);
HFONT CreateFontIndirect(const LOGFONT * lf);
HPEN CreatePen(int32_t iPenStyle, int32_t iWidth, COLORREF crColor);
HGDIOBJ GetStockObject(int32_t iStockObject);
HGDIOBJ SelectObject(HDC hdc, HGDIOBJ hgdiobj);
WINBOOL Rectangle(HDC hdc, int32_t x1, int32_t y1, int32_t x2, int32_t y2);
WINBOOL DeleteObject(HGDIOBJ hgdiobj);
HDC CreateCompatibleDC(HDC hdc);
//HBITMAP WINAPI CreateDIBSection(HDC hdc, const BITMAPINFO *lpbmi, UINT usage, void **ppvBits, HANDLE hSection, DWORD offset);
WINBOOL SetTextColor(HDC hdc, COLORREF cr);
WINBOOL SetBkMode(HDC hdc, int32_t iMode);
WINBOOL DeleteDC(HDC hdc);
WINBOOL AlphaBlend(HDC hdcDest, int32_t xoriginDest, int32_t yoriginDest, int32_t wDest, int32_t hDest, HDC hdcSrc, int32_t xoriginSrc, int32_t yoriginSrc, int32_t wSrc, int32_t hSrc, BLENDFUNCTION ftn);
WINBOOL GetObject(HGDIOBJ hgdiobj, int32_t iSize, void * object);
WINBOOL GetTextExtentPoint(HDC hdc, const char * pszText, int32_t iSize, SIZE * psize);
WINBOOL WINAPI TransparentBlt(HDC hdcDest,
    __in int32_t xoriginDest,
    __in int32_t yoriginDest,
    __in int32_t wDest,
    __in int32_t hDest,
    __in HDC hdcSrc,
    __in int32_t xoriginSrc,
    __in int32_t yoriginSrc,
    __in int32_t wSrc,
    __in int32_t hSrc,
    __in UINT crTransparent);

*/



extern GMainContext * gtk_main_context;


BEGIN_EXTERN_C

gboolean gdk_callback_run_runnable(gpointer pdata);

END_EXTERN_C


template < typename PRED >
class gdk_fork_class :
   virtual public runnable
{
public:

   PRED  m_pred;

   gdk_fork_class(PRED pred) :
      m_pred(pred)
   {

      auto idle_source = g_idle_source_new();

      g_source_set_callback(idle_source, &gdk_callback_run_runnable, (::runnable *) this, NULL);

      g_source_attach(idle_source, gtk_main_context);


   }

   ~gdk_fork_class()
   {

   }

   virtual void run()
   {

      m_pred();

      delete this;

   }

};

template < typename PRED >
void gdk_fork(PRED pred)
{

   gdk_fork_class < PRED > * gdkfork = new gdk_fork_class < PRED >(pred);

}

template < typename PRED >
class gdk_sync_class :
   virtual public runnable
{
public:

   PRED  m_pred;

   sp(manual_reset_event) m_pev;

   gdk_sync_class(PRED pred, manual_reset_event * pev) :
      m_pred(pred)
      {

      m_pev = pev;

       m_pev->ResetEvent();

      auto idle_source = g_idle_source_new();

      g_source_set_callback(idle_source, &gdk_callback_run_runnable, (::runnable *) this, NULL);

      g_source_attach(idle_source, gtk_main_context);


   }

   ~gdk_sync_class()
   {

   }

   virtual void run()
   {

      m_pred();

      manual_reset_event * pev = m_pev;
      if(pev != NULL)
      {
          m_pev->SetEvent();

      }

      delete this;

   }

};


template < typename PRED >
bool gdk_sync(const duration & durationTimeout, PRED pred)
{

   sp(manual_reset_event) pev(canew(manual_reset_event(::get_app())));

   gdk_sync_class < PRED > * gdksync = new gdk_sync_class < PRED >(pred, pev);

   return pev->wait(durationTimeout).succeeded();

}

