#pragma once


namespace xml
{


   class node;

   // Parse info.
   class CLASS_DECL_AURA parse_info
   {
   public:

      
      bool               m_bTrimValue;        // [set] do trim when parse?
      bool               m_bEntityValue;      // [set] do convert from reference to entity? ( &lt; -> < )
      entities *        m_pentities;         // [set] entity table for entity decode
      char              m_chEscapeValue;     // [set] escape value (default '\\')
      bool              m_bForceParse;       // [set] force parse even if xml is not welformed

      string            m_strXml;            // [get] xml source
      bool               m_bErrorOccur;       // [get] is occurance of error?
      char *             m_pszErrorPointer;   // [get] error position of xml source
      e_parse_error     m_eparseerror;         // [get] error code
      string            m_strError;          // [get] error string

      sp(::xml::document)        m_pdoc;

      
      parse_info(::aura::application * papp);
      
      
   };

   
   CLASS_DECL_AURA char * LoadOtherNodes( node * node, bool* pbRet, const char * pszXml, parse_info * pi = NULL);
   

} // namespace xml





