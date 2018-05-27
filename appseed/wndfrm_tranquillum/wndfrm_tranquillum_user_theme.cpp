#include "framework.h" // from "base/user/user.h"
#include "core/user/menu/user_menu_central.h"
// pgraphics->GetTextExtent("->:<-"); // oh no!! omg!! The size is the size of the alien!!
#define MAGIC_PALACE_TAB_SPLT "->:<-"
#define MAGIC_PALACE_TAB_SIZE "-/-"
#define MAGIC_PALACE_TAB_TEXT "/"





namespace wndfrm_tranquillum
{


   theme::theme(::aura::application * papp):
      object(papp),
      ::user::theme(papp)
      //m_fontEdit(allocer()),
      //m_fontList(allocer())
   {

//      m_fontEdit->create_point_font("MS Sans Serif", 9.0);

      //    m_fontList->create_point_font("Tahoma", 10, FW_BOLD);

      //theme_current_control(::user::control_none);

      //create_translucency(::user::element_none, ::user::translucency_none);

      create_point_font(::user::font_default,"Segoe UI", 12.0);
      create_point_font(::user::font_button, "Segoe UI", 12.0, 800);
      create_point_font(::user::font_plain_edit, "Segoe UI", 12.0, 800);
      create_point_font(::user::font_list_header, "Segoe UI", 12.0, 800);

      create_point_font(::user::font_tab, "Segoe UI", 13.0, 400);
      {
         auto font = create_point_font(::user::font_tab_hover, "Segoe UI", 13.0, 400);
         font->m_bUnderline = true;
      }
      create_point_font(::user::font_tab_sel, "Segoe UI", 13.0, 800);
      {
         auto font = create_point_font(::user::font_tab_sel_hover, "Segoe UI", 13.0, 800);
         font->m_bUnderline = true;
      }
      create_point_font(::user::font_tab_big_bold, "Segoe UI", 13.0, 800);


      create_double(::user::double_list_item_height_rate, 1.65);

      create_pixel_rect_coord(::user::rect_menu_item_padding, 5, 5, 5, 5);

      create_int(::user::int_element_padding, 4);

      create_color(::user::color_background, ARGB(255, 255, 255, 255));
      create_color(::user::color_text, ARGB(255, 0, 0, 0));
      create_color(::user::color_edit_text, ARGB(255, 0, 0, 0));
      create_color(::user::color_edit_text_selected, ARGB(255, 255, 255, 255));
      create_color(::user::color_edit_background_selected, ARGB(255, 100, 150, 230));
      create_color(::user::color_text_selected, ARGB(255, 255, 255, 255));
      create_color(::user::color_text_selected_highlight, ARGB(255, 255, 255, 255));
      create_color(::user::color_text_highlight, ARGB(255, 255, 255, 255));
      create_color(::user::color_background_selected, ARGB(255, 100, 150, 230));
      create_color(::user::color_background_selected_highlight, ARGB(255, 110, 180, 240));
      create_color(::user::color_background_highlight, ARGB(255, 120, 200, 250));
      create_color(::user::color_background, ARGB(255, 255, 255, 255));
      create_color(::user::color_button_text, ARGB(255, 255, 255, 255));
      create_color(::user::color_list_header, ARGB(255, 40, 40, 40));
      create_color(::user::color_list_header_background, ARGB(255, 230, 230, 230));
      create_color(::user::color_list_background, ARGB(255, 255, 255, 255));
      create_color(::user::color_list_item_text, ARGB(255, 50, 50, 50));
      create_color(::user::color_list_item_text_hover, ARGB(255, 50, 50, 50));
      create_color(::user::color_list_item_text_selected, ARGB(255, 250, 250, 250));
      create_color(::user::color_list_item_text_selected_hover, ARGB(255, 250, 250, 250));
      create_color(::user::color_list_item_background, ARGB(255, 255, 255, 255));
      create_color(::user::color_list_item_background_hover, ARGB(255, 255, 255, 255));
      create_color(::user::color_list_item_background_selected, ARGB(255, 100, 150, 230));
      create_color(::user::color_list_item_background_selected_hover, ARGB(255, 130, 180, 240));
      create_color(::user::color_button_background, ARGB(255, 80, 150, 220));
      create_color(::user::color_button_background_hover, ARGB(255, 110, 180, 240));
      create_color(::user::color_button_background_press, ARGB(255, 95, 165, 230));
      create_color(::user::color_button_background_disabled, ARGB(255, 160, 170, 180));
      create_color(::user::color_button_text, ARGB(255, 255, 255, 255));
      create_color(::user::color_button_text_hover, ARGB(255, 255, 255, 255));
      create_color(::user::color_button_text_press, ARGB(255, 255, 255, 255));
      create_color(::user::color_button_text_disabled, ARGB(255, 200, 210, 220));


   }


   theme::~theme()
   {

   }



   bool theme::_001OnDrawMainFrameBackground(::draw2d::graphics * pgraphics, ::user::frame * pframe)
   {

      rect rectClient;

      pframe->GetClientRect(rectClient);

      COLORREF crBackground = pframe->_001GetColor(::user::color_background);

      pgraphics->fill_solid_rect(rectClient, crBackground);

      return true;

   }


   bool theme::_001OnTabLayout(::user::tab * ptab)
   {

      if (!ptab->get_data()->m_bCreated)
         return false;

      ptab->m_bDrawTabAtBackground = true;

      ptab->defer_handle_auto_hide_tabs(false);

      ::draw2d::memory_graphics pgraphics(allocer());
      pgraphics->SelectObject(ptab->_001GetFont(::user::font_tab_sel));

      ptab->m_dcextension.GetTextExtent(pgraphics, MAGIC_PALACE_TAB_SIZE, ptab->get_data()->m_sizeSep);

      if (ptab->get_data()->m_bVertical)
      {
         int32_t iTabWidth = 16;
         int32_t iTabHeight = 8;
         int32_t cx;
         int32_t cy;
         for (int32_t iPane = 0; iPane < ptab->get_data()->m_panea.get_size(); iPane++)
         {

            ::user::tab_pane & tab_pane = ptab->get_data()->m_panea(iPane);

            if (!tab_pane.m_bTabPaneVisible)
               continue;

            string str = tab_pane.get_title();

            tab_pane.do_split_layout(ptab->m_dcextension, pgraphics);

            ::size size;

            ptab->m_dcextension.GetTextExtent(pgraphics, str, size);



            if (tab_pane.m_dib.is_set())
            {
               size.cx += tab_pane.m_dib->m_size.cx + 2;
               size.cy = MAX(size.cy, tab_pane.m_dib->m_size.cy);
            }
            cx = size.cx + 2;

            if (!tab_pane.m_bPermanent)
            {
               cx += 2 + 16 + 2;
            }

            if (cx > iTabWidth)
            {
               iTabWidth = cx;
            }
            cy = size.cy + 2;
            if (cy > iTabHeight)
            {
               iTabHeight = cy;
            }
         }

         // close tab button
         cy = 2 + 16 + 2;
         if (cy > iTabHeight)
         {
            iTabHeight = cy;
         }

         iTabWidth += ptab->get_data()->m_rectBorder.left + ptab->get_data()->m_rectBorder.right +
                      ptab->get_data()->m_rectMargin.left + ptab->get_data()->m_rectMargin.right +
                      ptab->get_data()->m_rectTextMargin.left + ptab->get_data()->m_rectTextMargin.right;

         ptab->get_data()->m_iTabWidth = iTabWidth;

         iTabHeight += ptab->get_data()->m_rectBorder.top + ptab->get_data()->m_rectBorder.bottom +
                       ptab->get_data()->m_rectMargin.top + ptab->get_data()->m_rectMargin.bottom +
                       ptab->get_data()->m_rectTextMargin.top + ptab->get_data()->m_rectTextMargin.bottom;

         ptab->get_data()->m_iTabHeight = iTabHeight;

         rect rectClient;
         ptab->GetClientRect(rectClient);

         ptab->get_data()->m_rectTab.left = rectClient.left;
         ptab->get_data()->m_rectTab.top = rectClient.top;
         ptab->get_data()->m_rectTab.right = ptab->get_data()->m_rectTab.left + ptab->get_data()->m_iTabWidth;
         ptab->get_data()->m_rectTab.bottom = rectClient.bottom;

         /*      m_pui->SetWindowPos(
         ZORDER_TOP,
         m_rectTab.left,
         m_rectTab.top,
         m_rectTab.width(),
         m_rectTab.height(),
         0);*/

         ptab->get_data()->m_rectTabClient.left = ptab->m_bShowTabs ? ptab->get_data()->m_rectTab.right : rectClient.left;
         ptab->get_data()->m_rectTabClient.top = ptab->get_data()->m_rectTab.top;
         ptab->get_data()->m_rectTabClient.right = rectClient.right;
         ptab->get_data()->m_rectTabClient.bottom = ptab->get_data()->m_rectTab.bottom;

      }
      else
      {
         int32_t iTabHeight = 16;
         int32_t cy;
         ::draw2d::graphics_sp graphics(allocer());
         graphics->CreateCompatibleDC(NULL);
         ::draw2d::graphics * pgraphics = graphics;
         pgraphics->SelectObject(ptab->_001GetFont(::user::font_tab_sel));

         rect rectClient;
         ptab->GetClientRect(rectClient);
         int x = rectClient.left;

         int32_t ixAdd;
         for (int32_t iPane = 0; iPane < ptab->get_data()->m_panea.get_size(); iPane++)
         {

            ::user::tab_pane & tab_pane = ptab->get_data()->m_panea(iPane);

            if (!tab_pane.m_bTabPaneVisible)
               return false;

            string str = tab_pane.get_title();

            tab_pane.do_split_layout(ptab->m_dcextension, pgraphics);

            size size;

            ptab->m_dcextension.GetTextExtent(pgraphics, str, size);

            if (tab_pane.m_dib.m_p != NULL)
            {
               size.cy = MAX(size.cy, tab_pane.m_dib->size().cy);
            }
            cy = size.cy + 2;

            if (cy > iTabHeight)
            {
               iTabHeight = cy;
            }

            tab_pane.m_pt.x = x;
            tab_pane.m_pt.y = rectClient.top;


            //            string str = tab_pane.get_title();

            //            size size;

            ixAdd = 5;

            if (tab_pane.m_dib.is_set())
            {
               //::image_list::info ii;
               ixAdd += tab_pane.m_dib->m_size.cx + 2;
            }

            if (!tab_pane.m_bPermanent)
            {
               ixAdd += 2 + 16 + 2;
            }




            tab_pane.m_size.cx = size.cx + ixAdd
                                 + ptab->get_data()->m_rectBorder.left + ptab->get_data()->m_rectBorder.right
                                 + ptab->get_data()->m_rectMargin.left + ptab->get_data()->m_rectMargin.right
                                 + ptab->get_data()->m_rectTextMargin.left + ptab->get_data()->m_rectTextMargin.right;

            x += tab_pane.m_size.cx;
         }

         // close tab button
         cy = 2 + 16 + 2;
         if (cy > iTabHeight)
         {
            iTabHeight = cy;
         }

         iTabHeight += ptab->get_data()->m_rectBorder.top + ptab->get_data()->m_rectBorder.bottom +
                       ptab->get_data()->m_rectMargin.top + ptab->get_data()->m_rectMargin.bottom + ptab->get_data()->m_iHeightAddUp;

         ptab->get_data()->m_iTabHeight = iTabHeight + 8;

         for (int32_t iPane = 0; iPane < ptab->get_data()->m_panea.get_size(); iPane++)
         {

            ::user::tab_pane & tab_pane = ptab->get_data()->m_panea(iPane);

            tab_pane.m_size.cy = iTabHeight;

         }




         ptab->get_data()->m_rectTab.left = rectClient.left;
         ptab->get_data()->m_rectTab.top = rectClient.top;
         ptab->get_data()->m_rectTab.right = rectClient.right;
         ptab->get_data()->m_rectTab.bottom = ptab->get_data()->m_rectTab.top + ptab->get_data()->m_iTabHeight;

         /*      SetWindowPos(
         ZORDER_TOP,
         m_rectTab.left,
         m_rectTab.top,
         m_rectTab.width(),
         m_rectTab.height(),
         0);*/

         rect & rectTabClient = ptab->get_data()->m_rectTabClient;

         rectTabClient.left = ptab->get_data()->m_rectTab.left;
         rectTabClient.top = ptab->m_bShowTabs ? ptab->get_data()->m_rectTab.bottom : rectClient.top;
         rectTabClient.right = ptab->get_data()->m_rectTab.right;
         rectTabClient.bottom = rectClient.bottom;

         //TRACE0("rectTabClient");

      }

      for (int32_t iPane = 0; iPane < ptab->get_data()->m_panea.get_size(); iPane++)
      {

         if (iPane != ptab->_001GetSel())
         {

            ptab->layout_pane(iPane);

         }

      }

      ptab->layout_pane(ptab->_001GetSel(), ptab->IsWindowVisible());

      return true;

   }


   bool theme::_001TabOnDrawSchema01(::draw2d::graphics * pgraphics, ::user::tab * ptab)
   {

      class rect rect;
      class rect rectBorder;
      class rect rectText;
      class rect rectClient;
      class rect rectIcon;
      class rect rectClose;

      class rect r1;
      ptab->GetClientRect(r1);

      if (!ptab->get_data()->m_bNoClient)
      {

         pgraphics->fill_solid_rect(r1, ARGB(255, 255, 255, 255));

      }

      ptab->get_data()->m_pen->create_solid(1, RGB(32, 32, 32));

      pgraphics->set_text_rendering(::draw2d::text_rendering_anti_alias_grid_fit);

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      ::rect rcTab;

      rcTab = ptab->get_data()->m_rectTab;

      if (ptab->get_data()->m_bNoClient)
      {

         pgraphics->fill_solid_rect(rcTab, ARGB(255, 255, 255, 255));

      }
      ::rect rcTape(rcTab);

      rcTape.top = rcTape.bottom - 8;

      pgraphics->fill_solid_rect(rcTape, ARGB(255, 192, 192, 192));


      ::rect rcTabs(rcTab);

      ::rect rcClient;

      rcClient = ptab->get_data()->m_rectTabClient;

      int iTabHeight = ptab->get_data()->m_iTabHeight;

      //int iB = rcClient.top;

      rcTabs.bottom = rcTabs.top + iTabHeight - ptab->get_data()->m_rectBorder.bottom;

      rcClient.top = rcTabs.bottom;

      COLORREF crbk = ptab->_001GetColor(::user::color_tab_layout_background);

      pgraphics->fill_solid_rect(rcTabs, crbk);

      crbk = ptab->_001GetColor(::user::color_tab_client_background);

      pgraphics->fill_solid_rect(rcClient, crbk);

      int32_t iTab = -1;

      ::draw2d::brush_sp brushText;

      for (int32_t iPane = 0; iPane < ptab->get_data()->m_panea.get_size(); iPane++)
      {

         ::user::tab_pane & pane = ptab->get_data()->m_panea(iPane);

         if (!pane.m_bTabPaneVisible)
            continue;

         iTab++;

         if (!ptab->get_element_rect(iTab, rect, ::user::element_tab))
            continue;

         if (!ptab->get_element_rect(iTab, rectBorder, ::user::element_border))
            continue;

         if (!ptab->get_element_rect(iTab, rectClient, ::user::element_client))
            continue;

         if (ptab->get_data()->m_bVertical)
         {

            if (ptab->get_element_rect(iTab, rectIcon, ::user::element_icon))
            {

               pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);
               pane.m_dib->bitmap_blend(pgraphics, rectIcon);

            }

            ::draw2d::path_sp path(allocer());

            if (true)
            {

               if (ptab->get_data()->m_idaSel.contains(pane.m_id))
               {

                  ::rect rSel;

                  rSel = rectClient;

                  rSel.bottom = rectClient.top + 3;

                  pgraphics->fill_solid_rect(rSel, ARGB(255, 120, 155, 240));

                  pane.m_brushFillSel->CreateLinearGradientBrush(rectBorder.top_left(), rectBorder.bottom_left(), ARGB(230, 235, 235, 230), ARGB(250, 255, 255, 250));

                  pgraphics->SelectObject(pane.m_brushFillSel);

                  pgraphics->fill_path(path);

                  pgraphics->SelectObject(ptab->get_data()->m_penBorderSel);

                  pgraphics->draw_path(path);

                  if (iTab == ptab->m_iHover && ptab->m_eelementHover != ::user::element_close_tab_button && ptab->m_eelementHover < ::user::element_split && ptab->m_eelementHover >(::user::element_split + 100))
                  {

                     pgraphics->set_font(ptab->_001GetFont(::user::font_tab_sel_hover));

                  }
                  else
                  {

                     pgraphics->set_font(ptab->_001GetFont(::user::font_tab_sel));

                  }

                  brushText = ptab->get_data()->m_brushTextSel;

               }
               else
               {

                  //path->start_figure();

                  path->add_line(rectBorder.right, rectBorder.bottom, rectBorder.left + 1, rectBorder.bottom);
                  path->add_line(rectBorder.left, rectBorder.top - (rectBorder.left - rectClient.left));
                  path->add_line(rectText.left, rectBorder.top);
                  path->add_line(rectBorder.right, rectBorder.top);
                  path->add_line(rectBorder.right, rectBorder.bottom);

                  path->end_figure(true);

                  if (iTab == ptab->m_iHover && ptab->m_eelementHover != ::user::element_close_tab_button && ptab->m_eelementHover < ::user::element_split && ptab->m_eelementHover >(::user::element_split + 100))
                  {

                     pane.m_brushFillHover->CreateLinearGradientBrush(rectBorder.top_left(), rectBorder.bottom_left(), ARGB(230, 215, 215, 210), ARGB(250, 235, 235, 230));

                     pgraphics->SelectObject(pane.m_brushFillHover);

                     pgraphics->fill_path(path);

                     pgraphics->SelectObject(ptab->get_data()->m_penBorderHover);

                     pgraphics->draw_path(path);

                     pgraphics->set_font(ptab->_001GetFont(::user::font_tab_hover));

                     brushText = ptab->get_data()->m_brushTextHover;

                  }
                  else
                  {

                     pane.m_brushFill->CreateLinearGradientBrush(rectBorder.top_left(), rectBorder.bottom_left(), ARGB(230, 175, 175, 170), ARGB(250, 195, 195, 190));

                     pgraphics->SelectObject(pane.m_brushFill);

                     pgraphics->fill_path(path);

                     pgraphics->SelectObject(ptab->get_data()->m_penBorder);

                     pgraphics->draw_path(path);

                     pgraphics->set_font(ptab->_001GetFont(::user::font_tab));

                     brushText = ptab->get_data()->m_brushText;

                  }

               }

            }

         }
         else
         {

            if (ptab->get_element_rect(iTab, rectIcon, ::user::element_icon))
            {

               pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

               pane.m_dib->bitmap_blend(pgraphics, rectIcon);

            }
            //if (iPane == 0)
            //{

            //   if (rcTab.left < rectBorder.left)
            //   {

            //      pgraphics->SelectObject(ptab->get_data()->m_penBorder);

            //      pgraphics->draw_line(rcTab.left, rectClient.bottom, rectBorder.left, rectClient.bottom);

            //   }

            //}

            if (true)
            {

               ::draw2d::path_sp path(allocer());

               if (ptab->get_data()->m_idaSel.contains(pane.m_id))
               {

                  ::rect rSel;

                  rSel = rect;

                  rSel.bottom = rectClient.top + 3;

                  pgraphics->fill_solid_rect(rSel, ARGB(255, 120, 155, 240));

                  pane.m_brushFillSel->create_solid(ARGB(255, 255, 255, 255));

                  pgraphics->SelectObject(pane.m_brushFillSel);

                  pgraphics->fill_path(path);

                  ptab->get_data()->m_penBorderSel->create_solid(1.0, ARGB(255, 0, 0, 0));

                  pgraphics->SelectObject(ptab->get_data()->m_penBorderSel);

                  pgraphics->draw_path(path);

                  if (iTab == ptab->m_iHover && ptab->m_eelementHover != ::user::element_close_tab_button && ptab->m_eelementHover < ::user::element_split || ptab->m_eelementHover >(::user::element_split + 100))
                  {

                     pgraphics->set_font(ptab->_001GetFont(::user::font_tab_sel_hover));

                  }
                  else
                  {

                     pgraphics->set_font(ptab->_001GetFont(::user::font_tab_sel));


                  }

                  brushText = ptab->get_data()->m_brushTextSel;

               }
               else
               {


                  if (iTab == ptab->m_iHover && ptab->m_eelementHover != ::user::element_close_tab_button && (ptab->m_eelementHover < ::user::element_split || ptab->m_eelementHover >(::user::element_split + 100)))
                  {

                     pane.m_brushFillHover->CreateLinearGradientBrush(rectBorder.top_left(), rectBorder.bottom_left(), ARGB(230, 215, 215, 210), ARGB(250, 235, 235, 230));

                     pgraphics->SelectObject(pane.m_brushFillHover);

                     pgraphics->fill_path(path);

                     pgraphics->SelectObject(ptab->get_data()->m_penBorderHover);

                     pgraphics->draw_path(path);

                     pgraphics->set_font(ptab->_001GetFont(::user::font_tab_hover));

                     brushText = ptab->get_data()->m_brushTextHover;

                  }
                  else
                  {

                     pane.m_brushFill->CreateLinearGradientBrush(rectBorder.top_left(), rectBorder.bottom_left(), ARGB(230, 175, 175, 170), ARGB(250, 195, 195, 190));

                     pgraphics->SelectObject(pane.m_brushFill);

                     pgraphics->fill_path(path);

                     pgraphics->SelectObject(ptab->get_data()->m_penBorder);

                     pgraphics->draw_path(path);

                     pgraphics->set_font(ptab->_001GetFont(::user::font_tab));

                     brushText = ptab->get_data()->m_brushTextSel;

                  }

               }

            }

            ::rect rVertLine;

            rVertLine = rect;

            rVertLine.left = rVertLine.right - 1;
            pgraphics->fill_solid_rect(rVertLine, ARGB(127, 80, 80, 80));

            //if (iPane == ptab->get_data()->m_panea.get_upper_bound())
            //{

            //   if (rectBorder.right - 1 < rcTab.right)
            //   {

            //      pgraphics->SelectObject(ptab->get_data()->m_penBorder);

            //      pgraphics->draw_line(rectBorder.right - 1, rectClient.bottom, rcTab.right, rectClient.bottom);

            //   }

            //}


         }

         if (true)
         {

            if (ptab->get_element_rect(iTab, rectText, ::user::element_text))
            {

               _001OnTabPaneDrawTitle(pane, ptab, pgraphics, rectText, brushText);

            }

         }

         if (true)
         {

            if (ptab->get_element_rect(iTab, rectClose, ::user::element_close_tab_button))
            {

               pgraphics->set_font(ptab->_001GetFont(::user::font_tab_big_bold));

               if (iTab == ptab->m_iHover && ptab->m_eelementHover == ::user::element_close_tab_button)
               {

                  brushText = ptab->get_data()->m_brushCloseHover;

               }
               else
               {

                  brushText = ptab->get_data()->m_brushClose;

               }

               pgraphics->SelectObject(brushText);

               pgraphics->draw_text("x", rectClose, DT_CENTER | DT_VCENTER);

            }

         }

      }

      return true;

   }



   void theme::_001OnTabPaneDrawTitle(::user::tab_pane & pane,::user::tab * ptab,::draw2d::graphics * pgraphics,LPCRECT lpcrect,::draw2d::brush_sp & brushText)
   {

      stringa & straTitle = pane.m_straTitle;

      pgraphics->SelectObject(brushText);

      if(straTitle.get_count() <= 1)
      {

         pgraphics->_DrawText(pane.get_title(),*lpcrect,DT_LEFT | DT_BOTTOM | DT_NOPREFIX);

      }
      else
      {

         ::rect rectText(lpcrect);

         ::draw2d::font_sp font;
         font = pgraphics->get_current_font();
         size sSep = ptab->get_data()->m_sizeSep;
         ::rect rectEmp;
         for(index i = 0; i < straTitle.get_size(); i++)
         {
            string str = straTitle[i];
            size s = pane.m_sizeaText[i];
            rectText.right =rectText.left + s.cx;
            pgraphics->_DrawText(str,rectText,DT_LEFT | DT_BOTTOM | DT_NOPREFIX);
            rectText.left += s.cx;
            if(i < straTitle.get_upper_bound())
            {
               rectText.right = rectText.left + sSep.cx;
               rectEmp = rectText;
               rectEmp.deflate(1,1);
               ::draw2d::e_alpha_mode emode = pgraphics->m_ealphamode;
               pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);
               if(ptab->m_eelementHover == (int)::user::element_split + i)
               {
                  pgraphics->fill_solid_rect(rectEmp,ARGB(128,149,184,255));
                  pgraphics->SelectObject(ptab->get_data()->m_brushTextHover);
               }
               else
               {
                  //pgraphics->FillSolidRect(rectEmp,ARGB(128,208,223,233));
                  pgraphics->SelectObject(ptab->get_data()->m_brushText);
               }
               pgraphics->set_font(ptab->_001GetFont(::user::font_tab_big_bold));
               pgraphics->set_alpha_mode(emode);
               pgraphics->_DrawText(MAGIC_PALACE_TAB_TEXT,rectText,DT_CENTER | DT_VCENTER | DT_NOPREFIX);
               rectText.left += sSep.cx;
               pgraphics->selectFont(font);
               pgraphics->SelectObject(brushText);
            }
         }

      }

   }





   bool theme::on_ui_event(::user::e_event eevent, ::user::e_object eobject, ::user::interaction * pui)
   {

      if (eevent == ::user::event_calc_item_height)
      {

         pui->m_iItemHeight += 8;

         return true;

      }

      return false;

   }


   bool theme::_001DrawToolbarItem(::draw2d::graphics * pgraphics, int32_t iItem, ::user::toolbar * ptoolbar)
   {

//      if (1)
      {

         _001DrawTranquillumToolbarItem(pgraphics, iItem, ptoolbar);

      }
//      else
//      {
//
//         _001DrawSimpleToolbarItem(pgraphics, iItem, ptoolbar);
//
//      }

      return true;

   }


   void theme::_001DrawSimpleToolbarItem(::draw2d::graphics * pgraphics, int32_t iItem, ::user::toolbar * ptoolbar)
   {

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      rect rectItem;

      rect rectImage;

      ptoolbar->select_font(pgraphics, ::user::font_toolbar);

      ::user::toolbar_item & item = ptoolbar->m_itema(iItem);

      UINT nStyle = ptoolbar->GetButtonStyle(iItem);

      bool bHover = iItem == ptoolbar->_001GetHoverItem();

      BaseMenuCentral * pmenucentral = BaseMenuCentral::GetMenuCentral(get_app());

      UINT uiImage = pmenucentral->CommandToImage(item.m_id);

      ::user::toolbar::e_element eelement = ::user::toolbar::element_item;
      ::user::toolbar::e_element eelementImage = ::user::toolbar::element_image;
      ::user::toolbar::e_element eelementText = ::user::toolbar::element_text;
      if ((nStyle & TBBS_SEPARATOR) == 0)
      {
         if ((nStyle & TBBS_DISABLED) == 0)
         {
            // item is enabled
            if (ptoolbar->m_iButtonPressItem >= 0)
            {
               if (iItem == ptoolbar->m_iButtonPressItem)
               {
                  if (bHover)
                  {
                     eelement = ::user::toolbar::ElementItemPress;
                     eelementImage = ::user::toolbar::ElementImagePress;
                     eelementText = ::user::toolbar::ElementTextPress;
                  }
                  else
                  {
                     eelement = ::user::toolbar::ElementItemHover;
                     eelementImage = ::user::toolbar::ElementImageHover;
                     eelementText = ::user::toolbar::ElementTextHover;
                  }
               }
            }
            else if (bHover)
            {
               eelement = ::user::toolbar::ElementItemHover;
               eelementImage = ::user::toolbar::ElementImageHover;
               eelementText = ::user::toolbar::ElementTextHover;
            }
         }
         else
         {
            // item is disabled
            eelement = ::user::toolbar::element_item;
            eelementImage = ::user::toolbar::element_image;
            eelementText = ::user::toolbar::element_text;
         }
      }
      else
      {
         eelement = ::user::toolbar::element_item;
         eelementImage = ::user::toolbar::element_image;
         eelementText = ::user::toolbar::element_text;
      }


      //int iOffsetX = 0;
      //int iOffsetY = 0;

      ptoolbar->_001GetElementRect(iItem, rectItem, eelement);

      ptoolbar->_001GetElementRect(iItem, rectImage, eelementImage);

      if ((nStyle & TBBS_SEPARATOR) != 0)
      {
         rect rectSeparator;
         rectSeparator.left = (rectImage.left + rectImage.right) / 2 - 1;
         rectSeparator.right = rectSeparator.left + 2;
         rectSeparator.top = rectImage.top;
         rectSeparator.bottom = rectImage.bottom;
         pgraphics->draw3d_rect(rectSeparator, ARGB(255, 92, 92, 92), ARGB(255, 255, 255, 255));
      }
      else
      {
         if (eelement == ::user::toolbar::ElementItemHover)
         {
            if ((nStyle & TBBS_CHECKED) != 0)
            {

               ptoolbar->_001GetElementRect(iItem, rectItem, ::user::toolbar::element_item);

               ptoolbar->_001GetElementRect(iItem, rectImage, ::user::toolbar::element_image);

               if ((ptoolbar->m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
               {
                  Application.imaging().color_blend(
                  pgraphics,
                  rectItem.left,
                  rectItem.top,
                  rectItem.width(),
                  rectItem.height(),
                  RGB(255, 255, 250), 208);

                  pgraphics->draw3d_rect(rectItem, ARGB(255, 127, 127, 127), ARGB(255, 255, 255, 255));

               }

               if (uiImage != 0xffffffffu)
               {

                  if ((nStyle & TBBS_DISABLED) == 0)
                  {

                     // button is enabled
                     pmenucentral->MenuV033GetImageListBlend()->draw(pgraphics, uiImage, rectImage.top_left(), 0);

                  }
                  else
                  {

                     // button is disabled
                     pmenucentral->MenuV033GetImageListHueLight()->draw(pgraphics, uiImage, rectImage.top_left(), 0);

                  }

               }

            }
            else
            {

               rect rectShadow;

               ptoolbar->_001GetElementRect(iItem, rectShadow, ::user::toolbar::ElementItemHover);

               if ((ptoolbar->m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
               {

                  ::draw2d::pen_sp pen(pgraphics, 1, ARGB(184, 92, 184, 92));
                  ::draw2d::brush_sp brush(allocer(), ARGB(123, 177, 184, 255));
                  ::draw2d::pen * ppenOld = pgraphics->SelectObject(pen);
                  ::draw2d::brush * pbrushOld = pgraphics->SelectObject(brush);
                  pgraphics->rectangle(rectItem);
                  pgraphics->SelectObject(ppenOld);
                  pgraphics->SelectObject(pbrushOld);

               }

               if (item.m_spdib.is_set())
               {

                  rect rect;

                  ptoolbar->_001GetElementRect(iItem, rect, ::user::toolbar::ElementImageHover);

                  Application.imaging().color_blend(pgraphics, rect.top_left(), rect.get_size(), item.m_spdib->get_graphics(), null_point(), 0.84);

               }
               else if (uiImage != 0xffffffffu)
               {

                  rect rect;

                  ptoolbar->_001GetElementRect(iItem, rect, ::user::toolbar::ElementItemHover);

                  pmenucentral->MenuV033GetImageListHue()->draw(pgraphics, uiImage, rect.top_left(), 0);

                  pmenucentral->MenuV033GetImageList()->draw(pgraphics, uiImage, rectImage.top_left(), 0);
               }

            }

         }
         else if (eelement == ::user::toolbar::ElementItemPress)
         {

            if ((ptoolbar->m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
            {

               ::draw2d::pen_sp pen(pgraphics, 1, ARGB(255, 92, 92, 92));
               ::draw2d::brush_sp brush(allocer(), ARGB(255, 255, 255, 255));
               ::draw2d::pen * ppenOld = pgraphics->SelectObject(pen);
               ::draw2d::brush * pbrushOld = pgraphics->SelectObject(brush);
               pgraphics->rectangle(rectItem);
               pgraphics->SelectObject(ppenOld);
               pgraphics->SelectObject(pbrushOld);

            }

            if (item.m_spdib.is_set())
            {

               rect rect;

               ptoolbar->_001GetElementRect(iItem, rect, ::user::toolbar::ElementImagePress);

               Application.imaging().color_blend(pgraphics, rect.top_left(), rect.get_size(), item.m_spdib->get_graphics(), null_point(), 1.0);

            }
            else if (uiImage != 0xffffffff)
            {

               pmenucentral->MenuV033GetImageList()->draw(pgraphics, uiImage, rectImage.top_left(), 0);

            }

         }
         else
         {

            if ((nStyle & TBBS_DISABLED) == 0)
            {

               ptoolbar->_001GetElementRect(iItem, rectItem, ::user::toolbar::element_item);

               pgraphics->fill_solid_rect(rectItem, ARGB(184, 255, 255, 255));

            }

            if ((nStyle & TBBS_CHECKED) != 0)
            {

               pgraphics->draw3d_rect(rectItem, ARGB(255, 127, 127, 127), ARGB(255, 255, 255, 255));

            }

            if (item.m_spdib.is_set())
            {

               rect rect;

               ptoolbar->_001GetElementRect(iItem, rect, ::user::toolbar::element_image);

               Application.imaging().color_blend(pgraphics, rect.top_left(), rect.get_size(), item.m_spdib->get_graphics(), null_point(), 0.23);

            }
            else if (uiImage != 0xffffffff)
            {

               if ((nStyle & TBBS_DISABLED) == 0)
               {

                  pmenucentral->MenuV033GetImageListBlend()->draw(pgraphics, uiImage, rectImage.top_left(), 0);

               }
               else
               {

                  pmenucentral->MenuV033GetImageListHueLight()->draw(pgraphics, uiImage, rectImage.top_left(), 0);

               }

            }

         }

      }

      if (item.m_str.has_char())
      {

         ptoolbar->select_font(pgraphics, ::user::font_toolbar);

         rect rectText;

         ::draw2d::brush_sp brushText(allocer());

         if ((nStyle & TBBS_DISABLED) == 0)
         {

            brushText->create_solid(ARGB(255, 0, 0, 0));

         }
         else
         {

            brushText->create_solid(ARGB(255, 123, 123, 118));

         }

         pgraphics->SelectObject(brushText);

         if (ptoolbar->_001GetElementRect(iItem, rectText, eelementText) && rectText.right > 0)
         {

            pgraphics->_DrawText(item.m_str, item.m_str.get_length(), rectText, DT_BOTTOM | DT_LEFT | DT_NOPREFIX);

         }

      }

   }

   void theme::_001DrawTranquillumToolbarItem(::draw2d::graphics * pgraphics, int32_t iItem, ::user::toolbar * ptoolbar)
   {

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      rect rectItem;

      rect rectImage;

      ptoolbar->select_font(pgraphics, ::user::font_toolbar);

      ::user::toolbar_item & item = ptoolbar->m_itema(iItem);

      UINT nStyle = ptoolbar->GetButtonStyle(iItem);

      bool bHover = iItem == ptoolbar->_001GetHoverItem();

      BaseMenuCentral * pmenucentral = BaseMenuCentral::GetMenuCentral(get_app());

      UINT uiImage = pmenucentral->CommandToImage(item.m_id);

      ::user::toolbar::e_element eelement = ::user::toolbar::element_item;
      ::user::toolbar::e_element eelementImage = ::user::toolbar::element_image;
      ::user::toolbar::e_element eelementText = ::user::toolbar::element_text;
      if ((nStyle & TBBS_SEPARATOR) == 0)
      {
         if ((nStyle & TBBS_DISABLED) == 0)
         {
            // item is enabled
            if (ptoolbar->m_iButtonPressItem >= 0)
            {
               if (iItem == ptoolbar->m_iButtonPressItem)
               {
                  if (bHover)
                  {
                     eelement = ::user::toolbar::ElementItemPress;
                     eelementImage = ::user::toolbar::ElementImagePress;
                     eelementText = ::user::toolbar::ElementTextPress;
                  }
                  else
                  {
                     eelement = ::user::toolbar::ElementItemHover;
                     eelementImage = ::user::toolbar::ElementImageHover;
                     eelementText = ::user::toolbar::ElementTextHover;
                  }
               }
            }
            else if (bHover)
            {
               eelement = ::user::toolbar::ElementItemHover;
               eelementImage = ::user::toolbar::ElementImageHover;
               eelementText = ::user::toolbar::ElementTextHover;
            }
         }
         else
         {
            // item is disabled
            eelement = ::user::toolbar::element_item;
            eelementImage = ::user::toolbar::element_image;
            eelementText = ::user::toolbar::element_text;
         }
      }
      else
      {
         eelement = ::user::toolbar::element_item;
         eelementImage = ::user::toolbar::element_image;
         eelementText = ::user::toolbar::element_text;
      }


      //int iOffsetX = 0;
      //int iOffsetY = 0;

      ptoolbar->_001GetElementRect(iItem, rectItem, eelement);

      ptoolbar->_001GetElementRect(iItem, rectImage, eelementImage);

      if (item.m_id.compare_ci("separator") == 0)
      {
         /*rect rectSeparator;
         rectSeparator.left = (rectImage.left + rectImage.right) / 2 - 1;
         rectSeparator.right = rectSeparator.left + 2;
         rectSeparator.top = rectImage.top;
         rectSeparator.bottom = rectImage.bottom;*/
         //pgraphics->Draw3dRect(rectSeparator, ARGB(255, 92, 92, 92), ARGB(255, 255, 255, 255));
      }
      else
      {
         if (eelement == ::user::toolbar::ElementItemHover)
         {
            if ((nStyle & TBBS_CHECKED) != 0)
            {

               ptoolbar->_001GetElementRect(iItem, rectItem, ::user::toolbar::element_item);

               ptoolbar->_001GetElementRect(iItem, rectImage, ::user::toolbar::element_image);

               if ((ptoolbar->m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
               {
                  Application.imaging().color_blend(
                  pgraphics,
                  rectItem.left,
                  rectItem.top,
                  rectItem.width(),
                  rectItem.height(),
                  RGB(255, 255, 250), 208);

                  pgraphics->draw3d_rect(rectItem, ARGB(255, 127, 127, 127), ARGB(255, 255, 255, 255));

               }

               if (uiImage != 0xffffffffu)
               {

                  if ((nStyle & TBBS_DISABLED) == 0)
                  {

                     // button is enabled
                     pmenucentral->MenuV033GetImageListBlend()->draw(pgraphics, uiImage, rectImage.top_left(), 0);

                  }
                  else
                  {

                     // button is disabled
                     pmenucentral->MenuV033GetImageListHueLight()->draw(pgraphics, uiImage, rectImage.top_left(), 0);

                  }

               }

            }
            else
            {

               rect rectShadow;

               ptoolbar->_001GetElementRect(iItem, rectShadow, ::user::toolbar::ElementItemHover);

               if ((ptoolbar->m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
               {

                  ::draw2d::pen_sp pen(pgraphics, 1, ptoolbar->_001GetColor(::user::color_button_background_hover));
                  ::draw2d::brush_sp brush(allocer(), ptoolbar->_001GetColor(::user::color_button_background_hover));
                  ::draw2d::pen * ppenOld = pgraphics->SelectObject(pen);
                  ::draw2d::brush * pbrushOld = pgraphics->SelectObject(brush);
                  pgraphics->rectangle(rectItem);
                  pgraphics->SelectObject(ppenOld);
                  pgraphics->SelectObject(pbrushOld);

               }

               if (item.m_spdib.is_set())
               {

                  rect rect;

                  ptoolbar->_001GetElementRect(iItem, rect, ::user::toolbar::ElementImageHover);

                  Application.imaging().color_blend(pgraphics, rect.top_left(), rect.get_size(), item.m_spdib->get_graphics(), null_point(), 0.84);

               }
               else if (uiImage != 0xffffffffu)
               {

                  rect rect;

                  ptoolbar->_001GetElementRect(iItem, rect, ::user::toolbar::ElementItemHover);

                  pmenucentral->MenuV033GetImageListHue()->draw(pgraphics, uiImage, rect.top_left(), 0);

                  pmenucentral->MenuV033GetImageList()->draw(pgraphics, uiImage, rectImage.top_left(), 0);
               }

            }

         }
         else if (eelement == ::user::toolbar::ElementItemPress)
         {

            if ((ptoolbar->m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
            {

               ::draw2d::pen_sp pen(pgraphics, 1, ptoolbar->_001GetColor(::user::color_button_background_press));
               ::draw2d::brush_sp brush(allocer(), ptoolbar->_001GetColor(::user::color_button_background_press));
               ::draw2d::pen * ppenOld = pgraphics->SelectObject(pen);
               ::draw2d::brush * pbrushOld = pgraphics->SelectObject(brush);
               pgraphics->rectangle(rectItem);
               pgraphics->SelectObject(ppenOld);
               pgraphics->SelectObject(pbrushOld);

            }

            if (item.m_spdib.is_set())
            {

               rect rect;

               ptoolbar->_001GetElementRect(iItem, rect, ::user::toolbar::ElementImagePress);

               Application.imaging().color_blend(pgraphics, rect.top_left(), rect.get_size(), item.m_spdib->get_graphics(), null_point(), 1.0);

            }
            else if (uiImage != 0xffffffff)
            {

               pmenucentral->MenuV033GetImageList()->draw(pgraphics, uiImage, rectImage.top_left(), 0);

            }

         }
         else
         {

            if ((nStyle & TBBS_DISABLED) == 0)
            {

               ptoolbar->_001GetElementRect(iItem, rectItem, ::user::toolbar::element_item);

               pgraphics->fill_solid_rect(rectItem, ARGB(184, 255, 255, 255));

            }

            if ((nStyle & TBBS_CHECKED) != 0)
            {

               pgraphics->draw3d_rect(rectItem, ARGB(255, 127, 127, 127), ARGB(255, 255, 255, 255));

            }

            if ((ptoolbar->m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
            {

               ::draw2d::pen_sp pen(pgraphics, 1, ptoolbar->_001GetColor(
                                    (nStyle & TBBS_DISABLED) == 0 ?
                                    ::user::color_button_background :
                                    ::user::color_button_background_disabled));
               ::draw2d::brush_sp brush(allocer(), ptoolbar->_001GetColor(
                                        (nStyle & TBBS_DISABLED) == 0 ?
                                        ::user::color_button_background :
                                        ::user::color_button_background_disabled));
               ::draw2d::pen * ppenOld = pgraphics->SelectObject(pen);
               ::draw2d::brush * pbrushOld = pgraphics->SelectObject(brush);
               pgraphics->rectangle(rectItem);
               pgraphics->SelectObject(ppenOld);
               pgraphics->SelectObject(pbrushOld);

            }

            if (item.m_spdib.is_set())
            {

               rect rect;

               ptoolbar->_001GetElementRect(iItem, rect, ::user::toolbar::element_image);

               Application.imaging().color_blend(pgraphics, rect.top_left(), rect.get_size(), item.m_spdib->get_graphics(), null_point(), 0.23);

            }
            else if (uiImage != 0xffffffff)
            {

               if ((nStyle & TBBS_DISABLED) == 0)
               {

                  pmenucentral->MenuV033GetImageListBlend()->draw(pgraphics, uiImage, rectImage.top_left(), 0);

               }
               else
               {

                  pmenucentral->MenuV033GetImageListHueLight()->draw(pgraphics, uiImage, rectImage.top_left(), 0);

               }

            }

         }

      }

      if (item.m_str.has_char())
      {

         ptoolbar->select_font(pgraphics, ::user::font_toolbar);

         rect rectText;

         ::draw2d::brush_sp brushText(allocer());

         if ((nStyle & TBBS_DISABLED) == 0)
         {

            brushText->create_solid(ARGB(255, 255, 255, 255));

            pgraphics->set_text_color(ARGB(255, 255, 255, 255));

         }
         else
         {

            brushText->create_solid(::user::color_button_text_disabled);

            pgraphics->set_text_color(ptoolbar->_001GetColor(

                                      ::user::color_button_text_disabled));

         }

         if (ptoolbar->_001GetElementRect(iItem, rectText, eelementText) && rectText.right > 0)
         {

            pgraphics->_DrawText(item.m_str, item.m_str.get_length(), rectText, DT_BOTTOM | DT_LEFT | DT_NOPREFIX);

         }

      }

   }


   bool theme::_001OnDrawSplitLayout(::draw2d::graphics * pgraphics, ::user::split_layout * psplitlayout)
   {

      rect rectClient;

      psplitlayout->GetClientRect(rectClient);

      pgraphics->fill_solid_rect(rectClient, ARGB(255, 255, 255, 255));

      return true;

   }


   //bool theme::get_font(::draw2d::font_sp & sp, ::user::e_font efont, ::user::style_context * pcontext)
   //{

   //   return ::user::theme::get_font(sp, efont, pcontext);

   //}

   //bool theme::get_double(double & d, ::user::e_double edouble, ::user::style_context * pcontext)
   //{

   //   if (edouble == ::user::double_height_rate)
   //   {

   //      d = 1.65;

   //      return true;

   //   }

   //   return ::user::theme::get_double(d, edouble, pcontext);

   //}

} // namespace wndfrm_tranquillum









