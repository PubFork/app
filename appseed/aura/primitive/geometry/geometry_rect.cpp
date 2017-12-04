#include "framework.h"
//#include <math.h>


void rect::DeflateBottomRightSizeByRate(double dRate)
{
    double dx = width();
    double dy = height();
    double dxNew = dx / dRate;
    double dyNew = dy / dRate;
    dx = dx - dxNew;
    dy = dy - dyNew;
    right -= (long) dx;
    bottom -= (long) dy;
}

void rect::SetBottomRightSize(int32_t iWidth, int32_t iHeight)
{
    right = left + iWidth;
    bottom = top + iHeight;
}


void rect::SetBottomRightSize(SIZE size)
{
   SetBottomRightSize(size.cx,size.cy);
}

void rect::ExtendOnCenter(const RECT & rect)
{

   int32_t cx = width();
   int32_t cy = height();

   double dx = ::width(rect);
   double dy = ::height(rect);
   double dr = MAX(dx / cx, dy / cy);

   int32_t cw = (int32_t) (cx * dr);
   int32_t ch = (int32_t) (cy * dr);
   
   left = (LONG) ((dx - cw) / 2.0);
   top = (LONG) ((dy - ch) / 2.0);
   right = left + cw;
   bottom = top + ch;
   
}

void rect::FitOnCenterOf(const RECT & rect,SIZE size)
{
   int32_t cx = size.cx;
   int32_t cy = size.cy;

   double dx = ::width(rect);
   double dy = ::height(rect);
   double dr = MIN(cx == 0 ? 1 : dx / cx,cy == 0 ? 1 : dy / cy);

   int32_t cw = cx == 0 ? (int32_t)dx : ((int32_t)(cx * dr));
   int32_t ch = cy == 0 ? (int32_t)dy : ((int32_t)(cy * dr));

   left = (LONG)((rect.left) + (dx - cw) / 2.0);
   top = (LONG)((rect.top) + (dy - ch) / 2.0);
   right = left + cw;
   bottom = top + ch;

}

void rect::FitOnCenterOf(const RECT & rect)
{
   
   FitOnCenterOf(rect,size());
   
}


void rect::CenterOf(const RECT & rect,SIZE size)
{
   int32_t cx = size.cx;
   int32_t cy = size.cy;

   LONG dx = ::width(rect);
   LONG dy = ::height(rect);

   left     = rect.left   + (dx - cx) / 2;
   top      = rect.top    + (dy - cy) / 2;
   right    = left            + cx;
   bottom   = top             + cy;

}

void rect::CenterOf(const RECT & rect)
{

   CenterOf(rect,size());

}


void rect::ScaleRect(double dx, double dy, int32_t ix, int32_t iy)
{
   left    = (LONG) (((left    - ix) * dx) + ix);
   top     = (LONG) (((top     - iy) * dy) + iy);
   right   = (LONG) (((right   - ix) * dx) + ix);
   bottom  = (LONG) (((bottom  - iy) * dy) + iy);

}

void rect::ScaleHeightAspect(int32_t iNewHeight, int32_t iCenterX, int32_t iCenterY)
{
   int32_t iHeight = height();
   if(iHeight != 0)
   {
      double d = (double) iNewHeight / iHeight;
      ScaleRect(d, d, iCenterX, iCenterY);
   }
}

void rect::Align(int32_t align, const RECT & rect)
{

   point pt(0, 0);

   if((align & align_horizontal) == align_horizontal_center)
   {
      pt.x = rect.left + (rect.right - rect.left) / 2 - width() / 2 - left;
   }
   else if((align & align_horizontal) == align_left)
   {
      pt.x = rect.left - left;
   }
   else if((align & align_horizontal) == align_right)
   {
      pt.x = rect.right - right;
   }

   if((align & align_vertical) ==  align_vertical_center)
   {
      pt.y = rect.top + (rect.bottom - rect.top) / 2 - height() / 2 - top;
   }
   else if((align & align_vertical) == align_top)
   {
      pt.y = rect.top - top;
   }
   else if((align & align_vertical) == align_bottom)
   {
      pt.y = rect.bottom - bottom;
   }

   offset(pt);

}

void rect::constraint_v5(const RECT & rect, const class size sizeMin)
{
   if(left < rect.left)
      left = rect.left;
   if(right > rect.right)
      right = rect.right;
   if(top < rect.top)
      top = rect.top;
   if(bottom > rect.bottom)
      bottom = rect.bottom;

   if(width() < sizeMin.cx)
      right = left + sizeMin.cx;
   if(height() < sizeMin.cy)
      bottom = top + sizeMin.cy;

}

void rect::constraint_v7(const RECT & rect)
{

   ::size size = this->size();

   if(size.cx > ::width(rect))
   {

      intersect_x(this,&rect);

   }
   else if(intersect_x(this, &rect))
   {

      if(left == rect.left)
      {

         right = left + size.cx;

      }
      else
      {

         left = right - size.cx;

      }

   }

   if(size.cy > ::height(rect))
   {

      intersect_y(this,&rect);

   }
   else if(intersect_y(this,&rect))
   {

      if(top == rect.top)
      {

         bottom = top + size.cy;

      }
      else
      {

         top = bottom - size.cy;

      }

   }

}

bool rect::contains(const RECT & rect) const
{
   return rect.left >= left
      && rect.right <= right
      && rect.top >= top
      && rect.bottom <= bottom;
}

// Subtract minor from major and return the greatest box around.
void rect::SubtractRectMajor(LPCRECT lpcrectMajor, LPCRECT lpcrectMinor)
{
   rect rectIntersect;
   rect rectRet(*this);
   if(!rectIntersect.intersect(lpcrectMajor, lpcrectMinor))
   {
      rectRet = *lpcrectMajor;
   }
   else
   {
      if(rectIntersect == *lpcrectMajor)
      {
         rectRet.set(0, 0, 0, 0);
      }
      else
      {
         if(rectIntersect.left == lpcrectMajor->left
            && rectIntersect.right == lpcrectMajor->right)
         {
            if(rectIntersect.top == lpcrectMajor->top)
            {
               rectRet.set(
                  lpcrectMajor->left,
                  rectIntersect.top,
                  lpcrectMajor->right,
                  lpcrectMajor->bottom);
            }
            else if(rectIntersect.bottom == lpcrectMajor->bottom)
            {
               rectRet.set(
                  lpcrectMajor->left,
                  lpcrectMajor->top,
                  lpcrectMajor->right,
                  rectIntersect.bottom);
            }
            else
            {
               rectRet = *lpcrectMajor;
            }
         }
         else if(rectIntersect.top == lpcrectMajor->top
            && rectIntersect.bottom == lpcrectMajor->bottom)
         {
            if(rectIntersect.left == lpcrectMajor->left)
            {
               rectRet.set(
                  rectIntersect.left,
                  lpcrectMajor->top,
                  lpcrectMajor->right,
                  lpcrectMajor->bottom);
            }
            else if(rectIntersect.right == lpcrectMajor->right)
            {
               rectRet.set(
                  lpcrectMajor->left,
                  lpcrectMajor->top,
                  rectIntersect.right,
                  lpcrectMajor->bottom);
            }
            else
            {
               rectRet = *lpcrectMajor;
            }
         }
         else
         {
            rectRet = *lpcrectMajor;
         }
      }
   }
   *this = rectRet;
   return;

}

void rect::SubtractRectMinor(LPCRECT lpcrectMajor, LPCRECT lpcrectMinor)
{
   UNREFERENCED_PARAMETER(lpcrectMajor);
   UNREFERENCED_PARAMETER(lpcrectMinor);
}

LONG rect::minimum_signed_absolute_dimension(bool bNegativePreference) const NOTHROW
{

   LONG w = width();

   LONG h = height();

   if(abs(w) < abs(h))
   {

      return w;

   }
   else if(abs(h) < abs(w))
   {

      return h;

   }
   else if(bNegativePreference) // absolutely equal, prefer negative ...
   {

      return MIN(w, h);

   }
   else // ... otherwise prefer positive
   {

      return MAX(w,h);

   }


}


LONG rect::maximum_signed_absolute_dimension(bool bPositivePreference) const NOTHROW
{

   LONG w = width();

   LONG h = height();

   if(abs(w) > abs(h))
   {

      return w;

   }
   else if(abs(h) > abs(w))
   {

      return h;

   }
   else if(bPositivePreference) // absolutely equal, prefer positive ...
   {

      return MAX(w,h);

   }
   else // ... otherwise prefer negative
   {

      return MIN(w,h);

   }


}





void rect64::DeflateBottomRightSizeByRate(double dRate)
{
    double dx = (double) width();
    double dy = (double) height();
    double dxNew = dx / dRate;
    double dyNew = dy / dRate;
    dx = dx - dxNew;
    dy = dy - dyNew;
    right -= (long) dx;
    bottom -= (long) dy;
}

void rect64::SetBottomRightSize(int64_t iWidth, int64_t iHeight)
{
    right = left + iWidth;
    bottom = top + iHeight;
}

void rect64::ExtendOnCenter(const RECT64 *  lpcrect)
{
    int64_t cx = width();
    int64_t cy = height();

    double dx = (double) (lpcrect->right - lpcrect->left);
    double dy = (double) (lpcrect->bottom - lpcrect->top);
    double dr = MAX(dx / cx, dy / cy);

    int64_t cw = (int64_t) (cx * dr);
   int64_t ch = (int64_t) (cy * dr);
   left = (long) ((dx - cw) / 2.0);
   top = (long) ((dy - ch) / 2.0);
    right = left + cw;
    bottom = top + ch;
}


void rect64::FitOnCenterOf(const RECT64 *  lpcrect)
{
    int64_t cx = width();
    int64_t cy = height();

    double dx = (double) (lpcrect->right - lpcrect->left);
    double dy = (double) (lpcrect->bottom - lpcrect->top);
    double dr = MIN(cx == 0 ? 1 : dx / cx, cy == 0 ? 1 : dy / cy);

    int64_t cw = cx == 0 ? (int64_t) dx : ((int64_t) (cx * dr));
   int64_t ch = cy == 0 ? (int64_t) dy : ((int64_t) (cy * dr));
   left = (long) ((lpcrect->left) + (dx - cw) / 2.0);
   top = (long) ((lpcrect->top) + (dy - ch) / 2.0);
    right = left + cw;
    bottom = top + ch;
}

void rect64::ScaleRect(double dx, double dy, int64_t ix, int64_t iy)
{
   left    = (long) (((left    - ix) * dx) + ix);
   top     = (long) (((top     - iy) * dy) + iy);
   right   = (long) (((right   - ix) * dx) + ix);
   bottom  = (long) (((bottom  - iy) * dy) + iy);

}

void rect64::ScaleHeightAspect(int64_t iNewHeight, int64_t iCenterX, int64_t iCenterY)
{
   int64_t iHeight = height();
   if(iHeight != 0)
   {
      double d = (double) iNewHeight / iHeight;
      ScaleRect(d, d, iCenterX, iCenterY);
   }
}

void rect64::Align(int64_t align, const RECT64 *  lpcrect)
{

   point64 pt(0, 0);

   if((align & align_horizontal) == align_horizontal_center)
   {
      pt.x = lpcrect->left + (lpcrect->right - lpcrect->left) / 2 - width() / 2 - left;
   }
   else if((align & align_horizontal) == align_left)
   {
      pt.x = lpcrect->left - left;
   }
   else if((align & align_horizontal) == align_right)
   {
      pt.x = lpcrect->right - right;
   }

   if((align & align_vertical) ==  align_vertical_center)
   {
      pt.y = lpcrect->top + (lpcrect->bottom - lpcrect->top) / 2 - height() / 2 - top;
   }
   else if((align & align_vertical) == align_top)
   {
      pt.y = lpcrect->top - top;
   }
   else if((align & align_vertical) == align_bottom)
   {
      pt.y = lpcrect->bottom - bottom;
   }

   offset(pt);

}

void rect64::ConstraintV5(const RECT64 *  lpcrect, const class size sizeMin)
{
   if(left < lpcrect->left)
      left = lpcrect->left;
   if(right > lpcrect->right)
      right = lpcrect->right;
   if(top < lpcrect->top)
      top = lpcrect->top;
   if(bottom > lpcrect->bottom)
      bottom = lpcrect->bottom;

   if(width() < sizeMin.cx)
      right = left + sizeMin.cx;
   if(height() < sizeMin.cy)
      bottom = top + sizeMin.cy;

}

bool rect64::contains(const RECT64 *  lpcrect) const
{
   return lpcrect->left >= left
      && lpcrect->right <= right
      && lpcrect->top >= top
      && lpcrect->bottom <= bottom;
}

// Subtract minor from major and return the greatest box around.
void rect64::SubtractRectMajor(const RECT64 *  lpcrectMajor, const RECT64 *  lpcrectMinor)
{
   rect64 rectIntersect;
   rect64 rectRet(*this);
   if(!rectIntersect.intersect(lpcrectMajor, lpcrectMinor))
   {
      rectRet = *lpcrectMajor;
   }
   else
   {
      if(rectIntersect == *lpcrectMajor)
      {
         rectRet.set(0, 0, 0, 0);
      }
      else
      {
         if(rectIntersect.left == lpcrectMajor->left
            && rectIntersect.right == lpcrectMajor->right)
         {
            if(rectIntersect.top == lpcrectMajor->top)
            {
               rectRet.set(
                  lpcrectMajor->left,
                  rectIntersect.top,
                  lpcrectMajor->right,
                  lpcrectMajor->bottom);
            }
            else if(rectIntersect.bottom == lpcrectMajor->bottom)
            {
               rectRet.set(
                  lpcrectMajor->left,
                  lpcrectMajor->top,
                  lpcrectMajor->right,
                  rectIntersect.bottom);
            }
            else
            {
               rectRet = *lpcrectMajor;
            }
         }
         else if(rectIntersect.top == lpcrectMajor->top
            && rectIntersect.bottom == lpcrectMajor->bottom)
         {
            if(rectIntersect.left == lpcrectMajor->left)
            {
               rectRet.set(
                  rectIntersect.left,
                  lpcrectMajor->top,
                  lpcrectMajor->right,
                  lpcrectMajor->bottom);
            }
            else if(rectIntersect.right == lpcrectMajor->right)
            {
               rectRet.set(
                  lpcrectMajor->left,
                  lpcrectMajor->top,
                  rectIntersect.right,
                  lpcrectMajor->bottom);
            }
            else
            {
               rectRet = *lpcrectMajor;
            }
         }
         else
         {
            rectRet = *lpcrectMajor;
         }
      }
   }
   *this = rectRet;
   return;

}

void rect64::SubtractRectMinor(const RECT64 *  lpcrectMajor, const RECT64 *  lpcrectMinor)
{
   UNREFERENCED_PARAMETER(lpcrectMajor);
   UNREFERENCED_PARAMETER(lpcrectMinor);
}



int64_t rect64::minimum_absolute_dimension() const NOTHROW{ return MIN(INTABS(width()),INTABS(height())); }
int64_t rect64::maximum_absolute_dimension() const NOTHROW{ return MIN(INTABS(width()),INTABS(height())); }



int64_t rect64::minimum_signed_absolute_dimension(bool bNegativePreference) const NOTHROW
{

   int64_t w = width();

   int64_t h = height();

   if(abs(w) < abs(h))
   {

      return w;

   }
   else if(abs(h) < abs(w))
   {

      return h;

   }
   else if(bNegativePreference) // absolutely equal, prefer negative ...
   {

      return MIN(w,h);

   }
   else // ... otherwise prefer positive
   {

      return MAX(w,h);

   }


}


int64_t rect64::maximum_signed_absolute_dimension(bool bPositivePreference) const NOTHROW
{

   int64_t w = width();

   int64_t h = height();

   if(abs(w) > abs(h))
   {

      return w;

   }
   else if(abs(h) > abs(w))
   {

      return h;

   }
   else if(bPositivePreference) // absolutely equal, prefer positive ...
   {

      return MAX(w,h);

   }
   else // ... otherwise prefer negative
   {

      return MIN(w,h);

   }


}





















// rect
rect::rect() NOTHROW
   { /* random filled */ }
rect::rect(int64_t l, int64_t t, int64_t r, int64_t b) NOTHROW
   { left = (int32_t) l; top = (int32_t) t; right = (int32_t) r; bottom = (int32_t) b; }
rect::rect(const RECT& srcRect) NOTHROW
   { ::CopyRect(this, (LPCRECT) &srcRect); }
rect::rect(const RECT64& srcRect) NOTHROW
   { ::copy(this, &srcRect); }
rect::rect(LPCRECT lpSrcRect) NOTHROW
   { ::CopyRect(this, lpSrcRect); }
rect::rect(POINT point, SIZE size) NOTHROW
   { right = (left = point.x) + size.cx; bottom = (top = point.y) + size.cy; }
rect::rect(POINT topLeft, POINT bottomRight) NOTHROW
   { left = topLeft.x; top = topLeft.y;
      right = bottomRight.x; bottom = bottomRight.y; }
int32_t rect::width() const NOTHROW
   { return right - left; }
int32_t rect::height() const NOTHROW
   { return bottom - top; }
class size rect::size() const NOTHROW
   {
      class size sizeRet(right - left, bottom - top);
      return sizeRet; }
class size rect::size(LONG cx, LONG cy) NOTHROW
{
   right = left + cx;
   bottom = top + cy;
   class size sizeRet(right - left,bottom - top);
   return sizeRet;
}
point& rect::top_left() NOTHROW
   { return *((point*)this); }
point& rect::bottom_right() NOTHROW
   { return *((point*)this+1); }
const point& rect::top_left() const NOTHROW
   { return *((point*)this); }
const point& rect::bottom_right() const NOTHROW
   { return *((point*)this+1); }
void rect::swap_left_right() NOTHROW
   { swap_left_right(LPRECT(this)); }
void WINAPI rect::swap_left_right(LPRECT lpRect) NOTHROW
   { LONG temp = lpRect->left; lpRect->left = lpRect->right; lpRect->right = temp; }
rect::operator LPRECT() NOTHROW
   { return this; }
rect::operator LPCRECT() const NOTHROW
   { return (LPCRECT) this; }
bool rect::contains(POINT point) const NOTHROW
   { return ::PtInRect((LPCRECT) this, point) != FALSE; }
void rect::set(int32_t i) NOTHROW
{
   ::SetRect(this, i, i, i, i);
}
void rect::set(int32_t x, int32_t y) NOTHROW
{
   ::SetRect(this, x, y, x, y);
}
void rect::set(int32_t x1, int32_t y1, int32_t x2, int32_t y2) NOTHROW
   { ::SetRect(this, x1, y1, x2, y2); }
void rect::set(POINT topLeft, POINT bottomRight) NOTHROW
   { ::SetRect(this, topLeft.x, topLeft.y, bottomRight.x, bottomRight.y); }
void rect::null() NOTHROW
   { ::SetRectEmpty(this); }
void rect::copy(LPCRECT lpSrcRect) NOTHROW
   { ::CopyRect(this, lpSrcRect); }
bool rect::is_equal(LPCRECT lpRect) const NOTHROW
   { return ::EqualRect((LPCRECT) this, lpRect) != FALSE; }
void rect::inflate(int32_t x, int32_t y) NOTHROW
   { ::InflateRect(this, x, y); }
void rect::inflate(SIZE size) NOTHROW
   { ::InflateRect(this, size.cx, size.cy); }
void rect::deflate(int32_t x, int32_t y) NOTHROW
   { ::InflateRect(this, -x, -y); }
void rect::deflate(SIZE size) NOTHROW
   { ::InflateRect(this, -size.cx, -size.cy); }
void rect::offset(int32_t x, int32_t y) NOTHROW
   { ::OffsetRect(this, x, y); }
void rect::offset(POINT point) NOTHROW
   { ::OffsetRect(this, point.x, point.y); }
void rect::offset(SIZE size) NOTHROW
   { ::OffsetRect(this, size.cx, size.cy); }
void rect::move_to_y(int32_t y) NOTHROW
   { bottom = height() + y; top = y; }
void rect::move_to_x(int32_t x) NOTHROW
   { right = width() + x; left = x; }
void rect::move_to(int32_t x, int32_t y) NOTHROW
   { move_to_x(x); move_to_y(y); }
void rect::move_to(POINT pt) NOTHROW
   { move_to_x(pt.x); move_to_y(pt.y); }
bool rect::intersect_x(LPCRECT lpRect1,LPCRECT lpRect2) NOTHROW
{
   return ::x_intersect_rect(this,lpRect1,lpRect2) != FALSE;
}
bool rect::intersect_y(LPCRECT lpRect1,LPCRECT lpRect2) NOTHROW
{
   return ::y_intersect_rect(this,lpRect1,lpRect2) != FALSE;
}
bool rect::intersect(LPCRECT lpRect1,LPCRECT lpRect2) NOTHROW
   { return ::IntersectRect(this, lpRect1, lpRect2) != FALSE;}
rect & rect::intersect(LPCRECT lpcrect) NOTHROW
{
   ::IntersectRect(this, this, lpcrect);
   return *this;
}
rect rect::intersect(LPCRECT lpcrect) const NOTHROW
{
   ::rect rect;
   ::IntersectRect(&rect,this,lpcrect);
   return rect;
}
bool rect::null_intersect(LPCRECT lpRect1,LPCRECT lpRect2) NOTHROW
{
   return ::null_intersect_rect(this,lpRect1,lpRect2) != FALSE;
}
bool rect::top_left_null_intersect(LPCRECT lpRect1,LPCRECT lpRect2) NOTHROW
{
   return ::top_left_null_intersect_rect(this,lpRect1,lpRect2) != FALSE;
}
bool rect::unite(LPCRECT lpRect1,LPCRECT lpRect2) NOTHROW
   { return ::UnionRect(this, lpRect1, lpRect2) != FALSE; }
void rect::operator=(const RECT& srcRect) NOTHROW
   { ::CopyRect(this, (LPCRECT) &srcRect); }
bool rect::operator==(const RECT& rect) const NOTHROW
   { return ::EqualRect((LPCRECT)this, (LPCRECT) &rect) != FALSE; }
bool rect::operator!=(const RECT& rect) const NOTHROW
   { return ::EqualRect((LPCRECT)this, (LPCRECT) &rect) == FALSE; }
void rect::operator+=(POINT point) NOTHROW
   { ::OffsetRect(this, point.x, point.y); }
void rect::operator+=(SIZE size) NOTHROW
   { ::OffsetRect(this, size.cx, size.cy); }
void rect::operator+=(LPCRECT lpRect) NOTHROW
   { inflate(lpRect); }
void rect::operator-=(POINT point) NOTHROW
   { ::OffsetRect(this, -point.x, -point.y); }
void rect::operator-=(SIZE size) NOTHROW
   { ::OffsetRect(this, -size.cx, -size.cy); }
void rect::operator-=(LPCRECT lpRect) NOTHROW
   { deflate(lpRect); }
void rect::operator&=(const RECT& rect) NOTHROW
   { ::IntersectRect(this, this, (LPCRECT)&rect); }
void rect::operator|=(const RECT& rect) NOTHROW
   { ::UnionRect(this, this,(LPCRECT) &rect); }
rect rect::operator+(POINT pt) const NOTHROW
   { rect rect(*this); ::OffsetRect(&rect, pt.x, pt.y); return rect; }
rect rect::operator-(POINT pt) const NOTHROW
   { rect rect(*this); ::OffsetRect(&rect, -pt.x, -pt.y); return rect; }
rect rect::operator+(SIZE size) const NOTHROW
   { rect rect(*this); ::OffsetRect(&rect, size.cx, size.cy); return rect; }
rect rect::operator-(SIZE size) const NOTHROW
   { rect rect(*this); ::OffsetRect(&rect, -size.cx, -size.cy); return rect; }
rect rect::operator+(LPCRECT lpRect) const NOTHROW
   { class rect rect((LPCRECT)this); rect.inflate(lpRect); return rect; }
rect rect::operator-(LPCRECT lpRect) const NOTHROW
   { class rect rect((LPCRECT)this); rect.deflate(lpRect); return rect; }
rect rect::operator&(const RECT& rect2) const NOTHROW
   { class rect rect; ::IntersectRect(&rect, (LPCRECT)this, (LPCRECT)&rect2);
      return rect; }
rect rect::operator|(const RECT& rect2) const NOTHROW
   { class rect rect; ::UnionRect(&rect, (LPCRECT)this, (LPCRECT)&rect2);
      return rect; }
bool rect::subtract(LPCRECT lpRectSrc1, LPCRECT lpRectSrc2) NOTHROW
   { return ::SubtractRect(this, lpRectSrc1, lpRectSrc2) != FALSE; }

void rect::normalize() NOTHROW
   {
      int32_t nTemp;
      if (left > right)
      {
         nTemp = left;
         left = right;
         right = nTemp;
      }
      if (top > bottom)
      {
         nTemp = top;
         top = bottom;
         bottom = nTemp;
      }
   }

void rect::inflate(LPCRECT lpRect) NOTHROW
   {
      left -= lpRect->left;      top -= lpRect->top;
      right += lpRect->right;      bottom += lpRect->bottom;
   }

void rect::inflate(int32_t l, int32_t t, int32_t r, int32_t b) NOTHROW
   {
      left -= l;         top -= t;
      right += r;         bottom += b;
   }

void rect::deflate(LPCRECT lpRect) NOTHROW
{
   left += lpRect->left;   top += lpRect->top;
   right -= lpRect->right;   bottom -= lpRect->bottom;
}

void rect::deflate(int32_t l, int32_t t, int32_t r, int32_t b) NOTHROW
   {
      left += l;      top += t;
      right -= r;      bottom -= b;
   }

rect rect::MulDiv(int32_t nMultiplier, int32_t nDivisor) const NOTHROW
   {
      return rect(
         ::MulDiv(left, nMultiplier, nDivisor),
         ::MulDiv(top, nMultiplier, nDivisor),
         ::MulDiv(right, nMultiplier, nDivisor),
         ::MulDiv(bottom, nMultiplier, nDivisor));
   }

int64_t rect::area()
   { return size().area(); }


void rect::get_bounding_rect(const POINT * lppoint, ::count count)
{

   point_array::get_bounding_rect(this, lppoint, count);

}

void rect::get_bounding_rect(const point_array & pointa)
{

   pointa.get_bounding_rect(this);

}






































































// rect64
rect64::rect64() NOTHROW
   { /* random filled */ }
rect64::rect64(int64_t l, int64_t t, int64_t r, int64_t b) NOTHROW
   { left = l; top = t; right = r; bottom = b; }
rect64::rect64(const RECT64 & srcRect) NOTHROW
   { ::copy(this, &srcRect); }
rect64::rect64(const RECT & srcRect) NOTHROW
   { ::copy(this, &srcRect); }
rect64::rect64(const RECT64 * lpSrcRect) NOTHROW
   { ::copy(this, lpSrcRect); }
rect64::rect64(const RECT * lpSrcRect) NOTHROW
   { ::copy(this, lpSrcRect); }
rect64::rect64(POINT64 point64, SIZE64 size64) NOTHROW
   { right = (left = point64.x) + size64.cx; bottom = (top = point64.y) + size64.cy; }
rect64::rect64(POINT64 topLeft, POINT64 bottomRight) NOTHROW
   { left = topLeft.x; top = topLeft.y;
      right = bottomRight.x; bottom = bottomRight.y; }
int64_t rect64::width() const NOTHROW
   { return right - left; }
int64_t rect64::height() const NOTHROW
   { return bottom - top; }
size64 rect64::size() const NOTHROW
   { return size64(right - left, bottom - top); }
point64& rect64::top_left() NOTHROW
   { return *((point64*)this); }
point64& rect64::bottom_right() NOTHROW
   { return *((point64*)this+1); }
const point64& rect64::top_left() const NOTHROW
   { return *((point64*)this); }
const point64& rect64::bottom_right() const NOTHROW
   { return *((point64*)this+1); }
void rect64::swap_left_right() NOTHROW
   { swap_left_right((RECT64 *)(this)); }
void WINAPI rect64::swap_left_right(RECT64 * lpRect) NOTHROW
   { int64_t temp = lpRect->left; lpRect->left = lpRect->right; lpRect->right = temp; }
rect64::operator RECT64 *() NOTHROW
   { return this; }
rect64::operator const RECT64 *() const NOTHROW
   { return this; }
rect64::operator rect() const
{
   return rect(*this);
}
bool rect64::contains(POINT64 point) const NOTHROW
   { return ::contains(this, point); }
void rect64::set(int64_t x1, int64_t y1, int64_t x2, int64_t y2) NOTHROW
   { ::set_rect(this, x1, y1, x2, y2); }
void rect64::set(POINT64 topLeft, POINT64 bottomRight) NOTHROW
   { ::set_rect(this, topLeft.x, topLeft.y, bottomRight.x, bottomRight.y); }
void rect64::null() NOTHROW
   { ::null(this); }
void rect64::copy(const RECT64 * lpSrcRect) NOTHROW
   { ::copy(this, lpSrcRect); }
bool rect64::is_equal(const RECT64 * lpRect) const NOTHROW
   { return ::is_equal(this, lpRect); }
void rect64::inflate(int64_t x, int64_t y) NOTHROW
   { ::inflate(this, x, y); }
void rect64::inflate(SIZE64 size64) NOTHROW
   { ::inflate(this, size64.cx, size64.cy); }
void rect64::deflate(int64_t x, int64_t y) NOTHROW
   { ::inflate(this, -x, -y); }
void rect64::deflate(SIZE64 size64) NOTHROW
   { ::inflate(this, -size64.cx, -size64.cy); }
void rect64::offset(int64_t x, int64_t y) NOTHROW
   { ::offset(this, x, y); }
void rect64::offset(POINT64 point64) NOTHROW
   { ::offset(this, point64.x, point64.y); }
void rect64::size(SIZE64 s) NOTHROW
{
   this->size(s.cx, s.cy);
}
void rect64::rsize(SIZE64 s) NOTHROW
{
   this->rsize(s.cx, s.cy);
}
void rect64::size(int64_t cx,int64_t cy) NOTHROW
{
   ::resize(this,cx,cy);
}
void rect64::rsize(int64_t cx,int64_t cy) NOTHROW
{
   ::reverse_size(this,cx,cy);
}
void rect64::offset(SIZE64 size64) NOTHROW
   { ::offset(this, size64.cx, size64.cy); }
void rect64::move_to_y(int64_t y) NOTHROW
   { bottom = height() + y; top = y; }
void rect64::move_to_x(int64_t x) NOTHROW
   { right = width() + x; left = x; }
void rect64::move_to(int64_t x, int64_t y) NOTHROW
   { move_to_x(x); move_to_y(y); }
void rect64::move_to(POINT64 pt) NOTHROW
   { move_to_x(pt.x); move_to_y(pt.y); }
bool rect64::intersect(const RECT64 * lpRect1, const RECT64 * lpRect2) NOTHROW
   { return ::intersect(this, lpRect1, lpRect2);}
bool rect64::unite(const RECT64 * lpRect1, const RECT64 * lpRect2) NOTHROW
   { return ::unite(this, lpRect1, lpRect2); }
void rect64::operator=(const RECT64& srcRect) NOTHROW
   { ::copy(this, &srcRect); }
bool rect64::operator==(const RECT64& rect64) const NOTHROW
   { return ::is_equal(this, &rect64); }
bool rect64::operator!=(const RECT64& rect64) const NOTHROW
   { return !::is_equal(this, &rect64); }
void rect64::operator+=(POINT64 point64) NOTHROW
   { ::offset(this, point64.x, point64.y); }
void rect64::operator+=(SIZE64 size64) NOTHROW
   { ::offset(this, size64.cx, size64.cy); }
void rect64::operator+=(const RECT64 * lpRect) NOTHROW
   { inflate(lpRect); }
void rect64::operator-=(POINT64 point64) NOTHROW
   { ::offset(this, -point64.x, -point64.y); }
void rect64::operator-=(SIZE64 size64) NOTHROW
   { ::offset(this, -size64.cx, -size64.cy); }
void rect64::operator-=(const RECT64 * lpRect) NOTHROW
   { deflate(lpRect); }
void rect64::operator&=(const RECT64& rect64) NOTHROW
   { ::intersect(this, this, &rect64); }
void rect64::operator|=(const RECT64& rect64) NOTHROW
   { ::unite(this, this, &rect64); }
rect64 rect64::operator+(POINT64 pt) const NOTHROW
   { rect64 rect64(*this); ::offset(&rect64, pt.x, pt.y); return rect64; }
rect64 rect64::operator-(POINT64 pt) const NOTHROW
   { rect64 rect64(*this); ::offset(&rect64, -pt.x, -pt.y); return rect64; }
rect64 rect64::operator+(SIZE64 size64) const NOTHROW
   { rect64 rect64(*this); ::offset(&rect64, size64.cx, size64.cy); return rect64; }
rect64 rect64::operator-(SIZE64 size64) const NOTHROW
   { rect64 rect64(*this); ::offset(&rect64, -size64.cx, -size64.cy); return rect64; }
rect64 rect64::operator+(const RECT64 * lpRect) const NOTHROW
   { rect64 rect64(this); rect64.inflate(lpRect); return rect64; }
rect64 rect64::operator-(const RECT64 * lpRect) const NOTHROW
   { rect64 rect64(this); rect64.deflate(lpRect); return rect64; }
rect64 rect64::operator&(const RECT64& rect2) const NOTHROW
   { rect64 rect64; ::intersect(&rect64, this, &rect2);
      return rect64; }
rect64 rect64::operator|(const RECT64& rect2) const NOTHROW
   { rect64 rect64; ::unite(&rect64, this, &rect2);
      return rect64; }
//bool rect64::subtract(const RECT64 * lpRectSrc1, const RECT64 * lpRectSrc2) NOTHROW
//   { return ::subtract(this, lpRectSrc1, lpRectSrc2); }

void rect64::normalize() NOTHROW
   {
      int64_t nTemp;
      if (left > right)
      {
         nTemp = left;
         left = right;
         right = nTemp;
      }
      if (top > bottom)
      {
         nTemp = top;
         top = bottom;
         bottom = nTemp;
      }
   }

void rect64::inflate(const RECT64 * lpRect) NOTHROW
   {
      left -= lpRect->left;      top -= lpRect->top;
      right += lpRect->right;      bottom += lpRect->bottom;
   }

void rect64::inflate(int64_t l, int64_t t, int64_t r, int64_t b) NOTHROW
   {
      left -= l;         top -= t;
      right += r;         bottom += b;
   }

void rect64::deflate(const RECT64 * lpRect) NOTHROW
   {
      left += lpRect->left;   top += lpRect->top;
      right -= lpRect->right;   bottom -= lpRect->bottom;
   }

void rect64::deflate(int64_t l, int64_t t, int64_t r, int64_t b) NOTHROW
   {
      left += l;      top += t;
      right -= r;      bottom -= b;
   }

rect64 rect64::MulDiv(int64_t nMultiplier, int64_t nDivisor) const NOTHROW
   {
      return rect64(
         ::MulDiv(left, nMultiplier, nDivisor),
         ::MulDiv(top, nMultiplier, nDivisor),
         ::MulDiv(right, nMultiplier, nDivisor),
         ::MulDiv(bottom, nMultiplier, nDivisor));
   }

int64_t rect64::area()
   { return size().area(); }

















































// rectd
rectd::rectd() NOTHROW
   { /* random filled */ }
rectd::rectd(double l, double t, double r, double b) NOTHROW
   { left = (double) l; top = (double) t; right = (double) r; bottom = (double) b; }
rectd::rectd(const RECTD& srcRect) NOTHROW
   { ::copy(this, &srcRect); }
rectd::rectd(const RECT64& srcRect) NOTHROW
   { ::copy(this, &srcRect); }
rectd::rectd(LPCRECTD lpSrcRect) NOTHROW
   { ::copy(this, lpSrcRect); }
rectd::rectd(POINTD point, SIZED size) NOTHROW
   { right = (left = point.x) + size.cx; bottom = (top = point.y) + size.cy; }
rectd::rectd(POINTD topLeft, POINTD bottomRight) NOTHROW
   { left = topLeft.x; top = topLeft.y;
      right = bottomRight.x; bottom = bottomRight.y; }
double rectd::width() const NOTHROW
   { return right - left; }
double rectd::height() const NOTHROW
   { return bottom - top; }
class sized rectd::size() const NOTHROW
{
   class sized sizeRet(right - left, bottom - top);
   return sizeRet;
}

pointd & rectd::top_left() NOTHROW
   { return *((pointd*)this); }
pointd & rectd::bottom_right() NOTHROW
   { return *((pointd*)this+1); }
const pointd & rectd::top_left() const NOTHROW
   { return *((pointd*)this); }
const pointd & rectd::bottom_right() const NOTHROW
   { return *((pointd*)this+1); }
void rectd::swap_left_right() NOTHROW
   { swap_left_right(LPRECTD(this)); }
void WINAPI rectd::swap_left_right(LPRECTD lpRect) NOTHROW
   { double temp = lpRect->left; lpRect->left = lpRect->right; lpRect->right = temp; }
rectd::operator LPRECTD() NOTHROW
   { return this; }
rectd::operator LPCRECTD() const NOTHROW
   { return (LPCRECTD) this; }
bool rectd::contains(POINTD point) const NOTHROW
   { return ::contains((LPCRECTD) this, point) != FALSE; }
void rectd::set(double x1, double y1, double x2, double y2) NOTHROW
   { ::set_rect(this, x1, y1, x2, y2); }
void rectd::set(POINTD topLeft, POINTD bottomRight) NOTHROW
   { ::set_rect(this, topLeft.x, topLeft.y, bottomRight.x, bottomRight.y); }
void rectd::null() NOTHROW
   { ::null(this); }
void rectd::copy(LPCRECTD lpSrcRect) NOTHROW
   { ::copy(this, lpSrcRect); }
bool rectd::is_equal(LPCRECTD lpRect) const NOTHROW
   { return ::is_equal((LPCRECTD) this, lpRect) != FALSE; }
void rectd::inflate(double x, double y) NOTHROW
   { ::inflate(this, x, y); }
void rectd::inflate(SIZED size) NOTHROW
   { ::inflate(this, size.cx, size.cy); }
void rectd::deflate(double x, double y) NOTHROW
   { ::inflate(this, -x, -y); }
void rectd::deflate(SIZED size) NOTHROW
   { ::inflate(this, -size.cx, -size.cy); }
void rectd::offset(double x, double y) NOTHROW
   { ::offset(this, x, y); }
void rectd::offset(POINTD point) NOTHROW
   { ::offset(this, point.x, point.y); }
void rectd::offset(SIZED size) NOTHROW
   { ::offset(this, size.cx, size.cy); }
void rectd::move_to_y(double y) NOTHROW
   { bottom = height() + y; top = y; }
void rectd::move_to_x(double x) NOTHROW
   { right = width() + x; left = x; }
void rectd::move_to(double x, double y) NOTHROW
   { move_to_x(x); move_to_y(y); }
void rectd::move_to(POINTD pt) NOTHROW
   { move_to_x(pt.x); move_to_y(pt.y); }
bool rectd::intersect(LPCRECTD lpRect1, LPCRECTD lpRect2) NOTHROW
{ return ::intersect(this, lpRect1, lpRect2) != FALSE;}
bool rectd::unite(LPCRECTD lpRect1, LPCRECTD lpRect2) NOTHROW
   { return ::unite(this, lpRect1, lpRect2) != FALSE; }
void rectd::operator=(const RECTD& srcRect) NOTHROW
   { ::copy(this, (LPCRECTD) &srcRect); }
bool rectd::operator==(const RECTD& rectd) const NOTHROW
   { return ::is_equal((LPCRECTD)this, (LPCRECTD) &rectd) != FALSE; }
bool rectd::operator!=(const RECTD& rectd) const NOTHROW
   { return !::is_equal((LPCRECTD)this, (LPCRECTD) &rectd) != FALSE; }
void rectd::operator+=(POINTD point) NOTHROW
   { ::offset(this, point.x, point.y); }
void rectd::operator+=(SIZED size) NOTHROW
   { ::offset(this, size.cx, size.cy); }
void rectd::operator+=(LPCRECTD lpRect) NOTHROW
   { inflate(lpRect); }
void rectd::operator-=(POINTD point) NOTHROW
   { ::offset(this, -point.x, -point.y); }
void rectd::operator-=(SIZED size) NOTHROW
   { ::offset(this, -size.cx, -size.cy); }
void rectd::operator-=(LPCRECTD lpRect) NOTHROW
   { deflate(lpRect); }
void rectd::operator&=(const RECTD& rectd) NOTHROW
   { ::intersect(this, this, (LPCRECTD)&rectd); }
void rectd::operator|=(const RECTD& rectd) NOTHROW
   { ::unite(this, this,(LPCRECTD) &rectd); }
rectd rectd::operator+(POINTD pt) const NOTHROW
   { rectd rectd(*this); ::offset(&rectd, pt.x, pt.y); return rectd; }
rectd rectd::operator-(POINTD pt) const NOTHROW
   { rectd rectd(*this); ::offset(&rectd, -pt.x, -pt.y); return rectd; }
rectd rectd::operator+(SIZED size) const NOTHROW
   { rectd rectd(*this); ::offset(&rectd, size.cx, size.cy); return rectd; }
rectd rectd::operator-(SIZED size) const NOTHROW
   { rectd rectd(*this); ::offset(&rectd, -size.cx, -size.cy); return rectd; }
rectd rectd::operator+(LPCRECTD lpRect) const NOTHROW
   { class rectd rectd((LPCRECTD)this); rectd.inflate(lpRect); return rectd; }
rectd rectd::operator-(LPCRECTD lpRect) const NOTHROW
   { class rectd rectd((LPCRECTD)this); rectd.deflate(lpRect); return rectd; }
rectd rectd::operator&(const RECTD& rect2) const NOTHROW
{ class rectd rectd; ::intersect(&rectd, (LPCRECTD)this, (LPCRECTD)&rect2);
      return rectd; }
rectd rectd::operator|(const RECTD& rect2) const NOTHROW
   { class rectd rectd; ::unite(&rectd, (LPCRECTD)this, (LPCRECTD)&rect2);
      return rectd; }
//bool rectd::subtract(LPCRECTD lpRectSrc1, LPCRECTD lpRectSrc2) NOTHROW
  // { return ::subtract(this, lpRectSrc1, lpRectSrc2) != FALSE; }

void rectd::normalize() NOTHROW
   {
      double nTemp;
      if (left > right)
      {
         nTemp = left;
         left = right;
         right = nTemp;
      }
      if (top > bottom)
      {
         nTemp = top;
         top = bottom;
         bottom = nTemp;
      }
   }

void rectd::inflate(LPCRECTD lpRect) NOTHROW
   {
      left -= lpRect->left;      top -= lpRect->top;
      right += lpRect->right;      bottom += lpRect->bottom;
   }

void rectd::inflate(double l, double t, double r, double b) NOTHROW
   {
      left -= l;         top -= t;
      right += r;         bottom += b;
   }

void rectd::deflate(LPCRECTD lpRect) NOTHROW
{
   left += lpRect->left;   top += lpRect->top;
   right -= lpRect->right;   bottom -= lpRect->bottom;
}

void rectd::deflate(double l, double t, double r, double b) NOTHROW
   {
      left += l;      top += t;
      right -= r;      bottom -= b;
   }

rectd rectd::MulDiv(double nMultiplier, double nDivisor) const NOTHROW
   {
      return rectd(  left     *  nMultiplier / nDivisor,
                     top      *  nMultiplier / nDivisor,
                     right    *  nMultiplier / nDivisor,
                     bottom   *  nMultiplier / nDivisor);
   }

double rectd::area()
   { return size().area(); }


void rectd::get_bounding_rect(const POINTD * lppoint, ::count count)
{

   pointd_array::get_bounding_rect(this, lppoint, count);

}

void rectd::get_bounding_rect(const pointd_array & pointa)
{

   pointa.get_bounding_rect(this);

}





void rectd::CenterOf(LPCRECTD lpcrect,SIZED size)
{
   double cx = size.cx;
   double cy = size.cy;

   double dx = ::width(lpcrect);
   double dy = ::height(lpcrect);

   left     = lpcrect->left + (dx - cx) / 2;
   top      = lpcrect->top + (dy - cy) / 2;
   right    = left + cx;
   bottom   = top + cy;

}

void rectd::CenterOf(LPCRECTD lpcrect)
{

   CenterOf(lpcrect,size());

}





double rectd::minimum_signed_absolute_dimension(bool bNegativePreference) const NOTHROW
{

   double w = width();

   double h = height();

   if(fabs(w) < fabs(h))
   {

      return w;

   }
   else if(fabs(h) < fabs(w))
   {

      return h;

   }
   else if(bNegativePreference) // absolutely equal, prefer negative ...
   {

      return MIN(w,h);

   }
   else // ... otherwise prefer positive
   {

      return MAX(w,h);

   }


}


double rectd::maximum_signed_absolute_dimension(bool bPositivePreference) const NOTHROW
{

   double w = width();

   double h = height();

   if(fabs(w) > fabs(h))
   {

      return w;

   }
   else if(fabs(h) > fabs(w))
   {

      return h;

   }
   else if(bPositivePreference) // absolutely equal, prefer positive ...
   {

      return MAX(w,h);

   }
   else // ... otherwise prefer negative
   {

      return MIN(w,h);

   }


}



double rectd::minimum_absolute_dimension() const NOTHROW{ return MIN(fabs(width()),fabs(height())); }
double rectd::maximum_absolute_dimension() const NOTHROW{ return MIN(fabs(width()),fabs(height())); }
