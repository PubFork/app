#pragma once


namespace userex
{


   class CLASS_DECL_CORE top_view :
      virtual public ::user::split_view
   {
   public:


      top_edit_view *                     m_peditview;
      top_toggle_view *                   m_ptoggleview;


      top_view(::aura::application * papp);
      virtual ~top_view();


      virtual void assert_valid() const override;

      virtual void dump(dump_context & dumpcontext) const override;

      void on_create_views() override;

      virtual void on_update(::user::impact * pSender, LPARAM lHint, object* pHint) override;

      virtual bool is_this_visible() override;


      virtual void _001OnNcDraw(::draw2d::graphics * pgraphics) override;
      virtual void _001OnDraw(::draw2d::graphics * pgraphics) override;


   };


} // namespace userex







