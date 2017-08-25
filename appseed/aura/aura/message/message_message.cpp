#include "framework.h"


namespace message
{


   message::message(::aura::application * papp) :
      object(papp)
   {

      common_construct();

   }

   message::message(::message::e_type etype)
   {

      common_construct(etype);

   }

   message::~message()
   {

   }


   void message::common_construct(::message::e_type etype)
   {

      m_id = etype;
      m_psender = NULL;
      m_wparam = 0;
      m_iRouteIndex = -1;
      m_iParam = 0;
      m_bRet = false;

   }



   bool message::route()
   {

      if (m_routea.is_empty())
      {

         return true;

      }

      if (m_iRouteIndex >= m_routea.get_count())
      {

         m_iRouteIndex = m_routea.get_upper_bound();

      }

      if (m_iRouteIndex < 0)
      {

         return true;

      }

      m_routea[m_iRouteIndex]->route_message(this);

      return m_bRet;

   }


   bool message::all_previous()
   {

      while (true)
      {

         bool bRet = previous();

         if (bRet)
         {

            break;

         }

      }

      return true;

   }


   bool message::previous()
   {
      
      m_iRouteIndex--;

      return route();

   }



} // namespace message



