#pragma once


#include "collection_iterable.h"


namespace str
{

   namespace iter
   {



   } // namespace iter


} // namespace str

template < typename ITERABLE >
class string_iterable :
   public ITERABLE
{
public:

   typedef typename ITERABLE::iterator    iterator;
   typedef typename ITERABLE              Iterable;
   typedef typename ITERABLE::iterator    iterator;
   typedef typename Iterable::BASE_TYPE   Type;
   typedef iterable                       Container;

   iterator add(const char * psz);

   iterator add(const unichar * pwsz);

   iterator add(char ch);

   iterator add(unichar wch);

   iterator add(const var & var);

   iterator add(const property & prop);

   iterator add(const id & id);

   iterator add(const Type & newElement);

};


template < typename ITERABLE >
typename string_iterable < ITERABLE >::iterator string_iterable < ITERABLE >::add(const char * psz)
{
   index nIndex = this->m_nSize;
   set_at_grow(nIndex, psz);
   return m_pData + nIndex;
}


template < typename ITERABLE >
typename string_iterable < ITERABLE >::iterator string_iterable < ITERABLE >::add(const unichar * pwsz)
{
   index nIndex = this->m_nSize;
   set_at_grow(nIndex, (Type) ::str::international::unicode_to_utf8(pwsz));
   return m_pData + nIndex;
}



template < typename ITERABLE >
typename string_iterable < ITERABLE >::iterator string_iterable < ITERABLE >::add(char ch)
{
   if (ch == '\0')
      return add("");
   else
   {
      char str[16];
      str[0] = ch;
      str[1] = '\0';
      return add(str);
   }
}


template < typename ITERABLE >
typename string_iterable < ITERABLE >::iterator string_iterable < ITERABLE >::add(unichar wch)
{
   if (wch == L'\0')
      return add("");
   else
   {
      unichar wstr[16];
      wstr[0] = wch;
      wstr[1] = L'\0';
      return add(wstr);
   }
}


template < typename ITERABLE >
typename string_iterable < ITERABLE >::iterator string_iterable < ITERABLE >::add(const Type & newElement)
{

   index nIndex = this->m_nSize;

   set_at_grow(nIndex, newElement);

   return m_pData + nIndex;

}


//template < typename ITERABLE >
//void string_iterable < ITERABLE >::push_back(const Type & newElement)
//{
//   index nIndex = this->m_nSize;
//   set_at_grow(nIndex, newElement);
//}




template < typename ITERABLE >
typename string_iterable < ITERABLE >::iterator string_iterable < ITERABLE >::add(const id & id)
{
   if (id.is_null())
   {

      return end();

   }
   else
   {
      add(id);
   }
}




//// same as clear
//void string_iterable < ITERABLE >::remove_all()
//{
//   set_size(0);
//}
//
//// same as remove all
//void string_iterable < ITERABLE >::clear()
//{
//   set_size(0);
//}




template < typename ITERABLE >
typename ITERABLE::iterator string_iterable < ITERABLE >::add(const var & var)
{
   if (var.is_empty())
   {
      return end();
   }
   else if (var.get_type() == var::type_stra)
   {
      ::lemon::array::add(*this, var.stra());
   }
   else if (var.cast < string_array < Type > >() != NULL)
   {
      ::lemon::array::add(*this, *var.cast < string_array < Type > >());
   }
   else if (var.get_type() == var::type_vara)
   {
      for (int32_t i = 0; i < var.vara().get_count(); i++)
      {
         ::lemon::array::add(*this, var.vara()[i].get_string());
      }
   }
   else if (var.get_type() == var::type_inta)
   {
      for (int32_t i = 0; i < var.inta().get_count(); i++)
      {
         ::lemon::array::add(*this, ::str::from(var.inta()[i]));
      }
   }
   else if (var.get_type() == var::type_propset)
   {
      for (auto assoc : var.propset())
      {
         ::lemon::array::add(*this, assoc.get_value().get_string());
      }
   }
   else
   {
      ::lemon::array::add(*this, var.get_string());
   }

   return upper_bound();

}




template < typename ITERABLE >
typename ITERABLE::iterator string_iterable < ITERABLE >::add(const property & prop)
{

   return add(prop.get_value());

}
