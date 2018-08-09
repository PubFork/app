#pragma once


inline CLASS_DECL_AURA LONG width(LPCRECT lpcrect)
{
   return lpcrect->right - lpcrect->left;
}

inline CLASS_DECL_AURA LONG height(LPCRECT lpcrect)
{
   return lpcrect->bottom - lpcrect->top;
}

inline CLASS_DECL_AURA LONG width(const RECT & rect)
{
   return width(&rect);
}

inline CLASS_DECL_AURA LONG height(const RECT & rect)
{
   return height(&rect);
}

inline CLASS_DECL_AURA LONG area(LPCRECT lpcrect)
{
   return width(lpcrect) * height(lpcrect);
}

inline CLASS_DECL_AURA LONG area(const RECT & rect)
{
   return width(rect) * height(rect);
}


inline CLASS_DECL_AURA RECT & inflate_rect(RECT & rect, LONG dleft, LONG dtop, LONG dright, LONG dbottom)
{
   rect.left -= dleft;
   rect.right += dtop;
   rect.top -= dright;
   rect.bottom += dbottom;
   return rect;
}

inline CLASS_DECL_AURA LPRECT inflate_rect(LPRECT lprect, LONG dleft, LONG dtop, LONG dright, LONG dbottom)
{
   return &inflate_rect(*lprect, dleft, dtop, dright, dbottom);
}

template < typename R >
inline R * deflate_rect(R * prect,decltype(R::left) dleft,decltype(R::top) dtop,decltype(R::right) dright,decltype(R::bottom) dbottom)
{
   prect->left += dleft;
   prect->right -= dtop;
   prect->top += dright;
   prect->bottom -= dbottom;
   return prect;
}

template < typename R >
inline R & deflate_rect(R & prect,decltype(R::left) dleft,decltype(R::top) dtop,decltype(R::right) dright,decltype(R::bottom) dbottom)
{
   return *deflate_rect(&prect, dleft, dtop, dright, dbottom);
}

template < typename R >
inline R * deflate_rect(R * prect,decltype(R::left) horz,decltype(R::top) vert)
{
   return deflate_rect(prect, horz, vert, horz, vert);
}

template < typename R >
inline R & deflate_rect(R & prect,decltype(R::left) horz,decltype(R::top) vert)
{
   return *deflate_rect(&prect,horz,vert);
}

template < typename R >
inline R * deflate_rect(R * prect,decltype(R::left) dim)
{
   return deflate_rect(prect,dim,dim);
}

template < typename R >
inline R & deflate_rect(R & prect,decltype(R::left) dim)
{
   return *deflate_rect(&prect,dim);
}


//inline CLASS_DECL_AURA LPRECT deflate_rect(LPRECT lprect, LONG dleft, LONG dtop, LONG dright, LONG dbottom)
//{
//   return &deflate_rect(*lprect, dleft, dtop, dright, dbottom);
//}

//inline CLASS_DECL_AURA RECT64 & deflate_rect(RECT64 & rect,LONG dleft,LONG dtop,LONG dright,LONG dbottom)
//{
//   rect.left += dleft;
//   rect.right -= dtop;
//   rect.top += dright;
//   rect.top -= dbottom;
//   return rect;
//}
//
//
//inline CLASS_DECL_AURA RECT64 * deflate_rect(RECT64 * lprect,LONG dleft,LONG dtop,LONG dright,LONG dbottom)
//{
//   return &deflate_rect(*lprect,dleft,dtop,dright,dbottom);
//}

inline CLASS_DECL_AURA RECT & inflate_rect(RECT & rect, LONG dx, LONG dy)
{
   return inflate_rect(rect, dx, dy, dx, dy);
}

inline CLASS_DECL_AURA LPRECT inflate_rect(LPRECT lprect, LONG dx, LONG dy)
{
   return &inflate_rect(*lprect, dx, dy);
}

//inline CLASS_DECL_AURA RECT & deflate_rect(RECT & rect, LONG dx, LONG dy)
//{
//   return deflate_rect(rect, dx, dy, dx, dy);
//}
//
//inline CLASS_DECL_AURA LPRECT deflate_rect(LPRECT lprect, LONG dx, LONG dy)
//{
//   return &deflate_rect(*lprect, dx, dy);
//}
//
//inline CLASS_DECL_AURA RECT64 & deflate_rect(RECT64 & rect,LONG dx,LONG dy)
//{
//   return deflate_rect(rect,dx,dy,dx,dy);
//}
//
//
//inline CLASS_DECL_AURA RECT64 * deflate_rect(RECT64 * lprect,LONG dx,LONG dy)
//{
//   return &deflate_rect(*lprect,dx,dy);
//}
//
inline CLASS_DECL_AURA RECT & inflate_rect(RECT & rect, LONG d)
{
   return inflate_rect(rect, d, d);
}

inline CLASS_DECL_AURA LPRECT inflate_rect(LPRECT lprect, LONG d)
{
   return &inflate_rect(*lprect, d);
}

//inline CLASS_DECL_AURA RECT & deflate_rect(RECT & rect, LONG d)
//{
//   return deflate_rect(rect, d, d);
//}
//
//inline CLASS_DECL_AURA LPRECT deflate_rect(LPRECT lprect, LONG d)
//{
//   return &deflate_rect(*lprect, d);
//}
//
//inline CLASS_DECL_AURA RECT64 & deflate_rect(RECT64 & rect,LONG d)
//{
//   return deflate_rect(rect,d,d);
//}
//
//inline CLASS_DECL_AURA RECT64 * deflate_rect(RECT64  * lprect,LONG d)
//{
//   return &deflate_rect(*lprect,d);
//}

inline CLASS_DECL_AURA RECT & rect_by_dimension(RECT & rect, LONG x, LONG y, LONG cx, LONG cy)
{
   rect.left = x;
   rect.top = y;
   rect.right = x + cx;
   rect.bottom = y + cy;
   return rect;
}

inline CLASS_DECL_AURA RECT & rect_dim(RECT & rect, LONG x, LONG y, LONG cx, LONG cy)
{
   return rect_by_dimension(rect, x, y, cx, cy);
}

inline CLASS_DECL_AURA LPRECT rect_by_dimension(LPRECT lprect, LONG x, LONG y, LONG cx, LONG cy)
{
   return &rect_by_dimension(*lprect, x, y, cx, cy);
}

inline CLASS_DECL_AURA LPRECT rect_dim(LPRECT lprect, LONG x, LONG y, LONG cx, LONG cy)
{
   return rect_by_dimension(lprect, x, y, cx, cy);
}

inline CLASS_DECL_AURA ::rect rect_by_dimension(LONG x, LONG y, LONG cx, LONG cy)
{
   ::rect r;
   return rect_by_dimension(r, x, y, cx, cy);
}

inline CLASS_DECL_AURA ::rect rect_dim(LONG x, LONG y, LONG cx, LONG cy)
{
   return rect_by_dimension(x, y, cx, cy);
}


inline CLASS_DECL_AURA POINT & point_by_coordinate(POINT & p, LONG x, LONG y)
{
   p.x = x;
   p.y = y;
   return p;
}

inline CLASS_DECL_AURA POINT & point_coord(POINT & p, LONG x, LONG y)
{
   return point_by_coordinate(p, x, y);
}


inline CLASS_DECL_AURA LPPOINT point_by_coordinate(LPPOINT lppt, LONG x, LONG y)
{
   return &point_by_coordinate(*lppt, x, y);
}

inline CLASS_DECL_AURA LPPOINT point_coord(LPPOINT lppt, LONG x, LONG y)
{
   return point_by_coordinate(lppt, x, y);
}

inline CLASS_DECL_AURA POINT point_by_coordinate(LONG x, LONG y)
{
   POINT p;
   return point_by_coordinate(p, x, y);
}

inline CLASS_DECL_AURA POINT point_coord(LONG x, LONG y)
{
   return point_by_coordinate(x, y);
}

inline CLASS_DECL_AURA POINT & offset(POINT & pt, LONG x, LONG y)
{
   pt.x += x;
   pt.y += y;
   return pt;
}

inline CLASS_DECL_AURA LONG offset_x(LPRECT lprect, LONG x)
{
   lprect->left += x;
   lprect->right+= x;
   return x;
}

inline CLASS_DECL_AURA LONG  offset_y(LPRECT lprect, LONG y)
{
   lprect->top += y;
   lprect->bottom += y;
   return y;
}

inline CLASS_DECL_AURA double offset_x(LPRECTD lprect, double x)
{
   lprect->left += x;
   lprect->right += x;
   return x;
}

inline CLASS_DECL_AURA double  offset_y(LPRECTD lprect, double y)
{
   lprect->top += y;
   lprect->bottom += y;
   return y;
}

CLASS_DECL_AURA bool polygon_contains(LPCPOINT lppt, LPCPOINT lpptPolygon, i32 iCount);

CLASS_DECL_AURA bool polygon_contains(LPCPOINT64 lppt, LPCPOINT64 lpptPolygon, i32 iCount);

CLASS_DECL_AURA bool polygon_contains(LPCPOINTD lppt, LPCPOINTD lpptPolygon, i32 iCount);


inline CLASS_DECL_AURA POINT & top_left(LPRECT lpcrect)
{
   return *(POINT *) lpcrect;
}

inline CLASS_DECL_AURA const POINT & top_left(LPCRECT lpcrect)
{
   return *(const POINT *)lpcrect;
}

inline CLASS_DECL_AURA const POINT & top_left(const RECT & rect)
{
   return ::top_left(&rect);
}




CLASS_DECL_AURA bool deflate(LPRECT prect,LPCRECT lpcrect);



#if defined(MACOS)




void copy(CGRect & rectDst, const RECT & rectSrc);
void copy(LPRECT lprectDst, const CGRect & rectSrc);

#endif


CLASS_DECL_AURA int_bool IsRectEmpty(const RECT & rect);





inline CLASS_DECL_AURA RECTD & rectd_by_dimension(RECTD & rectd, double x, double y, double cx, double cy)
{
   rectd.left = x;
   rectd.top = y;
   rectd.right = x + cx;
   rectd.bottom = y + cy;
   return rectd;
}

inline CLASS_DECL_AURA RECTD & rectd_dim(RECTD & rectd, double x, double y, double cx, double cy)
{
   return rectd_by_dimension(rectd, x, y, cx, cy);
}

inline CLASS_DECL_AURA LPRECTD rectd_by_dimension(LPRECTD lprectd, double x, double y, double cx, double cy)
{
   return &rectd_by_dimension(*lprectd, x, y, cx, cy);
}

inline CLASS_DECL_AURA LPRECTD rectd_dim(LPRECTD lprectd, double x, double y, double cx, double cy)
{
   return rectd_by_dimension(lprectd, x, y, cx, cy);
}

inline CLASS_DECL_AURA::rectd rectd_by_dimension(double x, double y, double cx, double cy)
{
   ::rectd r;
   return rectd_by_dimension(r, x, y, cx, cy);
}

inline CLASS_DECL_AURA::rectd rectd_dim(double x, double y, double cx, double cy)
{
   return rectd_by_dimension(x, y, cx, cy);
}


inline CLASS_DECL_AURA POINTD & pointd_by_coordinate(POINTD & p, double x, double y)
{
   p.x = x;
   p.y = y;
   return p;
}

inline CLASS_DECL_AURA POINTD & pointd_coord(POINTD & p, double x, double y)
{
   return pointd_by_coordinate(p, x, y);
}


inline CLASS_DECL_AURA LPPOINTD pointd_by_coordinate(LPPOINTD lppt, double x, double y)
{
   return &pointd_by_coordinate(*lppt, x, y);
}

inline CLASS_DECL_AURA LPPOINTD pointd_coord(LPPOINTD lppt, double x, double y)
{
   return pointd_by_coordinate(lppt, x, y);
}

inline CLASS_DECL_AURA POINTD pointd_by_coordinate(double x, double y)
{
   POINTD p;
   return pointd_by_coordinate(p, x, y);
}

inline CLASS_DECL_AURA POINTD pointd_coord(double x, double y)
{
   return pointd_by_coordinate(x, y);
}

inline CLASS_DECL_AURA POINTD & offset(POINTD & pt, double x, double y)
{
   pt.x += x;
   pt.y += y;
   return pt;
}

CLASS_DECL_AURA bool polygon_contains(LPCPOINTD lppt, LPCPOINTD lpptPolygon, i32 iCount);

CLASS_DECL_AURA bool polygon_contains(LPCPOINT64 lppt, LPCPOINT64 lpptPolygon, i32 iCount);

CLASS_DECL_AURA bool polygon_contains(LPCPOINTD lppt, LPCPOINTD lpptPolygon, i32 iCount);


inline CLASS_DECL_AURA POINTD & top_left(LPRECTD lpcrectd)
{
   return *(POINTD *)lpcrectd;
}

inline CLASS_DECL_AURA const POINTD & top_left(LPCRECTD lpcrectd)
{
   return *(const POINTD *)lpcrectd;
}

inline CLASS_DECL_AURA const POINTD & top_left(const RECTD & rectd)
{
   return ::top_left(&rectd);
}




CLASS_DECL_AURA bool deflate(LPRECTD prectd, LPCRECTD lpcrectd);



#if defined(MACOS)




void copy(CGRect & rectdDst, const RECTD & rectdSrc);
void copy(LPRECTD lprectdDst, const CGRect & rectdSrc);

#endif


CLASS_DECL_AURA int_bool IsRectEmpty(const RECTD & rectd);


