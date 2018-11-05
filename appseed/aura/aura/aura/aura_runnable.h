#pragma once


class interlocked_long;


class CLASS_DECL_AURA runnable
{
public:


   interlocked_long *  m_pinterlockedlong;


   runnable();
   virtual ~runnable();


   interlocked_long & interlockedlong();

   virtual void run() = 0;


};
