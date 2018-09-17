#include "framework.h"


runnable::runnable()
{

   m_pinterlockedlong = NULL;

}


runnable::~runnable()
{

   if (m_pinterlockedlong != NULL)
   {

      delete m_pinterlockedlong;

   }

}


interlocked_long & runnable::interlockedlong()
{

   if (m_pinterlockedlong == NULL)
   {

      m_pinterlockedlong = new interlocked_long();

   }

   return *m_pinterlockedlong;

}