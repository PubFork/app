#pragma once

template < typename SIZE >
SIZE typed_unit_size()
{
   SIZE s = {1, 1};
   return s;
}

template < >
inline ::SIZE typed_unit_size < ::SIZE >()
{
   ::SIZE s = {1, 1};
   return s;
}


template < typename POINT2D >
class point2d_array_base :
   public comparable_array < POINT2D >,
   virtual public ::xml::exportable,
   virtual public ::xml::importable
{
public:
   inline point2d_array_base(): comparable_array < POINT2D >() {}
   inline point2d_array_base(point2d_array_base && pointset) : comparable_array < POINT2D > (::move(pointset)) { }
   inline point2d_array_base(const point2d_array_base & pointset) { operator=(pointset); }
   virtual ~point2d_array_base() { }


   operator typename POINT2D::BASE * () { return this->get_data(); }

   void offset(typename POINT2D::TYPE x,typename POINT2D::TYPE y);
   void offset(POINT2D point) { offset(point.x,point.y); }

   void rotate(double dAngle);

   void get_bounding_rect(typename POINT2D::LPRECT lprect) const;

   static void get_bounding_rect(typename POINT2D::LPRECT lprect,const typename POINT2D::BASE * lppoint,::count count);

   bool bounding_rect_contains_pt(typename POINT2D::BASE pt) const;

   bool polygon_contains(typename POINT2D::BASE pt) const;

   inline index add(typename POINT2D::TYPE x,typename POINT2D::TYPE y) { return comparable_array < POINT2D >::add(POINT2D(x,y)); }
   inline index add(typename POINT2D::BASE point) { return comparable_array < POINT2D >::add(POINT2D(point)); }
   inline point2d_array_base & operator =(const point2d_array_base & pointset) { this->copy(pointset); return *this; }

   virtual void xml_import(::xml::input_tree & xmlif);
   virtual void xml_export(::xml::output_tree & xmlof);


   ::count add_unique_range(typename POINT2D::BASE ptBeg,typename POINT2D::BASE ptEnd,typename POINT2D::SIZE s = POINT2D::SIZE::unit_size());


};


using point64_array = point2d_array_base < point64 >;



