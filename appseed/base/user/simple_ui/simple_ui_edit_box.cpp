#include "framework.h" // from "base/user/user.h"
//#include "base/user/user.h"
#include "aura/user/colorertake5/colorertake5.h"


namespace simple_ui
{


   edit_box::edit_box(::aura::application * papp) :
      ::object(papp),
      ::user::interaction(papp),
      ::user::plain_edit(papp)
   {

      m_iPos = 0;

   }


   edit_box::~edit_box()
   {

   }


   void edit_box::install_message_routing(::message::sender * psender)
   {

      ::user::plain_edit::install_message_routing(psender);

      IGUI_MSG_LINK(WM_KEYDOWN, psender, this, &edit_box::_001OnKeyDown);
      IGUI_MSG_LINK(WM_KEYUP, psender, this, &edit_box::_001OnKeyDown);
      IGUI_MSG_LINK(WM_LBUTTONDOWN, psender, this, &edit_box::_001OnLButtonDown);
      IGUI_MSG_LINK(WM_LBUTTONUP, psender, this, &edit_box::_001OnLButtonUp);

   }


   void edit_box::_001OnLButtonDown(::message::message * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

//      SCAST_PTR(::message::mouse,pmouse,pobj);

  //    keyboard_set_focus();

//      pmouse->m_bRet = true;
      pobj->previous();
      pobj->m_bRet = true;
   }


   void edit_box::_001OnLButtonUp(::message::message * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);
      pobj->previous();

//      SCAST_PTR(::message::mouse,pmouse,pobj);

      pobj->m_bRet = true;

   }



   bool edit_box::keyboard_focus_is_focusable()
   {

      return true;

   }


   /*

   CLASS_DECL_BASE char to_upper(int32_t ch)
   {

   if(ch >= 'a' && ch <= 'z')
   {
   ch = ch - 'a' + 'A';
   }

   return ch;

   }


   CLASS_DECL_BASE char * to_upper(char * pchParam)
   {
   char * pch = pchParam;
   while(*pch == '\0')
   {
   *pch = to_upper(*pch);
   pch++;
   }
   return pchParam;
   }


   */


   void edit_box::_001OnDraw(::draw2d::graphics * pgraphics)
   {


      ::user::plain_edit::_001OnDraw(pgraphics);


   }


   void edit_box::_001OnKeyDown(::message::message * pobj)
   {
      pobj->previous();
      pobj->m_bRet = true;
      return;


   }


} // namespace simple_ui
