#pragma once


namespace visual
{


   class CLASS_DECL_AURA font_list_item :
      virtual public simple_object
   {
   public:

      text_box                            m_box[3];
      string                              m_strName;
      string                              m_strFont;
      string                              m_strSample;
      ::draw2d::font::char_set_array      m_echarseta;

      font_list_item();
      virtual ~font_list_item();

   };


   class CLASS_DECL_AURA font_list :
      virtual public ::user::style
   {
   public:


      enum e_type
      {

         type_wide,
         type_single_column,

      };


      index                                     m_iLayoutId;
      sp(::visual::font_enumeration)            m_pfontenumeration;
      sp(::draw2d::font::enum_item_array)       m_pitema;


      spa(font_list_item)                       m_itema;


      uint32_array                              m_dwaBg;
      uint32_array                              m_dwaFg;
      int                                       m_iUpdated;
      pointer_array < ::user::interaction * >   m_uiptra;

      e_type                                    m_etype;
      point                                     m_pt;
      ::size                                    m_size;
      string                                    m_strText;
      string                                    m_strTextLayout;

      rect                                      m_rectLayout;
      rect                                      m_rectClient;
      rect                                      m_rectMargin;
      index                                     m_iSel;
      index                                     m_iHover;
      manual_reset_event *                      m_pevLayoutReady;
      int                                       m_iBaseSizeLayout;
      int_array                                 m_iaSizeLayout;
      bool                                      m_bOnLayout;
      sp(::thread)                              m_pthreadDelayedLayout;


      font_list(::aura::application * papp);
      virtual ~font_list();


      virtual void layout(bool bSynch);

      virtual void update();
      virtual void start_layout();
      virtual void _on_end_layout();
      virtual void on_layout();
      virtual void on_layout_wide();
      virtual void on_layout_single_column();



      virtual void _001OnDraw(::draw2d::graphics * pgraphics);
      virtual void _001OnDrawWide(::draw2d::graphics * pgraphics);
      virtual void _001OnDrawSingleColumn(::draw2d::graphics * pgraphics);

      virtual index find_name(string str);

      virtual index hit_test(point pt);
      virtual index hit_test_wide(point pt);
      virtual index hit_test_single_column(point pt);


   };


} // namespace visual





