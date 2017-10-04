//
//  apple.cpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 21/07/17.
//
//

#include "framework.h"
#include "apple_main.h"

// ThomasBS-LiveEdu.TV(LiveCoding.TV)

void * CreateDispatchQueue()
{
   
   return dispatch_queue_create (NULL, NULL);
   
}

void CancelDispatchSource(void * p)
{
   
   dispatch_source_cancel((dispatch_source_t) p);
   
}

void * CreateDispatchTimer(uint64_t interval, uint64_t leeway, void * queue, void (*pfnTimer)(void * p), void * p)
{
   
   dispatch_source_t timer = dispatch_source_create(DISPATCH_SOURCE_TYPE_TIMER, 0, 0, (dispatch_queue_t) queue);
   
   if (timer)
   {
      
      dispatch_source_set_timer(timer, dispatch_walltime(DISPATCH_TIME_NOW, interval * NSEC_PER_MSEC), DISPATCH_TIME_FOREVER, leeway * NSEC_PER_MSEC);
      
      dispatch_source_set_event_handler(timer, ^(){ pfnTimer(p); });
      
      dispatch_resume(timer);
      
   }
   
   return timer;
   
}


void * ResetDispatchTimer(void * timerParam, uint64_t interval, uint64_t leeway)
{
   
   dispatch_source_t timer = (dispatch_source_t) timerParam;
   
   if (timer)
   {
      
      dispatch_source_set_timer(timer, dispatch_walltime(DISPATCH_TIME_NOW, interval * NSEC_PER_MSEC), DISPATCH_TIME_FOREVER, leeway * NSEC_PER_MSEC);
      
      //dispatch_resume(timer);
      
   }
   
   return timer;
   
}


void ReleaseDispatch(void * p)
{
   
   dispatch_release((dispatch_object_t) p);
   
}







int32_t defer_run_system()
{
   
   return __start_system_with_file(NULL);
   
}


int32_t defer_run_system(const char * pszFileName)
{
   
   return __start_system_with_file(pszFileName);
   
}


int32_t defer_run_system(char ** pszaFileName, int iFileCount)
{
   
   return __start_system_with_file((const char **) pszaFileName, iFileCount);
   
}





void apple_on_app_activate()
{
   
   ::aura::system::g_p->on_setting_changed(::aura::setting_app_activation);
   
}


void apple_on_new_file()
{
   
   ::aura::system::g_p->on_open_file(var::type_empty, "");
   
}

// iMillisDelay default 500ms good
void apple_accumulate_on_open_file(const char ** psza, int iCount, const char * pszExtra, int iMillisDelay)
{
   
   stringa stra;
   
   stra.c_add((char **) psza, iCount);
   
   ::aura::system::g_p->accumulate_on_open_file(stra, pszExtra, iMillisDelay);
   
}



void apple_on_open_file(const char ** psza, int iCount, const char * pszExtra)
{
   
   if(iCount <= 0)
   {
      
      apple_on_new_file();
      
   }
   else if(iCount == 1)
   {
      
      ::aura::system::g_p->on_open_file(psza[0], pszExtra);
      
      ::free((void *) psza[0]);
      
      ::free(psza);
      
   }
   else
   {
      
      stringa stra;
      
      stra.c_add((char **) psza, iCount);
      
      ::aura::system::g_p->on_open_file(stra, pszExtra);
      
   }
   
}


