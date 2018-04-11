#pragma once


namespace user
{


   namespace wndfrm
   {


      namespace frame
      {


         namespace wndfrm_tranquillum
         {


            class CLASS_DECL_APP_WNDFRM_TRANQUILLUM FrameSchemaHardCoded008 :
               public frame_schema
            {
            public:

               
               bool     m_bHollow;


               FrameSchemaHardCoded008(::aura::application * papp);
               virtual ~FrameSchemaHardCoded008();


               virtual void on_style_change() override;

               void on_draw_frame(::draw2d::graphics * pgraphics) override;
               void DrawBorder(::draw2d::graphics * pgraphics, const RECT & lpcrectClient);
               void DrawBorderSide(::draw2d::graphics * pgraphics, const RECT & lpcrectClient, EBorder eside);
               void GetBorderRect(const RECT & lpcrectClient, LPRECT lprect, EBorder eside);

               virtual EHitTest _000HitTest(point pt) override;
               COLORREF get_border_main_body_color() override;

               virtual bool get_color(COLORREF & cr, ::user::e_color ecolor, ::user::interaction * pui) override;


            };


         } // namespace wndfrm_tranquillum


      } // namespace frame


   } // namespace wndfrm


} // namespace user






