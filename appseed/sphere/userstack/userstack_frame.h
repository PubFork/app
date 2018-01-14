#pragma once


namespace userstack
{


   class CLASS_DECL_SPHERE frame :
      virtual public simple_frame_window,
      virtual public ::user::message_queue_listener
   {
   public:

      ::user::message_queue_sp   m_spqueue;


      image_list  *              m_pimagelist;
      sp(::user::document)                 m_pdocument;
      bool                       m_bHoverMouse;
      uint32_t                      m_dwLastHover;
      bool                       m_bTimerOn;

      bool                       m_bMouseOver;

      sp(view)                     m_pview;
      sp(pane_view)                m_ppaneview;


      frame(::aura::application * papp);
      virtual void install_message_routing(::message::sender * pinterface);

      DECL_GEN_SIGNAL(_001OnApp1);
      DECL_GEN_SIGNAL(_001OnMouseLeave);
      virtual void _000OnMouse(::message::mouse * pmouse);

      void OnHoverAction();

      virtual bool pre_create_window(::user::create_struct& cs);

      void ShowControlBars(bool bShow);

      virtual ~frame();
   
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   

      virtual void pre_translate_message(::message::message * pobj);

      DECL_GEN_SIGNAL(_001OnCreate);
      void _001OnTimer(::timer * ptimer);
      DECL_GEN_SIGNAL(_001OnApp2000);

      
      virtual void message_handler(::message::base * pbase);


      virtual void message_queue_message_handler(::message::message * pobj);


   };


} // namespace userstack


