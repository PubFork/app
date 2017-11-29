#pragma once


class keyboard;
class front_end_schema;

//#include "user_window_map.h"
//#include "user_style.h"


namespace user
{


   class CLASS_DECL_BASE user :
      virtual public ::aura::department
   {
      public:



         ::user::elemental *           m_pmousefocusLButtonDown;
         ::user::elemental *           m_pmousefocusRButtonDown;
         stringa                       m_straEscape;
         //::user::style_sp              m_puserstyle;




         user(::aura::application * papp);
         virtual ~user();



         //::user::style * get_user_style();


         virtual bool init1();
         virtual bool init2();
         virtual bool initialize();




         virtual ::user::elemental * get_mouse_focus_LButtonDown();
         virtual void set_mouse_focus_LButtonDown(::user::elemental * pmousefocus);
         virtual ::user::elemental * get_mouse_focus_RButtonDown();
         virtual void set_mouse_focus_RButtonDown(::user::elemental * pmousefocus);



         virtual void SendMessageToWindows(UINT message, WPARAM wParam, LPARAM lParam);

         virtual bool finalize();




         virtual sp(type) controltype_to_typeinfo(::user::e_control_type type);





   };



} // namespace user



