#pragma once

#undef new

#include <D2d1_1.h>


inline void copy(D2D1_RECT_F & r, LPCRECT lpcrect)
{
   r.left = lpcrect->left;
   r.top = lpcrect->top;
   r.right = lpcrect->right;
   r.bottom = lpcrect->bottom;
}

inline void copy(D2D1_RECT_U & r, LPCRECT lpcrect)
{
   r.left = lpcrect->left;
   r.top = lpcrect->top;
   r.right = lpcrect->right;
   r.bottom = lpcrect->bottom;
}

inline void copy(D2D1_RECT_L & r, LPCRECT lpcrect)
{
   r.left = lpcrect->left;
   r.top = lpcrect->top;
   r.right = lpcrect->right;
   r.bottom = lpcrect->bottom;
}



inline void copy(D2D1_RECT_F & r, LPCRECTD lpcrect)
{
   r.left = lpcrect->left;
   r.top = lpcrect->top;
   r.right = lpcrect->right;
   r.bottom = lpcrect->bottom;
}

inline void copy(D2D1_RECT_U & r, LPCRECTD lpcrect)
{
   r.left = lpcrect->left;
   r.top = lpcrect->top;
   r.right = lpcrect->right;
   r.bottom = lpcrect->bottom;
}

inline void copy(D2D1_RECT_L & r, LPCRECTD lpcrect)
{
   r.left = lpcrect->left;
   r.top = lpcrect->top;
   r.right = lpcrect->right;
   r.bottom = lpcrect->bottom;
}



inline void copy(LPRECT lprect, const D2D1_RECT_F & r)
{

   lprect->left = r.left;
   lprect->top = r.top;
   lprect->right = r.right;
   lprect->bottom = r.bottom;

}


inline void copy(LPRECT lprect, const D2D1_RECT_U & r)
{

   lprect->left = r.left;
   lprect->top = r.top;
   lprect->right = r.right;
   lprect->bottom = r.bottom;

}



inline void copy(LPRECT lprect, const D2D1_RECT_L & r)
{

   lprect->left = r.left;
   lprect->top = r.top;
   lprect->right = r.right;
   lprect->bottom = r.bottom;

}


inline void copy(LPRECTD lprect, const D2D1_RECT_F & r)
{

   lprect->left = r.left;
   lprect->top = r.top;
   lprect->right = r.right;
   lprect->bottom = r.bottom;

}


inline void copy(LPRECTD lprect, const D2D1_RECT_U & r)
{

   lprect->left = r.left;
   lprect->top = r.top;
   lprect->right = r.right;
   lprect->bottom = r.bottom;

}



inline void copy(LPRECTD lprect, const D2D1_RECT_L & r)
{

   lprect->left = r.left;
   lprect->top = r.top;
   lprect->right = r.right;
   lprect->bottom = r.bottom;

}
