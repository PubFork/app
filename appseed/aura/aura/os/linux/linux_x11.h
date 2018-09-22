#pragma once


extern mutex * g_pmutexX11;
extern list < sp(object) > * g_prunnableptrlX11;

template < typename PRED >
void fork_x11(PRED pred)
{

   synch_lock sl(g_pmutexX11);

   g_prunnableptrlX11->add_tail(create_runnable_pred(pred));

}

template < typename PRED >
void sync_x11(PRED pred)
{

   synch_lock sl(g_pmutexX11);

   sp(object) prunnable = create_runnable_pred(pred);

   g_prunnableptrlX11->add_tail(prunnable);

   tick tickStart = tick::now();

   while(prunnable->interlockedlong() <= 0)
   {

      Sleep(100);

      if(tick::now() - tickStart > 10000)
      {

         break;

      }

   }

}

