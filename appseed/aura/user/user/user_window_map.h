#pragma once

//#ifdef _WIN64
//template <>
//inline UINT HashKey(int_ptr key)
//{
//   // default identity hash - works for most primitive values
//   return (uint32_t)(((uint_ptr)key) >> 32);
//}
//#else
//template <>
//inline UINT HashKey(int_ptr key)
//{
//   // default identity hash - works for most primitive values
//   return (uint32_t)(((uint_ptr)key) >> 16);
//}
//#endif

namespace user
{


   class interaction_base;


   class CLASS_DECL_AURA window_map :
      virtual public ::object
   {
   public:


      map < oswindow, oswindow, ::user::interaction_base *, ::user::interaction_base * > m_map;


      window_map(::aura::application * papp);
      virtual ~window_map();


      ::user::interaction_base * get(oswindow oswindow);


      void set(oswindow oswindow, const ::user::interaction_base * pinterface);

   };


} // namespace user


