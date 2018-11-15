#pragma once


namespace hi5
{


   class CLASS_DECL_SPHERE youtube_api :
      virtual public object
   {
   public:


      string      m_strApiProfile;

      DWORD       m_dwApiSleep;


      youtube_api(::aura::application * papp, const char * pszApiProfile);
      virtual ~youtube_api();


      virtual sync_object * get_api_mutex();

      virtual string get_local_path();

      virtual string youtube_api_token(bool bForce);

      virtual void log(string strOutput);

      virtual string randomDataBase64url(u32 uiLength);

      virtual memory sha256(string str);

      virtual string base64urlencodeNoPadding(memory m);

      virtual bool api_get(string strGet, var & var, property_set * pset);


   };


} // namespace hi5



