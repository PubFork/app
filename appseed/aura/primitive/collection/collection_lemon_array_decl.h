#pragma once




namespace lemon
{

   namespace array
   {

      template < class TYPE >
      ::count ensure_sequence(numeric_array < TYPE > & a,TYPE start,TYPE end,TYPE increment = 1);

      template < class TYPE >
      ::count append_sequence(numeric_array < TYPE > & a, TYPE iterator,TYPE end,TYPE increment = 1);

      template < class TYPE >
      ::count set_sequence(numeric_array < TYPE > & a,TYPE start,TYPE end,TYPE increment = 1);


      template<class ARRAY>
      bool binary_search(ARRAY & a,typename ARRAY::BASE_ARG_TYPE t,index & iIndex,index(* fCompare) (typename ARRAY::BASE_ARG_TYPE,typename ARRAY::BASE_ARG_TYPE));

      template<class ARRAY>
      bool binary_search(ARRAY & a,typename ARRAY::BASE_ARG_TYPE t,index & iIndex,index(* fCompare) (typename ARRAY::BASE_ARG_TYPE,typename ARRAY::BASE_ARG_TYPE),index_array & ia);

      template<class ARRAY>
      index sort_add(ARRAY & a,typename ARRAY::BASE_ARG_TYPE t,index(* fCompare) (typename ARRAY::BASE_ARG_TYPE,typename ARRAY::BASE_ARG_TYPE),index_array & ia);

      template<class ARRAY, class ARRAY2>
      ::count sort_add_array(ARRAY & a,ARRAY2 & a2,index(* fCompare) (typename ARRAY::BASE_ARG_TYPE,typename ARRAY::BASE_ARG_TYPE),index_array & ia);

      template<class ARRAY>
      inline typename ARRAY::BASE_TYPE pop(ARRAY & a,index n = -1);

      template<class ARRAY>
      inline void pop_back(ARRAY & a,index n = -1);

      template<class ARRAY>
      inline index push(ARRAY & a,typename ARRAY::BASE_ARG_TYPE newElement,index n = 0);

      template<class ARRAY>
      inline void push_back(ARRAY & a, typename ARRAY::BASE_ARG_TYPE newElement,index n = 0);

      template<class TARGET,class SOURCE> inline void add(TARGET & target,const SOURCE & source) { target.add(source); }
      template<> inline void add(stringa & stra,const stringa & straSource);
      template<> inline void add(::file::patha & patha,const stringa & stra);
      template<> inline void add(::file::patha & patha,const string & str);


      template < typename T >
      inline bool are_all_elements_equal(const spa(T) & a1, const spa(T) & a2);


      template < typename A, typename PA >
      void copy_points(A & a, const PA * pa, ::count c);


   } // namespace array

   namespace array2d
   {

      template < typename A >
      ::count predominant_column_count(A & a);

   } // namespace array2d

   template < class TYPE >
   ::count remove_greater_than(::numeric_array < TYPE > & a,TYPE hi);

   template < class TYPE >
   ::count remove_greater_than_or_equal(::numeric_array < TYPE > & a,TYPE hi);

   template < class TYPE >
   ::count remove_lesser_than(::numeric_array < TYPE > & a,TYPE lo);

   template < class TYPE >
   ::count remove_lesser_than_or_equal(::numeric_array < TYPE > & a,TYPE lo);

   template < class TYPE >
   ::count remove_lesser_than_or_greater_than(::numeric_array < TYPE > & a,TYPE lo,TYPE hi);

   template < class TYPE >
   ::count remove_lesser_than_or_greater_than_or_equal(::numeric_array < TYPE > & a,TYPE lo,TYPE hi);

   template < class TYPE >
   ::count remove_lesser_than_or_equal_or_greater_than(::numeric_array < TYPE > & a,TYPE lo,TYPE hi);

   template < class TYPE >
   ::count remove_lesser_than_or_equal_or_greater_than_or_equal(::numeric_array < TYPE > & a,TYPE lo,TYPE hi);


} // namespace lemon




