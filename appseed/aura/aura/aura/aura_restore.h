#pragma once


template <class TYPE> class restore
{
public:


   TYPE *  m_pKept;
   TYPE    m_valueRestore;

   restore(TYPE * pKept);
   restore(TYPE * pKept,const TYPE & valueRestore);
   virtual ~restore();

   void Restore();

};


template <class TYPE>
restore<TYPE>::restore(TYPE * pKept):
restore(pKept, *pKept)
{
   
}


template <class TYPE>
restore<TYPE>::restore(TYPE * pKept,const TYPE & valueRestore) : 
m_pKept(pKept),
m_valueRestore(valueRestore)
{
   
}



template <class TYPE>
restore<TYPE>::~restore()
{

   Restore();
   
}


template <class TYPE>
void restore<TYPE>::Restore()
{

   *m_pKept = m_valueRestore;

}


//#define PRINT_STRING_1_ARGS(message)              PrintString(message, 0, 0)
//#define PRINT_STRING_2_ARGS(message, size)        PrintString(message, size, 0)
//#define PRINT_STRING_3_ARGS(message, size, style) PrintString(message, size, style)
//
//#define GET_4TH_ARG(arg1, arg2, arg3, arg4, ...) arg4
//#define PRINT_STRING_MACRO_CHOOSER(...) \
//    GET_4TH_ARG(__VA_ARGS__, PRINT_STRING_3_ARGS, \
//                PRINT_STRING_2_ARGS, PRINT_STRING_1_ARGS, )
//
//#define PRINT_STRING(...) PRINT_STRING_MACRO_CHOOSER(__VA_ARGS__)(__VA_ARGS__)

#define RESTORE_1(var) ::restore < decltype(var) > TOKEN_CONCAT(restore, __COUNTER__) (&var)
#define RESTORE_2(var, set) ::restore < decltype(var) > TOKEN_CONCAT(restore, __COUNTER__) (&var); var = set


#define GET_3TH_ARG(arg1, arg2, arg3, ...) arg3
#define RESTORE_MACRO_CHOOSER(...) GET_3TH_ARG(__VA_ARGS__, RESTORE_2, RESTORE_1, )
#define RESTORE(...) RESTORE_MACRO_CHOOSER(__VA_ARGS__)(__VA_ARGS__)

