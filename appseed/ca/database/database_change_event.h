#pragma once


#include "ca/database/database_key.h"


namespace database
{


   class server;
   class update_hint;


   class CLASS_DECL_ca change_event :
      public gen::signal_object
   {
   public:


      server *          m_pserver;
      key               m_key;
      update_hint *     m_puh;
      bool              m_bOk;
      var *             m_pvar;

      change_event();
      change_event(var & var);


      bool data_get(gen::byte_serializable & obj);


   };


} // namespace event


