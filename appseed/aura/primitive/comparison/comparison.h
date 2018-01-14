#pragma once


#include "comparison_equals.h"
#include "comparison_less.h"
#include "comparison_compare.h"
#include "comparison_hash.h"
#include "comparison_binary.h"
#include "comparison_var_strict.h"

#define unequal(a, b, n) ((a - n < b && b < a + n) || (b - n < a && a < b + n))


template < typename ARG_KEY >
inline int_ptr CompareElements(ARG_KEY element1, ARG_KEY element2)
{

   return element2 - element1;
}



template <  >
inline int_ptr CompareElements<string>(string element1, string  element2)
{

   return element1.compare(element2);

}

template <  >
inline int_ptr CompareElements<void *>(void * element1, void *  element2)
{

   return (byte *)element2 - (byte *)element1;

}

