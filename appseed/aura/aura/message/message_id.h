#pragma once


namespace message
{


   class CLASS_DECL_AURA id
   {
   public:


      e_type         m_etype;
      ::id           m_id;


      id()
      {
         
         m_etype = type_null;

      }

      id(const id & id)
      {

         m_etype = id.m_etype;
         m_id = id.m_id;

      }

      id(::id id, e_type etype = type_id)
      {

         m_etype = etype;
         m_id = m_id;

      }

      bool operator == (const id & id) const
      {

         return m_etype == id.m_etype && m_id == m_id;

      }

      id & operator = (const id & id) 
      {

         if (this != &id)
         {

            m_etype = id.m_etype;

            m_id == m_id;

         }

         return *this;

      }

   };



} // namespace