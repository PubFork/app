#pragma once


namespace simpledb
{


   class CLASS_DECL_AXIS record_row :
      virtual public ::object
   {
   public:


      table *     m_ptable;
      stringa     m_straFields;
      var         m_var;


      virtual void io(stream & stream);


   };


} // namespace simpledb



