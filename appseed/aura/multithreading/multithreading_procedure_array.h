#pragma once


template < typename TYPE >
class procedure_array :
   virtual public array < void (TYPE::*)() >,
   virtual public thread
{
public:


   TYPE * m_p;


   procedure_array(TYPE * p) :
      ::object(p->get_app()),
      ::thread(p->get_app())
   {

      m_p = p;

   }

   procedure_array(const procedure_array < TYPE > & a) :
      ::object(a.get_app()),
      ::thread(a.get_app())
   {

      m_p = a.m_p;

   }


   virtual void assert_valid() const {}
   virtual void dump(dump_context &) const {}


   inline ref_array < thread * > async_all()
   {

      ref_array < thread * > threadptra;

      array < void (TYPE::*)() > & a = *this;

      for(auto pfnProcedure : a)
      {

         threadptra.add(m_p->fork([=]()
         {

            (m_p->*pfnProcedure)();

         }));

      }

      return threadptra;

   }

   inline void sync_all()
   {

      m_p->threadrefa_add(this);

      register_at_required_threads();

      array < void (TYPE::*)() > & a = *this;

      for(auto pfnProc : a)
      {

         try
         {

            if(!::get_thread_run())
            {

               break;

            }

            if(!get_thread_run())
            {

               break;

            }

         }
         catch(...)
         {

         }

         try
         {

            (m_p->*pfnProc)();

         }
         catch(...)
         {

         }

      }

      unregister_from_required_threads();

      m_p->threadrefa_remove(this);

   }

};

template < typename TYPE >
procedure_array < TYPE > new_proc_array(TYPE * p)
{

   return procedure_array < TYPE > (p);

}
