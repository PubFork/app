#pragma once


namespace wndfrm_tranquillum
{


   class CLASS_DECL_APP_WNDFRM_TRANQUILLUM theme :
      virtual public ::user::theme
   {
   public:


      //::draw2d::font_sp                m_fontEdit;
      //::draw2d::font_sp                m_fontList;


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


//      virtual bool get_color(COLORREF & cr, ::user::e_color ecolor, ::user::interaction * pui) override;
      //    virtual bool get_font(::draw2d::font_sp & font, ::user::e_font efont, ::user::interaction * pui) override;
      //  virtual bool get_translucency(::user::e_translucency & etranslucency, ::user::e_element eelement, ::user::interaction * pui) override;


      virtual bool on_ui_event(::user::e_event eevent, ::user::e_object eobject, ::user::interaction * pui) override;

      bool _001TabOnDrawSchema01(::draw2d::graphics * pgraphics,::user::tab * ptab) override;
      void _001OnTabPaneDrawTitle(::user::tab_pane & pane,::user::tab * ptab,::draw2d::graphics * pgraphics,LPCRECT lpcrect,::draw2d::brush_sp & brushText) override;
      bool _001OnTabLayout(::user::tab * ptab) override;

      virtual bool _001OnDrawMainFrameBackground(::draw2d::graphics * pgraphics, ::user::frame * pframe) override;
      virtual bool _001DrawToolbarItem(::draw2d::graphics * pgraphics, int32_t iItem, ::user::toolbar * ptoolbar) override;
      virtual void _001DrawSimpleToolbarItem(::draw2d::graphics * pgraphics, int32_t iItem, ::user::toolbar * ptoolbar);
      virtual void _001DrawTranquillumToolbarItem(::draw2d::graphics * pgraphics, int32_t iItem, ::user::toolbar * ptoolbar);
      virtual bool _001OnDrawSplitLayout(::draw2d::graphics * pgraphics, ::user::split_layout * psplitlayout) override;

      //virtual bool get_font(::draw2d::font_sp & sp, ::user::e_font efont, ::user::style_context * pcontext) override;
      //virtual bool get_double(double & d, ::user::e_double edouble, ::user::style_context * pcontext) override;


   };


} // namespace wndfrm_tranquillum



