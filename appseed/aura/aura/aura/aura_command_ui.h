#pragma once


namespace message
{





} // namespace message




// class CLASS_DECL_AURA ::user::command :
//    public ::message::base
// {
// public:


//    id                      m_id;
//    id                      m_idControl;     // menu item or other index

//    index                   m_iIndex;
//    ::count m_iCount;        // last + 1 for iterating m_iIndex

//    // if a menu item
//    ::user::menu *          m_pMenu;         // NULL if not a menu
//    ::user::menu *          m_pSubMenu;      // sub containing menu item
//    // if a popup sub menu - ID is for first in popup

//    // if from some other interaction_impl
//    ::user::primitive *     m_pOther;         // NULL if a menu or not a interaction_impl

//    bool                    m_bEnableChanged;
//    bool                    m_bContinueRouting;
//    bool                    m_bEnableIfHasCommandHandler;

//    ::user::menu *          m_pParentMenu;   // NULL if parent menu not easily determined
//    //  (probably a secondary popup menu)


//    ::user::command(::aura::application * papp);
//    ::user::command(class ::message::sender * psignal);


//    void reset(class ::message::sender * psignal);


//    // Operations to do in ON_UPDATE_::user::command
//    virtual void Enable(bool bOn = TRUE, ::action::context actioncontext = ::action::source_system);
//    virtual void _001SetCheck(bool bCheck, ::action::context = ::action::source_system);   // 0, 1 or 2 (indeterminate)
//    virtual void _001SetCheck(check::e_check echeck, ::action::context = ::action::source_system);   // 0, 1 or 2 (indeterminate)
//    virtual void SetRadio(bool bOn = TRUE, ::action::context actioncontext = ::action::source_system);
//    virtual void SetText(const char * lpszText, ::action::context actioncontext = ::action::source_system);

//    // Advanced operation
//    void ContinueRouting();


//    bool DoUpdate(command_target* pTarget, bool bDisableIfNoHndler);



// };






// ::user::command
//inline void ::user::command::ContinueRouting()
//{
//
//   m_bContinueRouting = TRUE;
//
//}

