#pragma once


#include "aura/aura/os/windows/windows_comptr.h"

/*
class millis_timer
{

public:


   HANDLE hTimerQueue;
   HANDLE gDoneEvent;

   millis_timer()
   {

      // Use an event object to track the TimerRoutine execution
      gDoneEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
      if(NULL == gDoneEvent)
      {
         _throw(- 1);
      }
      // Create the timer queue.
      hTimerQueue = CreateTimerQueue();
      if(NULL == hTimerQueue)
      {
         _throw(- 1);
      }
   }

   ~millis_timer()
   {

      CloseHandle(gDoneEvent);

      // Delete all timers in the timer queue.
      DeleteTimerQueue(hTimerQueue);


   }


   static VOID CALLBACK TimerRoutine(PVOID lpParam,BOOLEAN TimerOrWaitFired)
   {
      millis_timer * ptimer = (millis_timer *)lpParam;

      SetEvent(ptimer->gDoneEvent);

      ptimer->on_millis_timer_step();
   }

   bool wait(int millis)
   {

      ::ResetEvent(gDoneEvent);

      HANDLE hTimer = NULL;

      // Set a timer to call the timer routine in 10 seconds.
      if(!CreateTimerQueueTimer(&hTimer,hTimerQueue,(WAITORTIMERCALLBACK)TimerRoutine,this,millis,0,0))
      {
         return false;
      }

      if(WaitForSingleObject(gDoneEvent,INFINITE) != WAIT_OBJECT_0)
         return false;

      //      DeleteTimerQueue(hTimer);

      return true;
   }
   bool timer(int millis)
   {

      ::ResetEvent(gDoneEvent);

      HANDLE hTimer = NULL;

      // Set a timer to call the timer routine in 10 seconds.
      if(!CreateTimerQueueTimer(&hTimer,hTimerQueue,(WAITORTIMERCALLBACK)TimerRoutine,this,millis,millis,0))
      {
         return false;
      }

      if(WaitForSingleObject(gDoneEvent,INFINITE) != WAIT_OBJECT_0)
         return false;

      //      DeleteTimerQueue(hTimer);

      return true;
   }

   virtual void on_millis_timer_step()
   {
   }

};

*/

namespace multimedia
{


   namespace audio_xaudio
   {


      class  CLASS_DECL_AUDIO_XAUDIO wave_out :
         virtual public ::multimedia::audio::wave_out,
         virtual public IXAudio2VoiceCallback
      {
      public:


         ::thread  * m_pthreadFree;
         //HANDLE streamEndEventHandle;
         //VoiceCallback(): streamEndEventHandle(CreateEvent(NULL,FALSE,FALSE,NULL)){}
         //~VoiceCallback()
         //{
         //CloseHandle(streamEndEventHandle);
         //}

         // Called when the voice has just finished playing a contiguous audio stream.
         STDMETHOD_(void,OnStreamEnd());

         // Unused methods in this application
         STDMETHOD_(void,OnVoiceProcessingPassEnd());
         STDMETHOD_(void,OnVoiceProcessingPassStart(UINT32 SamplesRequired)) ;
         STDMETHOD_(void,OnBufferEnd(void * pBufferContext))  ;
         STDMETHOD_(void,OnBufferStart(void * pBufferContext));
         STDMETHOD_(void,OnLoopEnd(void * pBufferContext));
         STDMETHOD_(void,OnVoiceError(void * pBufferContext,HRESULT Error));

         ::windows::comptr<IXAudio2>                        m_pxaudio;
         IXAudio2MasteringVoice *                           m_pvoice;
         IXAudio2SourceVoice *                              m_psourcevoice;

//         run_step_thread *                m_prunstepthread;

         int                              m_iBuffer;

         WAVEFORMATEX                     m_waveformatex;



         wave_out(::aura::application * papp);
         virtual ~wave_out();


         virtual void wave_out_launch_buffers() override;
         void install_message_routing(::message::sender * pinterface);

         virtual imedia_time wave_out_get_position_millis() override;
         virtual imedia_position wave_out_get_position() override;
         virtual void wave_out_buffer_ready(index iBuffer) override;

         virtual ::multimedia::e_result wave_out_open_ex(::thread * pthreadCallback, ::count iBufferSampleCount, uint32_t uiSamplesPerSec, uint32_t uiChannelCount, uint32_t uiBitsPerSample,::multimedia::audio::e_purpose epurpose) override;
         virtual ::multimedia::e_result wave_out_stop() override;
         virtual ::multimedia::e_result wave_out_close() override;
         virtual ::multimedia::e_result wave_out_pause() override;
         virtual ::multimedia::e_result wave_out_restart() override;
         virtual void * get_os_data();

         virtual void wave_out_on_playback_end() override;
         virtual void wave_out_free(index iBuffer) override;

         virtual bool init_thread() override;

         ::count wave_out_get_buffered_buffer_count() override;


         WAVEFORMATEX * wave_format();
         virtual void wave_out_prebuffer_eof() override;


      };


   } // namespace audio_xaudio


} // namespace multimedia



