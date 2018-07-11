#include "framework.h"


namespace file
{


   stream_base::stream_base()
   {

      m_iostate         = goodbit;
      m_fmtflags        = nofmtflags;
      m_precision       = 0;

   }


   stream_base::stream_base(file_sp pfile):
      m_spfile(pfile)
   {

      m_iostate         = goodbit;
      m_fmtflags        = nofmtflags;
      m_precision       = 0;

   }


   stream_base::stream_base(const stream_base & buffer)
   {

      m_iostate         = buffer.m_iostate;
      m_fmtflags        = nofmtflags;
      m_precision       = 0;
      m_spfile        = buffer.m_spfile;

   }


   stream_base::~stream_base()
   {

   }


   string stream_base::GetFilePath() const
   {

      return m_spfile->GetFilePath();

   }


   void stream_base::close()
   {

      m_spfile.release();

   }


   file_position_t stream_base::seek(file_offset_t offset, e_seek eseek)
   {

      return m_spfile->seek(offset, eseek);

   }

   fmtflags stream_base::setf(fmtflags flagsAdd)
   {

      fmtflags fmtflagsOld = m_fmtflags;

      m_fmtflags = (fmtflags) ((uint32_t) m_fmtflags | (uint32_t) flagsAdd);

      return fmtflagsOld;

   }


   fmtflags stream_base::setf(fmtflags flagsAdd, fmtflags flagsRemove)
   {

      fmtflags fmtflagsOld = m_fmtflags;

      m_fmtflags = (fmtflags) (((uint32_t) m_fmtflags | (uint32_t) flagsAdd) & (~(uint32_t)flagsRemove));

      return fmtflagsOld;

   }


   fmtflags stream_base::flags() const
   {

      return m_fmtflags;

   }

   fmtflags stream_base::flags(fmtflags flags)
   {

      return m_fmtflags = flags;

   }



   file_size_t stream_base::precision() const
   {

      return m_precision;

   }

   file_size_t stream_base::precision(file_size_t prec)
   {

      return m_precision = prec;

   }

   file_size_t stream_base::width() const
   {

      return m_width;

   }

   file_size_t stream_base::width(file_size_t prec)
   {

      return m_width = prec;

   }

   bool stream_base::is_open() const
   {

      if(m_spfile.is_null())
         return false;

      if(!m_spfile->is_open())
         return false;

      return true;

   }



} // namespace file








namespace file
{
   
   
   stream::stream()
   {
      
   }
   
   
   stream::stream(file * pfile):
   m_spfile(pfile)
   {
      
   }
   
   
   //   stream::stream(const stream & stream) :
   //      stream_base(stream)
   //   {
   //
   //   }
   
   
   stream::~stream()
   {
      
   }
   
   
   //   stream & stream::operator = (const stream & stream)
   //   {
   //      istream::operator = (stream);
   //      ostream::operator = (stream);
   //      return *this;
   //   }
   
   
   void stream::close()
   {
      //istream::close();
      //ostream::close();
      
      if(m_spfile.is_set())
      {
         
         m_spfile->close();
         
         m_spfile.release();
         
      }
      
   }
   
   
   void * stream::get_internal_data()
   {
      
      return m_spfile->get_internal_data();
      
   }
   
   
   memory_size_t stream::get_internal_data_size() const
   {
      
      return m_spfile->get_internal_data_size();
      
   }
   
   
   bool stream::set_internal_data_size(memory_size_t c)
   {
      
      return m_spfile->set_internal_data_size(c);
      
   }
   
   
   file_position_t stream::get_position() const
   {
      
      return m_spfile->get_position();
      
   }
   
   
} // namespace file


