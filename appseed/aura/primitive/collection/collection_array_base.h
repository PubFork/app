// raw_array is an array that does not call constructors or destructor in elements
// array is an array that call only copy constructor and destructor in elements
// array is an array that call default constructors, copy constructs and destructors in elements
template < class TYPE, class ARG_TYPE = const TYPE &, class ALLOCATOR = allocator::nodef < TYPE > >
class array_base :
   virtual public ::object
{
public:

   typedef TYPE BASE_TYPE;

   class iterator
   {
   public:

      typedef TYPE BASE_TYPE;
      typedef array_base < TYPE, ARG_TYPE, ALLOCATOR > BASE_ARRAY;

      index             m_i;
      BASE_ARRAY *      m_parray;


      BASE_ARRAY & iterable()
      {

         return *m_parray;

      }

      iterator()
      {
         m_i = 0;
         m_parray = NULL;
      }

      iterator(index i, BASE_ARRAY * parray)
      {
         m_i = i;
         m_parray = parray;
      }

      iterator(const iterator & it)
      {
         operator = (it);
      }


      iterator & operator = (const iterator & it)
      {
         if (this != &it)
         {
            m_i = it.m_i;
            m_parray = it.m_parray;
         }
         return *this;
      }

      bool operator == (const iterator & it)
      {
         if (this == &it)
            return true;
         if (m_parray != it.m_parray)
            return false;
         if (m_i >= m_parray->get_size() && it.m_i >= m_parray->get_size())
            return true;
         if (m_i <= 0 && it.m_i <= 0)
            return true;
         return m_i == it.m_i;
      }

      bool operator != (const iterator & it)
      {
         return !operator==(it);
      }

      iterator operator ++(int)
      {
         iterator it = *this;
         operator ++();
         return it;
      }

      iterator operator --(int)
      {
         iterator it = *this;
         operator --();
         return it;
      }

      iterator & operator ++()
      {
         m_i++;
         if (m_i >= m_parray->get_size())
            m_i = m_parray->get_size();
         return *this;
      }

      iterator & operator +(index i)
      {
         m_i += i;
         if (m_i >= m_parray->get_size())
            m_i = m_parray->get_size();
         return *this;
      }

      iterator & operator --()
      {
         m_i--;
         if (m_i < 0)
            m_i = 0;
         return *this;
      }

      iterator mid(const iterator & i) const
      {
         return iterator((m_i + i.m_i + 1) / 2, m_parray);
      }

      iterator & operator -(::count c)
      {
         m_i -= c;
         if (m_i < 0)
            m_i = 0;
         return *this;
      }

      bool operator < (const iterator & i) const
      {

         return m_i < i.m_i;

      }

      ::count get_count() const
      {
         return m_parray->get_count();
      }


      TYPE & operator * ()
      {
         return ((TYPE*)m_parray->m_pData)[m_i];
      }

      const TYPE & operator * () const
      {
         return ((const TYPE*)m_parray->m_pData)[m_i];
      }


   };


   class const_iterator
   {
   public:


      typedef TYPE BASE_TYPE;
      typedef array_base < TYPE, ARG_TYPE, ALLOCATOR > BASE_ARRAY;


      index                   m_i;
      const BASE_ARRAY *      m_parray;

      const_iterator()
      {
         m_i = 0;
         m_parray = NULL;
      }

      const_iterator(index i, const BASE_ARRAY * parray)
      {
         m_i = i;
         m_parray = parray;
      }

      const_iterator(const iterator & it)
      {
         operator = (it);
      }

      const_iterator(const const_iterator & it)
      {
         operator = (it);
      }


      const BASE_ARRAY & iterable()
      {

         return *m_parray;

      }

      const_iterator & operator = (const iterator & it)
      {
         m_i = it.m_i;
         m_parray = it.m_parray;
         return *this;
      }

      const_iterator & operator = (const const_iterator & it)
      {
         if (this != &it)
         {
            m_i = it.m_i;
            m_parray = it.m_parray;
         }
         return *this;
      }

      bool operator == (const const_iterator & it)
      {
         if (this == &it)
            return true;
         if (m_parray != it.m_parray)
            return false;
         if (m_i >= m_parray->get_size() && it.m_i >= m_parray->get_size())
            return true;
         if (m_i <= 0 && it.m_i <= 0)
            return true;
         return m_i == it.m_i;
      }

      bool operator != (const const_iterator & it)
      {
         return !operator==(it);
      }

      const_iterator operator ++(int)
      {
         const_iterator it = *this;
         operator ++();
         return it;
      }

      const_iterator operator --(int)
      {
         const_iterator it = *this;
         operator --();
         return it;
      }

      const_iterator & operator ++()
      {
         m_i++;
         if (m_i >= m_parray->get_size())
            m_i = m_parray->get_size();
         return *this;
      }

      const_iterator & operator +(index i)
      {
         m_i += i;
         if (m_i >= m_parray->get_size())
            m_i = m_parray->get_size();
         return *this;
      }

      const_iterator & operator --()
      {
         m_i--;
         if (m_i < 0)
            m_i = 0;
         return *this;
      }

      const_iterator mid(const const_iterator & i) const
      {
         return const_iterator_base((m_i + i.m_i + 1) / 2, m_parray);
      }

      const_iterator & operator -(::count c)
      {
         m_i -= c;
         if (m_i < 0)
            m_i = 0;
         return *this;
      }

      bool operator < (const const_iterator & i) const
      {

         return m_i < i.m_i;

      }

      ::count get_count() const
      {
         return m_parray->get_count();
      }

      const TYPE & operator * ()
      {
         return ((const TYPE*)m_parray->m_pData)[m_i];
      }

   };


   TYPE *         m_pData;    // the actual array of data
   ::count        m_nSize;    // # of elements (upperBound - 1)
   ::count        m_nMaxSize; // MAX allocated
   ::count        m_nGrowBy;  // grow amount

   array_base();
   virtual ~array_base();


   inline iterator begin()
   {
      return iterator(0, this);
   }

   inline iterator end()
   {
      return iterator(this->get_size(), this);
   }

   inline const_iterator begin() const
   {
      return const_iterator(0, this);
   }

   inline const_iterator end() const
   {
      return const_iterator(this->get_size(), this);
   }


   inline ::count get_size() const;
   inline ::count get_size_in_bytes() const;
   inline ::count get_count() const;
   inline ::count get_byte_count() const;
   inline ::count get_length() const;
   inline ::count size() const;
   inline ::count count() const;
   inline ::count length() const;

   inline bool is_empty(::count countMinimum = 1) const;
   inline bool empty(::count countMinimum = 1) const;
   inline bool isEmpty(::count countMinimum = 1) const;
   inline bool has_elements(::count countMinimum = 1) const;
   inline index get_upper_bound(index i = -1) const;
   inline index get_middle_index(index i = 0) const;
   inline bool bounds(index i) const;


   inline const TYPE & element_at(index nIndex) const;
   inline TYPE & element_at(index nIndex);

   inline TYPE & first(index n = 0);
   inline const TYPE & first(index n = 0) const;

   inline TYPE & last(index n = -1);
   inline const TYPE & last(index n = -1) const;

   inline TYPE & middle(index n = 0);
   inline const TYPE & middle(index n = 0) const;


   ::count set_size(index nNewSize, ::count nGrowBy = -1); // does not call default constructors on new items/elements
   ::count allocate(index nNewSize, ::count nGrowBy = -1); // does not call default constructors on new items/elements
   ::count allocate_in_bytes(index nNewSize, ::count nGrowBy = -1); // does not call default constructors on new items/elements
   ::count set_raw_size(index nNewSize, ::count nGrowBy = -1); // does not call constructors and destructors on items/elements
   ::count resize(index nNewSize, ::count nGrowBy = -1); // does not call default constructors on new items/elements
   void free_extra();
   virtual void destroy();

   inline void swap(index index1, index index2);
   inline void swap(iterator index1, iterator index2);
   //   inline void swap(const_iterator index1, const_iterator index2);


   void zero(index iStart = 0, ::count c = -1);

   void _001RemoveIndexes(index_array & ia);
   void remove_indexes(const index_array & ia);
   void remove_descending_indexes(const index_array & ia);


   inline void prepare_first_last(index & first, index & last) const;
   inline void prepare_first_in_count_last_out(index & first, ::count & inCountLastOut) const;


   inline void remove_last();
   inline ::count remove_all();
   inline void clear();


   void on_construct_element(TYPE * p) { ALLOCATOR::construct(p); }
   void on_construct_element(TYPE * p, ::count c) { ALLOCATOR::construct(p, c); }
   void on_destruct_element(TYPE * p) { ALLOCATOR::destruct(p); }
   void on_copy_element(index i, const TYPE * p) { ALLOCATOR::copy(&m_pData[i], p); }


   // overloaded operator helpers
   inline const TYPE& operator[](index nIndex) const;
   inline TYPE& operator[](index nIndex);

   index insert_at(index nIndex, const TYPE & newElement, ::count nCount = 1);
   index remove_at(index nIndex, ::count nCount = 1);
   index insert_at(index nStartIndex, array_base * pNewArray);


   inline TYPE pop(index index = -1);
   inline index push(ARG_TYPE newElement, index i = 0);
   inline void pop_back(index index = -1);
   inline void push_back(ARG_TYPE newElement, index = 0);

   inline TYPE takeAt(index index);
   inline TYPE takeFirst(index index = 0);
   inline TYPE takeLast(index index = -1);

   virtual ::count append(const array_base & src); // return old size
   virtual void copy(const array_base & src);

   virtual void on_after_read();

   template < typename PRED >
   ::count pred_each(PRED pred, index iStart = 0, ::count c = -1)
   {

      index iEnd = c < 0 ? get_count() + c : iStart + c - 1;

      int cProcessed = 0;

      for (index i = iStart; i <= iEnd; i++)
      {

         pred(m_pData[i]);

         cProcessed++;

      }

      return cProcessed;

   }


   template < typename PRED >
   bool pred_contains(PRED pred, index iStart = 0, index iEnd = -1) const
   {

      return this->pred_find_first(pred, iStart, iEnd) >= 0;

   }


   template < typename PRED >
   index pred_find_first(PRED pred, index iStart = 0, index iEnd = -1) const
   {

      if (iEnd < 0)
      {

         iEnd += get_count();

      }

      if (iEnd >= get_count())
      {

         iEnd = get_count() - 1;

      }

      for (index i = iStart; i <= iEnd; i++)
      {

         if (pred(m_pData[i]))
         {

            return i;

         }

      }

      return -1;

   }

   template < typename PRED >
   index pred_find_last(PRED pred, index iLast = -1)
   {

      if (iLast < 0)
      {

         iLast += get_count();

      }

      for (index i = iLast; i >= 0; i--)
      {

         if (pred(m_pData[i]))
         {

            return i;

         }

      }

      return -1;

   }

   template < typename PRED >
   TYPE * pred_get_first(PRED pred)
   {
      for (int i = 0; i < get_count(); i++)
      {

         if (pred(m_pData[i]))
         {

            return &element_at(i);

         }

      }

      return NULL;

   }


   template < typename PRED >
   ::count pred_get_count(PRED pred)
   {

      ::count c = 0;

      for (int i = 0; i < get_count(); i++)
      {

         if (pred(m_pData[i]))
         {

            c++;

         }

      }

      return c;

   }


   inline index add(ARG_TYPE newElement)
   {
      index nIndex = this->m_nSize;
      this->allocate(nIndex + 1);
      this->last() = newElement;
      return nIndex;
   }
   template < typename PRED >
   ::count pred_remove(PRED pred)
   {
      ::count cTotal = 0;
      for (int i = 0; i < get_count();)
      {

         if (!pred(m_pData[i]))
         {
            i++;
         }
         else
         {

            int iStart = i;

            int iCount = 1;

            i++;

            for (; i < get_count();)
            {

               if (!pred(m_pData[i]))
               {

                  break;

               }

               iCount++;

               i++;

            }

            remove_at(iStart, iCount);

            cTotal += iCount;

            i = iStart;

         }

      }
      return cTotal;
   }

   template < typename F >
   void each(F f)
   {

      for (index i = 0; i < get_count(); i++)
      {
         f(m_pData[i]);
      }

   }


   template < typename PRED >
   void pred_sort(PRED pred);

   template < typename T, typename PRED >
   index pred_binary_search(const T & t, PRED pred) const;

   inline bool valid_iter(iterator first, iterator last)
   {

      return first.m_i < last.m_i;

   }

   inline bool rvalid_iter(iterator first, iterator last)
   {

      return first.m_i > last.m_i;

   }


};

template < class TYPE, class ARG_TYPE, class ALLOCATOR = allocator::nodef < TYPE > >
inline const TYPE& operator%(index nIndex, const array_base < TYPE, ARG_TYPE, ALLOCATOR > & a)
{

   return a[nIndex % a.get_size()];

}
template < class TYPE, class ARG_TYPE, class ALLOCATOR = allocator::nodef < TYPE > >
inline TYPE& operator%(index nIndex, array_base < TYPE, ARG_TYPE, ALLOCATOR > & a)
{

   return a[nIndex % a.get_size()];

}


