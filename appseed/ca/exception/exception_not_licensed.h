#pragma once


class CLASS_DECL_ca not_licensed : 
   public base_exception
{
public:


   vsstring      m_strRealm;    // license realm
   vsstring      m_strUrl;      // licensing url


   not_licensed(const char * pszRealm, const char * pszUrl);
   not_licensed(const not_licensed & e);
   virtual ~not_licensed();


};
