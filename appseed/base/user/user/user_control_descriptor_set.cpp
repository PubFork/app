#include "framework.h"


namespace user
{


   control_descriptor_set::control_descriptor_set()
   {

   }


   control_descriptor_set::~control_descriptor_set()
   {

   }


   sp(control) control_descriptor_set::get_control(::user::form_window * pform, id id, int iItem)
   {

      for (int32_t i = 0; i < this->get_size(); i++)
      {

         class control_descriptor & control_descriptor = *this->element_at(i);

         if (control_descriptor.m_id == id)
         {

            return control_descriptor.get_control(pform, iItem);

         }

      }

      return NULL;

   }


   bool control_descriptor_set::find_control(::user::interaction * pui, index & iItem, index & iSubItem)
   {

      for (int32_t i = 0; i < this->get_size(); i++)
      {

         class control_descriptor & control_descriptor = *this->element_at(i);

         iItem = control_descriptor.find_control(pui);

         if (iItem >= 0)
         {

            iSubItem = control_descriptor.m_iSubItem;

            return true;

         }

      }

      iItem = -1;

      iSubItem = -1;

      return false;

   }


   //class control_descriptor * control_descriptor_set::get(sp(::user::interaction) puie)
   //{

   //   sp(control) pcontrol =  (puie.m_p);

   //   if(pcontrol == NULL)
   //      return NULL;

   //   for(int32_t i = 0; i < this->get_size(); i++)
   //   {

   //      class control_descriptor & control_descriptor = *this->element_at(i);

   //      if(control_descriptor.m_pcontrol == pcontrol)
   //      {

   //         return &control_descriptor;

   //      }

   //   }

   //   return NULL;

   //}


   class control_descriptor * control_descriptor_set::get_by_sub_item(int32_t iSubItem)
   {

      for (int32_t i = 0; i < this->get_size(); i++)
      {

         class control_descriptor & control_descriptor = *this->element_at(i);

         if (control_descriptor.m_iSubItem == iSubItem)
         {

            return &control_descriptor;

         }

      }

      return NULL;

   }


} // namespace user



