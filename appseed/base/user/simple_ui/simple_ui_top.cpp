
#include "framework.h"
//#include "base/user/user.h"




namespace simple_ui
{


   top::top(::aura::application * papp) :
      ::object(papp),
      ::simple_ui::style(papp)
   {

      m_bDrag = false;

   }


   top::~top()
   {

   }


   void top::install_message_routing(::message::sender * psender)
   {

      ::simple_ui::interaction::install_message_routing(psender);

      IGUI_MSG_LINK(WM_CREATE, psender, this, &top::_001OnCreate);
      IGUI_MSG_LINK(WM_LBUTTONDOWN,psender,this,&top::_001OnLButtonDown);
      IGUI_MSG_LINK(WM_LBUTTONUP,psender,this,&top::_001OnLButtonUp);
      IGUI_MSG_LINK(WM_MOUSEMOVE,psender,this,&top::_001OnMouseMove);

   }


   void top::_001OnCreate(::message::message * pobj)
   {

      SCAST_PTR(::message::create,pcreate,pobj);

      if(pcreate->previous())
         return;

      m_puserstyle = this;

   }


   void top::_001OnLButtonDown(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse,pmouse,pobj);

      if (pobj->previous())
         return;

      get_wnd()->show_keyboard(false);

      m_bLButtonDown = true;
      m_bDrag = false;

      m_ptLButtonDown = pmouse->m_pt;
      m_ptLButtonDownPos = m_ptLButtonDown;
      ScreenToClient(&m_ptLButtonDownPos);
      SetCapture();

      pmouse->m_bRet = true;

   }


   void top::_001OnLButtonUp(::message::message * pobj)
   {

      m_bLButtonDown = false;

      SCAST_PTR(::message::mouse,pmouse,pobj);

      if(pmouse->previous())
         return;

      ReleaseCapture();

      m_bDrag = false;

      pobj->m_bRet = true;

   }


   void top::_001OnMouseMove(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse,pmouse,pobj);

      if (m_bLButtonDown)
      {
         if (!m_bDrag)
         {
            m_bDrag = true;
            POINT ptNow = pmouse->m_pt;
            point pt;
            pt.x = ptNow.x - m_ptLButtonDownPos.x;
            pt.y = ptNow.y - m_ptLButtonDownPos.y;
            MoveWindow(pt);
            m_bDrag = false;
         }
         pobj->m_bRet = true;

      }
      else
      {
         if(pobj->previous())
            return;

         pobj->m_bRet = true;
      }

   }


} // namespace fontopus


