#pragma once


template < typename POINTER, class ARRAY_TYPE = comparable_array < POINTER, POINTER, comparable_eq_array < POINTER, POINTER, raw_array < POINTER, POINTER, ::allocator::zero < POINTER > > > >  >
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

////////////////////////////////////////////////////////
//
//   *naked* pointer raw array
//   by *naked*, it means just raw referencing pointers
//   no implicit neither automatic destruction/deallocation/allocation or construction
//
template < class TYPE, class ARRAY_TYPE = pointer_array < TYPE * > >
class ref_array :
   public ARRAY_TYPE
{
   public:

      typedef ARRAY_TYPE BASE_TYPE;

      inline ref_array() {}
      inline ref_array(::aura::application * papp) : BASE_TYPE(papp) {   }
      inline ref_array(const ref_array & a) : BASE_TYPE(a) { }
      inline ref_array(const BASE_TYPE & a) : BASE_TYPE(a) { }
      inline ref_array(ref_array && a): BASE_TYPE(move(a)) { }


      inline ref_array & operator = (const ref_array & a) { this->BASE_TYPE::operator = (a); return *this; }
      inline ref_array & operator = (const BASE_TYPE & a) { this->BASE_TYPE::operator = (a); return *this; }
      inline ref_array & operator = (ref_array && a) { this->BASE_TYPE::operator = (::move(a)); return *this; }


      inline TYPE & operator()(index i) { return *this->element_at(i); }
      inline const TYPE & operator()(index i) const { return *this->element_at(i); }

      template < class T >
      T * typed_ptr_at(index i)
      {

         return dynamic_cast <T *> (this->element_at(i));

      }


};




class CLASS_DECL_AURA object_refa :
   virtual public ::ref_array < object >
{
   public:

      typedef ::ref_array < object > BASE_TYPE;

      inline object_refa() {}
      inline object_refa(::aura::application * papp) : BASE_TYPE(papp) { }
      inline object_refa(const object_refa & a) : BASE_TYPE(a) { }
      inline object_refa(const BASE_TYPE & a) : BASE_TYPE(a) { }
      inline object_refa(const BASE_TYPE::BASE_TYPE & a) : BASE_TYPE(a) { }
      inline object_refa(object_refa && a): BASE_TYPE(::move(a)) { }

      inline object_refa & operator = (const object_refa & a) { this->BASE_TYPE::operator = (a); return *this; }
      inline object_refa & operator = (const BASE_TYPE & a) { this->BASE_TYPE::operator = (a); return *this; }
      inline object_refa & operator = (const BASE_TYPE::BASE_TYPE & a) { this->BASE_TYPE::operator = (a); return *this; }
      inline object_refa & operator = (object_refa && a) { this->BASE_TYPE::operator = (::move(a)); return *this; }


};







class CLASS_DECL_AURA const_char_ptra :
   public ref_array < const char >
{
};






typedef pointer_array < void * > void_ptra;

