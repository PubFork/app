#include "framework.h"


namespace user
{


   notify_icon_listener::notify_icon_listener()
   {

   }


   notify_icon_listener::~notify_icon_listener()
   {

   }


   void notify_icon_listener::OnNotifyIconMessage(UINT uiNotifyIcon, UINT message)
   {

      switch(message)
      {
      case WM_RBUTTONDOWN:

         OnNotifyIconContextMenu(uiNotifyIcon);

         break;

      case WM_LBUTTONDBLCLK:

         OnNotifyIconLButtonDblClk(uiNotifyIcon);

         break;

      case WM_LBUTTONDOWN:

         OnNotifyIconLButtonDown(uiNotifyIcon);

         break;

      }

   }


   void notify_icon_listener::OnNotifyIconContextMenu(UINT uiNotifyIcon)
   {

      UNREFERENCED_PARAMETER(uiNotifyIcon);

   }


   void notify_icon_listener::OnNotifyIconLButtonDblClk(UINT uiNotifyIcon)
   {

      UNREFERENCED_PARAMETER(uiNotifyIcon);

   }


   void notify_icon_listener::OnNotifyIconLButtonDown(UINT uiNotifyIcon)
   {

      UNREFERENCED_PARAMETER(uiNotifyIcon);

   }


   int notify_icon_listener::notification_area_action_count()
   {

      return 0;

   }


   void notify_icon_listener::notification_area_action_info(char ** ppszName, char ** ppszId, char ** ppszLabel, char ** ppszAccelerator, char ** ppszDescription, int iIndex)
   {

   }


   void notify_icon_listener::notification_area_action(const char * pszId)
   {

   }


} // namespace user
