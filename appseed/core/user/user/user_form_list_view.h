#pragma once


namespace user
{


   class CLASS_DECL_CORE form_list_view:
      virtual public ::user::form_list,
      virtual public ::user::form_view,
      virtual public ::user::list_view
   {
   public:


      form_list_view();
      virtual ~form_list_view();


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;

      virtual bool pre_create_window(::user::create_struct & createstruct) override;

      virtual void install_message_routing(::message::sender *pinterface) override;

      virtual void _001OnDraw(::draw2d::graphics * pgraphics) override;
      virtual void _001OnTimer(::timer * ptime) override;

      virtual void route_command_message(::user::command * pcommand) override;
      virtual void on_update(::user::impact * pviewSender, LPARAM lparam, ::object * pobjectHint) override;

      virtual void set_viewport_offset(int, int) override;
      virtual ::pointd get_viewport_offset() override;
      virtual ::size get_total_size() override;
      
      virtual void on_control_event(::user::control_event * pevent) override;

   };


} // namespace user





