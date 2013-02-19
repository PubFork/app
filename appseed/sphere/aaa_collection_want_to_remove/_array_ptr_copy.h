#pragma once

template <class TYPE, class ARG_TYPE = const TYPE &>
class array_ptr_copy :
   public array_ptr < TYPE, ARG_TYPE >
{
public:
	array_ptr_copy();
   array_ptr_copy(const array_ptr_copy & a);
	virtual ~array_ptr_copy();

   index add(const TYPE & t);
   index add(TYPE * p);
   inline void insert_at(int iIndex, ARG_TYPE t);

   count add(const array_ptr_copy < TYPE, ARG_TYPE > & base_array);

   void copy(const array_ptr_copy < TYPE, ARG_TYPE > & base_array);

   const TYPE & element_at(INT_PTR nIndex) const;
   TYPE & element_at(INT_PTR nIndex);

	const TYPE & operator[](INT_PTR nIndex) const;
	TYPE& operator[](INT_PTR nIndex);

	array_ptr_copy < TYPE, ARG_TYPE > & operator = (const array_ptr_copy <TYPE, ARG_TYPE> & base_array);
};
template <class TYPE, class ARG_TYPE>
array_ptr_copy < TYPE, ARG_TYPE >::array_ptr_copy()
{
}

template <class TYPE, class ARG_TYPE>
array_ptr_copy < TYPE, ARG_TYPE >::array_ptr_copy(const array_ptr_copy & a)
{
   operator = (a);
}

template <class TYPE, class ARG_TYPE>
array_ptr_copy < TYPE, ARG_TYPE >::~array_ptr_copy()
{
   remove_all();
}

template <class TYPE, class ARG_TYPE>
inline index array_ptr_copy < TYPE, ARG_TYPE >::add(
   const TYPE & t)
{
   return m_ptra.add(gen::alloc<TYPE>(t));
}

template <class TYPE, class ARG_TYPE>
inline index array_ptr_copy < TYPE, ARG_TYPE >::add(
   TYPE * p)
{
   return array_ptr < TYPE, ARG_TYPE >::add(p);
}

template <class TYPE, class ARG_TYPE>
inline void array_ptr_copy < TYPE, ARG_TYPE >::insert_at(
   int iIndex,
   ARG_TYPE t)
{
   m_ptra.insert_at(iIndex, gen::alloc<TYPE>(t));
}


template <class TYPE, class ARG_TYPE>
inline array_ptr_copy <TYPE, ARG_TYPE> & array_ptr_copy < TYPE, ARG_TYPE >::operator = (
   const array_ptr_copy <TYPE, ARG_TYPE> & a)
{
   if(&a == this)
      return *this;
	int i;
   for(i = 0; i < m_ptra.get_size(); i++)
   {
      this->element_at(i) = *a.m_ptra[i];
   }
   for(; i < a.m_ptra.get_size(); i++)
   {
      m_ptra.add(gen::alloc<TYPE>(*a.m_ptra[i]));
   }
   m_ptra.set_size(a.m_ptra.get_size());
   return *this;
}


template <class TYPE, class ARG_TYPE>
void array_ptr_copy < TYPE, ARG_TYPE >::copy(const array_ptr_copy < TYPE, ARG_TYPE > & a)
{
   remove_all();
   add(a);
}

template <class TYPE, class ARG_TYPE>
count array_ptr_copy < TYPE, ARG_TYPE >::add(const array_ptr_copy < TYPE, ARG_TYPE > & a)
{
   count countOld = this->get_count();
   for(int i = 0; i < a.get_size(); i++)
   {
      add(a[i]);
   }
   return countOld;
}


template <class TYPE, class ARG_TYPE>
const TYPE & array_ptr_copy < TYPE, ARG_TYPE >::
this->element_at(INT_PTR nIndex) const
{
   return *m_ptra.element_at(nIndex);
}

template <class TYPE, class ARG_TYPE>
TYPE & array_ptr_copy < TYPE, ARG_TYPE >::
this->element_at(INT_PTR nIndex)
{
   return *m_ptra.element_at(nIndex);
}

template <class TYPE, class ARG_TYPE>
const TYPE & array_ptr_copy < TYPE, ARG_TYPE >::
operator[](INT_PTR nIndex) const
{
   return this->element_at(nIndex);
}

template <class TYPE, class ARG_TYPE>
TYPE & array_ptr_copy < TYPE, ARG_TYPE >::
operator[](INT_PTR nIndex)
{
   return this->element_at(nIndex);
}
