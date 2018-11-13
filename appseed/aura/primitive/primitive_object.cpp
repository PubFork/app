#include "framework.h"


simple_object::simple_object()
{

   m_countReference = 1;

}


simple_object::~simple_object()
{


}
void simple_object::set_heap_alloc()
{


}

int64_t simple_object::add_ref()
{

   return atomic_increment(&m_countReference);

}


int64_t simple_object::dec_ref()
{

   return atomic_decrement(&m_countReference);

}


void simple_object::delete_this()
{

   try
   {

      delete this;

   }
   catch (...)
   {

   }

}




int64_t simple_object::release()
{

   int64_t i = dec_ref();

   if(i == 0)
   {

      delete_this();

   }

   return i;

}


void simple_object::run()
{


}


void simple_object::assert_valid() const
{

   ASSERT(this != NULL);

}


object::object()
{

   m_psetObject = NULL;
   m_pmutex = NULL;
   m_ulFlags = (uint32_t)flag_auto_clean;
   m_pfactoryitembase = NULL;
   m_papp = NULL;
   m_pchildren = NULL;
   m_pparents = NULL;

}


object::object(const object& objectSrc)
{

   if (objectSrc.m_psetObject != NULL)
   {

      m_psetObject = new property_set(*objectSrc.m_psetObject);

   }
   else
   {

      m_psetObject = NULL;

   }

   if (objectSrc.m_pmutex != NULL)
   {

      m_pmutex = new mutex(objectSrc.m_papp);

   }
   else
   {

      m_pmutex = NULL;

   }

   m_ulFlags = (uint32_t)flag_auto_clean;
   m_pfactoryitembase = NULL;
   m_countReference = 1;
   m_papp = objectSrc.m_papp;
   m_pchildren = NULL;
   m_pparents = NULL;

}


object::object(::aura::application * papp)
{

   m_psetObject = NULL;
   m_pmutex = NULL;
   m_ulFlags = (uint32_t)flag_auto_clean;
   m_pfactoryitembase = NULL;
   m_countReference = 1;
   m_papp = papp;
   m_pchildren = NULL;
   m_pparents = NULL;

}


object::~object()
{

   try
   {

      // Last Chance : Objects shouldn't rely on this call.
      // This object (as parent) is virtually completely destroyed.
      // Any children registered as dependant of this object is
      // having trouble to access this object at this point.
      // Solution: right before deleting the object,
      // call children_post_quit_and_wait with appropriate timeout
      // duration, to ask children to destroy themselves and wait
      // for then to finish.

      children_post_quit();

   }
   catch (...)
   {

   }

   try
   {

      release_parents();

   }
   catch (...)
   {

   }

   ::aura::del(m_pchildren);

   ::aura::del(m_pparents);

   ::aura::del(m_psetObject);

   ::aura::delobj(m_pmutex);

}


void simple_object::dump(dump_context & dumpcontext) const
{

   dumpcontext << "a " << typeid(*this).name() << " at " << (void *)this << "\n";

}


void __assert_valid_object(const object * pOb, const char * lpszFileName, int32_t nLine)
{
   if (pOb == NULL)
   {
//      TRACE(::aura::trace::category_AppMsg, 0, "ASSERT_VALID fails with NULL pointer.\n");
      if (__assert_failed_line(lpszFileName, nLine))
         debug_break();
      return;     // quick escape
   }
   if (!__is_valid_address(pOb, sizeof(object)))
   {
      ///TRACE(::aura::trace::category_AppMsg, 0, "ASSERT_VALID fails with illegal pointer.\n");
      if (__assert_failed_line(lpszFileName, nLine))
         debug_break();
      return;     // quick escape
   }

   // check to make sure the VTable pointer is valid
   //   ASSERT(sizeof(::object) == sizeof(void *));
   //   if (!__is_valid_address(*(void **)pOb, sizeof(void *), FALSE))
   if (!__is_valid_address(*(void **)pOb, sizeof(void *), FALSE))
   {
//      TRACE(::aura::trace::category_AppMsg, 0, "ASSERT_VALID fails with illegal vtable pointer.\n");
      if (__assert_failed_line(lpszFileName, nLine))
         debug_break();
      return;     // quick escape
   }

   /*if (!__is_valid_address(pOb, typeid(pOb->GetRuntimeClass()->m_nObjectSize, FALSE))
   {
   TRACE(::aura::trace::category_AppMsg, 0, "ASSERT_VALID fails with illegal pointer.\n");
   if (__assert_failed_line(lpszFileName, nLine))
   debug_break();
   return;     // quick escape
   }*/
   pOb->assert_valid();
}


void object::keep_alive()
{

   try
   {

      on_keep_alive();

   }
   catch(...)
   {

   }


}


void object::on_keep_alive()
{

}


bool object::is_alive()
{

   return true;

}



//
//object::waitable()
//{
//
//   m_pmutex = NULL;
//
//}
//
//object::waitable(const waitable & objectSrc)
//{
//
//   UNREFERENCED_PARAMETER(objectSrc);
//
//   m_pmutex = NULL;
//
//}
//
//
/////  \brief     destructor
//object::~waitable()
//{
//
//   if(m_pmutex != NULL)
//   {
//
//      delete m_pmutex;
//
//      m_pmutex = NULL;
//
//   }
//
//}

///  \brief    abstract function to initialize a waiting action without a timeout
wait_result sync_object::wait()
{

   return wait(duration::infinite());

}

///  \brief    abstract function to initialize a waiting action with a timeout
///  \param    duration time period to wait for item
///  \return   waiting action result as wait_result
//wait_result object::wait(const duration & duration)
//{
//
//
//   if(m_pmutex == NULL)
//   {
//
//      ((object *)this)->m_pmutex = new mutex();
//
//   }
//
//   try
//   {
//      return m_pmutex->wait(duration);
//   }
//   catch(...)
//   {
//   }
//
//   return wait_result(wait_result::Failure);
//
//}




// forward declaration
//class event_base;

/// This class represents a virtual interface for a callback method for WaitableItems in a
/// event_collection.

waitable_callback::~waitable_callback()
{
}

/// called on signalization of a event_base
/// \param signaling event_base
// virtual void callback(const event_base& waitItem) = 0;
//};


///  \brief    pauses waitable for specified time
///  \param    duration sleeping time of waitable
/*CLASS_DECL_AURA void sleep(const duration & duration)
{
Sleep((uint32_t)duration.total_milliseconds());
}*/






//void * object::get_os_data() const
//{
//
//   //if(m_pmutex == NULL)
//   //{
//
//     // ((object *)this)->m_pmutex = new mutex();
//
//   //}
//
//   //return m_pmutex;
//
//   return NULL;
//
//}

//bool sync_object::lock()
//{
//
//   return lock(duration::infinite());
//
//}

//bool object::lock(const duration & duration)
//{
//
//   if(m_pmutex == NULL)
//   {
//
//      ((object *)this)->m_pmutex = new mutex();
//
//   }
//
//   bool bLocked = false;
//
//   try
//   {
//
//      bLocked = m_pmutex->lock(duration);
//
//   }
//   catch(...)
//   {
//
//      bLocked = false;
//
//   }
//
//   if(!bLocked)
//      return false;
//
//   return true;
//
//}


//bool sync_object::unlock()
//{
//
//   if(m_pmutex == NULL)
//      return false;
//
//   bool bUnlocked = false;
//
//   try
//   {
//
//      bUnlocked = m_pmutex->unlock();
//
//   }
//   catch(...)
//   {
//
//      bUnlocked = false;
//
//   }
//
//   if(!bUnlocked)
//      return false;
//
//   return true;
//
//}

//bool object::unlock(LONG lCount,LPLONG lpPrevCount)
//{
//   UNREFERENCED_PARAMETER(lCount);
//   UNREFERENCED_PARAMETER(lpPrevCount);
//   return true;
//}


bool sync_object::is_locked() const
{

   // CRITICAL SECTIONS does *NOT* support is locked and timed locks
   ASSERT(dynamic_cast < critical_section * > (const_cast < sync_object * > (this)) == NULL);

   single_lock sl(const_cast < sync_object * > (this));

   bool bWasLocked = !sl.lock(duration::zero());

   if(!bWasLocked)
      sl.unlock();

   return bWasLocked;

}


void object::defer_update_object_id()
{

   if(m_id.is_empty())
   {

      m_id = calc_default_object_id();

   }

}





::id object::calc_default_object_id() const
{

   string strType = typeid(*this).name();

#ifndef WINDOWS

   strType = demangle(strType);

#endif

   ::str::begins_eat_ci(strType, "class ");

   return strType;

}


void object::handle(::command::command * pcommand)
{

   on_handle(pcommand);

}


void object::handle(::create * pcreate)
{

   if(pcreate->m_spCommandLine->m_varQuery.has_property("client_only"))
   {

      pcreate->m_bClientOnly = true;

   }

   request_create(pcreate);

}


void object::add_line(const char * pszCommandLine, application_bias * pbiasCreate)
{

   ::command::command command;

   command.m_strCommandLine = pszCommandLine;

   add_line(&command, pbiasCreate);

}


void object::add_line(::command::command * pcommand,application_bias * pbiasCreate)
{

   ::handler * commandcentral = get_app()->handler();

   sp(::create) create(canew(::create(commandcentral)));

   create->m_spApplicationBias = pbiasCreate;

   if (Application.m_strAppId == "acid")
   {

      create->m_spCommandLine->m_strApp = "acid";

      create->m_spCommandLine->m_varQuery["app"] = "acid";

   }
   else
   {

      create->m_spCommandLine->_001ParseCommandLine(pcommand->m_strCommandLine);

      if (create->m_spCommandLine->m_strApp.find_ci("app._.exe") >= 0)
         return;

      if (get_app()->handler()->m_varTopicQuery.has_property("appid"))
      {

         if (create->m_spCommandLine->m_varQuery["app"].is_empty())
         {

            create->m_spCommandLine->m_varQuery["app"] = get_app()->handler()->m_varTopicQuery["appid"];

         }
         else
         {

            create->m_spCommandLine->m_varQuery["app"].stra().insert_at(0, get_app()->handler()->m_varTopicQuery["appid"].get_string());

         }

         create->m_spCommandLine->m_strApp = create->m_spCommandLine->m_varQuery["app"];

      }

      if (get_app()->handler()->m_varTopicQuery["build"].has_char())
      {

         create->m_spCommandLine->m_varQuery["build"] = get_app()->handler()->m_varTopicQuery["build"];

      }
      else if (create->m_spCommandLine->m_varQuery["build"].is_empty())
      {

         if (create->m_spCommandLine->m_strApp.compare_ci("app-core/netnodelite") == 0)
         {

            create->m_spCommandLine->m_varQuery["build"] = "static";

         }
         else
         {

            create->m_spCommandLine->m_varQuery["build"] = "installed";

         }

      }

   }

   create->m_spCommandLine->m_varFile._001Add(pcommand->m_varFile.stra());

   if(!create->m_spCommandLine->m_varFile.is_empty())
   {

      create->m_spCommandLine->m_ecommand = command_line::command_file_open;

   }

   commandcentral->merge(create);

   if (commandcentral != System.handler())
   {

      System.handler()->merge(create);

   }

   handle(create);

}


void object::add_line_uri(const char * pszCommandLine,application_bias * pbiasCreate)
{

   sp(::handler) handler = get_app()->handler();

   sp(::create) create(canew(::create(handler)));

   create->m_spApplicationBias = pbiasCreate;

   create->m_spCommandLine->_001ParseCommandLineUri(pszCommandLine);

   handler->merge(create);

   System.handler()->merge(create);

   handle(create);

}


void object::add_fork(const char * pszCommandLine, application_bias * pbiasCreate)
{

   ::command::command command;

   command.m_strCommandLine = pszCommandLine;

   add_fork(&command, pbiasCreate);

}


void object::add_fork(::command::command * pcommand, application_bias * pbiasCreate)
{

   sp(::handler) handler = get_app()->handler();

   sp(::create) create(canew(::create(handler)));

   create->m_spApplicationBias = pbiasCreate;

   create->m_spCommandLine->_001ParseCommandFork(pcommand->m_strCommandLine);

   create->m_spCommandLine->m_varFile._001Add(pcommand->m_varFile.stra());

   handler->merge(create);

   System.handler()->merge(create);

   handle(create);

}


void object::add_fork_uri(const char * pszCommandFork,application_bias * pbiasCreate)
{

   sp(::handler) handler = get_app()->handler();

   sp(::create) create(canew(::create(handler)));

   create->m_spApplicationBias = pbiasCreate;

   create->m_spCommandLine->_001ParseCommandForkUri(pszCommandFork);

   handler->merge(create);

   System.handler()->merge(create);

   handle(create);

}


bool object::enable_system_events(bool bEnable)
{

   if(::is_null(m_papp))
   {

      return false;

   }

   if(!m_papp->enable_system_events(this, bEnable))
   {

      return false;

   }

   return true;

}


void object::request_file(var & varFile)
{

   sp(::handler) handler = get_app()->handler();

   sp(::create) create(canew(::create(handler)));

   create->m_spCommandLine->m_varFile              = varFile;

   request_create(create);

   varFile = create->m_spCommandLine->m_varFile;

}


void object::request_file_query(var & varFile,var & varQuery)
{

   sp(::handler) handler = get_app()->handler();

   sp(::create) create(canew(::create(handler)));

   create->m_spCommandLine->m_varFile              = varFile;

   create->m_spCommandLine->m_varQuery             = varQuery;

   if(!varFile.is_empty())
   {

      create->m_spCommandLine->m_ecommand = command_line::command_file_open;

   }
   else if (varQuery["command"] == "new_file")
   {

      create->m_spCommandLine->m_ecommand = command_line::command_file_new;

   }

   request_create(create);

   varFile                       = create->m_spCommandLine->m_varFile;

   varQuery                      = create->m_spCommandLine->m_varQuery;

}


void object::request_command(command_line * pcommandline)
{

   sp(::handler) handler = get_app()->handler();

   sp(::create) create(canew(::create(handler)));

   create->m_spCommandLine = pcommandline;

   request_create(create);

}


void object::request_create(::create * pcreate)
{

   on_request(pcreate);

}


void object::on_request(::create * pcreate)
{

   UNREFERENCED_PARAMETER(pcreate);

}






void object::set_app(::aura::application * papp)
{

   m_papp = papp;

}


void object::destruct()
{



}


void object::system(const char * pszProjectName)
{

   UNREFERENCED_PARAMETER(pszProjectName);

}


void object::safe_pre_term()
{
   
   if(string(m_id).contains("::rx"))
   {
      
      output_debug_string("::rx safe_pre_term");
      
   }
   if(string(m_id).contains("::ipi"))
   {
      
      output_debug_string("::ipi safe_pre_term");
      
   }

   post_quit();

   wait_quit(one_minute());

   release_parents();

}


void object::delete_this()
{

   if(string(m_id).contains("::rx"))
   {
      
      output_debug_string("::rx delete_this()");
      
   }

   safe_pre_term();

   if(m_pfactoryitembase != NULL && m_pfactoryitembase->m_pallocator)
   {

      m_pfactoryitembase->m_pallocator->discard(this);

   }
   else if(m_ulFlags & flag_discard_to_factory)
   {

      m_papp->m_psystem->discard_to_factory(this);

   }
   else if(is_heap())
   {

      simple_object::delete_this();

   }

}


object * object::clone()
{

   if(m_pfactoryitembase == NULL)
   {

      return NULL;

   }

   return m_pfactoryitembase->clone(this);

}

void object::defer_create_mutex()
{

   if (m_pmutex == NULL)
   {

      m_pmutex = new mutex(get_app());

   }

}



string object::lstr(id id, string strDefault)
{

   return m_papp->lstr(id,strDefault);

}



namespace aura
{


   allocatorsp::allocatorsp(::aura::application * papp)
   {

      allocator * pallocator = canew(allocator());

      pallocator->m_papp = papp;

      smart_pointer < allocator >::operator = (pallocator);

   }







} // namespace aura











void object::copy_this(const object & o)
{

   m_papp = o.m_papp;

   ::aura::del(m_psetObject);

   if (o.m_psetObject != NULL)
   {

      m_psetObject = new property_set(*o.m_psetObject);

   }

}


object & object::operator = (const object & o)
{

   if (&o == this)
   {

      return *this;

   }

   copy_this(o);

   return *this;

}




void object::on_handle(::command::command * pcommand)
{



}


void object::on_system_event(e_system_event eevent, lparam lparam)
{



}


void object::on_handle(::create * pcreate)
{




}


void object::children_post_quit()
{

   synch_lock sl(m_pmutex);

   try
   {

      if (::is_null(m_pchildren))
      {

         return;

      }

      sl.unlock();

      m_pchildren->post_quit(this);

   }
   catch (...)
   {

   }

}


void object::post_quit()
{

   try
   {

      release_children();

   }
   catch (...)
   {

   }

}


void object::wait_quit(duration durationTimeout)
{

   try
   {

      children_post_quit_and_wait(durationTimeout);

   }
   catch (...)
   {

   }

}


void object::children_wait_quit(::duration duration)
{

   try
   {

      synch_lock sl(m_pmutex);

      if (::is_null(m_pchildren) || m_pchildren->m_ptra.isEmpty())
      {

         return;

      }

      sl.unlock();

      m_pchildren->wait_quit(this, duration);

   }
   catch (...)
   {

   }

}


void object::children_post_quit_and_wait(duration durationTimeout)
{

   try
   {

      children_post_quit();

      children_wait_quit(durationTimeout);

   }
   catch (...)
   {

   }

}


void object::release_parents()
{

   try
   {

      synch_lock sl(m_pmutex);

      if (::is_set(m_pparents))
      {
         
         auto ptra = m_pparents->m_ptra;
         
         ::aura::del(m_pparents);
         
         sl.unlock();
         
         for (auto & pparent : ptra)
         {

            try
            {

               pparent->children_remove(this);

            }
            catch (...)
            {


            }

         }

      }
      
   }
   catch (...)
   {

   }

}

                  
void object::release_children()
{
   
   children_post_quit();

//   try
//   {
//
//      synch_lock sl(m_pmutex);
//
//      if (::is_set(m_pchildren))
//      {
//
//         for (auto & pchild : m_pchildren->m_ptra)
//         {
//
//            sl.unlock();
//
//            try
//            {
//
//               {
//
//                  synch_lock sl(pchild->m_pmutex);
//
//                  if(::is_set(pchild->m_pparents))
//                  {
//
//                     pchild->m_pparents->m_ptra.remove(this);
//
//                  }
//
//               }
//
//            }
//            catch (...)
//            {
//
//            }
//
//            sl.lock();
//
//         }
//
//      }
//
//   }
//   catch (...)
//   {
//
//   }

}

                  
void object::children_add(::object * pobjectChild)
{

   if (::is_null(pobjectChild))
   {

      return;

   }

   if (pobjectChild == this)
   {

      return;

   }

   if (children_is(pobjectChild))
   {

      return;

   }

   try
   {

   if (pobjectChild->children_is(this))
   {

      return;

   }
   }
   catch(...)
   {

   return;
   }

   {

      synch_lock sl(m_pmutex);

      if (::is_null(m_pchildren))
      {

         m_pchildren = new children;

      }

      m_pchildren->m_ptra.add(pobjectChild);

   }

   {

      synch_lock sl(pobjectChild->m_pmutex);

      if (::is_null(pobjectChild->m_pparents))
      {

         pobjectChild->m_pparents = new parents;

      }

      pobjectChild->m_pparents->m_ptra.add(this);

   }

}


/// tells if pobject is dependant of this object or of any dependant objects
bool object::children_is(::object * pobjectDescendantCandidate) const
{

   if (::is_null(pobjectDescendantCandidate))
   {

      return false;

   }

   synch_lock sl(m_pmutex);

   if (::is_null(m_pchildren))
   {

      return false;

   }

   for (auto & pobjectChild : m_pchildren->m_ptra)
   {

      if (pobjectChild == pobjectDescendantCandidate)
      {

         return true;

      }

   }

   for (auto & pobjectChild : m_pchildren->m_ptra)
   {

      sl.unlock();

      if (pobjectChild->children_is(pobjectDescendantCandidate))
      {

         return true;

      }

      sl.lock();

   }

   return false;

}


void object::children_remove(::object * pobjectChild)
{

   try
   {

      synch_lock sl(m_pmutex);

      if (::is_set(m_pchildren))
      {

         m_pchildren->m_ptra.remove(pobjectChild);

      }

   }
   catch (...)
   {


   }

//   if (bRemoveFromParent)
//   {
//
//      try
//      {
//
//         synch_lock sl(pobjectChild->m_pmutex);
//
//         if (::is_set(pobjectChild->m_pparents))
//         {
//
//            pobjectChild->m_pparents->m_ptra.remove(this);
//
//         }
//
//      }
//      catch (...)
//      {
//
//      }
//
//   }

}


parents::parents()
{

}


parents::~parents()
{

}


children::children()
{

}


children::~children()
{

}


void children::post_quit(::object * pobjectParent)
{

   synch_lock sl(pobjectParent->m_pmutex);

   try
   {

restart:

      for (index i = 0; i < m_ptra.get_count(); i++)
      {

         ::object * pobject = m_ptra[i];

         sl.unlock();

         try
         {

            /// this is quite dangerous
            //synch_lock slThread(pthread->m_pmutex);

            pobject->post_quit();

         }
         catch (...)
         {

            sl.lock();

            m_ptra.remove(pobject);

            goto restart;

         }

         sl.lock();

      }

   }
   catch (...)
   {

   }

}


#undef CHILD_SLEEP_MILLIS


//#define CHILD_SLEEP_MILLIS 50


::count children::_wait_quit(::object * pobjectParent)
{

   if (::is_null(pobjectParent))
   {

      return 0;

   }

   spa(object) ptraChildren;

   string strLog;

   try
   {

      synch_lock sl(pobjectParent->m_pmutex);

      ptraChildren = m_ptra;

      string strName = typeid(*pobjectParent).name();

      strLog += "\n ";
      strLog += "\n---------------------";
      strLog += "\n ";
      strLog += "\n   _wait_quit";
      strLog += "\n      " + strName;
      strLog += "\n      ";


   }
   catch (...)
   {

      return 0;

   }

   ::object * pobjectThread = ::get_thread();

   ptraChildren.remove(pobjectThread);

   ptraChildren.pred_remove([pobjectThread, pobjectParent](auto pobjectChild)
   {

      try
      {

         return pobjectChild->children_is(pobjectThread);

      }
      catch (...)
      {

      }

      try
      {

         synch_lock sl(pobjectParent->m_pmutex);

         pobjectParent->m_pchildren->m_ptra.remove(pobjectChild);

      }
      catch (...)
      {

         return true;

      }

      return true;

   });

   ::count cRemainingObjects = 0;

   try
   {

      synch_lock sl(pobjectParent->m_pmutex);

      for(index i = 0; i < ptraChildren.get_count(); i++)
      {

         sp(::object) pobjectChild = ptraChildren[i];

         if (pobjectChild.is_null())
         {

            continue;

         }

         sl.unlock();

         try
         {

            synch_lock ls(pobjectChild->m_pmutex);

            sp(thread) pthreadChild = pobjectChild;

            if (pthreadChild.is_set())
            {

               strLog += ::str::from((int_ptr)pthreadChild->get_os_int()) + " <-- thread id, ";

            }

            string strName = typeid(*pobjectChild.m_p).name();

            strLog += strName + "\n      ";

//            if (::is_set(pobjectChild->m_pchildren)
//                  && pobjectChild->m_pchildren->m_ptra.has_elements())
//            {
//
//               pobjectChild->m_pchildren->_wait_quit(pobjectChild);
//
//            }
//
            cRemainingObjects++;

         }
         catch (...)
         {

         }

         sl.lock();

      }

   }
   catch (...)
   {

   }

   strLog += "\n---------------------\n";
   strLog += "\n ";
   strLog += "\n ";

   ::aura::application * papp = ::aura::system::g_p;

   APPTRACE("%s", strLog);

   return cRemainingObjects;

}


/// returns remaining object, i.e., objects not yet destroyed
::count children::wait_quit(::object * pobjectParent, const duration & duration)
{

   ::count cRemainingObjects = 0;

   ::datetime::time timeStart = ::datetime::time::get_current_time();

   ::datetime::time timeEnd = timeStart + MAX(seconds(2), duration - m_durationWait);

   try
   {

      do
      {

         cRemainingObjects = _wait_quit(pobjectParent);

         if (cRemainingObjects <= 0)
         {

            break;

         }

         Sleep(50);

      }
      while (::datetime::time::get_current_time() < timeEnd);

   }
   catch (...)
   {

   }

   synch_lock sl(pobjectParent->m_pmutex);

   m_durationWait += ::datetime::time::get_current_time() - timeStart;

   return cRemainingObjects;

}


string object::__get_text(string str)
{

   if(get_app() == NULL)
   {

      return ::__get_text(str);

   }

   return Application.__get_text(str);

}




CLASS_DECL_AURA void one_shot_run(::object * pobjectRunnable)
{

   pobjectRunnable->run();

   ::release(pobjectRunnable);

}



