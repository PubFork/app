#pragma once


namespace database
{


   class client;


} // namespace database


namespace file
{


   class CLASS_DECL_AXIS data_trigger_ostream :
      virtual public memory_writer
   {
   public:


      ::database::client *    m_pclient;
      ::database::key         m_key;


      data_trigger_ostream(data_trigger_ostream && d);
      data_trigger_ostream(::database::client * pclient, class ::database::key);
      virtual ~data_trigger_ostream();


   };


   class CLASS_DECL_AXIS data_trigger_istream :
      virtual public memory_reader
   {
   public:


      data_trigger_istream(data_trigger_istream && d);
      data_trigger_istream(::database::client * pclient, class ::database::key );
      virtual ~data_trigger_istream();

   };


} // namespace file


namespace database
{


   class client_array;


   class CLASS_DECL_AXIS client :
      virtual public ::object
   {
   protected:

      /// Value to be add to data key on defer_update_data_id
      ::database::key            m_datakeyModifier;
      /// Cached Value from calc_data_id
      ::database::key            m_datakey;


   public:


      friend class client_array;
      friend class server;


      server *    m_pdataserver;


      client();
      virtual ~client();


      virtual bool set_data_server(server * pserver);


      void initialize_data_client(server * pserver);

      DECL_GEN_SIGNAL(data_on_before_change);
      DECL_GEN_SIGNAL(data_on_after_change);

      virtual bool data_set(key key, bool b, update_hint * phint = NULL);
      virtual bool data_set(key key, var & var, update_hint * puh = NULL);
      virtual bool data_set(key key, int32_t i, update_hint * puh = NULL);
      virtual bool data_set(key key, float f, update_hint * puh = NULL);
      virtual bool data_set(key key, int64_t i, update_hint * puh = NULL);
      virtual bool data_set(key key, double d, update_hint * puh = NULL);
#ifdef APPLEOS
      virtual bool data_set(key key, long l, update_hint * puh = NULL);
#endif
      virtual bool data_set(key key, const char * lpsz, update_hint * puh = NULL);
      virtual bool data_set(key key, const unichar * lpsz, update_hint * puh = NULL);
      virtual bool data_set(key key, ::file::file & obj, update_hint * puh = NULL);
      virtual bool data_set(key key, object & obj, update_hint * puh = NULL);
      virtual bool data_set(key key, serialize & serialize, update_hint * puh = NULL);
      virtual bool data_set(selection & selection, const char * lpsz, update_hint * puh = NULL);
      virtual bool data_set(selection & selection, var & var, update_hint * puh = NULL);

      template < typename T >
      inline bool data_save(key key, T & t)
      {
         try
         {

            ::file::data_trigger_ostream os(this,key);

            os(t);

         }
         catch(...)
         {
            return false;
         }
         return true;
      }


      virtual bool data_get(key key,  bool & b);
      virtual bool data_get(key key, var & var);
      virtual bool data_get(key key, int32_t & i);
      virtual bool data_get(key key, float & f);
      virtual bool data_get(key key, int64_t & i);
      virtual bool data_get(key key, double & d);
#ifdef APPLEOS
      virtual bool data_get(key key, long & l);
#endif
      virtual bool data_get(key key, string & str);
      virtual bool data_get(key key, ::file::file & obj);
      virtual bool data_get(key key, object & obj);
      virtual bool data_get(key key, serialize & obj);


      template < typename T >
      inline bool data_load(key key,T & t)
      {
         try
         {

            ::file::data_trigger_istream is(this, key);

            is(t);

            if(is.fail())
               return false;

         }
         catch(...)
         {
            return false;
         }
         return true;
      }

      virtual bool data_pulse_change(key key, update_hint * puh);


      virtual void set_data_key_modifier(::database::key key);


      virtual key calc_data_key(key key);


      virtual key calc_parent_data_key();
      virtual key calc_data_key();
      virtual void defer_update_data_key();
      virtual void update_data_key();
      virtual bool is_local_data();
      virtual void set_local_data(bool bLocalData = true);

   };


   class CLASS_DECL_AXIS client_array :
      public pointer_array < client * >
   {
   public:


      client_array();
      virtual ~client_array();


      virtual void add_client(client * pclient);
      virtual void remove_client(client * pclient);
      client * client_at(index iClient);
      ::count get_client_count();


   };


} // namespace database


