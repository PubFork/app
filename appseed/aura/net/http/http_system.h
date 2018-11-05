#pragma once


class tinyjs;


namespace http
{


   class session;


   class CLASS_DECL_AURA system :
      virtual public ::message::receiver
   {
   public:


      class CLASS_DECL_AURA pac :
         virtual public ::object
      {
      public:


         string         m_strUrl;
         string         m_strAutoConfigScript;
         tinyjs *       m_pjs;
         uint32_t       m_dwLastChecked;


         pac(::aura::application * papp);
         virtual ~pac();


      };


      class CLASS_DECL_AURA proxy :
         virtual public ::object
      {
      public:


         string         m_strUrl;
         bool           m_bDirect;
         string         m_strProxy;
         int32_t        m_iPort;
         uint32_t       m_dwLastChecked;


         proxy(::aura::application * papp);


      };

      mutex *                                m_pmutexPac;
      string_map < sp(pac)  >                  m_mapPac;
      mutex *                                m_pmutexProxy;
      string_map < sp(proxy)  >                m_mapProxy;

      mutex *                                m_pmutexDownload;
      stringa                                m_straDownloading;
      stringa                                m_straExists;
      //::sockets::socket_handler *            m_phandler;



      system(::aura::application * papp);
      virtual ~system();

      DECL_GEN_SIGNAL(get);

      virtual bool get(::sockets::socket_handler & handler, sp(::sockets::http_client_socket) & m_psocket, const char * pszUrl, property_set & set);
      virtual bool get(::http::session & session, const char * pszUrl, string & str, property_set & set);
      virtual string get(::http::session & session, const char * pszUrl, property_set & set);


      virtual void set_proxy_auth(::fontopus::user * puser, ::sockets::http_client_socket * pfile);
      virtual void clean_proxy_auth(::fontopus::user * puser);


      virtual bool open(::sockets::socket_handler & handler, sp(::sockets::http_session) & psession, const char * pszHost,const char * pszProtocol, property_set & set,::fontopus::user * puser,const char * pszVersion);


      virtual bool request(::sockets::socket_handler & handler, sp(::sockets::http_session) & spsession,const char * pszUrl,property_set & set);

      virtual bool exists(const char * pszUrl, property_set & set);
      virtual bool is_file_or_dir(const char * pszUrl, property_set & set, ::file::e_type * petype = NULL);

      virtual var length(const char * pszUrl, property_set & set);

      virtual bool get(const char * pszUrl, property_set & set);

      virtual bool request(const char * pszMethod, const char * pszUrl, property_set & set);

      virtual bool download(::sockets::socket_handler & handler, sp(::sockets::http_session) & psession,const char * pszRequest, var varFile,property_set & set);
      virtual bool download(const char * pszUrl, var varFile, property_set & set);

      virtual bool put(const char * pszUrl, primitive::memory_base & memory, property_set & set);
      virtual bool put(const char * pszUrl, ::file::file_sp  pfile, property_set & set);

      virtual void defer_auto_initialize_proxy_configuration();
      virtual void auto_config_proxy(int32_t i);
      virtual int32_t auto_config_proxy_count();
      virtual void config_proxy(const char * pszUrl, ::sockets::http_tunnel * psocket);
      virtual void config_proxy(const char * pszUrl, proxy * pproxy);
      virtual bool try_pac_script(const char * pszScriptUrl, const char * pszUrl, proxy * pproxy);

      virtual string gmdate(time_t t);

      virtual pac * get_pac(const char * pszUrl);
      virtual proxy * get_proxy(const char * pszUrl);


   };


} // namespace http















