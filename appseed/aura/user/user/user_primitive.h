#pragma once


namespace user
{


   class interaction;


   class CLASS_DECL_AURA primitive:
      virtual public command_target,
      virtual public ::aura::draw_interface
   {
   public:


      interaction *     m_puiThis;


      primitive();
      virtual ~primitive();

      inline oswindow get_safe_handle() const;

#ifdef WINDOWSEX

      virtual bool GetWindowPlacement(WINDOWPLACEMENT* lpwndpl);

      virtual bool SetWindowPlacement(const WINDOWPLACEMENT* lpwndpl);

#endif

      virtual bool SetPlacement(const RECT & rect,UINT nFlags = SWP_SHOWWINDOW);

      virtual int32_t get_total_page_count(::job * pjob);

      virtual void _001OnTimer(::timer * ptimer);

      virtual bool enable_window(bool bEnable = true);
      //virtual void _001SetCheck(check::e_check echeck,::action::context);
      //virtual void _001SetText(const string & strText,::action::context);

      virtual LRESULT send_message(UINT uiMessage, WPARAM wparam = 0, lparam lparam = 0);
      virtual bool post_message(UINT message, WPARAM wParam = 0, lparam lParam = 0);

   };


} // namespace user



