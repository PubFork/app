#pragma once


namespace helloworld
{


   class CLASS_DECL_APP_HELLOWORLD view_base :
      virtual public ::hellobase::view_base
   {
   public:

      enum e_effect
      {

         effect_none,
         effect_crt,

      };


      int                     m_yDrawStatus;
      ::draw2d::font_sp       m_fontDrawStatus;
      COLORREF                m_crDrawStatus;

      double                  m_dFps;
      DWORD                   m_dwRoll;

      string                  m_strHoverFont;
      string                  m_strNewFont;
      string                  m_strFont;
      e_effect                m_eeffect;


      mutex                   m_mutexText;
      string                  m_strNewHelloWorld;
      string                  m_strHelloWorld;


      ::draw2d::dib_sp        m_dibPost;
      ::visual::dib_sp        m_dibTime;

      ::draw2d::dib_sp        m_dib1;
      ::draw2d::dib_sp        m_dib2;

      render *                m_prender;


      uint32_array            m_dwaFrame;



      view_base(::aura::application * papp);
      virtual ~view_base();

      virtual int64_t add_ref()
      {
         return ::object::add_ref();
      }
      virtual int64_t dec_ref()
      {
         return ::object::dec_ref();
      }


      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;


      virtual void install_message_routing(::message::sender * psender);

      virtual void _001OnPostProcess(::draw2d::graphics * pgraphics);
      virtual void _001OnHelloDraw(::draw2d::graphics * pgraphics);
      virtual void _001OnNcDraw(::draw2d::graphics * pgraphics);
      virtual void _001OnDraw(::draw2d::graphics * pgraphics);
      virtual void on_draw_image_layer(::draw2d::graphics * pgraphics);

      virtual void defer_check_on_draw_layout();

      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnDestroy);


   };


} // namespace helloworld





















