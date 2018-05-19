#pragma once


namespace user
{


   class CLASS_DECL_AURA menu_interaction :
      virtual public interaction
   {
   public:


      menu_item *             m_pitem;


      menu_interaction(menu_item * pitem);
      virtual ~menu_interaction();

      virtual void install_message_routing(::message::sender * pinterface);

      virtual void on_layout();

      virtual void _001DrawCheck(::draw2d::graphics * pgraphics);

      virtual void _001OnNcDraw(::draw2d::graphics * pgraphics);

      virtual void _001OnDraw(::draw2d::graphics * pgraphics);

      virtual void _001OnDrawDefault(::draw2d::graphics * pgraphics);

      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnMouseMove);


      virtual void on_calc_size(calc_size * psize) override;


   };


} // namespace user







