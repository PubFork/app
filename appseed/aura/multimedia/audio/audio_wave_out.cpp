#include "framework.h"


//namespace aura
//{
//
//
//   namespace audio
//   {
//
//
//      wave_out::wave_out(::aura::application * papp) :
//         ::object(papp)
//      {
//
//         defer_create_mutex();
//
//      }
//
//
//      wave_out::~wave_out()
//      {
//
//
//      }
//
//
//      bool wave_out::wave_out_push_packet(WAVE_OUT_PACKET * ppacket)
//      {
//
//         single_lock sl(m_pmutex);
//
//         auto & a = m_mapPacket[ppacket->m_chChannel];
//
//         a.insert_at(0, ppacket);
//
//         return;
//
//      }
//
//
//
//      WAVE_OUT_PACKET * wave_out::wave_out_pop_packet(char chChannel)
//      {
//
//         single_lock sl(m_pmutex);
//
//         auto & a = m_mapPacket[chChannel];
//
//         if(a.is_empty())
//         {
//
//            return NULL;
//
//         }
//
//         return a.pop();
//
//      }
//
//
//   } // namespace audio
//
//
//} // namespace aura
//
//
//
//
//
//CLASS_DECL_AURA bool wave_out_push_packet(WAVE_OUT_PACKET * ppacket)
//{
//
//   return ::aura::system::g_p->m_spwaveout->wave_out_push_packet(ppacket);
//
//}
//
//
//CLASS_DECL_AURA WAVE_OUT_PACKET * wave_out_pop_packet(char chChannel)
//{
//
//   return ::aura::system::g_p->m_spwaveout->wave_out_pop_packet(chChannel);
//
//}



LPWAVEOUT waveout_open(int iChannel, LPAUDIOFORMAT pformat, LPWAVEOUT_CALLBACK pcallback)
{

   return aura::system::g_p->waveout_open(iChannel, pformat, pcallback);

}


int waveout_start(LPWAVEOUT pwaveout)
{

   return (*pwaveout->waveout_start)(pwaveout->waveoutcontext);

}

int waveout_write(LPWAVEOUT pwaveout, const void * pdata, unsigned int s)
{

   return (*pwaveout->waveout_write)(pwaveout->waveoutcontext, pdata, s);

}

int waveout_stop(LPWAVEOUT pwaveout)
{

   return (*pwaveout->waveout_stop)(pwaveout->waveoutcontext);

}

int waveout_close(LPWAVEOUT pwaveout)
{

   return (*pwaveout->waveout_close)(pwaveout->waveoutcontext);

}


