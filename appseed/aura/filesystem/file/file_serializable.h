#pragma once


#include "aura_serialize.h"


namespace file
{


   class istream;
   class ostream;






   namespace array
   {

      //template < class ARRAY >
      //void s(ostream & ostream,const ARRAY & a)
      //{
      //   ::count count = a.get_count();
      //   ostream.write_arbitrary(count);
      //   for(index index = 0; index < count; index++)
      //   {
      //      ostream << a.element_at(index);
      //   }
      //}

      template < class TYPE >
      void defer_alloc(TYPE & t)
      {

      }

      //template < class ARRAY >
      //void read(istream & istream,ARRAY & a)
      //{
      //   ::count count;
      //   //istream >> count;
      //   istream.read_arbitrary(count);

      //   if(istream.fail())
      //   {
      //      return;
      //   }

      //   a.allocate(count);
      //   for(index index = 0; index < count; index++)
      //   {
      //      defer_alloc(a.element_at(index));
      //      istream >> a.element_at(index);
      //      if(istream.fail())
      //      {
      //         return;
      //      }
      //   }
      //   a.on_after_read();
      //}

      //template < typename TYPE >
      //void read(istream & istream, sp(TYPE) & a)
      //{
      //   ::count count;
      //   //istream >> count;
      //   istream.read_arbitrary(count);

      //   if(istream.fail())
      //   {
      //      return;
      //   }

      //   a.allocate(count);
      //   for(index index = 0; index < count; index++)
      //   {
      //      if(a.is_null())
      //      {

      //         a = canew(TYPE);

      //      }
      //      istream >> a.element_at(index);
      //      if(istream.fail())
      //      {
      //         return;
      //      }
      //   }
      //   a.on_after_read();
      //}


   } // namespace array

   namespace ptra
   {

      //template < class ARRAY >
      //void write(ostream & ostream,const ARRAY & a)
      //{
      //   ::count count = a.get_count();
      //   ostream.write_arbitrary(count);
      //   for(index index = 0; index < count; index++)
      //   {
      //      ostream << *a.element_at(index);
      //   }
      //}

      //template < class ARRAY >
      //void read(istream & istream,ARRAY & a)
      //{
      //   ::count count;
      //   //istream >> count;
      //   istream.read_arbitrary(count);

      //   if(istream.fail())
      //   {
      //      return;
      //   }

      //   a.allocate(count);
      //   for(index index = 0; index < count; index++)
      //   {
      //      istream >> *a.element_at(index);
      //      if(istream.fail())
      //      {
      //         return;
      //      }
      //   }
      //   a.on_after_read();
      //}


   } // namespace array

   //namespace map
   //{

   //   template < class type_map >
   //   void write(ostream & ostream,const type_map & m)
   //   {

   //      ostream.write_arbitrary(m.get_count());

   //      auto p = m.PGetFirstAssoc();

   //      while(p != NULL)
   //      {

   //         ostream << p->m_element1;

   //         ostream << p->m_element2;

   //         p = m.PGetNextAssoc(p);

   //      }

   //   }


   //   template < class type_map >
   //   void read(istream & istream,type_map & m)
   //   {

   //      ::count count;

   //      istream.read_arbitrary(count);

   //      if (istream.fail())
   //      {

   //         return;

   //      }

   //      typename type_map::BASE_KEY key;

   //      typename type_map::BASE_VALUE value;

   //      for(index index = 0; index < count; index++)
   //      {

   //         istream >> key;

   //         if (istream.fail())
   //         {

   //            return;

   //         }

   //         istream >> value;

   //         if (istream.fail())
   //         {

   //            return;

   //         }

   //         m.set_at(key,value);

   //      }

   //      m.on_after_read();

   //   }

   //} // namespace map



} // namespace file




CLASS_DECL_AURA bool file_put(const char * path, ::serializable & s, ::aura::application * papp = NULL);
CLASS_DECL_AURA bool file_as(::serializable & s, const char * path, ::aura::application * papp = NULL);


template < class ARRAY >
bool file_put_array(const char * path, const ARRAY & a, ::aura::application * papp = NULL);


template < class ARRAY >
bool file_as_array(ARRAY & a, const char * path, ::aura::application * papp = NULL);



