#include "framework.h"
#include "fiasco_finder.h"

//#ifndef SMALLCODE
//
//#include "Freeimage/FreeImage.h"
//
//#endif



void axis_on_init_thread();
void axis_on_term_thread();

int g_iAxisRefCount = 0;


CLASS_DECL_AXIS int get_axis_init()
{

   return g_iAxisRefCount;

}

::aura::system * axis_create_aura_system(app_core * pappcore)
{

   return new ::axis::system(NULL, pappcore);

}


CLASS_DECL_AXIS int_bool defer_axis_init()
{


   if(!defer_aura_init())
      return false;


   g_iAxisRefCount++;

   if(g_iAxisRefCount > 1)
      return TRUE;

   ::axis::static_start::init();

   if(!__node_axis_pre_init())
      return false;

   if(!axis_init())
      return false;

   if(!__node_axis_pos_init())
      return false;

   return true;

}


CLASS_DECL_AXIS int_bool defer_axis_term()
{

   g_iAxisRefCount--;

   if(g_iAxisRefCount >= 1)
      return TRUE;

   __node_axis_pre_term();

   axis_term();

   __node_axis_pos_term();

   ::axis::static_start::term();

   defer_aura_term();

   return TRUE;

}



bool axis_init()
{

   g_axisoninitthread = &axis_on_init_thread;
   g_axisontermthread = &axis_on_term_thread;

   g_pfn_create_system = &axis_create_aura_system;

   return true;

}


bool axis_term()
{

//#ifndef WINDOWS

//#ifdef BSD_STYLE_SOCKETS
//
//   ERR_remove_state(::GetCurrentProcessId());
//
//#endif

   // todo (casey tips) : do real/explicit dynamic linking
   //_throw(todo(get_app()));
   //try
   //{

   //   FreeImage_DeInitialise();

   //}
   //catch(...)
   //{

   //}
//#endif
   /*__wait_threading_count(::millis((5000) * 8));

   __node_axis_pre_term();
   */
//   ::user::term_windowing();
   /*
   ::multithreading::term_multithreading();

   __term_threading_count();

   __node_axis_pos_term();*/

//   ::axis::static_start::term();

   //defer_axis_term();

   return true;

}

void axis_on_init_thread()
{

}


void axis_on_term_thread()
{


}



