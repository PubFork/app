#pragma once


#include "app/appseed/axis/axis/axis/axis.h"


#include "app/appseed/aura/aura/node/ansios/ansios.h"
#include "app/appseed/aura/aura/node/ios/ios.h"



string get_error_message(DWORD dwError);

sp(::aura::application)     ios_instantiate_application(sp(::aura::application) pappSystem, const char * pszId);


#include "ios_implementation.h"
#include "ios_axis_dir.h"
#include "ios_axis_file_system.h"
#include "ios_factory_exchange.h"
#include "ios_port_forward.h"
#include "ios_copydesk.h"
#include "ios_crypto.h"
#include "ios_file_set.h"




WINBOOL PeekMessage(
                    LPMESSAGE lpMsg,
                    oswindow hWnd,
                    UINT wMsgFilterMin,
                    UINT wMsgFilterMax,
                    UINT wRemoveMsg);

WINBOOL GetMessage(
                   LPMESSAGE lpMsg,
                   oswindow hWnd,
                   UINT wMsgFilterMin,
                   UINT wMsgFilterMax);



int32_t CLASS_DECL_AXIS __ios_main(int32_t argc, char * argv[]);


CLASS_DECL_AXIS void vfxThrowFileException(sp(::aura::application) papp, int32_t cause, LONG lOsError, const char * lpszFileName = NULL);





