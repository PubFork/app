#include "framework.h"


namespace user
{


   list_view::list_view()
   {

   }


   list_view::~list_view()
   {

   }


   void list_view::install_message_routing(::message::sender * psender)
   {

      BASE_VIEW::install_message_routing(psender);

   }


   void list_view::_001OnInitialUpdate()
   {

      BASE_VIEW::_001OnInitialUpdate();

      //_001UpdateColumns();

   }


   void list_view::_001OnSelectionChange()
   {

      BASE_VIEW::_001OnSelectionChange();

      if (GetParentFrame() != NULL)
      {

         GetParentFrame()->SetActiveView(this);

      }

   }

} // namespace user




