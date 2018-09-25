#pragma once


namespace win32
{


   class CLASS_DECL_AURA dialog :
      virtual public window
   {
   public:


      LPCWSTR m_pszResource;


      dialog();
      dialog(::aura::application * papp, LPCWSTR pszResource);
      virtual ~dialog();


      bool create_dialog(window * pwindow = NULL);

      static INT_PTR CALLBACK DialogProc(HWND h, UINT u, WPARAM, LPARAM);
      virtual INT_PTR on_dialog_message(UINT uiMessage, WPARAM wparam, LPARAM lparam);

      virtual bool on_init_dialog();
      virtual void on_close();
      virtual void on_notify(NMHDR * p);
      virtual void on_notify(int iCode, int iId);

   };



} // namespace win32



