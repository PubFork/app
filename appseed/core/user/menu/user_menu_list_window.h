#pragma once


namespace user
{


   class CLASS_DECL_CORE menu_list_window :
      virtual public ::user::menu
   {
   public:

      bool                                m_bAutoClose;
      bool                                m_bAutoDelete;

      menu_list_window();
      menu_list_window(::aura::application * papp);
      menu_list_window(::aura::application * papp, menu_item * pitem);
      virtual ~menu_list_window();

      void on_layout();

      virtual void install_message_routing(::message::sender * pinterface);

      virtual bool get_color(COLORREF & cr, e_color ecolor, ::user::interaction * pui) override;

      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnDestroy);
      DECL_GEN_SIGNAL(_001OnClose);
      
      void _001OnTimer(::timer * ptimer);

      void _001OnDraw(::draw2d::graphics * pgraphics);

      //bool BaseOnControlEvent(::user::control_event * pevent);

      virtual void calc_size(menu_item * pitemParent, ::draw2d::graphics * pgraphics, int32_t & iMaxWidth, int32_t & iMaxHeight);

      virtual void layout_buttons(menu_item * pitemParent, int32_t iMaxWidth, LPRECT lprect, LPCRECT lpcrectBound);


   };


} // namespace user







