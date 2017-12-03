#pragma once



// Ubuntu apt-get install libx11-dev
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>



#include "linux_osdisplay.h"

#include "linux_oswindow.h"

#include "linux_window_cairo.h"

#include "linux_window_xlib.h"

#include "linux_windowing.h"

#ifdef __cplusplus

void set_xcolor(XColor & color, COLORREF cr);

#endif



struct hthread;

namespace ca2
{


   class thread_base;


} // namespace ca2


//class oswindow_data;


//typedef oswindow_data * oswindow;



namespace user
{


   class interaction;
   class interaction;


} // namespace user


class oswindow_dataptra;


class simple_event;


class mutex;


class CLASS_DECL_AURA oswindow_data
{
public:


   osdisplay                     m_osdisplay;
   Window                        m_window;
   Visual                        m_visual;
   int                           m_iDepth;
   int                           m_iScreen;
   bool                          m_bMessageOnlyWindow;
   ::user::interaction_impl *    m_pimpl;
   HTHREAD                       m_hthread;
   int_ptr_to_int_ptr *          m_plongptrmap;
   Colormap                      m_colormap;
   DWORD                         m_dwLastMouseMove;
   Window                        m_parent;
   RECT                          m_rect;

   //ref_array < bool >            m_bptraTellMeDestroyed; // Telmo why!! :-)


   static oswindow_dataptra * s_pdataptra;
   static mutex * s_pmutex;

   static Atom s_atomLongType;
   static Atom s_atomLongStyle;
   static Atom s_atomLongStyleEx;

   static Atom get_window_long_atom(int32_t nIndex);




   oswindow_data();
   //oswindow_data(::user::interaction * puibaseMessageOnlyWindow);
   //oswindow_data(const void * p);
   //oswindow_data(const LPARAM & lparam);
   //oswindow_data(const WPARAM & wparam);


   ~oswindow_data();



   operator void * ()
   {
      return this;
   }

   operator void * () const
   {
      return (void *) this;
   }

   oswindow_data & operator = (const oswindow_data & window);

   bool operator == (const void * p) const
   {
      return this == p;
   }

   bool operator != (const void * p) const
   {
      return this != p;
   }

   Display * display()
   {
      return this == NULL ? NULL : m_osdisplay->display();
   }

   Display * display() const
   {
      return this == NULL ? NULL : m_osdisplay->display();
   }

   Window window()
   {
      return this == NULL ? None : m_window;
   }

   Window window() const
   {
      return this == NULL ? None : m_window;
   }

   Visual * visual()
   {
      return this == NULL ? NULL : &m_visual;
   }

   Visual * visual() const
   {
      return this == NULL ? NULL : (Visual *) &m_visual;
   }


   void send_client_event(Atom atom, unsigned int numArgs, ...);
   int32_t store_name(const char * psz);
   int32_t select_input(int32_t iInput);
   int32_t select_all_input();
   int32_t map_window();

   void set_user_interaction(::user::interaction_impl * pui);


   void post_nc_destroy();


   bool is_child(oswindow oswindowcandidateChildOrDescendant); // or descendant
   oswindow get_parent();
   Window get_parent_handle();
   oswindow set_parent(oswindow oswindowNewParent);
   long get_state();
   bool is_iconic();
   bool is_window_visible();
   bool show_window(int32_t nCmdShow);
   LONG_PTR get_window_long_ptr(int32_t nIndex);
   LONG_PTR set_window_long_ptr(int32_t nIndex, LONG_PTR l);
   bool client_to_screen(LPPOINT lppoint);
   bool screen_to_client(LPPOINT lppoint);



   bool is_null() const
   {
      return this == NULL;
   }


   bool is_destroying();


};


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




class oswindow_dataptra :
   public array < oswindow_data * >
{
public:

   virtual ~oswindow_dataptra()
   {

         remove_all();

   }

   void remove_all()
   {

      for(auto p : *this)
      {

         delete p;

      }

      array < oswindow_data * >::remove_all();
   }

};

extern oswindow g_oswindowDesktop;




class osdisplay_dataptra :
   public ::raw_array < osdisplay_data * >
{
public:

   virtual ~osdisplay_dataptra()
   {

         remove_all();

   }

   void remove_all()
   {

      for(auto p : *this)
      {

         delete p;

      }

      raw_array < osdisplay_data * >::remove_all();
   }

};


#pragma once

// // Ubuntu apt-get install libx11-dev
// // CentOS yum install libX11-devel
#include <X11/Xlib.h>
#include <X11/Xutil.h>
// // Ubuntu apt-get install libcairo2-dev


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
/*WINBOOL WINAPI TransparentBlt(HDC hdcDest,
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




