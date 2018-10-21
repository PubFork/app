#include "framework.h"


namespace user
{


   window_map::window_map(::aura::application * papp) :
      ::object(papp)
   {

   }


   window_map::~window_map()
   {

   }


   ::user::interaction_base * window_map::get(oswindow oswindow)
   {

      ::user::interaction_base * puibase;

      if (!m_map.Lookup(oswindow, puibase))
      {

         return NULL;

      }

      return puibase;

   }


   void window_map::set(oswindow oswindow, const ::user::interaction_base * puibase)
   {

      m_map.set_at(oswindow, (::user::interaction_base *) puibase);

   }


} // namespace user



