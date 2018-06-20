#include "framework.h"


namespace user
{


   form::form()
   {

      m_pform = this;

   }


   form::~form()
   {

   }


   bool form::create_control(class control_descriptor * pdescriptor, index iItem)
   {

      return false;

   }


   int_ptr form::_001AddControl(class control_descriptor & descriptor)
   {

      return -1;

   }



} // namespace user







