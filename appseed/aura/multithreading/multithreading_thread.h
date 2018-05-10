#pragma once


class CLASS_DECL_AURA error :
   virtual public object
{
public:


   int_array                                    m_iaErrorCode2;
   index_map < sp(::exception::exception) >     m_mapError2;


   error();
   virtual ~error();


   error & operator =(const error & error);


   void set(int iErrorCode, ::exception::exception * pexception);

   void set(int iErrorCode);

   void set(::exception::exception * pexception);

   void set_last_error();

   void set_if_not_set(int iErrorCode = -1);


   int get_exit_code();

   ::exception::exception * get_exception();

   ::exception::exception * detach_exception();


};


///
/// a thread must be always allocated in the heap
///
class CLASS_DECL_AURA thread :
   virtual public command_target
#ifdef WINDOWS
   ,virtual public ::exception::translator
#endif
{
private:

   bool                                   m_bRunThisThread;

public:

   static mutex *                         s_pmutexDependencies;

   enum e_op
   {

      op_none,
      op_tool,
      op_pred,
      op_fork_count,

   };

   enum e_tool
   {

      tool_draw2d,

   };


   class CLASS_DECL_AURA file_info :
      virtual public object
   {
   public:


      file_info();
      ~file_info();

      ::duration                             m_durationFileSharingViolationTimeout;

   };

   bool                                   m_bAvoidProcFork;
   bool                                   m_bThreadToolsForIncreasedFps;
   //::duration                             m_durationRunLock;
   map < ::multithreading::e_priority,
       ::multithreading::e_priority,
       sp(::thread_tools) >               m_toolmap;
   user_interaction_ptr_array *           m_puiptra;

   single_lock *                          m_pslUser;
   static bool                            s_bAllocReady;

   object_ptra                            m_objectptraDependent;

   //mutex *                              m_pmutex;

   //thread_impl_sp                       m_pthreadimpl;

   //bool                                 m_bAutoDelete;       // enables 'delete this' after thread termination
   uint_ptr                               m_dwAlive;
   bool                                   m_bReady;
   error                                  m_error;
   ::user::primitive *                       m_puiMain;           // main interaction_impl (usually same System.m_puiMain)
   ::user::primitive *                    m_puiActive;         // active main interaction_impl (may not be m_puiMain)
   //property_set                           m_set;
   string                                 m_strWorkUrl;
   thread_ptra                            m_threadrefaDependent;
   thread_ptra                            m_threadrefaRequired;
   ::user::interactive *                  m_pinteractive;
   bool                                   m_bSimpleMessageLoop;
   bool                                   m_bZipIsDir;

//   replace_thread *                       m_preplacethread;

   //manual_reset_event *                   m_peventEvent;

   sp(file_info) m_pfileinfo;


#ifndef WINDOWSEX

   mq *                                      m_mq;

#endif

   //thread *                                  m_pthread;

   //sp(ref_array < ::user::primitive >)     m_spuiptra;

   bool                                      m_bDupHandle;
   HTHREAD                                   m_hthread;
   IDTHREAD                                  m_uiThread;

   pointer_array < ::user::frame * >         m_frameptra;

   LPVOID                                    m_pThreadParams;
   __THREADPROC                              m_pfnThreadProc;

   manual_reset_event *                      m_pevReady;
   UINT                                      m_nDisablePumpCount;
   mutex                                     m_mutexUiPtra;

   UINT                                      m_dwFinishTimeout;

   string                                    m_strDebug;
   string                                    m_strFile;
   int                                       m_iLine;

   sp(::handler)                             m_phandler;
   DWORD_PTR                                 m_dwThreadAffinityMask;
   spa(::thread_toolset)                     m_toolset;




   thread();
   thread(::aura::application * papp);
   thread(::aura::application * papp, __THREADPROC pfnThreadProc, LPVOID pParam);
   virtual ~thread();


   virtual void assert_valid() const override;
   virtual void dump(dump_context & dumpcontext) const override;


   thread_tools * tools(::multithreading::e_priority epriority);
   thread_toolset * toolset(e_tool etool);

   // file related stuff
   file_info * get_file_info();
   DWORD get_file_sharing_violation_timeout_total_milliseconds();
   ::duration set_file_sharing_violation_timeout(::duration duration);


   virtual void threadrefa_add(::thread * pthread) override;

   ///  \brief    starts thread on first call
   virtual void start();

   virtual void * get_os_data() const;
   virtual IDTHREAD get_os_int() const;


   virtual HTHREAD get_os_handle() const;


   virtual void set_os_data(void * pvoidOsData);
   virtual void set_os_int(IDTHREAD iData);


   friend bool __internal_pre_translate_message(MESSAGE * pMsg);


   void CommonConstruct();

   virtual void on_keep_alive() override;
   virtual bool is_alive() override;


   virtual bool has_message();

   virtual int get_x_window_count() const;

   virtual wait_result wait(const duration & duration);

   void set_priority(int32_t priority);

   int32_t priority();

   ::user::interactive * interactive();
   //virtual bool is_auto_delete();

   virtual bool begin(int32_t epriority = ::multithreading::priority_normal, uint_ptr nStackSize = 0, uint32_t dwCreateFlags = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL, IDTHREAD * puiId = NULL, error * perror = NULL);

   virtual bool create_thread(int32_t epriority = ::multithreading::priority_normal,uint_ptr nStackSize = 0, uint32_t dwCreateFlags = 0,LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL, IDTHREAD * puiId = NULL, error * perror = NULL);

   virtual bool begin_synch(int32_t epriority = ::multithreading::priority_normal,uint_ptr nStackSize = 0, uint32_t dwCreateFlags = 0,LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL, IDTHREAD * puiId = NULL, error * perror = NULL);

   virtual bool create_thread_synch(int32_t epriority = ::multithreading::priority_normal,uint_ptr nStackSize = 0, uint32_t dwCreateFlags = 0,LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL, IDTHREAD * puiId = NULL, error * perror = NULL);


   virtual int32_t get_thread_priority();
   virtual bool set_thread_priority(int32_t epriority);

   virtual uint32_t ResumeThread();
   virtual bool post_message(UINT message, WPARAM wParam = 0, lparam lParam = 0);
   virtual bool send_message(UINT message,WPARAM wParam = 0,lparam lParam = 0, ::duration durWaitStep = millis(1));
   virtual bool post_object(UINT message, WPARAM wParam, lparam lParam);
   virtual bool send_object(UINT message, WPARAM wParam, lparam lParam, ::duration durWaitStep = millis(1));
   virtual bool post_message(::user::primitive * pui, UINT message, WPARAM wParam = 0, lparam lParam = 0);

   template < typename PRED >
   bool post_pred(sp(object) phold, PRED pred)
   {
      return post_object(message_system, system_message_pred, dynamic_cast < pred_holder_base *>(canew(pred_holder < PRED >(get_app(), phold, pred))));
   }

   template < typename PRED >
   bool post_pred(PRED pred)
   {
      return post_object(message_system, system_message_pred, dynamic_cast < pred_holder_base *>(canew(pred_holder < PRED >(get_app(), pred))));
   }

   template < typename PRED >
   bool schedule_pred(sp(object) phold, PRED pred)
   {
      return post_pred(phold, pred);
   }

   template < typename PRED >
   bool schedule_pred(PRED pred)
   {
      return post_pred(pred);
   }

   virtual bool on_run_exception(::exception::exception * pexception);



   // running and idle processing
   virtual void pre_translate_message(::message::message * pobj);
   virtual bool pump_message();     // low level message pump
   virtual bool raw_pump_message();     // low level message pump
   virtual bool defer_pump_message();     // deferred message pump
   virtual bool process_message(LPMESSAGE lpmessage);     // route message
   virtual bool raw_process_message(LPMESSAGE lpmessage);     // route message
   // virtual bool on_idle(LONG lCount); // return TRUE if more idle processing
   virtual bool on_thread_on_idle(::thread * pthread, LONG lCount);
   virtual bool is_idle_message(::message::message * pobj);  // checks for special messages
   virtual bool is_idle_message(LPMESSAGE lpmessage);  // checks for special messages

   virtual bool init_thread();
   virtual bool on_pre_run_thread();
   virtual void run();
   virtual void on_pos_run_thread();
   virtual void term_thread();

   virtual void close_dependent_threads(const ::duration & dur);

   virtual void process_window_procedure_exception(::exception::exception *, ::message::message * pobj);

   virtual void process_message_filter(int32_t code, ::message::message * pobj);

   // virtual void add(::user::primitive * pui);
   //virtual void remove(::user::primitive * pui);
   //virtual ::count get_ui_count();
   //virtual ::user::primitive * get_ui(index iIndex);
   //virtual void set_timer(::user::primitive * pui, uint_ptr nIDEvent, UINT nEllapse);
   //virtual void unset_timer(::user::primitive * pui, uint_ptr nIDEvent);
   //virtual void set_auto_delete(bool bAutoDelete = true);
   virtual ::user::primitive * get_active_ui();
   virtual ::user::primitive * set_active_ui(::user::primitive * pui);
   //virtual void step_timer();
   //virtual bool on_run_step();


   virtual void Delete();
   // 'delete this' only if m_bAutoDelete == TRUE

   virtual void dispatch_thread_message(::message::message * pobj);  // helper

   virtual void main();





   virtual void wait();


   virtual int_ptr item() const;



   virtual bool verb();


   virtual void post_to_all_threads(UINT message,WPARAM wparam,LPARAM lparam);


   virtual bool register_dependent_thread(::thread * pthread);
   virtual void unregister_dependent_thread(::thread * pthread);
   virtual bool on_register_dependent_thread(::thread * pthread);
   virtual void on_unregister_dependent_thread(::thread * pthread);
   virtual void signal_close_dependent_threads();
   virtual void wait_close_dependent_threads(const duration & duration);
   virtual bool register_at_required_threads();
   virtual void unregister_from_required_threads();

   virtual void do_events();
   virtual void do_events(const duration & duration);

   virtual bool thread_get_run();
   virtual bool should_enable_thread();
   virtual void post_quit();

   virtual bool kick_thread();

   //virtual void defer_add_thread_run_wait(sync_object_ptra & soa);

   virtual void message_queue_message_handler(::message::base * pobj);

   //DECL_GEN_SIGNAL(_001OnSendThreadMessage);
   DECL_GEN_SIGNAL(_001OnThreadMessage);


   virtual void shutdown(bool bPrompt = true);

   virtual bool on_before_shutdown();

   virtual bool is_application();
   virtual bool is_session();
   virtual bool is_system();

   virtual void delete_this() override;

   /// thread implementation
   virtual int32_t thread_startup(::thread_startup * pstartup);
   virtual bool thread_entry();
   virtual int32_t thread_exit();
   virtual int32_t thread_term();
   virtual void thread_delete();
   operator HTHREAD() const;

   void construct();

   void construct(__THREADPROC pfnthread_implProc, LPVOID pParam);

   virtual bool begin_thread(bool bSynch = false, int32_t epriority= ::multithreading::priority_normal,uint_ptr nStackSize = 0,uint32_t dwCreateFlagsParam = 0,LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL, IDTHREAD * puiId = NULL, error * perror = NULL);

   virtual bool initialize_message_queue();

   virtual void message_handler(::message::base * pbase);

   ::handler * handler();

   virtual void handle_command(::command::command * pcommand);

   virtual void on_create(::create * pcreate);

   virtual void request_create(::create * pcreate) override;


   virtual int get_exit_code();

};


//
//class CLASS_DECL_AURA replace_thread
//{
//public:
//
//   ::thread *                    m_pthread;
//   ::thread *                    m_pthreadNew;
//   mutex &                       m_mutex;
//
//   replace_thread(mutex & m): m_mutex(m) {  }
//
//   void replace(::thread * pcanew);
//
//   bool do_replace(::thread * pthread);
//
//};




namespace multithreading
{


   CLASS_DECL_AURA void post_quit();
   CLASS_DECL_AURA void post_quit_and_wait(const duration & duration);


   CLASS_DECL_AURA void post_quit(::thread * pthread);
   CLASS_DECL_AURA void post_quit_and_wait(::thread * pthread, const duration & duration);


} // namespace multithreading


CLASS_DECL_AURA bool is_thread_on(IDTHREAD id);
CLASS_DECL_AURA void set_thread_on(IDTHREAD id);
CLASS_DECL_AURA void set_thread_off(IDTHREAD id);




CLASS_DECL_AURA bool thread_sleep(DWORD dwMillis);


