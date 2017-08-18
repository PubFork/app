#pragma once


#include "base/user/user/user_control.h"


namespace user
{


   class menu_item;


   class CLASS_DECL_BASE menu :
      virtual public ::user::control
   {
   public:
      
      
      enum e_message
      {
         
         MessageDestroyWindow = WM_USER + 128
         
      };
      
      enum EChildId
      {
         ChildIdClose = 0x00800000
      };
      
      menu *                                 m_pmenuParent;
      sp(menu_item)                          m_pitem;
      ::user::interaction *                  m_puiParent;
      ::user::interaction *                  m_puiNotify;
      HMENU                                  m_hmenu;
      bool                                   m_bOwnItem;
      size                                   m_size;
      int32_t                                m_iItemHeight;
      int32_t                                m_iCheckBoxSize;
      bool                                   m_bAutoDelete;
      int32_t                                m_iHeaderHeight;
      ::user::menu_item                      m_itemClose;
      id                                     m_idSubMenu;
      int32_t                                m_iHoverSubMenu;
      uint32_t                               m_dwOut;
      sp(menu)                               m_psubmenu;
      id                                     m_idTimerMenu;
      point                                  m_ptTrack;
      point                                  m_ptPositionHint;
      int                                    m_iFlags;
      bool                                   m_bPositionHint;
      
      
      
      menu();
      menu(::aura::application * papp);
      menu(::aura::application * papp, ::user::menu_item * pitem);
      virtual ~menu();
      
      
      virtual int64_t add_ref()
      {
         
         return ::object::add_ref();
         
      }
      
      virtual int64_t dec_ref()
      {
         
         return ::object::dec_ref();
         
      }
      
      virtual ::user::interaction * get_target_window();
      
      ::user::menu_item * GetSubMenu(int32_t i);
      
      void layout_menu(point pt);
      
      virtual void hint_flags(int iFlags);
      virtual void hint_position(point pt);
      virtual void hints(int iFlags, point pt);
      
      virtual bool track_popup_menu(::user::interaction * puiParent, ::user::interaction * puiNotify = NULL);
      
      void _001OnTimer(::timer * ptimer);
      
      void _001OnDraw(::draw2d::graphics * pgraphics);
      
      DECL_GEN_SIGNAL(OnMessageDestroyWindow);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnDestroy);
      DECL_GEN_SIGNAL(_001OnIdleUpdateCmdUI);
      DECL_GEN_SIGNAL(_001OnNcActivate);
      DECL_GEN_SIGNAL(_001OnNcCalcSize);
      DECL_GEN_SIGNAL(_001OnEnable);
      DECL_GEN_SIGNAL(_001OnShowWindow);
      
      virtual bool BaseOnControlEvent(::user::control_event * pevent);
      
      bool pre_create_window(::user::create_struct& cs);
      
      virtual void install_message_handling(::message::dispatch * pinterface);
      
      sp(::user::menu_item) get_item();
      
      sp(::user::menu_item) get_item(::user::interaction * pui);
      
      virtual bool get_color(COLORREF & cr,::user::e_color ecolor);
      virtual bool get_translucency(::user::e_translucency & etranslucency, ::user::e_element eelement);
      virtual bool has_pending_graphical_update();
      
      virtual bool create_menu(const stringa & straCommand, const stringa & straCommandTitle);

      virtual bool load_menu(::xml::node * pnode);
      
      virtual bool load_xml_menu(const char * pszMatter);
      
      virtual void destroy_menu();
      
   };


} // namespace user



