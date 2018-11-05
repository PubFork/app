#pragma once


namespace wndfrm_core
{


   class CLASS_DECL_APP_CORE_WNDFRM_CORE theme:
      virtual public ::user::theme
   {
   public:



      theme(::aura::application * papp);
      virtual ~theme();


      virtual int64_t add_ref() override
      {

         return ::object::add_ref();

      }

      virtual int64_t dec_ref() override
      {

         return ::object::dec_ref();

      }


      bool _001TabOnDrawSchema01(::draw2d::graphics * pgraphics,::user::tab * ptab) override;
      void _001OnTabPaneDrawTitle(::user::tab_pane & pane,::user::tab * ptab,::draw2d::graphics * pgraphics,LPCRECT lpcrect,::draw2d::brush_sp & brushText) override;
      bool _001OnTabLayout(::user::tab * ptab) override;

      virtual bool get_color(COLORREF & cr, ::user::e_color ecolor, ::user::style_context * pcontext) override;

      virtual bool _001DrawSimpleScrollBar(::draw2d::graphics * pgraphics, simple_scroll_bar * pbar) override;



   };


} // namespace wndfrm_core


