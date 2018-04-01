#pragma once


namespace install
{


   class CLASS_DECL_AURA window :
      virtual public ::user::interaction
   {
   public:



      int                           m_iHealingSurface;
      double                        m_dAnime;
      double                        m_dPi;
      bool                          m_bDrag;
      POINT                         m_ptDragStart;
      RECT                          m_rectWindowDragStart;

      ::draw2d::font_sp             m_font;
      ::draw2d::font_sp             m_fontBold;
      ::draw2d::font_sp             m_fontHeader;
      ::draw2d::pen_sp              m_penBorder;
      ::draw2d::brush_sp            m_brushText;
      ::draw2d::brush_sp            m_brushBar;
      ::draw2d::brush_sp            m_brushBarBk;
      ::draw2d::pen_sp              m_penBarBorder;
      ::draw2d::brush_sp            m_brushBk;
      string                        m_strLastStatus;
      bool                          m_bDraw;

      bool                          m_bRunMainLoop;

      static window *               s_p;


      window(::aura::application * papp);
      virtual ~window();


      virtual bool create();

      //virtual void draw();

      virtual void drag();

      virtual void on_resize(int cx, int cy);

      virtual void layout() override;

      virtual void _001OnDraw(::draw2d::graphics * pgraphics) override;

      virtual void draw_install(::draw2d::graphics * pgraphics);

      virtual bool has_pending_graphical_update() override;

      //LRESULT message_handler(UINT message, WPARAM wParam, LPARAM lParam);

//#ifdef WINDOWS
//
//      static LRESULT CALLBACK window_procedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
//
//#endif

      //virtual ATOM register_class();

      virtual void main();

   };


} // namespace install



