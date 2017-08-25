#pragma once


namespace userex
{


   class CLASS_DECL_CORE split_view :
      virtual public ::user::split_view,
      virtual public ::user::view_creator
   {
   public:


      split_view(::aura::application * papp);
      virtual ~split_view();

      virtual bool on_new_view_creator_data(::user::view_creator_data * pcreatordata);

      virtual void on_simple_command_probe(::user::command * pcommand) override;

      virtual void on_simple_command(::user::command * pcommand) override;

      bool create_pane(int32_t iPane, bool bFixedSize, ::id id);


   };


} // namespace userex




