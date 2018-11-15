#include "framework.h"


#define DEBUG_THROTTLE 0
#define PARALLEL_UPDATE_USER 1


namespace hi5
{


   youtube_api::youtube_api(::aura::application * papp, const char * pszApiProfile) :
      ::object(papp),
      m_strApiProfile(pszApiProfile)
   {

      m_dwApiSleep = 800;

   }


   youtube_api::~youtube_api()
   {
   }


   sync_object * youtube_api::get_api_mutex()
   {

      defer_create_mutex();

      return m_pmutex;

   }


   string youtube_api::get_local_path()
   {

      return System.defer_process_matter_path("appconfig://youtube_api", get_app());

   }


   string youtube_api::youtube_api_token(bool bForce)
   {

      string strClientId;
      string strSecret;
      string strRedirectUri;
      string strAuthUri;

      if (1)
      {

#include "youtube_api.txt"

         const char * pszSecret =
#include "youtube_secret!!.txt"
         ;

         strClientId = pszClientId;

         strSecret = pszSecret;

         strAuthUri = pszAuthUri;

         strRedirectUri = pszRedirectUris;

      }

      string strCode;

      string strToken;

      if (!bForce)
      {

         strCode = Application.file().as_string(get_local_path() / "youtube_token_" + m_strApiProfile + ".txt");

         if (strCode.has_char())
         {

            return strCode;

         }

      }

      string strState = randomDataBase64url(32);
      string strCodeVerifier = randomDataBase64url(32);
      string strCodeChallenge = base64urlencodeNoPadding(sha256(strCodeVerifier));
      string strCodeChallengeMethod = "S256";

      log("redirect URI: " + strRedirectUri);

      string strAuthorizationRequest;

      string strScope = "https://www.googleapis.com/auth/youtube";

      strAuthorizationRequest = strAuthUri + "?response_type=code&scope=" +
                                System.url().url_encode(strScope) + "&redirect_uri="
                                +
                                System.url().url_encode(strRedirectUri)
                                + "&client_id=" +
                                strClientId
                                + "&state=" +
                                strState
                                + "&code_challenge=" +
                                strCodeChallenge +
                                +"&code_challenge_method=" +
                                strCodeChallengeMethod;


      string strBrowser;

      if (m_strApiProfile == "bot")
      {

         strBrowser = "ca2bot";

      }
      else
      {

         strBrowser = "native";

      }

      System.open_link(strAuthorizationRequest, strBrowser, "youtube_browser");

      {

         int iRetry = 100;

         string strUrl = "https://ca2.cc/api/account/get_string?key=" + System.url().url_encode("youtube_resident." + strState);

         while (::get_thread_run() && iRetry > 0)
         {

            {

               ::property_set set;

               set["raw_http"] = true;

               strCode = Application.http().get(strUrl, set);

               if (strCode.has_char())
               {

                  break;

               }

            }

            Sleep(1000);

            iRetry--;

         }

      }

      if (!::get_thread_run())
      {

         return "";

      }

      log("Exchanging code for tokens...");

      // builds the  request
      string strTokenRequestUri = "https://www.googleapis.com/oauth2/v4/token";
      //string strTokenRequestBody;

      //strTokenRequestBody.Format("code=%s&redirect_uri=%s&client_id=%s&code_verifier=%s&client_secret=%s&scope=&grant_type=authorization_code",
      //                           strCode,
      //                           System.url().url_encode(strRedirectUri),
      //                           strClientId,
      //                           strCodeVerifier,
      //                           strSecret
      //                          );

      property_set setToken;
      setToken["post"]["code"] = strCode;
      setToken["post"]["redirect_uri"] = strRedirectUri;
      setToken["post"]["client_id"] = strClientId;
      setToken["post"]["code_verifier"] = strCodeVerifier;
      setToken["post"]["client_secret"] = strSecret;
      setToken["post"]["grant_type"] = "authorization_code";
      setToken["headers"]["accept"] = "application/json";

      string strJson = Application.http().get(strTokenRequestUri, setToken);

      ::property_set setResp;

      const char * pszJson = strJson;

      setResp.parse_json(pszJson);

      strToken = setResp["access_token"];

      string strRefresh = setResp["refresh_token"];

      Application.file().put_contents(get_local_path() / "youtube_token_" + m_strApiProfile + ".txt", strToken);

      Application.file().put_contents(get_local_path() / "youtube_refresh_" + m_strApiProfile + ".txt", strRefresh);

      return strToken;

   }


   bool youtube_api::api_get(string strGet, var & var, property_set * pset)
   {

      synch_lock sl(get_api_mutex());

      ::property_set setHttp;

      if (pset == NULL)
      {

         pset = &setHttp;

      }

      ::property_set &set = *pset;

      bool bForce = false;

      string strResponse;

retry:

      set["raw_http"] = true;

      set["disable_common_name_cert_check"] = true;

      string strApiProfile = m_strApiProfile;

      string strToken = youtube_api_token(bForce);

      set["headers"]["Authorization"] = "Bearer " + strToken;

      set["headers"]["accept"] = "application/json";

      if (!str::begins_ci(strGet, "https://"))
      {

         strGet = "https://www.googleapis.com" + strGet;

      }

      strResponse = Application.http().get(strGet, set);

      int iStatusCode = set["http_status_code"].i32();

      if (pset != NULL)
      {

         *pset = set;

      }

      if (iStatusCode == 429 || DEBUG_THROTTLE != 0)
      {

         string strDetail = var["detail"];

         if (strDetail.find_ci("throttled") >= 0 || DEBUG_THROTTLE != 0)
         {

            output_debug_string(strDetail);

#if DEBUG_THROTTLE != 0

            double iMillis = DEBUG_THROTTLE * 1000;

#else
            strsize iFind = strDetail.find_ci("second");

            iFind--;
            while (iFind >= 0 && (isspace_dup(strDetail[iFind])))
            {
               iFind--;
            }
            while (iFind >= 0 && (isdigit_dup(strDetail[iFind]) || strDetail[iFind] == '.'))
            {
               iFind--;
            }

            string strSeconds = strDetail.Mid(iFind);

            double iMillis = atof(strSeconds) * 1500.0 + 5000.0;


#endif

            Application.oprop("seconds") = 0;
            Application.oprop("total_seconds") = iMillis / 1000.0;

            bForce = false;

            DWORD dwStart = get_tick_count();

            while (get_tick_count() - dwStart < iMillis)
            {

               Sleep(25);

               Application.oprop("seconds") = (iMillis - (get_tick_count() - dwStart)) / 1000.0;

            }


            Application.oprop("seconds") = 0.0;
            Application.oprop("total_seconds") = 0.0;

            goto retry;

         }

      }

      if (iStatusCode == 400)
      {

         TRACE("%s", strResponse);

      }
      else if (iStatusCode != 200 || strResponse.is_empty())
      {

         if (!bForce)
         {

            bForce = true;

            goto retry;

         }
         else
         {
            return false;

         }

      }

      const char * pszJson = strResponse;

      var.parse_json(pszJson);

      Sleep(m_dwApiSleep);

      return true;

   }


   void youtube_api::log(string str)
   {

      TRACE("resident_youtube_api: %s", str);

   }


   string youtube_api::randomDataBase64url(u32 length)
   {

      memory m;

      m.random_bytes(length);

      return base64urlencodeNoPadding(m);

   }


   memory youtube_api::sha256(string inputStirng)
   {

      memory m;

      m.from_asc(inputStirng);

      memory mDst;

      System.crypto().sha256(mDst, m);

      return mDst;

   }


   string youtube_api::base64urlencodeNoPadding(memory m)
   {

      string str = System.base64().encode(m);

      // Converts base64 to base64url.
      str.replace("+", "-");
      str.replace("/", "_");
      // Strips padding.
      str.replace("=", "");

      return str;

   }


} // namespace hi5



