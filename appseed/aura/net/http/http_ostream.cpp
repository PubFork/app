#include "framework.h"


namespace http
{


   stream::stream()
   {

   }


   stream::stream(::file::file * pbuffer) :
      ::file::plain_text_stream(pbuffer)
   {

   }


   stream::~stream()
   {

      close();

   }


   /*void stream::write(const char * lpcsz)
   {

      write(lpcsz, strlen(lpcsz));

      return *this;

   }*/

   void stream::write (const string & str)
   {

      write((const char *) str, str.get_length());

   }


   stream & stream::operator << (::memory_file & memfile)
   {

      write(memfile.get_data(), (memory_size_t) memfile.get_length());

      return *this;

   }





   /*bool stream::read_string(string & str)
   {
      uint_ptr nRead;
      char ch;
      bool bR = false;
      str.Empty();
      while((nRead = read(&ch, sizeof(ch))) > 0)
      {
         str += ch;
         if(bR)
         {
            if(ch == '\n')
            {
               break;
            }
            else
            {
               seek(-1, ::file::seek_current);
            }
         }
         else if(ch == '\r')
         {
            bR = true;
         }
         else if(ch == '\n')
         {
            break;
         }
      }
      return str.has_char();
   }*/

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


   /*    void stream::to_string(string & str);
         {

            read(str.GetBufferSetLength((int32_t)get_length()), (int32_t)(get_length()));

            str.ReleaseBuffer();

         }*/

} // namespace http
