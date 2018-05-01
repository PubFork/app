#include "framework.h"

namespace prompt
{

   form_callback::form_callback()
   {
   }

   form_callback::~form_callback()
   {
   }

   void form_callback::on_update(::user::form * pview, sp(::user::impact) pSender, LPARAM lHint, ::object* phint)
   {
      UNREFERENCED_PARAMETER(pview);
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(lHint);
      UNREFERENCED_PARAMETER(phint);
   }


   bool form_callback::BaseOnControlEvent(::user::control_event * pevent)
   {

      sp(::user::interaction) pui =  (this);

      if(pui != NULL && pui->GetParent() != NULL)
      {

         return pui->GetParent()->BaseOnControlEvent(pevent);

      }

      return false;

   }


} // namespace prompt



