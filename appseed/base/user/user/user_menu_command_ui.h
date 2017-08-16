#pragma once


namespace user
{


   class CLASS_DECL_BASE menu_command_ui : public command_ui
   {
   public:
      
      
      menu_item_ptra *  m_pitema;
      menu_item *          m_pitemContainer;
      
      
      menu_command_ui(::aura::application * papp);
      
      
      virtual void Enable(bool bOn, ::action::context actioncontext);
      virtual void _001SetCheck(check::e_check echeck, ::action::context actioncontext);
      virtual void SetText(const char * lpszText, ::action::context actioncontext);
      
   };


} // namespace user



