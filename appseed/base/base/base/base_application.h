#pragma once


namespace base
{


   class CLASS_DECL_BASE application :
      virtual public ::axis::application,
      virtual public ::user::form_callback
   {
   public:





      bool                                            m_bBaseProcessInitialize;
      bool                                            m_bBaseProcessInitializeResult;

      bool                                            m_bBaseInitializeInstance;
      bool                                            m_bBaseInitializeInstanceResult;

      bool                                            m_bBaseInitialize1;
      bool                                            m_bBaseInitialize1Result;

      bool                                            m_bBaseInitialize;
      bool                                            m_bBaseInitializeResult;



      application();
      virtual ~application();




      virtual bool process_init() override;



      virtual sp(type) user_default_controltype_to_typeinfo(::user::e_control_type econtroltype);


      virtual void on_create_view(::user::view_creator_data * pcreatordata);
      void process_message_filter(int32_t code,::message::message * pobj) override;



      //virtual string get_cred(const string & strRequestUrl,const RECT & rect,string & strUsername,string & strPassword,string strToken,string strTitle,bool bInteractive);

      virtual ::user::user * create_user();

      virtual bool on_thread_on_idle(::thread_impl * pimpl,LONG lCount);

      virtual bool is_window(::user::primitive * pui) override;

      using ::aura::application::send_message;
      virtual LRESULT send_message(::user::primitive * pui,UINT message,WPARAM wparam = 0,lparam lparam = 0) override;

      virtual oswindow get_safe_handle(::user::primitive * pui) override;
      virtual void dispatch_user_message(::user::message * pmessage);
      virtual void dispatch_user_message_object(::object * pobject) override;
      virtual ::user::interaction * get_parent(::user::interaction * pui);
      virtual bool enable_window(::user::primitive * pui,bool bEnable = true) override;
      virtual bool set_window_text(::user::interaction * pui,const string & strText);

      //virtual void process_message(::message::base * pbase) override;
      virtual bool process_message(LPMESSAGE lpmessage) override;

      int32_t hotplugin_host_host_starter_start_sync(const char * pszCommandLine,::aura::application * papp,::hotplugin::host * phost,::hotplugin::plugin * pplugin) override;

      virtual ::user::interaction * FindWindow(const char * lpszClassName,const char * lpszWindowName);
      virtual ::user::interaction * FindWindowEx(oswindow oswindowParent,oswindow oswindowChildAfter,const char * lpszClass,const char * lpszWindow);
      virtual bool post_user_message(::thread * pthread,::user::primitive * pui,UINT message,WPARAM wparam = 0,lparam lparam = 0) override;



      using ::axis::application::on_control_event;
      using ::user::form_callback::on_control_event;


      virtual void remove_document_template(::user::impact_system * pimpactsystem);

//      virtual ::user::style * userstyle();
//
//      virtual ::user::style * userstyle(::user::e_schema estyle);

      //virtual int32_t exit_instance();

      virtual void term_application() override;


      virtual void SetCurrentHandles() override;

      virtual ::visual::icon * set_icon(object * pobject, ::visual::icon * picon, bool bBigIcon) override;


      virtual ::visual::icon * get_icon(object * pobject, bool bBigIcon) const override;

      virtual void on_control_event(::user::control_event * pevent) override;

      virtual ::user::interaction * create_menu_interaction();

   };


} // namespace base






