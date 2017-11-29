#include "framework.h"


simple_thread::simple_thread(::aura::application * papp) :
   object(papp),
   thread(papp)
{

//   set_auto_delete(false);

   m_dwFinishTimeout = 2000 * 30; // default

}


simple_thread::~simple_thread()
{
   
   ::multithreading::post_quit(this);

}


bool simple_thread::init_thread()
{

   return true;

}




