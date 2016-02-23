#pragma once


namespace android
{
   
   
   class CLASS_DECL_AURA window_draw :
      virtual public ::user::window_draw,
      virtual public ::user::message_queue
   {
   public:
      

      bool                                   m_bRender;
      DWORD                                  m_dwLastRedrawRequest;
      DWORD                                  m_dwLastUpdate;
      DWORD                                  m_dwLastDelay;


      window_draw(::aura::application * papp);
      virtual ~window_draw();


      virtual void do_events();


      virtual void message_handler(signal_details * pobj);


      bool UpdateBuffer(const RECT & rect);

      virtual bool UpdateBuffer();

      virtual bool pre_run();
      virtual int32_t run();
      virtual bool finalize();

      virtual UINT RedrawProc();

      virtual void asynch_redraw();
      virtual void _asynch_redraw();
      virtual void synch_redraw();
      virtual void _synch_redraw();

   };
   

} // namespace android




