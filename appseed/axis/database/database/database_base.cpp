#include "framework.h"

namespace database
{

   base::base()
   {
      active = false;   // No connection yet
      error = "";//S_NO_CONNECTION;
      host = "";
      port = "";
      db = "";
      login = "";
      passwd = "";
      sequence_table = "db_sequence";
      defer_create_mutex();
   }

   base::~base()
   {
      disconnect();      // Disconnect if connected to base
   }

   int32_t base::connectFull(const char *newHost, const char *newPort, const char *newDb, const char *newLogin, const char *newPasswd)
   {
      host = newHost;
      port = newPort;
      db = newDb;
      login = newLogin;
      passwd = newPasswd;
      return connect();
   }


   int32_t base::init()
   {

      return DB_COMMAND_OK;

   }
   void base::create_long_set(const string & strTable)
   {
   }

   void base::create_string_set(const string & strTable)
   {
   }




   var base::query_rows(const char * pszQuery)
   {

      synch_lock sl(m_pmutex);

      sp(set) s(CreateDataset());

      return s->query_rows(pszQuery);

   }


   var base::query_items(const char * pszQuery)
   {

      synch_lock sl(m_pmutex);

      sp(set) s(CreateDataset());

      return s->query_items(pszQuery);

   }


   var base::query_item(const char * pszQuery)
   {

      synch_lock sl(m_pmutex);

      sp(set) s(CreateDataset());

      return s->query_item(pszQuery);

   }


   bool base::query_rows(var & rows, const char * pszQuery)
   {

      synch_lock sl(m_pmutex);

      sp(set) s(CreateDataset());

      return s->query_rows(rows, pszQuery);

   }


   bool base::query_items(var & items, const char * pszQuery)
   {

      synch_lock sl(m_pmutex);

      sp(set) s(CreateDataset());

      return s->query_items(items, pszQuery);

   }


   bool base::query_item(var & item, const char * pszQuery)
   {

      synch_lock sl(m_pmutex);

      sp(set) s(CreateDataset());

      return s->query_item(item, pszQuery);

   }

} // namespace database

