#pragma once


namespace user
{


   class CLASS_DECL_AURA menu_command :
      public ::user::command,
      public ::user::check
   {
      public:


         menu_item_ptra *     m_pitema;
         menu_item *          m_pitemContainer;


         menu_command(::aura::application * papp);


         virtual void Enable(bool bOn, ::action::context actioncontext);
         virtual void _001SetCheck(check::e_check echeck, ::action::context actioncontext);
         virtual void SetText(const char * lpszText, ::action::context actioncontext);

   };


} // namespace user



