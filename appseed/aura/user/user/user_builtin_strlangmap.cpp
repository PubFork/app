#include "framework.h"


#define STR_BOM "\xEF\xBB\xBF"

#ifdef WINDOWSEX
string load_pofile(int iId);
#else
string load_pofile(string strLang);
#endif

builtin_strlangmap::builtin_strlangmap(::aura::application * papp, STRLANGMAP * pmap) :
   ::object(papp)
{

   m_pmap = pmap;

   int i = 0;

   while (m_pmap[i].m_pszLanguageCode != NULL)
   {

      m_straLang.add(m_pmap[i].m_pszLanguageCode);

      m_pomap[m_pmap[i].m_pszLanguageCode].m_iPo = m_pmap[i].m_iPo;

      string strLanguageCode = m_pmap[i].m_pszLanguageCode;

      m_pomap[m_pmap[i].m_pszLanguageCode].m_strLanguageCode = strLanguageCode;

      i++;

   }


}



builtin_strlangmap::~builtin_strlangmap()
{


}


bool builtin_strlangmap::process_init()
{

   m_strLang = get_current_language();

   if (!m_straLang.contains_ci(m_strLang))
   {

      m_strLang = "en";

   }

   return true;

}


string builtin_strlangmap::get_current_language()
{

   return System.standalone_setting("current_language");

}


bool builtin_strlangmap::set_current_language(index iSel)
{

   if (iSel >= 0 && iSel < System.m_pstrlangmap->m_straLang.get_count())
   {

      string strLang = System.m_pstrlangmap->m_straLang[iSel];

      if (strLang != System.m_pstrlangmap->m_strLang)
      {

         if (!set_current_language(strLang))
         {

            return false;

         }

      }

      return true;

   }

}


bool builtin_strlangmap::set_current_language(string strLang)
{

   return System.set_standalone_setting("current_language", strLang);

}


#ifdef WINDOWSEX

void builtin_strlangmap::_001FillCombo(HWND hwnd)
{

   ::win32::window comboLang;

   comboLang.attach(hwnd);

   int iSel = CB_ERR;

   for (int i = 0; i < m_straLang.get_size(); i++)
   {

      if (m_straLang[i] == m_strLang)
      {

         iSel = i;

      }

      string strText = _get_text(m_pomap[m_straLang[i]].m_strLanguageCode, "IDS_LANGUAGE");

      wstring wstr(strText);

      //comboLang.send_message(CB_ADDSTRING, 0, (LPARAM)wstr.c_str());
      comboLang.send_message_w(CB_ADDSTRING, 0, (LPARAM)wstr.c_str());

   }

   comboLang.send_message(CB_SETCURSEL, iSel);

}

#endif


bool builtin_strlangmap::_load_text(string strLang)
{

   if (m_po[strLang].has_char())
   {

      return true;

   }

   auto & m = m_text[strLang];

#ifdef WINDOWSEX

   string strPo = load_pofile(m_pomap[strLang].m_iPo);

#else

   string strPo = load_pofile(strLang);

#endif

   ::str::begins_eat_ci(strPo, STR_BOM);

   stringa stra;

   stra.add_lines(strPo);
   int iState = -1;
   string strMsgId;
   string strText;

   avoid_parsing_exception avoidParsingException;

   for (index i = 0; i < stra.get_count(); i++)
   {
      string strLine = stra[i];

      const char * psz = strLine;
      const char * pszEnd = psz + strLine.get_length();

      ::str::consume_spaces(psz, 0, pszEnd);
      try
      {
         if (iState == -1)
         {
            strMsgId = ::str::consume_nc_name(psz);
            if (strMsgId == "msgid")
            {
               iState = 0;
               ::str::consume_spaces(psz, 1, pszEnd);
               strMsgId = ::str::consume_quoted_value_ex(psz, pszEnd);
            }
         }
         else if (iState == 0)
         {
            strText = ::str::consume_nc_name(psz);
            if (strText == "msgstr")
            {
               iState = -1;
               ::str::consume_spaces(psz, 1, pszEnd);
               strText = ::str::consume_quoted_value_ex(psz, pszEnd);
               m[strMsgId] = strText;
            }


         }
      }
      catch (...)
      {


      }
   }


   return true;

}



string builtin_strlangmap::_get_text(string strLang, string strId)
{

   _load_text(strLang);

   auto p = m_text.PLookup(strLang);

   if (p == NULL)
   {

      //         _load_text(strLang);

      //       p = m_text.PLookup(strLang);

      //     if (p == NULL)
      //   {

      //    return strId;

      //}

      if (is_debugger_attached())
      {

         ::file::path p1 = ::dir::home() / (".quasar_science_language_missing_" + strLang);

         string str1 = file_as_string_dup(p1);

         str1 += "\nmsgid\"" + strId + "\"\n";
         str1 += "\nmsgstr\"" + strId + "\"\n";
         str1 += "\n";

         file_put_contents_dup(p1, str1);

         m_text[strLang][strId] = "!" + strLang + ":" + strId;

      }

      return strId;

   }

   if (p->m_element2[strId].is_empty())
   {

      return strId;

   }

   return p->m_element2[strId];

}


string builtin_strlangmap::__get_text(string str)
{

   return _get_text(m_strLang, str);

}







#ifdef WINDOWSEX

string load_pofile(int iId)
{

   return read_resource_as_string_dup(NULL, iId, "PO");

}


#else

string load_pofile(string strLang)
{

   ::file::path path = ::dir::module() / "po" / (strLang + ".po");

   return file_as_string_dup(path);

}


#endif
