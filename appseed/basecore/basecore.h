#pragma once

extern "C"
{

void basecore_init();
void basecore_term();
void * basecore_app_indicator_new(const char * pszId, const char * pszIcon, const char * pszFolder, struct user_notify_icon_appindicator_bridge * pi);
void basecore_step(void * pind);
void basecore_app_indicator_term(void * pind);


} // extern "C"


struct user_notify_icon_appindicator_bridge
{
public:


   virtual void __open() = 0;
   virtual void __close() = 0;
   virtual void __quit() = 0;
   virtual bool __close_is_closed() = 0;


   virtual int bridge_extra_action_count() = 0;
   virtual void notification_area_action_info(char ** ppszName, char ** ppszId, char ** ppszLabel, char ** ppszAccelerator, char ** ppszDescription, int iIndex) = 0;
   virtual void notification_area_extra_action(const char * pszId) = 0;

};

