#pragma once


namespace visual
{


   class CLASS_DECL_AURA font_list :
      virtual public ::object
   {
   public:

      enum e_layout
      {

         layout_wide,
         layout_single_column,

      };


      class CLASS_DECL_AURA text_box
      {
      public:

         ::draw2d::dib_sp     m_dib;
         ::draw2d::font_sp    m_font;
         rect                 m_rect;
         bool                 m_bOk;
         size                 m_size;

         text_box();
         ~text_box();


         void update(font_list * pdata, int iBox, string strText);


      };


      class CLASS_DECL_AURA item :
         virtual public simple_object
      {
      public:

         text_box             m_box[3];
         string               m_strName;
         string               m_strFont;
         string               m_strSample;

         item();
         virtual ~item();

      };


      class CLASS_DECL_AURA layout :
         virtual public spa(item),
         virtual public ::user::style
      {
      public:

         int            m_iUpdate;
         e_layout       m_elayout;
         point          m_pt;
         ::size         m_size;


         layout();
         virtual ~layout();


      };


      int                                       m_iUpdate;
      sp(::visual::font_enumeration)            m_pfontenumeration;
      ::draw2d::font::enum_item_array           m_itema;

      string                                    m_strText;
      string                                    m_strTextLayout;

      rect                                      m_rectLayout;
      rect                                      m_rectClient;
      rect                                      m_rectMargin;
      index                                     m_iSel;
      index                                     m_iHover;

      uint32_array                              m_dwaBg;
      uint32_array                              m_dwaFg;
      int                                       m_iUpdated;
      pointer_array < ::user::interaction * >   m_uiptra;


      font_list(::aura::application * papp);
      virtual ~font_list();


      virtual void update();

      virtual index find_name(string str, layout * playout);

      virtual index hit_test(point pt, layout * playout);
      virtual index hit_test_wide(point pt, layout * playout);
      virtual index hit_test_single_column(point pt, layout * playout);

      virtual void _001OnDraw(::draw2d::graphics * pgraphics, layout * playout);
      virtual void _001OnDrawWide(::draw2d::graphics * pgraphics, layout * playout);
      virtual void _001OnDrawSingleColumn(::draw2d::graphics * pgraphics, layout * playout);

      virtual bool on_layout(layout * playout);
      virtual bool on_layout_wide(layout * playout);
      virtual bool on_layout_single_column(layout * playout);

      virtual void defer_update_layout(layout * playout);

   };


} // namespace visual





