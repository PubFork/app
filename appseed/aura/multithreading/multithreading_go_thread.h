#pragma once


class CLASS_DECL_AURA go_thread :
   virtual public simple_thread
{
public:


   go_thread(::aura::application * papp);
   virtual ~go_thread();
   

   virtual void start();

   virtual void run();
   
   virtual void go() = 0;

};
