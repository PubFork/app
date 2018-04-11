#pragma once


namespace user
{


   class CLASS_DECL_BASE progress :
      virtual public ::user::control
   {
   public:


      scalar_base * m_pscalar;

      double         m_dRate;



      progress(::aura::application * papp);
      virtual ~progress();


      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;

      void install_message_routing(::message::sender * pinterface);


      virtual void _001OnDraw(::draw2d::graphics * pgraphics);


   };



} // namespace user




