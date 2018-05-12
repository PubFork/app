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
   r.X = lpcrect->left;
   r.Y = lpcrect->top;
   r.Width = ::width(lpcrect);
   r.Height = ::height(lpcrect);
}

inline void copy(Gdiplus::RectF & r, LPCRECT lpcrect)
{
   r.X = lpcrect->left;
   r.Y = lpcrect->top;
   r.Width = ::width(lpcrect);
   r.Height = ::height(lpcrect);
}

inline void copy(Gdiplus::RectF & r, LPCRECTD lpcrect)
{
   r.X = lpcrect->left;
   r.Y = lpcrect->top;
   r.Width = ::width(lpcrect);
   r.Height = ::height(lpcrect);
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
   lprect->left = r.X;
   lprect->top = r.Y;
   lprect->right = r.X + r.Width;
   lprect->bottom = r.Y + r.Height;
}

inline void copy(LPRECTD lprect, Gdiplus::RectF & r)
{
   lprect->left = r.X;
   lprect->top = r.Y;
   lprect->right = r.X + r.Width;
   lprect->bottom = r.Y + r.Height;
}

#endif


