#pragma once


namespace prompt
{


   class CLASS_DECL_SPHERE pane_view :
      virtual public ::userex::pane_tab_view,
      virtual public ::filemanager::callback,
      virtual public prompt::form_callback
   {
   public:


      pane_view(::aura::application * papp);
      virtual ~pane_view();


      void rotate() override;

      void on_create_view(::user::view_creator_data * pcreatordata) override;
      void on_show_view() override;

      virtual void install_message_routing(::message::sender * pinterface) override;

      virtual void on_update(::user::impact * pSender, LPARAM lHint, ::object* pHint) override;
      virtual bool pre_create_window(::user::create_struct& cs) override;


      void OnFileManagerOpenFile(::filemanager::data * pdata, ::fs::item_array & itema);

      DECL_GEN_SIGNAL(_001OnMenuMessage);

      virtual void on_control_event(::user::control_event * pevent) override;

      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;


      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnSize);
   };


} // namespace prompt



