#pragma once


class command_target_interface;


namespace user
{


   class CLASS_DECL_AURA command:
      public ::message::base
   {
   public:


      ::command_target_interface *                 m_pcommandtargetSource;
      ::command_ui  *                              m_pcommandui;
      id                                           m_id;
      id                                           m_idControl;     // menu item or other index
      index                                        m_iIndex;
      ::count                                      m_iCount;        // last + 1 for iterating m_iIndex
      ref_array < ::command_target >               m_commandtargetptraHandle;

      bool                                         m_bEnabled;
      check::e_check                               m_echeck; // m_bCheckChanged is similar to m_echeck != undefined
      string                                       m_strText;
      bool                                         m_bRadio;
      bool                                         m_bRadioChanged;
   
      // if a menu item
      ::user::menu *                               m_pmenu;         // NULL if not a menu
      ::user::menu *                               m_pmenuChild;      // sub containing menu item
      ::user::menu *                               m_pmenuParent;   // NULL if parent menu not easily determined
      // if a popup sub menu - ID is for first in popup
   
      // if from some other interaction_impl
      ::user::primitive *                          m_puiOther;         // NULL if a menu or not a interaction_impl
   
      bool                                         m_bEnableChanged;
      bool                                         m_bHasCommandHandler;
      //bool                     m_bContinueRouting;
      ///bool                    m_bEnableIfHasCommandHandler;
   
      //  (probably a secondary popup menu)
   
//      probe_command_ui();
   
   
      command(::aura::application * papp);
      command(signal * psignal);
      command(id id);
      command(::command_ui * pcommandui);

      void common_construct();

      bool handle(::command_target * pcommandtarget);
      bool is_handled(::command_target * pcommandtarget);

   
   
      //command_ui(::aura::application * papp);
      //command_ui(class ::message::sender * psignal);
   
   
      void reset(class ::message::sender * psignal);
   
   
      virtual void Enable(bool bOn = true,::action::context actioncontext = ::action::source_system);
      virtual void _001SetCheck(bool bCheck = true,::action::context = ::action::source_system);   // true or false
      virtual void _001SetCheck(check::e_check echeck,::action::context = ::action::source_system);   // 0, 1 or 2 (indeterminate)
      virtual void SetRadio(bool bOn = true,::action::context actioncontext = ::action::source_system);
      virtual void SetText(const char * lpszText,::action::context actioncontext = ::action::source_system);
   
      // Operations to do in ON_UPDATE_COMMAND_UI
      //virtual void Enable(bool bOn = TRUE, ::action::context actioncontext = ::action::source_system);
      //virtual void _001SetCheck(bool bCheck, ::action::context = ::action::source_system);   // 0, 1 or 2 (indeterminate)
      //virtual void _001SetCheck(check::e_check echeck, ::action::context = ::action::source_system);   // 0, 1 or 2 (indeterminate)
      //virtual void SetRadio(bool bOn = TRUE, ::action::context actioncontext = ::action::source_system);
      //virtual void SetText(const char * lpszText, ::action::context actioncontext = ::action::source_system);
   
      // Advanced operation
      //void ContinueRouting();
   
   
      bool DoUpdate(command_target* pTarget, bool bDisableIfNoHndler);
   
   
   
   //};
   
   };


} // namespace aura

















