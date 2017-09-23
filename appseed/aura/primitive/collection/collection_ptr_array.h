#pragma once

#include "collection_ref_array.h"

////////////////////////////////////////////////////////
//
//   array of managed pointers
//   the most that can be done clearly in array 
//   regarding implicit and automatic destruction,
//   deallocation, allocation and construction.
//
template < class TYPE, class ARRAY_TYPE = ref_array < TYPE > >
class ptr_array :
   public ARRAY_TYPE
{
public:


   //DECLARE_AND_IMPLEMENT_DEFAULT_CONSTRUCTION_AND_ASSIGNMENT(ref_array, ARRAY_TYPE)
   //inline ref_array() {}
   //inline ref_array(const ref_array & a) { this->operator = (a); }
   //inline ref_array(ref_array && a) { this->operator = (a); }



   virtual ~ptr_array()
   {

      this->remove_all();

   }

   void remove_all()
   {

      for(index i = 0; i < this->get_size(); i++)
      {

         try
         {

            delete this->element_at(i);

         }
         catch(...)
         {

         }

      }

      ARRAY_TYPE::remove_all();

   }


   ::count remove(TYPE * p)
   {

      ::count cRemoved = 0;

      index iFind = 0;

      while ((iFind = find_first(p, iFind)) >= 0)
      {

         cRemoved++;

         this->remove_at(iFind);

      }

      if (cRemoved > 0)
      {

         try
         {

            delete p;

         }
         catch (...)
         {

         }

      }

      return cRemoved;

   }


   index find_first(TYPE * p, index iFind = 0)
   {

      for (; iFind < this->get_size(); iFind++)
      {

         if (this->element_at(iFind) == p)
         {

            return iFind;

         }

      }

      return -1;

   }


   bool contains(TYPE * p, index iFind = 0)
   {

      return this->find_first(p, iFind) >= 0;

   }


   void remove_at(index i)
   {

      TYPE * p = this->element_at(i);

      ARRAY_TYPE::remove_at(i);

      try
      {

         delete p;

      }
      catch (...)
      {

      }

   }


   //inline ref_array & operator = (const ref_array & a) { this->ARRAY_TYPE::operator = (a); return *this; }
   //inline ref_array & operator = (ref_array && a){ this->ARRAY_TYPE::operator = (a); return *this; }


   inline TYPE & operator()(index i) { return *this->element_at(i); }
   inline const TYPE & operator()(index i) const { return *this->element_at(i); }



};



