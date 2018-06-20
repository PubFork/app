#pragma once


template < typename POINTER, class ARRAY_TYPE = comparable_array < POINTER, POINTER, comparable_eq_array < POINTER, POINTER, raw_array < POINTER, POINTER, ::allocator::zero < POINTER > > > > >
class pointer_array :
   public ARRAY_TYPE
{
public:



   inline pointer_array() {}
   inline pointer_array(::aura::application * papp) :object(papp) {   }
   inline pointer_array(const pointer_array & a) { this->operator = (a); }
   inline pointer_array(pointer_array && a) { this->operator = (::move(a)); }


   inline pointer_array & operator = (const pointer_array & a) { this->ARRAY_TYPE::operator = (a); return *this; }
   inline pointer_array & operator = (pointer_array && a) { this->ARRAY_TYPE::operator = (::move(a)); return *this; }


   index add(POINTER newElement) { return ARRAY_TYPE::add(newElement); }
   index add(const pointer_array & src) { return ARRAY_TYPE::add(src); }


   inline POINTER & element_at(index i) { return (POINTER &)ARRAY_TYPE::element_at(i); }
   inline POINTER element_at(index i) const { return (POINTER)ARRAY_TYPE::element_at(i); }

   inline POINTER & element_at_grow(index i) { return (POINTER &)ARRAY_TYPE::element_at_grow(i); }


   inline POINTER & operator[](index i) { return element_at(i); }
   inline POINTER operator[](index i) const { return element_at(i); }

   inline POINTER & first(index i = 0) { return (POINTER &)ARRAY_TYPE::first(i); }
   inline POINTER first(index i = 0) const { return (POINTER)ARRAY_TYPE::first(i); }

   inline POINTER & last(index i = -1) { return (POINTER &)ARRAY_TYPE::last(i); }
   inline POINTER last(index i = 0) const { return (POINTER)ARRAY_TYPE::last(i); }

   inline POINTER* get_data() { return (POINTER*)ARRAY_TYPE::get_data(); }
   inline POINTER* get_data() const { return (POINTER*)ARRAY_TYPE::get_data(); }

};



class CLASS_DECL_AURA object_ptra :
   virtual public ::pointer_array < object * >
{
public:

   typedef ::pointer_array < object * > BASE_TYPE;

   inline object_ptra() {}
   inline object_ptra(::aura::application * papp) : BASE_TYPE(papp) { }
   inline object_ptra(const object_ptra & a) : BASE_TYPE(a) { }
   inline object_ptra(const BASE_TYPE & a) : BASE_TYPE(a) { }
   inline object_ptra(object_ptra && a): BASE_TYPE(::move(a)) { }

   inline object_ptra & operator = (const object_ptra & a) { this->BASE_TYPE::operator = (a); return *this; }
   inline object_ptra & operator = (const BASE_TYPE & a) { this->BASE_TYPE::operator = (a); return *this; }
   inline object_ptra & operator = (object_ptra && a) { this->BASE_TYPE::operator = (::move(a)); return *this; }


};







class CLASS_DECL_AURA const_char_ptra :
   public pointer_array < const char * >
{
};






typedef pointer_array < void * > void_ptra;

