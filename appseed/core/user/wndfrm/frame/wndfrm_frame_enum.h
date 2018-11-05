#pragma once


namespace user
{


   namespace wndfrm
   {


      namespace frame
      {

         enum EHitTest
         {

            HitTestNone,
            HitTestClient,
            HitTestSizingLeft,
            HitTestSizingTopLeft,
            HitTestSizingTop,
            HitTestSizingTopRight,
            HitTestSizingRight,
            HitTestSizingBottomRight,
            HitTestSizingBottom,
            HitTestSizingBottomLeft,
            HitTestMove,

         };


         enum e_button
         {

            button_none,
            button_begin,
            button_close = button_begin, // stock_icon_close
            button_up, // stock_icon_level_up
            button_down, // stock_icon_level_down
            button_minimize, // stock_icon_iconify
            button_restore, // stock_icon_restore
            button_maximize, // stock_icon_maximize
            button_notify_icon, // stock_icon_notify
            button_transparent_frame, // stock_icon_transparent_frame
            button_dock, // stock_icon_dock
            button_end = button_dock

         };


      } // namespace frame


   } // namespace frame


} // namespace user







