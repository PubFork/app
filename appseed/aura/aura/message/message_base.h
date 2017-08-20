#pragma once


#undef new



namespace message
{


   class CLASS_DECL_AURA timer: virtual public base
   {
   public:


      timer(::aura::application * papp): ::message::base(papp) {}
      using ::message::base::set;
      virtual void set(::user::primitive * pwnd,UINT uiMessage,WPARAM wparam,::lparam lparam,LRESULT & lresult);
      UINT m_nIDEvent;
   };



} // namespace message


#define new AURA_NEW
