#pragma once


#include "file_istream.h"


namespace file
{

   namespace array
   {

      template < class ARRAY >
      void write(serialize & ostream, const ARRAY & a)
      {
         ::count count = a.get_count();
         ostream.write(count);
         for (index index = 0; index < count; index++)
         {
            ostream << a.element_at(index);
         }
      }

      template < class ARRAY >
      void read(serialize & istream, ARRAY & a)
      {
         ::count count;
         //istream >> count;
         istream.read(count);

         if (istream.fail())
         {
            return;
         }

         a.allocate(count);
         for (index index = 0; index < count; index++)
         {
            istream >> a.element_at(index);
            if (istream.fail())
            {
               return;
            }
         }
         a.on_after_read();
      }


   } // namespace array

   namespace ptra
   {

      template < class ARRAY >
      void write(serialize & ostream, const ARRAY & a)
      {
         ::count count = a.get_count();
         ostream.write(count);
         for (index index = 0; index < count; index++)
         {
            ostream << *a.element_at(index);
         }
      }

      template < class ARRAY >
      void read(serialize & istream, ARRAY & a)
      {
         ::count count;
         //istream >> count;
         istream.read(count);

         if (istream.fail())
         {
            return;
         }

         a.allocate(count);
         for (index index = 0; index < count; index++)
         {
            istream >> *a.element_at(index);
            if (istream.fail())
            {
               return;
            }
         }
         a.on_after_read();
      }


   } // namespace array

   namespace map
   {

      template < class type_map >
      void write(serialize & ostream, const type_map & m)
      {

         ostream.write(m.get_count());

         auto p = m.PGetFirstAssoc();

         while (p != NULL)
         {

            ostream << p->m_element1;

            ostream << p->m_element2;

            p = m.PGetNextAssoc(p);

         }

      }


      template < class type_map >
      void read(serialize & istream, type_map & m)
      {

         ::count count;

         istream.read(count);

         if (istream.fail())
         {

            return;

         }

         typename type_map::BASE_KEY key;

         typename type_map::BASE_VALUE value;

         for (index index = 0; index < count; index++)
         {

            istream >> key;

            if (istream.fail())
            {

               return;

            }

            istream >> value;

            if (istream.fail())
            {

               return;

            }

            m.set_at(key, value);

         }

         m.on_after_read();

      }

   } // namespace map



} // namespace file


template < class TYPE, class ARG_TYPE = const TYPE &, class ALLOCATOR = ::allocator::def < TYPE > >
serialize & operator << (serialize & s, array < TYPE, ARG_TYPE, ALLOCATOR > & a)
{

   s.stream_array(a);

   return s;

}


template < class TYPE, class ARG_TYPE = const TYPE &, class ALLOCATOR = ::allocator::def < TYPE > >
serialize & operator >> (serialize & s, array < TYPE, ARG_TYPE, ALLOCATOR > & a)
{

   s.stream_array(a);

   return s;

}



template<class TYPE, class ARG_TYPE = const TYPE &>
serialize & operator << (serialize & serialize, raw_array < TYPE, ARG_TYPE> & a)
{

   ASSERT(serialize.is_storing());

   serialize.stream_array(a);

   return serialize;

}


template<class TYPE, class ARG_TYPE = const TYPE &>
serialize & operator >> (serialize & s, raw_array < TYPE, ARG_TYPE > & a)
{

   s.stream_array(a);

   return s;

}



//template < class TYPE, class ARRAY_TYPE = raw_ref_array < TYPE * > >
//serialize & operator << (serialize & s, const ref_array < TYPE, ARRAY_TYPE> & a)
//{
//
//   s.stream_array(a);
//
//   return s;
//
//}
//
//
//template < class TYPE, class ARRAY_TYPE = raw_ref_array < TYPE * > >
//serialize & operator >> (serialize & s, ref_array < TYPE, ARRAY_TYPE > & a)
//{
//
//   s.stream_array(a);
//
//   return s;
//
//}


//CLASS_DECL_AURA bool file_put(const char * path, ::object & s, ::aura::application * papp = NULL);
//CLASS_DECL_AURA bool file_as(::object & s, const char * path, ::aura::application * papp = NULL);
//
//
//template < class ARRAY >
//bool file_put_array(const char * path, const ARRAY & a, ::aura::application * papp = NULL);
//
//
//template < class ARRAY >
//bool file_as_array(ARRAY & a, const char * path, ::aura::application * papp = NULL);





inline file_position_t serialize::tellp()
{
   
   return m_spfile->tell();
   
}


inline serialize & serialize::seekp(file_position_t position)
{
   
   m_spfile->seek_from_begin(position);
   
   return *this;
   
}


inline serialize & serialize::seekp(file_offset_t offset, ::file::e_seek eseek)
{
   
   m_spfile->seek(offset, eseek);
   
   return *this;
   
}


inline memory_size_t serialize::gcount() { return m_gcount; }
inline file_position_t serialize::tellg() { return m_spfile->tell(); }
inline serialize & serialize::seekg(file_position_t position) { m_spfile->seek_from_begin(position); return *this; }
inline serialize & serialize::seekg(file_offset_t offset, ::file::e_seek eseek) { m_spfile->seek(offset, eseek); return *this; }

inline file_size_t serialize::get_left() { return m_spfile->get_length() - m_spfile->get_position(); }
