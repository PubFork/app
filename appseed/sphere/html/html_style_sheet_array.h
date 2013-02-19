#pragma once



namespace html
{

   class CLASS_DECL_ca2 style_sheet_array :
      public array_ptr_alloc < style_sheet >
   {
   public:


      style_sheet_array();


      style * rfind(const char * pszTag, const char * pszClass, const char * pszSubClass, const char * pszName);
      style * rfind_border_width(const char * pszTag, const char * pszClass, const char * pszSubClass, const char * pszName, float & f);
      style * rfind_border_color(const char * pszTag, const char * pszClass, const char * pszSubClass, const char * pszName, COLORREF & cr);

      style * greater(style * pstyle1, style * pstyle2);

      // retunrs true if determined
      bool greater(style * & pstyleRet, index & iRet, var & varRet, style * pstyle1, index i1, const var & var1, style * pstyle2, index i2, const var & var2);

   };

} // namespace html