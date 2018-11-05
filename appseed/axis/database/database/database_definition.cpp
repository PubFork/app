#include "framework.h"


namespace database
{


   DbErrors::DbErrors(::aura::application * papp) :
      object(papp)
   {

      string str;

      str = "Unknown CDatabase Error";

      TRACE(str);

      m_pszMessage = strdup(str);

   }


   DbErrors::DbErrors(::aura::application * papp,const char *msg, ...) :
      object(papp)
   {

      string str;

      va_list vl;
      va_start(vl, msg);
      str.Format(msg, vl);
      va_end(vl);

      str = "CDatabase Error: " + str;

      TRACE(str);

      m_pszMessage = strdup(str);


   }


   parameter_list & parameter_list::operator = (const parameter_list & paramlist)
   {
      m_stra = paramlist.m_stra;
      m_fieldvaluea = paramlist.m_fieldvaluea;
      return *this;
   }

   field_properties::field_properties()
   {
   }

   field_properties::field_properties(const field_properties & field_properties)
   {
      operator = (field_properties);
   }

   field_properties & field_properties::operator = (const field_properties & field_properties)
   {
      if(this != &field_properties)
      {
         name           = field_properties.name;
         display_name   = field_properties.display_name;
         type           = field_properties.type;
         field_table    = field_properties.field_table;
         read_only      = field_properties.read_only;
         field_len      = field_properties.field_len;
         field_flags    = field_properties.field_flags;
         idx;
      }
      return *this;
   }

   field::field()
   {
   }

   field::field(const field & field)
   {
      operator = (field);
   }

   field & field::operator = (const field & field)
   {
      if(this != &field)
      {
         m_properties   = field.m_properties;
         m_value        = field.m_value;
      }
      return *this;
   }

   bool parameter_list::is_empty()
   {
      return this->get_size() <= 0;
   }

   ::count parameter_list::get_size()
   {
      return m_stra.get_size();
   }

   const char * parameter_list::GetKey(index i)
   {
      return m_stra[i];
   }

   var  & parameter_list::GetFieldValue(index i)
   {
      return m_fieldvaluea[i];
   }

   record::record()
   {
   }

   record::record(const record & record)
   {
      operator = (record);
   }


   record::~record()
   {

   }


   void query_data::io(stream & serialize)
   {

      serialize.stream_array(*this);

   }


   record & record::operator = (const record & record)
   {
      if(this != &record)
      {
         var_array::operator = ((const var_array &) record);
      }
      return *this;
   }


   result_set::result_set()
   {

   }


   result_set::result_set(::aura::application * papp) :
      ::object(papp)
   {

   }


   result_set::result_set(const result_set & set) :
      object(set.get_app())
   {

      operator = (set);

   }


   result_set & result_set::operator = (const result_set & set)
   {

      if(&set != this)
      {

         m_record_header     = set.m_record_header;

         m_records           = set.m_records;

      }

      return *this;

   }


   void result_set::io(stream & serialize)
   {

      serialize.stream_array(m_record_header);
      serialize.stream_array(m_records);

   }


   void field_properties::io(stream & serialize)
   {

      serialize(name);
      serialize(display_name);
      serialize((i32 &) type);
      serialize(field_table); //?
      serialize(read_only);
      serialize(field_len);
      serialize(field_flags);
      serialize(idx);

   }


} // namespace vmssqlite



