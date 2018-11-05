#pragma once


namespace user
{


   class CLASS_DECL_AURA command:
      virtual public ::message::base
   {
   public:


      ::command_target *                           m_pcommandtargetSource;
      id                                           m_idControl;     // menu item or other index
      index                                        m_iIndex;
      ::count                                      m_iCount;        // last + 1 for iterating m_iIndex
      pointer_array < ::command_target * >         m_commandtargetptraHandle;

      bool                                         m_bEnable;
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

//      probe_::user::command();


      command(::aura::application * papp = NULL);
      command(id id);
      //command(::user::command * pcommand);

      void common_construct();

      bool handle(::command_target * pcommandtarget);
      bool is_handled(::command_target * pcommandtarget);



      //::user::command(::aura::application * papp);
      //::user::command(class ::message::sender * psignal);


      void reset(class ::message::sender * psignal);


      virtual void Enable(bool bOn = true,::action::context actioncontext = ::action::source_system);
      virtual void _001SetCheck(bool bCheck = true,::action::context = ::action::source_system);   // true or false
      virtual void _001SetCheck(check::e_check echeck,::action::context = ::action::source_system);   // 0, 1 or 2 (indeterminate)
      virtual void SetRadio(bool bOn = true,::action::context actioncontext = ::action::source_system);
      virtual void SetText(const char * lpszText,::action::context actioncontext = ::action::source_system);

      // Operations to do in ON_UPDATE_::user::command
      //virtual void Enable(bool bOn = TRUE, ::action::context actioncontext = ::action::source_system);
      //virtual void _001SetCheck(bool bCheck, ::action::context = ::action::source_system);   // 0, 1 or 2 (indeterminate)
      //virtual void _001SetCheck(check::e_check echeck, ::action::context = ::action::source_system);   // 0, 1 or 2 (indeterminate)
      //virtual void SetRadio(bool bOn = TRUE, ::action::context actioncontext = ::action::source_system);
      //virtual void SetText(const char * lpszText, ::action::context actioncontext = ::action::source_system);

      // Advanced operation
      //void ContinueRouting();


      void do_probe(command_target * ptarget);



      //};

   };


} // namespace aura

















