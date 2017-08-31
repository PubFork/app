#include "framework.h"
//#include "signal.h"

//mutex * g_pmutexSignal = NULL;
//
//::message::message::message::message(::aura::application * papp) :
//   object(papp)
//{
//
//   m_iParam    = 0;
//   m_psignal   = NULL;
//   m_bRet      = false;
//   m_iIndex    = 0;
//   m_pset      = NULL;
//
//}
//
//
//::message::message::message::message(class signal * psignal) :
//   object(psignal->get_app())
//{
//
//   m_iParam    = 0;
//   m_psignal   = psignal;
//   m_bRet      = false;
//   m_iIndex    = 0;
//   m_pset      = NULL;
//
//}
//
//
//void ::message::message::reset(class ::message::sender * psignal)
//{
//   
//   if(psignal->get_app() != NULL)
//   {
//   
//      set_app(psignal->get_app());
//      
//   }
//   
//   m_psignal   = psignal;
//   m_bRet      = false;
//   m_iIndex    = 0;
//   
//}
//
//::message::message::message::message(::aura::application * papp,class signal * psignal):
//   object(papp)
//{
//
//   if(m_pauraapp == NULL && psignal != NULL)
//   {
//
//      m_pauraapp = psignal->m_pauraapp;
//
//   }
//
//   m_iParam    = 0;
//   m_psignal   = psignal;
//   m_bRet      = false;
//   m_iIndex    = 0;
//   m_pset      = NULL;
//
//}
//
//
//::message::message::~::message::message()
//{
//
//   synch_lock sl(g_pmutexSignal);
//
//   if(m_pset != NULL)
//   {
//
//      delete m_pset;
//
//   }
//
//}
//
//
//property_set & ::message::message::operator()()
//{
//
//   if(m_pset == NULL)
//   {
//
//      m_pset = new property_set(get_app());
//
//   }
//
//   return *m_pset;
//
//}
//
//
//bool ::message::message::all_previous() // returns bRet;
//{
//
//   m_psignal->emit_all_previous(this);
//
//   return m_bRet;
//
//}
//
//
//bool ::message::message::previous() // returns bRet;
//{
//
//   m_psignal->emit_previous(this);
//
//   return m_bRet;
//
//}
//
//
//void ::message::message::copy_this(const ::message::message & signaldetails)
//{
//
//   m_uiMessage = signaldetails.m_uiMessage;
//   m_wparam = signaldetails.m_wparam;
//   m_lparam = signaldetails.m_lparam;
//   m_iIndex = signaldetails.m_iIndex;
//   m_pset = signaldetails.m_pset;
//   m_iParam = signaldetails.m_iParam;
//   m_bRet = signaldetails.m_bRet;
//   m_psignal = signaldetails.m_psignal;
//
//}
//
//
//bool ::message::message::emit()
//{
//
//   m_psignal->emit(this);
//
//   return m_bRet;
//
//}
//
//
//::message::receiver::::message::receiver()
//{
//
//}
//
//
//::message::receiver::~::message::receiver()
//{
//
//   signalizable_disconnect_all();
//
//}
//
//
//void ::message::receiver::message::senderizable_disconnect_all()
//{
//
//   synch_lock sl(g_pmutexSignal);
//
//   index i = m_signalptra.get_upper_bound();
//
//   while(i >= 0)
//   {
//
//      class signal * psignal = m_signalptra[i];
//
//      psignal->disconnect(this);
//
//      i = MIN(i - 1, m_signalptra.get_upper_bound());
//
//   }
//
//   m_signalptra.remove_all();
//
//}
//
//
//void ::message::receiver::install_message_routing(::message::sender * psender)
//{
//
//   UNREFERENCED_PARAMETER(pdispatch);
//
//}
//
//
//void ::message::receiver::register_signal(class signal * psignal)
//{
//
//   synch_lock sl(g_pmutexSignal);
//
//   m_signalptra.add_unique(psignal);
//
//}
//
//
//void ::message::receiver::unregister_signal(class signal * psignal)
//{
//
//   synch_lock sl(g_pmutexSignal);
//
//   index i = m_signalptra.get_upper_bound();
//
//   while(i >= 0)
//   {
//
//      if(m_signalptra[i] == psignal)
//      {
//
//         class signal * p = psignal;
//
//         int64_t c = p->m_countReference;
//
//         m_signalptra.remove_at(i);
//
//         if(c > 1)
//         {
//
//            p->disconnect(this);
//
//         }
//
//      }
//
//      i = MIN(i - 1, m_signalptra.get_upper_bound());
//
//   }
//
//}
//
//
//void ::message::receiver::unregister_target(::message::receiver* psignalizable)
//{
//
//   synch_lock sl(g_pmutexSignal);
//
//   for(int32_t i = 0; i < m_signalptra.get_size();)
//   {
//
//      m_signalptra[i]->disconnect(psignalizable);
//
//      if(m_signalptra[i]->m_delegateptra.get_count() <= 0)
//      {
//
//         m_signalptra.remove_at(i);
//
//      }
//      else
//      {
//
//         i++;
//
//      }
//
//   }
//
//}
//
//
//void ::message::receiver::filter_target(::message::receiver* psignalizable)
//{
//
//   synch_lock sl(g_pmutexSignal);
//
//   for(int32_t i = 0; i < m_signalptra.get_size(); i++)
//   {
//
//      m_signalptra[i]->leave_only(psignalizable);
//
//   }
//
//   for (int32_t i = 0; i < m_signalptra.get_size();)
//   {
//
//      if (m_signalptra[i]->m_delegateptra.get_count() <= 0)
//      {
//
//         m_signalptra.remove_at(i);
//
//      }
//      else
//      {
//
//         i++;
//
//      }
//
//   }
//
//}
//
//
//void signal::message::sender_delegate::emit(::message::message * pobj)
//{
//
//   UNREFERENCED_PARAMETER(pobj);
//
//}
//
//
//signal::message::sender()
//{
//
//}
//
//
//signal::~signal()
//{
//
//   disconnect_all();
//
//}
//
//
//void signal::disconnect_all()
//{
//
//   synch_lock sl(g_pmutexSignal);
//
//   index i = m_delegateptra.get_upper_bound();
//
//   while(i >= 0)
//   {
//
//      m_delegateptra[i]->get_signalizable()->unregister_signal(this);
//
//      i = MIN(i - 1, m_delegateptra.get_upper_bound());
//
//   }
//
//   m_delegateptra.remove_all();
//
//}
//
//
//void signal::emit(::message::message * pobj)
//{
//
//   synch_lock sl(g_pmutexSignal);
//
//   if(pobj == NULL)
//   {
//
//      for(index i = m_delegateptra.get_size() - 1; i >= 0 ; i++)
//      {
//
//         signal_delegate * pdelegate = m_delegateptra.element_at(i);
//
//         sl.unlock();
//
//         pdelegate->emit(NULL);
//
//         sl.lock();
//
//      }
//
//   }
//   else
//   {
//
//      for(pobj->m_iIndex = m_delegateptra.get_upper_bound(); pobj->m_iIndex >= 0 ; pobj->m_iIndex = MIN(pobj->m_iIndex - 1, m_delegateptra.get_upper_bound()))
//      {
//
//         signal_delegate * pdelegate = m_delegateptra.element_at(pobj->m_iIndex);
//
//         sl.unlock();
//
//         pdelegate->emit(pobj);
//
//         if(pobj->m_bRet)
//         {
//            
//            return;
//            
//         }
//
//         sl.lock();
//
//      }
//
//   }
//
//}
//
//
//void signal::emit_previous(::message::message * pobj)
//{
//
//   synch_lock sl(g_pmutexSignal);
//
//   if(pobj->m_iIndex <= 0)
//      return;
//
//   pobj->m_iIndex--;
//
//   signal_delegate * pdelegate = m_delegateptra.element_at(pobj->m_iIndex);
//
//   sl.unlock();
//
//   pdelegate->emit(pobj);
//
//}
//
//
//void signal::emit_all_previous(::message::message * pobj)
//{
//
//   while(pobj->m_iIndex > 0)
//   {
//
//      emit_previous(pobj);
//
//      if(pobj->m_bRet)
//         return;
//
//   }
//
//}
//
//
//bool signal::has_handler()
//{
//
//   synch_lock sl(g_pmutexSignal);
//
//   return m_delegateptra.get_size() > 0;
//
//}
//
//
//void signal::disconnect(::message::receiver * psignalizable)
//{
//
//   synch_lock sl(g_pmutexSignal);
//
//   index i = m_delegateptra.get_upper_bound();
//
//   while(i >= 0)
//   {
//
//      if(m_delegateptra[i]->get_signalizable() == psignalizable)
//      {
//
//         try
//         {
//
//            ::message::receiver * p = psignalizable;
//
//            int64_t c = p->m_countReference;
//
//            m_delegateptra.remove_at(i);
//
//            if(c > 1)
//            {
//
//               psignalizable->unregister_signal(this);
//
//            }
//
//         }
//         catch(...)
//         {
//
//         }
//
//      }
//
//      i = MIN(i - 1, m_delegateptra.get_upper_bound());
//
//   }
//
//}
//
//
//void signal::leave_only(::message::receiver * psignalizable)
//{
//
//   synch_lock sl(g_pmutexSignal);
//
//   index i = m_delegateptra.get_upper_bound();
//
//   while(i >= 0)
//   {
//
//      if(m_delegateptra[i]->get_signalizable() != psignalizable)
//      {
//
//         m_delegateptra[i]->get_signalizable()->unregister_signal(this);
//
//         m_delegateptra.remove_at(i);
//
//      }
//
//      i = MIN(i - 1, m_delegateptra.get_upper_bound());
//
//   }
//
//}
//
//
//signalid::~signalid()
//{
//}
//
//signalid_array::message::senderid_array()
//{
//
//}
//
//signalid_array::~signalid_array()
//{
//}
//
//
//signalid * signalid_array::get(signalid * pid)
//{
//
//   synch_lock sl(g_pmutexSignal);
//
//   for(int32_t i = 0; i < this->get_size(); i++)
//   {
//
//      if(this->element_at(i)->is_equal(pid))
//      {
//
//         return this->element_at(i);
//
//      }
//
//   }
//
//   add(pid->copy());
//
//   return this->element_at(get_upper_bound());
//
//}
//
//
//
//void ::message::receiver::on_request_signal(request_signal * prequestsignal)
//{
//
//   request_file_query(prequestsignal->m_varFile, prequestsignal->m_varQuery);
//
//}
//
//
//dispatch::handler_item_base::~handler_item_base()
//{
//
//
//}
//
//
//dispatch::handler_item_array::~handler_item_array()
//{
//}
//
//bool dispatch::handler_item_array::HasSignalizable(::message::receiver* psignalizable)
//{
//
//   synch_lock sl(g_pmutexSignal);
//
//   for (int32_t i = 0; i < this->get_size(); i++)
//   {
//
//      if (this->element_at(i)->get_signalizable() == psignalizable)
//      {
//
//         return true;
//
//      }
//
//   }
//
//   return false;
//
//}
//
//
//dispatch::message::sender_item::message::sender_item()
//{
//
//   m_psignal      = NULL;
//
//   m_pid          = NULL;
//
//}
//
//
//dispatch::message::sender_item::~signal_item()
//{
//
//   ::aura::del(m_psignal);
//
//}
//
//
//dispatch::dispatch()
//{
//
//}
//
//
//dispatch::~dispatch()
//{
//
//   string strId = typeid(*this).name();
//
//}
//
//
