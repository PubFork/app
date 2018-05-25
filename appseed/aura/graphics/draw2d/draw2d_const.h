#pragma once


enum e_stock_icon
{

   stock_icon_none,
   stock_icon_control_box_begin,
   // TO Begin - TIGHTLY ORDERED Begin (relations : {ca2/app/core}::user::wndfrm::frame::e_button[button_close:stock_icon_close,...])
   stock_icon_close =  stock_icon_control_box_begin,
   stock_icon_level_up,
   stock_icon_level_down,
   stock_icon_iconify,
   stock_icon_restore,
   stock_icon_zoom,
   stock_icon_notify,
   stock_icon_transparent_frame,
   stock_icon_dock,
   // TO END - TIGHTLY ORDERED End
   stock_icon_control_box_end = stock_icon_dock
};


namespace draw2d
{

   enum e_smooth_mode
   {
      smooth_mode_none,
      smooth_mode_antialias,
      smooth_mode_high,
   };


   enum e_alpha_mode
   {
      alpha_mode_set,
      alpha_mode_blend
   };


   enum e_fill_mode
   {
      fill_mode_winding,
      fill_mode_alternate
   };


   enum e_unit
   {

      unit_pixel,
      unit_point,
      unit_em

   };


   enum e_text_rendering
   {

      text_rendering_undefined,
      text_rendering_none,
      text_rendering_anti_alias,
      text_rendering_anti_alias_grid_fit,
      text_rendering_single_bit_per_pixel,
      text_rendering_clear_type_grid_fit

   };


} // namespace draw2d




