#pragma once


namespace user
{


   class CLASS_DECL_AURA menu_command :
      virtual public ::user::command,
      virtual public ::user::check,
      virtual public ::user::set_text
   {
   public:


      menu_item_ptra *     m_pitema;
      menu_item *          m_pitemContainer;


      menu_command(::aura::application * papp);


      void delete_this() override;

      virtual void Enable(bool bOn, ::action::context actioncontext) override;
      virtual void _001SetCheck(::check::e_check echeck, ::action::context actioncontext) override;
      virtual void _001SetText(const string & lpszText, ::action::context actioncontext) override;

   };


} // namespace user



