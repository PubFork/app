#pragma once


namespace message
{


   class CLASS_DECL_AURA id :
      public ::id
   {
      public:


         ::message::e_type         m_emessagetype;


         id(::message::e_type etype = ::message::type_null)
         {

            m_emessagetype = etype;

         }


         id(int64_t i)
         {

            m_emessagetype = type_message;

            ::id::operator = ((int32_t) i);

         }



         id(const ::id id)
         {

            if (id.is_integer())
            {

               m_emessagetype = type_message;

            }
            else
            {

               m_emessagetype = type_command;

            }

            ::id::operator = (id);

         }

         id(const id & id)
         {

            m_emessagetype = id.m_emessagetype;
            ::id::operator = (id);

         }

         id(::id id, ::message::e_type etype)
         {

            m_emessagetype = etype;
            ::id::operator = (id);

         }

         bool operator == (int64_t i) const
         {

            return is_integer() && m_i == i;

         }

         bool operator == (int32_t i) const
         {

            return is_integer() && m_i == i;

         }

         bool operator == (const id & id) const
         {

            return m_emessagetype == id.m_emessagetype && ::id::operator==(id);

         }

         id & operator = (const id & id)
         {

            if (this != &id)
            {

               m_emessagetype = id.m_emessagetype;

               ::id::operator = (id);

            }

            return *this;

         }


         id & operator = (::message::e_type etype)
         {

            m_emessagetype = etype;

            return *this;

         }

   };



} // namespace




template <  >
inline UINT HashKey < const ::message::id & >(const ::message::id & key)
{

   return (UINT) (((int64_t)key.m_emessagetype) ^ HashKey < const ::id & >((const ::id &) key));

}
