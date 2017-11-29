#pragma once


namespace base
{


   class CLASS_DECL_BASE session:
      virtual public ::axis::session,
      virtual public :: base ::application
   {
      public:


         ::user::user *                   m_puser;



         session(::aura::application * papp);
         virtual ~session_parent;

         inline ::user::user *                        user() { return m_puser; }

         virtual sp(::user::impact)                      get_view();






         virtual void frame_pre_translate_message(::message::message * pobj) override;

         virtual bool process_init() override;

         virtual bool init1() override;

         virtual bool initialize() override;

         virtual int32_t exit_application() override;

         virtual string fontopus_get_cred(::aura::application * papp,const string & strRequestUrlParam,const RECT & rect,string & strUsername,string & strPassword,string strToken,string strTitle,bool bInteractive, ::user::interactive * pinteractive = NULL) override;

         //virtual void get_cursor_pos(LPPOINT lppoint) override;




         virtual void on_finally_focus_set(::user::elemental * pelementalFocus) override;

         virtual ::user::interaction * create_menu_button(::aura::application * papp) override;

         //virtual oswindow get_capture() override;


         virtual void _001OnDefaultTabPaneDrawTitle(::user::tab_pane & pane, ::user::tab * ptab, ::draw2d::graphics * pgraphics, LPCRECT lpcrect, ::draw2d::brush_sp & brushText) override;

         virtual bool prepare_menu_button(::user::menu_item * pitem) override;

         virtual bool on_ui_mouse_message(::user::mouse * pmouse) override;

   };


} // namespace base


