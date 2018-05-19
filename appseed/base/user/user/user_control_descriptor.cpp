#include "framework.h"


namespace user
{


   control_descriptor::control_descriptor()
   {

      clear();


   }


   control_descriptor::~control_descriptor()
   {

      //if(m_pcontrol != NULL)
      //{

      //   if(m_bCreated)
      //   {

      //      m_pcontrol->DestroyWindow();

      //   }
      //   else if(m_bSubclassed)
      //   {

      //      m_pcontrol->unsubclass_window();

      //   }

      //   m_pcontrol.release();

      //}

   }


   void control_descriptor::clear()
   {

      m_id.is_empty();
      m_iItem = 0;
      m_econtroltype = control_type_none;
      m_bTransparent = false;
      m_bCreated = false;
      m_edatatype = control_data_type_string;
      m_flagsfunction.unsignalize_all();
      m_controlmap.remove_all();
      m_puiParent = NULL;
      m_bSubclassed = false;
      m_iSubItem = -1;

   }


   control_descriptor::control_descriptor(const class control_descriptor & control_descriptor)
   {

      operator =(control_descriptor);

   }


   class control_descriptor & control_descriptor::operator = (const control_descriptor & control_descriptor)
   {

      if (&control_descriptor == this)
         return *this;

      m_iItem = control_descriptor.m_iItem;
      m_id = control_descriptor.m_id;
      m_econtroltype = control_descriptor.m_econtroltype;
      m_dataid = control_descriptor.m_dataid;
      m_bTransparent = control_descriptor.m_bTransparent;
      m_flagsfunction = control_descriptor.m_flagsfunction;
      m_typeinfo = control_descriptor.m_typeinfo;
      m_bCreated = control_descriptor.m_bCreated;
      m_edatatype = control_descriptor.m_edatatype;
      m_idPrivateDataSection = control_descriptor.m_idPrivateDataSection;
      //m_pcontrol              = control_descriptor.m_pcontrol;
      m_controlmap.remove_all();
      m_eddx = control_descriptor.m_eddx;
      m_ddx.m_pvoid = control_descriptor.m_ddx.m_pvoid;
      m_puiParent = control_descriptor.m_puiParent;
      m_iSubItem = control_descriptor.m_iSubItem;
      m_setValue = control_descriptor.m_setValue;
      m_iSubItemDisableCheckBox = control_descriptor.m_iSubItemDisableCheckBox;
      m_iSubItemDuplicateCheckBox = control_descriptor.m_iSubItemDuplicateCheckBox;
      m_iaSubItemDuplicate = control_descriptor.m_iaSubItemDuplicate;
      m_iaSubItemDisable = control_descriptor.m_iaSubItemDisable;

      return *this;

   }


   bool control_descriptor::operator == (const control_descriptor & control_descriptor) const
   {

      return m_id == control_descriptor.m_id
             && m_econtroltype == control_descriptor.m_econtroltype
             && m_dataid == control_descriptor.m_dataid
             && m_puiParent == control_descriptor.m_puiParent;

   }


   void control_descriptor::add_function(e_control_function e_control_function)
   {

      m_flagsfunction.signalize(e_control_function);

   }


   void control_descriptor::remove_function(e_control_function e_control_function)
   {

      m_flagsfunction.unsignalize(e_control_function);

   }


   bool control_descriptor::has_function(e_control_function e_control_function)
   {

      return m_flagsfunction.is_signalized(e_control_function);

   }


   void control_descriptor::set_data_type(e_control_data_type edatatype)
   {

      m_edatatype = edatatype;

   }


   e_control_data_type control_descriptor::get_data_type()
   {

      return m_edatatype;

   }


   void control_descriptor::set_ddx_dbflags(::database::id id, int_ptr value)
   {

      m_eddx = ::user::control_ddx_dbflags;

      class ::database::key key(NULL, id);

      m_ddx.m_pdbflags = new class ::user::control_ddx_dbflags(key, value);


   }

   control * control_descriptor::get_control(::user::form * pform, index iItem)
   {

      //sp(control) & pcontrol = m_controlmap[iItem];
      sp(control)  pcontrol = m_controlmap[0];
      if (pcontrol != NULL)
      {
         //pcontrol->m_iEditItem = iItem;

         return pcontrol;

      }

      iItem = 0;

      if (!pform->create_control(this, iItem))
      {

         pcontrol.release();

         return NULL;

      }

      return pcontrol;

   }

   index control_descriptor::find_control(::user::interaction * pui)
   {

      for (auto pair : m_controlmap)
      {

         if (pair.m_element2 == pui)
         {

            return pair.m_element1;

         }

      }

      return -1;

   }


} // namespace user




