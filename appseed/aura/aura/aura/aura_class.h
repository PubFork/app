#pragma once


struct __POSITION {};
typedef __POSITION* POSITION;
#define BEFORE_START_POSITION ((POSITION)-1L)




template<class TYPE>
inline void CopyElements(TYPE* pDest, const TYPE* pSrc, ::count nCount);


#ifdef DEBUG

template<class TYPE>
inline void dump_elements(dump_context & dumpcontext, const TYPE* pElements, ::count nCount);

#endif


template<class TYPE, class ARG_TYPE>
bool CompareElements(const TYPE* pElement1, const ARG_TYPE pElement2)
{
   ENSURE(pElement1 != NULL && pElement2 != NULL);
   ASSERT(__is_valid_address(pElement1, sizeof(TYPE), FALSE));
   ASSERT(__is_valid_address(pElement2, sizeof(ARG_TYPE), FALSE));

   return *pElement1 == *pElement2;
}







#define _TYPELIB_INDEX_LENGTH 10
#define _QUOTES_SPACE 2



template < class T >
class base_class
{
   public:


      template < class T2 >
      inline static bool bases(T2 * p)
      {
         return dynamic_cast < T * > (p) != NULL;
      }

      template < class T2 >
      inline static bool bases(const smart_pointer < T2 > & sp)
      {
         return dynamic_cast < T * > ((T2 *) sp.m_p) != NULL;
      }

};




#define ASSERT_KINDOF(class_name, object) ASSERT(base_class < class_name > ::bases(object))
#define DYNAMIC_DOWNCAST(class_name, object) (dynamic_cast < class_name * > (object))
#define STATIC_DOWNCAST(class_name, object) (dynamic_cast<class_name*>(object))
#define STATIC_DOWNCAST_T(class_name, T1, object) (static_cast<class_name<T1>*>(::core::StaticDownCast(RUNTIME_CLASS_T(class_name, T1), object)))
#define STATIC_DOWNCAST_T2(class_name, T1, T2, object) (static_cast<class_name<T1, T2>*>(::core::StaticDownCast(RUNTIME_CLASS_T2(class_name, T1, T2), object)))
