#include "framework.h"


void point::offset(int32_t xOffset, int32_t yOffset) NOTHROW
{ x += xOffset; y += yOffset; }
void point::offset(POINT point) NOTHROW
{ x += point.x; y += point.y; }
void point::offset(SIZE size) NOTHROW
{ x += size.cx; y += size.cy; }
void point::SetPoint(int32_t X, int32_t Y) NOTHROW
{ x = X; y = Y; }
//bool point::operator==(POINT point) const NOTHROW
//   { return (x == point.x && y == point.y); }
//bool point::operator!=(POINT point) const NOTHROW
//   { return (x != point.x || y != point.y); }
//void point::operator+=(SIZE size) NOTHROW
//   { x += size.cx; y += size.cy; }
//void point::operator-=(SIZE size) NOTHROW
//   { x -= size.cx; y -= size.cy; }
//void point::operator+=(POINT point) NOTHROW
//   { x += point.x; y += point.y; }
//void point::operator-=(POINT point) NOTHROW
//   { x -= point.x; y -= point.y; }
//point point::operator+(SIZE size) const NOTHROW
//{ return point(x + size.cx, y + size.cy); }
//point point::operator-(SIZE size) const NOTHROW
//{ return point(x - size.cx, y - size.cy); }
//point point::operator-() const NOTHROW
//{ return point(-x, -y); }
//point point::operator+(POINT pt) const NOTHROW
//{ return point(x +  pt.x, y +  pt.y); }
//size point::operator-(POINT  pt) const NOTHROW
//{ return size(x -  pt.x, y -  pt.y); }
//rect point::operator+(LPCRECT lpRect) const NOTHROW
//{ return rect(lpRect) + *this; }
//rect point::operator-(LPCRECT lpRect) const NOTHROW
//{ return rect(lpRect) - *this; }

uint32_t point::u32() const NOTHROW
{
   return MAKELONG(x, y);
}

uint64_t point::uint64() const NOTHROW
{
   return MAKELONG64(x, y);
}

::lparam point::lparam() const NOTHROW
{
   return MAKELPARAM(x, y);
}








void point64::offset(int64_t xOffset, int64_t yOffset) NOTHROW
{ x += xOffset; y += yOffset; }
void point64::offset(POINT64 point64) NOTHROW
{ x += point64.x; y += point64.y; }
void point64::offset(SIZE64 size64) NOTHROW
{ x += size64.cx; y += size64.cy; }
void point64::SetPoint(int64_t X, int64_t Y) NOTHROW
{ x = X; y = Y; }
bool point64::operator==(POINT64 point64) const NOTHROW
{ return (x == point64.x && y == point64.y); }
bool point64::operator!=(POINT64 point64) const NOTHROW
{ return (x != point64.x || y != point64.y); }
void point64::operator+=(SIZE64 size64) NOTHROW
{ x += size64.cx; y += size64.cy; }
void point64::operator-=(SIZE64 size64) NOTHROW
{ x -= size64.cx; y -= size64.cy; }
void point64::operator+=(POINT64 point64) NOTHROW
{ x += point64.x; y += point64.y; }
void point64::operator-=(POINT64 point64) NOTHROW
{ x -= point64.x; y -= point64.y; }
point64 point64::operator+(SIZE64 size64) const NOTHROW
{ return point64(x + size64.cx, y + size64.cy); }
point64 point64::operator-(SIZE64 size64) const NOTHROW
{ return point64(x - size64.cx, y - size64.cy); }
point64 point64::operator-() const NOTHROW
{ return point64(-x, -y); }
point64 point64::operator+(POINT64 pt) const NOTHROW
{ return point64(x + pt.x, y + pt.y); }
size64 point64::operator-(POINT64 pt) const NOTHROW
{ return size64(x - pt.x, y - pt.y); }
rect64 point64::operator+(const RECT64 * lpRect) const NOTHROW
{ return rect64(lpRect) + *this; }
rect64 point64::operator-(const RECT64 * lpRect) const NOTHROW
{ return rect64(lpRect) - *this; }

uint32_t point64::u32() const NOTHROW
{
   return MAKELONG(x, y);
}

uint64_t point64::ui64() const NOTHROW
{
   return MAKELONG64(x, y);
}

LPARAM point64::lparam() const NOTHROW
{
   return MAKELPARAM(x, y);
}










void pointd::offset(double xOffset, double yOffset) NOTHROW
{ x += xOffset; y += yOffset; }
void pointd::offset(POINTD pointd) NOTHROW
{ x += pointd.x; y += pointd.y; }
void pointd::offset(SIZED size) NOTHROW
{ x += size.cx; y += size.cy; }
void pointd::SetPoint(double X, double Y) NOTHROW
{ x = X; y = Y; }
bool pointd::operator==(POINTD pointd) const NOTHROW
{ return (x == pointd.x && y == pointd.y); }
bool pointd::operator!=(POINTD pointd) const NOTHROW
{ return (x != pointd.x || y != pointd.y); }
void pointd::operator+=(SIZED size) NOTHROW
{ x += size.cx; y += size.cy; }
void pointd::operator-=(SIZED size) NOTHROW
{ x -= size.cx; y -= size.cy; }
void pointd::operator+=(POINTD pointd) NOTHROW
{ x += pointd.x; y += pointd.y; }
void pointd::operator-=(POINTD pointd) NOTHROW
{ x -= pointd.x; y -= pointd.y; }
pointd pointd::operator+(SIZED size) const NOTHROW
{ return pointd(x + size.cx, y + size.cy); }
pointd pointd::operator-(SIZED size) const NOTHROW
{ return pointd(x - size.cx, y - size.cy); }
pointd pointd::operator-() const NOTHROW
{ return pointd(-x, -y); }
pointd pointd::operator+(POINTD pt) const NOTHROW
{ return pointd(x +  pt.x, y +  pt.y); }
sized pointd::operator-(POINTD  pt) const NOTHROW
{ return sized(x -  pt.x, y -  pt.y); }
rectd pointd::operator+(LPCRECTD lpRect) const NOTHROW
{ return rectd(lpRect) + *this; }
rectd pointd::operator-(LPCRECTD lpRect) const NOTHROW
{ return rectd(lpRect) - *this; }

uint32_t pointd::u32() const NOTHROW
{
   return MAKELONG((int32_t) x, (int32_t) y);
}

uint64_t pointd::ui64() const NOTHROW
{
   return MAKELONG64((int32_t) x, (int32_t) y);
}

LPARAM pointd::lparam() const NOTHROW
{
   return MAKELPARAM((int32_t) x, (int32_t) y);
}




point3d point3d::rotate(point3d p)
{

   point3d p1;
   p1.x = x *cos(p.z) - y * sin(p.z) ;
   p1.y = x *sin(p.z) + y * cos(p.z) ;
   p1.z = z;

   point3d p2;
   p2.y = p1.y*cos(p.x) - p1.z * sin(p.x) ;
   p2.z = p1.y *sin(p.x) + p1.z * cos(p.x) ;
   p2.x = p1.x;

   point3d p3;
   p3.z = p2.z *cos(p.y) - p2.x * sin(p.y) ;
   p3.x = p2.z *sin(p.y) + p2.x * cos(p.y) ;
   p3.y = p2.y;

   return p3;
}


