#pragma once


namespace simpledb
{


   class CLASS_DECL_AXIS record_row :
      virtual public ::serializable
   {
   public:


      table *     m_ptable;
      stringa     m_straFields;
      var         m_var;


      virtual void stream(serialize & serialize);


   };


} // namespace simpledb



