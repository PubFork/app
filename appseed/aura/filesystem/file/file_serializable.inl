#pragma once


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
stream & operator << (stream & s, array < TYPE, ARG_TYPE, ALLOCATOR > & a)
{

   s.stream_array(a);

   return s;

}


template < class TYPE, class ARG_TYPE = const TYPE &, class ALLOCATOR = ::allocator::def < TYPE > >
stream & operator >> (stream & s, array < TYPE, ARG_TYPE, ALLOCATOR > & a)
{

   s.stream_array(a);

   return s;

}



template<class TYPE, class ARG_TYPE = const TYPE &>
stream & operator << (stream & serialize, raw_array < TYPE, ARG_TYPE> & a)
{

   ASSERT(serialize.is_storing());

   serialize.stream_array(a);

   return serialize;

}


template<class TYPE, class ARG_TYPE = const TYPE &>
stream & operator >> (stream & s, raw_array < TYPE, ARG_TYPE > & a)
{

   s.stream_array(a);

   return s;

}





inline file_position_t stream::tellp()
{

   return m_spfile->tell();

}


inline stream & stream::seekp(file_position_t position)
{

   m_spfile->seek_from_begin(position);

   return *this;

}


inline stream & stream::seekp(file_offset_t offset, ::file::e_seek eseek)
{

   m_spfile->seek(offset, eseek);

   return *this;

}


inline memory_size_t stream::gcount() { return m_gcount; }
inline file_position_t stream::tellg() { return m_spfile->tell(); }
inline stream & stream::seekg(file_position_t position) { m_spfile->seek_from_begin(position); return *this; }
inline stream & stream::seekg(file_offset_t offset, ::file::e_seek eseek) { m_spfile->seek(offset, eseek); return *this; }

inline file_size_t stream::get_left() { return m_spfile->get_length() - m_spfile->get_position(); }
