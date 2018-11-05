


















// size
inline size::size() NOTHROW
{

   /* NOT random filled ANYMORE */
   /* with you want a random filled, or more properly a not explicitly initialized size, pass noinit dummy class as argument */

   cx = 0;
   cy = 0;

}


inline size::size(no_init) NOTHROW
{

   /* random filled*/
   /* with you want a random filled, or more properly a not explicitly initialized size, pass noinit dummy class as argument */

}


inline size::size(int64_t initCX,int64_t initCY) NOTHROW
{

   cx = (int32_t)initCX;

   cy = (int32_t)initCY;

}


inline size::size(SIZE initSize) NOTHROW
{

   *(SIZE*)this = initSize;

}


inline size::size(const SIZE * pinitSize) NOTHROW
{

   *this = *pinitSize;

}


inline size::size(const RECT & rect) NOTHROW
{

   cx = width(rect);

   cy = height(rect);

}


inline size::size(LPCRECT lpcrect) NOTHROW
{

   if(lpcrect == NULL)
   {

      cx = 0;

      cy = 0;

   }
   else
   {

      cx = width(lpcrect);

      cy = height(lpcrect);

   }

}


inline size::size(SIZE64  initSize) NOTHROW
{

   cx = (int32_t)initSize.cx;

   cy = (int32_t)initSize.cy;

}


inline size::size(const SIZE64 *  pinitSize) NOTHROW
{

   cx = (int32_t)pinitSize->cx;

   cy = (int32_t)pinitSize->cy;

}


inline size::size(SIZED  initSize) NOTHROW
{

   cx = (int32_t)initSize.cx;

   cy = (int32_t)initSize.cy;

}


inline size::size(const SIZED *  pinitSize) NOTHROW
{

   cx = (int32_t)pinitSize->cx;

   cy = (int32_t)pinitSize->cy;

}


inline size::size(POINT initPt) NOTHROW
{

   *(POINT*)this = initPt;

}


inline size::size(uint32_t dwSize) NOTHROW
{

   cx = (int16_t)LOWORD(dwSize);

   cy = (int16_t)HIWORD(dwSize);

}


inline size::operator SIZE *() NOTHROW
{

   return this;

}


inline size::operator const SIZE *() const NOTHROW
{

   return this;

}


inline bool size::operator==(SIZE size) const NOTHROW
{

   return (cx == size.cx && cy == size.cy);

}


inline bool size::operator!=(SIZE size) const NOTHROW
{

   return (cx != size.cx || cy != size.cy);

}


inline void size::operator+=(SIZE size) NOTHROW
{

   cx += size.cx;

   cy += size.cy;

}


inline void size::operator-=(SIZE size) NOTHROW
{

   cx -= size.cx;

   cy -= size.cy;

}

inline void size::set_size(LONG CX, LONG CY) NOTHROW
{

   cx = CX;

   cy = CY;

}


inline void size::set_size(LPCSIZE lpcsize) NOTHROW
{

   set_size(lpcsize->cx, lpcsize->cy);

}


inline class size size::operator+(SIZE size) const NOTHROW
{

   class size sizeRet;

   sizeRet.cx = cx + size.cx;

   sizeRet.cy = cy + size.cy;

   return sizeRet;

}


inline size size::operator-(SIZE size) const NOTHROW
{

   class size sizeRet;

   sizeRet.cx = cx - size.cx;

   sizeRet.cy = cy - size.cy;

   return sizeRet;

}


inline size size::operator-() const NOTHROW
{

   return size(-cx,-cy);

}


inline point size::operator+(POINT point) const NOTHROW
{

   class point pointRet;

   pointRet.x = cx + point.x;

   pointRet.y = cy + point.y;

   return pointRet;

}


inline point size::operator-(POINT point) const NOTHROW
{

   class point pointRet;

   pointRet.x = cx - point.x;

   pointRet.y = cy - point.y;

   return pointRet;

}


inline rect size::operator+(LPCRECT lpRect) const NOTHROW
{

   return rect(lpRect) + *this;

}


inline rect size::operator-(LPCRECT lpRect) const NOTHROW
{

   return rect(lpRect) - *this;

}


inline int64_t size::area() const NOTHROW
{

   return (cx < 0 && cy < 0 ? -1 : 1) * cx * cy;

}


inline uint32_t  size::  u32() const NOTHROW
{

   return MAKELONG((int32_t)cx,(int32_t)cy);

}


inline uint64_t  size::  ui64() const NOTHROW
{

   return MAKELONG64((int32_t)cx,(int32_t)cy);

}


inline LPARAM    size::lparam() const NOTHROW
{

   return MAKELPARAM((int32_t)cx,(int32_t)cy);

}




inline size64::operator SIZE() NOTHROW
{

   SIZE sz = { (LONG)cx, (LONG)cy };

   return sz;

}

inline size size::operator /(int i) { return size(cx / i, cy / i); }
inline size size::operator /(double d) { return size((int64_t)(cx / d), (int64_t)(cy / d)); }

inline size size::operator *(int i) { return size(cx * i, cy * i); }
inline size size::operator *(double d) { return size((int64_t)(cx * d), (int64_t)(cy * d)); }

inline size size::operator +(int i) { return size(cx + i, cy + i); }
inline size size::operator +(double d) { return size((int64_t)(cx + d), (int64_t)(cy + d)); }

inline size size::operator -(int i) { return size(cx - i, cy - i); }
inline size size::operator -(double d) { return size((int64_t)(cx - d), (int64_t)(cy - d)); }





inline sized sized::operator /(double d) { return sized((cx / d), (cy / d)); }
