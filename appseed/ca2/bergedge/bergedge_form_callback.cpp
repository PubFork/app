#include "framework.h"

namespace bergedge
{

   form_callback::form_callback()
   {
   }

   form_callback::~form_callback()
   {
   }

   void form_callback::on_update(::user::form * pview, ::view* pSender, LPARAM lHint, ::gen::object* phint) 
   {
      UNREFERENCED_PARAMETER(pview);
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(lHint);
      UNREFERENCED_PARAMETER(phint);

   }


   bool form_callback::BaseOnControlEvent(::user::form * pview, ::user::control_event * pevent)
   {
      UNREFERENCED_PARAMETER(pview);
      UNREFERENCED_PARAMETER(pevent);
      return false;
   }

} // namespace bergedge