#include "framework.h"

namespace xml
{
   disp_option::disp_option(::aura::application * papp)
   {
      newline = true;
      reference_value = true;
      m_pentities = &papp->m_paurasystem->m_pxml->m_entities;
      tab_base = 0;
      value_quotation_mark = '"';
   }


} // namespace xml