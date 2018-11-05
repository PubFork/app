#pragma once


namespace user
{


   class control_descriptor;


   class CLASS_DECL_AURA form :
      virtual public ::user::interaction
   {
   public:


      form();
      virtual ~form();


      virtual bool create_control(class control_descriptor * pdescriptor, index iItem);


      virtual int_ptr _001AddControl(class control_descriptor & descriptor);


   };


} // namespace user


