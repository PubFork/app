#include "framework.h"


namespace calculator
{


   view::view(::aura::application * papp) :
      ::object(papp),
      ::user::interaction(papp)
   {

   }


   view::~view()
   {

   }


   void view::install_message_routing(::message::sender * pinterface)
   {

      ::user::impact::install_message_routing(pinterface);

      IGUI_MSG_LINK(WM_DESTROY, pinterface, this, &view::_001OnDestroy);
      IGUI_MSG_LINK(WM_SIZE, pinterface, this, &view::_001OnSize);
      IGUI_MSG_LINK(WM_PAINT, pinterface, this, &view::_001OnPaint);
      IGUI_MSG_LINK(WM_CREATE, pinterface, this, &view::_001OnCreate);
      IGUI_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &view::_001OnContextMenu);
      IGUI_MSG_LINK(WM_SETCURSOR, pinterface, this, &view::_001OnSetCursor);

      //   IGUI_MSG_LINK(WM_USER + 177     , this, this, &view::_001OnTabClick);
      IGUI_MSG_LINK(WM_APP + 119      , this, this, &view::_001OnWavePlayerEvent);
      //connect_command(ID_FILE_PRINT, ::user::impact::OnFilePrint)
      //connect_command(ID_FILE_PRINT_DIRECT, ::user::impact::OnFilePrint)
      //connect_command(ID_FILE_PRINT_PREVIEW, ::user::impact::OnFilePrintPreview)
      //IGUI_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &::user::interaction::_001OnLButtonDown);
      //IGUI_MSG_LINK(WM_LBUTTONUP, pinterface, this, &::user::interaction::_001OnLButtonUp);
      //IGUI_MSG_LINK(WM_KEYDOWN, pinterface, this, &::user::interaction::_001OnKeyDown);
      //IGUI_MSG_LINK(WM_KEYUP, pinterface, this, &::user::interaction::_001OnKeyUp);


   }


   void view::assert_valid() const
   {
      ::user::impact::assert_valid();
   }

   void view::dump(dump_context & dumpcontext) const
   {
      ::user::impact::dump(dumpcontext);
   }


   /////////////////////////////////////////////////////////////////////////////
   // view message handlers

   // vmpLightView.cpp : implementation of the view class
   //


   /////////////////////////////////////////////////////////////////////////////
   // view


   bool view::pre_create_window(::user::create_struct& cs)
   {

      cs.style &= ~WS_EX_CLIENTEDGE;

      return ::user::impact::pre_create_window(cs);

   }


   void view::_001OnInitialUpdate()
   {
      ::user::impact::_001OnInitialUpdate();


   }

   void view::on_update(::user::impact * pSender, LPARAM lHint, ::object* phint)
   {
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(lHint);
      UNREFERENCED_PARAMETER(phint);
   }

   sp(::user::interaction) view::BackViewGetWnd()
   {
      return this;
   }
   void view::_001OnDestroy(::message::message * pobj)
   {
      ::user::impact::_001OnDestroy(pobj);

   }



   void view::_001OnSize(::message::message * pobj)
   {
      
      UNREFERENCED_PARAMETER(pobj);

   }

   void view::_001OnPaint(::message::message * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

   }


   void view:: _001OnDraw(::draw2d::graphics * pgraphics)
   {
      
      UNREFERENCED_PARAMETER(pgraphics);

   }


   void view::_001OnCreate(::message::message * pobj)
   {
      if(pobj->previous())
         return;


   }
   void view::_001OnContextMenu(::message::message * pobj)
   {
//      SCAST_PTR(::message::context_menu, pcontextmenu, pobj);
//         point point = pcontextmenu->GetPoint();

   }


   void view::_001OnTabClick(int32_t iTab)
   {
      if(iTab == 1)
      {
         System.simple_message_box(NULL, "Playlist");
      }
   }

   void view::_001OnWavePlayerEvent(::message::message * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      //SCAST_PTR(::message::base, pbase, pobj);
   }

   void view::_001OnUpdateViewEncoding(::message::message * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      //SCAST_PTR(::user::command, pcommand, pobj);
   }
   void view::_001OnViewEncoding(::message::message * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      //SCAST_PTR(::message::command, pcommand, pobj);
   }



   void view::_001OnSetCursor(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      pmouse->m_ecursor = ::visual::cursor_arrow;

   }


   ::user::document * view::get_document()
   {

      return  (::user::impact::get_document());

   }


} // namespace calculator








