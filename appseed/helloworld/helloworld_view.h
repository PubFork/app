#pragma once


namespace helloworld
{


   class CLASS_DECL_APP_HELLOWORLD view :
      virtual public hellobase::view,
      virtual public hellobase::view_base
   {
   public:




      string                  m_strServer;
      ::visual::dib_sp        m_dibAi1;
      ::visual::dib_sp        m_dibAi2;

      string                  m_strImage;
      ::draw2d::dib_sp        m_dibColor;

      bool                    m_bOkPending;


      bool                    m_bHelloLayoutOn001Layout;
      bool                    m_b001LayoutIgnoreEmpty;


      view(::aura::application * papp);
      virtual ~view();

      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;

      virtual int64_t add_ref()
      {
         return ::object::add_ref();
      }
      virtual int64_t dec_ref()
      {
         return ::object::dec_ref();
      }

      virtual void install_message_routing(::message::sender * psender);

      virtual void _001OnHelloDraw(::draw2d::graphics * pgraphics);

      virtual void on_update(::user::impact * pSender, LPARAM lHint, object* pHint);

      ::user::document * get_document();



      virtual void on_layout();

      DECL_GEN_SIGNAL(_001OnLayout);
      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnDestroy);

      virtual string get_helloworld();

      virtual string get_processed_helloworld();



      virtual void defer_check_on_draw_layout();
      virtual void on_draw_image_layer(::draw2d::graphics * pgraphics);

   };


} // namespace helloworld





















