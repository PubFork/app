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

   class CLASS_DECL_AURA get_text :
      virtual public object
   {
   public:

      virtual void _001GetText(string & str) const;

      virtual strsize _001GetTextLength() const;
      virtual void _001GetText(char * psz, strsize len) const;
      virtual void _001GetText(string & str, index iBeg, index iEnd) const;

   };

   class CLASS_DECL_AURA set_text :
      virtual public object
   {
   public:

      virtual void _001SetText(const string & str, ::action::context actioncontext);

      virtual void _001SetText(const char * psz, strsize len, ::action::context actioncontext);


   };


   class CLASS_DECL_AURA edit_text :
      virtual public get_text,
      virtual public set_text
   {
   public:


      virtual void _001GetSel(strsize & iBeg, strsize & iEnd) const;
      virtual void _001SetSel(strsize iBeg, strsize iEnd);
      virtual void _001SetSelEnd(strsize iSelEnd);


      virtual void _001GetSelText(string & str) const;
      virtual void _001SetSelText(const char * psz, ::action::context actioncontext);


      virtual void _001GetViewSel(strsize &iSelStart, strsize &iSelEnd) const;


      virtual void MacroBegin();
      virtual void MacroEnd();


   };

   class CLASS_DECL_AURA elemental :
      virtual public ::user::primitive,
      virtual public ::user::check,
      virtual public ::user::edit_text
   {
   public:


      DWORD                               m_dwFocusStartTick;
      bool                                m_bUserElementalOk;


      elemental();
      virtual ~elemental();


      virtual void pre_translate_message(::message::message * pobj);


      virtual ::user::elemental * first_child_elemental();
      virtual ::user::elemental * top_elemental();
      virtual ::user::elemental * under_elemental();
      virtual ::user::elemental * above_elemental();
      virtual ::user::elemental * next_elemental();
      virtual ::user::elemental * previous_elemental();


      // keyboard focus
      virtual bool on_keyboard_focus(::user::elemental * pfocus);
      virtual void keyboard_focus_OnTimer(int32_t iTimer);
      virtual void keyboard_focus_OnChar(::message::message * pobj);
      virtual void keyboard_focus_OnSysChar(::message::message * pobj);
      virtual void keyboard_focus_OnKeyDown(::message::message * pobj);
      virtual void keyboard_focus_OnKeyUp(::message::message * pobj);
      virtual ::user::interaction * GetParent() const;
      virtual ::user::elemental * get_parent() const;
      virtual ::user::interaction * get_wnd() const;
      virtual ::user::interaction_impl * get_impl() const;
      virtual ::user::elemental * get_wnd_elemental() const;
      virtual bool BaseOnControlEvent(control_event * pevent);
      virtual elemental * keyboard_get_next_focusable(elemental * pfocus = NULL,bool bSkipChild = false,bool bSkipSiblings = false,bool bSkipParent = false);
      virtual bool keyboard_set_focus();

      // focus
      virtual bool keyboard_focus_is_focusable();
      virtual bool keyboard_focus_OnSetFocus();
      virtual bool keyboard_focus_OnKillFocus();
      virtual bool keyboard_focus_OnChildKillFocus();

      // mouse focus

      virtual void mouse_focus_OnLButtonUp(::message::message * pobj);




      virtual void _001OnTimer(::timer * ptimer);

      virtual void on_reset_focus_start_tick();


      virtual bool IsWindow() const;


   };




} // namespace user




