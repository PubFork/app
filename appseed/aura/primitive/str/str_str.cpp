#include "framework.h"
#include <stdio.h>






namespace hex
{

   uint16_t parse_uint16_exc(const char * & psz, const char * pszEnd)
   {
      string strUni;
      const char * pszNext = psz;
      for (index i = 0; i < 4; i++)
      {
         psz = pszNext;
         pszNext = ::str::__utf8_inc(psz);
         if (pszNext > pszEnd)
         {
            throw_parsing_exception("hexadecimal digit expected, premature end");
            return -1;
         }
         if ((pszNext - psz == 1) && ((*psz >= '0' && *psz <= '9') || (*psz >= 'A' && *psz <= 'F') || (*psz >= 'a' && *psz <= 'f')))
         {
            strUni += *psz;
         }
         else
         {
            throw_parsing_exception("hexadecimal digit expect expected here");
            return -1;
         }
      }
      psz = pszNext;
      return ::hex::to_uint(strUni);

   }

}

#ifdef LINUX
////#include <ctype.h>
#endif
//bool is_high_surrogate(uint16_t ui)
//{
//   return ui >= 0xD800 && ui <= 0xDBFF;
//
//}
//bool is_low_surrogate(uint16_t ui)
//{
//   return ui >= 0xDC00 && ui <= 0xDFFF;
//}
//CLASS_DECL_AURA bool is_surrogated(uint32_t character)
//{
//   return 0x10000 <= character && character <= 0x10FFFF;
//}
CLASS_DECL_AURA void
encode_utf16_pair(uint32_t character, uint16_t *units)
{
   unsigned int code;
   ASSERT(is_surrogated(character));
   code = (character - 0x10000);
   units[0] = 0xD800 | (code >> 10);
   units[1] = 0xDC00 | (code & 0x3FF);
}

uint32_t
decode_utf16_pair(uint16_t *units)
{
   uint32_t code;
   ASSERT(is_high_surrogate(units[0]));
   ASSERT(is_low_surrogate(units[1]));
   code = 0x10000;
   code += (units[0] & 0x03FF) << 10;
   code += (units[1] & 0x03FF);
   return code;
}
namespace str
{

   CLASS_DECL_AURA e_err g_eerr = err_none;


//    const char trailingBytesForUTF8[256] =
//    {
//       (const char)  -1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//       0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//       0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//       0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//       0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//       0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//       1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
//       2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, 3,3,3,3,3,3,3,3,4,4,4,4,5,5,5,5
//    };

   //void          make_lower(char * psz)
   //{

   //   while (*psz)
   //   {
   //      *psz = tolower(*psz);
   //      psz++;
   //   }

   //}


   //void          make_upper(char * psz)
   //{

   //   while (*psz)
   //   {
   //      *psz = toupper(*psz);
   //      psz++;
   //   }

   //}


   int32_t  compare(const char * psz1, const char * psz2)
   {
      return strcmp(psz1, psz2);
   }

   int32_t  compare_ci(const char * psz1, const char * psz2)
   {
      return stricmp_dup(psz1, psz2);
   }

   bool equals(const char * psz1, const char * psz2)
   {
      return compare(psz1, psz2) == 0;
   }

   bool equals_ci(const char * psz1, const char * psz2)
   {
      return compare_ci(psz1, psz2) == 0;
   }

   string  equals_get(const char * psz1, const char * psz2, const char * pszGetOnEqual, const char * pszGetOnDifferent)
   {
      return equals(psz1, psz2) ? pszGetOnEqual : pszGetOnDifferent;
   }

   string  equals_ci_get(const char * psz1, const char * psz2, const char * pszGetOnEqual, const char * pszGetOnDifferent)
   {
      return equals_ci(psz1, psz2) ? pszGetOnEqual : pszGetOnDifferent;
   }

   bool begins(const char * lpcsz, const char * lpcszPrefix)
   {
      if(lpcsz == NULL || *lpcsz == '\0')
      {
         if(lpcszPrefix == NULL || *lpcszPrefix == '\0')
         {
            return true;
         }
         else
         {
            return false;
         }
      }
      while(*lpcsz == *lpcszPrefix)
      {
         lpcsz++;
         lpcszPrefix++;
         if(*lpcsz == '\0')
         {
            if(*lpcszPrefix == '\0')
               return true;
            else
               return false;
         }
         else if(*lpcszPrefix == '\0')
         {
            return true;
         }
      }
      return false;
   }

   bool begins_with(const char * lpcsz, const char * lpcszPrefix)
   {
      return begins(lpcsz, lpcszPrefix);
   }

   bool begins(const string & str, const char * lpcszPrefix)
   {
      if(str.is_empty())
      {
         if(lpcszPrefix == NULL || *lpcszPrefix == '\0')
         {
            return true;
         }
         else
         {
            return false;
         }
      }
      const char * lpcsz = str;
      while(*lpcsz == *lpcszPrefix)
      {
         lpcsz++;
         lpcszPrefix++;
         if(*lpcsz == '\0')
         {
            if(*lpcszPrefix == '\0')
               return true;
            else
               return false;
         }
         else if(*lpcszPrefix == '\0')
         {
            return true;
         }
      }
      return false;
   }

   bool begins_with(const string & str, const char * lpcszPrefix)
   {
      return begins(str, lpcszPrefix);
   }

   bool begins_ci(const char * lpcsz, const char * lpcszPrefix)
   {
      if(lpcsz == NULL || *lpcsz == '\0')
      {
         if(lpcszPrefix == NULL || *lpcszPrefix == '\0')
         {
            return true;
         }
         else
         {
            return false;
         }
      }
      while(tolower((byte) *lpcsz) == tolower((byte)*lpcszPrefix))
      {
         lpcsz++;
         lpcszPrefix++;
         if(*lpcsz == '\0')
         {
            if(*lpcszPrefix == '\0')
               return true;
            else
               return false;
         }
         else if(*lpcszPrefix == '\0')
         {
            return true;
         }
      }
      return false;
   }

   // case insensitive, ignore white space - only in searched string
   bool begins_ci_iws(const char * lpcsz, const char * lpcszPrefix)
   {
      if(lpcsz == NULL || *lpcsz == '\0')
      {
         if(lpcszPrefix == NULL || *lpcszPrefix == '\0')
         {
            return true;
         }
         else
         {
            return false;
         }
      }
      while(*lpcsz && isspace((byte) *lpcsz))
         lpcsz++;
      if(!*lpcsz)
         return false;
      while(tolower(*lpcsz) == tolower((byte) *lpcszPrefix))
      {
         lpcsz++;
         lpcszPrefix++;
         if(*lpcsz == '\0')
         {
            if(*lpcszPrefix == '\0')
               return true;
            else
               return false;
         }
         else if(*lpcszPrefix == '\0')
         {
            return true;
         }
      }
      return false;
   }

   bool begins_ci_iws(const string & str, const char * lpcszPrefix)
   {
      return begins_ci_iws(str.c_str(), lpcszPrefix);
   }


   bool eat_before(string & strBefore, string strSeparator, string & str, bool bEatEverythingIfNotFound)
   {

      ASSERT(&str != &strBefore);

      if (&str == &strBefore)
      {

         return false;

      }

      index iFind = str.find(strSeparator);

      if (iFind < 0)
      {

         if (bEatEverythingIfNotFound)
         {

            strBefore = str;

            str.Empty();

         }

         return false;

      }

      strBefore = str.Left(iFind);

      str = str.Mid(iFind + strSeparator.length());

      return true;

   }


   bool eat_before_let_separator(string & strBefore, string strSeparator, string & str, bool bEatEverythingIfNotFound)
   {

      ASSERT(&str != &strBefore);

      if (&str == &strBefore)
      {

         return false;

      }

      index iFind = str.find(strSeparator);

      if (iFind < 0)
      {

         if (bEatEverythingIfNotFound)
         {

            strBefore = str;

            str = strSeparator;

         }

         return false;

      }

      strBefore = str.Left(iFind);

      str = str.Mid(iFind);

      return true;

   }




   bool begins_eat(string & str, const char * lpcszPrefix)
   {

      string strPrefix(lpcszPrefix);

      strsize iLen = strPrefix.get_length();

      if(str.Left(iLen) == lpcszPrefix)
      {
         str = str.Mid(iLen);
         return true;
      }

      return false;

   }

   bool begins_eat_ci(string & str, const char * lpcszPrefix)
   {

      if(lpcszPrefix == NULL)
         return true;

      string strPrefix(lpcszPrefix);

      strsize iLen = strPrefix.get_length();

      if(str.Left(iLen).compare_ci(lpcszPrefix) == 0)
      {
         str = str.Mid(iLen);
         return true;
      }

      return false;

   }

   bool begins_eat_ci(string & str, const char * lpcszPrefix, const char * pszSeparator)
   {
      if(str.compare_ci(lpcszPrefix) == 0)
      {
         str.Empty();
         return true;
      }
      else
      {
         return begins_eat_ci(str, string(lpcszPrefix) + pszSeparator);
      }
   }

   bool ends(const char * lpcsz, const char * lpcszSuffix)
   {
      if(lpcsz == NULL || *lpcsz == '\0')
      {
         if(lpcszSuffix == NULL || *lpcszSuffix == '\0')
            return true;
         else
            return false;
      }
      else if(lpcszSuffix == NULL || *lpcszSuffix == '\0')
      {
         return true;
      }
      const char * lpcszEnd = lpcsz;
      const char * lpcszSuffixEnd = lpcszSuffix;
      while(*lpcszEnd)
         lpcszEnd++;
      while(*lpcszSuffixEnd)
         lpcszSuffixEnd++;
      if((lpcszSuffixEnd - lpcszSuffix) > (lpcszEnd - lpcsz))
         return false;
      while(lpcszSuffixEnd[-1] == lpcszEnd[-1])
      {
         lpcszSuffixEnd--;
         lpcszEnd--;
         if(lpcszSuffixEnd <= lpcszSuffix)
            return true;
      }

      return false;
      /*      string str(lpcsz);
      string strSuffix(lpcszSuffix);
      int32_t iLen = strSuffix.get_length();
      if(str.Right(iLen) == lpcszSuffix)
      {
      return true;
      }
      return false;*/
   }

   bool ends_ci(const char * lpcsz, const char * lpcszSuffix)
   {
      if(lpcsz == NULL || *lpcsz == '\0')
      {
         if(lpcszSuffix == NULL || *lpcszSuffix == '\0')
            return true;
         else
            return false;
      }
      else if(lpcszSuffix == NULL || *lpcszSuffix == '\0')
      {
         return true;
      }
      const char * lpcszEnd = lpcsz;
      const char * lpcszSuffixEnd = lpcszSuffix;
      while(*lpcszEnd)
         lpcszEnd++;
      while(*lpcszSuffixEnd)
         lpcszSuffixEnd++;
      if((lpcszSuffixEnd - lpcszSuffix) > (lpcszEnd - lpcsz))
         return false;
      while(tolower(lpcszSuffixEnd[-1]) == tolower(lpcszEnd[-1]))
      {
         lpcszSuffixEnd--;
         lpcszEnd--;
         if(lpcszSuffixEnd <= lpcszSuffix)
            return true;
      }

      return false;

   }


   bool ends_ci(const string & str, const char * lpcszSuffix)
   {
      if(str.is_empty())
      {
         if(lpcszSuffix == NULL || *lpcszSuffix == '\0')
            return true;
         else
            return false;
      }
      else if(lpcszSuffix == NULL || *lpcszSuffix == '\0')
      {
         return true;
      }
      const char * lpcsz = str;
      const char * lpcszEnd = lpcsz + str.get_length();
      const char * lpcszSuffixEnd = lpcszSuffix;
      while(*lpcszSuffixEnd)
         lpcszSuffixEnd++;
      if((lpcszSuffixEnd - lpcszSuffix) > (lpcszEnd - lpcsz))
         return false;
      while(tolower(lpcszSuffixEnd[-1]) == tolower(lpcszEnd[-1]))
      {
         lpcszSuffixEnd--;
         lpcszEnd--;
         if(lpcszSuffixEnd <= lpcszSuffix)
            return true;
      }

      return false;

   }

   bool ends_ci(const var & var, const char * lpcszSuffix)
   {
      return ends_ci(var.get_string(), lpcszSuffix);
   }


   bool ends_eat_ci(string & str, const char * lpcszSuffix)
   {

      string strSuffix(lpcszSuffix);

      strsize iLen = strSuffix.get_length();

      if(str.Right(iLen).compare_ci(lpcszSuffix) == 0)
      {

         str = str.Left(str.get_length() - iLen);
         return true;

      }

      return false;

   }

   void copy(string & str, const char * lpcsz, int32_t iCount)
   {
      string strCopy(lpcsz, iCount);
      str = strCopy;
   }

   string replace(const char * pszFind, const char * pszReplace, const char * psz, strsize iStart)
   {
      string str(psz);
      str.replace(pszFind, pszReplace, iStart);
      return str;
   }


   index  find_first(const stringa & straSearch, index & iFound, const string & str, index iStart)
   {

      index iFind = -1;

      iFound = -1;

      for(index i = 0; i < straSearch.get_count(); i++)
      {

         if(straSearch[i].has_char())
         {

            index iSearch = str.find(straSearch[i], iStart);

            if(iSearch >= 0 && iSearch >= iStart && (iSearch < iFind || iFind < 0))
            {

               iFind = iSearch;
               iFound = i;

            }

         }

      }

      return iFind;

   }

   string  random_replace(::aura::application * papp, const stringa & straReplacement, const stringa & straSearch, const char * psz)
   {

      string str(psz);

      index iFind;

      index iFound;

      index iStart = 0;

      while((iFind = find_first(straSearch, iFound, str, iStart)) >= 0)
      {

         if(iFind < iStart)
         {
            throw_parsing_exception("random replace error");
            return "";
         }

         index i = (index) (rand() % straReplacement.get_size());

         str = str.Left(iFind) + straReplacement[i] + str.Mid(iFind + straSearch[iFound].get_length());

         iFind += straReplacement[i].get_length();

         iStart = iFind;

      }

      return str;
   }

   ::count utf8_replace(string & str, const char * pszFind, const char * pszReplace, strsize iStart)
   {

      ::count c = 0;

      index iPos = iStart;

      ::count iReplaceLen = -1;

      ::count iFindLen = -1;

      while(true)
      {

         iPos = utf8_find(pszFind, str, iPos);

         if(iPos < 0)
            break;

         if(iReplaceLen < 0)
            iReplaceLen = strlen(pszReplace);

         if(iFindLen < 0)
            iFindLen = strlen(pszFind);

         str = str.Left(iPos) + pszReplace + str.Mid(iPos + iFindLen);

         iPos += iReplaceLen;

         c++;

      }

      return c;

   }


   string utf8_replace(const char * pszFind, const char * pszReplace, const char * psz, strsize iStart)
   {

      index iPos = iStart;

      string str(psz);

      ::count iReplaceLen = -1;

      ::count iFindLen = -1;

      while(true)
      {

         iPos = utf8_find(pszFind, str, iPos);

         if(iPos < 0)
            break;

         if(iReplaceLen < 0)
            iReplaceLen = strlen(pszReplace);

         if(iFindLen < 0)
            iFindLen = strlen(pszFind);

         str = str.Left(iPos) + pszReplace + str.Mid(iPos + iFindLen);

         iPos += iReplaceLen;

      }

      return str;
   }

   string replace_ci(const char * pszFind, const char * pszReplace, const char * psz, strsize iStart)
   {

      index iPos = iStart;

      string str(psz);

      ::count iReplaceLen = -1;

      ::count iFindLen = -1;

      while(true)
      {

         iPos = find_ci(pszFind, str, iPos);

         if(iPos < 0)
            break;

         if(iReplaceLen < 0)
            iReplaceLen = strlen(pszReplace);

         if(iFindLen < 0)
            iFindLen = strlen(pszFind);

         str = str.Left(iPos) + pszReplace + str.Mid(iPos + iFindLen);

         iPos += iReplaceLen;

      }

      return str;
   }

   ::count replace_ci_count(const char * pszFind, const char * pszReplace, const char * psz, strsize iStart)
   {

      index iPos = iStart;

      string str(psz);

      ::count iReplaceLen = -1;

      ::count iFindLen = -1;

      ::count c = 0;

      while (true)
      {

         iPos = find_ci(pszFind, str, iPos);

         if (iPos < 0)
            break;

         if (iReplaceLen < 0)
            iReplaceLen = strlen(pszReplace);

         if (iFindLen < 0)
            iFindLen = strlen(pszFind);

         str = str.Left(iPos) + pszReplace + str.Mid(iPos + iFindLen);

         iPos += iReplaceLen;

         c++;

      }

      return c;

   }


   index find_ci(const string & strFind, const string & str, index iStart)
   {

      if(strFind.get_length() > (str.get_length() - iStart))
         return -1;

      string strFindLow(&((LPCSTR)strFind)[0], strFind.get_length()); // avoid optimized read only string copy

      strFindLow.make_lower();

      string strLow(&((LPCSTR)str)[iStart], str.get_length() - iStart); // avoid optimized read only string copy

      strLow.make_lower();

      index iFind = strLow.find(strFindLow);

      if(iFind < 0)
         return -1;

      return iStart + iFind;

   }


   index find_ci(const string & strFind, const char * psz, index iStart)
   {

      ::count iFindLen = strFind.get_length();

      ::count iLen = strlen(&psz[iStart]);

      if(iFindLen > iLen)
         return -1;

      if(iFindLen < 256)
      {

         char szFind[256];

         memcpy(szFind, strFind, iFindLen + 1);

         make_lower(szFind);

         if(iLen < 256)
         {

            char sz[256];

            memcpy(sz, &psz[iStart], iLen + 1);

            make_lower(sz);

            const char * pszFind = strstr(sz, szFind);

            if(pszFind == NULL)
               return -1;

            return iStart + (pszFind - sz);

         }
         else
         {

            string strLow(&psz[iStart], iLen); // avoid optimized read only string copy

            strLow.make_lower();

            psz = strLow;

            const char * pszFind = strstr(psz, szFind);

            if(pszFind == NULL)
               return -1;

            return iStart + (pszFind - psz);

         }

      }
      else
      {

         string strFindLow(&((LPCSTR)strFind)[0], iFindLen); // avoid optimized read only string copy

         strFindLow.make_lower();

         string strLow(&psz[iStart], iLen); // avoid optimized read only string copy

         strLow.make_lower();

         index iFind = strLow.find(strFindLow);

         if(iFind < 0)
            return -1;

         return iStart + iFind;

      }

   }


   index find_ci(const char * pszFind, const string & str, index iStart)
   {

      ::count iFindLen = strlen(pszFind);

      index iLen = str.get_length() - iStart;

      if (iLen < iFindLen)
      {

         return -1;

      }


      strsize len1;
      strsize len2;

      const char * psz1 = str;

      psz1 += iStart;

      const char * psz2 = pszFind;

      while(true)
      {

         if(*psz1 == '\0')
         {
            break;
         }

         if(*psz2 == '\0')
         {
            break;
         }

         const char * pszC1 = psz1;
         const char * pszC2 = psz2;

         while(true)
         {

            if(ch::to_lower_case(ch::uni_index_len(pszC1,len1)) == ch::to_lower_case(ch::uni_index_len(pszC2,len2)))
            {
               pszC1 += len1;
               pszC2 += len2;
               if(*pszC2 == '\0')
               {
                  return psz1 - (const char *) str;
               }
               if(*pszC1 == '\0')
               {
                  return -1;
               }
            }
            else
            {
               ch::uni_index_len(psz1,len1);
               psz1 += len1;
               break;
            }
         }

      }

      return -1;

   }


   index find_ci(const char * pszFind,const string & str,index iStart, index iLast)
   {

      ::count iFindLen = strlen(pszFind);

      index iLen = str.get_length() - iStart;

      if(iLast < 0)
         iLast +=iLen;

      strsize len1;
      strsize len2;

      const char * psz1 = str;
      const char * psz2 = pszFind;

      strsize iPos = 0;

      while(iPos <= iLast)
      {

         if(*psz1 == '\0')
         {
            break;
         }

         if(*psz2 == '\0')
         {
            break;
         }

         const char * pszC1 = psz1;
         const char * pszC2 = psz2;

         while(true)
         {

            if(ch::to_lower_case(ch::uni_index_len(pszC1,len1)) == ch::to_lower_case(ch::uni_index_len(pszC2,len2)))
            {
               pszC1 += len1;
               pszC2 += len2;
               if(*pszC2 == '\0')
               {
                  return psz1 - (const char *)str;
               }
               if(*pszC1 == '\0')
               {
                  return -1;
               }
            }
            else
            {
               ch::uni_index_len(psz1,len1);
               psz1 += len1;
               iPos += len1;
               break;
            }
         }

      }

      return -1;

   }




   index find_file_extension(const char * pszFind,const string & str,index iStart, index iLast)
   {

      if(pszFind == NULL || pszFind[0] == '\0') // do not search for empty Extensions
         return -1;

      // for dir::name_is (check if base name of a file is a directory, checking if there is a simple ansi '.', may be very good start point definitive false).
      // if there is a dot, it may still does not have a Latin dot, if the dot is inside a Multibyte UTF8 char, anyway, algo following should check it properly.

      index iLen = str.get_length() - iStart;

      if(iLast < 0)
         iLast += iLen;

      {

         const char * pszOkToContinue = strchr(str,'.');

         if(pszOkToContinue == NULL || pszOkToContinue - (const char *)str >= iLast)
            return -1;

      }

      ::count iFindLen = strlen(pszFind);



      strsize len1;
      strsize len2;

      const char * psz1 = str;
      const char * psz2 = pszFind;

      strsize iPos = 0;
      strsize iPos2 = 0;

      while(iPos <= iLast)
      {

         if(*psz1 == '\0')
         {
            break;
         }

         if(*psz2 == '\0')
         {
            break;
         }

         if(*psz1 != '.')
         {

            len1 = str_uni_len(psz1);

            psz1 += len1;

            iPos += len1;

         }
         else
         {

            psz1 += 1;

            iPos += 1;

            if(iPos > iLast)
               break;

            const char * pszC1 = psz1;
            const char * pszC2 = psz2;

            iPos2 = iPos;

            while(true)
            {

               if(ch::to_lower_case(ch::uni_index_len(pszC1,len1)) == ch::to_lower_case(ch::uni_index_len(pszC2,len2)))
               {
                  pszC1 += len1;
                  pszC2 += len2;
                  iPos2 += len1;
                  if(*pszC2 == '\0')
                  {
                     return (psz1 - (const char *)str) - 1; // "-1" because find file extension returns the index of the dot
                  }
                  if(*pszC1 == '\0' || iPos2 > iLast)
                  {
                     return -1;
                  }
               }
               else
               {
                  ch::uni_index_len(psz1,len1);
                  psz1 += len1;
                  iPos += len1;
                  break;
               }
            }

         }

      }

      return -1;

   }


   index utf8_find(const char * pszFind, const char * pszParam, index iStart)
   {
      if(pszFind == NULL)
         return -1;

      if(*pszFind == '\0')
         return 0;

      if(pszParam == NULL || *pszParam == '\0')
         return -1;

      const char * psz = &pszParam[iStart];
      const char * pSrc;
      const char * pFin = pszFind;
      strsize lenSrc;
      strsize lenFin;
      while(*psz)
      {
         pSrc = psz;
         while(ch::_uni_index_len(pSrc, lenSrc) == ch::_uni_index_len(pFin, lenFin) && lenSrc == lenFin)
         {
            pSrc+=lenSrc;
            pFin+=lenFin;
            if(*pSrc == '\0')
            {
               if(*pFin == '\0')
               {
                  return pSrc - pszParam;
               }
               else
               {
                  return -1;
               }
            }
            else if(*pFin == '\0')
            {

               break;

            }

         }

         psz+=lenSrc;
      }

      return -1;

   }


   index find_ci(const char * pszFind, const char * psz, index iStart)
   {

      index iFindLen = strlen(pszFind);

      index iLen = strlen(&psz[iStart]);

      if(iFindLen > iLen)
         return -1;

      if(iFindLen < 256)
      {

         char szFind[256];

         memcpy(szFind, pszFind, iFindLen + 1);

         make_lower(szFind);

         if(iLen < 256)
         {

            char sz[256];

            memcpy(sz, &psz[iStart], iLen + 1);

            make_lower(sz);

            pszFind = strstr(sz, szFind);

            if(pszFind == NULL)
               return -1;

            return iStart + (pszFind - sz);

         }
         else
         {

            string strLow(&psz[iStart], iLen); // avoid optimized read only string copy
            strLow.make_lower();

            psz = strLow;

            pszFind = strstr(psz, szFind);

            if(pszFind == NULL)
               return -1;

            return iStart + (pszFind - psz);

         }

      }
      else
      {

         string strFindLow(pszFind, iFindLen); // avoid optimized read only string copy
         strFindLow.make_lower();

         string strLow(&psz[iStart], iLen); // avoid optimized read only string copy
         strLow.make_lower();

         index iFind = strLow.find(strFindLow);

         if(iFind < 0)
            return -1;

         return iStart + iFind;

      }

   }

   index find_wwci(const char * pszFind, const char * psz, index iStart)
   {

      string strFind(pszFind);

      strFind.make_lower();

      string str(psz);

      str.make_lower();

      return find_ww(strFind, str, iStart);

   }

   index find_awwci(const char * pszFind, const char * psz, index iStart)
   {

      string strFind(pszFind);

      strFind.make_lower();

      string str(psz);

      str.make_lower();

      return find_aww(strFind, str, iStart);

   }

   index find_ww(const char * pszFind, const char * psz, index iStart)
   {

      if(psz == NULL)
         return -1;

      const char * pszIter = &psz[iStart];

      if(pszIter == NULL)
         return -1;

      string strFind(pszFind);

      index i = 0;

      if(iStart == 0)
      {

         if(strFind == string(pszIter, strFind.get_length())
               && (strlen(pszIter) == (size_t) strFind.get_length() || !::str::ch::is_letter_or_digit(pszIter + strFind.get_length())))
         {
            return i;
         }

      }
      while(*pszIter != '\0')
      {

         string strChar = get_utf8_char(pszIter);

         if(!::str::ch::is_letter_or_digit(strChar))
         {

            do
            {
               i += strChar.get_length();
               pszIter = utf8_inc(pszIter);
               strChar = get_utf8_char(pszIter);
            }
            while(!::str::ch::is_letter_or_digit(strChar) && *pszIter != '\0');

            if(*pszIter == '\0')
               break;

            if(strFind == string(pszIter, strFind.get_length())
                  && (strlen(pszIter) == (size_t) strFind.get_length() || !::str::ch::is_letter_or_digit(pszIter + strFind.get_length())))
            {

               return iStart + i;

            }

         }

         i += strChar.get_length();

         pszIter = utf8_inc(pszIter);

      }

      return -1;

   }

   index find_aww(const char * pszFind, const char * psz, index iStart)
   {

      if(psz == NULL)
         return -1;

      const char * pszIter = &psz[iStart];

      if(pszIter == NULL)
         return -1;

      string strFind(pszFind);

      index i = 0;

      if(iStart == 0)
      {

         if(strFind == string(pszIter, strFind.get_length())
               && (strlen(pszIter) == (size_t) strFind.get_length() || !::str::ch::is_letter(pszIter + strFind.get_length())))
         {

            return i;

         }

      }

      while(*pszIter != '\0')
      {

         string strChar = get_utf8_char(pszIter);

         if(!::str::ch::is_letter(strChar))
         {

            do
            {

               i += strChar.get_length();

               pszIter = utf8_inc(pszIter);

               strChar = get_utf8_char(pszIter);

            }
            while(!::str::ch::is_letter(strChar) && *pszIter != '\0');

            if(*pszIter == '\0')
               break;

            if(strFind == string(pszIter, strFind.get_length())
                  && (strlen(pszIter) == (size_t) strFind.get_length() || !::str::ch::is_letter(pszIter + strFind.get_length())))
            {

               return iStart + i;

            }
         }

         i += strChar.get_length();

         pszIter = utf8_inc(pszIter);

      }

      return -1;

   }

   string has_char(const char * pszIfHasChar, const char * pszBefore, const char * pszAfter, const char * pszDoesnt)
   {

      string str;

      if (pszIfHasChar == NULL)
      {

         if (pszDoesnt != NULL)
         {

            return pszDoesnt;

         }
         else
         {

            return str;

         }

      }

      if(strlen(pszIfHasChar) == 0)
         return str;

      if(pszBefore != NULL)
      {

         str = pszBefore;

      }

      str += pszIfHasChar;

      if(pszAfter != NULL)
      {

         str += pszAfter;

      }

      return str;

   }


   bool has_upper(const char * psz)
   {

      bool bHasUpper;
      bool bHasLower;
      bool bHasDigit;

      calc_v1(psz, bHasUpper, bHasLower, bHasDigit);

      return bHasUpper;

   }

   bool has_lower(const char * psz)
   {

      bool bHasUpper;
      bool bHasLower;
      bool bHasDigit;

      calc_v1(psz, bHasUpper, bHasLower, bHasDigit);

      return bHasLower;

   }

   bool has_digit(const char * psz)
   {

      bool bHasUpper;
      bool bHasLower;
      bool bHasDigit;

      calc_v1(psz, bHasUpper, bHasLower, bHasDigit);

      return bHasDigit;

   }

   void calc_v1(const char * psz, bool & bHasUpper, bool & bHasLower, bool & bHasDigit)
   {

      bHasUpper = false;
      bHasLower = false;
      bHasDigit = false;

      while(true)
      {
         string qc = get_utf8_char(psz);
         if(qc.is_empty())
         {
            break;
         }
         else if(::str::ch::is_digit(qc))
         {
            bHasDigit = true;
         }
         else if(::str::ch::is_lower_case(qc))
         {
            bHasLower = true;
         }
         else if(::str::ch::is_upper_case(qc))
         {
            bHasUpper = true;
         }
         if(bHasUpper && bHasDigit && bHasLower)
         {
            // it is not necessary to evaluate more chars anymore
            break;
         }
         psz = utf8_inc(psz);
      }

   }

   bool has_one_v1(const char * psz, bool & bHasUpper, bool & bHasLower, bool & bHasDigit)
   {

      calc_v1(psz, bHasUpper, bHasLower, bHasDigit);

      return bHasUpper || bHasLower || bHasDigit;

   }

   bool has_all_v1(const char * psz, bool & bHasUpper, bool & bHasLower, bool & bHasDigit)
   {

      calc_v1(psz, bHasUpper, bHasLower, bHasDigit);

      return bHasUpper && bHasLower && bHasDigit;

   }

   bool has_all_v1(const char * psz)
   {

      bool bHasUpper;
      bool bHasLower;
      bool bHasDigit;

      return has_all_v1(psz, bHasUpper, bHasLower, bHasDigit);

   }


   string if_null(const char * psz, const char * pszIfNull)
   {

      if(psz == NULL)
         return pszIfNull;
      else
         return psz;

   }

   string get_window_text_timeout(oswindow oswindow, DWORD dwTimeout)
   {

      string str;

      if (oswindow != NULL)
      {

#ifdef WINDOWSEX

         DWORD_PTR lresult = 0;

         DWORD dwStart = get_tick_count();

         dwTimeout = MAX(10, dwTimeout);

         if(!::SendMessageTimeoutW(oswindow,WM_GETTEXTLENGTH,0,0,SMTO_ABORTIFHUNG,dwTimeout,&lresult))
            return "";

         wstring wstr;

         dwTimeout = MIN(dwTimeout, MAX(10, (get_tick_count() - dwStart) - dwTimeout));

         if(!::SendMessageTimeoutW(oswindow,WM_GETTEXT,(LPARAM)wstr.alloc(lresult + 1),lresult + 1,SMTO_ABORTIFHUNG,dwTimeout,&lresult))
            return "";

         str = wstr;

         //int32_t nLen = ::GetWindowTextLength(oswindow);

         //::GetWindowText(oswindow, str.GetBufferSetLength(nLen), nLen+1);

         //str.ReleaseBuffer();

#else

         _throw(todo(get_app()));

#endif

      }

      return str;

   }

   string get_word(
   const char * psz,
   const char * pszSeparator,
   bool bWithSeparator,
   bool bEndIsSeparator)
   {

      if(psz == NULL)
         return string();

      if(pszSeparator == NULL)
      {

         if(bEndIsSeparator)
         {
            return psz;
         }
         else
         {
            return string();
         }
      }
      const char * pszFind = strstr(psz, pszSeparator);
      if(pszFind == NULL)
      {
         if(bEndIsSeparator)
         {
            return psz;
         }
         else
         {
            return string();
         }
      }
      if(bWithSeparator)
      {
         return string(psz, pszFind - psz + 1);
      }
      else
      {
         return string(psz, pszFind - psz);
      }
   }

   bool to(int64_t & i, const char * psz)
   {

      char * pszEnd;

      int64_t iConversion = ::atoi64_dup(psz, &pszEnd);

      if(pszEnd == psz)
         return false;

      i = iConversion;

      return true;

   }

   bool to(int32_t & i, const char * psz)
   {

      const char * pszEnd;

      int64_t iConversion = ::atoi_dup(psz, &pszEnd);

      if(pszEnd == psz)
         return false;

      if(iConversion > numeric_info< int32_t >::max ())
         return false;

      i = (int32_t) iConversion;

      return true;

   }


   bool to(int64_t & i, int32_t iBase, const char * psz)
   {

      if(iBase < 0 || iBase == 1 || iBase > 36)
         return false;

      char * pszEnd;

#ifdef WINDOWS

      int64_t iConversion = ::_strtoi64(psz, &pszEnd, iBase);

#else

      int64_t iConversion = ::atoi64_dup(psz, &pszEnd, iBase);

#endif

      if(pszEnd == psz)
         return false;

      i = iConversion;

      return true;

   }

   bool to(int32_t & i, int32_t iBase, const char * psz)
   {

      if(iBase < 0 || iBase == 1 || iBase > 36)
         return false;

      char * pszEnd;

#ifdef WINDOWS

      int64_t iConversion = ::_strtoi64(psz, &pszEnd, iBase);

#else

      int64_t iConversion = ::atoi64_dup(psz, &pszEnd, iBase);

#endif

      if(pszEnd == psz)
         return false;

      if(iConversion > numeric_info< int32_t >::max ())
         return false;

      i = (int32_t) iConversion;

      return true;

   }

   bool to(uint64_t & ui, const char * psz)
   {

      char * pszEnd;

      uint64_t uiConversion = ::atoi64_dup(psz, &pszEnd);

      if(pszEnd == psz)
         return false;

      ui = uiConversion;

      return true;

   }

   bool to(uint32_t & ui, const char * psz)
   {

      const char * pszEnd;

      int64_t uiConversion = ::atoui_dup(psz, &pszEnd);

      if(pszEnd == psz)
         return false;

      if(uiConversion > numeric_info < uint32_t > ::max())
         return false;

      ui = (uint32_t) uiConversion;

      return true;

   }


   bool to(uint64_t & ui, int32_t iBase, const char * psz)
   {

      if(iBase < 0 || iBase == 1 || iBase > 36)
         return false;

      char * pszEnd;

      uint64_t uiConversion = ::atoui64_dup(psz, &pszEnd, iBase);

      if(pszEnd == psz)
         return false;

      ui = uiConversion;

      return true;

   }

   bool to(uint32_t & ui, int32_t iBase, const char * psz)
   {

      if(iBase < 0 || iBase == 1 || iBase > 36)
         return false;

      const char * pszEnd;

      uint32_t uiConversion = ::atoui_dup(psz, &pszEnd, iBase);

      if(pszEnd == psz)
         return false;

      if(uiConversion > numeric_info< uint32_t >::max ())
         return false;

      ui = uiConversion;

      return true;

   }

   int_ptr to_int_ptr(const char * psz)
   {

#if defined(_LP64) || defined(_AMD64_)

      return to_int64(psz);

#else
      return to_int(psz);

#endif

   }



   string uni_to_utf8(int64_t w)
   {
      string str;
      if(w < 0x0080 )
      {
         str += (char) w;
      }
      else if(w < 0x0800)
      {
         str = (char)(0xc0 | ((w) >> 6));
         str += (char)(0x80 | ((w) & 0x3f));
      }
      else
      {
         str = (char)(0xe0 | ((w) >> 12));
         str += (char)(0x80 | (((w) >> 6) & 0x3f));
         str += (char)(0x80 | ((w) & 0x3f));
      }
      return str;
   }


   const char * utf8_inc(const char * psz)
   {

      if (psz == NULL)
      {

         return NULL;

      }

      if (*psz == '\0')
      {

         return psz;

      }

      clear_err();

      char len =  1 + trailingBytesForUTF8(*psz);
      if(len == 0)      return psz;
      if(*psz++ == 0)
      {
         set_err(err_invalid_utf8_character);
         return NULL;
      }
      if(len == 1)      return psz;
      if(*psz++ == 0)
      {
         set_err(err_invalid_utf8_character);
         return NULL;
      }
      if(len == 2)      return psz;
      if(*psz++ == 0)
      {
         set_err(err_invalid_utf8_character);
         return NULL;
      }
      if(len == 3)      return psz;
      if(*psz++ == 0)
      {
         set_err(err_invalid_utf8_character);
         return NULL;
      }
      if(len == 4)      return psz;
      if(*psz++ == 0)
      {
         set_err(err_invalid_utf8_character);
         return NULL;
      }
      if(len == 5)      return psz;
      if(*psz++ == 0)
      {
         set_err(err_invalid_utf8_character);
         return NULL;
      }
      if(len == 6)      return psz;

      {
         set_err(err_invalid_utf8_character);
         return NULL;
      }
   }


   const char * utf8_inc_slide(strsize * pslide, const char * psz)
   {
      char len =  1 + trailingBytesForUTF8(*psz);
      if(len == 0)
      {
         *pslide += 0;
         return psz;
      }
      if(*psz++ == 0)   _throw(invalid_character(get_app(), "invalid utf8 character"));
      if(len == 1)
      {
         *pslide += 1;
         return psz;
      }
      if(*psz++ == 0)   _throw(invalid_character(get_app(), "invalid utf8 character"));
      if(len == 2)
      {
         *pslide += 2;
         return psz;
      }
      if(*psz++ == 0)   _throw(invalid_character(get_app(), "invalid utf8 character"));
      if(len == 3)
      {
         *pslide += 3;
         return psz;
      }
      if(*psz++ == 0)   _throw(invalid_character(get_app(), "invalid utf8 character"));
      if(len == 4)
      {
         *pslide += 4;
         return psz;
      }
      if(*psz++ == 0)   _throw(invalid_character(get_app(), "invalid utf8 character"));
      if(len == 5)
      {
         *pslide += 5;
         return psz;
      }
      if(*psz++ == 0)   _throw(invalid_character(get_app(), "invalid utf8 character"));
      if(len == 6)
      {
         *pslide += 6;
         return psz;
      }
      _throw(invalid_character(get_app(), "invalid utf8 character"));
   }


   const char * utf8_inc_copy_slide_back(strsize * pslideback, char * pchDst, const char * pchSrc)
   {

      strsize count = 0;

      ::str::utf8_inc_slide(&count, pchSrc);

      memcpy(pchDst, pchSrc, count);

      pchSrc         += count;

      pchDst         += count;

      *pslideback    -= count;

      return pchSrc;

   }



   const char * utf8_dec(const char * pszBeg, const char * psz)
   {
      if(psz <= pszBeg)
      {
         return NULL;
      }
      if((*(psz - 1) & 0x80) == 0x00)
      {
         if((psz - 1) < pszBeg)
         {
            return NULL;
         }
         return psz - 1;
      }
      else if((*(psz - 2) & 0xE0) == 0xC0)
      {
         if((psz - 2) < pszBeg)
         {
            return NULL;
         }
         return psz - 2;
      }
      else if((*(psz - 3) & 0xF0) == 0xE0)
      {
         if((psz - 3) < pszBeg)
         {
            return NULL;
         }
         return psz - 3;
      }
      else if((*(psz - 4) & 0xF8) == 0xF0)
      {
         if((psz - 4) < pszBeg)
         {
            return NULL;
         }
         return psz - 4;
      }
      else if((*(psz - 5) & 0xFC) == 0xF8)
      {
         if((psz - 5) < pszBeg)
         {
            return NULL;
         }
         return psz - 5;
      }
      else if((*(psz - 6) & 0xFE) == 0xFC)
      {
         if((psz - 6) < pszBeg)
         {
            return NULL;
         }
         return psz - 6;
      }
      if((psz - 1) < pszBeg)
      {
         return NULL;
      }
      return psz - 1;
   }

   const char * utf8_dec(::str::utf8_char * pchar, const char * pszBeg, const char * psz)
   {
      if(psz <= pszBeg)
      {
         pchar->m_chLen = -1;
         return NULL;
      }
      if((*(psz - 1) & 0x80) == 0x00)
      {
         if((psz - 1) < pszBeg)
         {
            pchar->m_chLen = -1;
            return NULL;
         }
         pchar->m_sz[0] = psz[-1];
         pchar->m_sz[1] = '\0';
         pchar->m_chLen = 1;
         return psz - 1;
      }
      else if((*(psz - 2) & 0xE0) == 0xC0)
      {
         if((psz - 2) < pszBeg)
         {
            pchar->m_chLen = -1;
            return NULL;
         }
         pchar->m_sz[0] = psz[-2];
         pchar->m_sz[1] = psz[-1];
         pchar->m_sz[2] = '\0';
         pchar->m_chLen = 2;
         return psz - 2;
      }
      else if((*(psz - 3) & 0xF0) == 0xE0)
      {
         if((psz - 3) < pszBeg)
         {
            pchar->m_chLen = -1;
            return NULL;
         }
         pchar->m_sz[0] = psz[-3];
         pchar->m_sz[1] = psz[-2];
         pchar->m_sz[2] = psz[-1];
         pchar->m_sz[3] = '\0';
         pchar->m_chLen = 3;
         return psz - 3;
      }
      else if((*(psz - 4) & 0xF8) == 0xF0)
      {
         if((psz - 4) < pszBeg)
         {
            pchar->m_chLen = -1;
            return NULL;
         }
         pchar->m_sz[0] = psz[-4];
         pchar->m_sz[1] = psz[-3];
         pchar->m_sz[2] = psz[-2];
         pchar->m_sz[3] = psz[-1];
         pchar->m_sz[4] = '\0';
         pchar->m_chLen = 4;
         return psz - 4;
      }
      else if((*(psz - 5) & 0xFC) == 0xF8)
      {
         if((psz - 5) < pszBeg)
         {
            pchar->m_chLen = -1;
            return NULL;
         }
         pchar->m_sz[0] = psz[-5];
         pchar->m_sz[1] = psz[-4];
         pchar->m_sz[2] = psz[-3];
         pchar->m_sz[3] = psz[-2];
         pchar->m_sz[4] = psz[-1];
         pchar->m_sz[5] = '\0';
         pchar->m_chLen = 5;
         return psz - 5;
      }
      else if((*(psz - 6) & 0xFE) == 0xFC)
      {
         if((psz - 6) < pszBeg)
         {
            pchar->m_chLen = -1;
            return NULL;
         }
         pchar->m_sz[0] = psz[-6];
         pchar->m_sz[1] = psz[-5];
         pchar->m_sz[2] = psz[-4];
         pchar->m_sz[3] = psz[-3];
         pchar->m_sz[4] = psz[-2];
         pchar->m_sz[5] = psz[-1];
         pchar->m_sz[6] = '\0';
         pchar->m_chLen = 6;
         return psz - 6;
      }
      if((psz - 1) < pszBeg)
      {
         pchar->m_chLen = -1;
         return NULL;
      }
      pchar->m_sz[0] = psz[-1];
      pchar->m_sz[1] = '\0';
      pchar->m_chLen = 1;
      return psz - 1;
   }


   string get_utf8_char(const char * psz)
   {
      ::str::utf8_char ch;
      int32_t len = ch.parse(psz);
      if(len < 0)
         return "";
      return string(ch.m_sz);
   }


   string get_utf8_char(const char * psz, const char * pszEnd)
   {
      const char * pszNext = __utf8_inc(psz);
      if(pszNext > pszEnd)
         return "";
      return string(psz, pszNext - psz);
   }

   bool get_utf8_char(string & str, const char * & psz, const char * pszEnd)
   {
      const char * pszNext = __utf8_inc(psz);
      if(pszNext > pszEnd)
      {
         return false;
      }
      str = string(psz, pszNext - psz);
      psz = pszNext;
      return true;
   }

   string get_utf8_char(const char * pszBeg, const char * psz, index i)
   {

      if(i > 0)
      {
         while(i != 0)
         {
            psz = utf8_inc(psz);
            if(*psz == '\0')
            {
               return "";
            }
            i--;
         }
         return get_utf8_char(psz);
      }
      else
      {
         while(i != 0)
         {
            psz = utf8_dec(pszBeg, psz);
            if(psz == NULL)
            {
               return "";
            }
            else if(*psz == '\0')
            {
               return "";
            }
            i++;
         }
         return get_utf8_char(psz);
      }
   }

   string utf8_next_char(const char * pszBeg, const char * psz, index i)
   {
      return get_utf8_char(pszBeg, psz, i + 1);
   }

   string utf8_previous_char(const char * pszBeg, const char * psz, index i)
   {
      return utf8_next_char(pszBeg, psz, -i);
   }


   int32_t get_escaped_char(const char * lpcsz, strsize pos, strsize &retPos)
   {
      retPos = pos;
      if(lpcsz[pos] == '\\')
      {
         retPos++;
         if(lpcsz[pos+1] == 'x')
         {
            if(lpcsz[pos+2] == '{')
            {
               string val;
               if(!get_curly_content(&lpcsz[pos+2], val))
               {
                  return BAD_WCHAR;
               }
               int64_t hex = ::hex::to_int64(val);
               strsize val_len = val.get_length();
               if(hex < 0 || hex > 0xFFFF)
               {
                  return BAD_WCHAR;
               }
               retPos += val_len + 2;
               return (int32_t) hex;
            }
            else
            {
               int64_t hex = ::hex::to_int64(string(&lpcsz[pos+2], 2));
               if(int64_t(strlen(lpcsz)) <= pos + 2 || hex== -1)
               {
                  return BAD_WCHAR;
               }
               retPos += 2;
               return (int32_t) hex;
            }
         }
         return lpcsz[pos+1];
      }
      return lpcsz[pos];
   }

   bool get_curly_content(const char * psz, string & str)
   {
      if (psz[0] != '{') return false;
      const char * pszChar;
      for(pszChar = utf8_inc(psz); pszChar != NULL; pszChar = utf8_inc(pszChar))
      {
         if (*pszChar == '}')
            break;
         /*  ECharCategory cc = Character::getCategory(str[lpos]);
         // check for what??
         if (Character::isWhitespace(str[lpos]) ||
         cc == CHAR_CATEGORY_Cn || cc == CHAR_CATEGORY_Cc ||
         cc == CHAR_CATEGORY_Cf || cc == CHAR_CATEGORY_Cs)
         return NULL;*/
      };
      if (pszChar == NULL || *pszChar == '\0')
         return false;
      str = string(&psz[1], pszChar - psz - 1);
      return true;
   }


   bool is_simple_natural(const char * pszCandidate, strsize iCount)
   {

      if(iCount == 0)
         return false;

      string str(pszCandidate);

      str.trim();

      LPCSTR psz = str;

      if(*psz == '\0')
         return false;

      while(*psz != '\0' && iCount != 0)
      {
         if(!::str::ch::is_digit(psz))
            return false;
         psz = utf8_inc(psz);
         iCount--;
      }
      return true;
   }


   bool is_natural(const char * psz)
   {

      string str(psz);

      str.trim();

      for (index i = 0; i < str.get_length(); i++)
      {

         if (!isdigit_dup(str[i]))
         {

            return false;

         }

      }

      return true;

   }


   bool is_integer(const char * psz)
   {

      string str(psz);

      str.trim();

      if (::str::begins_eat_ci(str, "-") || ::str::begins_eat_ci(str, "+"))
      {

         return is_natural(str);

      }
      else
      {

         return is_natural(str);

      }

   }


   void consume(const char * & pszXml, const char * psz)
   {

      index idx;

      strsize len = strlen(psz);
      for(idx = 0; idx < len; idx++)
      {
         if(pszXml[idx] != psz[idx])
         {
            throw_parsing_exception("Name does not match expected");
            break;
         }
      }
      pszXml += len;
   }


   bool eats(const char * & pszXml, const char * psz)
   {

      for (; *psz != '\0'; pszXml++, psz++)
      {

         if (*pszXml != *psz)
         {
            return false;

         }

      }

      return true;

   }


   bool eats_ci(const char * & pszXml, const char * psz)
   {

      for (; *psz != '\0'; pszXml++, psz++)
      {

         if (tolower(*pszXml) != tolower(*psz))
         {
            return false;

         }

      }

      return true;

   }


   void consume(const char * & pszXml, const char * psz, const char * pszEnd)
   {
      UNREFERENCED_PARAMETER(pszEnd);
      strsize idx;
      strsize len = strlen(psz);
      for(idx = 0; idx < len; idx++)
      {
         if(pszXml[idx] != psz[idx])
         {
            throw_parsing_exception("Name does not match expected");
            break;
         }
      }
      pszXml += len;
   }

   void consume(const char * & pszXml, const char * psz, strsize len, const char * pszEnd)
   {
      UNREFERENCED_PARAMETER(pszEnd);
      int32_t idx;
      for(idx = 0; idx < len; idx++)
      {
         if(pszXml[idx] != psz[idx])
         {
            throw_parsing_exception("Name does not match expected");
            break;
         }
      }
      pszXml += len;
   }

   void consume_spaces(const char * & pszXml, ::count iMinimumCount)
   {
      const char * psz = pszXml;
      int32_t i = 0;
      while(::str::ch::is_whitespace(psz))
      {
         psz = utf8_inc(psz);
         i++;
      }
      if(i < iMinimumCount)
      {
         throw_parsing_exception("Space is required");
      }
      pszXml = psz;
   }

   uint64_t consume_natural(const char * & pszXml, uint64_t uiMax, uint64_t uiMin)
   {
      if(uiMax < uiMin)
      {
         _throw(invalid_argument_exception(get_app(), "MAX should be greater than MIN"));
      }
      const char * psz = pszXml;
      int32_t i = 0;
      uint64_t ui;
      while(::str::ch::is_digit(psz))
      {
         psz = utf8_inc(psz);
         i++;
      }
      if(psz == pszXml)
      {
         throw_parsing_exception("empty natural found");
      }
      ui = ::str::to_uint(string(pszXml, psz - pszXml));
      if(ui < uiMin)
      {
         throw_parsing_exception("natural less than MIN");
      }
      else if(ui > uiMax)
      {
         throw_parsing_exception("natural greater than MAX");
      }
      pszXml = psz;
      return ui;

   }

   void consume_spaces(const char * & pszXml, ::count iMinimumCount, const char * pszEnd)
   {
      const char * psz = pszXml;
      int32_t i = 0;
      while(::str::ch::is_whitespace(psz, pszEnd))
      {
         psz = __utf8_inc(psz);
         if(psz > pszEnd)
         {
            throw_parsing_exception("premature end");
            break;
         }
         i++;
      }
      if(i < iMinimumCount)
      {
         throw_parsing_exception("Space is required");
      }
      pszXml = psz;
   }

   string consume_non_spaces(const char * & pszXml, const char * pszEnd)
   {
      const char * psz = pszXml;
      while(!::str::ch::is_whitespace(psz, pszEnd))
      {
         psz = __utf8_inc(psz);
         if(psz >= pszEnd)
         {
            break;
         }
      }
      string str(pszXml, psz - pszXml);
      pszXml = psz;
      return str;
   }

   string consume_hex(const char * & pszXml)
   {
      const char * psz = pszXml;
//      int32_t i = 0;
      while(*psz != '\0')
      {
         int64_t i = ::str::ch::uni_index(pszXml);
         if(isdigit((int32_t) i) || (i >= 'a' && i <= 'f') || (i >= 'A' && i <= 'F'))
         {
            psz = __utf8_inc(psz);
         }
      }
      if(psz == pszXml)
      {
         throw_parsing_exception("no hex consumed");
         return "";
      }
      string str(pszXml, psz - pszXml);
      pszXml = psz;
      return psz;
   }


   string consume_nc_name(const char * & pszXml)
   {
      const char * psz = pszXml;
      bool start = true;
      while(true)
      {
         const char * ca = psz;
         // first char
         if(start)
         {
            if(!::str::ch::is_letter(ca) || *ca == '\0')
            {
               throw_parsing_exception("NCName required here");
               return "";
            }
            start = false;
         }
         else
         {
            if(!::str::ch::is_letter_or_digit(ca) && *ca != '_' && *ca != '-')
            {
               break;
            }
            psz = ::str::utf8_inc(psz);
         }
      }
      string str(pszXml, psz - pszXml);
      pszXml = psz;
      return str;
   }

   string consume_quoted_value(const char * & pszXml)
   {

      ::str::utf8_char utf8char;

      const char * psz = pszXml;
      utf8char.parse(psz); // quote character
      if(utf8char.m_chLen != 1)
      {
         throw_parsing_exception("Quote character is required here");
         return "";
      }
      char qc = utf8char.m_sz[0];
      if(qc != '\"' && qc != '\\')
      {
         throw_parsing_exception("Quote character is required here");
         return "";
      }
      int iPos = utf8char.m_chLen;
      string str;
      int iPosStart = iPos;
      while(true)
      {
         iPos += utf8char.parse(&psz[iPos]);
         if(utf8char.m_chLen <= 0)
         {
            throw_parsing_exception("Quote character is required here, premature end");
            return "";
         }
         if(utf8char.m_chLen == 1 && utf8char.m_sz[0] == qc)
            break;

      }
      str = string(&psz[iPosStart], iPos - iPosStart - 1);
      pszXml = &psz[iPos];
      return str;
   }

   string consume_quoted_value(const char * & pszXml, const char * pszEnd)
   {

      const char * psz = pszXml;

      if(*psz != '\"' && *psz != '\'')
      {

         throw_parsing_exception("Quote character is required here");

         return "";

      }

      char qc = *psz;

      psz++;

      const char * pszValueStart = psz;

      while(*psz != qc)
      {

skip:

         psz = __utf8_inc(psz);

         if(psz > pszEnd)
         {

            throw_parsing_exception("Quote character is required here, premature end");

            return "";

         }

         if(*psz == '\\')
         {

            psz = __utf8_inc(psz);

            if(psz > pszEnd)
            {

               throw_parsing_exception("Quote character is required here, premature end");

               return "";

            }

            goto skip;

         }

      }

      psz++;

      pszXml = psz;

      return string(pszValueStart, psz - pszValueStart - 1);

   }


   void consume_quoted_value_ex2(const char * & pszXml, const char * pszEnd, char ** ppsz, strsize & iBufferSize)
   {

      const char * psz = pszXml;

      if (*psz != '\"' && *psz != '\\')
      {

         throw_parsing_exception("Quote character is required here");

         return;

      }

      char qc = *psz;

      psz++;

      const char * pszValueStart = psz;

      while (*psz != qc)
      {

         psz = __utf8_inc(psz);

         if (psz > pszEnd)
         {

            throw_parsing_exception("Quote character is required here, premature end");

            return;

         }

      }

      strsize iNewBufferSize = psz - pszValueStart;


      if (iNewBufferSize > iBufferSize)
      {

         *ppsz = (char *) memory_alloc(iNewBufferSize+1);

      }

      strncpy(*ppsz, pszValueStart, iNewBufferSize);

      (*ppsz)[iNewBufferSize] = '\0';

      iBufferSize = iNewBufferSize;

      psz++;

      pszXml = psz;

   }

   void skip_quoted_value_ex2(const char * & pszXml, const char * pszEnd)
   {

      const char * psz = pszXml;

      if (*psz != '\"' && *psz != '\\')
      {

         throw_parsing_exception("Quote character is required here");

         return;

      }

      char qc = *psz;

      psz++;

      const char * pszValueStart = psz;

      while (*psz != qc)
      {

         psz = __utf8_inc(psz);

         if (psz > pszEnd)
         {

            throw_parsing_exception("Quote character is required here, premature end");

            return;

         }

      }

      memory_size_t iNewBufferSize = psz - pszValueStart;

      psz++;

      pszXml = psz;

   }

   template < const strsize m_iSize = 1024 >
   class mini_str_buffer
   {
   public:


      strsize     m_iPos;
      char        m_sz[m_iSize];
      string      m_str;


      mini_str_buffer()
      {

         m_iPos = 0;

      }

      void append(char ch)
      {

         if (m_iPos + 1 > m_iSize)
         {

            m_str.append(m_sz, m_iPos);

            m_iPos = 0;

         }

         m_sz[m_iPos] = ch;

         m_iPos ++;


      }

      void append_uni(int64_t w)
      {

         if (m_iPos + 3 > m_iSize)
         {

            m_str.append(m_sz, m_iPos);

            m_iPos = 0;

         }

         if (w < 0x0080)
         {

            m_sz[m_iPos] = char(w);
            m_iPos++;

         }
         else if (w < 0x0800)
         {
            m_sz[m_iPos] = (char)(0xc0 | ((w) >> 6));
            m_iPos++;
            m_sz[m_iPos] = (char)(0x80 | ((w) & 0x3f));
            m_iPos++;
         }
         else
         {
            m_sz[m_iPos] = (char)(0xe0 | ((w) >> 12));
            m_iPos++;
            m_sz[m_iPos] = (char)(0xc0 | (((w) >> 6) & 0x3f));
            m_iPos++;
            m_sz[m_iPos] = (char)(0x80 | ((w) & 0x3f));
            m_iPos++;
         }
      }

      void append(const char * psz, strsize iSize)
      {

         if (m_iPos + iSize > m_iSize)
         {

            m_str.append(m_sz, m_iPos);

            m_iPos = 0;

            if (iSize > m_iSize)
            {

               m_str.append(m_sz, iSize);

               return;

            }

         }

         strncpy(&m_sz[m_iPos], psz, iSize);

         m_iPos += iSize;

      }


      void update()
      {

         m_str.append(m_sz, m_iPos);

         m_iPos = 0;

      }

   };

   string consume_quoted_value_ex(const char * & pszXml,const char * pszEnd)
   {
      const char * psz = pszXml;
      char qc = *psz; // quote character
      if(qc != '\"' && qc != '\'')
      {
         throw_parsing_exception("Quote character is required here, premature end");
         return "";
      }
      psz++;
      const char * pszValueStart = psz;
      //const char * pszValueEnd = psz;
      const char * pszNext = psz;
      string str;
      while(true)
      {
         pszNext = __utf8_inc(psz);
         if(pszNext > pszEnd)
         {
            throw_parsing_exception("Quote character is required here, premature end");
            return "";
         }
         if (*psz == '\0')
         {
            throw_parsing_exception("Quote character is required here, premature end");
            return "";
         }
         else if(*psz == qc)
         {
            psz++;
            break;
         }
         else if(*psz == '\\')
         {
            psz = pszNext;
            pszNext = __utf8_inc(psz);
            if(pszNext > pszEnd)
            {
               throw_parsing_exception("Quote character is required here, premature end");
               return "";
            }
            if(*psz == 'n')
            {
               str += '\n';
            }
            else if(*psz == 't')
            {
               str+='\t';
            }
            else if(*psz == 'r')
            {
               str+='\r';
            }
            else if(*psz == 'u')
            {
               psz++;
               uint16_t ui[2];
               ui[0] = ::hex::parse_uint16_exc(psz, pszEnd);
               if (is_high_surrogate(ui[0]))
               {
                  if (*psz != '\\')
                  {
                     throw_parsing_exception("expect back slash here (for low surrogate)");
                  }
                  psz++;
                  if (*psz != 'u' && *psz != 'U')
                  {
                     throw_parsing_exception("expect 'u' character here (for low surrogate)");
                  }
                  psz++;
                  ui[1] = ::hex::parse_uint16_exc(psz, pszEnd);

                  if (!is_low_surrogate(ui[1]))
                  {

                     throw_parsing_exception("expect low surrogate");

                  }
                  else
                  {

                     unichar32 uni = (unichar32)decode_utf16_pair(ui);
                     string strUtf8 = utf32_to_utf8(&uni, 1);
                     str+=strUtf8;

                  }

               }
               else
               {

                  unichar32 uni = ui[0];
                  string strUtf8 = utf32_to_utf8(&uni, 1);
                  str += strUtf8;

               }
               pszNext = psz;
            }
            else if(*psz == '\"')
            {
               str+='\"';
            }
            else
            {
               str.append(psz,pszNext - psz);
            }
         }
         else
         {
            str.append(psz, pszNext - psz);
         }

         psz = pszNext;

         //pszValueEnd = psz;

      }

      pszXml = psz;

      return str;

   }

   void skip_quoted_value_ex(const char * & pszXml, const char * pszEnd)
   {
      const char * psz = pszXml;
      char qc = *pszXml; // quote character
      if (qc != '\"' && qc != '\'')
      {
         throw_parsing_exception("Quote character is required here, premature end");
         return;
      }
      psz++;
      const char * pszValueStart = psz;
      //const char * pszValueEnd = psz;
      const char * pszNext = psz;
      while (true)
      {
         pszNext = __utf8_inc(psz);
         if (pszNext > pszEnd)
         {
            throw_parsing_exception("Quote character is required here, premature end");
            return;
         }
         if (*psz == '\0')
         {
            throw_parsing_exception("Quote character is required here, premature end");
            return;
         }
         else if (*psz == '\"')
         {
            psz++;
            break;
         }
         else if (*psz == '\\')
         {
            psz = pszNext;
            pszNext = __utf8_inc(psz);
            if (pszNext > pszEnd)
            {
               throw_parsing_exception("Quote character is required here, premature end");
               return;
            }
            if (*psz == 'n')
            {
            }
            else if (*psz == 't')
            {
            }
            else if (*psz == 'r')
            {
            }
            else if (*psz == 'u')
            {
               string strUni;
               for (index i = 0; i < 4; i++)
               {
                  psz = pszNext;
                  pszNext = __utf8_inc(psz);
                  if (pszNext > pszEnd)
                  {
                     throw_parsing_exception("Quote character is required here, premature end");
                     return;
                  }
                  if ((pszNext - psz == 1) && ((*psz >= '0' && *psz <= '9') || (*psz >= 'A' && *psz <= 'F') || (*psz >= 'a' && *psz <= 'f')))
                  {
                  }
                  else
                  {
                     throw_parsing_exception("16 bit unicode expect here");
                     return;
                  }

               }
            }
            else if (*psz == '\"')
            {
            }
            else
            {
            }
         }
         else
         {
         }

         psz = pszNext;

         //pszValueEnd = psz;

      }

      pszXml = psz;

   }


   string consume_spaced_value(string & str)
   {

      strsize i = 0;

      while(i < str.length() && isspace((byte) str[i]))
      {

         i++;

      }

      if(i >= str.length())
      {

         str.Empty();

         return "";

      }

      strsize iStart = i;

      while(i < str.length() && !isspace((byte) str[i]))
      {
         i++;
      }

      string strResult = str.Mid(iStart, i - iStart);

      str = str.Mid(i);

      return strResult;


   }

   string consume_spaced_value(const char * & psz)
   {

      string str(psz);

      strsize iOldLen = str.length();

      string strResult = consume_spaced_value(str);

      psz += iOldLen - str.length();

      return strResult;

   }

   string consume_spaced_value(const char * & psz, const char * pszEnd)
   {

      string str(psz, pszEnd - psz);

      strsize iOldLen = str.length();

      string strResult = consume_spaced_value(str);

      psz += iOldLen - str.length();

      return strResult;

   }


   string consume_command_line_argument(string & str)
   {

      string strResult;

      strsize iFind = str.find('\"');

      if(iFind < 0)
      {

         strResult = consume_spaced_value(str);

      }
      else
      {

         strsize i = 0;

         while(i < iFind && isspace((byte) str[i]))
         {
            i++;
         }

         if(i < iFind)
         {

            strsize iStart = i;

            while(i < iFind && !isspace((byte) str[i]))
            {
               i++;
            }

            strResult = str.Mid(iStart, i - iStart);

            str = str.Mid(i);

         }
         else
         {

            iFind++;

            strsize iFind2 = str.find('\"',iFind);

            if(iFind2 < 0)
            {

               strsize iStart = iFind;

               i = iStart;

               while(i < str.length() && !isspace((byte) str[i]))
               {
                  i++;
               }

               strResult = str.Mid(iStart, i - iStart);

               str = str.Mid(i);

            }
            else
            {

               strResult = str.Mid(iFind, iFind2 - iFind);

               str = str.Mid(iFind2 + 1);

            }

         }

      }

      return strResult;

   }


   string consume_command_line_argument(const char * & psz)
   {

      string str(psz);

      strsize iOldLen = str.length();

      string strResult = consume_command_line_argument(str);

      psz += iOldLen - str.length();

      return strResult;

   }

   string consume_command_line_argument(const char * & psz, const char * pszEnd)
   {

      string str(psz, pszEnd - psz);

      strsize iOldLen = str.length();

      string strResult = consume_command_line_argument(str);

      psz += iOldLen - str.length();

      return strResult;

   }


   string consume_c_quoted_value(const char * & pszXml)
   {
      const char * psz = pszXml;
      string strQuoteChar = get_utf8_char(psz);
      if(strQuoteChar != "\"" && strQuoteChar != "\\")
      {
         throw_parsing_exception("Quote character is required here");
         return "";
      }
      string strCurrentChar;
      string str;
      string strPreviousChar;
      while(true)
      {
         psz = utf8_inc(psz);
         strPreviousChar = strCurrentChar;
         strCurrentChar = get_utf8_char(psz);
         //string str = ::str::international::utf8_to_unicode(qc2);
         if(strCurrentChar.is_empty())
         {
            throw_parsing_exception("Quote character is required here, premature end");
            return "";
         }
         if(strPreviousChar == "\\")
         {
            str += strCurrentChar;
            strCurrentChar.Empty();
         }
         else if(strCurrentChar == "\\")
         {
         }
         else
         {
            if(strCurrentChar == strQuoteChar)
               break;
            str += strCurrentChar;
         }
      }
      psz = utf8_inc(psz);
      pszXml = psz;
      return str;
   }

   bool begins_consume(const char * & pszXml, const char * psz)
   {
      strsize idx;
      strsize len = strlen(psz);
      for(idx = 0; idx < len; idx++)
      {
         if(pszXml[idx] != psz[idx])
         {
            return false;
         }
      }
      pszXml += len;
      return true;
   }

   bool xml_is_comment(const char * pszXml)
   {
      return pszXml[0] == '<' && pszXml[1] == '!' && pszXml[2] == '-';
   }

   string xml_consume_comment(const char * & pszXml)
   {
      string str;
      ::str::consume(pszXml, "<!--");
      while(pszXml[0] != '-' || pszXml[1] != '-' ||pszXml[2] != '>')
      {

         if(*pszXml == '\0')
         {
            break;
         }
         str += *pszXml;
         pszXml = ::str::utf8_inc(pszXml);
      }
      consume(pszXml, "-->");
      return str;
   }

   string pad(const char * psz, ::count iLen, const char * pszPattern, e_pad epad)
   {
      string str;
      str = psz;
      if(pszPattern == NULL || strlen(pszPattern) == 0)
         return str;
      int32_t i = 0;
      if(epad == pad_left)
      {
         while(str.get_length() < iLen)
         {
            if(pszPattern[i] == '\0')
               i = 0;
            str = pszPattern[i] + str;
            i++;
         }
      }
      else if(epad == pad_right)
      {
         while(str.get_length() < iLen)
         {
            if(pszPattern[i] == '\0')
               i = 0;
            str = str + pszPattern[i];
            i++;
         }
      }
      return str;
   }

   var ends_get(const char * pszSuffix, const char * psz)
   {
      if(pszSuffix == NULL)
         return psz;
      if(psz == NULL)
         return "";
      string str(psz);
      strsize iLen = strlen(psz);
      strsize iLenSuffix = strlen(pszSuffix);
      if(str.Right(iLenSuffix) == pszSuffix)
      {
         return str.Mid(0, iLen - iLenSuffix);
      }
      return false;
   }

   var ends_get_ci(const char * pszSuffix, const char * psz)
   {
      if(pszSuffix == NULL)
         return psz;
      if(psz == NULL)
         return "";
      string str(psz);
      strsize iLen = strlen(psz);
      strsize iLenSuffix = strlen(pszSuffix);
      if(str.Right(iLenSuffix).compare_ci(pszSuffix) == 0)
      {
         return str.Mid(0, iLen - iLenSuffix);
      }
      return false;
   }
   /** \file Utility.cpp
   **   \date  2004-02-13
   **   \author grymse@alhem.net
   **/
   /*
   Copyright (C) 2004-2007  Anders Hedstrom

   This library is made available under the terms of the GNU GPL.

   If you would like to use this library in a closed-source application,
   a separate license agreement is available. For information about
   the closed-source license agreement for the C++ sockets library,
   please visit http://www.alhem.net/Sockets/license.html and/or
   email license@alhem.net.

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
   */
   /*   string l2string(long l)
      {
         string str;
         char tmp[100];
         sprintf(tmp,"%ld",l);
         str = tmp;
         return str;
      }


      string bigint2string(uint64_t l)
      {
         string str;
         uint64_t tmp = l;
         while (tmp)
         {
            uint64_t a = tmp % 10;
            str = (char)(a + 48) + str;
            tmp /= 10;
         }
         if (!str.get_length())
         {
            str = "0";
         }
         return str;
      }*/

   int32_t to_int(const char * psz)
   {
      return atoi_dup(psz);
   }

   uint32_t to_uint(const char * psz)
   {
      return (uint32_t) atoi64_dup(psz);
   }

   int64_t to_int64(const string & str)
   {

      int32_t i = 0;

      for (; i < str.get_length() && isspace(str[i]); i++);

      bool bNegative = str[i] == '-';

      if(bNegative)
         i++;

      uint64_t ui = 0;

      for(; i < str.get_length() && isdigit(str[i]); i++)
      {
         ui = ui * 10 + str[i] - 48;
      }

      if(bNegative)
         return -(int64_t) ui;
      else
         return (int64_t) ui;
   }

   int64_t to_int64(const char * psz)
   {

      int32_t i = 0;

      for (; *psz != '\0' && i < 30 && isspace((uchar ) *psz); i++, psz++);

      bool bNegative = *psz == '-';

      if(bNegative)
         psz++;

      uint64_t ui = 0;

      for(; *psz != '\0' && i < 30 && isdigit((uchar ) *psz); psz++, i++)
      {
         ui = ui * 10 + *psz - 48;
      }

      if(bNegative)
         return -(int64_t) ui;
      else
         return (int64_t) ui;

   }

   uint64_t to_uint64(const string & str)
   {

      int32_t i = 0;

      for (; i < str.get_length() && isspace(str[i]); i++);

      uint64_t ui = 0;

      for(; i < str.get_length() && isdigit(str[i]); i++)
      {
         ui = ui * 10 + str[i] - 48;
      }

      return ui;

   }

   uint64_t to_uint64(const char * psz)
   {

      int32_t i = 0;

      for (; *psz != '\0' && i < 30 && isspace(*psz); i++, psz++);

      uint64_t ui = 0;

      for(; *psz != '\0' && i < 30 && isdigit(*psz); psz++, i++)
      {
         ui = ui * 10 + *psz - 48;
      }

      return ui;

   }



   void increment_digit_letter(string & str)
   {
      strsize i = str.get_length() - 1;
      while(i >= 0)
      {
         if(str[i] >= '0' && str[i] <= '8')
         {
            str = str.Left(i) + string((char)(str[i] + 1), 1) + str.Right(str.get_length() - i - 1);
            break;
         }
         else if(str[i] == '9')
         {
            str = str.Left(i) + string((char)('a'), 1) + str.Right(str.get_length() - i - 1);
            break;
         }
         else if(str[i] >= 'a' && str[i] <= 'y')
         {
            str = str.Left(i) + string((char)(str[i] + 1), 1) + str.Right(str.get_length() - i - 1);
            break;
         }
         else if(str[i] == 'z')
         {
            str = str.Left(i) + string((char)('0'), 1) + str.Right(str.get_length() - i - 1);
            i--;
         }
      }
   }


   bool  while_begins_with_chars_eat(string & str, const char * lpcszChars)
   {
      int32_t i = 0;
      for(i = 0; i < str.get_length(); i++)
      {
         if(strchr(lpcszChars, str[i]) == NULL)
            break;
      }
      str = str.Mid(i);
      return i > 0;
   }

   bool  while_begins_with_chars_eat_ci(string & str, const char * lpcszChars) // case insensitive
   {
      int32_t i = 0;
      for(i = 0; i < str.get_length(); i++)
      {
         if(strchr(lpcszChars, tolower(str[i])) == NULL)
            break;
      }
      str = str.Mid(i);
      return i > 0;
   }


   void begin(wstring & wstr, const unichar * lpcszPrefix)
   {

      strsize iPrefixLen = wcslen_dup(lpcszPrefix);
      if(natural(wstr.storage_size()) >= ((wstr.get_length() + iPrefixLen + 1) * sizeof(unichar)))
      {
         memmove(&wstr[iPrefixLen], (const unichar *) wstr, (wstr.get_length() + 1) * sizeof(unichar));
         memcpy_dup(wstr, lpcszPrefix, iPrefixLen);
      }
      else
      {
         wstring wstrNew;
         wstrNew.alloc((wstr.get_length() + iPrefixLen + 1) * sizeof(unichar));
         memcpy_dup(&wstrNew[iPrefixLen], (const unichar *) wstr, (wstr.get_length() + 1) * sizeof(unichar));
         memcpy_dup(wstrNew, lpcszPrefix, iPrefixLen * sizeof(unichar));
         wstr.attach(wstrNew.detach());
      }

   }


   bool begins(const unichar * lpcsz, const unichar * lpcszPrefix)
   {
      if(lpcsz == NULL || *lpcsz == L'\0')
      {
         if(lpcszPrefix == NULL || *lpcszPrefix == L'\0')
         {
            return true;
         }
         else
         {
            return false;
         }
      }
      while(*lpcsz == *lpcszPrefix)
      {
         lpcsz++;
         lpcszPrefix++;
         if(*lpcsz == L'\0')
         {
            if(*lpcszPrefix == L'\0')
               return true;
            else
               return false;
         }
         else if(*lpcszPrefix == L'\0')
         {
            return true;
         }
      }
      return false;
   }

   bool begins_with(const unichar * lpcsz, const unichar * lpcszPrefix)
   {
      return begins(lpcsz, lpcszPrefix);
   }

   bool begins(const wstring & str, const unichar * lpcszPrefix)
   {
      if(str.is_empty())
      {
         if(lpcszPrefix == NULL || *lpcszPrefix == L'\0')
         {
            return true;
         }
         else
         {
            return false;
         }
      }
      const unichar * lpcsz = str;
      while(*lpcsz == *lpcszPrefix)
      {
         lpcsz++;
         lpcszPrefix++;
         if(*lpcsz == L'\0')
         {
            if(*lpcszPrefix == L'\0')
               return true;
            else
               return false;
         }
         else if(*lpcszPrefix == L'\0')
         {
            return true;
         }
      }
      return false;
   }

   bool begins_with(const wstring & str, const unichar * lpcszPrefix)
   {
      return begins(str, lpcszPrefix);
   }



   ///
   /// \param[in] lpcsz Parsed string.
   /// \param[in] lpcszPrefix Candidate prefix string.
   /// \return True if \p lpcsz is prefixed with \p lpcszPrefix.
   /// \note Case insensitive.
   ///
   bool begins_ci(const unichar * lpcsz, const unichar * lpcszPrefix)
   {
      if(lpcsz == NULL || *lpcsz == L'\0')
      {
         if(lpcszPrefix == NULL || *lpcszPrefix == L'\0')
         {
            return true;
         }
         else
         {
            return false;
         }
      }
      while(::str::ch::to_lower_case(*lpcsz) == ::str::ch::to_lower_case(*lpcszPrefix))
      {
         lpcsz++;
         lpcszPrefix++;
         if(*lpcsz == L'\0')
         {
            if(*lpcszPrefix == L'\0')
               return true;
            else
               return false;
         }
         else if(*lpcszPrefix == L'\0')
         {
            return true;
         }
      }
      return false;
   }

   bool begins_ci(const wstring & wstr, const unichar * lpcszPrefix)
   {
      return begins_ci_iws((const unichar *) wstr, lpcszPrefix);
   }

   // case insensitive, ignore white space - only in searched string
   bool begins_ci_iws(const unichar * lpcsz, const unichar * lpcszPrefix)
   {
      if(lpcsz == NULL || *lpcsz == L'\0')
      {
         if(lpcszPrefix == NULL || *lpcszPrefix == L'\0')
         {
            return true;
         }
         else
         {
            return false;
         }
      }
      while(*lpcsz && ::str::ch::is_space_char(*lpcsz))
         lpcsz++;
      if(!*lpcsz)
         return false;
      while(::str::ch::to_lower_case(*lpcsz) == ::str::ch::to_lower_case(*lpcszPrefix))
      {
         lpcsz++;
         lpcszPrefix++;
         if(*lpcsz == L'\0')
         {
            if(*lpcszPrefix == L'\0')
               return true;
            else
               return false;
         }
         else if(*lpcszPrefix == L'\0')
         {
            return true;
         }
      }
      return false;
   }

   bool begins_ci_iws(const wstring & wstr, const unichar * lpcszPrefix)
   {
      return begins_ci_iws((const unichar *) wstr, lpcszPrefix);
   }


   string          to_lower(const char * psz)
   {

      return string(psz).make_lower();

   }


   string          to_upper(const char * psz)
   {

      return string(psz).make_upper();

   }


   /** End \file Utility.cpp
   **   \date  2004-02-13
   **   \author grymse@alhem.net
   **/


   bool simple_escaped(const string & str, strsize pos)
   {

      if(pos == 0)
         return false;

      return str[pos - 1] == '\\' && !simple_escaped(str, pos - 1);

   }


   CLASS_DECL_AURA  bool           trim(string & str)
   {

      strsize iLen = str.length();

      str.trim();

      return iLen != str.length();

   }

   CLASS_DECL_AURA  bool         _008Trim(string & str)
   {

      ::count c = 1;

      bool bTrim = false;

      while(c > 0)
      {

         c = 0;

         if(trim_any_quotes(str))
         {

            c++;

            bTrim = true;

         }

         if(trim(str))
         {

            c++;

            bTrim = true;

         }

      }

      return bTrim;

   }


   CLASS_DECL_AURA  bool         trim_any_quotes(string & strParam)
   {

      string str(strParam);

      bool bTrim = false;

      while(paired_trim(str,'\'') || paired_trim(str,'\"'))
      {
         bTrim = true;
      }

      return bTrim;

   }

   CLASS_DECL_AURA  bool paired_trim(string & str,char ch)
   {

      if(str.get_length() <= 1)
      {

         return false;

      }

      if(str[0] != ch || str.last_char() != ch)
      {

         return false;

      }

      str = str.Mid(1,str.get_length() - 2);

      return true;

   }

   CLASS_DECL_AURA string zero_pad(const string & strSrc,int iPad)
   {

      string str(strSrc);

      ::zero_pad(str,iPad);

      return str;

   }


   ///
   /// q(between quotes :-) )-valid string
   /// from:http://www.zedwood.com/article/cpp-is-valid-utf8-string-function
   /// more invalid strings to test: http://stackoverflow.com/questions/1301402/example-invalid-utf8-string
   ///
   CLASS_DECL_AURA bool utf8_check_is_valid(const string& string)
   {
      strsize i, c, ix, n, j;
      for (i = 0, ix = string.length(); i < ix; i++)
      {
         c = (unsigned char)string[i];
         //if (c==0x09 || c==0x0a || c==0x0d || (0x20 <= c && c <= 0x7e) ) n = 0; // is_printable_ascii
         if (0x00 <= c && c <= 0x7f) n = 0; // 0bbbbbbb
         else if ((c & 0xE0) == 0xC0) n = 1; // 110bbbbb
         else if (c == 0xed && i < (ix - 1) && ((unsigned char)string[i + 1] & 0xa0) == 0xa0) return false; //U+d800 to U+dfff
         else if ((c & 0xF0) == 0xE0) n = 2; // 1110bbbb
         else if ((c & 0xF8) == 0xF0) n = 3; // 11110bbb
         //else if (($c & 0xFC) == 0xF8) n=4; // 111110bb //byte 5, unnecessary in 4 byte UTF-8
         //else if (($c & 0xFE) == 0xFC) n=5; // 1111110b //byte 6, unnecessary in 4 byte UTF-8
         else return false;
         for (j = 0; j < n && i < ix; j++)   // n bytes matching 10bbbbbb follow ?
         {
            if ((++i == ix) || (((unsigned char)string[i] & 0xC0) != 0x80))
               return false;
         }
      }
      return true;

   }


   ///
   /// q(between quotes :-) )-valid string
   ///
   CLASS_DECL_AURA string q_valid(string str)
   {

      if (str.is_empty())
      {

         return str;

      }

      if (!utf8_check_is_valid(str))
      {

         str = ::str::international::multibyte_to_utf8(::str::international::CodePageAnsi, str);

         if (!utf8_check_is_valid(str))
         {

            return "";

         }

      }

      return str;

   }


   string signed_double(double d)
   {

      if (d > 0.0)
      {

         return "+" + ::str::from(d);

      }
      else if (d < 0.0)
      {

         return ::str::from(d);

      }
      else
      {

         return "0.0";

      }

   }

   string signed_int(int i)
   {

      if (i > 0)
      {

         return "+" + ::str::from(i);

      }
      else if (i < 0)
      {

         return ::str::from(i);

      }
      else
      {

         return "0";

      }

   }


   CLASS_DECL_AURA bool is_true(string str)
   {

      str.trim();

      if (str.is_empty())
      {

         return false;

      }

      if (str.compare_ci("yes") == 0)
      {

         return true;

      }

      if (str.compare_ci("true") == 0)
      {

         return true;

      }

      if (str.compare_ci("on") == 0)
      {

         return true;

      }

      if (str.compare_ci("enable") == 0)
      {

         return true;

      }

      if (str.compare_ci("enabled") == 0)
      {

         return true;

      }

      if (str.compare_ci("check") == 0)
      {

         return true;

      }

      if (str.compare_ci("checked") == 0)
      {

         return true;

      }

      for (index i = 0; i < str.get_length(); i++)
      {

         if (i == 0 && (str[i] == '+' || str[i] == '-'))
         {

         }
         else if (!isdigit_dup(str[i]))
         {

            return false;

         }

      }

      if (atoi_dup(str) == 0)
      {

         return false;

      }

      return true;

   }

   CLASS_DECL_AURA void replace_tab(strsize iOffset, string & strParam, int iWidth, array < strsize * > intptra, strsize_array * piaTab)
   {

      const char * psz = strParam;

      string str;

      string strTab;

      while (*psz)
      {

         string strChar = ::str::get_utf8_char(psz);

         if (strChar.is_empty())
         {

            break;

         }
         else if (strChar == "\t")
         {

            strTab = string(iWidth - (iOffset % iWidth), ' ');

            for (auto pi : intptra)
            {

               if (*pi > iOffset)
               {

                  (*pi) += strTab.get_length() - 1;

               }

            }

            str += strTab;

            iOffset += strTab.get_length();

            if (piaTab != NULL)
            {

               piaTab->add(strTab.get_length());

            }

         }
         else
         {

            str += strChar;

            iOffset++;

         }

         psz += strChar.get_length();

      }

      strParam = str;

   }

   CLASS_DECL_AURA void replace_tab(strsize iOffset, string & strParam, int iWidth, strsize_array * piaTab)
   {

      return replace_tab(iOffset, strParam, iWidth, array < strsize * >(), piaTab);

   }

   CLASS_DECL_AURA string block(char ch, int32_t iSize)
   {
      string str;
      for (int32_t i = 0; i < iSize; i++)
      {
         str += ch;
      }
      return str;
   }


   CLASS_DECL_AURA void fill(string & str, char ch)
   {

      str = block(ch, (int32_t)str.get_length());

   }


} // namespace str


template < >
CLASS_DECL_AURA void to_string(string & str, const float & f)
{

   char sz[256];
   sprintf(sz, "%f", f);
   str = sz;
   str.replace(",", ".");

}


template < >
CLASS_DECL_AURA void to_string(string & str, const double & d)
{

   char sz[256];
   sprintf(sz, "%f", d);
   str = sz;
   str.replace(",", ".");

}



