#pragma once


#ifdef WINDOWSEX

#undef new

#define min MIN
#define max MAX

#include <gdiplus.h>

#define new AURA_NEW

#undef min
#undef max

using namespace Gdiplus;

inline void copy(Gdiplus::Rect & r, LPCRECT lpcrect)
{
   r.X = lpcrect->left;
   r.Y = lpcrect->top;
   r.Width = ::width(lpcrect);
   r.Height = ::height(lpcrect);
}

inline void copy(Gdiplus::Rect & r, LPCRECTD lpcrect)
{
   r.X =  (INT) lpcrect->left;
   r.Y = (INT)lpcrect->top;
   r.Width = (INT) ::width(lpcrect);
   r.Height = (INT) ::height(lpcrect);
}

inline void copy(Gdiplus::RectF & r, LPCRECT lpcrect)
{
   r.X = (Gdiplus::REAL) lpcrect->left;
   r.Y = (Gdiplus::REAL) lpcrect->top;
   r.Width = (Gdiplus::REAL) ::width(lpcrect);
   r.Height = (Gdiplus::REAL) ::height(lpcrect);
}

inline void copy(Gdiplus::RectF & r, LPCRECTD lpcrect)
{
   r.X = (Gdiplus::REAL) lpcrect->left;
   r.Y = (Gdiplus::REAL) lpcrect->top;
   r.Width = (Gdiplus::REAL) ::width(lpcrect);
   r.Height = (Gdiplus::REAL) ::height(lpcrect);
}


inline void copy(LPRECT lprect, Gdiplus::Rect & r)
{
   lprect->left = r.X;
   lprect->top = r.Y;
   lprect->right = r.X + r.Width;
   lprect->bottom = r.Y + r.Height;
}

inline void copy(LPRECTD lprect, Gdiplus::Rect & r)
{
   lprect->left = r.X;
   lprect->top = r.Y;
   lprect->right = r.X + r.Width;
   lprect->bottom = r.Y + r.Height;
}


inline void copy(LPRECT lprect, Gdiplus::RectF & r)
{
   lprect->left = (LONG) r.X;
   lprect->top = (LONG)r.Y;
   lprect->right = (LONG)(r.X + r.Width);
   lprect->bottom = (LONG)(r.Y + r.Height);
}

inline void copy(LPRECTD lprect, Gdiplus::RectF & r)
{
   lprect->left = r.X;
   lprect->top = r.Y;
   lprect->right = r.X + r.Width;
   lprect->bottom = r.Y + r.Height;
}

#endif


