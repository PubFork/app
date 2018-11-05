#pragma once




namespace http
{


   class CLASS_DECL_AURA application :
      virtual public ::message::receiver
   {
   public:


      ::property_set       m_setHttp;


      application();
      virtual ~application();


      property_set & process_set(property_set & set, const char * pszUrl);

      DECL_GEN_SIGNAL(get);

      virtual bool get(::sockets::socket_handler & handler, sp(::sockets::http_client_socket) & psocket, const char * pszUrl, property_set & set);

      virtual bool get(const char * pszUrl, primitive::memory_base & memory, property_set & set);
      virtual bool get(const char * pszUrl, string & str, property_set & set);
      virtual string api_get(const char * pszUrl, property_set & set);
      virtual string api_get(const char * pszUrl);

      virtual bool exists(const char * pszUrl, property_set & set);
      virtual bool is_file_or_dir(const char * pszUrl, var * pvarQuery, ::file::e_type * petype, property_set & set);

      virtual var length(const char * pszUrl, property_set & set);
      virtual var length(const char * pszUrl, var * pvarQuery, property_set & set);

      virtual string get(const char * pszUrl, property_set & set);

      virtual bool request(const char * pszRequest, const char * pszUrl, property_set & set);

      virtual bool download(::sockets::socket_handler & handler, sp(::sockets::http_session) & psession,const char * pszUrl, var varFile,property_set & set);
      virtual bool download(const char * pszUrl, var varFile, property_set & set);


      virtual bool put(const char * pszUrl, memory & memory, property_set & set);
      virtual bool put(const char * pszUrl, ::file::file_sp  pfile, property_set & set);

      virtual string locale_schema_url(const char * pszUrl, const char * pszLocale, const char * pszSchema);

      virtual string get_locale_schema(const char * pszUrl,const char * pszLocale,const char * pszSchema);

   };


} // namespace htttp
