#include "framework.h"


namespace user
{


   primitive::primitive()
   {

      m_puiThis = NULL;

   }


   primitive::~primitive()
   {


   }


#ifdef WINDOWSEX


   bool primitive::GetWindowPlacement(WINDOWPLACEMENT * lpwndpl)
   {

      UNREFERENCED_PARAMETER(lpwndpl);

      return false;

   }

   bool primitive::SetWindowPlacement(const WINDOWPLACEMENT * lpcwndpl)
   {

      UNREFERENCED_PARAMETER(lpcwndpl);

      return false;

   }


#endif // WINDOWSEX


   bool primitive::SetPlacement(const RECT & rect,UINT nFlags)
   {

      UNREFERENCED_PARAMETER(rect);
      UNREFERENCED_PARAMETER(nFlags);

      return false;

   }

   int32_t primitive::get_total_page_count(::job * pjob)
   {
      UNREFERENCED_PARAMETER(pjob);
      return 1;
   }



   void primitive::_001OnTimer(::timer * ptimer)
   {

      UNREFERENCED_PARAMETER(ptimer);

   }

   //void primitive::add_thread(::thread * pthread)
   //{

   //   synch_lock sl(m_pmutex);

   //   m_threadptra.add(pthread);

   //}


   //void primitive::remove_thread(::thread * pthread)
   //{

   //   synch_lock sl(m_pmutex);

   //   m_threadptra.remove(pthread);

   //}

   bool primitive::enable_window(bool bEnableWindow)
   {

      return true;

   }


   LRESULT primitive::send_message(UINT uiMessage, WPARAM wparam, lparam lparam)
   {

      _throw(interface_only_exception(get_app()));

      return 0;

   }


   bool primitive::post_message(UINT message, WPARAM wParam, lparam lParam)
   {

      _throw(interface_only_exception(get_app()));

      return false;

   }


//   void check::_001SetCheck(::check::e_check echeck,::action::context)
//   {
//
//
//   }
//
//
//
//   void set_text::_001SetText(const string & strText,::action::context)
//   {
//
//   }


} // namespace user
























