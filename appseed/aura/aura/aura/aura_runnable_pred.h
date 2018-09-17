#pragma once





CLASS_DECL_AURA void main_async_runnable(runnable * prunnable);
CLASS_DECL_AURA void main_sync_runnable(runnable * prunnable);


template < typename PRED >
class runnable_pred :
   virtual public object
{
public:

   PRED m_pred;

   runnable_pred(PRED pred) :
      m_pred(pred)
   {

   }

   virtual ~runnable_pred()
   {


   }

   virtual void run()
   {

      m_pred();

   }


};


template < typename PRED >
inline ::object * create_runnable_pred(PRED pred)
{

   return canew(runnable_pred < PRED >(pred));

}


template < typename PRED >
inline void main_async(PRED pred)
{

   object * pobject = create_runnable_pred(pred);

   main_async_runnable(pobject);

}


template < typename PRED >
inline void main_sync(PRED pred)
{

   object * pobject = create_runnable_pred(pred);

   main_sync_runnable(pobject);

}
