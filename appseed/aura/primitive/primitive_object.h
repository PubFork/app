#pragma once


//class CLASS_DECL_AURA ::object :
class CLASS_DECL_AURA mini_object
// virtual public element
//class CLASS_DECL_AURA waitable :
//class CLASS_DECL_AURA object
//   virtual public ::object
{
public:


   int64_t m_countReference;

   mini_object()
   {
      m_countReference = 1;
   }
   virtual ~mini_object()
   {

   }

   virtual int64_t add_ref()
   {

#ifdef WINDOWS

      return InterlockedIncrement64(&m_countReference);

#elif defined(RASPBIAN) && defined(OS32BIT)

      return __sync_add_and_fetch_4(&m_countReference,1);

#else

      return __sync_add_and_fetch(&m_countReference, 1);

#endif

   }


   int64_t dec_ref()
   {

#ifdef WINDOWS

      return InterlockedDecrement64(&m_countReference);

#elif defined(RASPBIAN) && defined(OS32BIT)

      return __sync_sub_and_fetch_4(&m_countReference,1);

#else

      return __sync_sub_and_fetch(&m_countReference, 1);

#endif

   }


   int64_t release()
   {

      int64_t i = dec_ref();

      if (i == 0)
      {

         delete this;

      }

      return i;

   }

   inline void set_heap_alloc()
   {

   }


};

class var;
class application_bias;
class create;
class command_line;
class thread_ptra;
#include "aura/multithreading/multithreading_wait_result.h"
// Duplicated root here... element is essentially like root (Rute, Inha, Lenir) for templates, but not for polymorphism


inline int64_t atomic_increment(int64_t * pi)
{

#ifdef WINDOWS

   return InterlockedIncrement64(pi);

#elif defined(RASPBIAN) && defined(OS32BIT)

   return __sync_add_and_fetch_4(pi,1);

#else

   return __sync_add_and_fetch(pi,1);

#endif

}


inline int64_t atomic_decrement(int64_t * pi)
{

#ifdef WINDOWS

   return InterlockedDecrement64(pi);

#elif defined(RASPBIAN) && defined(OS32BIT)

   return __sync_sub_and_fetch_4(pi,1);

#else

   return __sync_sub_and_fetch(pi,1);

#endif

}


class CLASS_DECL_AURA simple_object
{
public:


   int64_t                       m_countReference;


   simple_object();
   virtual ~simple_object();

   virtual void set_heap_alloc();
   inline int64_t get_ref_count()
   {

      return m_countReference;

   }

   virtual void delete_this();


   virtual int64_t add_ref();
   virtual int64_t dec_ref();
   virtual int64_t release();


};



class CLASS_DECL_AURA object :
   virtual public simple_object
{
public:


   enum flag
   {

      flag_auto_clean = 1 << 0,
      flag_discard_to_factory = 1 << 1,
      flag_ready_for_delete = 1 << 2,
      flag_auto_delete = 1 << 3,
      flag_heap_alloc = 1 << 4,
      flag_locked = 1 << 5,
      flag_shared = 1 << 6

   };


   uint64_t                      m_ulFlags;
   factory_item_base *           m_pfactoryitembase;
   void *                        m_pthis;
   ::aura::application *         m_pauraapp;
   mutex *                       m_pmutex;
   property_set *                m_psetObject;
   thread_ptra *                 m_pthreadrefa;


   object();
   object(::aura::application * papp);
   object(const object & objectSrc);              // no implementation
   virtual ~object();  // virtual destructors are necessary


   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;




   template < typename PRED >
   inline ::thread * fork(PRED pred);

   template < typename PRED >
   inline ::thread * delay_fork(bool * pbExecuting, int64_t * piRequestCount, ::duration duration, PRED pred);

   template < typename TYPE >
   inline ::thread * async(void (TYPE::*pfnMemberProcedure)())
   {

      return fork([=]()
      {

         TYPE * ptype = dynamic_cast <TYPE *> (this);

         (ptype->*pfnMemberProcedure)();

      });

   }


   void defer_create_mutex();


   virtual void delete_this();


   virtual object * clone();


   static void system(const char * pszProjectName);

   inline ::aura::allocatorsp & allocer();

   inline ::aura::allocatorsp & allocer() const { return ((object *)this)->allocer(); }

   inline ::aura::application * get_app() const { return m_pauraapp; }

   virtual void set_app(::aura::application * papp);

   inline bool is_set_ca_flag(object::flag eflag)
   {
      return (m_ulFlags & ((uint32_t)eflag)) == (uint32_t)eflag;
   }

   inline void clear_ca_flag(object::flag eflag)
   {
      m_ulFlags &= ~eflag;
   }

   inline void set_ca_flag(object::flag eflag)
   {

      m_ulFlags |= eflag;

   }


   object & operator = (const object & o);

   void copy_this(const object & o);

   inline void set_heap_alloc()
   {

      m_ulFlags |= (uint64_t) ::object::flag_heap_alloc;

   }



   inline bool is_heap()
   {

      return (m_ulFlags & (uint64_t) flag_heap_alloc) != 0;

   }


   virtual ::id calc_object_id() const;
   virtual ::id calc_default_object_id() const;


   virtual void add_line(::command::command * pcommand, application_bias * pbiasCreate = NULL);
   virtual void add_line(const char * pszCommandLine, application_bias * pbiasCreate = NULL);
   virtual void add_line_uri(const char * pszCommandLine,application_bias * pbiasCreate = NULL);

   virtual void add_fork(::command::command * pcommand, application_bias * pbiasCreate = NULL);
   virtual void add_fork(const char * pszCommandLine,application_bias * pbiasCreate = NULL);
   virtual void add_fork_uri(const char * pszCommandLine,application_bias * pbiasCreate = NULL);


   // semantics defined by the requested object - ::object implementator
   virtual void request_file(var & varFile);
   virtual void request_file_query(var & varFile,var & varQuery);
   virtual void request_command(command_line * pcommandline);
   virtual void request_create(::create * pcreate);

   virtual void handle(::command::command * pcommand);
   virtual void handle(::create * pcreate);

   virtual void on_handle(::command::command * pcommand);
   virtual void on_handle(::create * pcreate);

   virtual void threadrefa_add(::thread * pthread);
   virtual void threadrefa_post_quit();
   virtual void threadrefa_wait(duration duration);
   virtual void threadrefa_remove(::thread * pthread);

   // main loosely coupled semantics :
   // varFile   : empty, one file path, many file paths, one file object, one or more file objects, or Url, of cached, downloaded, dowloading or queuing files to be opened
   // varQuery  : more ellaborated requests for the requested object - syntax and semantic defined by requested object - ::object implementator
   // virtual void on_request(sp(command_line) pcommandline);
   virtual void on_request(::create * pcreate);


   virtual string lstr(id id, string strDefault = "");

   //void common_construct();

   bool IsSerializable() const;


   property & oprop(const char * psz);
   property & oprop(const char * psz) const;
   property_set & oprop_set();


   inline sp(::handler) handler();


   virtual void keep_alive();
   virtual void on_keep_alive();
   virtual bool is_alive();


};



namespace aura
{


   class CLASS_DECL_AURA allocator:
      virtual public object
   {
   public:


      virtual ~allocator();


   };


   class CLASS_DECL_AURA allocatorsp:
      public sp(allocator)
   {
   public:


      allocatorsp(::aura::application * papp);


   };



} // namespace aura











template < class T >
T * dereference_no_delete(T * p) { p->set_heap_alloc(); p->m_countReference--; return p; }




template < class c_derived >
inline int64_t add_ref(c_derived * pca)
{
   if(pca == NULL)
      return -1;
   return pca->add_ref();
}

template < class c_derived >
inline int64_t release(c_derived * & pca)
{
   if(pca == NULL)
      return -1;
   c_derived * p = pca;
   pca = NULL;
   try
   {
      int64_t count = p->release();
      return count;
   }
   catch(...)
   {
      return -1;
   }
}



template < class c_derived >
inline int64_t ref_count(c_derived * pca)
{
   if(pca == NULL)
      return -1;
   return pca->get_ref_count();
}


#define canew(x) dereference_no_delete(new x)






