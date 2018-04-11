#pragma once


namespace user
{


   class CLASS_DECL_BASE view_update_hint :
      virtual public ::object
   {
   public:


      enum e_hint
      {

         hint_none,
         hint_open_document,
         hint_create_views,
         hint_pre_close_document,
         hint_after_change_text,
         hint_after_change_text_delayed,
         hint_control_event,
         hint_delete_contents,
         hint_key_down,

      };


      e_hint                     m_ehint;
      bool                       m_bOk;
      ::user::control_event *    m_pusercontrolevent;
      ::user::interaction *      m_pui;
      ::user::e_key              m_ekey;
      bool                       m_bEnterKeyPressed;


      bool is_type_of(e_hint ehint) const;


      view_update_hint(::aura::application * papp);
      virtual ~view_update_hint();


   };


} // namespace user



