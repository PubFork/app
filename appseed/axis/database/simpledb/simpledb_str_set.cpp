#include "framework.h"
//#include "axis/net/net_sockets.h"
//#include "db_str_set.h"
#include "aura/net/sockets/bsd/basic/sockets_socket_handler.h"
#include "aura/net/sockets/http/sockets_http_session.h"
#include "sqlite3.h"

class CLASS_DECL_AXIS db_str_set_item
{
public:


   uint32_t          m_dwTimeout;
   string            m_str;


};


class CLASS_DECL_AXIS db_str_set_queue_item :
   virtual public object
{
public:

   string            m_strKey;
   uint32_t          m_dwTimeout;
   string            m_str;


   db_str_set_queue_item() {}
   db_str_set_queue_item(const db_str_set_queue_item & item)
   {
      operator =(item);
   }
   virtual ~db_str_set_queue_item() {  }


   db_str_set_queue_item & operator = (const db_str_set_queue_item & item)
   {
      if (this != &item)
      {
         m_strKey = item.m_strKey;
         m_dwTimeout = item.m_dwTimeout;
         m_str = item.m_str;
      }
      return *this;
   }



};


class CLASS_DECL_AXIS db_str_set_core :
   virtual public ::db_set
{
public:


   sockets::socket_handler                      m_handler;
   sp(sockets::http_session)                    m_phttpsession;
   string_map < db_str_set_item >               m_map;
   bool                                         m_bIndexed;
   ::simpledb::database *                       m_psimpledbUser;
   string                                       m_strUser;
   int                                          m_iSelectId;
   int                                          m_iUpdateId;
   int                                          m_iUpdateVal;
   sp(class db_str_sync_queue)                  m_pqueue;
   sqlite3_stmt *                               m_pstmtSelect;
   sqlite3_stmt *                               m_pstmtUpdate;





   db_str_set_core(db_server * pserver) :
      ::object(pserver->get_app()),
      db_set(pserver, "stringtable"),
      m_handler(get_app()),
      m_phttpsession(NULL),
      m_pqueue(NULL),
      m_psimpledbUser(pserver->m_psimpledbUser),
      m_strUser(pserver->m_strUser)
   {
      m_pstmtSelect = NULL;
      m_pstmtUpdate = NULL;
      m_ptopthis = this;
      defer_create_mutex();

   }

   ~db_str_set_core()
   {
      if (m_pstmtSelect != NULL)
      {

         sqlite3_finalize(m_pstmtSelect);
         m_pstmtSelect = NULL;
      }
      if (m_pstmtUpdate != NULL)
      {

         sqlite3_finalize(m_pstmtUpdate);
         m_pstmtUpdate = NULL;
      }
   }


};


class CLASS_DECL_AXIS db_str_sync_queue :
   public simple_thread
{
public:

   mutex                                              m_mutex;
   db_str_set *                                       m_pset;
   sockets::socket_handler                            m_handler;
   sp(sockets::http_session)                          m_phttpsession;

   smart_pointer_array < db_str_set_queue_item >      m_itema;


   db_str_sync_queue(::aura::application * papp) :
      ::object(papp),
      thread(papp),
      simple_thread(papp),
      m_handler(papp),
      m_mutex(papp),
      m_phttpsession(NULL)
   { }

   virtual ~db_str_sync_queue() {}


   virtual void run();

   void queue(const char * pszKey, const char * psz);

};


void db_str_sync_queue::run()
{

   single_lock sl(&m_mutex, false);

   try
   {

      while (thread_get_run())
      {

         try
         {


            if (m_papp == NULL)
            {

               break;

            }

            if (m_papp->m_psession == NULL)
            {

               break;

            }

            if (m_papp->m_psession->m_pfontopus == NULL)
            {

               break;

            }

            if (&ApplicationUser == NULL)
            {

               Sleep(5000);

               continue;

            }

         }
         catch (...)
         {

            break;

         }

         sl.lock();

         if (m_itema.is_empty())
         {

            sl.unlock();

            Sleep(100);

            continue;

         }

         for (int32_t i = 1; i < m_itema.get_size(); i++)
         {

            if (m_itema[i]->m_strKey == m_itema[0]->m_strKey)
            {

               m_itema.remove_at(0);

               sl.unlock();

               continue;

            }

         }

         sp(db_str_set_queue_item) pitem = m_itema[0];

         m_itema.remove_at(0);

         sl.unlock();

         try
         {

            property_set set(get_app());

            string strUrl;

            set["interactive_user"] = true;

            strUrl = "https://ca2.cc/api/account/str_set_save?key=";

            strUrl += System.url().url_encode(pitem->m_strKey);

            strUrl += "&value=";

            strUrl += System.url().url_encode(pitem->m_str);

            set["user"] = &ApplicationUser;

            {

               single_lock slDatabase(m_pset->m_pcore->db()->get_database()->m_pmutex, true);

               Application.http().get(strUrl, set);

            }

            if (::http::status_failed(set["get_status"]))
            {

               Sleep(500);

               System.dir().m_strApiCc = "";

            }

         }
         catch (...)
         {

         }

      }

   }
   catch (...)
   {

   }

   ((db_str_set_core *)(m_pset->m_pcore->m_ptopthis))->m_pqueue = NULL;

}


void db_str_sync_queue::queue(const char * pszKey, const char * psz)
{

   single_lock sl(&m_mutex, true);

   sp(db_str_set_queue_item) item(canew(db_str_set_queue_item));

   item->m_strKey = pszKey;
   item->m_str = psz;

   m_itema.add(item);

}


db_str_set::db_str_set(db_server * pserver) :
   ::object(pserver->get_app())
{

   defer_create_mutex();
   m_pcore = canew(db_str_set_core(pserver));

}

db_str_set::~db_str_set()
{

}




// true if deleted
bool db_str_set::remove(const ::database::key & key)
{

   UNREFERENCED_PARAMETER(key);

   return false;

}


bool db_str_set::load(const ::database::key & key, string & strValue)
{

   synch_lock sl(m_pmutex);

   db_str_set_core * pcore = (db_str_set_core *)m_pcore->m_ptopthis;

   string strKey = key.m_strDataKey;

   strKey.replace("\\", "/");

   if (m_pcore->m_pdataserver == NULL)
   {

      return false;

   }

   if (m_pcore->m_pdataserver->m_bRemote && !key.m_bLocalData)
   {

      // Remote

      sl.unlock();

      Application.assert_user_logged_in();

      sl.lock();

      auto ppair = pcore->m_map.PLookup(strKey);

      if (ppair != NULL && ppair->m_element2.m_dwTimeout > get_tick_count())
      {

         strValue = ppair->m_element2.m_str;

         return true;

      }

      sl.unlock();

      //single_lock slDatabase(m_pcore->db()->get_database()->m_pmutex,true);

      //string xxx;
      //
      //if (&Session != NULL)
      //{
      //
      //   if (Session.fontopus())
      //   {

      //      if (Session.fontopus()->m_puser != NULL)
      //      {

      //         xxx = Session.fontopus()->m_puser->m_strFontopusServerSessId;

      //      }

      //   }

      //}

      {

         property_set set(get_app());

         set["interactive_user"] = true;

         string strUrl;

         strUrl = "https://ca2.cc/api/account/str_set_load?key=";

         strUrl += System.url().url_encode(strKey);

         set["user"] = &ApplicationUser;
         //set["timeout"] = 00;

         {

            //single_lock slDatabase(m_pcore->db()->get_database()->m_pmutex, true);

            strValue = Application.http().get(strUrl, set);

         }

         if (strValue.is_empty() || ::http::status_failed(set["get_status"]))
         {

            return false;

         }

      }

      {

         db_str_set_item stritem;

         stritem.m_dwTimeout = get_tick_count() + 23 * (5000);
         stritem.m_str = strValue;

         sl.lock();

         pcore->m_map.set_at(strKey, stritem);

      }


   }
#ifndef METROWIN
   else if (pcore->m_psimpledbUser != NULL)
   {

      try
      {

         strValue = pcore->m_psimpledbUser->query_item("SELECT `value` FROM fun_user_str_set WHERE user = '" + pcore->m_strUser + "' AND `key` = '" + pcore->m_psimpledbUser->real_escape_string(strKey) + "'");

         return true;

      }
      catch (...)
      {
      }

      return false;

   }
#endif
   else
   {

      // LOCAL (sqlite)

      sp(::sqlite::base) pdb = m_pcore->db()->get_database();

      //      ::sqlite::base * pdatabase = pdb->get_database();

      sync_object * pmutex = pdb->m_pmutex;

      //sl.unlock();

      synch_lock slDatabase(pmutex);

      if (pcore->m_pstmtSelect == NULL
            || pcore->m_iSelectId == 0)
      {


         if (pdb->setErr(sqlite3_prepare_v2(
                         (sqlite3 *)pdb->getHandle(),
                         "select `value` FROM `stringtable` WHERE `id` = :id;",
                         -1,
                         &pcore->m_pstmtSelect, NULL)) != SQLITE_OK)
         {

            pcore->m_pstmtSelect = NULL;

            return false;

         }

         pcore->m_iSelectId = sqlite3_bind_parameter_index(pcore->m_pstmtSelect, ":id");

      }
      else
      {

         sqlite3_reset(pcore->m_pstmtSelect);

      }

      int iLength = strKey.get_length();

      int res = sqlite3_bind_text(pcore->m_pstmtSelect, pcore->m_iSelectId, strKey, iLength, SQLITE_TRANSIENT);

      if (res != SQLITE_OK)
      {

         return false;

      }

      res = sqlite3_step(pcore->m_pstmtSelect);

      if (res != SQLITE_ROW)
      {

         var var = pdb->query_item("select `value` FROM stringtable WHERE `id` = '" + pdb->escape(strKey) + "'");

         if (!(bool)var)
            return false;

         return var.get_string();

      }

      const char * psz = (const char *)sqlite3_column_text(pcore->m_pstmtSelect, 0);

      strsize iLen = sqlite3_column_bytes(pcore->m_pstmtSelect, 0);

      strValue = string(psz, iLen);

      //sqlite3_reset(pcore->m_pstmtSelect);

   }

   return true;
}


bool db_str_set::save(const ::database::key & key, const string & strValue)
{

   db_str_set_core * pcore = (db_str_set_core *)m_pcore->m_ptopthis;

   string strKey = key.m_strDataKey;

   strKey.replace("\\", "/");

   if (m_pcore->m_pdataserver == NULL)
   {

      return false;

   }

   if (!m_pcore->m_pdataserver->m_bRemote || key.m_bLocalData)
   {

      if (m_pcore->db() == NULL)
      {

         return false;

      }

      sp(::sqlite::base) pdb = m_pcore->db()->get_database();

      string strSql;

      string str;

      string_map < db_str_set_item >::pair * pitem = NULL;

      {

         synch_lock sl(m_pmutex);

         pcore->m_map.PLookup(strKey);

      }

      string strLoad;

      string strEscapedValue;

      string strEscapedKey;

      {

         single_lock slDatabase(m_pcore->db()->get_database()->m_pmutex);

         strEscapedValue = m_pcore->db()->get_database()->escape(strValue);

         strEscapedKey = m_pcore->db()->get_database()->escape(strKey);

      }

      if (pitem != NULL || load(key, strLoad))
      {

         synch_lock sl(m_pmutex);

         if (pitem != NULL)
         {

            if (pitem->m_element2.m_str == strValue)
            {

               return true;

            }

         }
         else
         {

            if (strLoad == strValue)
            {

               return true;

            }

         }

         single_lock slDatabase(m_pcore->db()->get_database()->m_pmutex);

         {

            strSql.Format(
            "UPDATE stringtable SET value = '%s' WHERE id = '%s'",
            strEscapedValue,
            strEscapedKey);

            m_pcore->db()->get_database()->start_transaction();

            if (!m_pcore->m_pdataset->exec(strSql))
            {

               m_pcore->db()->get_database()->rollback_transaction();

               return false;

            }

            m_pcore->db()->get_database()->commit_transaction();

         }

      }
      else
      {

         single_lock slDatabase(m_pcore->db()->get_database()->m_pmutex);

         strSql.Format(
         "INSERT INTO stringtable (id, value) values ('%s', '%s');",
         strEscapedKey,
         strEscapedValue);

         m_pcore->db()->get_database()->start_transaction();

         if (!m_pcore->m_pdataset->exec(strSql))
         {

            m_pcore->db()->get_database()->rollback_transaction();

            return false;

         }

         m_pcore->db()->get_database()->commit_transaction();

      }

      if (pitem == NULL)
      {

         db_str_set_item stritem;

         stritem.m_dwTimeout = get_tick_count() + 23 * (5000);
         stritem.m_str = strValue;

         synch_lock sl(m_pmutex);

         pcore->m_map.set_at(strKey, stritem);

      }
      else
      {

         pitem->m_element2.m_dwTimeout = get_tick_count() + 23 * (5000);

      }

      return true;

   }
#ifdef HAVE_MYSQL
   else if (pcore->m_psimpledbUser != NULL)
   {

      string strSql = "REPLACE INTO fun_user_str_set VALUE('" + pcore->m_strUser + "', '" + pcore->m_psimpledbUser->real_escape_string(strKey) + "', '" + pcore->m_psimpledbUser->real_escape_string(strValue) + "')";

      TRACE(strSql);

      return pcore->m_psimpledbUser->query(strSql) != NULL;

   }
#endif
   else
   {

      if (pcore->m_pqueue == NULL)
      {

         pcore->m_pqueue = canew(db_str_sync_queue(get_app()));

         pcore->m_pqueue->m_pset = this;

         pcore->children_add(pcore->m_pqueue);

         pcore->m_pqueue->begin();

      }

      pcore->m_pqueue->queue(strKey, strValue);

      db_str_set_item stritem;

      stritem.m_dwTimeout = get_tick_count() + 23 * (5000);

      stritem.m_str = strValue;

      synch_lock sl(m_pmutex);

      pcore->m_map.set_at(strKey, stritem);

      return true;

   }

}

