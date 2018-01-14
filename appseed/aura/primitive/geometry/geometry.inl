#pragma once


inline void operator+=(point & p, SIZE size) NOTHROW
{
   p.x += size.cx; p.y += size.cy;
}

inline bool operator==(const point & p, POINT point) NOTHROW
{
   return p.x == point.x && p.y == point.y;
}
inline bool operator!=(const point & p, POINT point) NOTHROW
{
   return !(p == point);
}
inline void operator-=(point & p, SIZE size) NOTHROW
{
   p.x -= size.cx; p.y -= size.cy;
}
inline void operator+=(point & p, POINT point) NOTHROW
{
   p.x += point.x; p.y += point.y;
}
inline void operator-=(point & p, POINT point) NOTHROW
{
   p.x -= point.x; p.y -= point.y;
}

inline point operator+(const point & p, SIZE size) NOTHROW
{
   return point(p.x + size.cx, p.y + size.cy);
}
inline point operator-(const point & p, SIZE size) NOTHROW
{
   return point(p.x - size.cx, p.y - size.cy);
}
inline point operator-(const point & p) NOTHROW
{
   return point(-p.x, -p.y);
}
inline point operator+(const point & p, POINT pt) NOTHROW
{
   return point(p.x + pt.x, p.y + pt.y);
}
inline size operator-(const point & p, POINT  pt) NOTHROW
{
   return size(p.x - pt.x, p.y - pt.y);
}
inline rect operator+(const point & p, LPCRECT lpRect) NOTHROW
{
   return rect(lpRect) + p;
}
inline rect operator-(const point & p, LPCRECT lpRect) NOTHROW
{
   return rect(lpRect) - p;
}
inline bool operator < (const point & p, const point & pt) NOTHROW
{
   return (p.y < pt.y) || ((p.y == pt.y) && (p.x < pt.x));
}


inline point null_point() { return point(0, 0); }
