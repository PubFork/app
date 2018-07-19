#pragma once


namespace database
{


   class key;


   class CLASS_DECL_AXIS server :
      public client_array
   {
   public:


      bool                    m_bRemote;


      server(::aura::application * papp);
      virtual ~server();


      virtual bool data_server_load(client * pclient, key key, memory & mem, update_hint * phint = NULL);
      virtual bool data_server_load(client * pclient, key key, ::file::file & obj, update_hint * phint = NULL);
      virtual bool data_server_load(client * pclient, key key, serialize & serialize, update_hint * phint = NULL);
      virtual bool data_server_load(client * pclient, key key, object & obj, update_hint * phint = NULL);


      virtual bool data_server_save(client * pclient, key key, memory & mem, update_hint * phint = NULL);
      virtual bool data_server_save(client * pclient, key key, ::file::file & obj, update_hint * phint = NULL);
      virtual bool data_server_save(client * pclient, key key, serialize & serialize, update_hint * phint = NULL);
      virtual bool data_server_save(client * pclient, key key, object & obj, update_hint * phint = NULL);


      virtual bool data_pulse_change      (client * pclient, key key, update_hint * puh = NULL);


      virtual bool on_before_data_change  (client * pclient, key key, var & varNew, update_hint * puh = NULL);
      virtual bool on_after_data_change   (client * pclient, key key, update_hint * puh = NULL);


      virtual var data_load(client * pclient, key key, update_hint * phint = NULL);
      virtual bool data_save(client * pclient, key key, var & var, update_hint * phint = NULL);


   };


} // namespace database



