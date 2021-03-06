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

   if (iSel < 0 || iSel >= System.m_pstrlangmap->m_straLang.get_count())
   {

      return false;

   }

   string strLang = System.m_pstrlangmap->m_straLang[iSel];

   if (strLang == System.m_pstrlangmap->m_strLang)
   {

      return true;

   }

   if (!set_current_language(strLang))
   {

      return false;

   }

   return true;

}


bool builtin_strlangmap::set_current_language(string strLang)
{

   return System.set_standalone_setting("current_language", strLang);

}


/// return selected language in the list
index builtin_strlangmap::get_language_list(stringa & stra)
{

   index iSel = -1;

   for (int i = 0; i < m_straLang.get_size(); i++)
   {

      if (m_straLang[i] == m_strLang)
      {

         iSel = i;

      }

      string strText = _get_text(m_pomap[m_straLang[i]].m_strLanguageCode, "IDS_LANGUAGE");

      stra.add(strText);

   }

   return iSel;

}





bool builtin_strlangmap::_load_text(string strLang)
{

   if (m_po[strLang].has_char())
   {

      return true;

   }

   auto & m = m_text[strLang];
   auto & h = m_header[strLang];

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

   int iStringCount = 0;

   string strLine;

   const char * psz = NULL;

   const char * pszEnd = NULL;

   string strName;

   string str;

   string strHeader;

   for (index i = 0; i < stra.get_count(); i++)
   {

      strLine = stra[i];

      psz = strLine;

      pszEnd = psz + strLine.get_length();

      ::str::consume_spaces(psz, 0, pszEnd);


      try
      {

         strName = ::str::consume_nc_name(psz);

         if (strName == "msgid")
         {

            iState = 0;

         }
         else if(strName == "msgstr")
         {

            iState = -1;

         }
         else if (strName.is_empty())
         {

            iState = 1;

         }

         ::str::consume_spaces(psz, 1, pszEnd);

         str = ::str::consume_quoted_value_ex(psz, pszEnd);

         i++;

         while (i < stra.get_count())
         {

            strLine = stra[i];

            psz = strLine;

            pszEnd = psz + strLine.get_length();

            ::str::consume_spaces(psz, 0, pszEnd);

            strName = ::str::consume_nc_name(psz);

            if (strName.has_char())
            {

               i--;

               break;

            }

            if (iStringCount == 0)
            {

               if (iStringCount <= 1)
               {

                  try
                  {

                     strHeader = ::str::consume_quoted_value_ex(psz, pszEnd);

                     if (strHeader.has_char())
                     {

                        stringa stra;

                        stra.explode(":", strHeader);

                        h[stra[0]] = stra.slice(1).implode(":");

                     }

                  }
                  catch (...)
                  {

                     if (iStringCount == 1)
                     {

                        iStringCount = 2;

                     }
                     else
                     {


                     }

                  }

               }


            }
            else
            {

               ::str::consume_spaces(psz, 0, pszEnd);

               str += ::str::consume_quoted_value_ex(psz, pszEnd);

            }

            i++;

         }

         str.replace("\\n", "\n");

         if (iState == 0)
         {

            strMsgId = str;

         }
         else if(iState == -1)
         {

            if (iStringCount > 0 || strMsgId.has_char() || strText.has_char())
            {

               m[strMsgId] = str;

               iStringCount++;

            }
            else if(iStringCount <= 0)
            {

               iStringCount = 1;

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


#elif defined(MACOS)


string load_pofile(string strLang)
{
   
   ::file::path pathFolder = ::aura::system::g_p->dir().module();
   
   pathFolder -= 1;
   
   ::file::path path = pathFolder / "Resources/po" / (strLang + ".po");
   
   return file_as_string_dup(path);
   
}


#else


string load_pofile(string strLang)
{

   ::file::path path = ::aura::system::g_p->dir().module() / "po" / (strLang + ".po");

   return file_as_string_dup(path);

}

#endif
