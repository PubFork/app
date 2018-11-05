#include "framework.h"


namespace fontopus
{


   user::user(::aura::application * papp) :
      ::object(papp)
   {

      m_ppresence          = NULL;
      m_phttpcookies       = new ::http::cookies();
      m_pifs               = NULL;

      string strFormat;
      for(int32_t i = 0; i < 64; i += 2)
      {
         int64_t iDigit = System.math().RandRange(0,255);
         strFormat = ::hex::lower_pad_from(iDigit, 2);
         m_strSessionSecret += strFormat;
      }


   }

   user::~user()
   {
      if(m_phttpcookies != NULL)
         delete m_phttpcookies;
   }


   bool user::initialize()
   {

      if(&Session == NULL)
         return true;

      Session.defer_initialize_user_presence();

      return true;

   }


   bool user::create_ifs()
   {

      if(get_app()->is_system()
            || get_app()->is_system())
         return false;


      if(m_strLogin == system_user_1
            || m_strLogin == system_user_2)
         return false;


      if(m_pifs != NULL)
      {
         return true;
      }

      m_pifs = Session.m_pifs;

      return true;

   }


   string user::get_sessid(const char * pszText, bool bInteractive)
   {
      if(pszText == NULL)
      {
         pszText = "https://ca2.cc/";
      }
      string strText(pszText);
      if(strText.is_empty())
      {
         strText = "https://ca2.cc/";
      }
      strText = System.url().get_server(strText);
      if(strText.is_empty())
         strText = pszText;
      string strSessId;
      if (strText == "api.ca2.cc")
      {
         strSessId = Session.fontopus()->m_mapFontopusSessId[Session.fontopus()->m_strFirstFontopusServer];
         if (strSessId.has_char())
            return strSessId;

      }
      strSessId = m_sessionidmap[strText];
      if(strSessId.has_char())
         return strSessId;
      string strFontopusServer = Session.fontopus()->get_server(strText);
      if(strFontopusServer.has_char())
      {

         strSessId = Session.fontopus()->m_mapFontopusSessId[strFontopusServer];

         if(strSessId.has_char())
            return strSessId;

      }
      class validate authuser(get_app(), "system\\user\\authenticate.xhtml", true, bInteractive);
      sp(user) puser = authuser.get_user(pszText);
      if(puser == NULL)
         strSessId = "not_auth";
      else
      {
         strSessId = puser->m_strFontopusServerSessId;
         if(puser->m_strRequestingServer != strText)
            strSessId = "not_auth";
         else if(strSessId.is_empty())
            strSessId = "not_auth";
      }
      m_sessionidmap[strText] = strSessId;
      return strSessId;
   }

   void user::set_sessid(const char * pszSessid, const char * pszText)
   {
      if(pszText == NULL)
      {
         pszText = "https://ca2.cc/";
      }
      string strText(pszText);
      if(strText.is_empty())
      {
         strText = "https://ca2.cc/";
      }
      strText = System.url().get_server(strText);
      m_sessionidmap[strText] = pszSessid;
   }


   string user::get_ca2_server(const char * pszPrefix)
   {

      string strPrefix(pszPrefix);
      string strDomain(".ca2.cc");

      stringa straServer;

      straServer.add(strPrefix + strDomain);
      straServer.add("eu-" + strPrefix + strDomain);
      straServer.add("asia-" + strPrefix + strDomain);

      for(int32_t i = 0; i < 3; i++)
      {

         for(int32_t j = 0; j < straServer.get_size(); j++)
         {

            string strSessId = ApplicationUser.get_sessid(straServer[j]);

            if(strSessId != "not_auth")
            {

               return straServer[j];

            }

         }

      }

      return straServer[0];

   }


   string user::get_session_secret()
   {
      return m_strSessionSecret;
   }

} // namespace fontopus


