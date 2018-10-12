#pragma once


namespace user
{


   class CLASS_DECL_CORE notify_icon_listener
   {
   public:


      notify_icon_listener();
      virtual ~notify_icon_listener();


      virtual void OnNotifyIconMessage(UINT uiNotifyIcon, UINT message);
      virtual void OnNotifyIconContextMenu(UINT uiNotifyIcon);
      virtual void OnNotifyIconLButtonDblClk(UINT uiNotifyIcon);
      virtual void OnNotifyIconLButtonDown(UINT uiNotifyIcon);


      virtual int notification_area_action_count();
      virtual bool notification_area_action_info(char ** ppszName, char ** ppszId, char ** ppszLabel, char ** ppszAccelerator, char ** ppszDescription, int & iIndex);
      virtual void notification_area_action(const char * pszId);


   };


} // namespace user



