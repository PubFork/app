#pragma once





CLASS_DECL_AURA void main_async_runnable(::object * pobjectRunnable);
CLASS_DECL_AURA void main_sync_runnable(::object * pobjectRunnable);


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

   object * pobjectRunnable = create_runnable_pred(pred);

   main_async_runnable(pobjectRunnable);

}


template < typename PRED >
inline void main_sync(PRED pred)
{

   object * pobjectRunnable = create_runnable_pred(pred);

   main_sync_runnable(pobjectRunnable);

}
