#pragma once


namespace user
{


   class CLASS_DECL_BASE button :
      virtual public control,
      virtual public check
   {
   public:

      enum e_style
      {
         style_none,
         style_normal,
         style_simple,
         style_bitmap,
         style_image_and_text,
         style_push,
         style_list
      };

      class bitmap
      {
      public:

         ::visual::dib_sp                    m_dib;          // not pressed default bitmap
         ::visual::dib_sp                    m_dibSel;       // pressed bitmap
         ::visual::dib_sp                    m_dibFocus;     // focus bitmap
         ::visual::dib_sp                    m_dibDisabled;  // disabled bitmap
         ::visual::dib_sp                    m_dibHover;     // hover bitmap

      };


      class list
      {
      public:

         sp(image_list)                      m_pimagelistNormal;
         sp(image_list)                      m_pimagelistItemHover;
         sp(image_list)                      m_pimagelistSubItemHover;
         int32_t                             m_iImageNormal;
         int32_t                             m_iImageItemHover;
         int32_t                             m_iImageSubItemHover;

      };

      //normal

      e_rect                              m_erectMargin;
      e_rect                              m_erectBorder;
      e_rect                              m_erectPadding;
      e_int                               m_eintTextAlign;
      e_style                             m_estyle;
      ::check::e_check                    m_echeck;
      rect                                m_rectText;
      index                               m_iClick;
      e_stock_icon                        m_estockicon;
      rect                                m_rectCheckBox;
      bitmap *                            m_pbitmap;
      list *                              m_plist;


      button();
      button(::aura::application * papp);
      virtual ~button();

      virtual bool create_control(class control_descriptor * pdescriptor) override;

      virtual void resize_to_fit() override;

      virtual void install_message_routing(::message::sender * pinterface) override;

      virtual void _001OnButtonDrawPush(::draw2d::graphics * pgraphics);
      virtual void _001OnButtonDrawList(::draw2d::graphics * pgraphics);
      virtual void _001OnButtonDrawBitmap(::draw2d::graphics * pgraphics);
      virtual void _001OnButtonDrawImageAndText(::draw2d::graphics * pgraphics);
      virtual void _001OnButtonDrawBackground(::draw2d::graphics * pgraphics);
      virtual void _001OnButtonDrawTextLayer(::draw2d::graphics * pgraphics, LPRECT lprectText);
      virtual void _001OnButtonDrawNormal(::draw2d::graphics * pgraphics);

      virtual void _001OnDraw(::draw2d::graphics * pgraphics) override;
      virtual void _002OnDraw(::draw2d::graphics * pgraphics);

      virtual bool is_custom_draw() override;

      virtual void _001SetCheck(::check::e_check check, ::action::context actioncontext) override;
      virtual ::check::e_check _001GetCheck() override;

      virtual bool is_pressed();


      virtual index hit_test(point pt, e_element & eelement) override;

      DECL_GEN_SIGNAL(_001OnKeyDown);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnMButtonDown);
      DECL_GEN_SIGNAL(_001OnMButtonUp);
      DECL_GEN_SIGNAL(_001OnMouseMove);
      DECL_GEN_SIGNAL(_001OnMouseLeave);
      DECL_GEN_SIGNAL(_001OnCreate);


      ::size calc_text_size();

      virtual bool keyboard_focus_is_focusable() override;

      virtual bool has_action_hover() override;

      bool LoadBitmaps(::var var,::var varSel = ::var::type_null,::var varFocus = ::var::type_null,::var varDisabled = ::var::type_null,::var varHover = ::var::type_null);


      virtual void set_button_style(e_style estyle);
      virtual void on_enter_button_style(e_style estyle);
      virtual void on_exit_button_style(e_style estyle);

      virtual void BaseToolTipRelayEvent(::message::message * pobj);
      virtual void BaseToolTipGetRect(LPRECT lprect);
      virtual int32_t BaseToolTipGetIndex();

      virtual void pre_translate_message(::message::message * pobj) override;


      virtual void on_layout() override;


      virtual void set_stock_icon(e_stock_icon eicon) override;
      virtual e_stock_icon get_stock_icon() override;

      virtual COLORREF get_button_text_color();


   };


} // namespace user



