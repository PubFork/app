#include "framework.h"
//#include "math.h"
//#include "draw2d_const.h"
//#include "draw2d_object.h"
//#include "draw2d_region.h"


namespace draw2d
{


   region::region()
   {

      m_etype        = type_none;
      m_bUpdated     = false;
      m_lppoints = NULL;
      m_lppolycounts = NULL;

   }


   region::region(const region & region)
   {

      m_lppolycounts = NULL;
      m_lppoints     = NULL;
      m_etype        = type_none;
      m_bUpdated     = false;

      operator = (region);

   }


   region::~region()
   {

   }

   bool region::destroy()
   {

      e_type etype = m_etype;

      m_etype = type_none;

      switch(etype)
      {
      case type_none:
         return false;
      case type_rect:
         return true;
      case type_oval:
         return true;
      case type_polygon:
         ::aura::adel(m_lppoints);
         return true;
      case type_poly_polygon:
         ::aura::adel(m_lppoints);
         ::aura::adel(m_lppolycounts);
         return true;
      case type_round_rect:
         return true;
      case type_combine:
         m_pregion1.release();
         m_pregion2.release();
         return true;
      default:
         ::exception::throw_not_implemented(get_app());
      };

      return false;

   }


   /*bool region::CreateRectRgn(i32 x1, i32 y1, i32 x2, i32 y2)
   {

      m_pta.remove_all();

      m_pta.add(pointd(x1, y1));
      m_pta.add(pointd(x2, y2));

      m_etype = type_rect;

      m_bUpdated = false;

      return TRUE;

   }

   bool region::create_rect(LPCRECT lpRect)
   {

      m_pta.remove_all();

      m_pta.add(pointd(lpRect->left, lpRect->top));
      m_pta.add(pointd(lpRect->right, lpRect->bottom));

      m_etype = type_rect;

      m_bUpdated = false;

      return TRUE;

   }

   bool region::CreateEllipticRgn(i32 x1, i32 y1, i32 x2, i32 y2)
   {

      m_pta.remove_all();

      m_pta.add(pointd(x1, y1));
      m_pta.add(pointd(x2, y2));

      m_etype = type_elliptic;

      m_bUpdated = false;

      return TRUE;

   }

   bool region::CreateEllipticRgnIndirect(LPCRECT lpRect)
   {

      m_pta.remove_all();

      m_pta.add(pointd(lpRect->left, lpRect->top));
      m_pta.add(pointd(lpRect->right, lpRect->bottom));

      m_etype = type_elliptic;

      m_bUpdated = false;

      return TRUE;

   }

   bool region::CreatePolygonRgn(LPPOINT lpPoints, i32 nCount, i32 nMode)
   {

      m_pta.remove_all();

      for(i32 i = 0; i < nCount; i++)
      {
         m_pta.add(pointd(lpPoints[i].x, lpPoints[i].y));
      }

      m_etype = type_polygon;

      m_bUpdated = false;

      return TRUE;

   }

   bool region::CreatePolyPolygonRgn(LPPOINT lpPoints, LPINT lpPolyCounts, i32 nCount, i32 nPolyFillMode)
   {

      m_pta.remove_all();
      m_iaCount.remove_all();

      i32 n = 0;

      for(i32 i = 0; i < nCount; i++)
      {
         m_iaCount.add(lpPolyCounts[i]);
         for(i32 j = 0; j < lpPolyCounts[i]; j++)
         {
            m_pta.add(pointd(lpPoints[n].x, lpPoints[n].y));
            n++;
         }
      }

      m_etype = type_poly_polygon;

      m_bUpdated = false;

      return TRUE;

   }

   bool region::CreateRoundRectRgn(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3)
   {

      m_pta.remove_all();
      m_iaCount.remove_all();

      m_pta.add(pointd(x1, y1));
      m_pta.add(pointd(x2, y2));
      m_pta.add(pointd(x3, y3));

      m_etype = type_polygon;

      m_bUpdated = false;

      return TRUE;

   }

   bool region::CreateFromPath(::draw2d::dib * pdib)
   {
      UNREFERENCED_PARAMETER(pgraphics);
      ::exception::throw_interface_only(get_app());
   }

   #ifdef WINDOWS

   bool region::CreateFromData(const XFORM* lpXForm, i32 nCount, const RGNDATA* pRgnData)
   {
      UNREFERENCED_PARAMETER(lpXForm);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(pRgnData);
      ::exception::throw_interface_only(get_app());
   }

   i32 region::GetRegionData(LPRGNDATA lpRgnData, i32 nDataSize) const
   {
      UNREFERENCED_PARAMETER(lpRgnData);
      UNREFERENCED_PARAMETER(nDataSize);
      ::exception::throw_interface_only(get_app());
   }

   #endif

   void region::SetRectRgn(i32 x1, i32 y1, i32 x2, i32 y2)
   {
      UNREFERENCED_PARAMETER(x1);
      UNREFERENCED_PARAMETER(y1);
      UNREFERENCED_PARAMETER(x2);
      UNREFERENCED_PARAMETER(y2);
      ::exception::throw_interface_only(get_app());
   }

   void region::SetRectRgn(LPCRECT lpRect)
   {
      UNREFERENCED_PARAMETER(lpRect);
      ::exception::throw_interface_only(get_app());
   }

   i32 region::CombineRgn(const region* pRgn1, const region* pRgn2, i32 nCombineMode)
   {
      UNREFERENCED_PARAMETER(pRgn1);
      UNREFERENCED_PARAMETER(pRgn2);
      UNREFERENCED_PARAMETER(nCombineMode);
      ::exception::throw_interface_only(get_app());
   }

   i32 region::CopyRgn(const region* pRgnSrc)
   {
      UNREFERENCED_PARAMETER(pRgnSrc);
      ::exception::throw_interface_only(get_app());
   }

   bool region::EqualRgn(const region* pRgn) const
   {
      UNREFERENCED_PARAMETER(pRgn);
      ::exception::throw_interface_only(get_app());
   }

   i32 region::OffsetRgn(i32 x, i32 y)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      ::exception::throw_interface_only(get_app());
   }

   i32 region::OffsetRgn(POINT point)
   {
      UNREFERENCED_PARAMETER(point);
      ::exception::throw_interface_only(get_app());
   }

   i32 region::GetRgnBox(LPRECT lpRect) const
   {
      UNREFERENCED_PARAMETER(lpRect);
      ::exception::throw_interface_only(get_app());
   }

   i32 region::GetRgnBox(rect64 * lpRect) const
   {
      rect rect;
      i32 iRgn = GetRgnBox(rect);
      *lpRect = rect;
      return iRgn;
   }

   bool region::PtInRegion(i32 x, i32 y) const
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      ::exception::throw_interface_only(get_app());
   }

   bool region::PtInRegion(POINT point) const
   {
      UNREFERENCED_PARAMETER(point);
      ::exception::throw_interface_only(get_app());
   }

   bool region::RectInRegion(LPCRECT lpRect) const
   {
      UNREFERENCED_PARAMETER(lpRect);
      ::exception::throw_interface_only(get_app());
   }
   */


   //bool region::create_rect(i32 x1, i32 y1, i32 x2, i32 y2)
   //{

   //   if(m_etype != type_none)
   //   {

   //      destroy();

   //   }

   //   m_etype = type_rect;

   //   m_x1 = x1;
   //   m_y1 = y1;
   //   m_x2 = x2;
   //   m_y2 = y2;

   //   return true;


   //}

   bool region::create_rect(LPCRECT lprect)
   {

      if(m_etype != type_none)
      {

         destroy();

      }

      m_etype = type_rect;

      m_x1 = lprect->left;
      m_y1 = lprect->top;
      m_x2 = lprect->right;
      m_y2 = lprect->bottom;

      return true;


   }

   /*bool region::create_oval(i32 x1, i32 y1, i32 x2, i32 y2)
   {

      if(m_etype != type_none)
      {

         destroy();

      }

      m_etype = type_oval;

      m_x1 = x1;
      m_y1 = y1;
      m_x2 = x2;
      m_y2 = y2;

      return true;

   }*/

   bool region::create_oval(LPCRECT lprect)
   {

      if(m_etype != type_none)
      {

         destroy();

      }

      m_etype = type_oval;

      m_x1 = lprect->left;
      m_y1 = lprect->top;
      m_x2 = lprect->right;
      m_y2 = lprect->bottom;

      return true;

   }


   bool region::create_polygon(LPCPOINTD lppoints, i32 nCount, ::draw2d::e_fill_mode efillmode)
   {

      if(m_etype != type_none)
      {

         destroy();

      }

      m_etype = type_polygon;

      m_nCount = nCount;
      m_lppoints = new POINTD[m_nCount];
      memcpy(m_lppoints, lppoints, sizeof(POINTD) * m_nCount);
      m_efillmode = efillmode;

      return true;
   }


   bool region::create_polygon(LPCPOINT lppoints, i32 nCount, ::draw2d::e_fill_mode efillmode)
   {

      if(m_etype != type_none)
      {

         destroy();

      }

      m_etype = type_polygon;

      m_nCount = nCount;

      m_lppoints = new POINTD[m_nCount];

      for(index i = 0; i < m_nCount; i++)
      {

         m_lppoints[i].x = (double) lppoints[i].x;

         m_lppoints[i].y = (double) lppoints[i].y;

      }

      m_efillmode = efillmode;

      return true;

   }


   bool region::create_poly_polygon(LPCPOINTD lppoints, LPCINT lppolycounts, i32 nCount, ::draw2d::e_fill_mode efillmode)
   {

      if(m_etype != type_none)
      {

         destroy();

      }

      m_etype = type_poly_polygon;

      m_nCount = nCount;

      m_lppolycounts = new INT[m_nCount];

      memcpy(m_lppolycounts, lppolycounts, sizeof(INT) * m_nCount);

      i32 iTotalCount = 0;

      for(i32 i = 0; i < nCount; i++)
      {

         iTotalCount += m_lppolycounts[i];

      }

      m_lppoints = new POINTD[iTotalCount];

      memcpy(m_lppoints, lppoints, sizeof(POINTD) * iTotalCount);

      m_efillmode = efillmode;

      return true;

   }


   bool region::create_poly_polygon(LPCPOINT lppoints, LPCINT lppolycounts,i32 nCount,::draw2d::e_fill_mode efillmode)
   {

      if(m_etype != type_none)
      {

         destroy();

      }

      m_etype = type_poly_polygon;

      m_nCount = nCount;

      m_lppolycounts = new INT[m_nCount];

      memcpy(m_lppolycounts,lppolycounts,sizeof(INT)* m_nCount);

      i32 iTotalCount = 0;

      for(i32 i = 0; i < nCount; i++)
      {

         iTotalCount += m_lppolycounts[i];

      }

      m_lppoints = new POINTD[iTotalCount];

      for(i32 i = 0; i < iTotalCount; i++)
      {

         m_lppoints[i].x = lppoints[i].x;

         m_lppoints[i].y = lppoints[i].y;

      }

      m_efillmode = efillmode;

      return true;

   }


   //virtual bool add_round_rect(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3);
//      virtual bool add_path(::draw2d::path * ppath);

//      virtual void SetRectRgn(i32 x1, i32 y1, i32 x2, i32 y2);
//      virtual void SetRectRgn(LPCRECT lpRect);
   bool region::combine(const ::draw2d::region * prgn1, const ::draw2d::region * prgn2, e_combine ecombine)
   {

      sp(::draw2d::region) pregion1 = (::draw2d::region *) prgn1;

      sp(::draw2d::region) pregion2 = (::draw2d::region *) prgn2;

      if(m_etype != type_none)
      {

         destroy();

      }

      m_etype = type_combine;

      m_pregion1 = pregion1;

      m_pregion2 = pregion2;

      m_ecombine  = ecombine;

      return true;

   }

   region & region::operator = (const ::draw2d::region & regionSrc)
   {

      if(this == &regionSrc)
         return *this;

      if(m_etype != type_none)
      {

         destroy();

      }

      m_etype = regionSrc.m_etype;

      switch(m_etype)
      {
      case type_none:
         return *this;
      case type_rect:
      case type_oval:
         m_x1 = regionSrc.m_x1;
         m_y1 = regionSrc.m_y1;
         m_x2 = regionSrc.m_x2;
         m_y2 = regionSrc.m_y2;
         return *this;
      case type_polygon:
         m_nCount = regionSrc.m_nCount;
         m_lppoints = new POINTD[m_nCount];
         memcpy(m_lppoints, regionSrc.m_lppoints, sizeof(POINTD) * m_nCount);
         m_efillmode = regionSrc.m_efillmode;
         return *this;
      case type_poly_polygon:
      {
         m_nCount = regionSrc.m_nCount;
         m_lppolycounts = new INT[m_nCount];
         memcpy(m_lppolycounts, regionSrc.m_lppolycounts, sizeof(INT) * m_nCount);
         i32 iTotalCount = 0;
         for(i32 i = 0; i < m_nCount; i++)
         {
            iTotalCount += m_lppolycounts[i];
         }
         m_lppoints = new POINTD[iTotalCount];
         memcpy(m_lppoints, regionSrc.m_lppoints, sizeof(POINTD) * iTotalCount);
         m_efillmode = regionSrc.m_efillmode;
      }
      return *this;
      case type_round_rect:
         m_x1 = regionSrc.m_x1;
         m_y1 = regionSrc.m_y1;
         m_x2 = regionSrc.m_x2;
         m_y2 = regionSrc.m_y2;
         m_x3 = regionSrc.m_x3;
         m_y3 = regionSrc.m_y3;
         return *this;
      case type_combine:
         m_pregion1 = new ::draw2d::region(*regionSrc.m_pregion1);
         m_pregion2 = new ::draw2d::region(*regionSrc.m_pregion2);
         m_ecombine = regionSrc.m_ecombine;
         return *this;
      default:
         ::exception::throw_not_implemented(get_app());
      };
      return *this;

   }


   bool region::get_bounding_box(LPRECT lprect)
   {

      ::exception::throw_interface_only(get_app());

      return false;

   }


   bool region::contains(LPCPOINTD lppt)
   {

      return ((region *) this)->internal_contains(lppt);

   }


   bool region::translate(LPCPOINT ppt)
   {

      m_bUpdated = false;

      switch(m_etype)
      {
      case type_none:
         return false;
      case type_round_rect:
         m_x3 += ppt->x;
         m_y3 += ppt->y;
      case type_rect:
      case type_oval:
         m_x1 += ppt->x;
         m_y1 += ppt->y;
         m_x2 += ppt->x;
         m_y2 += ppt->y;
         return true;
      case type_polygon:
         for(i32 i = 0; i < m_nCount; i++)
         {
            m_lppoints[i].x += ppt->x;
            m_lppoints[i].y += ppt->y;
         }
         return true;
      case type_poly_polygon:
      {
         i32 iTotalCount = 0;
         for(i32 i = 0; i < m_nCount; i++)
         {
            iTotalCount += m_lppolycounts[i];
         }
         for(i32 i = 0; i < iTotalCount; i++)
         {
            m_lppoints[i].x += ppt->x;
            m_lppoints[i].y += ppt->y;
         }
      }
      return true;
      case type_combine:
      {
         bool bOk1 = m_pregion1->translate(ppt);
         bool bOk2 = m_pregion2->translate(ppt);
         return bOk1 && bOk2;
      }
      default:
         ::exception::throw_not_implemented(get_app());
      };
      return false;

   }


   bool region::contains(LPCPOINT ppt)
   {

      return contains(pointd(ppt));

   }
   void region::max_bounding_box(LPRECT lprect)
   {

      ::rectd rect;

      max_bounding_box(rect);

      ::copy(lprect,rect);

   }


   void region::max_bounding_box_rect(LPRECT lprect)
   {

      ::rectd rect;

      max_bounding_box_rect(rect);

      ::copy(lprect,rect);

   }

   void region::max_bounding_box_oval(LPRECT lprect)
   {

      ::rectd rect;

      max_bounding_box_oval(rect);

      ::copy(lprect,rect);

   }


   void region::max_bounding_box_polygon(LPRECT lprect)
   {

      ::rectd rect;

      max_bounding_box_polygon(rect);

      ::copy(lprect,rect);

   }


   void region::max_bounding_box_poly_polygon(LPRECT lprect)
   {

      ::rectd rect;

      max_bounding_box_poly_polygon(rect);

      ::copy(lprect,rect);

   }


   void region::max_bounding_box_combine(LPRECT lprect)
   {

      ::rectd rect;

      max_bounding_box_combine(rect);

      ::copy(lprect,rect);

   }




   void region::max_bounding_box(LPRECTD lprect)
   {

      switch(m_etype)
      {
      case type_none:
         return;
      case type_rect:
         return max_bounding_box_rect(lprect);
      case type_oval:
         return max_bounding_box_oval(lprect);
      case type_polygon:
         return max_bounding_box_polygon(lprect);
      case type_poly_polygon:
         return max_bounding_box_poly_polygon(lprect);
      case type_combine:
         return max_bounding_box_combine(lprect);
      default:
         ::exception::throw_not_implemented(get_app());
      }

   }


   void region::max_bounding_box_rect(LPRECTD lprect)
   {

      lprect->left = MIN(lprect->left,m_x1);
      lprect->right = MAX(lprect->right,m_x2);
      lprect->top = MIN(lprect->left,m_y1);
      lprect->bottom = MAX(lprect->right,m_y2);

   }

   void region::max_bounding_box_oval(LPRECTD lprect)
   {

      lprect->left = MIN(lprect->left,m_x1);
      lprect->right = MAX(lprect->right,m_x2);
      lprect->top = MIN(lprect->left,m_y1);
      lprect->bottom = MAX(lprect->right,m_y2);

   }


   void region::max_bounding_box_polygon(LPRECTD lprect)
   {

      if(m_nCount <= 0)
         return;

      for(int i = 0; i < m_nCount; i++)
      {

         lprect->left = MIN(lprect->left,m_lppoints[i].x);
         lprect->right = MAX(lprect->right,m_lppoints[i].x);
         lprect->top = MIN(lprect->left,m_lppoints[i].y);
         lprect->bottom = MAX(lprect->right,m_lppoints[i].y);

      }

   }

   void region::max_bounding_box_poly_polygon(LPRECTD lprect)
   {

      i32 n = 0;

      for(i32 i = 0; i < m_nCount; i++)
      {

         i32 iCount = m_lppolycounts[i];

         for(int j = 0; j < iCount; j++,n++)
         {

            lprect->left = MIN(lprect->left,m_lppoints[n].x);
            lprect->right = MAX(lprect->right,m_lppoints[n].x);
            lprect->top = MIN(lprect->left,m_lppoints[n].y);
            lprect->bottom = MAX(lprect->right,m_lppoints[n].y);

         }

      }

   }


   void region::max_bounding_box_combine(LPRECTD lprect)
   {

      m_pregion1->max_bounding_box(lprect);

      m_pregion2->max_bounding_box(lprect);

   }


   bool region::internal_contains(LPCPOINTD lppt)
   {

      switch(m_etype)
      {
      case type_none:
         return false;
      case type_rect:
         return internal_rect_contains(lppt);
      case type_oval:
         return internal_oval_contains(lppt);
      case type_polygon:
         return internal_polygon_contains(lppt);
      case type_poly_polygon:
         return internal_poly_polygon_contains(lppt);
      case type_combine:
         return internal_combine_contains(lppt);
      default:
         ::exception::throw_not_implemented(get_app());
      }

      return false;

   }


   bool region::internal_rect_contains(LPCPOINTD lppt)
   {

      return lppt->x >= m_x1 && lppt->y >= m_y1 && lppt->x <= m_x2 && lppt->y <= m_y2;

   }


   bool region::internal_oval_contains(LPCPOINTD lppt)
   {

      double centerx    = (m_x2 + m_x1) / 2.0;
      double centery    = (m_y2 + m_y1) / 2.0;

      double radiusx    = fabs(m_x2 - m_x1) / 2.0;
      double radiusy    = fabs(m_y2 - m_y1) / 2.0;

      if(radiusx == 0.0 || radiusy == 0.0)
         return false;

      double x = lppt->x;
      double y = lppt->y;

      return ((x - centerx) * (x - centerx) / (radiusx * radiusx) + (y - centery) * (y - centery) / (radiusy * radiusy)) <= 1.0;

   }


   bool region::internal_polygon_contains(LPCPOINTD lppt)
   {

      if (m_nCount <= 0)
      {

         return false;

      }

      if (::polygon_contains(lppt, m_lppoints, m_nCount))
      {

         return true;

      }

      return false;

   }

   bool region::internal_poly_polygon_contains(LPCPOINTD lppt)
   {

      i32 n = 0;

      for(i32 i = 0; i < m_nCount; i++)
      {

         i32 iCount = m_lppolycounts[i];

         if (::polygon_contains(lppt, &m_lppoints[n], iCount))
         {

            return true;

         }

         n += iCount;

      }

      return false;

   }


   bool region::internal_combine_contains(LPCPOINTD lppt)
   {

      if(m_ecombine == ::draw2d::region::combine_add)
      {
         if(m_pregion1->internal_contains(lppt))
            return true;
         if(m_pregion2->internal_contains(lppt))
            return true;
         return false;
      }
      else if(m_ecombine == ::draw2d::region::combine_exclude)
      {
         if(m_pregion2->internal_contains(lppt))
            return false;
         if(m_pregion1->internal_contains(lppt))
            return true;
         return false;
      }
      else if(m_ecombine == ::draw2d::region::combine_intersect)
      {
         if(m_pregion1->internal_contains(lppt))
         {
            if(m_pregion2->internal_contains(lppt))
               return true;
         }
         return false;
      }
      else if(m_ecombine == ::draw2d::region::combine_xor)
      {
         if(m_pregion1->internal_contains(lppt))
         {
            if(m_pregion2->internal_contains(lppt))
               return false;
            else
               return true;
         }
         else if(m_pregion2->internal_contains(lppt))
         {
            return true;
         }
         else
         {
            return false;
         }
      }
      else
      {
         return false;
      }


   }


   bool region::internal_contains(LPCPOINT lppt)
   {

      return internal_contains(pointd(lppt));

   }


   bool region::internal_rect_contains(LPCPOINT lppt)
   {

      return internal_rect_contains(pointd(lppt));

   }


   bool region::internal_oval_contains(LPCPOINT lppt)
   {

      return internal_oval_contains(pointd(lppt));

   }


   bool region::internal_polygon_contains(LPCPOINT lppt)
   {

      return internal_polygon_contains(pointd(lppt));

   }


   bool region::internal_poly_polygon_contains(LPCPOINT lppt)
   {

      return internal_poly_polygon_contains(pointd(lppt));

   }


   bool region::internal_combine_contains(LPCPOINT lppt)
   {

      return internal_combine_contains(pointd(lppt));

   }


} // namespace draw2d





