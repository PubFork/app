//
//  userex_view_container.hpp
//  app_veriwell_musical_player
//
//  Created by Camilo Sasuke Tsumanuma on 14/07/18.
//  Copyright © 2018 Camilo Sasuke Tsumanuma. All rights reserved.
//  at macOS High Sierra 10.13.6
//
#pragma once


namespace userex
{


   class CLASS_DECL_CORE view_update_hint :
      public ::object
   {
   public:


      enum e_type
      {

         type_none,
         type_attach_view,
         type_detach_view,

      };


      string         m_strView;
      e_type         m_etype;


      view_update_hint();
      virtual ~view_update_hint();

   };


   class CLASS_DECL_CORE view_container :
      virtual public ::user::impact,
      virtual public ::user::wndfrm::frame::WorkSetListener
   {
   public:


      ::size                                          m_sizeTabbedFrame;
      string_map < sp(::user::document) >    m_mapdoc;
      string_map < simple_frame_window * >   m_mapframe;


      sp(::user::single_document_template)      m_ptemplateTab;

      view_container(::aura::application * papp);
      virtual ~view_container();


      virtual void install_message_routing(::message::sender * psender) override;

      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;

      virtual void on_update(::user::impact * pSender, LPARAM lHint, ::object* pHint) override;


      virtual bool _001IsCompactMode();

      virtual void _001OnView(string strView);
      virtual sp(::user::impact) _001GetView(string strView);
      virtual sp(::user::impact) _001DetachView(string strView);
      virtual bool _001AttachView(string strView);
      virtual void _001DefaultLayoutView(string strView);
      virtual sp(::user::impact) get_view(string strView);
      virtual sp(::user::document) get_doc(string strView);
      virtual sp(::user::document) detach_doc(string strView);
      virtual bool attach(sp(::user::document) pdoc, string strView);

      virtual bool OnUpDownTargetAttach(::user::wndfrm::frame::WorkSetUpDownInterface * pupdown) override;
      virtual bool OnUpDownTargetDetach(::user::wndfrm::frame::WorkSetUpDownInterface * pupdown) override;
      virtual void tabfy(::user::wndfrm::frame::WorkSetUpDownInterface * pupdown);


      virtual void on_layout() override;


   };


} // namespace userex


