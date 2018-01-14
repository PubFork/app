#pragma once


namespace userex
{


   class CLASS_DECL_CORE wait_message_dialog :
      virtual public dialog
   {
   public:
      
      
      uint32_t          m_dwStartTime;
      uint32_t          m_dwDelay;
      string            m_strResponse;


      wait_message_dialog(::aura::application * papp);
      virtual ~wait_message_dialog();


      virtual void install_message_routing(::message::sender * psender) override;

      virtual void on_show(const char * pszMatter, property_set * propertyset) override;

      virtual bool BaseOnControlEvent(::user::control_event * pevent) override;

      virtual void _001OnTimer(::timer * ptimer) override;

      DECL_GEN_SIGNAL(_001OnCreate);

      virtual bool on_timeout_check();
      virtual bool on_timeout();
      virtual void on_timer_soft_reload(uint32_t dwTimeout);


   };


} // namespace userex


