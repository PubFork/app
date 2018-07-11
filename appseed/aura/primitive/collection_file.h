#pragma once


#include "aura/filestream.h"
#include "collection.h"

/*

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR >
serialize & operator << (serialize & os, const map < KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR > & a)
{
   ::file::map::write(os, a);
   return os;
}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR >
serialize & operator >> (serialize & is, map < KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR > & a)
{
   ::file::map::read(is, a);
   return is;
}

*/

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR >
serialize & operator << (serialize & os, const ::property_map & a)
{
   ::file::map::write(os, a);
   return os;
}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR >
serialize & operator >> (serialize & is, property_map & a)
{
   ::file::map::read(is, a);
   return is;
}




