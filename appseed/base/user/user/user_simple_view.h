#pragma once


namespace user
{


   class CLASS_DECL_BASE simple_view :
      virtual public ::user::impact
   {
   public:

      class text
      {
      public:


         string               m_strText;
         ::draw2d::font_sp    m_font;
         point                m_point;
         ::color              m_color;


      };


      array < text >       m_texta;


      simple_view(::aura::application * papp);
      virtual ~simple_view();


      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;

      void install_message_routing(::message::sender * pinterface);

      void on_update(::user::impact * pSender, LPARAM lHint, ::object * phint);

      virtual void _001OnDraw(::draw2d::graphics * pgraphics);


   };



} // namespace user




