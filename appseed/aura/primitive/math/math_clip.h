#pragma once


template < typename T1, typename T2 >
inline bool convert(T1 & t1, const T2 & t2)
{

   if (::comparison::gt(t2, ::numeric_info < T1 >::get_maximum_value()))
   {

      t1 = ::numeric_info < T1 >::get_maximum_value();

      output_debug_string("clip::assign max clipped");

      return false;

   }

   if (::comparison::lt(t2, ::numeric_info < T1 >::get_minimum_value()))
   {

      t1 = ::numeric_info < T1 >::get_minimum_value();

      output_debug_string("clip::assign min clipped");

      return false;

   }

   t1 = (T1)t2;

   return true;

}


template < typename T1, typename T2 >
inline T1 convert(const T2 & t2)
{

   if (::comparison::gt(t2, ::numeric_info < T1 >::get_maximum_value()))
   {

      output_debug_string("clip::convert max clipped");

      return ::numeric_info < T1 >::get_maximum_value();

   }

   if (::comparison::lt(t2, ::numeric_info < T1 >::get_minimum_value()))
   {

      output_debug_string("clip::convert min clipped");

      return ::numeric_info < T1 >::get_minimum_value();

   }

   return (T1) t2;

}


template < typename T1, typename T2 >
inline bool convert_add(T1 & t1, const T2 & t2)
{

   auto t = t1 + t2;

   if (t > ::numeric_info < T1 >::get_maximum_value())
   {

      t1 = ::numeric_info < T1 >::get_maximum_value();

      output_debug_string("clip::assign max clipped");

      return false;

   }

   if (t < ::numeric_info < T1 >::get_minimum_value())
   {

      t1 = ::numeric_info < T1 >::get_minimum_value();

      output_debug_string("clip::assign min clipped");

      return false;

   }

   t1 = (T1)t;

   return true;

}


template < typename T1, typename T2 >
inline bool convert_multiply(T1 & t1, const T2 & t2)
{

   auto t = t2 * t1;

   if (t > (::numeric_info < T1 >::get_maximum_value()))
   {

      t1 = ::numeric_info < T1 >::get_maximum_value();

      output_debug_string("clip::assign max clipped");

      return false;

   }

   if (t < (::numeric_info < T1 >::get_minimum_value() - t1))
   {

      t1 = ::numeric_info < T1 >::get_minimum_value();

      output_debug_string("clip::assign min clipped");

      return false;

   }

   t1 = (T1) t;

   return true;

}


