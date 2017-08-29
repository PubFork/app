#pragma once


namespace prompt
{


   class CLASS_DECL_SPHERE frame : 
      virtual public simple_frame_window,
      virtual public ::user::message_queue_listener
   {
   public:

      ::user::message_queue_sp   m_spqueue;
      
      bool                       m_bAutoHideOnOutClick;
      int32_t                 m_iAnimateStep;
      sp(image_list)          m_pimagelist;
      bool                    m_bTimerHide;
      bool                    m_bTimerOn;
      e_position              m_eposition;
      bool                    m_bMoveDrag;
      bool                    m_bLControl;

	   frame(::aura::application * papp);
      virtual ~frame();

      virtual void install_message_routing(::message::sender * pinterface);

	   void ShowControlBars(bool bShow);
	  
   #ifdef DEBUG
	   virtual void assert_valid() const;
	   virtual void dump(dump_context & dumpcontext) const;
   #endif

      bool m_bHoverMouse;
      uint32_t m_dwLastHover;

      void OnHoverAction(bool bShowWinActionArea);
   
      void ToFront();

      virtual void on_simple_command(::user::command * pcommand);
      virtual void on_simple_command_probe(::user::command * pcommand);



	   DECL_GEN_SIGNAL(_001OnCreate);
	   void _001OnTimer(::timer * ptimer);

      DECL_GEN_SIGNAL(_001OnClose);
      DECL_GEN_SIGNAL(_001OnMove);
      DECL_GEN_SIGNAL(_001OnShowWindow);
      DECL_GEN_SIGNAL(_001OnApp2000);


      virtual void message_queue_message_handler(::message::message * pobj);
   };


} // namespace prompt


