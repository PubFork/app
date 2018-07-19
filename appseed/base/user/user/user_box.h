#pragma once


//#include "user_interaction_impl_base.h"
#include "user_scroll.h"
#include "base/user/simple_ui/simple_ui_interaction.h"


namespace user
{


   class CLASS_DECL_BASE box :
      virtual public scroll,
      virtual public ::simple_ui::interaction,
      virtual public ::database::client
   {
   public:


      string            m_strDisplay;
      ::database::key   m_datakeyWindowRect;

      box();
      virtual ~box();

      void install_message_routing(::message::sender * pinterface) override;

      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnSize);
      DECL_GEN_SIGNAL(_001OnShowWindow);

      virtual void _001WindowRestore() override;

      virtual string calc_display();
      virtual bool does_display_match();
      virtual void defer_update_display();

      virtual bool IsFullScreen();
      void WindowDataEnableSaveWindowRect(bool bEnable);
      bool WindowDataSaveWindowRect();
      bool WindowDataLoadWindowRect(bool bForceRestore = false, bool bInitialFramePosition = false);

      virtual bool LoadWindowRect_(class ::database::key id, sp(::user::box) pwindow, bool bForceRestore = false, bool bInitialFramePosition = false);
      virtual bool SaveWindowRect_(class ::database::key id, sp(::user::box) pwindow);


      virtual void on_simple_command(::message::simple_command * psimplecommand) override;
      virtual void on_command(::user::command * pcommand) override;


      virtual void on_set_parent(::user::interaction * puiParent) override;
      virtual bool on_before_set_parent(::user::interaction * pinterface) override;


      virtual bool parent_is_local_data();
      virtual bool is_local_data() override;


   };


} // namespace user





