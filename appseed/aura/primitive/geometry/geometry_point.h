#pragma once


class CLASS_DECL_AURA point : public POINT
{
public:

   typedef POINT BASE;

   typedef LONG TYPE;

   typedef ::LPRECT LPRECT;

   typedef ::rect RECT;

   typedef ::size SIZE;

   point() NOTHROW {}
   point(i64 a, i64 b) NOTHROW { x = (LONG) a; y = (LONG)b; }
   point(const POINT & pt) NOTHROW { *(POINT *)this = pt; }
explicit point(const ::lparam & lparam) NOTHROW:point(lparam.x(), lparam.y()) {}

point(const POINTD & pt) NOTHROW : point(pt.x, pt.y) {}
point(const POINT64 & pt) NOTHROW : point(pt.x, pt.y) {}
point(const SIZE & sz) NOTHROW : point((const POINT*)&sz) {}
point(const SIZED & sz) NOTHROW : point((const POINTD*)&sz) {}
point(const SIZE64 & sz) NOTHROW : point((const POINT64*)&sz) {}
point(const POINT * ppt) NOTHROW : point(*ppt) {}
point(const POINTD * ppt) NOTHROW : point(*ppt) {}
point(const POINT64 * ppt) NOTHROW : point(*ppt) {}
point(const SIZE * psz) NOTHROW : point(*psz) {}
point(const SIZED * psz) NOTHROW : point(*psz) {}
point(const SIZE64 * psz) NOTHROW : point(*psz) {}

   operator POINT *() NOTHROW { return this; }
   operator const POINT *() const NOTHROW { return this; }
   operator ::lparam() const { return lparam(); }

   uint32_t u32() const NOTHROW;
   uint64_t uint64() const NOTHROW;
   ::lparam lparam() const NOTHROW;


   void offset(int32_t xOffset, int32_t yOffset) NOTHROW;
   void offset(POINT point) NOTHROW;
   void offset(SIZE size) NOTHROW;
   void SetPoint(int32_t X, int32_t Y) NOTHROW;



   inline LONG get_dimension(e_orientation eorientation) const NOTHROW;
   inline LONG get_orthogonal_dimension(e_orientation eorientation) const NOTHROW;
   inline LONG get_orthogonal(e_orientation eorientation)const NOTHROW { return get_orthogonal_dimension(eorientation); }
   inline LONG get_normal_dimension(e_orientation eorientation) const NOTHROW { return get_orthogonal_dimension(eorientation); }
   inline LONG get_normal(e_orientation eorientation) const NOTHROW { return get_orthogonal_dimension(eorientation); }

   inline LONG set_dimension(e_orientation eorientation,LONG l) NOTHROW;
   inline LONG set_orthogonal_dimension(e_orientation eorientation,LONG l) NOTHROW;
   inline LONG set_orthogonal(e_orientation eorientation,LONG l)  NOTHROW { return set_orthogonal_dimension(eorientation,l); }
   inline LONG set_normal_dimension(e_orientation eorientation,LONG l)  NOTHROW { return set_orthogonal_dimension(eorientation,l); }
   inline LONG set_normal(e_orientation eorientation,LONG l) NOTHROW { return set_orthogonal_dimension(eorientation,l); }

};


inline void operator+=(point & p, SIZE size) NOTHROW;
inline bool operator==(const point & p, POINT point) NOTHROW;
inline bool operator!=(const point & p, POINT point) NOTHROW;
inline void operator-=(point & p, SIZE size) NOTHROW;
inline void operator+=(point & p, POINT point) NOTHROW;
inline void operator-=(point & p, POINT point) NOTHROW;
inline point operator+(const point & p, SIZE size) NOTHROW;
inline point operator-(const point & p, SIZE size) NOTHROW;
inline point operator-(const point & p) NOTHROW;
inline point operator+(const point & p, POINT pt) NOTHROW;
inline size operator-(const point & p, POINT  pt) NOTHROW;
inline rect operator+(const point & p, LPCRECT lpRect) NOTHROW;
inline rect operator-(const point & p, LPCRECT lpRect) NOTHROW;
inline bool operator < (const point & p, const point & pt) NOTHROW;

inline point null_point();


class CLASS_DECL_AURA point64 : public POINT64
{
public:


   typedef POINT64 BASE;

   typedef int64_t TYPE;

   typedef ::LPRECT64 LPRECT;

   typedef ::rect64 RECT;

   typedef ::size64 SIZE;

   point64() NOTHROW {}
   point64(i64 a, i64 b) NOTHROW { x = a; y = b; }
   point64(const POINT64 & pt) NOTHROW { *(POINT64*)this = pt; }
explicit point64(const ::lparam & lparam) NOTHROW : point64(lparam.x(), lparam.y()) {}

point64(const POINT & pt) NOTHROW : point64(pt.x, pt.y) {}
point64(const POINTD & pt) NOTHROW : point64(pt.x, pt.y) {}
point64(const SIZE & sz) NOTHROW : point64((const POINT*)&sz) {}
point64(const SIZED & sz) NOTHROW : point64((const POINTD*)&sz) {}
point64(const SIZE64 & sz) NOTHROW : point64((const POINT64*)&sz) {}
point64(const POINT * ppt) NOTHROW : point64(*ppt) {}
point64(const POINTD * ppt) NOTHROW : point64(*ppt) {}
point64(const POINT64 * ppt) NOTHROW : point64(*ppt) {}
point64(const SIZE * psz) NOTHROW : point64(*psz) {}
point64(const SIZED * psz) NOTHROW : point64(*psz) {}
point64(const SIZE64 * psz) NOTHROW : point64(*psz) {}


   operator POINT64 *() NOTHROW { return this; }
   operator const POINT64 *() const NOTHROW { return this; }

// Operations

// translate the point64
   void offset(int64_t xOffset, int64_t yOffset) NOTHROW;
   void offset(POINT64 point64) NOTHROW;
   void offset(SIZE64 size) NOTHROW;
   void SetPoint(int64_t X, int64_t Y) NOTHROW;

   bool operator==(POINT64 point64) const NOTHROW;
   bool operator!=(POINT64 point64) const NOTHROW;
   void operator+=(SIZE64 size) NOTHROW;
   void operator-=(SIZE64 size) NOTHROW;
   void operator+=(POINT64 point64) NOTHROW;
   void operator-=(POINT64 point64) NOTHROW;

// Operators returning point64 values
   point64 operator+(SIZE64 size) const NOTHROW;
   point64 operator-(SIZE64 size) const NOTHROW;
   point64 operator-() const NOTHROW;
   point64 operator+(POINT64 point64) const NOTHROW;

// Operators returning size values
   size64 operator-(POINT64 point64) const NOTHROW;

// Operators returning rect values
   rect64 operator+(const RECT64 * lpRect) const NOTHROW;
   rect64 operator-(const RECT64 * lpRect) const NOTHROW;

   uint32_t u32() const NOTHROW;
   uint64_t ui64() const NOTHROW;
   LPARAM   lparam() const NOTHROW;

   inline int64_t get_dimension(e_orientation eorientation) const NOTHROW;
   inline int64_t get_orthogonal_dimension(e_orientation eorientation) const NOTHROW;
   inline int64_t get_orthogonal(e_orientation eorientation)const NOTHROW { return get_orthogonal_dimension(eorientation); }
   inline int64_t get_normal_dimension(e_orientation eorientation) const NOTHROW { return get_orthogonal_dimension(eorientation); }
   inline int64_t get_normal(e_orientation eorientation) const NOTHROW { return get_orthogonal_dimension(eorientation); }

   inline int64_t set_dimension(e_orientation eorientation,int64_t l) NOTHROW;
   inline int64_t set_orthogonal_dimension(e_orientation eorientation,int64_t l) NOTHROW;
   inline int64_t set_orthogonal(e_orientation eorientation,int64_t l)  NOTHROW { return set_orthogonal_dimension(eorientation,l); }
   inline int64_t set_normal_dimension(e_orientation eorientation,int64_t l)  NOTHROW { return set_orthogonal_dimension(eorientation,l); }
   inline int64_t set_normal(e_orientation eorientation,int64_t l) NOTHROW { return set_orthogonal_dimension(eorientation,l); }


};




class CLASS_DECL_AURA pointd : public POINTD
{
public:

   typedef POINTD BASE;

   typedef double TYPE;

   typedef ::LPRECTD LPRECT;

   typedef ::rectd RECT;

   typedef ::sized SIZE;

   pointd() NOTHROW {}
   pointd(double a, double b) NOTHROW { x = a; y = b; }
   pointd(const POINTD & pt) NOTHROW { *(POINTD*)this = pt; }
explicit pointd(const lparam & lparam) NOTHROW :pointd(lparam.x(), lparam.y()) {}

pointd(const POINT & pt) NOTHROW : pointd(pt.x, pt.y) {}
pointd(const POINT64 & pt) NOTHROW : pointd(pt.x, pt.y) {}
   pointd(const SIZE & sz) NOTHROW;
pointd(const SIZED & sz) NOTHROW : pointd((const POINTD*)&sz) {}
   pointd(const SIZE64 & sz) NOTHROW;
pointd(const POINT * ppt) NOTHROW : pointd(*ppt) {}
pointd(const POINTD * ppt) NOTHROW : pointd(*ppt) {}
pointd(const POINT64 * ppt) NOTHROW : pointd(*ppt) {}
pointd(const SIZE * psz) NOTHROW : pointd(*psz) {}
pointd(const SIZED * psz) NOTHROW : pointd(*psz) {}
pointd(const SIZE64 * psz) NOTHROW : pointd(*psz) {}

   operator POINTD *() NOTHROW { return this; }
   operator const POINTD *() const NOTHROW { return this; }

// Operations

// translate the pointd
   void offset(double xOffset, double yOffset) NOTHROW;
   void offset(POINTD pointd) NOTHROW;
   void offset(SIZED sized) NOTHROW;
   void SetPoint(double X, double Y) NOTHROW;

   bool operator==(POINTD pointd) const NOTHROW;
   bool operator!=(POINTD pointd) const NOTHROW;
   void operator+=(SIZED sized) NOTHROW;
   void operator-=(SIZED sized) NOTHROW;
   void operator+=(POINTD pointd) NOTHROW;
   void operator-=(POINTD pointd) NOTHROW;

// Operators returning pointd values
   pointd operator+(SIZED sized) const NOTHROW;
   pointd operator-(SIZED sized) const NOTHROW;
   pointd operator-() const NOTHROW;
   pointd operator+(POINTD pointd) const NOTHROW;

// Operators returning sized values
   sized operator-(POINTD pointd) const NOTHROW;

// Operators returning rectd values
   rectd operator+(LPCRECTD lpRect) const NOTHROW;
   rectd operator-(LPCRECTD lpRect) const NOTHROW;

   uint32_t u32() const NOTHROW;
   uint64_t ui64() const NOTHROW;
   LPARAM   lparam() const NOTHROW;

   inline double get_dimension(e_orientation eorientation) const NOTHROW;
   inline double get_orthogonal_dimension(e_orientation eorientation) const NOTHROW;
   inline double get_orthogonal(e_orientation eorientation)const NOTHROW { return get_orthogonal_dimension(eorientation); }
   inline double get_normal_dimension(e_orientation eorientation) const NOTHROW { return get_orthogonal_dimension(eorientation); }
   inline double get_normal(e_orientation eorientation) const NOTHROW { return get_orthogonal_dimension(eorientation); }

   inline double set_dimension(e_orientation eorientation,double l) NOTHROW;
   inline double set_orthogonal_dimension(e_orientation eorientation,double l) NOTHROW;
   inline double set_orthogonal(e_orientation eorientation,double l)  NOTHROW { return set_orthogonal_dimension(eorientation,l); }
   inline double set_normal_dimension(e_orientation eorientation,double l)  NOTHROW { return set_orthogonal_dimension(eorientation,l); }
   inline double set_normal(e_orientation eorientation,double l) NOTHROW { return set_orthogonal_dimension(eorientation,l); }

};


inline pointd null_pointd() { return pointd(0.0, 0.0); }



inline LONG point::get_dimension(e_orientation eorientation) const NOTHROW
{
   if(eorientation == orientation_horizontal)
   {
      return x;
   }
   else if(eorientation == orientation_vertical)
   {
      return y;
   }
   else
   {
      return 0;
   }
}


inline LONG point::get_orthogonal_dimension(e_orientation eorientation) const NOTHROW
{
   if(eorientation == orientation_horizontal)
   {
      return y;
   }
   else if(eorientation == orientation_vertical)
   {
      return x;
   }
   else
   {
      return 0;
   }
}


inline LONG point::set_dimension(e_orientation eorientation,LONG l) NOTHROW
{
   if(eorientation == orientation_horizontal)
   {
      return x = l;
   }
   else if(eorientation == orientation_vertical)
   {
      return y = l;
   }
   else
   {
      return 0;
   }
}


inline LONG point::set_orthogonal_dimension(e_orientation eorientation,LONG l) NOTHROW
{
   if(eorientation == orientation_horizontal)
   {
      return y = l;
   }
   else if(eorientation == orientation_vertical)
   {
      return x = l;
   }
   else
   {
      return 0;
   }
}



inline int64_t point64::get_dimension(e_orientation eorientation) const NOTHROW
{
   if(eorientation == orientation_horizontal)
   {
      return x;
   }
   else if(eorientation == orientation_vertical)
   {
      return y;
   }
   else
   {
      return 0;
   }
}


inline int64_t point64::get_orthogonal_dimension(e_orientation eorientation) const NOTHROW
{
   if(eorientation == orientation_horizontal)
   {
      return y;
   }
   else if(eorientation == orientation_vertical)
   {
      return x;
   }
   else
   {
      return 0;
   }
}


inline int64_t point64::set_dimension(e_orientation eorientation,int64_t l) NOTHROW
{
   if(eorientation == orientation_horizontal)
   {
      return x = l;
   }
   else if(eorientation == orientation_vertical)
   {
      return y = l;
   }
   else
   {
      return 0;
   }
}


inline int64_t point64::set_orthogonal_dimension(e_orientation eorientation,int64_t l) NOTHROW
{
   if(eorientation == orientation_horizontal)
   {
      return y = l;
   }
   else if(eorientation == orientation_vertical)
   {
      return x = l;
   }
   else
   {
      return 0;
   }
}


inline double pointd::get_dimension(e_orientation eorientation) const NOTHROW
{
   if(eorientation == orientation_horizontal)
   {
      return x;
   }
   else if(eorientation == orientation_vertical)
   {
      return y;
   }
   else
   {
      return 0;
   }
}


inline double pointd::get_orthogonal_dimension(e_orientation eorientation) const NOTHROW
{
   if(eorientation == orientation_horizontal)
   {
      return y;
   }
   else if(eorientation == orientation_vertical)
   {
      return x;
   }
   else
   {
      return 0;
   }
}


inline double pointd::set_dimension(e_orientation eorientation,double l) NOTHROW
{
   if(eorientation == orientation_horizontal)
   {
      return x = l;
   }
   else if(eorientation == orientation_vertical)
   {
      return y = l;
   }
   else
   {
      return 0;
   }
}


inline double pointd::set_orthogonal_dimension(e_orientation eorientation,double l) NOTHROW
{
   if(eorientation == orientation_horizontal)
   {
      return y = l;
   }
   else if(eorientation == orientation_vertical)
   {
      return x = l;
   }
   else
   {
      return 0;
   }
}



template<> inline UINT HashKey<point> (point key)
{
   return key.x | key.y;
}



struct CLASS_DECL_AURA POINT3D
{
   double x;
   double y;
   double z;
};

using LPPOINT3D = POINT3D * ;
using LPCPOINT3D = const POINT3D *;

class CLASS_DECL_AURA point3d:
   public POINT3D
{
public:

   point3d() {}
   point3d(double xP,double yP,double zP) { x = xP; y=yP; z=zP; }

   point3d  operator +(const point3d &p1) const
   {
      point3d p;
      p.x =x + p1.x;
      p.y =y + p1.y;
      p.z =z + p1.z;
      return p;
   }
   point3d & operator +=(const point3d &p)
   {
      x += p.x;
      y += p.y;
      z += p.z;
      return *this;
   }

   point3d & operator -=(const point3d &p)
   {
      x -= p.x;
      y -= p.y;
      z -= p.z;
      return *this;
   }

   point3d & operator = (const point3d & p)
   {
      x = p.x;
      y = p.y;
      z = p.z;
      return *this;
   }

   point3d rotate(point3d d);

   operator LPPOINT3D() { return this; }
   operator LPCPOINT3D() const { return this; }

};



inline point pointxy(LPCPOINT3D lppt)
{
   return point(lppt->x, lppt->y);
}
