#include "framework.h"



namespace user
{


   elemental::elemental()
   {

      m_bUserElementalOk = false;

   }


   elemental::~elemental()
   {

   }


   void elemental::pre_translate_message(::message::message * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

   }


   // keyboard focus
   bool elemental::on_keyboard_focus(::user::elemental * pfocus)
   {
      UNREFERENCED_PARAMETER(pfocus);

      return true;

   }


   void elemental::keyboard_focus_OnTimer(int32_t iTimer)
   {
      UNREFERENCED_PARAMETER(iTimer);
   }

   void elemental::keyboard_focus_OnChar(::message::message * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void elemental::keyboard_focus_OnSysChar(::message::message * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void elemental::keyboard_focus_OnKeyDown(::message::message * pobj)
   {

   }

   void elemental::keyboard_focus_OnKeyUp(::message::message * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }


   ::user::interaction * elemental::GetParent() const
   {

      return NULL;

   }

   ::user::interaction * elemental::get_wnd() const
   {

      return NULL;

   }


   ::user::interaction_impl * elemental::get_impl() const
   {

      return NULL;

   }

   void elemental::on_control_event(control_event * pevent)
   {

      UNREFERENCED_PARAMETER(pevent);

   }


   bool elemental::keyboard_focus_is_focusable()
   {

      return Application.keyboard_focus_is_focusable(this);
   }

   bool elemental::keyboard_focus_OnSetFocus()
   {

      on_reset_focus_start_tick();

      // get_keyboard_focus will return the control with focus


      // return true to set focus to this control
      return Application.keyboard_focus_OnSetFocus(this);
   }


   bool elemental::keyboard_focus_OnKillFocus()
   {

      return true;

   }


   bool elemental::keyboard_focus_OnChildKillFocus()
   {

      return true;

   }


   elemental * elemental::keyboard_get_next_focusable(elemental * pfocus,bool bSkipChild,bool bSkipSiblings,bool bSkipParent)
   {

      sp(elemental) puiThis = this;

      sp(elemental) puiFocus = pfocus != NULL ? pfocus : this;



      elemental * pfocusTry;

      if(puiFocus == NULL)
         return NULL;

      if(puiThis == NULL)
         return NULL;

      single_lock(puiThis->m_pauraapp->m_pmutex,TRUE);

      sp(elemental) pui;

      if(!bSkipChild)
      {

         pui = puiThis->first_child_elemental();

         if(pui != NULL)
         {

            if(pui->keyboard_focus_is_focusable())
               return pui;

            pui = pui->keyboard_get_next_focusable(puiFocus,false,false,true);

            if(pui != NULL)
               return pui;

         }

      }

      if(!bSkipSiblings)
      {

         pui = puiThis->next_elemental();

         while(pui != NULL)
         {

            if(pui->keyboard_focus_is_focusable())
               return pui;

            pfocusTry = pui->keyboard_get_next_focusable(puiFocus,false,true,true);

            if(pfocusTry != NULL)
               return pfocusTry;

            pui = pui->next_elemental();

         }

      }

      if(!bSkipParent)
      {


         if(puiThis->GetParent() != NULL)
         {

            pui = puiThis->get_parent()->keyboard_get_next_focusable(puiFocus,true);

            if(pui.is_set())
               return pui;

         }

      }

      if(!bSkipSiblings)
      {

         pui = puiThis->first_child_elemental();

         if(pui != puiThis)
         {

            while(pui != NULL && pui != puiFocus)
            {

               if(pui->keyboard_focus_is_focusable())
                  return pui;

               pfocusTry = pui->keyboard_get_next_focusable(puiFocus,false,true,true);

               if(pfocusTry != NULL)
                  return pfocusTry;

               pui = pui->next_elemental();

            }

         }

      }


      return NULL;

   }



   bool elemental::keyboard_set_focus()
   {
      Session.set_keyboard_focus((this));
      return true;
   }

   // mouse focus

   void elemental::mouse_focus_OnLButtonUp(::message::message * pobj)
   {
   }

   // text interface

   void get_text::_001GetText(string & str) const
   {

      UNREFERENCED_PARAMETER(str);

   }


   void edit_text::_001SetSelText(const char * psz, ::action::context actioncontext)
   {

   }

   void set_text::_001SetText(const string & str,::action::context actioncontext)
   {

      UNREFERENCED_PARAMETER(str);
      UNREFERENCED_PARAMETER(actioncontext);

   }


   strsize get_text::_001GetTextLength() const
   {

      string str;

      _001GetText(str);

      return str.get_length();

   }


   void get_text::_001GetText(char * psz, strsize len) const
   {

      string str;

      _001GetText(str);

      strncpy(psz,str,len);

   }


   void get_text::_001GetText(string & str, strsize iBeg, strsize iEnd) const
   {

      // default implementation, probably inefficient
      // _001GetText(string) returns big string
      // or retrieving entire string, instead of portions, is slow

      string strText;

      _001GetText(strText);

      str = strText.Mid(iBeg, iEnd - iBeg);

   }


   void set_text::_001SetText(const char * psz, strsize iLen, ::action::context actioncontext)
   {

      _001SetText(string(psz, iLen),actioncontext);

   }


   void edit_text::_001GetSel(strsize & iBeg, strsize & iEnd) const
   {

      UNREFERENCED_PARAMETER(iBeg);
      UNREFERENCED_PARAMETER(iEnd);

   }


   void edit_text::_001SetSel(strsize iBeg, strsize iEnd)
   {

      UNREFERENCED_PARAMETER(iBeg);
      UNREFERENCED_PARAMETER(iEnd);

   }


   void edit_text::_001GetViewSel(strsize & iBeg, strsize & iEnd) const
   {

      UNREFERENCED_PARAMETER(iBeg);
      UNREFERENCED_PARAMETER(iEnd);

   }


   void edit_text::_001SetSelEnd(strsize iEnd)
   {

      UNREFERENCED_PARAMETER(iEnd);

   }


   void edit_text::_001GetSelText(string & str) const
   {

      // default implementation, maybe inefficient (if _001GetText is the default implementation)

      index iBeg, iEnd;

      _001GetSel(iBeg, iEnd);

      _001GetText(str, iBeg, iEnd);

   }


   void edit_text::MacroBegin()
   {

   }

   void edit_text::MacroEnd()
   {

   }


   // check interface

   ::check::e_check check::_001GetCheck()
   {

      return ::check::unchecked;

   }


   void check::_001SetCheck(bool bChecked,::action::context actioncontext)
   {

      _001SetCheck((::check::e_check) (bChecked ? ::check::checked : ::check::unchecked),actioncontext);

   }


   void check::_001SetCheck(::check::e_check echeck,::action::context actioncontext)
   {

      UNREFERENCED_PARAMETER(echeck);
      UNREFERENCED_PARAMETER(actioncontext);

   }


   void check::_001ToggleCheck(::action::context actioncontext)
   {

      if(_001GetCheck() == ::check::checked)
      {

         _001SetCheck(::check::unchecked,actioncontext);

      }
      else if(_001GetCheck() == ::check::unchecked)
      {

         _001SetCheck(::check::checked,actioncontext);

      }
      else if(_001GetCheck() == ::check::tristate)
      {

         _001SetCheck(::check::unchecked,actioncontext);

      }
      else
      {

         _001SetCheck(::check::unchecked,actioncontext);

      }

   }


   ::user::elemental * elemental::first_child_elemental()
   {

      return NULL;

   }


   ::user::elemental * elemental::top_elemental()
   {

      return NULL;

   }


   ::user::elemental * elemental::under_elemental()
   {

      return NULL;

   }


   ::user::elemental * elemental::above_elemental()
   {

      return NULL;

   }


   ::user::elemental * elemental::next_elemental()
   {

      return NULL;

   }


   ::user::elemental * elemental::previous_elemental()
   {

      return NULL;

   }

   ::user::elemental * elemental::get_parent() const
   {

      return NULL;

   }

   ::user::elemental * elemental::get_wnd_elemental() const
   {

      return NULL;

   }

   void elemental::_001OnTimer(::timer * ptimer)
   {

      UNREFERENCED_PARAMETER(ptimer);

   }


   void elemental::on_reset_focus_start_tick()
   {

      m_dwFocusStartTick = ::get_tick_count();

   }


   bool elemental::IsWindow() const
   {

      return m_bUserElementalOk;

   }


} // namespace user




