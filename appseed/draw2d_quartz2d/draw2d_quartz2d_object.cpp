#include "framework.h"


namespace draw2d_quartz2d
{
   
   
   
   object::object()
   {
      
   }
   
   
   object::~object()
   {
      
   }
   
   
   int32_t object::get_object(int32_t nCount, LPVOID lpObject) const
   {
      
      return 0;
      
   }
   
   
   bool object::CreateStockObject(int32_t nIndex)
   {
      
      return 0;
      
   }
   
   
   bool object::UnrealizeObject()
   {
   
      return 0;
      
   }
   
   
   UINT object::GetObjectType() const
   {
   
      return 0;
      
   }
   
   
   bool object::operator==(const ::draw2d::object& obj) const
   {
      
      return false;
      
   }
   
   
   bool object::operator!=(const ::draw2d::object& obj) const
   {
      
      return true;
      
   }
   
   
   object * graphics_object_allocator(::base::application * papp, HANDLE h)
   {
      
      return NULL;
      
   }
   
   
   bool object::delete_object()
   {

      return false;
      
   }
   

   void object::dump(dump_context & dumpcontext) const
   {

      ::object::dump(dumpcontext);
      
   }
   

   void object::assert_valid() const
   {

      ::object::assert_valid();

   }
   

   void * object::get_os_data() const
   {
      
      return const_cast < object * >(this);
      
   }
   
   
} // namespace draw2d_quartz2d



