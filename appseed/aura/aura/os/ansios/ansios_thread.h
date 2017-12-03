#ifndef AXIS_ANSIOS_THREAD_H
#define AXIS_ANSIOS_THREAD_H


#pragma once






class thread;
class mq;


CLASS_DECL_AURA mq * __get_mq(IDTHREAD id, bool bCreate);

CLASS_DECL_AURA int_bool WINAPI GetMessageW(LPMESSAGE lpMsg, oswindow oswindow, UINT wMsgFilterMin, UINT wMsgFilterMax);

#define GetMessage GetMessageW

CLASS_DECL_AURA int_bool WINAPI PeekMessageW(LPMESSAGE lpMsg, oswindow oswindow, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);

#define PeekMessage PeekMessageW

CLASS_DECL_AURA DWORD WINAPI GetThreadId(HTHREAD Thread);

#define PostThreadMessage  PostThreadMessageW

CLASS_DECL_AURA int_bool WINAPI PostThreadMessageW(IDTHREAD idthread, UINT Msg, WPARAM wParam, LPARAM lParam);

CLASS_DECL_AURA HTHREAD GetCurrentThread();

CLASS_DECL_AURA IDTHREAD GetCurrentThreadId();






#endif // AXIS_ANSIOS_THREAD_H










