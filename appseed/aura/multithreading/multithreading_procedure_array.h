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


   inline thread_ptra async_all()
   {

      thread_ptra threadptra;

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

      //register_at_required_threads();

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

  //    unregister_from_required_threads();
//
      m_p->threadrefa_remove(this);

   }


   inline cres try_sync_catch_all()
   {

      cres cres;

      m_p->threadrefa_add(this);

      //register_at_required_threads();

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
         catch(::exception::exception * p)
         {

            cres.add(p);

         }
         catch(...)
         {

            cres.add(canew(simple_exception(get_app())));

         }

         try
         {

            (m_p->*pfnProc)();

         }
         catch(::exception::exception * p)
         {

            cres.add(p);

         }
         catch(...)
         {

            cres.add(canew(simple_exception(get_app())));

         }

      }

      //unregister_from_required_threads();

      m_p->threadrefa_remove(this);

      return cres;

   }


};


template < typename TYPE >
procedure_array < TYPE > new_proc_array(TYPE * p)
{

   return procedure_array < TYPE > (p);

}
