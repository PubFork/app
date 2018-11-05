#include "framework.h"


namespace database
{

   change_event::change_event() :
      m_pvar(NULL)
   {
      m_pserver = NULL;
      m_puh = NULL;
      m_bOk = true;
   }

   change_event::change_event(var & var) :
      m_pvar(&var)
   {
      m_pserver = NULL;
      m_puh = NULL;
      m_bOk = true;
   }

   bool change_event::data_get(::object & obj)
   {

      if(m_pserver != NULL)
      {

         return m_pclient->data_get(m_datakey, obj);

      }

      return false;

   }


} // namespace database

