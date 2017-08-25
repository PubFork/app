#pragma once


#include "base/user/user/user_control_event.h"
#include "base/user/user/user_box.h"


namespace user
{


   class CLASS_DECL_BASE control :
      virtual public ::user::box
   {
   public:


      enum EMessageParam
      {
         MessageParamGetBaseControlExPtr = 1
      };


      index                      m_iHover;
      e_element                  m_eelementHover;
      control_descriptor *       m_pdescriptor;
      sp(::user::interaction)    m_pwndCustomWindowProc;
      bool                       m_bCustomWindowProc;
      index                      m_iEditItem;
      form_window *              m_pform;
      form_callback *            m_pformcallback;
      bool                       m_bControlExCommandEnabled;


      control();
      virtual ~control();


      virtual void install_message_routing(::message::sender * psender);

      /// if you (developer) don't know how to create a control,
      /// you should be able (control developer pay attention now),
      /// to build a default control with a default constructed
      /// ::user::control_descriptor.
      virtual bool create_control(class control_descriptor * pdescriptor) override;


      bool _003IsCustomMessage();
      ::user::interaction_base * _003GetCustomMessageWnd();


      virtual void _001OnDraw(::draw2d::graphics * pgraphics);



      virtual index get_hover();

      class control_descriptor & descriptor();

      virtual void _003CallCustomDraw(::draw2d::graphics * pgraphics, ::aura::draw_context * pitem);
      virtual bool _003CallCustomWindowProc(sp(::user::interaction) pwnd, UINT message, WPARAM wparam, LPARAM lparam, LRESULT & lresult);
      virtual void _003OnCustomDraw(::draw2d::graphics * pgraphics, ::aura::draw_context * pitem);
      virtual void _003CustomWindowProc(::message::message * pobj);

      virtual form_window * get_form();

      //virtual form_list * get_form_list();
      virtual bool _001IsPointInside(point64 pt);

      control null() { return control(); }
      bool Validate(string & str);
      bool get_data(sp(::user::interaction) pwnd, var & var);
      void SetEditItem(index iItem);
      void SetEditSubItem(index iItem);
      index GetEditSubItem();
      index GetEditItem();

      virtual ::user::interaction * ControlExGetWnd();

      using ::user::interaction::GetClientRect;
      using ::user::interaction::GetWindowRect;
      virtual bool GetClientRect(LPRECT lprect);
      virtual bool GetWindowRect(LPRECT lprect);


      bool operator == (const class ::user::control_descriptor & descriptor) const;
      bool operator == (const class control & control) const;


      virtual bool IsControlCommandEnabled();
      virtual void EnableControlCommand(bool bEnable);


      virtual void BaseControlExOnMouseMove(UINT nFlags, point point);

      virtual index hit_test(point point, e_element & eelement);

      DECL_GEN_SIGNAL(_001OnMouseMove);
      DECL_GEN_SIGNAL(_001OnMouseLeave);
      DECL_GEN_SIGNAL(_001OnKeyDown);


      virtual bool BaseOnControlEvent(::user::control_event * pevent);

      virtual bool simple_process_system_message(::message::message * pobj, ::user::e_event eevent);

      //virtual void walk_pre_translate_tree(::message::message * pobj,sp(::user::interaction) puiStop);

      virtual bool keyboard_focus_OnSetFocus();
      virtual bool keyboard_focus_OnKillFocus();

   };


   class control_cmd_ui : public ::user::command
   {
   public:
      
      
      id_to_id      m_mapControlCommand;


      control_cmd_ui();


      virtual void Enable(bool bOn);
      virtual void SetCheck(int32_t nCheck);
      virtual void SetText(const char * lpszText);
      id GetControlCommand(id id);

   };


   //class control_view_impl :
   //   virtual public ::object
   //{
   //public:

   //   control_view_impl();

   //   virtual LRESULT BaseControlExOnIdleUpdateCmdUI(WPARAM wParam, LPARAM);
   //   virtual void BaseControlExOnUpdateCmdUI(sp(::user::frame_window) pTarget, bool bDisableIfNoHndler);
   //   virtual bool BaseControlExOnCommand(WPARAM wParam, LPARAM lParam) ;
   //   virtual sp(::user::interaction) get_window();

   //   control_cmd_ui  m_commandui; // ::user::command derived class used to update
   //                                 // base_controlex derived controls
   //   list<oswindow, oswindow> m_listwndptrBlackList;
   //};



} // namespace user
