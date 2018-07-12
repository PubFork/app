#include "framework.h"


namespace database
{


   client::client()
   {

      m_bLocalDataModifier = false;
      m_pdataserver = NULL;

   }


   void client::initialize_data_client(server * pserver)
   {

      set_data_server(pserver);

   }


   bool client::set_data_server(server * pserver)
   {

      if(pserver != NULL)
      {

         synch_lock sl(pserver->m_pmutex);

         pserver->add_client(this);

      }

      m_pdataserver = pserver;

      return true;

   }


   client::~client()
   {

      if(m_pdataserver != NULL)
      {

         synch_lock sl(m_pdataserver->m_pmutex);

         try
         {

            m_pdataserver->remove_client(this);

         }
         catch(...)
         {

         }

      }

   }

   void client::data_on_before_change(::message::message * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void client::data_on_after_change(::message::message * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }


   bool client::data_set(class id id, bool b, update_hint * phint)
   {

      if (m_pdataserver != NULL)
      {

         memory_writer writer(get_app());

         writer(b);

         return m_pdataserver->data_server_save(this, id, writer.memory(), phint);

      }

      return false;

   }


   bool client::data_set(class id id, var & var, update_hint * puh)
   {

      if(m_pdataserver != NULL)
      {

         memory_writer writer(get_app());

         writer(var);

         return m_pdataserver->data_server_save(this, id, writer.memory(), puh);

      }

      return false;

   }


   bool client::data_set(class id id, float f, update_hint * puh)
   {

      if (m_pdataserver != NULL)
      {

         memory_writer writer(get_app());

         writer(f);

         return m_pdataserver->data_server_save(this, id, writer.memory(), puh);

      }

      return false;

   }


   bool client::data_set(class id id, int32_t i, update_hint * puh)
   {

      if(m_pdataserver != NULL)
      {

         memory_writer writer(get_app());

         writer(i);

         return m_pdataserver->data_server_save(this, id, writer.memory(), puh);

      }

      return false;

   }


   bool client::data_set(class id id, double d, update_hint * puh)
   {

      if (m_pdataserver != NULL)
      {

         memory_writer writer(get_app());

         writer(d);

         return m_pdataserver->data_server_save(this, id, writer.memory(), puh);

      }

      return false;

   }

   bool client::data_set(class id id, int64_t i, update_hint * puh)
   {

      if (m_pdataserver != NULL)
      {

         memory_writer writer(get_app());

         writer(i);

         return m_pdataserver->data_server_save(this, id, writer.memory(), puh);

      }

      return false;

   }

#ifdef APPLEOS

   bool client::data_set(class id id, long l, update_hint * puh)
   {

      if (m_pdataserver != NULL)
      {

         memory_writer writer(get_app());
         
         i64 i = l;

         writer(i);

         return m_pdataserver->data_server_save(this, id, writer.memory(), puh);

      }

      return false;

   }

#endif


   bool client::data_set(class id id, const char * lpsz, update_hint * puh)
   {

      if (m_pdataserver != NULL)
      {

         memory_writer writer(get_app());
         
         string str(lpsz);

         writer(str);

         return m_pdataserver->data_server_save(this, id, writer.memory(), puh);

      }

      return false;

   }

   bool client::data_set(class id id, const unichar * lpwsz, update_hint * puh)
   {

      if (m_pdataserver != NULL)
      {

         memory_writer writer(get_app());
         
         string str(lpwsz);

         writer(str);

         return m_pdataserver->data_server_save(this, id, writer.memory(), puh);

      }

      return false;

   }


   bool client::data_set(selection & selection, const char * lpsz, update_hint * puh)
   {

      ::count iCount = selection.get_item_count();

      bool bOk = true;

      for(index iItem = 0; iItem < iCount; iItem++)
      {

         selection_item & item = selection.get_item(iItem);

         if(!data_set(item.m_id, lpsz, puh))
         {

            bOk = false;

         }

      }

      return bOk;

   }


   bool client::data_set(selection & selection, var & var, update_hint * puh)
   {

      ::count iCount = selection.get_item_count();

      bool bOk = true;

      for(index iItem = 0; iItem < iCount; iItem++)
      {

         selection_item & item = selection.get_item(iItem);

         if(!data_set(item.m_id,var,puh))
         {

            bOk = false;

         }

      }

      return bOk;

   }


   bool client::data_set(class id id, ::file::file & readable, update_hint * puh)
   {

      if(m_pdataserver != NULL)
      {

         return m_pdataserver->data_server_save(this, id, readable, puh);

      }

      return false;

   }


   bool client::data_set(class id id, ::object & obj, update_hint * puh)
   {

      if(m_pdataserver != NULL)
      {

         if (!m_pdataserver->data_server_save(this, id, obj, puh))
         {

            return false;

         }

         return true;

      }

      return false;

   }


   bool client::data_set(class id id, serialize & serialize, update_hint * puh)
   {

      if(m_pdataserver != NULL)
      {

         return m_pdataserver->data_server_save(this, id, serialize, puh);

      }

      return false;

   }


   bool client::data_get(class id id, bool & b)
   {

      if (m_pdataserver != NULL)
      {

         memory_reader reader(get_app());

         if (!m_pdataserver->data_server_load(this, id, reader.memory()))
         {

            return false;

         }

         reader(b);

         return true;

      }

      return false;

   }


   bool client::data_get(class id id, var & var)
   {

      if (m_pdataserver != NULL)
      {

         memory_reader reader(get_app());

         if (!m_pdataserver->data_server_load(this, id, reader.memory()))
         {

            return false;

         }

         reader(var);

         return true;

      }

      return false;

   }


   bool client::data_get(class id id, float & f)
   {

      if (m_pdataserver != NULL)
      {

         memory_reader reader(get_app());

         if (!m_pdataserver->data_server_load(this, id, reader.memory()))
         {

            return false;

         }

         reader(f);

         return true;

      }

      return false;

   }


   bool client::data_get(class id id, int32_t & i)
   {

      if (m_pdataserver != NULL)
      {

         memory_reader reader(get_app());

         if (!m_pdataserver->data_server_load(this, id, reader.memory()))
         {

            return false;

         }

         reader(i);

         return true;

      }

      return false;

   }

   bool client::data_get(class id id, double & d)
   {

      if (m_pdataserver != NULL)
      {

         memory_reader reader(get_app());

         if (!m_pdataserver->data_server_load(this, id, reader.memory()))
         {

            return false;

         }

         reader(d);

         return true;

      }

      return false;

   }


   bool client::data_get(class id id, int64_t & i)
   {

      if (m_pdataserver != NULL)
      {

         memory_reader reader(get_app());

         if (!m_pdataserver->data_server_load(this, id, reader.memory()))
         {

            return false;

         }

         reader(i);

         return true;

      }

      return false;

   }

#ifdef APPLEOS

   bool client::data_get(class id id, long & l)
   {

      if (m_pdataserver != NULL)
      {

         memory_reader reader(get_app());

         if (!m_pdataserver->data_server_load(this, id, reader.memory()))
         {

            return false;

         }

         i64 i;
         
         reader(i);
         
         l = i;

         return true;

      }

      return false;

   }
#endif

   bool client::data_get(class id id, string & str)
   {

      if (m_pdataserver != NULL)
      {

         memory_reader reader(get_app());

         if (!m_pdataserver->data_server_load(this, id, reader.memory()))
         {

            return false;

         }

         reader(str);

         return true;

      }

      return false;

   }


   bool client::data_get(class id id, ::file::file & writable)
   {

      if (m_pdataserver != NULL)
      {

         if (!m_pdataserver->data_server_load(this, id, writable))
         {

            return false;

         }

         return true;

      }

      return false;

   }


   bool client::data_get(class id id, ::object & obj)
   {

      if (m_pdataserver != NULL)
      {

         if (!m_pdataserver->data_server_load(this, id, obj))
         {

            return false;

         }

         return true;

      }

      return false;

   }


   bool client::data_get(class id id, serialize & serialize)
   {

      if (m_pdataserver != NULL)
      {

         if (!m_pdataserver->data_server_load(this, id, serialize))
         {

            return false;

         }

         return true;

      }

      return false;

   }


   bool client::data_pulse_change(class id id, update_hint * puh)
   {

      if(m_pdataserver != NULL)
      {

         if (!m_pdataserver->data_pulse_change(this, id, puh))
         {

            return false;

         }

         return true;

      }

      return false;

   }


   client_array::client_array()
   {

   }


   client_array::~client_array()
   {

      for(int32_t i = 0; i < this->get_count(); i++)
      {

         this->element_at(i)->m_pdataserver = NULL;

      }

   }


   void client_array::add_client(client *pclient)
   {

      if(pclient != dynamic_cast < client * > (this))
      {

         add_unique(pclient);

      }

   }


   ::count client_array::get_client_count()
   {

      return this->get_size();

   }


   client * client_array::client_at(index iClient)
   {

      return this->element_at(iClient);

   }


   void client_array::remove_client(client *pclient)
   {

      remove(pclient);

   }


   string client::calc_data_key(::database::id & id)
   {

      string str;

      str = get_data_id();

      str += ".";

      str += ::str::from(id);

      return str;

   }


   id client::get_data_id()
   {

      if (m_dataid2.m_id.is_empty() || m_bDataKeyModified)
      {

         update_data_id();

      }

      return m_dataid2;

   }


   string client::calc_data_id()
   {

      return calc_default_data_id();

   }


   void client::update_data_id()
   {

      string strDataKey = calc_data_id();

      if (strDataKey.is_empty())
      {

         strDataKey = calc_default_data_id();

      }

      strDataKey += get_data_key_modifier();

      m_dataid2 = strDataKey;

      m_bDataKeyModified = false;

   }


   string client::calc_default_data_id()
   {

      string str;

      str = Application.m_strAppName;

      if (string(Application.get_data_id().m_id).find_ci("&data_source=local") >= 0)
      {

         str += "&data_source=local&";

      }
      else
      {

         str += "://";

      }

      str += calc_object_id();

      if (m_strDataKeyModifier.has_char())
      {

         str += "/";

         str += m_strDataKeyModifier;

      }

      return str;

   }


   void client::set_data_key_modifier(string strDataKeyModifier)
   {

      m_strDataKeyModifier = strDataKeyModifier;

      m_bDataKeyModified = true;

   }

   string client::get_data_key_modifier()
   {

      string strModifier = m_strDataKeyModifier;

      if (is_local_data())
      {

         strModifier += "&data_source=local&";

      }

      return strModifier;

   }


   void client::add_up_data_key_modifier(string strDataKeyModifier)
   {

      if (get_data_key_modifier().find_ci(strDataKeyModifier) < 0)
      {

         set_data_key_modifier(get_data_key_modifier() + strDataKeyModifier);

      }

   }


   void client::set_local_data_key_modifier()
   {

      m_bLocalDataModifier = true;

   }


   bool client::is_local_data()
   {

      return m_bLocalDataModifier || Application.is_local_data();

   }


} // namespace database



namespace file
{


   data_trigger_ostream::data_trigger_ostream(data_trigger_ostream && d):
      ::object(::move(d)),
      serialize(::move(d)),
      writer(::move(d)),
      memory_writer(::move(d)),
      m_id(::move(d.m_id))
   {

      m_pclient = d.m_pclient;
      d.m_pclient = NULL;

   }


   data_trigger_ostream::data_trigger_ostream(::database::client * pclient,class ::database::id id) :
      ::object(pclient->get_app()),
      ::serialize(pclient->get_app()),
      ::writer(pclient->get_app()),
      ::memory_writer(pclient->get_app())
   {

      m_id = id;

      m_pclient = pclient;

   }


   data_trigger_ostream::~data_trigger_ostream()
   {

      m_spfile->seek_to_begin();

      if(m_pclient != NULL)
      {

         ::reader reader(m_spfile);

         m_pclient->data_set(m_id, reader);

      }

   }


   data_trigger_istream::data_trigger_istream(data_trigger_istream && d) :
      ::object(::move(d)),
      serialize(::move(d)),
      reader(::move(d)),
      memory_reader(::move(d))
   {

   }


   data_trigger_istream::data_trigger_istream(::database::client * pclient,class ::database::id id) :
      ::object(pclient->get_app()),
      ::serialize(pclient->get_app()),
      ::reader(pclient->get_app()),
      ::memory_reader(pclient->get_app())
   {

      {

         ::writer writer(m_spfile);

         pclient->data_get(id, writer);

      }

      m_spfile->seek_to_begin();

   }


   data_trigger_istream::~data_trigger_istream()
   {

   }


} // namespace file


