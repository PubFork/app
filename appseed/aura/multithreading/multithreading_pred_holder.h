#pragma once


class CLASS_DECL_AURA pred_holder_base :
   virtual public object
{
public:

   ::tool_thread *      m_ptoolthread;
   sp(object)           m_pholdref;

   pred_holder_base(::aura::application * papp, sp(object) pholdref = NULL) :
      object(papp),
      m_pholdref(pholdref)
   {

      m_ptoolthread = NULL;

   }

   virtual void run() {}

};

template < typename PRED >
class pred_holder :
   virtual public pred_holder_base
{
public:

   PRED m_pred;

   pred_holder(::aura::application * papp, PRED pred) :
      object(papp),
      pred_holder_base(papp),
      m_pred(pred)
   {

   }

   pred_holder(::aura::application * papp, sp(object) pholdref, PRED pred) :
      object(papp),
      pred_holder_base(papp, pholdref),
      m_pred(pred)
   {

   }

   virtual void run() { m_pred(); }

};




class CLASS_DECL_AURA pred_array :
   virtual public array < sp(pred_holder_base) >
{
public:


   pred_array(::aura::application * papp);
   virtual ~pred_array();


   template < typename PRED >
   void pred_add(PRED pred)
   {

      add(canew(pred_holder < PRED >(get_app(), pred)));

   }

   void run_all();

};


