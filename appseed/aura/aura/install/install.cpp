#include "framework.h"


//#if defined()

//#ifdef LINUX

//#include <unistd.h>

//#endif




int32_t LangFromOS();





int32_t run_file(const char * pszFile, int32_t nCmdShow);









#ifdef SUPORTA_MATEMATICA_AVANCADA
double g_dPi = asin_dup(1.0) * 4;
#endif





namespace install
{

//   interaction_impl g_window;

} // namespace install









/*
string Login()
{
   if(stricmp_dup(g_pedit->m_str, "ca2") == 0
      && stricmp_dup(g_pedit->m_pnext->m_str, "ca2") == 0)
   {
      return "OK";
   }
   string document;
   string strPost;
   strPost = "entered_login=";
   strPost += g_pedit->m_str;
   strPost += "&entered_password=";
   strPost += g_pedit->m_pnext->m_str;
   document = ms_post("https://ca2os.com/ca2api/auth", strPost);
	return document;
}
*/



























string url_query_param(int32_t & iParam, const char * pszParam)
{
   string str;
   if(iParam == 0)
   {
      iParam++;
      str = "?";
      return str + pszParam;
   }
   else
   {
      iParam++;
      str = "&";
      return str + pszParam;
   }
}



