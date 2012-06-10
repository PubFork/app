#include "framework.h"


namespace xml
{


   parse_info::parse_info(::ca::application * papp)
   {
      m_bTrimValue      = false; 
      m_bEntityValue    = true; 
      m_bForceParse     = false;
      m_pentities       = &(dynamic_cast < ::xml::application * > (papp))->m_entities; 
      
      m_bErrorOccur     = false;
      m_pszErrorPointer = NULL;
      m_eparseerror     = parse_error_welformed;
      m_chEscapeValue   = '\\';
   }


} // namespace xml



