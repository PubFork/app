#include "framework.h"


namespace database
{


   server::server(::aura::application * papp) :
      object(papp)
   {

      defer_create_mutex();

   }


   server::~server()
   {

   }


   bool server::data_server_load(client * pclient, class id id, ::file::file & file, update_hint * puh)
   {

      memory mem;

      if (!data_server_load(pclient, id, mem, puh))
      {

         return false;

      }

      file.write(mem.get_data(), mem.get_size());

      return true;

   }


   bool server::data_server_load(client * pclient, class id id, memory & mem, update_hint * puh)
   {

#if MEMDLEAK

      mem.m_strTag = "memory://member=database::server::data_server_load(1)";

#endif

      return true;

   }


   bool server::data_server_load(client * pclient, class id id, serialize & serialize, update_hint * puh)
   {

      memory mem;

      if (!data_server_load(pclient, id, mem, puh))
      {

         return false;

      }

      serialize.write(mem.get_data(), mem.get_size());

      return true;

   }


   bool server::data_server_load(client * pclient, class id id, ::object & obj, update_hint * puh)
   {

      memory_reader reader(get_app());

      if (!data_server_load(pclient, id, reader.memory(), puh))
      {

         return false;

      }

      try
      {

         reader(obj);

      }
      catch(...)
      {

         return false;

      }

      return true;

   }


   bool server::data_server_save(client * pclient, class id id, ::file::file & file, update_hint * puh)
   {

      memory mem;

      mem.allocate(file.get_length() - file.get_position());

      file.read(mem.get_data(), mem.get_size());

      if (!data_server_save(pclient, id, mem, puh))
      {

         return false;

      }

      return true;

   }


   bool server::data_server_save(client * pclient, class id id, memory & mem, update_hint * puh)
   {

#if MEMDLEAK

      mem.m_strTag = "memory://member=database::server::data_server_save(1)";

#endif

      return true;

   }


   bool server::data_server_save(client * pclient, class id id, serialize & serialize, update_hint * puh)
   {

      memory mem;

      mem.allocate(serialize.get_left());

      serialize.read(mem.get_data(), mem.get_size());

      if (!data_server_save(pclient, id, mem, puh))
      {

         return false;

      }

      return true;

   }


   bool server::data_server_save(client * pclient, class id id, ::object & obj, update_hint * puh)
   {

      memory_writer writer(get_app());

      try
      {

         writer(obj);

      }
      catch (...)
      {

         return false;

      }

      if (!data_server_save(pclient, id, writer.memory(), puh))
      {

         return false;

      }

      return true;

   }


   bool server::data_pulse_change(client * pclient, class id id, update_hint * puh)
   {
      return on_after_data_change(pclient, id, puh);
   }


   bool server::on_before_data_change(client * pclient, class id id, var & var, update_hint * puh)
   {
      ::database::change_event signal(var);
      signal.m_pserver = this;
      signal.m_key.m_pclient = pclient;
      signal.m_key.m_id = id;
      signal.m_puh = puh;
      for(int32_t i = 0; i < client_array::get_count(); i++)
      {
         client_array::element_at(i)->data_on_before_change(&signal);
         if(!signal.m_bOk)
            return false;

      }
      return true;
   }

   bool server::on_after_data_change(client * pclient, class id id, update_hint * puh)
   {
      ::database::change_event signal;
      signal.m_pserver       = this;
      signal.m_key.m_pclient     = pclient;
      signal.m_key.m_id          = id;
      signal.m_puh = puh;
      for(int32_t i = 0; i < client_array::get_count(); i++)
      {
         client_array::element_at(i)->data_on_after_change(&signal);
      }
      return true;
   }

   //var server::data_load(client * pclient, class id id, update_hint * phint)
   //{
   //   var var;
   //   if(data_server_load(pclient, id, var, phint))
   //      return var;
   //   return ::var(::var::type_new);
   //}

   //bool server::data_save(client * pclient, class id id, var var, update_hint * phint)
   //{
   //   return data_server_save(pclient, id, var, phint);
   //}


   //bool server::var_load(client * pclient, class id id, serialize & serialize, update_hint * puh)
   //{

   //   string str;

   //   if (!data_server_load(pclient, id, str, puh))
   //   {

   //      return false;

   //   }

   //   memory m;

   //   System.

   //   ASSERT(serialize.is_storing());

   //   serialize(var);

   //   return true;

   //}


   //bool server::var_save(client * pclient, class id id, serialize & serialize, update_hint * puh)
   //{

   //   var var;

   //   ASSERT(!serialize.is_storing());

   //   serialize(var);

   //   if (!data_server_save(pclient, id, var, puh))
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   var server::data_load(client * pclient, class id id, update_hint * phint)
   {

      memory_reader reader(get_app());

      if (!data_server_load(pclient, id, reader.memory(), phint))
      {

         return var::type_null;

      }

      var var;

      reader(var);

      return var;

   }


   bool server::data_save(client * pclient, class id id, var & var, update_hint * phint)
   {

      memory_reader writer(get_app());

      writer(var);

      if (!data_server_load(pclient, id, writer.memory(), phint))
      {

         return false;

      }

      return true;

   }


} // namespace database
