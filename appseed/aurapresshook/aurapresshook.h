#pragma once


extern "C"
{


void basecore_init();
void basecore_term();
void * basecore_app_indicator_new(const char * pszId, const char * pszIcon, const char * pszFolder, struct basecore_bridge * pi);
void basecore_app_indicator_term(void * pind);


} // extern "C"


struct basecore_bridge
{
public:

   
   basecore_bridge() {}
   virtual ~basecore_bridge() {}


};

