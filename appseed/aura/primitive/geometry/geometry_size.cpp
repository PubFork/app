#include "framework.h"






//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//// size
//size::size() NOTHROW
//{
//
//   /* NOT random filled ANYMORE */
//   /* with you want a random filled, or more properly a not explicitly initialized size, pass noinit dummy class as argument */
//
//   cx = 0;
//   cy = 0;
//
//}
//size::size(no_init) NOTHROW
//{
//
//   /* random filled*/
//   /* with you want a random filled, or more properly a not explicitly initialized size, pass noinit dummy class as argument */
//
//}
//size::size(int64_t initCX,int64_t initCY) NOTHROW
//   { cx = (int32_t) initCX; cy = (int32_t) initCY; }
//size::size(SIZE initSize) NOTHROW
//   { *(SIZE*)this = initSize; }
//size::size(const SIZE * pinitSize) NOTHROW
//   { *(SIZE*)this = *pinitSize; }
//size::size(const RECT & rect) NOTHROW
//{
//   cx = width(rect);
//   cy = height(rect);
//}
//size::size(LPCRECT lpcrect) NOTHROW
//{
//   if(lpcrect == NULL)
//   {
//      cx = 0;
//      cy = 0;
//   }
//   else
//   {
//      cx = width(lpcrect);
//      cy = height(lpcrect);
//   }
//}
//size::size(SIZE64  initSize) NOTHROW
//   { cx = (int32_t) initSize.cx; cy = (int32_t) initSize.cy; }
//size::size(const SIZE64 *  pinitSize) NOTHROW
//   { cx = (int32_t) pinitSize->cx; cy = (int32_t) pinitSize->cy; }
//size::size(SIZED  initSize) NOTHROW
//{
//   cx = (int32_t)initSize.cx; cy = (int32_t)initSize.cy;
//}
//size::size(const SIZED *  pinitSize) NOTHROW
//{
//   cx = (int32_t)pinitSize->cx; cy = (int32_t)pinitSize->cy;
//}
//size::size(POINT initPt) NOTHROW
//   { *(POINT*)this = initPt; }
//size::size(uint32_t dwSize) NOTHROW
//   {
//      cx = (int16_t)LOWORD(dwSize);
//      cy = (int16_t)HIWORD(dwSize);
//   }
//
//size::operator SIZE *() NOTHROW
//   { return this; }
//size::operator const SIZE *() const NOTHROW
//   { return this; }
//
//bool size::operator==(SIZE size) const NOTHROW
//   { return (cx == size.cx && cy == size.cy); }
//bool size::operator!=(SIZE size) const NOTHROW
//   { return (cx != size.cx || cy != size.cy); }
//void size::operator+=(SIZE size) NOTHROW
//   { cx += size.cx; cy += size.cy; }
//void size::operator-=(SIZE size) NOTHROW
//   { cx -= size.cx; cy -= size.cy; }
//void size::set_size(int32_t CX, int32_t CY) NOTHROW
//   { cx = CX; cy = CY; }
//class size size::operator+(SIZE size) const NOTHROW
//   {
//      class size sizeRet;
//      sizeRet.cx = cx + size.cx;
//      sizeRet.cy = cy + size.cy;
//      return sizeRet;
//   }
//size size::operator-(SIZE size) const NOTHROW
//   {
//      class size sizeRet;
//      sizeRet.cx = cx - size.cx;
//      sizeRet.cy = cy - size.cy;
//      return sizeRet;
//   }
//size size::operator-() const NOTHROW
//   { return size(-cx, -cy); }
//point size::operator+(POINT point) const NOTHROW
//   {
//      class point pointRet;
//      pointRet.x = cx + point.x;
//      pointRet.y = cy + point.y;
//      return pointRet;
//   }
//point size::operator-(POINT point) const NOTHROW
//   {
//      class point pointRet;
//      pointRet.x = cx - point.x;
//      pointRet.y = cy - point.y;
//      return pointRet;
//   }
//rect size::operator+(LPCRECT lpRect) const NOTHROW
//   { return rect(lpRect) + *this; }
//rect size::operator-(LPCRECT lpRect) const NOTHROW
//   { return rect(lpRect) - *this; }
//
//int64_t size::area() const NOTHROW
//   { return (cx < 0 && cy < 0 ? -1 : 1) * cx * cy; }
//
//uint32_t  size::  u32() const NOTHROW
//{
//
//   return MAKELONG((int32_t) cx, (int32_t) cy);
//
//}
//
//uint64_t  size::  ui64() const NOTHROW
//{
//
//   return MAKELONG64((int32_t) cx, (int32_t) cy);
//
//}
//
//LPARAM    size::lparam() const NOTHROW
//{
//
//   return MAKELPARAM((int32_t) cx, (int32_t) cy);
//
//}





































// size64
size64::size64() NOTHROW
{ /* random filled */ }
size64::size64(int64_t initCX, int64_t initCY) NOTHROW
{ cx = initCX; cy = initCY; }
size64::size64(SIZE64 initSize) NOTHROW
{ *(SIZE64*)this = initSize; }
size64::size64(const SIZE64 * pinitSize) NOTHROW
{ *(SIZE64*)this = *pinitSize; }
size64::size64(POINT64 initPt) NOTHROW
{ *(POINT64*)this = initPt; }
size64::size64(uint64_t dwSize) NOTHROW
{
   cx = (int32_t)LODWORD(dwSize);
   cy = (int32_t)HIDWORD(dwSize);
}

size64::operator SIZE64 *() NOTHROW
{ return this; }
size64::operator const SIZE64 *() const NOTHROW
{ return this; }


bool size64::operator==(SIZE64 size64) const NOTHROW
{ return (cx == size64.cx && cy == size64.cy); }
bool size64::operator!=(SIZE64 size64) const NOTHROW
{ return (cx != size64.cx || cy != size64.cy); }
void size64::operator+=(SIZE64 size64) NOTHROW
{ cx += size64.cx; cy += size64.cy; }
void size64::operator-=(SIZE64 size64) NOTHROW
{ cx -= size64.cx; cy -= size64.cy; }
void size64::set_size(int64_t CX, int64_t CY) NOTHROW
{ cx = CX; cy = CY; }
void size64::set_size(LPCSIZE64 lpcsize) NOTHROW
{
   set_size(lpcsize->cx, lpcsize->cy);
}


size64 size64::operator+(SIZE64 size) const NOTHROW
{ return size64(cx + size.cx, cy + size.cy); }
size64 size64::operator-(SIZE64 size) const NOTHROW
{ return size64(cx - size.cx, cy - size.cy); }
size64 size64::operator-() const NOTHROW
{ return size64(-cx, -cy); }
point64 size64::operator+(POINT64 point) const NOTHROW
{ return point64(cx + point.x, cy + point.y); }
point64 size64::operator-(POINT64 point) const NOTHROW
{ return point64(cx - point.x, cy - point.y); }
rect64 size64::operator+(const RECT64 * lpRect) const NOTHROW
{ return rect64(lpRect) + *this; }
rect64 size64::operator-(const RECT64 * lpRect) const NOTHROW
{ return rect64(lpRect) - *this; }

int64_t size64::area() const NOTHROW
{
   return (cx < 0 && cy < 0 ? -1 : 1) * cx * cy;
}




uint32_t  size64::  u32() const NOTHROW
{

   return MAKELONG((int32_t) cx, (int32_t) cy);

}

uint64_t  size64::  ui64() const NOTHROW
{

   return MAKELONG64((int32_t) cx, (int32_t) cy);

}

LPARAM    size64::lparam() const NOTHROW
{

   return MAKELPARAM((int32_t) cx, (int32_t) cy);

}

























































// sized
sized::sized() NOTHROW
{
   /* random filled */
}
sized::sized(double initCX,double initCY) NOTHROW
{
   cx = initCX; cy = initCY;
}
sized::sized(SIZED initSize) NOTHROW
{
   *(SIZED*)this = initSize;
}
sized::sized(const SIZED * pinitSize) NOTHROW
{
   *(SIZED*)this = *pinitSize;
}
sized::sized(SIZE64  initSize) NOTHROW
{
   cx = (int32_t)initSize.cx; cy = (int32_t)initSize.cy;
}
sized::sized(const SIZE64 *  pinitSize) NOTHROW
{
   cx = (int32_t)pinitSize->cx; cy = (int32_t)pinitSize->cy;
}
sized::sized(SIZE  initSize) NOTHROW
{
   cx = (int32_t)initSize.cx; cy = (int32_t)initSize.cy;
}
sized::sized(const SIZE *  pinitSize) NOTHROW
{
   cx = (int32_t)pinitSize->cx; cy = (int32_t)pinitSize->cy;
}
sized::sized(POINT initPt) NOTHROW
{
   *(POINT*)this = initPt;
}
sized::sized(uint32_t dwSize) NOTHROW
{
   cx = (int16_t)LOWORD(dwSize);
   cy = (int16_t)HIWORD(dwSize);
}

sized::operator SIZED *() NOTHROW
{ return this; }
sized::operator const SIZED *() const NOTHROW
{ return this; }

bool sized::operator==(SIZED sized) const NOTHROW
{ return (cx == sized.cx && cy == sized.cy); }
bool sized::operator!=(SIZED sized) const NOTHROW
{ return (cx != sized.cx || cy != sized.cy); }
void sized::operator+=(SIZED sized) NOTHROW
{ cx += sized.cx; cy += sized.cy; }
void sized::operator-=(SIZED sized) NOTHROW
{ cx -= sized.cx; cy -= sized.cy; }
void sized::set_size(double CX, double CY) NOTHROW
{ cx = CX; cy = CY; }
void sized::set_size(LPCSIZED lpcsize) NOTHROW
{
   set_size(lpcsize->cx, lpcsize->cy);
}
class sized sized::operator+(SIZED sized) const NOTHROW
{
   class sized sizeRet;
   sizeRet.cx = cx + sized.cx;
   sizeRet.cy = cy + sized.cy;
   return sizeRet;
}
sized sized::operator-(SIZED sized) const NOTHROW
{
   class sized sizeRet;
   sizeRet.cx = cx - sized.cx;
   sizeRet.cy = cy - sized.cy;
   return sizeRet;
}
sized sized::operator-() const NOTHROW
{ return sized(-cx, -cy); }
pointd sized::operator+(POINTD pointd) const NOTHROW
{
   class pointd pointRet;
   pointRet.x = cx + pointd.x;
   pointRet.y = cy + pointd.y;
   return pointRet;
}
pointd sized::operator-(POINTD pointd) const NOTHROW
{
   class pointd pointRet;
   pointRet.x = cx - pointd.x;
   pointRet.y = cy - pointd.y;
   return pointRet;
}
rectd sized::operator+(LPCRECTD lpRect) const NOTHROW
{ return rectd(lpRect) + *this; }
rectd sized::operator-(LPCRECTD lpRect) const NOTHROW
{ return rectd(lpRect) - *this; }

double sized::area() const NOTHROW
{
   return (cx < 0.0 && cy < 0.0 ? -1.0 : 1.0) * cx * cy;
}


uint32_t  sized::  u32() const NOTHROW
{

   return MAKELONG((int32_t) cx, (int32_t) cy);

}

uint64_t  sized::  ui64() const NOTHROW
{

   return MAKELONG64((int32_t) cx, (int32_t) cy);

}

LPARAM    sized::lparam() const NOTHROW
{

   return MAKELPARAM((int32_t) cx, (int32_t) cy);

}

