#include "framework.h"
#include "aura/aura/os/os.h"


namespace multimedia
{


   namespace audio_xaudio
   {


      wave_out::wave_out(::aura::application * papp) :
         ::object(papp),
         ::thread(papp),
         wave_base(papp),
         ::multimedia::audio::wave_out(papp)
      {

         m_pthreadFree        = NULL;
         m_estate             = state_initial;
         m_pthreadCallback    = NULL;
         m_iBufferedCount     = 0;
         m_peffect            = NULL;

      }

      wave_out::~wave_out()
      {

      }

      void wave_out::install_message_routing(::message::sender * pinterface)
      {

         ::multimedia::audio::wave_out::install_message_routing(pinterface);

      }


      bool wave_out::init_thread()
      {

         if(!::multimedia::audio::wave_out::init_thread())
            return false;

         set_thread_priority(::multithreading::priority_time_critical);

         return true;

      }


      ::multimedia::e_result wave_out::wave_out_open_ex(thread * pthreadCallback, ::count iBufferSampleCount, uint32_t uiSamplesPerSec, uint32_t uiChannelCount, uint32_t uiBitsPerSample, ::multimedia::audio::e_purpose epurpose)
      {

         single_lock sLock(m_pmutex, TRUE);

         if(m_pxaudio.is_set() && m_pvoice != NULL && m_psourcevoice != NULL && m_estate != state_initial)
            return ::multimedia::result_success;

         m_iBuffer = 0;

         m_pthreadCallback = pthreadCallback;
         ::multimedia::e_result mmr;
         ASSERT(m_pxaudio.is_null());
         ASSERT(m_pvoice == NULL);
         ASSERT(m_psourcevoice == NULL);
         ASSERT(m_estate == state_initial);

         defer_co_initialize_ex(true);

         if (m_pthreadFree == NULL)
         {

            m_pthreadFree = fork([this]()
            {

               ::get_thread()->set_thread_priority(::multithreading::priority_time_critical);

               MESSAGE msg;

               while (::GetMessage(&msg, NULL, 0, 0))
               {

                  if (msg.message == message_free)
                  {

                     if (m_pprebuffer->m_bPlay)
                     {

                        wave_out_buffer_ready(msg.wParam);

                     }
                     else
                     {

                        m_iBufferedCount--;

                        output_debug_string("message_free and not playing");

                        if (m_iBufferedCount <= 0)
                        {

                           wave_out_on_playback_end();

                        }

                     }

                  }

               }

               output_debug_string("quit");

            });

         }


         // by (indirect casey)
         if(FAILED(XAudio2Create(&m_pxaudio,0,XAUDIO2_DEFAULT_PROCESSOR)))
         {

            return ::multimedia::result_error;

         }

#if (_WIN32_WINNT >= 0x0602 /*_WIN32_WINNT_WIN8*/) && defined(_DEBUG)
         // To see the trace output, you need to view ETW logs for this application:
         //    Go to Control Panel, Administrative Tools, Event Viewer.
         //    View->Show Analytic and Debug Logs.
         //    Applications and Services Logs / Microsoft / Windows / XAudio2.
         //    Right click on Microsoft Windows XAudio2 debug logging, Properties, then Enable Logging, and hit OK
         XAUDIO2_DEBUG_CONFIGURATION debug = {0};
         debug.TraceMask = XAUDIO2_LOG_ERRORS | XAUDIO2_LOG_WARNINGS;
         debug.BreakMask = XAUDIO2_LOG_ERRORS;
         m_pxaudio->SetDebugConfiguration(&debug,0);
#endif


         HRESULT hr;

         if(FAILED(hr = m_pxaudio->CreateMasteringVoice(&m_pvoice,uiChannelCount, uiSamplesPerSec)))
         {
            return ::multimedia::result_error;
         }
         int iSampleRate = XAUDIO2_MIN_SAMPLE_RATE;
         mmr = ::multimedia::result_success;
         m_pwaveformat->wFormatTag = WAVE_FORMAT_PCM;
         m_pwaveformat->nChannels = uiChannelCount;
         m_pwaveformat->nSamplesPerSec = uiSamplesPerSec;
         m_pwaveformat->wBitsPerSample = sizeof(::multimedia::audio::WAVEBUFFERDATA) * 8 ;
         m_pwaveformat->nBlockAlign = m_pwaveformat->wBitsPerSample  * uiChannelCount / 8;
         m_pwaveformat->nAvgBytesPerSec = m_pwaveformat->nSamplesPerSec * m_pwaveformat->nBlockAlign;
         m_pwaveformat->cbSize = 0;
         sp(::multimedia::audio::wave) audiowave = Application.audiowave();

         //if(FAILED(hr = m_pxaudio->CreateSourceVoice(&m_psourcevoice,wave_format(),XAUDIO2_VOICE_NOSRC | XAUDIO2_VOICE_NOPITCH,1.0f,this)))
         if(FAILED(hr = m_pxaudio->CreateSourceVoice(&m_psourcevoice,wave_format(),0,1.0f,this)))
         {
            return ::multimedia::result_error;
         }

         if(mmr != ::multimedia::result_success)
         {

            TRACE(::multimedia::strerror(mmr));

            return mmr;

         }
         ::count iBufferCount;

         if(epurpose == ::multimedia::audio::purpose_playback)
         {

            iBufferCount = 8;
            iBufferSampleCount = m_pwaveformat->nSamplesPerSec / 20;

         }
         else if(epurpose == ::multimedia::audio::purpose_playground)
         {

            iBufferCount = 4;
            iBufferSampleCount = m_pwaveformat->nSamplesPerSec / 40;

         }
         else
         {

            iBufferCount = 4;
            iBufferSampleCount = m_pwaveformat->nSamplesPerSec / 40;

         }
         
         int iAlign = 2048;

         int iFrameBufferSize = m_pwaveformat->nChannels * 2;

         auto uiBufferSize = iBufferSampleCount * iFrameBufferSize;

         uiBufferSize += 2048;

         uiBufferSize = uiBufferSize / 2048 * 2048;

         ASSERT((uiBufferSize % 2048) == 0);// Streaming size must be 2K aligned to use for async I/O

         iBufferSampleCount = uiBufferSize / iFrameBufferSize;

         wave_out_get_buffer()->PCMOutOpen(this, uiBufferSize, iBufferCount,iAlign, m_pwaveformat, m_pwaveformat);

         m_pprebuffer->open(this, m_pwaveformat->nChannels, iBufferCount, iBufferSampleCount);

         m_estate = state_opened;

         m_epurpose = epurpose;

         return ::multimedia::result_success;

      }


      ::multimedia::e_result wave_out::wave_out_close()
      {

         single_lock sLock(m_pmutex, TRUE);

         if(m_estate == state_playing)
         {

            wave_out_stop();

         }

         if (m_estate != state_opened)
         {

            return ::multimedia::result_success;

         }

         ::multimedia::e_result mmr;

         auto iSize =  wave_out_get_buffer()->GetBufferCount();

         mmr = xaudio::translate(m_psourcevoice->Stop());

         try
         {

            m_psourcevoice->DestroyVoice();

         }
         catch(...)
         {

         }

         m_psourcevoice = NULL;

         try
         {


            if(m_pvoice != NULL)
            {

               m_pvoice->DestroyVoice();

            }
         }
         catch (...)
         {

         }

         m_pvoice = NULL;

         try
         {


            if(m_pxaudio.is_set())
            {

               m_pxaudio->StopEngine();

            }

         }
         catch (...)
         {

         }

         m_pxaudio.Release();

         ::multimedia::audio::wave_out::wave_out_close();

         return ::multimedia::result_success;

      }


      /*
      * Find the first occurrence of the byte string s in byte string l.
      */

      void *
      memmem(const void *l,size_t l_len,const void *s,size_t s_len)
      {
         register char *cur,*last;
         const char *cl = (const char *)l;
         const char *cs = (const char *)s;

         /* we need something to compare */
         if(l_len == 0 || s_len == 0)
            return NULL;

         /* "s" must be smaller or equal to "l" */
         if(l_len < s_len)
            return NULL;

         /* special case where s_len == 1 */
         if(s_len == 1)
            return memchr((void *) l,(int)*cs,l_len);

         /* the last position where its possible to find "s" in "l" */
         last = (char *)cl + l_len - s_len;

         for (cur = (char *)cl; cur <= last; cur++)
         {

            if (cur[0] == cs[0] && memcmp(cur, cs, s_len) == 0)
            {

               return cur;

            }

         }

         return NULL;

      }


      void wave_out::wave_out_buffer_ready(index iBuffer)
      {

         synch_lock sl(m_pmutex);

         if (wave_out_get_state() != state_playing)
         {
            TRACE("ERROR wave_out::BufferReady while wave_out_get_state() != state_playing");
            return;
         }


         ::multimedia::audio::wave_buffer * pwbuffer = wave_out_get_buffer();

         ::multimedia::audio::wave_buffer::buffer * pbuffer = pwbuffer->get_buffer(iBuffer);

         ::multimedia::e_result mmr;

         XAUDIO2_BUFFER b;

         ZERO(b);

         b.pContext = pbuffer;
         b.AudioBytes = (UINT32)(pwbuffer->m_uiBufferSize);
         b.pAudioData = (const BYTE *)pbuffer->m_pData;
         b.Flags = m_bEOS ? XAUDIO2_END_OF_STREAM : 0;

         m_pprebuffer->read_buffer((void *) b.pAudioData, b.AudioBytes, iBuffer);

#if 0

         char sz[256];

         ZERO(sz);

         if(memmem(b.pAudioData,pwbuffer->m_uiBufferSize,sz,sizeof(sz)))
         {

            output_debug_string("too much zeros in audio buffer\n");

         }

#endif

         static DWORD g_dwLastBuffer;

         DWORD dwTick = get_tick_count();

         if(dwTick-g_dwLastBuffer > 50)
         {

            output_debug_string("too much delay for submitting audio buffer\n");

         }

         g_dwLastBuffer = dwTick;

         HRESULT hresult = m_psourcevoice->SubmitSourceBuffer(&b);

         mmr = xaudio::translate(hresult);

         VERIFY(::multimedia::result_success == mmr);

         if (mmr != ::multimedia::result_success)
         {

            m_iBufferedCount--;

            throw resource_exception(get_app());

         }

      }


      ::multimedia::e_result wave_out::wave_out_stop()
      {

         single_lock sLock(m_pmutex, TRUE);

         if (m_estate != state_playing && m_estate != state_paused)
         {

            return ::multimedia::result_error;

         }

         m_eventStopped.ResetEvent();

         m_pprebuffer->stop();

         m_estate = state_stopping;

         m_mmr = xaudio::translate(m_psourcevoice->Stop());

         if(m_mmr == ::multimedia::result_success)
         {

            m_estate = state_opened;

         }

         return m_mmr;

      }


      ::multimedia::e_result wave_out::wave_out_pause()
      {

         single_lock sLock(m_pmutex, TRUE);

         ASSERT(m_estate == state_playing);

         if (m_estate != state_playing)
         {

            return ::multimedia::result_error;

         }

         m_mmr = xaudio::translate(m_psourcevoice->Stop());

         ASSERT(m_mmr == ::multimedia::result_success);

         if(m_mmr == ::multimedia::result_success)
         {

            m_estate = state_paused;

         }

         return m_mmr;

      }

      void wave_out::wave_out_launch_buffers()
      {

         m_iBufferedCount = wave_out_get_buffer()->GetBufferCount();

         for (int iReady = 0; iReady < m_iBufferedCount; iReady++)
         {

            wave_out_buffer_ready(iReady);

         }

         HRESULT hresult = m_psourcevoice->Start(0, XAUDIO2_COMMIT_NOW);

         m_mmr = xaudio::translate(hresult);

      }


      ::multimedia::e_result wave_out::wave_out_restart()
      {

         single_lock sLock(m_pmutex, TRUE);

         ASSERT(m_estate == state_paused);

         if (m_estate != state_paused)
         {

            return ::multimedia::result_error;

         }

         m_mmr = xaudio::translate(m_psourcevoice->Start(0,XAUDIO2_COMMIT_NOW));

         ASSERT(m_mmr == ::multimedia::result_success);

         if(m_mmr == ::multimedia::result_success)
         {

            m_estate = state_playing;

         }

         return m_mmr;

      }


      imedia_time wave_out::wave_out_get_position_millis()
      {

         single_lock sLock(m_pmutex, TRUE);

         if (m_psourcevoice == NULL)
         {

            return 0;

         }

         XAUDIO2_VOICE_STATE s;

         m_psourcevoice->GetState(&s);

         int64_t i = s.SamplesPlayed;
            
         i *= 1000;

         i /= m_pwaveformat->nSamplesPerSec;

         return i;

      }

      
      imedia_position wave_out::wave_out_get_position()
      {

         single_lock sLock(m_pmutex, TRUE);

         if (m_psourcevoice == NULL)
         {

            return 0;

         }
          
         XAUDIO2_VOICE_STATE s;

         m_psourcevoice->GetState(&s);

         return s.SamplesPlayed;

      }


      void wave_out::wave_out_free(index iBuffer)
      {

         ::multimedia::audio::wave_out::wave_out_free(iBuffer);

      }


      void wave_out::wave_out_on_playback_end()
      {

         wave_out_stop();

         if(m_pprebuffer->m_pstreameffectOut != NULL)
         {
            
            ::multimedia::iaudio::wave_stream_effect * peffect = m_pprebuffer->m_pstreameffectOut;
            
            m_pprebuffer->m_pstreameffectOut = NULL;
            
            delete peffect;

         }

         m_eventStopped.SetEvent();

         ::fork(get_app(), [=]()
         {

            m_pplayer->OnEvent(::multimedia::audio::wave_player::EventPlaybackEnd);

         });


      }


      ::count wave_out::wave_out_get_buffered_buffer_count()
      {

         return ::multimedia::audio::wave_out::wave_out_get_buffered_buffer_count();

      }


      WAVEFORMATEX * wave_out::wave_format()
      {

         xaudio::translate(m_waveformatex, m_pwaveformat);

         return &m_waveformatex;

      }


      void * wave_out::get_os_data()
      {
         
         return m_psourcevoice;

      }


      void wave_out::wave_out_prebuffer_eof()
      {

         ::multimedia::audio::wave_out::wave_out_prebuffer_eof();

      }


      void wave_out::OnStreamEnd()
      {

      }


      void wave_out::OnVoiceProcessingPassStart(UINT32 bytesRequired)
      {

      }


      void wave_out::OnVoiceProcessingPassEnd()
      {

      }

      void wave_out::OnBufferStart(void* pBufferContext)
      {

         ::multimedia::audio::wave_buffer::buffer * pbuffer = (::multimedia::audio::wave_buffer::buffer *)pBufferContext;

      }


      void wave_out::OnBufferEnd(void* pBufferContext)
      {

         ::multimedia::audio::wave_buffer::buffer * pbuffer = (::multimedia::audio::wave_buffer::buffer *)pBufferContext;

         int32_t iBuffer = (int32_t)pbuffer->m_iIndex;

         ::PostThreadMessage(m_pthreadFree->get_os_int(), wave_out::message_free, iBuffer, 0);

      }


      void wave_out::OnLoopEnd(void * bufferContext)
      {

      }


      void wave_out::OnVoiceError(void * bufferContext, HRESULT hresult)
      {

      }


   } // namespace audio_xaudio


} // namespace multimedia






