#pragma once


namespace user
{


   class CLASS_DECL_AURA check :
      virtual public object
   {
   public:


      virtual ::check::e_check _001GetCheck();
      virtual void _001SetCheck(bool b, ::action::context actioncontext);
      virtual void _001SetCheck(::check::e_check check, ::action::context actioncontext);
      virtual void _001ToggleCheck(::action::context actioncontext);


   };


} // namespace user



