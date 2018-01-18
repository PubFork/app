#include "framework.h"
#include "linux_user_impl.h"


device_context::device_context()
{


  m_pdisplay     = NULL;
  m_drawable     = None;
  m_gc           = None;
  m_pixmap       = None;
  m_window       = None;
  m_pt.x         = 0;
  m_pt.y         = 0;
  m_ptOffset.x   = 0;
  m_ptOffset.y   = 0;
  m_iScreen      = 0;
  m_iDepth       = 0;
  m_fontset      = None;



}

//
//
//
//// HDC GetDC(oswindow hwnd)
//// {
//
//
////    HDC hdc = new device_context;
//
////    hdc->m_pdisplay      = hwnd->display();
////    hdc->m_window        = hwnd->window();
////    hdc->m_drawable      = (Drawable) (hwnd == NULL || hwnd->window() == NULL ? DefaultRootWindow(hdc->m_pdisplay) : hwnd->window());
////    hdc->m_gc            = XCreateGC(hdc->m_pdisplay, hdc->m_drawable, 0, 0);
//
////    return hdc;

// }


// HDC CreateCompatibleDC(HDC hdcParam)
// {

//    HDC hdc = new device_context;

//    return hdc;

// }


// HDC GetWindowDC(oswindow hwnd)
// {

//    return GetDC(hwnd);
// }


// WINBOOL ReleaseDC(oswindow hwnd, HDC hdc)
// {


//    //single_lock sl(&user_mutex(), true);


//    if(hdc == NULL)
//       return FALSE;

//    XFreeGC(hdc->m_pdisplay, hdc->m_gc);
//    XCloseDisplay(hdc->m_pdisplay);

//    delete hdc;
//    return TRUE;

// }




// int32_t FillRect(HDC hdc, const RECT * lprc, HBRUSH hbr)
// {

//    //single_lock sl(&user_mutex(), true);


//    XFillRectangle(hdc->m_pdisplay, hdc->m_drawable, hdc->m_gc, lprc->left, lprc->top, lprc->right - lprc->left, lprc->bottom - lprc->top);
//    return 1;
// }


// HDC BeginPaint(oswindow hwnd, PAINTSTRUCT * ps)
// {

//    HDC hdc = GetDC(hwnd);

//    GetClientRect(hwnd, &ps->rcPaint);

//    return hdc;

// }


// WINBOOL EndPaint(oswindow hwnd, PAINTSTRUCT * ps)
// {

//    return ReleaseDC(hwnd, ps->hdc);

// }











