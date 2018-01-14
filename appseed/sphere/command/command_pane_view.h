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
      
      
      void rotate();
      
      void on_create_view(::user::view_creator_data * pcreatordata);
      void on_show_view();

      virtual void install_message_routing(::message::sender * pinterface);

	   virtual void on_update(::user::impact * pSender, LPARAM lHint, ::object* pHint);
	   virtual bool pre_create_window(::user::create_struct& cs);


      void OnFileManagerOpenFile(::filemanager::data * pdata, ::fs::item_array & itema);

      DECL_GEN_SIGNAL(_001OnMenuMessage);


   
	   virtual void assert_valid() const;
	   virtual void dump(dump_context & dumpcontext) const;
   

	   DECL_GEN_SIGNAL(_001OnCreate);
	   DECL_GEN_SIGNAL(_001OnSize);
   };


} // namespace prompt



