#include "framework.h"


namespace http
{


   stream::stream()
   {

   }


   stream::stream(::file::file * pbuffer) :
      ::stream(pbuffer),
      ::file::plain_text_stream(pbuffer)
   {

   }


   stream::~stream()
   {

      close();

   }



   void stream::write (const string & str)
   {

      write((const char *) str, str.get_length());

   }


   stream & stream::operator << (::memory_file & memfile)
   {

      write(memfile.get_data(), (memory_size_t) memfile.get_length());

      return *this;

   }






   stream & stream::operator << (::file::file_sp spbuf)
   {
      uint_ptr nRead;
      memory mem;
      if(!mem.allocate(1024 * 1024))
      {
         _throw(memory_exception(get_app()));
      }
      while((nRead = spbuf->read(mem.get_data(), mem.get_size())) > 0)
      {
         write(mem.get_data(), nRead);
      }
      return *this;
   }


} // namespace http
