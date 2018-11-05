//
//  file_byte_stream_memory_file.h
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 10/07/18.
//


#include "file_serialize.h"
#include "file_memory_file.h"


namespace file
{


   class CLASS_DECL_AURA byte_stream_memory_file :
      virtual public serialize,
      virtual public memory_file
   {
   public:


      byte_stream_memory_file(::aura::application * papp);
      virtual ~byte_stream_memory_file();

      virtual file_position_t seek(file_offset_t offset, e_seek seekOrigin);
      virtual file_position_t get_position() const;
      virtual void flush();
      virtual void * get_internal_data();
      virtual const void * get_internal_data() const;
      virtual memory_size_t get_internal_data_size() const;
      virtual bool set_internal_data_size(memory_size_t s);
      virtual void write(const void * p, memory_size_t s);
      virtual memory_size_t read(void * p, memory_size_t s);
      virtual void set_length(file_size_t dwNewLen);
      virtual void close();

   };


} // namespace file




