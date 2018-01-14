#pragma once


template < class DST, class SRC >
class signal_thread :
   public thread
{
public:


   DST *                   m_psignalizableDst;
   void (DST::*            m_pfnDst)(::message::message *);
   SRC *                   m_psignalizableSrc;
   void (SRC::*            m_pfnSrc)(::message::message *);
   ::message::message *    m_pobj;


   signal_thread(::aura::application * papp,
      DST * psignalizableDst, void (DST::* pfnDst)(::message::message *),
      SRC * psignalizableSrc, void (SRC::* pfnSrc)(::message::message *),
      ::message::message * pobj) :
      object(papp),
      thread(papp)
   {
      
      m_psignalizableDst = psignalizableDst;
      
      m_pfnDst = pfnDst;
      
      m_psignalizableSrc = psignalizableSrc;
      
      m_pfnSrc = pfnSrc;
      
      m_pobj = pobj;
      
   }


   void run()
   {
      
      try
      {
         
         (m_psignalizableSrc->*m_pfnSrc)(m_pobj);
         
         (m_psignalizableDst->*m_pfnDst)(m_pobj);
         
      }
      catch (...)
      {
         
      }
      
      ::aura::del(m_pobj);
      
   }


};

template < class DST, class SRC >
void emit(::aura::application * papp,
   DST * psignalizableDst, void (DST::* pfnDst)(::message::message *),
   SRC * psignalizableSrc, void (SRC::* pfnSrc)(::message::message *),
   ::message::message * pobj)
{
   signal_thread < DST, SRC > * pthread = new signal_thread < DST, SRC >(papp, psignalizableDst, pfnDst, psignalizableSrc, pfnSrc, pobj);
   pthread->begin();
}

