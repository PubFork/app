#include "framework.h"


pred_array::pred_array(::aura::application * papp)
{

}

pred_array::~pred_array()
{

}


void pred_array::run_all()
{

   for(auto & pred : *this)
   {

      if(!::get_thread_run())
      {

         break;

      }

      try
      {

         pred->run();

      }
      catch(...)
      {

      }

   }

}
