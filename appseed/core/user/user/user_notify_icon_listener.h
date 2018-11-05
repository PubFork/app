#pragma once


namespace user
{


   class CLASS_DECL_CORE notify_icon_listener
   {
   public:


      class CLASS_DECL_CORE item :
         virtual public object
      {
      public:

         string m_strName;
         string m_strId;
         string m_strLabel;
         string m_strAccelerator;
         string m_strDescription;

         item();

         item(string strName, string strId = "", string strLabel = "", string strAccelerator = "", string strDescription = "");

         virtual ~item();

      };

      class CLASS_DECL_CORE item_array :
         virtual public array < item >
      {
      public:

      };


      item_array m_notifyiconitema;


      notify_icon_listener();
      virtual ~notify_icon_listener();


      virtual void OnNotifyIconMessage(UINT uiNotifyIcon, UINT message);
      virtual void OnNotifyIconContextMenu(UINT uiNotifyIcon);
      virtual void OnNotifyIconLButtonDblClk(UINT uiNotifyIcon);
      virtual void OnNotifyIconLButtonDown(UINT uiNotifyIcon);


      virtual int _get_notification_area_action_count();
      virtual bool _get_notification_area_action_info(char ** ppszName, char ** ppszId, char ** ppszLabel, char ** ppszAccelerator, char ** ppszDescription, int iIndex);
      virtual void notification_area_action(const char * pszId);


      virtual bool notify_icon_insert_item(index iIndex, string strName, string strId = "", string strLabel = "", string strAccelerator = "", string strDescription = "");

   };


} // namespace user



