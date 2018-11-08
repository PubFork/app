#pragma once


namespace hi5
{


   class CLASS_DECL_CORE youtube_api :
      virtual public object
   {
   public:


      string      m_strApiProfile;

      DWORD       m_dwApiSleep;


      youtube_api(::aura::application * papp, const char * pszApiProfile);
      virtual ~youtube_api();


      virtual mutex * get_api_mutex() = 0;

      virtual string get_local_path() = 0;

      virtual string youtube_api_token(bool bForce);

      virtual void log(string strOutput);

      virtual string randomDataBase64url(u32 uiLength);

      virtual memory sha256(string str);

      virtual string base64urlencodeNoPadding(memory m);

      virtual bool api_get(string strGet, var & var, property_set * pset);


   };


} // namespace hi5



