#pragma once


#include "app/appseed/sphere/command/command.h"


namespace userstack
{

   class view;
   class pane_view;
   class document;


   enum e_pane_view
   {
      pane_view_none,
      pane_view_context_menu,
      pane_view_winactionarea,
      pane_view_three_action_launch,
      pane_view_configuration,
      pane_view_properties,
   };




} // namespace userstack

#include "userstack_view.h"
#include "userstack_document.h"
#include "userstack_frame.h"
#include "userstack_form_callback.h"
#include "userstack_pane_view.h"
#include "userstack_pane_view_update_hint.h"


#include "userstack_application.h"



