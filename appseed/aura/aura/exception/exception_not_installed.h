#pragma once


class CLASS_DECL_AURA not_installed : 
   virtual public ::exception::base
{
public:


   string      m_strAppId;
   string      m_strAppType;
   string      m_strBuild;
   string      m_strPlatform;
   string      m_strConfiguration;
   string      m_strLocale;
   string      m_strSchema;


   not_installed(::aura::application * papp, const char * pszAppId, const char * pszAppType, const char * pszBuild = NULL, const char * pszPlatform = NULL, const char * pszConfiguration = NULL, const char * pszLocale = NULL, const char * pszSchema = NULL);
   not_installed(const not_installed & e);
   virtual ~not_installed();


};
