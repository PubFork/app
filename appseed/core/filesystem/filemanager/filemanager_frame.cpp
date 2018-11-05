#include "framework.h"


namespace filemanager
{


   frame::frame(::aura::application * papp) :
      object(papp),
      simple_frame_window(papp)
   {



   }


   frame::~frame()
   {

   }


   void  frame::_001OnCreate(::message::message * pobj)
   {

      pobj->previous();

   }


   bool  frame::on_create_bars()
   {

      return simple_frame_window::on_create_bars();

   }


   void  frame::install_message_routing(::message::sender * pinterface)
   {

      simple_frame_window::install_message_routing(pinterface);

      IGUI_MSG_LINK(WM_SETTEXT, pinterface, this, &frame::_001OnSetText);

      IGUI_MSG_LINK(WM_CREATE, pinterface, this, &frame::_001OnCreate);

   }


   void  frame::_001OnSetText(::message::message * pobj)
   {
      //   SCAST_PTR(::message::base, pbase, pobj);

      pobj->previous();

      string str;

      ::filemanager::tab_view * ptabview = GetTypedParent < ::filemanager::tab_view >();
      if (ptabview != NULL)
      {
         get_window_text(str);
         ptabview->SetTitleById(m_idTab, str);
      }

   }



} // namespace filemanager




