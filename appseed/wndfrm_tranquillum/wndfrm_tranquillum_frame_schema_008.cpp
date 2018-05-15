#include "framework.h"


#define GRIP_CORNER_LARGE_CX 16
#define GRIP_CORNER_SMALL_CX 5
#define GRIP_CORNER_LARGE_CY 16
#define GRIP_CORNER_SMALL_CY 5


#define GRIP_CENTER_LARGE_CX 36
#define GRIP_CENTER_SMALL_CX 7
#define GRIP_CENTER_LARGE_CY 36
#define GRIP_CENTER_SMALL_CY 7


namespace user
{


   namespace wndfrm
   {


      namespace frame
      {


         namespace wndfrm_tranquillum
         {


            FrameSchemaHardCoded008::FrameSchemaHardCoded008(::aura::application * papp) :
               object(papp),
               frame_schema(papp)
            {

               m_bHollow = false;

               set_style(StyleTranslucidWarmLiteGray);

               m_penHollow1.alloc(allocer());
               m_penHollow2.alloc(allocer());
               m_penHollow3.alloc(allocer());
               m_penHollow4.alloc(allocer());
               m_penHollow5.alloc(allocer());

            }


            FrameSchemaHardCoded008::~FrameSchemaHardCoded008()
            {

            }


            EHitTest FrameSchemaHardCoded008::_000HitTest(point ptCursor)
            {
               EHitTest etest = HitTestClient;
               {
                  //      m_pworkset->GetEventWindow()->ScreenToClient(pt);
                  rect rectEvent;
                  m_pworkset->GetRegionWindow()->GetWindowRect(rectEvent);
                  rect rect;
                  //point ptCenter = rectEvent.center();
                  EGrip egrip = m_pworkset->GetSizingManager()->GetGripMask();

                  point ptHitTest = ptCursor;

                  if(rectEvent.left < 0)
                     ptHitTest.x -= rectEvent.left;
                  if(rectEvent.top < 0)
                     ptHitTest.y -= rectEvent.top;

                  if(egrip & GripTopLeft)
                  {
                     rect = rectEvent;
                     rect.right = rect.left + 16;
                     rect.bottom = rect.top + 5;
                     if(rect.contains(ptHitTest))
                     {
                        etest = HitTestSizingTopLeft;
                        goto SizingSuccess;
                     }
                     rect = rectEvent;
                     rect.right = rect.left + 5;
                     rect.bottom = rect.top + 16;
                     if(rect.contains(ptHitTest))
                     {
                        etest = HitTestSizingTopLeft;
                        goto SizingSuccess;
                     }
                  }
                  if(egrip & GripTopRight)
                  {
                     rect = rectEvent;
                     rect.left = rect.right - 16;
                     rect.bottom = rect.top + 5;
                     if(rect.contains(ptHitTest))
                     {
                        etest = HitTestSizingTopRight;
                        goto SizingSuccess;
                     }
                     rect = rectEvent;
                     rect.left = rect.right - 5;
                     rect.bottom = rect.top + 16;
                     if(rect.contains(ptHitTest))
                     {
                        etest = HitTestSizingTopRight;
                        goto SizingSuccess;
                     }
                  }
                  if(egrip & GripBottomRight)
                  {
                     rect = rectEvent;
                     rect.left = rect.right - 16;
                     rect.top = rect.bottom - 5;
                     if(rect.contains(ptHitTest))
                     {
                        etest = HitTestSizingBottomRight;
                        goto SizingSuccess;
                     }
                     rect = rectEvent;
                     rect.left = rect.right - 5;
                     rect.top = rect.bottom - 16;
                     if(rect.contains(ptHitTest))
                     {
                        etest = HitTestSizingBottomRight;
                        goto SizingSuccess;
                     }
                  }
                  if(egrip & GripBottomLeft)
                  {
                     rect = rectEvent;
                     rect.right = rect.left + 16;
                     rect.top = rect.bottom - 5;
                     if(rect.contains(ptHitTest))
                     {
                        etest = HitTestSizingBottomLeft;
                        goto SizingSuccess;
                     }
                     rect = rectEvent;
                     rect.right = rect.left + 5;
                     rect.top = rect.bottom - 16;
                     if(rect.contains(ptHitTest))
                     {
                        etest = HitTestSizingBottomLeft;
                        goto SizingSuccess;
                     }
                  }
                  if(egrip & GripCenterTop)
                  {
                     rect.top = rectEvent.top;
                     rect.left = rectEvent.left;
                     rect.right = rectEvent.right;
                     rect.bottom = rectEvent.top + 5;
                     if(rect.contains(ptHitTest))
                     {
                        etest = HitTestSizingTop;
                        goto SizingSuccess;
                     }
                  }
                  if(egrip & GripCenterBottom)
                  {
                     rect.top = rectEvent.bottom - 5;
                     rect.left = rectEvent.left;
                     rect.right = rectEvent.right;
                     rect.bottom = rectEvent.bottom;
                     if(rect.contains(ptHitTest))
                     {
                        etest = HitTestSizingBottom;
                        goto SizingSuccess;
                     }
                  }
                  if(egrip & GripCenterLeft)
                  {
                     rect.top = rectEvent.top;
                     rect.left = rectEvent.left;
                     rect.right = rectEvent.left + 5;
                     rect.bottom = rectEvent.bottom;
                     if(rect.contains(ptHitTest))
                     {
                        etest = HitTestSizingLeft;
                        goto SizingSuccess;
                     }
                  }
                  if(egrip & GripCenterRight)
                  {
                     rect.top = rectEvent.top;
                     rect.left = rectEvent.right - 5;
                     rect.right = rectEvent.right;
                     rect.bottom = rectEvent.bottom;
                     if(rect.contains(ptHitTest))
                     {
                        etest = HitTestSizingRight;
                        goto SizingSuccess;
                     }
                  }
                  goto SizingNone;
SizingSuccess:
                  return etest;
SizingNone:
                  ;
               }
               return HitTestClient;
            }






            void FrameSchemaHardCoded008::DrawBorderSide(::draw2d::graphics * pgraphics, const RECT & lpcrectClient, EBorder eside)
            {

               appearance * pappearance = get_appearance();

               if(pappearance == NULL)
                  return;

               COLORREF    crMoveableBorder;
               COLORREF    crMoveableBorderHilight;
               COLORREF    crMoveableBorderShadow;

               if(pappearance->m_fActive)
               {
                  crMoveableBorder = m_crMoveableBorder;
                  crMoveableBorderHilight = m_crMoveableBorderHilight;
                  crMoveableBorderShadow = m_crMoveableBorderShadow;
               }
               else
               {
                  crMoveableBorder = Session.get_default_color(COLOR_BTNFACE);
                  crMoveableBorderHilight = Session.get_default_color(COLOR_BTNHILIGHT);
                  crMoveableBorderShadow = Session.get_default_color(COLOR_BTNSHADOW);
               }

               EDock edock = m_pworkset->GetDockingManager()->GetDockState();
               rect rectA(lpcrectClient);

               if(m_bHollow)
               {


               }
               else if(m_estyle == StyleLightBlue || m_estyle == StyleRedOrange)
               {
                  //rectA.deflate(1,1,1,1);
                  Draw3dRectSide(pgraphics,rectA,eside, crMoveableBorderHilight,0);//m_crMoveableBorderDkShadow);

                  //if(!m_bHollow)
                  //{

                  //   rectA.deflate(1,1,1,1);
                  //   Draw3dRectSide(pgraphics,rectA,eside,crMoveableBorderHilight,crMoveableBorderShadow);

                  //   rectA.deflate(1,1,1,1);
                  //   Draw3dRectSide(pgraphics,rectA,eside,crMoveableBorder,crMoveableBorder);

                  //   rectA.deflate(1,1,1,1);
                  //   Draw3dRectSide(pgraphics,rectA,eside,crMoveableBorder,crMoveableBorder);

                  //   rect rect;
                  //   GetBorderRect(lpcrectClient,rect,eside);
                  //   class imaging & imaging = Application.imaging();
                  //   imaging.color_blend(pgraphics,
                  //      rect,
                  //      crMoveableBorder,
                  //      127);

                  //}

               }
               else if(m_estyle == StyleTranslucidWarmGray
                       || m_estyle == StyleTranslucidLightBlue
                       || m_estyle == StyleTranslucidLightGreen)
               {
                  rect rect;
                  GetBorderRect(lpcrectClient, rect, eside);
                  class imaging & imaging = Application.imaging();
                  imaging.color_blend(pgraphics,
                                      rect,
                                      crMoveableBorder,
                                      127);
               }
               else
               {
                  rect rect;
                  GetBorderRect(lpcrectClient, rect, eside);
                  class imaging & imaging = Application.imaging();
                  imaging.color_blend(pgraphics,
                                      rect,
                                      crMoveableBorder,
                                      127);

                  class rect rectClientB = rectA;

                  rectClientB.bottom--;
                  rectClientB.right--;

                  rectA.top++;
                  rectA.bottom--;
                  rectA.left++;
                  rectA.right--;
                  if(edock == DockNone)
                  {
                     Draw3dRectSide(pgraphics, rectA, eside, m_crDkShadow, m_crDkShadow);
                  }

                  rectA.top++;
                  rectA.bottom--;
                  rectA.left++;
                  rectA.right--;
                  Draw3dRectSide(pgraphics, rectA, eside, m_crDkShadow, m_crDkShadow);

                  rectA.top++;
                  rectA.bottom--;
                  rectA.left++;
                  rectA.right--;
                  if(edock == DockNone)
                  {
                     Draw3dRectSide(pgraphics, rectA, eside, m_crDkShadow, m_crDkShadow);
                  }
               }

            }

            void FrameSchemaHardCoded008::on_draw_frame(::draw2d::graphics * pgraphics)
            {

               sp(::user::interaction) pwndDraw = get_draw_window();

               if(pwndDraw == NULL)
                  return;

               appearance * pappearance = get_appearance();

               if(!pappearance->IsEnabled())
                  return;

               sp(::user::interaction) pwnd = get_window();

               //bool bZoomed = pwnd->WfiIsZoomed() != 0;

               //    CVMSApp * pApp = (CVMSApp *) &System;
               //::aura::savings & savings = Session.savings();


               rect rectClient;
               pwndDraw->GetClientRect(rectClient);

               string str;


               rect rectNClient;

               pwndDraw->GetWindowRect(rectNClient);

               rectNClient -= rectNClient.top_left();

               ////////////////////
               //
               // Routine:
               // draw frame border
               //
               ////////////////////


               if(!pappearance->IsFullScreen())
               {
                  DrawBorder(pgraphics, rectNClient);
               }



            }


            void FrameSchemaHardCoded008::DrawBorder(::draw2d::graphics * pgraphics, const RECT & lpcrectClient)
            {

               MoveManager * pwmm = m_pworkset->GetMovingManager();

               EBorder eborder = pwmm->GetBorderMask();

               if(get_appearance()->IsZoomed())
               {
                  eborder = (EBorder)
                            (eborder &
                             ~(BorderRight
                               | BorderBottom
                               | BorderLeft));
               }



               if(m_bHollow)
               {
                  //return;
                  rect rectA(lpcrectClient);

                  pgraphics->set_alpha_mode(::draw2d::alpha_mode_set);

                  pgraphics->set_smooth_mode(::draw2d::smooth_mode_none);

                  for (index i = 0; i < 9; i++)
                  {

                     pgraphics->draw3d_rect(rectA, ARGB(0, 0, 0, 0), ARGB(0, 0, 0, 0));

                     rectA.deflate(1, 1, 1, 1);

                  }

                  if (m_pworkset->GetWndDraw()->get_handle() == GetActiveWindow())
                  {

                     rect rectA(lpcrectClient);

                     pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

                     pgraphics->set_smooth_mode(::draw2d::smooth_mode_high);

                     for (index i = 0; i < 9; i++)
                     {

                        ::draw2d::pen_sp pen(allocer());

                        pen->create_solid(1.0, ARGB((i+1) * 5, 0, 0, 0));

                        pgraphics->draw_round_rect(rectA, pen, (int) (10 - i));

                        rectA.deflate(1, 1, 1, 1);

                     }

                     //rectA.deflate(9, 9, 9, 9);

                     pgraphics->set_alpha_mode(::draw2d::alpha_mode_set);

                     pgraphics->set_smooth_mode(::draw2d::smooth_mode_none);


                     if (m_estyle == StyleRedOrange)
                     {

                        pgraphics->draw3d_rect(rectA, ARGB(255, 255, 170, 136), ARGB(255, 255, 170, 136));

                     }
                     else if (m_estyle == StyleLightGreen)
                     {

                        pgraphics->draw3d_rect(rectA, ARGB(255, 128, 230, 150), ARGB(255, 128, 230, 150));

                     }
                     else
                     {

                        pgraphics->draw3d_rect(rectA, ARGB(255, 0x07, 0x6D, 0x91), ARGB(255, 0x07, 0x6D, 0x91));

                     }

                  }
                  else
                  {

                     //rectA.deflate(9, 9, 9, 9);
                     pgraphics->draw3d_rect(rectA, ARGB(255, 128, 128, 128), ARGB(255, 128, 128, 128));
                  }


               }
               else
               {

                  if(eborder & BorderTop)
                  {
                     DrawBorderSide(pgraphics,lpcrectClient,BorderTop);
                  }
                  if(eborder & BorderRight)
                  {
                     DrawBorderSide(pgraphics,lpcrectClient,BorderRight);
                  }
                  if(eborder & BorderBottom)
                  {
                     DrawBorderSide(pgraphics,lpcrectClient,BorderBottom);
                  }
                  if(eborder & BorderLeft)
                  {
                     DrawBorderSide(pgraphics,lpcrectClient,BorderLeft);
                  }

               }

            }

            void FrameSchemaHardCoded008::GetBorderRect(
            const RECT & lpcrectClient,
            LPRECT lprect,
            EBorder eside)
            {
               rect rectBig(lpcrectClient);
               rect rectSmall;
               get_window_client_rect(rectSmall);
               rect rect;
               if(eside == BorderTop)
               {
                  rect.left = rectBig.left;
                  rect.right = rectBig.right;
                  rect.top = rectBig.top;
                  rect.bottom = rectSmall.top;
               }
               else if(eside == BorderLeft)
               {
                  rect.left = rectBig.left;
                  rect.right = rectSmall.left;
                  rect.top = rectSmall.top;
                  rect.bottom = rectSmall.bottom;
               }
               else if(eside == BorderRight)
               {
                  rect.left = rectSmall.right;
                  rect.right = rectBig.right;
                  rect.top = rectSmall.top;
                  rect.bottom = rectSmall.bottom;
               }
               else if(eside == BorderBottom)
               {
                  rect.left = rectBig.left;
                  rect.right = rectBig.right;
                  rect.top = rectSmall.bottom;
                  rect.bottom = rectBig.bottom;
               }
               *lprect = rect;
            }


            void FrameSchemaHardCoded008::on_style_change()
            {

               on_style_change_001_and_002();
               m_rectMarginNormal.set(10, 10, 10, 10);

               if (m_estyle == StyleDarkRed)
               {
                  //m_penHollow1->create_solid(1.0, ARGB(20, 0, 0, 0));
                  //m_penHollow2->create_solid(1.0, ARGB(60, 20, 20, 20));
                  //m_penHollow3->create_solid(1.0, ARGB(100, 40, 40, 40));
                  //m_penHollow4->create_solid(1.0, ARGB(140, 60, 60, 60));
                  //m_penHollow5->create_solid(1.0, ARGB(255, 90, 220, 100));
                  m_crCaptionTextBk = ARGB(255, 200, 200, 200);
                  m_crActiveCaptionTextBk = ARGB(255, 165, 32, 32);
               }
               else if (m_estyle == StyleLightGreen)
               {
                  //m_penHollow1->create_solid(1.0, ARGB(20, 0, 0, 0));
                  //m_penHollow2->create_solid(1.0, ARGB(60, 20, 20, 20));
                  //m_penHollow3->create_solid(1.0, ARGB(100, 40, 40, 40));
                  //m_penHollow4->create_solid(1.0, ARGB(140, 60, 60, 60));
                  //m_penHollow5->create_solid(1.0, ARGB(255, 90, 220, 100));
                  m_crCaptionTextBk = ARGB(255, 200, 200, 200);
                  m_crActiveCaptionTextBk = ARGB(255, 140, 200, 160);
               }
               else
               {
                  m_crCaptionTextBk = ARGB(255, 200, 200, 200);
                  m_crActiveCaptionTextBk = ARGB(255, 0x07, 0x6D, 0x91);
                  //m_penHollow1->create_solid(1.0, ARGB(20, 50, 100, 200));
                  //m_penHollow2->create_solid(1.0, ARGB(60, 50, 100, 200));
                  //m_penHollow3->create_solid(1.0, ARGB(100, 50, 100, 200));
                  //m_penHollow4->create_solid(1.0, ARGB(140, 50, 100, 200));
                  //m_penHollow5->create_solid(1.0, ARGB(255, 50, 100, 200));
               }

               if (m_spcontrolbox.is_set())
               {

                  m_spcontrolbox->m_brushButtonBackSel = m_spcontrolbox->m_brushButtonBack;
                  m_spcontrolbox->m_penButtonBackSel = m_spcontrolbox->m_penButtonBack;
                  m_spcontrolbox->m_crButtonForeSel = m_spcontrolbox->m_crButtonFore;

               }

            }


            COLORREF FrameSchemaHardCoded008::get_border_main_body_color()
            {

               if (m_estyle == StyleRedOrange)
               {

                  return ARGB(255, 255, 170, 136);

               }
               else
               {

                  return ARGB(255, 50, 100, 200);

               }

            }


            bool FrameSchemaHardCoded008::get_color(COLORREF & cr, ::user::e_color ecolor, ::user::interaction * pui)
            {

               if (m_estyle == StyleLightGreen)
               {

                  if (ecolor == ::user::color_face_lite)
                  {

                     cr = ARGB(80, 160, 160, 160);

                     return true;

                  }
                  else if (ecolor == ::user::color_text)
                  {

                     cr = ARGB(200, 80, 80, 80);

                     return true;

                  }
                  else if (ecolor == ::user::color_text_hover)
                  {

                     cr = ARGB(200, 80, 80, 80);

                     return true;

                  }
                  else if (ecolor == ::user::color_text_highlight)
                  {

                     cr = ARGB(200, 80, 80, 80);

                     return true;

                  }
                  else if (ecolor == ::user::color_background_hover)
                  {

                     cr = ARGB(20, 0, 0, 0);

                     return true;

                  }

                  return ::user::wndfrm::frame::frame::get_color(cr, ecolor, pui);

               }
               else // if (m_estyle != StyleLightGreen)
               {

                  if (ecolor == ::user::color_background)
                  {

                     cr = ARGB(255, 255, 255, 255);

                     return true;

                  }
                  else if (ecolor == ::user::color_list_background)
                  {

                     cr = ARGB(255, 255, 255, 255);

                     return true;

                  }
                  else if (ecolor == ::user::color_edit_background)
                  {

                     cr = ARGB(255, 255, 255, 255);

                     return true;

                  }
                  else if (ecolor == ::user::color_tree_background)
                  {

                     cr = ARGB(255, 255, 255, 255);

                     return true;

                  }
                  else if (ecolor == ::user::color_view_background)
                  {

                     cr = ARGB(255, 255, 255, 255);

                     return true;

                  }
                  else if (ecolor == ::user::color_scrollbar_background)
                  {

                     cr = ARGB(255, 255, 255, 255);

                     return true;

                  }
                  else if (ecolor == ::user::color_tab_layout_background)
                  {

                     cr = ARGB(255, 255, 255, 255);

                     return true;

                  }
                  else if (ecolor == ::user::color_tab_client_background)
                  {

                     cr = ARGB(255, 0xF3, 0XF5, 0xF5);

                     return true;

                  }
                  else if (ecolor == ::user::color_split_layout_background)
                  {

                     cr = ARGB(255, 255, 255, 255);

                     return true;

                  }
                  else if (ecolor == ::user::color_background_selected)
                  {

                     cr = ARGB(255, 155, 185, 255);

                     return true;

                  }
                  else if (ecolor == ::user::color_list_header)
                  {

                     cr = ARGB(255, 255, 255, 255);

                     return true;

                  }
                  else if (ecolor == ::user::color_list_header_background)
                  {

                     cr = ARGB(255, 0x58, 0x5C, 0x5D);

                     return true;

                  }
                  else if (ecolor == ::user::color_list_item_background)
                  {

                     cr = ARGB(30, 0, 0, 0);

                     return true;

                  }
                  else if (ecolor == ::user::color_list_header_separator)
                  {

                     cr = 0;

                     return true;

                  }
                  else if (ecolor == ::user::color_toolbar_background)
                  {

                     cr = ARGB(255, 0xF3, 0XF5, 0xF5);

                     return true;


                  }
                  else if (ecolor == ::user::color_button_background_disabled)
                  {

                     cr = ARGB(255, 128, 128, 128);

                     return true;


                  }
                  else if (ecolor == ::user::color_button_background_hover)
                  {

                     if (m_estyle == StyleDarkRed)
                     {
                        cr = ARGB(255, 205, 72, 72);
                     }
                     else
                     {
                        cr = ARGB(255, 0x55, 0x99, 0xC2);

                     }

                     return true;

                  }
                  else if (ecolor == ::user::color_button_background)
                  {

                     if (m_estyle == StyleDarkRed)
                     {
                        cr = ARGB(255, 165, 32, 32);
                     }
                     else
                     {
                        cr = ARGB(255, 0x30, 0x75, 0xA0);
                     }


                     return true;
                  }
                  else if (ecolor == ::user::color_button_background_press)
                  {

                     cr = ARGB(255, 0x07, 0x6D, 0x91);

                     return true;
                  }
                  else if (ecolor == ::user::color_button_text_disabled)
                  {

                     cr = ARGB(255, 0x80, 0x80, 0x80);

                     return true;

                  }
                  else if (ecolor == ::user::color_button_text_hover)
                  {

                     cr = ARGB(255, 255, 255, 255);

                     return true;

                  }
                  else if (ecolor == ::user::color_button_text)
                  {

                     cr = ARGB(255, 255, 255, 255);

                     return true;

                  }
                  else if (ecolor == ::user::color_button_text_press)
                  {

                     cr = ARGB(255, 255, 255, 255);

                     return true;

                  }

               }

               return false;

               //               return m_mapColor.Lookup(ecolor, cr);

            }


         } // namespace wndfrm_tranquillum


      } // namespace frame


   } // namespace wndfrm


} // namespace user




















































