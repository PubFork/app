#pragma once


namespace user
{


   class CLASS_DECL_CORE menu_list_view : 
      virtual public ::user::show < ::user::menu_list_window >
   {
   public:


      typedef ::user::show <  ::user::menu_list_window  > BASE;


      menu_list_view(::aura::application * papp);
      virtual ~menu_list_view();
      

      virtual void install_message_routing(::message::sender * pinterface) override;

      virtual bool pre_create_window(::user::create_struct & cs) override;

      //virtual void GuieProc(::message::message * pobj);

      virtual void route_command_message(::user::command * pcommand) override;

      bool load_menu(::xml::node * pnode, ::user::interaction * puiNotify, UINT uiCallbackMessage);
         
      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;
   
      virtual void PostNcDestroy() override;

   };

} // namespace user
