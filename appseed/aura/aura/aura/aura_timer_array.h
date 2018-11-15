#pragma once


namespace aura
{


   class CLASS_DECL_AURA timer_array:
      virtual public timer_callback
   {
   public:


      typedef map < uint_ptr,uint_ptr, sp(::timer), sp(::timer) > MAP;

      MAP                                    m_map;

      ::timer_callback *                     m_pcallback;


      timer_array(::aura::application * papp);
      virtual ~timer_array();



      virtual bool create_timer(uint_ptr nIDEvent, UINT nEllapse, PFN_TIMER pfnTimer, bool bPeriodic = true, void * pvoidData = NULL);
      virtual bool delete_timer(uint_ptr nIDEvent);

      virtual void safe_pre_term() override;
      virtual void delete_all_timers();

      virtual bool on_timer(::timer * ptimer) override;
      virtual void _001OnTimer(::timer * ptimer);


   };


} // namespace aura



