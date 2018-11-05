#include "framework.h"


namespace draw2d
{
   
   
   object::object()
   {
      
      
   }
   

   object::~object()
   {

      destroy();

   }

   void object::dump(dump_context & dumpcontext) const
   {
      
      UNREFERENCED_PARAMETER(dumpcontext);
      
      ::exception::throw_interface_only(get_app());
      
   }
   
   void object::assert_valid() const
   {
      ::exception::throw_interface_only(get_app());
   }
   

   bool object::CreateStockObject(int32_t nIndex)
   {
      ::exception::throw_interface_only(get_app());
      return false;
   }

   bool object::UnrealizeObject()
   {
      ::exception::throw_interface_only(get_app());
      return false;
   }

   UINT object::GetObjectType() const
   {
      ::exception::throw_interface_only(get_app());
      return 0;
   }

   bool object::operator==(const object & obj) const
   {
      UNREFERENCED_PARAMETER(obj);
      ::exception::throw_interface_only(get_app());
      return false;
   }

   bool object::operator!=(const object & obj) const
   {
      UNREFERENCED_PARAMETER(obj);
      ::exception::throw_interface_only(get_app());
      return false;
   }


   void * object::get_os_data() const
   {

      return 0;

   }

   void * object::get_os_data_ex(int i) const
   {

      if(i == 0)
      {
         return get_os_data();
      }
      else
      {
         return NULL;
      }

   }



   bool object::is_set()
   {

      return get_os_data() != 0;

   }


   bool object::is_updated()
   {

      return is_set() && m_bUpdated;

   }


   void object::defer_update() const
   {

      if(!m_bUpdated)
      {

         const_cast < ::draw2d::object * > (this)->destroy();

         const_cast < ::draw2d::object * > (this)->create();

         const_cast < ::draw2d::object * > (this)->m_bUpdated = true;

      }

   }


   bool object::create()
   {

      return true;

   }


   bool object::destroy()
   {

      return true;

   }


} // namespace draw2d





