#include "framework.h"


namespace database
{


   client::client()
   {

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


   bool client::data_set(key key, bool b, update_hint * phint)
   {

      if (m_pdataserver != NULL)
      {

         memory_writer writer(get_app());

         writer(b);

         return m_pdataserver->data_server_save(this, key, writer.get_memory(), phint);

      }

      return false;

   }


   bool client::data_set(key id, var & var, update_hint * puh)
   {

      if(m_pdataserver != NULL)
      {

         memory_writer writer(get_app());

         writer(var);

         return m_pdataserver->data_server_save(this, id, writer.get_memory(), puh);

      }

      return false;

   }


   bool client::data_set(key id, float f, update_hint * puh)
   {

      if (m_pdataserver != NULL)
      {

         memory_writer writer(get_app());

         writer(f);

         return m_pdataserver->data_server_save(this, id, writer.get_memory(), puh);

      }

      return false;

   }


   bool client::data_set(key id, int32_t i, update_hint * puh)
   {

      if(m_pdataserver != NULL)
      {

         memory_writer writer(get_app());

         writer(i);

         return m_pdataserver->data_server_save(this, id, writer.get_memory(), puh);

      }

      return false;

   }


   bool client::data_set(key id, double d, update_hint * puh)
   {

      if (m_pdataserver != NULL)
      {

         memory_writer writer(get_app());

         writer(d);

         return m_pdataserver->data_server_save(this, id, writer.get_memory(), puh);

      }

      return false;

   }

   bool client::data_set(key id, int64_t i, update_hint * puh)
   {

      if (m_pdataserver != NULL)
      {

         memory_writer writer(get_app());

         writer(i);

         return m_pdataserver->data_server_save(this, id, writer.get_memory(), puh);

      }

      return false;

   }

#ifdef APPLEOS

   bool client::data_set(key id, long l, update_hint * puh)
   {

      if (m_pdataserver != NULL)
      {

         memory_writer writer(get_app());

         i64 i = l;

         writer(i);

         return m_pdataserver->data_server_save(this, id, writer.get_memory(), puh);

      }

      return false;

   }

#endif


   bool client::data_set(key id, const char * lpsz, update_hint * puh)
   {

      if (m_pdataserver != NULL)
      {

         memory_writer writer(get_app());

         string str(lpsz);

         writer(str);

         return m_pdataserver->data_server_save(this, id, writer.get_memory(), puh);

      }

      return false;

   }

   bool client::data_set(key id, const unichar * lpwsz, update_hint * puh)
   {

      if (m_pdataserver != NULL)
      {

         memory_writer writer(get_app());

         string str(lpwsz);

         writer(str);

         return m_pdataserver->data_server_save(this, id, writer.get_memory(), puh);

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

         if(!data_set(item.m_datakey, lpsz, puh))
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

         if(!data_set(item.m_datakey,var,puh))
         {

            bOk = false;

         }

      }

      return bOk;

   }


   bool client::data_set(key id, ::file::file & readable, update_hint * puh)
   {

      if(m_pdataserver != NULL)
      {

         return m_pdataserver->data_server_save(this, id, readable, puh);

      }

      return false;

   }


   bool client::data_set(key id, ::object & obj, update_hint * puh)
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


   bool client::data_set(key id, serialize & serialize, update_hint * puh)
   {

      if(m_pdataserver != NULL)
      {

         return m_pdataserver->data_server_save(this, id, serialize, puh);

      }

      return false;

   }


   bool client::data_get(key id, bool & b)
   {

      if (m_pdataserver != NULL)
      {

         memory_reader reader(get_app());

         if (!m_pdataserver->data_server_load(this, id, reader.get_memory()))
         {

            return false;

         }

         reader(b);

         return true;

      }

      return false;

   }


   bool client::data_get(key id, var & var)
   {

      if (m_pdataserver != NULL)
      {

         memory_reader reader(get_app());

         if (!m_pdataserver->data_server_load(this, id, reader.get_memory()))
         {

            return false;

         }

         reader(var);

         return true;

      }

      return false;

   }


   bool client::data_get(key id, float & f)
   {

      if (m_pdataserver != NULL)
      {

         memory_reader reader(get_app());

         if (!m_pdataserver->data_server_load(this, id, reader.get_memory()))
         {

            return false;

         }

         reader(f);

         return true;

      }

      return false;

   }

   bool client::data_get(key id, int32_t & i)
   {

      if (m_pdataserver != NULL)
      {

         memory_reader reader(get_app());

         if (!m_pdataserver->data_server_load(this, id, reader.get_memory()))
         {

            return false;

         }

         reader(i);

         return true;

      }

      return false;

   }

   bool client::data_get(key id, double & d)
   {

      if (m_pdataserver != NULL)
      {

         memory_reader reader(get_app());

         if (!m_pdataserver->data_server_load(this, id, reader.get_memory()))
         {

            return false;

         }

         reader(d);

         return true;

      }

      return false;

   }


   bool client::data_get(key id, int64_t & i)
   {

      if (m_pdataserver != NULL)
      {

         memory_reader reader(get_app());

         if (!m_pdataserver->data_server_load(this, id, reader.get_memory()))
         {

            return false;

         }

         reader(i);

         return true;

      }

      return false;

   }

#ifdef APPLEOS

   bool client::data_get(key id, long & l)
   {

      if (m_pdataserver != NULL)
      {

         memory_reader reader(get_app());

         if (!m_pdataserver->data_server_load(this, id, reader.get_memory()))
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

   bool client::data_get(key id, string & str)
   {

      if (m_pdataserver != NULL)
      {

         memory_reader reader(get_app());

         if (!m_pdataserver->data_server_load(this, id, reader.get_memory()))
         {

            return false;

         }

         reader(str);

         return true;

      }

      return false;

   }


   bool client::data_get(key id, ::file::file & writable)
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


   bool client::data_get(key id, ::object & obj)
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


   bool client::data_get(key id, serialize & serialize)
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


   bool client::data_pulse_change(key id, update_hint * puh)
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


   void client::set_data_key_modifier(::database::key key)
   {

      m_datakeyModifier = key;

      m_datakey.m_strDataKey.Empty();

   }


   key client::calc_data_key(key datakey)
   {

      defer_update_data_key();

      return m_datakey + datakey;

   }


   key client::calc_parent_data_key()
   {

      return Application.calc_data_key();

   }


   key client::calc_data_key()
   {

      ::database::key key(calc_parent_data_key(), is_local_data());

      defer_update_object_id();

      key.m_strDataKey += "/" + m_id;

      return key;

   }

   void client::update_data_key()
   {

      m_datakey = calc_data_key() + m_datakeyModifier;

   }

   void client::defer_update_data_key()
   {

      if(m_datakey.m_strDataKey.is_empty())
      {

         update_data_key();

      }

   }


   bool client::is_local_data()
   {

      return m_datakey.m_bLocalData;

   }


   void client::set_local_data(bool bLocalData)
   {

      return m_datakey.set_local_data(bLocalData);

   }


} // namespace database



namespace file
{


   data_trigger_ostream::data_trigger_ostream(data_trigger_ostream && d):
      ::object(::move(d)),
      serialize(::move(d)),
      writer(::move(d)),
      memory_writer(::move(d)),
      m_key(::move(d.m_key))
   {

      m_pclient = d.m_pclient;
      d.m_pclient = NULL;

   }


   data_trigger_ostream::data_trigger_ostream(::database::client * pclient,class ::database::key key) :
      ::object(pclient->get_app()),
      ::serialize(pclient->get_app()),
      ::writer(pclient->get_app()),
      ::memory_writer(pclient->get_app())
   {

      m_key = key;

      m_pclient = pclient;

   }


   data_trigger_ostream::~data_trigger_ostream()
   {

      m_spfile->seek_to_begin();

      if(m_pclient != NULL)
      {

         ::reader reader(m_spfile);

         m_pclient->data_set(m_key, reader);

      }

   }


   data_trigger_istream::data_trigger_istream(data_trigger_istream && d) :
      ::object(::move(d)),
      serialize(::move(d)),
      reader(::move(d)),
      memory_reader(::move(d))
   {

   }


   data_trigger_istream::data_trigger_istream(::database::client * pclient,class ::database::key key) :
      ::object(pclient->get_app()),
      ::serialize(pclient->get_app()),
      ::reader(pclient->get_app()),
      ::memory_reader(pclient->get_app())
   {

      {

         ::writer writer(m_spfile);

         pclient->data_get(key, writer);

      }

      m_spfile->seek_to_begin();

   }


   data_trigger_istream::~data_trigger_istream()
   {

   }


} // namespace file


