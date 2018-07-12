#include "framework.h"


namespace simpledb
{


//      table *     m_ptable;
   //    stringa     m_straFields;
   //  var         m_var;

   void record_row::io(stream & serialize)
   {
      if (serialize.is_storing())
      {

         if (m_straFields.get_size() <= 0)
         {
            var_array vara = m_var.vara();
            if (vara.get_count() != m_ptable->m_fielddefinition.get_count())
            {
               _throw(simple_exception(get_app(), "no fields specified and values ::count is different from table '" + m_ptable->m_strName + "' field count"));
            }
            else
            {
               for (int32_t i = 0; i < m_ptable->m_fielddefinition.get_count(); i++)
               {
                  ::database::field_definition_item & item = m_ptable->m_fielddefinition[i];
                  var var = vara[i];
                  if (item.m_etype == ::database::field_definition_item::type_text)
                  {
                     if (item.m_iSize > 0)
                     {
                        strsize iLen = MIN(255, var.get_string().get_length());
                        serialize << (char)iLen;
                        serialize.write(var.get_string().Left(iLen), iLen);
                        if (iLen < item.m_iSize)
                        {
                           string str(' ', item.m_iSize - iLen);
                           serialize.write(str, item.m_iSize - iLen);
                        }
                     }
                  }
               }
            }

         }
      }
      else
      {
         if (m_straFields.get_size() <= 0 || (m_straFields.get_size() == 1 && m_straFields[0] == "*"))
         {
            for (int32_t i = 0; i < m_ptable->m_fielddefinition.get_count(); i++)
            {
               ::database::field_definition_item & item = m_ptable->m_fielddefinition[i];
               var var;
               if (item.m_etype == ::database::field_definition_item::type_text)
               {
                  if (item.m_iSize > 0)
                  {
                     byte uchLen;
                     serialize >> uchLen;
                     string str;
                     serialize.read(str.GetBufferSetLength(uchLen), uchLen);
                     var = str;
                     str.ReleaseBuffer(uchLen);
                     if (uchLen < item.m_iSize)
                     {
                        char sz[255];
                        serialize.read(sz, item.m_iSize - uchLen);
                     }
                  }
               }
               m_var.vara().add(var);
            }
         }


      }
   }


} // namespace simpledb


