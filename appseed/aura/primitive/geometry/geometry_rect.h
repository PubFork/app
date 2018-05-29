#pragma once


class point_array;


/////////////////////////////////////////////////////////////////////////////
// rect - A 2-D rectangle, similar to Windows RECT structure.

class CLASS_DECL_AURA rect : public tagRECT
{
public:


   rect() NOTHROW {}
   rect(i64 l, int64_t t, int64_t r, int64_t b) NOTHROW { left = l; top = t; right = r;  bottom = b;  }
   rect(const RECT & r) NOTHROW { *this = r; }

rect(const RECTD & r) NOTHROW : rect(r.left, r.top, r.right, r.bottom) {}
rect(const RECT64 & r) NOTHROW : rect(r.left, r.top, r.right, r.bottom) {}
rect(const RECT * prect) NOTHROW : rect(*prect) {}
rect(const RECTD * prect) NOTHROW : rect(*prect) {}
rect(const RECT64 * prect) NOTHROW : rect(*prect) {}
rect(point pt, size sz) NOTHROW : rect(pt.x, pt.y, pt.x + sz.cx, pt.y + sz.cy) {}
rect(size sz, point pt = null_point()) NOTHROW : rect(pt, sz) {}
rect(point ptTopLeft, point ptBottomRight) NOTHROW : rect(ptTopLeft.x, ptTopLeft.y, ptBottomRight.x, ptBottomRight.y) {}

// Attributes (in addition to RECT members)

   // retrieves the width
   int32_t width() const NOTHROW;
   // returns the height
   int32_t height() const NOTHROW;
   // returns the sizeF
   class ::size get_size() const NOTHROW;
   void set_size(LONG cx, LONG cy) NOTHROW;
   void set_size(LPCSIZE psz) NOTHROW;
   // reference to the top-left point
   point& top_left() NOTHROW;
   // reference to the bottom-right point
   point& bottom_right() NOTHROW;
   // const reference to the top-left point
   const point& top_left() const NOTHROW;
   // const reference to the bottom-right point
   const point& bottom_right() const NOTHROW;
   // the geometric center point of the rectangle
   point center() const NOTHROW;
   // swap the left and right
   void swap_left_right() NOTHROW;
   static void WINAPI swap_left_right(LPRECT lpRect) NOTHROW;

   // convert between rect and LPRECT/LPCRECT (no need for &)
   operator LPRECT() NOTHROW;
   operator LPCRECT() const NOTHROW;

   // returns TRUE if rectangle has no area
   bool is_empty() const NOTHROW;
   // returns TRUE if rectangle is at (0,0) and has no area
   bool is_null() const NOTHROW;
   // returns TRUE if point is within rectangle
   bool contains(POINT point) const NOTHROW;

// Operations

   // set rectangle from left, top, right, and bottom
   void set(int32_t i) NOTHROW;
   void set(int32_t x, int32_t y) NOTHROW;
   void set(int32_t x1, int32_t y1, int32_t x2, int32_t y2) NOTHROW;
   void set(POINT topLeft, POINT bottomRight) NOTHROW;
   // is_empty the rectangle
   void null() NOTHROW;
   // copy from another rectangle
   void copy(LPCRECT lpSrcRect) NOTHROW;
   // TRUE if exactly the same as another rectangle
   bool is_equal(LPCRECT lpRect) const NOTHROW;

   // Inflate rectangle's width and height by
   // x units to the left and right ends of the rectangle
   // and y units to the top and bottom.
   void inflate(int32_t x, int32_t y) NOTHROW;
   // Inflate rectangle's width and height by
   // size.cx units to the left and right ends of the rectangle
   // and size.cy units to the top and bottom.
   void inflate(SIZE size) NOTHROW;
   // Inflate rectangle's width and height by moving individual sides.
   // Left side is moved to the left, right side is moved to the right,
   // top is moved up and bottom is moved down.
   void inflate(LPCRECT lpRect) NOTHROW;
   void inflate(int32_t l, int32_t t, int32_t r, int32_t b) NOTHROW;

   // deflate the rectangle's width and height without
   // moving its top or left
   void deflate(int32_t x, int32_t y) NOTHROW;
   void deflate(SIZE size) NOTHROW;
   void deflate(LPCRECT lpRect) NOTHROW;
   void deflate(int32_t l, int32_t t, int32_t r, int32_t b) NOTHROW;

   // translate the rectangle by moving its top and left
   void offset(int32_t x, int32_t y) NOTHROW;
   void offset(SIZE size) NOTHROW;
   void offset(POINT point) NOTHROW;
   void normalize() NOTHROW;

   // absolute position of rectangle
   void move_to_y(int32_t y) NOTHROW;
   void move_to_x(int32_t x) NOTHROW;
   void move_to(int32_t x, int32_t y) NOTHROW;
   void move_to(POINT point) NOTHROW;

   // set this rectangle to intersection of two others
   bool intersect_x(LPCRECT lpRect1,LPCRECT lpRect2) NOTHROW;
   bool intersect_y(LPCRECT lpRect1,LPCRECT lpRect2) NOTHROW;
   bool intersect(LPCRECT lpRect1, LPCRECT lpRect2) NOTHROW;
   bool intersects_x(LPCRECT lpRect) const NOTHROW;
   bool intersects_y(LPCRECT lpRect) const NOTHROW;
   bool intersects(LPCRECT lpRect) const NOTHROW;
   rect & intersect(LPCRECT lpRect2) NOTHROW;
   rect intersect(LPCRECT lpRect2) const NOTHROW;

   bool null_intersect(LPCRECT lpRect1,LPCRECT lpRect2) NOTHROW;

   bool top_left_null_intersect(LPCRECT lpRect1,LPCRECT lpRect2) NOTHROW;

   // set this rectangle to bounding union of two others
   bool unite(LPCRECT lpRect1, LPCRECT lpRect2) NOTHROW;

   // set this rectangle to minimum of two others
   bool subtract(LPCRECT lpRectSrc1, LPCRECT lpRectSrc2) NOTHROW;

// Additional Operations
   void operator=(const RECT& srcRect) NOTHROW;
   bool operator==(const RECT& rect) const NOTHROW;
   bool operator!=(const RECT& rect) const NOTHROW;
   void operator+=(POINT point) NOTHROW;
   void operator+=(SIZE size) NOTHROW;
   void operator+=(LPCRECT lpRect) NOTHROW;
   void operator-=(POINT point) NOTHROW;
   void operator-=(SIZE size) NOTHROW;
   void operator-=(LPCRECT lpRect) NOTHROW;
   void operator&=(const RECT& rect) NOTHROW;
   void operator|=(const RECT& rect) NOTHROW;

// Operators returning rect values
   rect operator+(POINT point) const NOTHROW;
   rect operator-(POINT point) const NOTHROW;
   rect operator+(LPCRECT lpRect) const NOTHROW;
   rect operator+(SIZE size) const NOTHROW;
   rect operator-(SIZE size) const NOTHROW;
   rect operator-(LPCRECT lpRect) const NOTHROW;
   rect operator&(const RECT& rect2) const NOTHROW;
   rect operator|(const RECT& rect2) const NOTHROW;
   rect MulDiv(int32_t nMultiplier, int32_t nDivisor) const NOTHROW;

   int64_t area();

   bool contains(const RECT & rect) const;
   void constraint_v5(const RECT & rect, const class size sizeMin);
   void constraint_v7(const RECT & rect);
   void Align(int32_t align,const RECT & rect);
   void ScaleHeightAspect(int32_t iNewHeight, int32_t iCenterX, int32_t iCenterY);
   void ScaleRect(double dx, double dy, int32_t ix, int32_t iy);
   void ExtendOnCenter(const RECT & rect);
   void FitOnCenterOf(const RECT & rect);
   void FitOnCenterOf(const RECT & rect, SIZE size);
   void CenterOf(const RECT & rect);
   void CenterOf(const RECT & rect,SIZE size);
   void DeflateBottomRightSizeByRate(double dRate);
   void SetBottomRightSize(int32_t iWidth, int32_t iHeight);
   void SetBottomRightSize(SIZE sz);
   inline point top_right();
   inline point bottom_left();

   void SubtractRectMajor(LPCRECT lpcrectMajor, LPCRECT lpcrectMinor);
   void SubtractRectMinor(LPCRECT lpcrectMajor, LPCRECT lpcrectMinor);


   void get_bounding_rect(const POINT * lppoint, ::count count);
   void get_bounding_rect(const point_array & pointa);

   void assign(const RECT & rect,e_orientation eorientation) NOTHROW;
   void assign_normal(const RECT & rect,e_orientation eorientation) NOTHROW;

   LONG minimum_dimension() const NOTHROW { return MIN(width(),height()); }
   LONG maximum_dimension() const NOTHROW { return MAX(width(),height()); }
   LONG min_dimension() const NOTHROW { return minimum_dimension(); }
   LONG max_dimension() const NOTHROW { return maximum_dimension(); }
   LONG min_dim() const NOTHROW { return min_dimension(); }
   LONG max_dim() const NOTHROW { return max_dimension(); }

   LONG minimum_natural_dimension() const NOTHROW { return MIN(MAX(0, width()),MAX(0,height())); }
   LONG maximum_natural_dimension() const NOTHROW { return MAX(MAX(0, width()),MAX(0, height())); }

   LONG minimum_absolute_dimension() const NOTHROW { return MIN(abs(width()),abs(height())); }
   LONG maximum_absolute_dimension() const NOTHROW { return MIN(abs(width()),abs(height())); }

   LONG minimum_signed_absolute_dimension(bool bNegativePreference = true) const NOTHROW;
   LONG maximum_signed_absolute_dimension(bool bPositivePreference = true) const NOTHROW;

};

/////////////////////////////////////////////////////////////////////////////
// rect64 - A 2-D rect64angle, similar to Windows RECT structure.

class CLASS_DECL_AURA rect64 : public RECT64
{
public:


   rect64() NOTHROW {}
   rect64(i64 l, i64 t, i64 r, i64 b) NOTHROW { left = l; top = t; right = r; bottom = b; }
   rect64(const RECT64 & rect) NOTHROW { *this = rect; }


rect64(const RECT & rect) NOTHROW : rect64(rect.left, rect.top, rect.right, rect.bottom) {}
rect64(const RECTD & rect) NOTHROW : rect64(rect.left, rect.top, rect.right, rect.bottom) {}
rect64(const RECT * prect) NOTHROW : rect64(*prect) {}
rect64(const RECTD * prect) NOTHROW : rect64(*prect) {}
rect64(const RECT64 * prect) NOTHROW : rect64(*prect) {}
rect64(point64 pt, size64 sz) NOTHROW : rect64(pt.x, pt.y, pt.x + sz.cx, pt.y + sz.cy) {}
rect64(size64 sz, point64 pt = null_point()) NOTHROW : rect64(pt, sz) {}
rect64(point64 ptTopLeft, point64 ptBottomRight) NOTHROW : rect64(ptTopLeft.x, ptTopLeft.y, ptBottomRight.x, ptBottomRight.y) {}


   // retrieves the width
   int64_t width() const NOTHROW;
   // returns the height
   int64_t height() const NOTHROW;
   // returns the size
   size64 get_size() const NOTHROW;
   // reference to the top-left POINT64
   point64& top_left() NOTHROW;
   // reference to the bottom-right POINT64
   point64& bottom_right() NOTHROW;
   // const reference to the top-left POINT64
   const point64& top_left() const NOTHROW;
   // const reference to the bottom-right POINT64
   const point64& bottom_right() const NOTHROW;
   // the geometric center POINT64 of the rect64angle
   point64 center() const NOTHROW;
   // swap the left and right
   void swap_left_right() NOTHROW;
   static void WINAPI swap_left_right(RECT64 * lpRect) NOTHROW;

   // convert between rect64 and RECT64 */const RECT64 * (no need for &)
   operator RECT64 *() NOTHROW;
   operator const RECT64 *() const NOTHROW;
   operator rect() const;

   // returns TRUE if rect64angle has no area
   bool is_empty() const NOTHROW;
   // returns TRUE if rect64angle is at (0,0) and has no area
   bool is_null() const NOTHROW;
   // returns TRUE if POINT64 is within rect64angle
   bool contains(POINT64 pt) const NOTHROW;

// Operations

   // set rect64angle from left, top, right, and bottom
   void set(int64_t x1, int64_t y1, int64_t x2, int64_t y2) NOTHROW;
   void set(POINT64 topLeft, POINT64 bottomRight) NOTHROW;
   // is_empty the rect64angle
   void null() NOTHROW;
   // copy from another rect64angle
   void copy(const RECT64 * lpSrcRect) NOTHROW;
   // TRUE if exactly the same as another rect64angle
   bool is_equal(const RECT64 * lpRect) const NOTHROW;

   // Inflate rect64angle's width and height by
   // x units to the left and right ends of the rect64angle
   // and y units to the top and bottom.
   void inflate(int64_t x, int64_t y) NOTHROW;
   // Inflate rect64angle's width and height by
   // size.cx units to the left and right ends of the rect64angle
   // and size.cy units to the top and bottom.
   void inflate(SIZE64 size) NOTHROW;
   // Inflate rect64angle's width and height by moving individual sides.
   // Left side is moved to the left, right side is moved to the right,
   // top is moved up and bottom is moved down.
   void inflate(const RECT64 * lpRect) NOTHROW;
   void inflate(int64_t l, int64_t t, int64_t r, int64_t b) NOTHROW;

   // deflate the rect64angle's width and height without
   // moving its top or left
   void deflate(int64_t x, int64_t y) NOTHROW;
   void deflate(SIZE64 size) NOTHROW;
   void deflate(const RECT64 * lpRect) NOTHROW;
   void deflate(int64_t l, int64_t t, int64_t r, int64_t b) NOTHROW;

   // translate the rect64angle by moving its top and left
   void offset(int64_t x, int64_t y) NOTHROW;
   void offset(SIZE64 size) NOTHROW;
   void offset(POINT64 POINT64) NOTHROW;
   void normalize() NOTHROW;

   void size(SIZE64 size) NOTHROW;
   void rsize(SIZE64 size) NOTHROW;
   void size(int64_t cx,int64_t cy) NOTHROW;
   void rsize(int64_t cx,int64_t cy) NOTHROW;

   // absolute position of rect64angle
   void move_to_y(int64_t y) NOTHROW;
   void move_to_x(int64_t x) NOTHROW;
   void move_to(int64_t x, int64_t y) NOTHROW;
   void move_to(POINT64 pt) NOTHROW;

   // set this rect64angle to int64_tersection of two others
   bool intersect(const RECT64 * lpRect1, const RECT64 * lpRect2) NOTHROW;

   // set this rect64angle to bounding union of two others
   bool unite(const RECT64 * lpRect1, const RECT64 * lpRect2) NOTHROW;

   // set this rect64angle to minimum of two others
//   bool subtract(const RECT64 * lpRectSrc1, const RECT64 * lpRectSrc2) NOTHROW;

// Additional Operations
   void operator=(const RECT64& srcRect) NOTHROW;
   bool operator==(const RECT64& rect64) const NOTHROW;
   bool operator!=(const RECT64& rect64) const NOTHROW;
   void operator+=(POINT64 POINT64) NOTHROW;
   void operator+=(SIZE64 size) NOTHROW;
   void operator+=(const RECT64 * lpRect) NOTHROW;
   void operator-=(POINT64 POINT64) NOTHROW;
   void operator-=(SIZE64 size) NOTHROW;
   void operator-=(const RECT64 * lpRect) NOTHROW;
   void operator&=(const RECT64& rect64) NOTHROW;
   void operator|=(const RECT64& rect64) NOTHROW;

// Operators returning rect64 values
   rect64 operator+(POINT64 POINT64) const NOTHROW;
   rect64 operator-(POINT64 POINT64) const NOTHROW;
   rect64 operator+(const RECT64 * lpRect) const NOTHROW;
   rect64 operator+(SIZE64 size) const NOTHROW;
   rect64 operator-(SIZE64 size) const NOTHROW;
   rect64 operator-(const RECT64 * lpRect) const NOTHROW;
   rect64 operator&(const RECT64 & rect642) const NOTHROW;
   rect64 operator|(const RECT64& rect642) const NOTHROW;
   rect64 MulDiv(int64_t nMultiplier, int64_t nDivisor) const NOTHROW;

   int64_t area();
   bool contains(const RECT64 * lpcrect) const;
   bool contains(const RECT64 * lpcrect);
   void ConstraintV5(const RECT64 * lpcrect, const class size sizeMin);
   void Align(int64_t align, const RECT64 * lpcrect);
   void ScaleHeightAspect(int64_t iNewHeight, int64_t iCenterX, int64_t iCenterY);
   void ScaleRect(double dx, double dy, int64_t ix, int64_t iy);
   void ExtendOnCenter(const RECT64 * lpcrect);
   void FitOnCenterOf(const RECT64 * lpcrect);
   void DeflateBottomRightSizeByRate(double dRate);
   void SetBottomRightSize(int64_t iWidth, int64_t iHeight);

   inline point64 top_right() const NOTHROW;
   inline point64 bottom_left() const NOTHROW;

   void SubtractRectMajor(const RECT64 * lpcrectMajor, const RECT64 * lpcrectMinor);
   void SubtractRectMinor(const RECT64 * lpcrectMajor, const RECT64 * lpcrectMinor);


   void assign(const RECT64 * lpcrect,e_orientation eorientation) NOTHROW;
   void assign_normal(const RECT64 * lpcrect,e_orientation eorientation) NOTHROW;


   int64_t minimum_dimension() const NOTHROW { return MIN(width(),height()); }
   int64_t maximum_dimension() const NOTHROW { return MAX(width(),height()); }
   int64_t min_dimension() const NOTHROW { return minimum_dimension(); }
   int64_t max_dimension() const NOTHROW { return maximum_dimension(); }
   int64_t min_dim() const NOTHROW { return min_dimension(); }
   int64_t max_dim() const NOTHROW { return max_dimension(); }

   int64_t minimum_natural_dimension() const NOTHROW { return MIN(MAX(0,width()),MAX(0,height())); }
   int64_t maximum_natural_dimension() const NOTHROW { return MAX(MAX(0,width()),MAX(0,height())); }

   int64_t minimum_absolute_dimension() const NOTHROW;
   int64_t maximum_absolute_dimension() const NOTHROW;

   int64_t minimum_signed_absolute_dimension(bool bNegativePreference = true) const NOTHROW;
   int64_t maximum_signed_absolute_dimension(bool bPositivePreference = true) const NOTHROW;

};





inline point rect::top_right()
{
   return point(right, top);
}

inline point rect::bottom_left()
{
   return point(left, bottom);
}

inline point rect::center() const NOTHROW
{
   return point((left + right) / 2, (top + bottom) / 2);
}

inline bool rect::is_null() const NOTHROW
{
   return left == 0 && top == 0 && right == 0 && bottom == 0;
}

inline bool rect::is_empty() const NOTHROW
{
   return width() == 0 || height() == 0;
}









inline point64 rect64::top_right() const NOTHROW
{
   return point64(right, top);
}

inline point64 rect64::bottom_left() const NOTHROW
{
   return point64(left, bottom);
}

inline point64 rect64::center() const NOTHROW
{
   return point64((left + right) / 2, (top + bottom) / 2);
}

inline bool rect64::is_null() const NOTHROW
{
   return left == 0 && top == 0 && right == 0 && bottom == 0;
}

inline bool rect64::is_empty() const NOTHROW
{
   return width() == 0 && height() == 0;
}

















class pointd_array;


/////////////////////////////////////////////////////////////////////////////
// rect - A 2-D rectangle, similar to Windows RECT structure.

class CLASS_DECL_AURA rectd : public RECTD
{
public:


   rectd() NOTHROW {}
   rectd(f64 l, f64 t, f64 r, f64 b) NOTHROW { left = l; top = t; right = r; bottom = b; }
   rectd(const RECTD & rect) NOTHROW { *this = rect; }


rectd(const RECT & rect) NOTHROW : rectd(rect.left, rect.top, rect.right, rect.bottom) {}
rectd(const RECT64 & rect) NOTHROW : rectd(rect.left, rect.top, rect.right, rect.bottom) {}
rectd(const RECT * prect) NOTHROW : rectd(*prect) {}
rectd(const RECTD * prect) NOTHROW : rectd(*prect) {}
rectd(const RECT64 * prect) NOTHROW : rectd(*prect) {}
rectd(pointd pt, sized sz) NOTHROW : rectd(pt.x, pt.y, pt.x + sz.cx, pt.y + sz.cy) {}
rectd(sized sz, pointd pt = null_point()) NOTHROW : rectd(pt, sz) {}
rectd(pointd ptTopLeft, pointd ptBottomRight) NOTHROW : rectd(ptTopLeft.x, ptTopLeft.y, ptBottomRight.x, ptBottomRight.y) {}

   // retrieves the width
   double width() const NOTHROW;
   // returns the height
   double height() const NOTHROW;
   // returns the size
   class sized size() const NOTHROW;
   // reference to the top-left point
   pointd& top_left() NOTHROW;
   // reference to the bottom-right point
   pointd& bottom_right() NOTHROW;
   // const reference to the top-left point
   const pointd& top_left() const NOTHROW;
   // const reference to the bottom-right point
   const pointd& bottom_right() const NOTHROW;
   // the geometric center point of the rectangle
   pointd center() const NOTHROW;
   // swap the left and right
   void swap_left_right() NOTHROW;
   static void WINAPI swap_left_right(LPRECTD lpRect) NOTHROW;

   // convert between rectd and LPRECTD/LPCRECTD (no need for &)
   operator LPRECTD() NOTHROW;
   operator LPCRECTD() const NOTHROW;

   // returns TRUE if rectangle has no area
   bool is_empty() const NOTHROW;
   // returns TRUE if rectangle is at (0,0) and has no area
   bool is_null() const NOTHROW;
   // returns TRUE if point is within rectangle
   bool contains(POINTD point) const NOTHROW;

// Operations

   // set rectangle from left, top, right, and bottom
   void set(double x1, double y1, double x2, double y2) NOTHROW;
   void set(POINTD topLeft, POINTD bottomRight) NOTHROW;
   // is_empty the rectangle
   void null() NOTHROW;
   // copy from another rectangle
   void copy(LPCRECTD lpSrcRect) NOTHROW;
   // TRUE if exactly the same as another rectangle
   bool is_equal(LPCRECTD lpRect) const NOTHROW;

   // Inflate rectangle's width and height by
   // x units to the left and right ends of the rectangle
   // and y units to the top and bottom.
   void inflate(double x, double y) NOTHROW;
   // Inflate rectangle's width and height by
   // size.cx units to the left and right ends of the rectangle
   // and size.cy units to the top and bottom.
   void inflate(SIZED size) NOTHROW;
   // Inflate rectangle's width and height by moving individual sides.
   // Left side is moved to the left, right side is moved to the right,
   // top is moved up and bottom is moved down.
   void inflate(LPCRECTD lpRect) NOTHROW;
   void inflate(double l, double t, double r, double b) NOTHROW;

   // deflate the rectangle's width and height without
   // moving its top or left
   void deflate(double x, double y) NOTHROW;
   void deflate(SIZED size) NOTHROW;
   void deflate(LPCRECTD lpRect) NOTHROW;
   void deflate(double l, double t, double r, double b) NOTHROW;

   // translate the rectangle by moving its top and left
   void offset(double x, double y) NOTHROW;
   void offset(SIZED size) NOTHROW;
   void offset(POINTD point) NOTHROW;
   void normalize() NOTHROW;

   // absolute position of rectangle
   void move_to_y(double y) NOTHROW;
   void move_to_x(double x) NOTHROW;
   void move_to(double x, double y) NOTHROW;
   void move_to(POINTD point) NOTHROW;

   // set this rectangle to intersection of two others
   bool intersect(LPCRECTD lpRect1, LPCRECTD lpRect2) NOTHROW;

   // set this rectangle to bounding union of two others
   bool unite(LPCRECTD lpRect1, LPCRECTD lpRect2) NOTHROW;

   // set this rectangle to minimum of two others
   //bool subtract(LPCRECTD lpRectSrc1, LPCRECTD lpRectSrc2) NOTHROW;

// Additional Operations
   void operator=(const RECTD& srcRect) NOTHROW;
   bool operator==(const RECTD& rectd) const NOTHROW;
   bool operator!=(const RECTD& rectd) const NOTHROW;
   void operator+=(POINTD point) NOTHROW;
   void operator+=(SIZED size) NOTHROW;
   void operator+=(LPCRECTD lpRect) NOTHROW;
   void operator-=(POINTD point) NOTHROW;
   void operator-=(SIZED size) NOTHROW;
   void operator-=(LPCRECTD lpRect) NOTHROW;
   void operator&=(const RECTD& rectd) NOTHROW;
   void operator|=(const RECTD& rectd) NOTHROW;

// Operators returning rectd values
   rectd operator+(POINTD point) const NOTHROW;
   rectd operator-(POINTD point) const NOTHROW;
   rectd operator+(LPCRECTD lpRect) const NOTHROW;
   rectd operator+(SIZED size) const NOTHROW;
   rectd operator-(SIZED size) const NOTHROW;
   rectd operator-(LPCRECTD lpRect) const NOTHROW;
   rectd operator&(const RECTD& rect2) const NOTHROW;
   rectd operator|(const RECTD& rect2) const NOTHROW;
   rectd MulDiv(double nMultiplier, double nDivisor) const NOTHROW;

   double area();

   bool contains(LPCRECTD lpcrect) const;
   void ConstraintV5(LPCRECTD lpcrect, const class size sizeMin);
   void Align(double align, LPCRECTD lpcrect);
   void ScaleHeightAspect(double iNewHeight, double iCenterX, double iCenterY);
   void ScaleRect(double dx, double dy, double ix, double iy);
   void ExtendOnCenter(LPCRECTD lpcrect);
   void FitOnCenterOf(LPCRECTD lpcrect);
   void CenterOf(LPCRECTD lpcrect);
   void CenterOf(LPCRECTD lpcrect,SIZED size);
   void DeflateBottomRightSizeByRate(double dRate);
   void SetBottomRightSize(double iWidth, double iHeight);
   inline pointd top_right();
   inline pointd bottom_left();

   void SubtractRectMajor(LPCRECTD lpcrectMajor, LPCRECTD lpcrectMinor);
   void SubtractRectMinor(LPCRECTD lpcrectMajor, LPCRECTD lpcrectMinor);


   void get_bounding_rect(const POINTD * lppoint, ::count count);
   void get_bounding_rect(const pointd_array & pointa);

   void assign(const RECTD * lpcrect,e_orientation eorientation) NOTHROW;
   void assign_normal(const RECTD * lpcrect,e_orientation eorientation) NOTHROW;

   double minimum_dimension() const NOTHROW { return MIN(width(),height()); }
   double maximum_dimension() const NOTHROW { return MAX(width(),height()); }
   double min_dimension() const NOTHROW { return minimum_dimension(); }
   double max_dimension() const NOTHROW { return maximum_dimension(); }
   double min_dim() const NOTHROW { return min_dimension(); }
   double max_dim() const NOTHROW { return max_dimension(); }

   double minimum_natural_dimension() const NOTHROW { return MIN(MAX(0,width()),MAX(0,height())); }
   double maximum_natural_dimension() const NOTHROW { return MAX(MAX(0,width()),MAX(0,height())); }

   double minimum_absolute_dimension() const NOTHROW;
   double maximum_absolute_dimension() const NOTHROW;

   double minimum_signed_absolute_dimension(bool bNegativePreference = true) const NOTHROW;
   double maximum_signed_absolute_dimension(bool bPositivePreference = true) const NOTHROW;


};

inline CLASS_DECL_AURA void null_rect(LPRECT p) { ZEROP(p);}
inline CLASS_DECL_AURA void null_rect(LPRECT64 p ) { ZEROP(p);}


inline CLASS_DECL_AURA ::rect null_rect() { return ::rect(0, 0, 0, 0); }
inline CLASS_DECL_AURA ::rect64 null_rect64() { return ::rect64(0, 0, 0, 0); }


inline void rect::assign(const RECT & rect,e_orientation eorientation) NOTHROW
{

   if(eorientation == orientation_horizontal)
   {

      left = rect.left;
      right = rect.right;

   }
   else if(eorientation == orientation_vertical)
   {

      top = rect.top;
      bottom = rect.bottom;

   }

}


inline void rect::assign_normal(const RECT & rect,e_orientation eorientation) NOTHROW
{

   if(eorientation == orientation_horizontal)
   {

      top = rect.top;
      bottom = rect.bottom;

   }
   else if(eorientation == orientation_vertical)
   {

      left = rect.left;
      right = rect.right;

   }

}

inline void rect64::assign(const RECT64 * lpcrect,e_orientation eorientation) NOTHROW
{

   if(eorientation == orientation_horizontal)
   {

      left = lpcrect->left;
      right = lpcrect->right;

   }
   else if(eorientation == orientation_vertical)
   {

      top = lpcrect->top;
      bottom = lpcrect->bottom;

   }

}


inline void rect64::assign_normal(const RECT64 * lpcrect,e_orientation eorientation) NOTHROW
{

   if(eorientation == orientation_horizontal)
   {

      top = lpcrect->top;
      bottom = lpcrect->bottom;

   }
   else if(eorientation == orientation_vertical)
   {

      left = lpcrect->left;
      right = lpcrect->right;

   }

}

inline void rectd::assign(const RECTD * lpcrect,e_orientation eorientation) NOTHROW
{

   if(eorientation == orientation_horizontal)
   {

      left = lpcrect->left;
      right = lpcrect->right;

   }
   else if(eorientation == orientation_vertical)
   {

      top = lpcrect->top;
      bottom = lpcrect->bottom;

   }

}


inline void rectd::assign_normal(const RECTD * lpcrect,e_orientation eorientation) NOTHROW
{

   if(eorientation == orientation_horizontal)
   {

      top = lpcrect->top;
      bottom = lpcrect->bottom;

   }
   else if(eorientation == orientation_vertical)
   {

      left = lpcrect->left;
      right = lpcrect->right;

   }

}



template<> inline UINT HashKey<rect> (rect key)
{
   return key.left | key.top | key.bottom | key.right;
}






class CLASS_DECL_AURA rect3d
{
public:

   rect3d() {};
   rect3d(double x,double y,double z,double x2,double y2,double z2,double,double cx,double cy): m_p(x,y,z),m_d(x2,y2,z2),m_size(cx,cy) {}

   point3d    m_p;
   point3d    m_d; // direction
   pointd     m_size; // size


};




inline bool rect::intersects_x(LPCRECT lpRect) const NOTHROW
{
   return (left >= lpRect->left && left <= lpRect->right) ||
          (right >= lpRect->left && right <= lpRect->right) ||
          (lpRect->left >= left && lpRect->left <= right) ||
          (lpRect->right >= left && lpRect->right <= right);
}

inline bool rect::intersects_y(LPCRECT lpRect) const NOTHROW
{
   return (top >= lpRect->top && top <= lpRect->bottom) ||
          (bottom >= lpRect->top && bottom <= lpRect->bottom) ||
          (lpRect->top >= top && lpRect->top <= bottom) ||
          (lpRect->bottom >= top && lpRect->bottom <= bottom);
}

inline bool rect::intersects(LPCRECT lpRect) const NOTHROW
{

   return intersects_x(lpRect) && intersects_y(lpRect);

}

