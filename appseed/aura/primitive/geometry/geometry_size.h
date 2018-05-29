#pragma once


/////////////////////////////////////////////////////////////////////////////
// size - An extent, similar to Windows SIZE structure.

class CLASS_DECL_AURA size : public tagSIZE
{
public:

// Constructors
   // construct an zero-initialized size
   size() NOTHROW;
   // construct an uninitialized size
   size(no_init) NOTHROW;
   // create from two integers
   size(int64_t initCX, int64_t initCY) NOTHROW;
   // create from another size
   size(const SIZE * pinitSize) NOTHROW;
   size(const RECT & rect) NOTHROW;
   size(LPCRECT lpcrect) NOTHROW;
   size(SIZE initSize) NOTHROW;
   size(SIZE64 initSize) NOTHROW;
   size(const SIZE64 * pinitSize) NOTHROW;
   size(SIZED initSize) NOTHROW;
   size(const SIZED * pinitSize) NOTHROW;
   // create from a point
   size(POINT initPt) NOTHROW;
   // create from a uint32_t: cx = LOWORD(dw) cy = HIWORD(dw)
   size(uint32_t dwSize) NOTHROW;

   operator SIZE *() NOTHROW;
   operator const SIZE *() const NOTHROW;


// Operations
   bool operator==(SIZE size) const NOTHROW;
   bool operator!=(SIZE size) const NOTHROW;
   void operator+=(SIZE size) NOTHROW;
   void operator-=(SIZE size) NOTHROW;
   void set_size(LONG CX, LONG CY) NOTHROW;
   void set_size(LPCSIZE lpcsize) NOTHROW;

// Operators returning size values
   size operator+(SIZE size) const NOTHROW;
   size operator-(SIZE size) const NOTHROW;
   size operator-() const NOTHROW;

// Operators returning point values
   point operator+(POINT point) const NOTHROW;
   point operator-(POINT point) const NOTHROW;

// Operators returning rect values
   rect operator+(LPCRECT lpRect) const NOTHROW;
   rect operator-(LPCRECT lpRect) const NOTHROW;

   size operator /(int i);
   size operator /(double d);

   size operator *(int i);
   size operator *(double d);

   size operator +(int i);
   size operator +(double d);

   size operator -(int i);
   size operator -(double d);

   int64_t area() const NOTHROW;
   inline bool is_empty() const NOTHROW;

   uint32_t    u32() const NOTHROW;
   uint64_t    ui64() const NOTHROW;
   LPARAM    lparam() const NOTHROW;
   POINT &        pt() NOTHROW { return (POINT &)*this; }
   const POINT &  pt() const NOTHROW { return (const POINT &)*this; }

   inline LONG get_minimum_dimension() const NOTHROW;
   inline LONG get_maximum_dimension() const NOTHROW;

   inline LONG get_dimension(e_orientation eorientation) const NOTHROW;
   inline LONG get_orthogonal_dimension(e_orientation eorientation) const NOTHROW;
   inline LONG get_orthogonal(e_orientation eorientation)const NOTHROW { return get_orthogonal_dimension(eorientation); }
   inline LONG get_normal_dimension(e_orientation eorientation) const NOTHROW { return get_orthogonal_dimension(eorientation); }
   inline LONG get_normal(e_orientation eorientation) const NOTHROW { return get_orthogonal_dimension(eorientation); }

   inline LONG set_dimension(e_orientation eorientation, LONG l) NOTHROW;
   inline LONG set_orthogonal_dimension(e_orientation eorientation, LONG l) NOTHROW;
   inline LONG set_orthogonal(e_orientation eorientation,LONG l)  NOTHROW{ return set_orthogonal_dimension(eorientation,l); }
   inline LONG set_normal_dimension(e_orientation eorientation,LONG l)  NOTHROW{ return set_orthogonal_dimension(eorientation,l); }
   inline LONG set_normal(e_orientation eorientation,LONG l) NOTHROW { return set_orthogonal_dimension(eorientation,l); }

   inline void set(LONG c) NOTHROW;
   inline void set(LONG cx, LONG cy) NOTHROW;

   inline ::size max(const size & s)const NOTHROW;

   inline static size unit_size() { return ::size(1,1);  }

};


inline bool size::is_empty() const NOTHROW
{
   return cx <= 0 || cy <= 0;
}

/////////////////////////////////////////////////////////////////////////////
// size64 - An extent, similar to Windows SIZE structure.

class CLASS_DECL_AURA size64 : public SIZE64
{
public:

// Constructors
   // construct a zero-initialized size64
   size64() NOTHROW;
   // construct an uninitialized size64
   size64(no_init) NOTHROW;
   // create from two integers
   size64(int64_t initCX, int64_t initCY) NOTHROW;
   // create from another size64
   size64(SIZE64 initSize) NOTHROW;
   size64(const SIZE64 *pinitSize) NOTHROW;
   // create from a point
   size64(POINT64 initPt) NOTHROW;
   // create from a uint32_t: cx = LODWORD(dw) cy = HIDWORD(dw)
   size64(uint64_t dwSize) NOTHROW;


   operator SIZE64 *() NOTHROW;
   operator const SIZE64 *() const NOTHROW;

   operator SIZE() NOTHROW;

// Operations
   bool operator==(SIZE64 size64) const NOTHROW;
   bool operator!=(SIZE64 size64) const NOTHROW;
   void operator+=(SIZE64 size64) NOTHROW;
   void operator-=(SIZE64 size64) NOTHROW;
   void set_size(int64_t CX, int64_t CY) NOTHROW;
   void set_size(LPCSIZE64 lpcsize) NOTHROW;

// Operators returning size64 values
   size64 operator+(SIZE64 size64) const NOTHROW;
   size64 operator-(SIZE64 size64) const NOTHROW;
   size64 operator-() const NOTHROW;

// Operators returning point values
   point64 operator+(POINT64 point) const NOTHROW;
   point64 operator-(POINT64 point) const NOTHROW;

// Operators returning rect values
   rect64 operator+(const RECT64 * lpRect) const NOTHROW;
   rect64 operator-(const RECT64 * lpRect) const NOTHROW;

   int64_t area() const NOTHROW;
   inline bool is_empty() const NOTHROW;

   uint32_t    u32() const NOTHROW;
   uint64_t    ui64() const NOTHROW;
   LPARAM    lparam() const NOTHROW;

   inline int64_t get_minimum_dimension() const NOTHROW;
   inline int64_t get_maximum_dimension() const NOTHROW;


   inline int64_t get_dimension(e_orientation eorientation) const NOTHROW;
   inline int64_t get_orthogonal_dimension(e_orientation eorientation) const NOTHROW;
   inline int64_t get_orthogonal(e_orientation eorientation)const NOTHROW { return get_orthogonal_dimension(eorientation); }
   inline int64_t get_normal_dimension(e_orientation eorientation) const NOTHROW { return get_orthogonal_dimension(eorientation); }
   inline int64_t get_normal(e_orientation eorientation) const NOTHROW { return get_orthogonal_dimension(eorientation); }

   inline int64_t set_dimension(e_orientation eorientation,int64_t l) NOTHROW;
   inline int64_t set_orthogonal_dimension(e_orientation eorientation,int64_t l) NOTHROW;
   inline int64_t set_orthogonal(e_orientation eorientation,int64_t l)  NOTHROW{ return set_orthogonal_dimension(eorientation,l); }
   inline int64_t set_normal_dimension(e_orientation eorientation,int64_t l)  NOTHROW{ return set_orthogonal_dimension(eorientation,l); }
   inline int64_t set_normal(e_orientation eorientation,int64_t l) NOTHROW { return set_orthogonal_dimension(eorientation,l); }

   inline static size64 unit_size() { return ::size64(1ll,1ll); }

};


inline bool size64::is_empty() const NOTHROW
{
   return cx <= 0 || cy <= 0;
}


/////////////////////////////////////////////////////////////////////////////
// sized - An extent, similar to Windows SIZE structure.

class CLASS_DECL_AURA sized : public SIZED
{
public:

// Constructors
   // construct a 0.-initialized sized
   sized() NOTHROW;
   // construct an uninitialized sized
   sized(no_init) NOTHROW;
   // create from two integers
   sized(double initCX, double initCY) NOTHROW;
   // create from another sized
   sized(const SIZED * pinitSize) NOTHROW;
   sized(SIZED initSize) NOTHROW;
   sized(SIZE64 initSize) NOTHROW;
   sized(const SIZE64 * pinitSize) NOTHROW;
   sized(SIZE initSize) NOTHROW;
   sized(const SIZE * pinitSize) NOTHROW;
   // create from a pointd
   sized(POINT initPt) NOTHROW;
   // create from a uint32_t: cx = LOWORD(dw) cy = HIWORD(dw)
   sized(uint32_t dwSize) NOTHROW;

   operator SIZED *() NOTHROW;
   operator const SIZED *() const NOTHROW;

// Operations
   bool operator==(SIZED size) const NOTHROW;
   bool operator!=(SIZED size) const NOTHROW;
   void operator+=(SIZED size) NOTHROW;
   void operator-=(SIZED size) NOTHROW;
   void set_size(double CX, double CY) NOTHROW;
   void set_size(LPCSIZED lpcsize) NOTHROW;

// Operators returning sized values
   sized operator+(SIZED size) const NOTHROW;
   sized operator-(SIZED size) const NOTHROW;
   sized operator-() const NOTHROW;

// Operators returning pointd values
   pointd operator+(POINTD point) const NOTHROW;
   pointd operator-(POINTD point) const NOTHROW;

// Operators returning rectd values
   rectd operator+(LPCRECTD lpRect) const NOTHROW;
   rectd operator-(LPCRECTD lpRect) const NOTHROW;

   double area() const NOTHROW;
   inline bool is_empty() const NOTHROW;

   uint32_t    u32() const NOTHROW;
   uint64_t    ui64() const NOTHROW;
   LPARAM    lparam() const NOTHROW;

   inline double get_minimum_dimension() const NOTHROW;
   inline double get_maximum_dimension() const NOTHROW;


   inline double get_dimension(e_orientation eorientation) const NOTHROW;
   inline double get_orthogonal_dimension(e_orientation eorientation) const NOTHROW;
   inline double get_orthogonal(e_orientation eorientation)const NOTHROW { return get_orthogonal_dimension(eorientation); }
   inline double get_normal_dimension(e_orientation eorientation) const NOTHROW { return get_orthogonal_dimension(eorientation); }
   inline double get_normal(e_orientation eorientation) const NOTHROW { return get_orthogonal_dimension(eorientation); }

   inline double set_dimension(e_orientation eorientation,double l) NOTHROW;
   inline double set_orthogonal_dimension(e_orientation eorientation,double l) NOTHROW;
   inline double set_orthogonal(e_orientation eorientation,double l)  NOTHROW{ return set_orthogonal_dimension(eorientation,l); }
   inline double set_normal_dimension(e_orientation eorientation,double l)  NOTHROW{ return set_orthogonal_dimension(eorientation,l); }
   inline double set_normal(e_orientation eorientation,double l) NOTHROW { return set_orthogonal_dimension(eorientation,l); }

   inline static sized unit_size() { return ::sized(1.0,1.0); }

};


inline bool sized::is_empty() const NOTHROW
{
   return cx <= 0 || cy <= 0;
}

inline LONG size::get_minimum_dimension() const NOTHROW
{

   return MIN(cx, cy);

}


inline LONG size::get_maximum_dimension() const NOTHROW
{

   return MAX(cx, cy);

}

inline LONG size::get_dimension(e_orientation eorientation) const NOTHROW
{
   if(eorientation == orientation_horizontal)
   {
      return cx;
   }
   else if(eorientation == orientation_vertical)
   {
      return cy;
   }
   else
   {
      return 0;
   }
}


inline ::size size::max(const ::size & s) const NOTHROW
{

   return ::size(MAX(cx,s.cx),MAX(cy,s.cy));

}


inline LONG size::get_orthogonal_dimension(e_orientation eorientation) const NOTHROW
{
   if(eorientation == orientation_horizontal)
   {
      return cy;
   }
   else if(eorientation == orientation_vertical)
   {
      return cx;
   }
   else
   {
      return 0;
   }
}

inline void size::set(LONG c) NOTHROW
{

   cx = c;

   cy = c;

}
inline void size::set(LONG cxParam, LONG cyParam) NOTHROW
{

   cx = cxParam;

   cy = cyParam;

}

inline LONG size::set_dimension(e_orientation eorientation, LONG l) NOTHROW
{
   if(eorientation == orientation_horizontal)
   {
      return cx = l;
   }
   else if(eorientation == orientation_vertical)
   {
      return cy = l;
   }
   else
   {
      return 0;
   }
}


inline LONG size::set_orthogonal_dimension(e_orientation eorientation, LONG l) NOTHROW
{
   if(eorientation == orientation_horizontal)
   {
      return cy = l;
   }
   else if(eorientation == orientation_vertical)
   {
      return cx = l;
   }
   else
   {
      return 0;
   }
}

inline int64_t size64::get_minimum_dimension() const NOTHROW
{

   return MIN(cx, cy);

}

inline int64_t size64::get_maximum_dimension() const NOTHROW
{

   return MAX(cx, cy);

}


inline int64_t size64::get_dimension(e_orientation eorientation) const NOTHROW
{
   if(eorientation == orientation_horizontal)
   {
      return cx;
   }
   else if(eorientation == orientation_vertical)
   {
      return cy;
   }
   else
   {
      return 0;
   }
}


inline int64_t size64::get_orthogonal_dimension(e_orientation eorientation) const NOTHROW
{
   if(eorientation == orientation_horizontal)
   {
      return cy;
   }
   else if(eorientation == orientation_vertical)
   {
      return cx;
   }
   else
   {
      return 0;
   }
}


inline int64_t size64::set_dimension(e_orientation eorientation,int64_t l) NOTHROW
{
   if(eorientation == orientation_horizontal)
   {
      return cx = l;
   }
   else if(eorientation == orientation_vertical)
   {
      return cy = l;
   }
   else
   {
      return 0;
   }
}


inline int64_t size64::set_orthogonal_dimension(e_orientation eorientation,int64_t l) NOTHROW
{
   if(eorientation == orientation_horizontal)
   {
      return cy = l;
   }
   else if(eorientation == orientation_vertical)
   {
      return cx = l;
   }
   else
   {
      return 0;
   }
}

inline double sized::get_minimum_dimension() const NOTHROW
{

   return MIN(cx, cy);

}

inline double sized::get_maximum_dimension() const NOTHROW
{

   return MAX(cx, cy);

}

inline double sized::get_dimension(e_orientation eorientation) const NOTHROW
{
   if(eorientation == orientation_horizontal)
   {
      return cx;
   }
   else if(eorientation == orientation_vertical)
   {
      return cy;
   }
   else
   {
      return 0;
   }
}


inline double sized::get_orthogonal_dimension(e_orientation eorientation) const NOTHROW
{
   if(eorientation == orientation_horizontal)
   {
      return cy;
   }
   else if(eorientation == orientation_vertical)
   {
      return cx;
   }
   else
   {
      return 0;
   }
}


inline double sized::set_dimension(e_orientation eorientation,double l) NOTHROW
{
   if(eorientation == orientation_horizontal)
   {
      return cx = l;
   }
   else if(eorientation == orientation_vertical)
   {
      return cy = l;
   }
   else
   {
      return 0;
   }
}


inline double sized::set_orthogonal_dimension(e_orientation eorientation,double l) NOTHROW
{
   if(eorientation == orientation_horizontal)
   {
      return cy = l;
   }
   else if(eorientation == orientation_vertical)
   {
      return cx = l;
   }
   else
   {
      return 0;
   }
}



template<> inline UINT HashKey<size> (size key)
{
   return key.cx | key.cy;
}




