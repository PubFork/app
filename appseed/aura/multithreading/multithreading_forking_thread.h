#pragma once

template < typename PRED >
::thread * pred_run(::aura::application * papp, bool bSync, PRED pred, ::object * pobjectDependent = NULL);


CLASS_DECL_AURA int get_current_process_affinity_order();

#undef new

#define new AURA_NEW

template < typename PRED >
class forking_thread:
   virtual public thread
{
public:

   PRED m_pred;

   sp(object) m_pholdref;

   forking_thread(::aura::application * papp, sp(object) pholdref, PRED pred) :
      object(papp),
      thread(papp),
      m_pholdref(pholdref),
      m_pred(pred)
   {

   }

   forking_thread(::aura::application * papp,PRED pred) :
      object(papp),
      thread(papp),
      m_pred(pred)
   {

   }


   virtual ~forking_thread()
   {

   }

   void run()
   {

      m_pred();

   }

};


template < typename PRED >
::thread * fork(::aura::application * papp, sp(object) pholdref, PRED pred)
{

   auto pforkingthread = canew(forking_thread < PRED >(papp, pholdref, pred));

   ::thread * pthread = dynamic_cast < ::thread * > (pforkingthread);

   pthread->begin();

   return pthread;

}







template < typename PRED >
::thread * fork(::aura::application * papp, PRED pred, ::object * pobjectDependent = NULL)
{

   auto pforkingthread = canew(forking_thread < PRED >(papp, pred));

   ::thread * pthread = dynamic_cast < ::thread * > (pforkingthread);

   if (pobjectDependent != NULL)
   {

      pthread->m_objectptraDependent.add(pobjectDependent);

   }

   pthread->begin();

   return pthread;

}


template < typename PRED >
inline ::thread * object::fork(PRED pred)
{

   defer_create_mutex();

   synch_lock sl(m_pmutex);

   thread * pthread = ::fork(get_app(),pred, this);

   threadrefa_add(pthread);

   return pthread;

}


template < typename PRED >
inline ::thread * object::pred_run(bool bSync, PRED pred)
{

   defer_create_mutex();

   synch_lock sl(m_pmutex);

   thread * pthread = ::pred_run(get_app(), bSync, pred, this);

   if (pthread != NULL)
   {

      threadrefa_add(pthread);

   }

   return pthread;

}


template < typename PRED >
inline ::thread * object::delay_fork(bool * pbExecuting, int64_t * piRequestCount, ::duration duration, PRED pred)
{

   atomic_increment(piRequestCount);

   return fork([=]
   {

restart:

      Sleep(duration);

      if(!::get_thread_run())
      {

         return;

      }

      int64_t iPendingRequestCount = atomic_decrement(piRequestCount);

      if(iPendingRequestCount > 0)
      {

         return;

      }

      if(*pbExecuting)
      {

         atomic_increment(piRequestCount);

         goto restart;

      }

      keep < bool > keepExecutingFlag(pbExecuting, true, false, true);

      if(!::get_thread_run())
      {

         return;

      }

      pred();

   });

}


template < typename T >
inline void fork_release(::aura::application * papp, sp(T) & t)
{

   try
   {

      T * pt;

      pt = t.m_p;

      pt->add_ref();

      t.release();

      ::fork(papp, [&]()
      {

         ::release(pt);

      });

   }
   catch (...)
   {


   }

}


CLASS_DECL_AURA DWORD_PTR translate_processor_affinity(int i);


template < typename PRED >
class forking_count_pred :
   virtual public pred_holder_base
{
public:

   PRED m_pred;

   struct fork_index
   {

      index       m_iOrder;
      index       m_iIndex;
      index       m_iScan;
      ::count     m_cCount;
      index       m_i;

      operator index()
      {

         return m_i;

      }

   };

   fork_index m_index;

   forking_count_pred(::aura::application * papp, index iOrder, index iIndex, ::count iScan, ::count cCount, PRED pred) :
      ::object(papp),
      ::pred_holder_base(papp),
      m_pred(pred)
   {

      m_index.m_iOrder  = iOrder;
      m_index.m_iIndex  = iIndex;
      m_index.m_iScan   = iScan;
      m_index.m_cCount  = cCount;

   }

   virtual void run()
   {

      for (m_index.m_i = m_index.m_iIndex; m_index.m_i < m_index.m_cCount; m_index.m_i += m_index.m_iScan)
      {

         m_pred(m_index);

      }

   }

};


template < typename PRED >
class forking_count_thread :
   virtual public thread
{
public:



   PRED     m_pred;


   index    m_iOrder;
   index    m_iIndex;
   ::count  m_iScan;
   ::count  m_iCount;

   runnable * m_prunnableEnd;

   sp(object) m_pholdref;


   forking_count_thread(::aura::application * papp, sp(object) pholdref, index iOrder, index iIndex, ::count iScan, ::count iCount, PRED pred, runnable * prunnableEnd = NULL) :
      object(papp),
      thread(papp),
      m_pholdref(pholdref),
      m_pred(pred),
      m_iOrder(iOrder),
      m_iIndex(iIndex),
      m_iScan(iScan),
      m_iCount(iCount),
      m_prunnableEnd(prunnableEnd)
   {
      construct();
   }

   forking_count_thread(::aura::application * papp, index iOrder, index iIndex, ::count iScan, ::count iCount, PRED pred, runnable * prunnableEnd = NULL) :
      object(papp),
      thread(papp),
      m_pred(pred),
      m_iOrder(iOrder),
      m_iIndex(iIndex),
      m_iScan(iScan),
      m_iCount(iCount),
      m_prunnableEnd(prunnableEnd)
   {
      construct();
   }

   void construct()
   {

      m_dwThreadAffinityMask = translate_processor_affinity(int (m_iOrder));

   }

   virtual ~forking_count_thread()
   {

   }

   void run()
   {

      m_pred(m_iOrder, m_iIndex, m_iCount, m_iScan);

      if (m_prunnableEnd != NULL)
      {

         m_prunnableEnd->interlockedlong().subtract(1);

         if (m_prunnableEnd->interlockedlong() <= 0)
         {

            if (::get_thread_run())
            {

               m_prunnableEnd->run();

            }
            else
            {

               output_debug_string("optimized m_prunnableEnd->run()");

            }

            delete m_prunnableEnd;

         }

      }

   }

};


template < typename PRED >
::count fork_count(::aura::application * papp, ::count iCount, PRED pred, index iStart = 0)
{

   int iAffinityOrder = get_current_process_affinity_order();

   if (::get_thread() == NULL || ::get_thread()->m_bAvoidProcFork)
   {

      iAffinityOrder = 1;

   }

   ::count iScan = MAX(1, MIN(iCount - iStart, iAffinityOrder));

   for (index iOrder = 0; iOrder < iScan; iOrder++)
   {

      auto pforkingthread = canew(forking_count_thread < PRED >(papp, iOrder, iOrder + iStart, iScan, iCount, pred));

      ::thread * pthread = dynamic_cast <::thread *> (pforkingthread);

      pthread->begin();

   }

   return iScan;

}




template < typename PRED, typename PRED_END >
::count fork_count_end_pred(::aura::application * papp, ::count iCount, PRED pred, PRED_END predEnd, ::duration duration = ::duration::infinite(), index iStart = 0)
{

   int iAffinityOrder = get_current_process_affinity_order();

   if (::get_thread() == NULL || ::get_thread()->m_bAvoidProcFork)
   {

      iAffinityOrder = 1;

   }

   ::count iScan = MAX(1, MIN(iCount - iStart, iAffinityOrder));

   runnable * prunnableEnd = new runnable_pred < PRED_END > (predEnd);

   prunnableEnd->interlockedlong().add(iScan);

   for (index iOrder = 0; iOrder < iScan; iOrder++)
   {

      auto pforkingthread = canew(forking_count_thread < PRED >(papp, iOrder, iOrder + iStart, iScan, iCount, pred, prunnableEnd));

      ::thread * pthread = dynamic_cast <::thread *> (pforkingthread);

      pthread->begin();

   }

   return iScan;

}



template < typename PRED >
class forking_for_thread :
   virtual public thread
{
public:

   PRED     m_pred;



   index    m_iOrder;
   index    m_iIndex;
   ::count  m_iScan;
   ::count  m_iCount;

   sp(object) m_pholdref;

   forking_for_thread(::aura::application * papp, sp(object) pholdref, index iOrder, index iIndex, ::count iScan, ::count iCount, PRED pred) :
      object(papp),
      thread(papp),
      m_pholdref(pholdref),
      m_pred(pred),
      m_iOrder(iOrder),
      m_iIndex(iIndex),
      m_iScan(iScan),
      m_iCount(iCount)
   {
      construct();
   }

   forking_for_thread(::aura::application * papp, index iOrder, index iIndex, ::count iScan, ::count iCount, PRED pred) :
      object(papp),
      thread(papp),
      m_pred(pred),
      m_iOrder(iOrder),
      m_iIndex(iIndex),
      m_iScan(iScan),
      m_iCount(iCount)
   {
      construct();
   }

   void construct()
   {

      m_dwThreadAffinityMask = translate_processor_affinity(int(m_iOrder));

   }

   virtual ~forking_for_thread()
   {

   }

   void run()
   {

      for (; m_iIndex < m_iCount; m_iIndex += m_iScan)
      {

         m_pred(m_iIndex);

      }

   }

};


template < typename PRED >
::count fork_for(::aura::application * papp, ::count iCount, PRED pred, index iStart = 0)
{

   int iAffinityOrder = get_current_process_affinity_order();

   if (::get_thread() == NULL || ::get_thread()->m_bAvoidProcFork)
   {

      iAffinityOrder = 1;

   }

   ::count iScan = MAX(1, MIN(iCount - iStart, iAffinityOrder));

   for (index iOrder = 0; iOrder < iScan; iOrder++)
   {

      auto pforkingthread = canew(forking_for_thread < PRED >(papp, iOrder, iOrder + iStart, iScan, iCount, pred));

      ::thread * pthread = dynamic_cast <::thread *> (pforkingthread);

      pthread->begin();

   }

   return iScan;

}


CLASS_DECL_AURA uint32_t random_processor_index_generator();

template < typename PRED >
spa(::thread) fork_proc(::aura::application * papp, PRED pred, index iCount = -1, ::object * pobjectOwner = NULL)
{

   spa(::thread) threadptra;

   int iProcCount = get_current_process_affinity_order();

   if (iCount < 0 || iCount > iProcCount)
   {

      iCount = iProcCount;

   }

   iCount = MAX(1, iCount);

   if (::get_thread() == NULL || ::get_thread()->m_bAvoidProcFork)
   {

      iCount = 1;

   }

   for (index iProcessor = 0; iProcessor < iCount; iProcessor++)
   {

      auto pforkingthread = canew(forking_thread < PRED >(papp, pred, pobjectOwner));

      ::thread * pthread = dynamic_cast < ::thread * > (pforkingthread);

      pthread->m_dwThreadAffinityMask = translate_processor_affinity(random_processor_index_generator() % iProcCount);

      pthread->m_bThreadToolsForIncreasedFps = false;

      pthread->m_bAvoidProcFork = true;

      threadptra.add(pthread);

      pthread->begin();

   }

   return threadptra;

}



//template < typename PRED >
//class forking_count_thread_end :
//   virtual public forking_count_thread < PRED >
//{
//public:
//
//   manual_reset_event m_evEnd;
//
//   forking_count_thread_end(::aura::application * papp, sp(object) pholdref, index iOrder, index iIndex, ::count iScan, ::count iCount, PRED pred) :
//      object(papp),
//      thread(papp),
//      forking_count_thread<PRED>(papp, pholdref, iOrder, iIndex, iScan, iCount, pred),
//      m_evEnd(papp)
//   {
//      construct();
//   }
//
//   forking_count_thread_end(::aura::application * papp, index iOrder, index iIndex, ::count iScan, ::count iCount, PRED pred) :
//      object(papp),
//      thread(papp),
//      forking_count_thread<PRED>(papp, iOrder, iIndex, iScan, iCount, pred),
//      m_evEnd(papp)
//   {
//      construct();
//   }
//
//   void construct()
//   {
//
//      m_evEnd.ResetEvent();
//
//      forking_count_thread<PRED>::construct();
//
//   }
//
//   virtual ~forking_count_thread_end()
//   {
//
//   }
//
//   int32_t run()
//   {
//
//      try
//      {
//
//         m_pred(this->m_iOrder, this->m_iIndex, this->m_iCount, this->m_iScan);
//
//      }
//      catch (...)
//      {
//
//
//      }
//
//      m_evEnd.SetEvent();
//
//      return 0;
//
//   }
//
//};







//class pred_base
//{
//public:
//
//   virtual void run() = 0;
//
//};
//
//template < typename PRED >
//class pred_holder
//{
//public:
//
//   PRED m_pred;
//
//   virtual void run()
//   {
//
//      m_pred();
//
//   }
//
//};



//class pred_holder_ptra :
//   virtual public array < pred_holder_base * >
//{
//public:
//
//   pred_holder_ptra(::aura::application * papp) :
//      object(papp)
//   {
//
//
//   }
//
//   virtual ~pred_holder_ptra()
//   {
//
//   }
//
//   virtual ::count release()
//   {
//      ::count c = m_countReference - 1;
//      if (m_countReference >= 2)
//      {
//         dec_ref();
//      }
//      else if (m_countReference == 1)
//      {
//
//         ::fork(get_app(), [&]()
//         {
//
//            for (index i = 0; i < get_size(); i++)
//            {
//
//               try
//               {
//
//                  element_at(i)->run();
//
//               }
//               catch (...)
//               {
//
//                  break;
//
//               }
//
//            }
//
//            for (index i = 0; i < get_size(); i++)
//            {
//
//               try
//               {
//
//                  delete element_at(i);
//
//               }
//               catch (...)
//               {
//
//                  break;
//
//               }
//
//            }
//
//            delete this;
//
//         });
//
//
//      }
//
//      return c;
//
//   }
//
//   template < typename PRED >
//   sp(pred_holder_ptra) then(PRED pred)
//   {
//
//      add(new pred_holder <PRED>(get_app(), pred));
//
//      return this;
//
//   }
//
//};
//
//
//template < typename PRED >
//sp(pred_holder_ptra) then(::aura::application * papp, PRED pred)
//{
//
//   sp(pred_holder_ptra) pptra = canew(pred_holder_ptra(papp));
//
//   pptra->add(new pred_holder <PRED>(papp, pred));
//
//   return pptra;
//
//}


template < typename PRED >
::thread * pred_run(::aura::application * papp, bool bSync, PRED pred, ::object * pobjectDependent)
{

   if (bSync)
   {

      pred();

      return NULL;

   }
   else
   {

      return fork(papp, pred, pobjectDependent);

   }

}



