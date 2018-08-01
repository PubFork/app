#include "framework.h"


istring::istring(::aura::application * papp)
{

   m_papp = papp;

}
      
istring::~istring()
{
}


void istring::update_string()
{

   m_str = m_papp->lstr(m_strTemplate, m_strTemplate);

}


istring & istring::operator = (const char * psz)
{
   
   m_strTemplate = psz;

   update_string();

   return *this;

}


