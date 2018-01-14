#pragma once



template < class TYPE, class ARG_TYPE = const TYPE &, class ALLOCATOR = ::allocator::def < TYPE > >
class array :
   public ::array_base < TYPE, ARG_TYPE, ALLOCATOR >
{
   public:

      typedef TYPE BASE_TYPE;
      typedef ARG_TYPE BASE_ARG_TYPE;
      typedef array < TYPE, ARG_TYPE > BASE_ARRAY;
      typedef typename array_base < TYPE, ARG_TYPE, ALLOCATOR >::iterator iterator;





      array(::aura::application * papp = NULL, ::count nGrowBy = 0);
      array(const array & a);
      array(::std::initializer_list < TYPE > l);
      array(::count n);
      array(::count n, ARG_TYPE t);
      array(array && a);
      virtual ~array();


      void dump(dump_context &) const;
      void assert_valid() const;


      inline const TYPE& get_at(index nIndex) const;
      inline TYPE& get_at(index nIndex);
      inline void set_at(index nIndex, ARG_TYPE newElement);



      inline const TYPE* get_data() const;
      inline TYPE* get_data();


      inline index add(ARG_TYPE newElement);
      inline index add(const array& src);
      inline index append(const array& src);
      inline void copy(const array& src);

      inline TYPE & add_new();
      inline index add_new( ::count count);





      inline iterator erase(iterator pos);
      inline iterator erase(iterator first,iterator last);


      // Operations that move elements around
      //inline index insert_at(index nIndex, ARG_TYPE newElement, ::count nCount = 1);
      //void _001RemoveIndexes(index_array & ia);
      //void remove_indexes(const index_array & ia); // remove indexes from index array upper bound to index array lower bound
      //void remove_descending_indexes(const index_array & ia); // remove indexes from index array lower bound to index array upper bound
      //index insert_at(index nStartIndex, array* pNewArray);

      inline array & operator = (const array & src);
      inline array & operator = (array && a);
      inline array & move (array && a);


      //inline index find_first(ARG_TYPE t, index (* lpfnCompare)(ARG_TYPE, ARG_TYPE), index start = 0, index last = -1) const;
      //index raw_find_first(TYPE * pt, index first = 0, index last = -1) const;

      //template < class DERIVED >
      //inline index find_first(DERIVED * pt, index first = 0, index last = -1)
      //{
      //   return raw_find_first(dynamic_cast < TYPE * > (pt), first, last);
      //}

      template < class ARRAY >
      inline ::count slice(ARRAY & a, index iStart = 0, ::count nCount = -1)
      {

         ::count ca = 0;

         index iEnd;

         if(nCount < 0)
            iEnd = this->get_upper_bound(nCount);
         else
            iEnd = iStart + nCount - 1;

         for(index i = iStart; i <= iEnd; i++)
         {

            a.add(this->element_at(i));
            ca++;

         }

         return ca;

      }

      //void quick_sort(index (* fCompare)(TYPE *, TYPE *));
      //void quick_sort(index (* fCompare)(TYPE *, TYPE *), void (* fSwap)(TYPE *, TYPE *));
      //void quick_sort(index (* fCompare)(TYPE *, TYPE *), index_array & ia);
      //bool binary_search(ARG_TYPE t, index & iIndex, index ( * fCompare ) (TYPE *, TYPE *)) const;

      //bool binary_search(ARG_TYPE t, index & iIndex, index ( * fCompare ) (TYPE *, TYPE *), index_array & ia) const;
      //index sort_add(ARG_TYPE t, index ( * fCompare ) (TYPE *, TYPE *), index_array & ia);
      //::count sort_add(const array < TYPE, ARG_TYPE > & a, index ( * fCompare ) (TYPE *, TYPE *), index_array & ia);
      //index sort_remove(ARG_TYPE t, index ( * fCompare ) (TYPE *, TYPE *), index_array & ia);

      operator TYPE *() {return this->m_pData;}
      operator const TYPE *() const {return this->m_pData;}
      operator count() const { return this->get_count(); }

      inline array & operator += (const array & a);
      inline array operator + (const array & a) const;

      //inline array & move(array && a);

      inline void set_at_grow(index nIndex, ARG_TYPE newElement);

      inline TYPE & element_at_grow(index nIndex);

      template < typename... T >
      void fadd(T... a)
      {

         add(TYPE(a...));

      }


      template < typename PRED >
      bool pred_add_unique(TYPE t, PRED pred)
      {

         if (this->pred_find_first(pred) >= 0)
         {

            return false;

         }

         this->add(t);

         return true;

      }

      template < typename ITERABLE >
      array_base< TYPE, ARG_TYPE,  ALLOCATOR > & copy_iter(const ITERABLE & iterable)
      {

         this->set_size(0, MAX(iterable.get_count(), 17));

         for (auto & item : iterable)
         {

            add(item);

         }

         return *this;

      }

};



template < class TYPE, class ARG_TYPE = const TYPE & >
class nodefctr_array :
   public array < TYPE, ARG_TYPE, ::constructor::nodef < TYPE > >
{
   public:


      nodefctr_array(::aura::application * papp = NULL, ::count nGrowBy = 32) : array < TYPE, ARG_TYPE, ::constructor::nodef < TYPE > > (papp, nGrowBy) {}
      nodefctr_array(const array <TYPE, ARG_TYPE> & a) : array < TYPE, ARG_TYPE, ::constructor::nodef < TYPE >  > (a) {}
      nodefctr_array(::count n) : array < TYPE, ARG_TYPE, ::constructor::nodef < TYPE > > (n) {}
      virtual ~nodefctr_array() {}

};


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
void array_base < TYPE, ARG_TYPE, ALLOCATOR > ::prepare_first_last(index & first, index & last) const
{

   if (first < 0)
   {

      first += this->get_count();

   }

   if (last < 0)
   {

      last += this->get_count();

   }

}
