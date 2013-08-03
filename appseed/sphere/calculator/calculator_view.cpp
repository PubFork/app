﻿#include "framework.h"


namespace calculator
{


   view::view(sp(::ca2::application) papp) :
      ca2(papp),
      ::user::interaction(papp)
   {

   }


   view::~view()
   {

   }


   void view::install_message_handling(::ca2::message::dispatch * pinterface)
   {

      ::user::view::install_message_handling(pinterface);

      IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &view::_001OnDestroy);
      IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &view::_001OnSize);
      IGUI_WIN_MSG_LINK(WM_PAINT, pinterface, this, &view::_001OnPaint);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &view::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &view::_001OnContextMenu);
      IGUI_WIN_MSG_LINK(WM_SETCURSOR, pinterface, this, &view::_001OnSetCursor);

      //   IGUI_WIN_MSG_LINK(WM_USER + 177     , this, this, &view::_001OnTabClick);
      IGUI_WIN_MSG_LINK(WM_APP + 119      , this, this, &view::_001OnWavePlayerEvent);
      //connect_command(ID_FILE_PRINT, ::user::view::OnFilePrint)
      //connect_command(ID_FILE_PRINT_DIRECT, ::user::view::OnFilePrint)
      //connect_command(ID_FILE_PRINT_PREVIEW, ::user::view::OnFilePrintPreview)
      //  IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &::user::interaction::_001OnLButtonDown);
      //   IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &::user::interaction::_001OnLButtonUp);
      IGUI_WIN_MSG_LINK(WM_KEYDOWN, pinterface, this, &::user::interaction::_001OnKeyDown);
      IGUI_WIN_MSG_LINK(WM_KEYUP, pinterface, this, &::user::interaction::_001OnKeyUp);


   }

#ifdef DEBUG
   void view::assert_valid() const
   {
      ::user::view::assert_valid();
   }

   void view::dump(dump_context & dumpcontext) const
   {
      ::user::view::dump(dumpcontext);
   }
#endif //DEBUG

   /////////////////////////////////////////////////////////////////////////////
   // view message handlers

   // vmpLightView.cpp : implementation of the view class
   //


   /////////////////////////////////////////////////////////////////////////////
   // view


   bool view::pre_create_window(CREATESTRUCT& cs)
   {

      cs.style &= ~WS_EX_CLIENTEDGE;

      return ::user::view::pre_create_window(cs);

   }


   void view::_001OnInitialUpdate(::ca2::signal_object * pobj)
   {
      ::user::view::_001OnInitialUpdate(pobj);


   }

   sp(::user::interaction) view::get_guie()
   {
      return this;
   }

   void view::on_update(sp(::user::view) pSender, LPARAM lHint, ::ca2::object* phint)
   {
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(lHint);
      UNREFERENCED_PARAMETER(phint);
   }

   sp(::user::interaction) view::BackViewGetWnd()
   {
      return this;
   }
   void view::_001OnDestroy(::ca2::signal_object * pobj)
   {
      ::user::view::_001OnDestroy(pobj);

   }



   void view::_001OnSize(::ca2::signal_object * pobj)
   {
      
      UNREFERENCED_PARAMETER(pobj);

   }

   void view::_001OnPaint(::ca2::signal_object * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

   }


   void view:: _001OnDraw(::draw2d::graphics * pdc)
   {
      UNREFERENCED_PARAMETER(pdc);
   }

   void view::_001OnCreate(::ca2::signal_object * pobj)
   {
      if(pobj->previous())
         return;


   }
   void view::_001OnContextMenu(::ca2::signal_object * pobj)
   {
//      SCAST_PTR(::ca2::message::context_menu, pcontextmenu, pobj)
//         point point = pcontextmenu->GetPoint();

   }


   void view::_001OnTabClick(int32_t iTab)
   {
      if(iTab == 1)
      {
         System.simple_message_box(NULL, "Playlist");
      }
   }

   void view::_001OnWavePlayerEvent(::ca2::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      //SCAST_PTR(::ca2::message::base, pbase, pobj)
   }

   void view::_001OnUpdateViewEncoding(::ca2::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      //SCAST_PTR(::ca2::message::update_cmd_ui, pupdatecmdui, pobj)
   }
   void view::_001OnViewEncoding(::ca2::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      //SCAST_PTR(::ca2::message::command, pcommand, pobj)
   }


   /*xxxvoid view::data_on_after_change(int32_t iConfigurationId, ::database::id & idIndex CVmsDataUpdateHint * puh)
   {
   if(iConfigurationId == _vmsp::CConfiguration::CfgKaraokeEncoding)
   {
   PrepareLyricLines();
   RedrawWindow();
   }
   }*/


   void view::_001OnSetCursor(::ca2::signal_object * pobj)
   {

      SCAST_PTR(::ca2::message::mouse, pmouse, pobj)

      pmouse->m_ecursor = ::visual::cursor_arrow;

   }


   sp(::user::document) view::get_document()
   {

      return  (::user::view::get_document());

   }


} // namespace calculator




