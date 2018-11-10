#pragma once


#include "aura/primitive/primitive_var.h"
#include "aura/primitive/primitive_property_set.h"
#include "aura/primitive/primitive_application_bias.h"
#include "aura/primitive/primitive_color.h"
#include "aura/primitive/primitive_command.h"
#include "aura/primitive/primitive_command_line.h"
#include "aura/primitive/primitive_create.h"
#include "aura/primitive/primitive_edit.h"
#include "aura/primitive/primitive_factory.h"
#include "aura/primitive/primitive_id.h"
#include "aura/primitive/primitive_id_space.h"
#include "aura/primitive/primitive_interlocked_long.h"
#include "aura/primitive/primitive_interlocked_long_pulse.h"
#include "aura/primitive/primitive_job.h"
#include "aura/primitive/primitive_memory_container.h"
#include "aura/primitive/primitive_relation_set.h"
#include "aura/primitive/primitive_request_signal.h"
#include "aura/primitive/primitive_shared_memory.h"
#include "aura/primitive/primitive_virtual_memory.h"



class CLASS_DECL_AURA parents
{
public:

   pointer_array < object * >    m_ptra;

   parents();
   ~parents();


};


class CLASS_DECL_AURA children
{
public:


   spa(object)                   m_ptra;
   duration                      m_durationWait;


   children();
   ~children();


   //virtual ::count get_count_except_current_thread(::object * pobjectParent);
   virtual void post_quit(::object * pobjectParent);
   virtual ::count wait_quit(::object * pobjectParent, const duration & duration);
   virtual ::count _wait_quit(::object * pobjectParent);


};









namespace file
{

   class writer;
   class reader;

}








namespace lemon
{

   CLASS_DECL_AURA void transfer_to(stream & writer, ::primitive::memory_base & mem, memory_size_t uiBufferSize = 1024 * 1024);

   CLASS_DECL_AURA void transfer_from_begin(stream & reader, ::primitive::memory_base & mem, memory_size_t uiBufferSize = 1024 * 1024);

   CLASS_DECL_AURA void transfer_from(stream & reader, ::primitive::memory_base & mem, memory_size_t uiBufferSize = 1024 * 1024);


} // namespace lemon

CLASS_DECL_AURA stream & operator >> (stream & istream, ::primitive::memory_container & memcontainer);

CLASS_DECL_AURA stream & operator << (stream & ostream, ::primitive::memory_base & mem);

CLASS_DECL_AURA stream & operator >> (stream & istream, ::primitive::memory_base & mem);


#include "primitive.inl"
#include "primitive_factory_impl.inl"
