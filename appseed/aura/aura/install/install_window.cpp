#include "framework.h"


#define ID_ONE 1

namespace install
{


   window * window::s_p = NULL;


   window::window(::aura::application * papp) :
      ::object(papp),
      m_font(allocer()),
      m_fontBold(allocer()),
      m_fontHeader(allocer()),
      m_penBorder(allocer()),
      m_brushText(allocer()),
      m_penBarBorder(allocer()),
      m_brushBar(allocer()),
      m_brushBarBk(allocer()),
      m_brushBk(allocer())

   {

      s_p = this;

      m_bDraw = true;

      m_dAnime = 0.0;

      m_dPi = asin(1.0) * 4;

      m_bDrag = false;

      m_bDrag = false;

      m_bRunMainLoop = true;

   }


   window::~window()
   {

   }
   void window::layout()
   {

      rect rectClient;

      GetClientRect(rectClient);

      if (rectClient.area() <= 0)
      {

         return;

      }

      on_resize(rectClient.width(), rectClient.height());

   }


   void window::on_resize(int cx, int cy)
   {

      m_font->create_point_font("Lucida Sans Unicode", 10.0);
      m_fontBold->create_point_font("Lucida Sans Unicode", 10.0, 800);
      m_fontHeader->create_point_font("Lucida Sans Unicode", 16.0, 800);
      m_penBorder->create_solid(1.0, ARGB(80, 80, 80, 80));
      m_brushText->create_solid(ARGB(180, 230, 230, 220));
      m_penBarBorder->create_solid(1.0, ARGB(255, 150,150, 140));
      m_brushBar->create_solid(ARGB(180, 80, 180, 80));
      m_brushBarBk->create_solid(ARGB(255, 110, 110, 110));
      m_brushBk->create_solid(ARGB(210, 20, 20, 20));

   }


   void window::_001OnDraw(::draw2d::graphics * pgraphics)
   {

      draw_install(pgraphics);

   }


   bool window::has_pending_graphical_update()
   {

      return IsWindowVisible();

   }



   void window::draw_install(::draw2d::graphics * pgraphics)
   {

      int iMode = 1;

      bool bProgress = false;

      double dProgressTotal = 0.0;

      double dProgress = 0.0;

      string strHeader;

      string strBold;

      string strNormal;

      string strProgress;

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_set);

      ::rect rect;

      GetClientRect(&rect);

      pgraphics->FillSolidRect(rect, ARGB(208, 0, 0, 0));

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      pgraphics->set_text_rendering(::draw2d::text_rendering_anti_alias_grid_fit);

      {

         string strPlatform = "x86";

         ::mutex m(NULL, false, "Global\\ca2-install-install-" + strPlatform);

         synch_lock sl(&m);

         string strFile = dir::install() / ("install-" + strPlatform + ".log");

         ::file::file_sp file = Application.file().get_file(strFile, ::file::type_binary | ::file::mode_read | ::file::share_deny_none);

         if (file.is_set())
         {

            auto iTell = file->seek(0, ::file::seek_end);

            iTell--;

            string strLine;

            int iSkip = 0;

            bool bNormal = false;

            bool bHeader = false;

            bool bBold = false;

            bool bPreNormal = true;

            bool bStart = false;

            while (iTell > 0 && !bStart && !(bNormal && bBold && bProgress && bHeader))
            {

               file->seek(iTell, ::file::seek_begin);

               char ch;

               file->read( &ch, 1);

               if (ch == '\r')
               {

                  iSkip++;

               }
               else if (ch == '\n')
               {

                  iSkip++;

               }
               else if (iSkip > 0)
               {

                  iSkip = 0;

                  strLine.trim();

                  if (strLine == "--")
                  {

                     bStart = true;

                  }
                  else if (::str::begins_eat(strLine, "#----------"))
                  {

                     strHeader = L"Thank you";

                     bHeader = true;

                     strBold = u16(strLine);

                     bBold = true;

                     dProgress = 0.0;

                     bProgress = true;

                  }
                  else if (::str::begins_eat(strLine, ":::::"))
                  {
                     if (!bHeader && strLine.length() > 0 && bBold && bNormal && bPreNormal)
                     {
                        bHeader = true;
                        strHeader = u16(strLine);
                     }
                  }
                  else if (::str::begins_eat(strLine, "***"))
                  {
                     if (!bBold && strLine.length() > 0 && bNormal && bPreNormal)
                     {
                        bBold = true;
                        strBold = u16(strLine);
                     }
                  }
                  else if (::str::begins_eat(strLine, "|||"))
                  {
                     if (!bProgress && strLine.length() > 0)
                     {
                        bProgress = true;
                        long long int i = atoi64_dup(strLine.c_str());
                        dProgress = (double)i / 10000000.0;
                        //char sz[128];
                        //sprintf(sz,"%0.1f%%",dProgress);
                        //strProgress = u16(sz);
                        dProgress /= 100.0;
                     }
                  }
                  else if (!::str::begins_ci(strLine, "/ ") && strLine.length() > 0 && !bNormal && !bBold && !bHeader && bPreNormal)
                  {
                     bNormal = true;
                     strNormal = u16(strLine);
                  }
                  //else if(strLine.length() > 0 && !bPreNormal && !bBold && !bNormal && !bHeader)
                  //{
                  //   bPreNormal = true;
                  //   //::SelectObject(hdc, hfont);
                  //   //::TextOutU(hdc, 10, 10 + size.cy * 4, strLine.c_str(), strLine.length());
                  //}
                  strLine = ch;
               }
               else
               {
                  strLine = ch + strLine;
               }
               iTell--;
            }
         }
      }

      dProgressTotal += dProgress / 2.0;

      dProgress = 0.0;

      strHeader.Empty();
      strBold.Empty();
      strNormal.Empty();
      strProgress.Empty();

      {

         string strPlatform = "x64";

         ::mutex m(NULL, false, "Global\\ca2-install-install-" + strPlatform);

         synch_lock sl(&m);

         string strFile = dir::install() / ("install-" + strPlatform + ".log");


         ::file::file_sp file = Application.file().get_file(strFile, ::file::type_binary | ::file::mode_read);

         if (file.is_set())
         {

            auto iTell = file->seek(0, ::file::seek_end);

            iTell--;

            string strLine;
            int iSkip = 0;
            bool bNormal = false;
            bool bHeader = false;
            bool bBold = false;
            bool bPreNormal = true;
            bool bStart = false;
            while (iTell > 0 && !bStart && !(bNormal && bBold && bProgress && bHeader))
            {
               iTell = file->seek(iTell, ::file::seek_end);
               char ch;
               file->read(&ch, 1);
               if (ch == '\r')
               {
                  iSkip++;
               }
               else if (ch == '\n')
               {
                  iSkip++;
               }
               else if (iSkip > 0)
               {
                  iSkip = 0;
                  strLine.trim();
                  if (strLine == "--")
                  {
                     bStart = true;
                  }
                  else if (::str::begins_eat(strLine, "#----------"))
                  {
                     strHeader = L"Thank you";
                     bHeader = true;
                     strBold = u16(strLine);
                     bBold = true;
                     dProgress = 0.0;
                     bProgress = true;
                  }
                  else if (::str::begins_eat(strLine, ":::::"))
                  {
                     if (!bHeader && strLine.length() > 0 && bBold && bNormal && bPreNormal)
                     {
                        bHeader = true;
                        strHeader = u16(strLine);
                     }
                  }
                  else if (::str::begins_eat(strLine, "***"))
                  {
                     if (!bBold && strLine.length() > 0 && bNormal && bPreNormal)
                     {
                        bBold = true;
                        strBold = u16(strLine);
                     }
                  }
                  else if (::str::begins_eat(strLine, "|||"))
                  {
                     if (!bProgress && strLine.length() > 0)
                     {
                        bProgress = true;
                        long long int i = atoi64_dup(strLine.c_str());
                        dProgress = (double)i / 10000000.0;
                        //char sz[128];
                        //sprintf(sz,"%0.1f%%",dProgress);
                        //strProgress = u16(sz);
                        dProgress /= 100.0;
                     }
                  }
                  else if (!::str::begins_ci(strLine, "/ ") && strLine.length() > 0 && !bNormal && !bBold && !bHeader && bPreNormal)
                  {
                     bNormal = true;
                     strNormal = u16(strLine);
                  }
                  //else if(strLine.length() > 0 && !bPreNormal && !bBold && !bNormal && !bHeader)
                  //{
                  //   bPreNormal = true;
                  //   //::SelectObject(hdc, hfont);
                  //   //::TextOutU(hdc, 10, 10 + size.cy * 4, strLine.c_str(), strLine.length());
                  //}
                  strLine = ch;
               }
               else
               {
                  strLine = ch + strLine;
               }
               iTell--;
            }

         }
      }

      dProgressTotal += dProgress / 2.0;

      dProgress = dProgressTotal;

      strHeader.Empty();
      strBold.Empty();
      strNormal.Empty();
      strProgress.Empty();



      int cx = rect.width();

      int cy = rect.height();

      iMode = iMode % 5;

      if (iMode == 2 || iMode == 1 || iMode == 0)
      {

         pgraphics->DrawRect(rect, m_penBorder);

      }

      pgraphics->SelectFont(m_font);

      ::size s = pgraphics->GetTextExtent(L"CCpp");

      double cyText = MAX(s.cy, 5.0);

      int iLineCount = (int) ((rect.bottom - 30) / cyText);

      // !m_bHealingSurface => "Surgery Internals"
      {

         size_t iRefresh = 884;
         size_t iEat = 8;
         //      const wchar_t * psz = L"development message so international english file \"install.log\" excerpt  ::::::::";
         //    pgraphics->DrawString(psz,wcslen(psz) - iEat + 1 + ((::GetTickCount() / (iRefresh - 277) % iEat)),g_pfont,PointF(10,10 + cyText * 2),StringFormat::GenericTypographic(),g_ptextColor1);

         if (strHeader.length() > 0)
         {
            pgraphics->SelectFont(m_fontHeader);
            pgraphics->SelectObject(m_brushText);
            pgraphics->text_out(10.0, 10+cyText * 3 + 4, strHeader);
         }
         if (strBold.length() > 0)
         {
            pgraphics->SelectFont(m_fontBold);
            pgraphics->SelectObject(m_brushText);
            pgraphics->text_out(10.0, 10 + cyText * 5, strBold);
         }
         if (strNormal.length() > 0)
         {
            pgraphics->SelectFont(m_font);
            pgraphics->SelectObject(m_brushText);
            pgraphics->text_out(10.0, 10 + cyText * 6, strNormal);
         }
         //if(strProgress.length() > 0)
         //{
         //   pgraphics->DrawString(u16(strProgress),-1,m_pfont,PointF(10,10 + cyText * 7),StringFormat::GenericTypographic(),m_ptextColor1);
         //}

      }

      double cyBar = cyText * 1.2;

      {

         pgraphics->SelectObject(m_brushBarBk);
         pgraphics->FillRectangle(
         ::rect(point(10, (int) ((rect.top + rect.bottom - cyBar) / 2.0)),
                ::size((int) (rect.right - 10 - 10), (int) (cyBar))));

         if (bProgress)
         {
            double iRight = ((double)cx - 11.0 - 11.0) * dProgress;
            pgraphics->SelectObject(m_brushBar);

            pgraphics->FillRectangle(
            ::rect(
            ::point(11, (int)((rect.top + rect.bottom - cyBar) / 2.0 + 1.0)),
            ::size((int) iRight, (int) (cyBar - 1.0))));

         }
         else
         {
            double dPeriod = 2000.0;
            dProgress = fmod((double)get_tick_count(), dPeriod) / dPeriod;
            double iBarWidth = (rect.right - 11.0 - 11.0) / 2;
            double i = ((rect.right - 11.0 - 11.0) * dProgress) + 11.0;
            double iRight = i + iBarWidth;
            pgraphics->SelectObject(m_brushBar);

            pgraphics->FillRectangle(
            ::rect(
            ::point((int) (11.0 + i), (int) ((rect.top + rect.bottom - cyBar) / 2.0 + 1.0)),
            ::size((int) (MIN(rect.right - 10.0, iRight) - 11 - i), (int) (cyBar - 1.0))));

            if (iRight >= rect.right - 10)
            {

               pgraphics->FillRectangle(
               ::rect(
               ::point((int) (11.0), (int) ((rect.top + rect.bottom - cyBar) / 2.0 + 1.0)),
               ::size((int) (iRight - rect.right - 10.0 - 11.0), (int) (cyBar - 1.0))));

            }
         }

         pgraphics->SelectObject(m_penBarBorder);

         pgraphics->DrawRectangle(
         ::rect(
         ::point((int) 10.0, (int) ((rect.top + rect.bottom - cyBar) / 2.0)),
         ::size((int) (rect.right - 10.0 - 10.0), (int) cyBar)));

      }

      {

         pgraphics->selectFont(m_font);

         pgraphics->SelectObject(m_brushText);

         pgraphics->text_out(10.0, 10.0, "Thank you");

      }

   }







//   bool window::update_layered_window()
//   {
//
//#ifdef WINDOWSEX
//
//      RECT rect;
//
//      rect.left = 0;
//
//      rect.top = 0;
//
//      rect.right = m_cx;
//
//      rect.bottom = m_cy;
//
//      m_dib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);
//
//      {
//
//         m_dib->get_graphics()->SelectObject(m_brushBk);
//
//         m_dib->get_graphics()->FillRectangle(rect);
//
//      }
//
//      paint_install(&rect, 1);
//
//      RECT rectWindow;
//
//      oswindow hwnd = get_safe_handle();
//
//      ::GetWindowRect(hwnd, &rectWindow);
//
//      HDC hdcWindow = ::GetWindowDC(hwnd);
//
//      POINT pt;
//
//      pt.x = rectWindow.left;
//
//      pt.y = rectWindow.top;
//
//      SIZE sz;
//
//      sz.cx = ::width(&rectWindow);
//
//      sz.cy = ::height(&rectWindow);
//
//      POINT ptSrc = { 0 };
//
//      BLENDFUNCTION blendPixelFunction = { AC_SRC_OVER,0,255,AC_SRC_ALPHA };
//
//      UpdateLayeredWindow(hwnd, hdcWindow, &pt, &sz, m_hdc, &ptSrc, 0, &blendPixelFunction, ULW_ALPHA);
//
//      ::ReleaseDC(hwnd, hdcWindow);
//
//#endif
//
//      return true;
//
//   }


//   LRESULT window::message_handler(UINT message, WPARAM wParam, LPARAM lParam)
//   {
//
//#ifdef WINDOWSEX
//
//      switch (message)
//      {
//
//      case WM_CREATE:
//
//         break;
//
//      case WM_PAINT:
//
//         break;
//
//      case WM_ERASEBKGND:
//
//         return TRUE;
//
//      case WM_MBUTTONDOWN:
//
//      case WM_RBUTTONDOWN:
//
//         return TRUE;
//
//      case WM_LBUTTONDOWN:
//      {
//
//         m_bDrag = true;
//
//         ::GetCursorPos(&m_ptDragStart);
//
//         GetWindowRect(&m_rectWindowDragStart);
//
//      }
//
//      break;
//
//      case WM_MOUSEMOVE:
//      {
//
//         if (m_bDrag)
//         {
//
//            drag();
//
//         }
//
//      };
//      break;
//      case WM_LBUTTONUP:
//      {
//         if (m_bDrag)
//         {
//
//            drag();
//
//            m_bDrag = false;
//
//         }
//
//      };
//
//      break;
//
//      case WM_DESTROY:
//
//         m_bDraw = false;
//
//         Sleep(2000);
//
//         delete this;
//
//         PostQuitMessage(0);
//
//         break;
//
//
//      default:
//
//         return DefWindowProc(m_hwnd, message, wParam, lParam);
//
//      }
//
//#endif
//
//      return 0;
//
//   }


   void window::drag()
   {

#ifdef WINDOWSEX
      POINT ptCursor;

      ::GetCursorPos(&ptCursor);

      SetWindowPos(NULL,
                   ptCursor.x - m_ptDragStart.x + m_rectWindowDragStart.left,
                   ptCursor.y - m_ptDragStart.y + m_rectWindowDragStart.top,
                   0,
                   0,
                   SWP_NOSIZE | SWP_SHOWWINDOW);
#endif

   }


   //void window::draw()
   //{

   //   while (::get_thread_run() && m_bDraw)
   //   {

   //      if (!update_layered_window())
   //      {

   //         break;

   //      }

   //      Sleep(5);

   //   }

   //}


   bool window::create()
   {

      if (!create_window_ex(WS_EX_LAYERED, NULL, NULL, 0))
      {

         return false;

      }

      ModifyStyle(WS_BORDER | WS_POPUP | WS_CAPTION, 0);

      return true;

   }




   void window::main()
   {

      //while (GetMessage(&m_msg, NULL, 0, 0) && m_bRunMainLoop && !Application.m_bFinished)
      //{

      //   TranslateMessage(&m_msg);

      //   DispatchMessage(&m_msg);

      //}

   }


} // namespace install


