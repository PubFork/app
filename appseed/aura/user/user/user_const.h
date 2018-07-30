#pragma once


namespace user
{


   enum e_object
   {

      object_list,
      object_tree

   };


   enum e_theme
   {

      theme_lite,
      theme_blue,
      theme_dark

   };


   enum e_appearance
   {

      appearance_none,
      appearance_current,
      appearance_iconic,
      appearance_normal,
      appearance_left,
      appearance_top,
      appearance_right,
      appearance_bottom,
      appearance_top_left,
      appearance_top_right,
      appearance_bottom_left,
      appearance_bottom_right,
      appearance_zoomed,
      appearance_full_screen,
      appearance_minimal,
      appearance_notify_icon,
      appearance_up,
      appearance_down,
      appearance_fixed_size,


   };


   enum e_translucency
   {

      translucency_undefined,
      translucency_none,
      translucency_present,
      translucency_total

   };

   enum e_control_type
   {
      control_type_none,
      control_type_static,
      control_type_check_box,
      control_type_edit,
      control_type_simple_list,
      control_type_button,
      control_type_combo_box,
      control_type_edit_plain_text,
      control_type_list,
      control_type_mesh,
      control_type_tree,
      control_type_split,
      control_type_tab,
      control_type_toolbar,
      control_type_statusbar,
      control_type_menu,
      control_type_menu_popup,
      control_type_menu_button,
      control_type_menu_button_close,
      control_type_system_menu,
      control_type_system_menu_popup,
      control_type_system_menu_button,
      control_type_system_menu_close,
   };




   enum e_element
   {

      element_none,
      element_frame_window,
      element_tab,
      element_close_tab_button,
      element_status_image,
      element_text,
      element_icon,
      element_border,
      element_client,
      element_area,
      element_drop_down,
      element_item,
      element_search_edit,
      element_search_ok,
      element_scrollbar_rect,
      element_scrollbar_rectA,
      element_scrollbar_rectB,
      element_scrollbar_pageA,
      element_scrollbar_pageB,
      element_margin_top,
      element_margin_left,
      element_margin_right,
      element_margin_bottom,


      element_split = 10000,

   };

   using translucency_map = ::map < e_element,e_element,e_translucency,e_translucency >;


   enum e_event
   {
      event_initialize_control,
      event_action,
      event_button_down,
      event_button_clicked,
      event_m_button_down,
      event_m_button_up,
      event_list_clicked,
      event_mouse_enter,
      event_mouse_leave,
      event_set_check,
      event_timer,
      event_enter_key,
      event_escape,
      event_tab_key,
      event_key_down,
      event_after_change_text,
      event_after_change_text_format,
      event_after_change_cur_sel,
      event_after_change_cur_hover,
      event_timebar_change,
      event_menu_hover,
      event_context_menu_close,
      event_set_focus,
      event_kill_focus,
      event_on_create_view,
      event_on_create_tab,
      event_form_initialize,
      event_create,
      event_layout,
      event_calc_item_height,
      event_change_view_style,
      event_item_clicked,
   };

   enum e_color
   {

      color_none,
      color_text,
      color_text_highlight,
      color_text_selected,
      color_text_selected_highlight,
      color_text_focused,
      color_background,
      color_background_highlight,
      color_background_selected,
      color_background_selected_highlight,
      color_background_selected_hover,
      color_border,
      color_border_hover,
      color_border_press,
      color_border_disabled,
      color_background_hover,
      color_background_press,
      color_background_press_hover,
      color_background_disabled,
      color_text_normal,
      color_text_hover,
      color_text_press,
      color_text_press_hover,
      color_text_disabled,
      color_button_background,
      color_button_background_hover,
      color_button_background_press,
      color_button_background_disabled,
      color_button_text,
      color_button_text_hover,
      color_button_text_press,
      color_button_text_disabled,
      color_face,
      color_face_lite,
      color_list_header,
      color_list_header_background,
      color_list_header_separator,
      color_list_item_background,
      color_list_item_background_hover,
      color_list_item_background_selected,
      color_list_item_background_selected_hover,
      color_list_item_text,
      color_list_item_text_hover,
      color_list_item_text_selected,
      color_list_item_text_selected_hover,
      color_list_background,
      color_edit_text,
      color_edit_background,
      color_edit_text_selected,
      color_edit_background_selected,
      color_edit_text_empty,
      color_tree_background,
      color_view_background,
      color_toolbar_background,
      color_toolbar_separator,
      color_split_layout_background,
      color_tab_client_background,
      color_tab_layout_background,
      color_action_hover_border_color,
      color_scrollbar,
      color_scrollbar_hover,
      color_scrollbar_draw,
      color_scrollbar_draw_hover,
      color_scrollbar_strong,
      color_scrollbar_strong_hover,
      color_scrollbar_border,
      color_scrollbar_border_hover,
      color_scrollbar_lite_border,
      color_scrollbar_lite_border_hover,
      color_scrollbar_background,
      color_scrollbar_background_hover,
   };

   using color_map = map < e_color,e_color,COLORREF,COLORREF >;

   enum e_font
   {

      font_default,
      font_button,
      font_plain_edit,
      font_tree,
      font_list_item,
      font_list_hover,
      font_list_header,
      font_static,
      font_toolbar,
      font_tab,
      font_tab_hover,
      font_tab_sel,
      font_tab_sel_hover,
      font_tab_big_bold

   };

   using font_map = map < e_font,e_font,::draw2d::font_sp >;

   enum e_flag
   {

      flag_none,
      flag_border,
      flag_blur_background

   };

   using flag_map = map < e_flag,e_flag,bool,bool >;

   enum e_rect
   {

      rect_none,
      rect_button_margin,
      rect_button_padding,
      rect_button_border,
      rect_menu_margin,
      rect_menu_padding,
      rect_menu_border,
      rect_menu_item_margin,
      rect_menu_item_padding,
      rect_menu_item_border,
      rect_edit_padding,
      rect_tab_margin,
      rect_tab_border,
      rect_tab_padding,

   };

   using rect_map = ::map < e_rect,e_rect, style_rect >;

   enum e_int
   {

      int_none,
      int_border,
      int_element_padding,
      int_menu_check_padding,
      int_check_box_size,
      int_still_draw_text_flags,
      int_button_draw_text_flags,
      int_button_draw_text_and_image_flags,
      int_edit_draw_text_flags,
      int_menu_item_draw_text_flags,
      int_list_item_draw_text_flags,
      int_top_level_drawing_order,
      int_button_press_shift_cx,
      int_button_press_shift_cy
   };

#define DRAWING_ORDER_FRAME_OVER 0
#define DRAWING_ORDER_CLIENT_OVER 1


   enum e_double
   {

      double_none,
      double_default_one_min,
      double_width_rate,
      double_list_item_height_rate,
      double_tree_item_height_rate,
      double_default_one_max,

   };

   using int_map = ::map < e_int,e_int,int,int >;

   using double_map = ::map < e_double,e_double,double,double >;

   enum e_timer
   {

      timer_command_probe = 11225,
      timer_menu,
      timer_overflow_scrolling,

   };


   enum e_control_function
   {
      // Text got from control m_uiId member
      control_function_static,
      // Text got from control m_uiText member
      control_function_static2,
      control_function_data_selection,
      control_function_check_box,
      control_function_duplicate_on_check_box,
      control_function_disable_on_check_box,
      control_function_save_on_change,
      control_function_vms_data_edit,
      control_function_action,
      control_function_edit_multi_line,
   };


   enum e_control_data_type
   {
      control_data_type_string,
      control_data_type_natural,
   };


   enum e_control_ddx
   {

      control_ddx_none,
      control_ddx_flags,
      control_ddx_dbflags,

   };


} // namespace user


