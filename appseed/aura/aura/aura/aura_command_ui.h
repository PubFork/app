#pragma once


namespace message
{


   class CLASS_DECL_AURA base :
      public signal_details
   {
   public:


      sp(::user::primitive)      m_pwnd;
      bool                       m_bConditional;
      bool                       m_bReflect;
      bool                       m_bDestroyed;
      bool                       m_bDoSystemDefault;
      LRESULT *                  m_plresult;
      LRESULT                    m_lresult;


      base(class ::signal * psignal);
      base(::aura::application * papp, class ::signal * psignal = NULL);
      base(::aura::application * papp, ::user::primitive * pwnd, UINT uiMessage, WPARAM wparam, ::lparam lparam, LRESULT & lresult);
      base(const base & base);
      virtual ~base();



      virtual void set_lresult(LRESULT lresult);
      virtual LRESULT & get_lresult();
      virtual void set(::user::primitive * pwnd, UINT uiMessage, WPARAM wparam, ::lparam lparam, LRESULT & lresult);
      virtual void set(::user::primitive * pwnd, UINT uiMessage, WPARAM wparam, ::lparam lparam);

      base & operator = (const base & base);

      void copy_this(const base & base);

   };



} // namespace message




class CLASS_DECL_AURA command_ui :
   public ::message::base
{
public:


   id                      m_id;
   id                      m_idControl;     // menu item or other index

   index                   m_iIndex;
   ::count m_iCount;        // last + 1 for iterating m_iIndex

   // if a menu item
   ::user::menu *          m_pMenu;         // NULL if not a menu
   ::user::menu *          m_pSubMenu;      // sub containing menu item
   // if a popup sub menu - ID is for first in popup

   // if from some other interaction_impl
   ::user::primitive *     m_pOther;         // NULL if a menu or not a interaction_impl

   bool                    m_bEnableChanged;
   bool                    m_bContinueRouting;
   bool                    m_bEnableIfHasCommandHandler;

   ::user::menu *          m_pParentMenu;   // NULL if parent menu not easily determined
   //  (probably a secondary popup menu)


   command_ui(::aura::application * papp);
   command_ui(class ::signal * psignal);


   void reset(class ::signal * psignal);


   // Operations to do in ON_UPDATE_COMMAND_UI
   virtual void Enable(bool bOn = TRUE, ::action::context actioncontext = ::action::source_system);
   virtual void _001SetCheck(bool bCheck, ::action::context = ::action::source_system);   // 0, 1 or 2 (indeterminate)
   virtual void _001SetCheck(check::e_check echeck, ::action::context = ::action::source_system);   // 0, 1 or 2 (indeterminate)
   virtual void SetRadio(bool bOn = TRUE, ::action::context actioncontext = ::action::source_system);
   virtual void SetText(const char * lpszText, ::action::context actioncontext = ::action::source_system);

   // Advanced operation
   void ContinueRouting();


   bool DoUpdate(command_target* pTarget, bool bDisableIfNoHndler);



};






// command_ui
inline void command_ui::ContinueRouting()
{

   m_bContinueRouting = TRUE;

}

