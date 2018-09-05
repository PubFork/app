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

      return 2;

   }


   void notify_icon_listener::notification_area_action_info(char ** ppszName, char ** ppszId, char ** ppszLabel, char ** ppszAccelerator, char ** ppszDescription, int iIndex)
   {

      if(iIndex == 0)
      {

         string strAppTitle = Application.m_strAppTitle;

         if(strAppTitle.is_empty())
         {

            stringa stra;

            stra.explode("/", Application.m_strAppId);

            strAppTitle = stra.slice(1).implode(" ");

            strAppTitle.replace("_", " ");

            strAppTitle.replace("-", " ");

            strAppTitle.replace(".", " ");

         }

         *ppszName = strdup(strAppTitle);
         *ppszId = strdup("notify_icon_topic");
         *ppszLabel = strdup(Application.m_strAppTitle);
         *ppszAccelerator = strdup("");
         *ppszDescription = strdup(Application.m_strAppTitle);

      }
      else if(iIndex == 1)
      {

         *ppszName =strdup("Quit");
         *ppszId =strdup("app_exit");
         *ppszLabel = strdup("_Quit");
         *ppszAccelerator = strdup("ESC");
         *ppszDescription = strdup("Quit application");

      }

   }


   void notify_icon_listener::notification_area_action(const char * pszId)
   {

   }


} // namespace user
