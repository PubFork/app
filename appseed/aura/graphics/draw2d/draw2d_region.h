#pragma once


namespace draw2d
{


   class CLASS_DECL_AURA region :
      virtual public object
   {
   public:


      enum e_combine
      {

         combine_add,
         combine_exclude,
         combine_intersect,
         combine_xor

      };


      enum e_type
      {

         type_none,
         type_rect,
         type_oval,
         type_polygon,
         type_poly_polygon,
         type_round_rect,
         type_combine

      };


      e_type                  m_etype;
      double                  m_x1;
      double                  m_y1;
      double                  m_x2;
      double                  m_y2;
      double                  m_x3;
      double                  m_y3;
      LPPOINTD                m_lppoints;
      LPINT                   m_lppolycounts;
      int32_t                 m_nCount;
      ::draw2d::e_fill_mode   m_efillmode;
      sp(::draw2d::region)    m_pregion1;
      sp(::draw2d::region)    m_pregion2;
      e_combine               m_ecombine;


      region();
      region(const region & region);
      virtual ~region();


      virtual bool create_rect(LPCRECT lpRect);
      virtual bool create_oval(LPCRECT lpRect);
      virtual bool create_polygon(const LPPOINT lpPoints, int32_t nCount, ::draw2d::e_fill_mode efillmode);
      virtual bool create_polygon(const LPPOINTD lpPoints,int32_t nCount,::draw2d::e_fill_mode efillmode);
      virtual bool create_poly_polygon(const LPPOINTD lpPoints, LPINT lpPolyCounts, int32_t nCount, ::draw2d::e_fill_mode efillmode);
      virtual bool create_poly_polygon(const LPPOINT lpPoints,LPINT lpPolyCounts,int32_t nCount,::draw2d::e_fill_mode efillmode);
      virtual bool combine(const ::draw2d::region * prgn1, const ::draw2d::region * prgn2, e_combine ecombine);
      virtual bool translate(const LPPOINT point);
      virtual bool get_bounding_box(LPRECT lpRect);
      virtual bool contains(const LPPOINT point);
      virtual bool contains(const LPPOINTD point);

      bool internal_contains(LPPOINT lppt);
      bool internal_rect_contains(LPPOINT lppt);
      bool internal_oval_contains(LPPOINT lppt);
      bool internal_polygon_contains(LPPOINT lppt);
      bool internal_poly_polygon_contains(LPPOINT lppt);
      bool internal_combine_contains(LPPOINT lppt);


      bool internal_contains(LPPOINTD lpptd);
      bool internal_rect_contains(LPPOINTD lpptd);
      bool internal_oval_contains(LPPOINTD lpptd);
      bool internal_polygon_contains(LPPOINTD lpptd);
      bool internal_poly_polygon_contains(LPPOINTD lpptd);
      bool internal_combine_contains(LPPOINTD lpptd);

      virtual void max_bounding_box(LPRECT lpRect);
      virtual void max_bounding_box_rect(LPRECT lpRect);
      virtual void max_bounding_box_oval(LPRECT lpRect);
      virtual void max_bounding_box_polygon(LPRECT lpRect);
      virtual void max_bounding_box_poly_polygon(LPRECT lpRect);
      virtual void max_bounding_box_combine(LPRECT lpRect);

      virtual void max_bounding_box(LPRECTD lpRect);
      virtual void max_bounding_box_rect(LPRECTD lpRect);
      virtual void max_bounding_box_oval(LPRECTD lpRect);
      virtual void max_bounding_box_polygon(LPRECTD lpRect);
      virtual void max_bounding_box_poly_polygon(LPRECTD lpRect);
      virtual void max_bounding_box_combine(LPRECTD lpRect);

      virtual bool destroy();

      region & operator = (const ::draw2d::region & regionSrc);

   };


   typedef sp(region) region_sp;


} // namespace draw2d






