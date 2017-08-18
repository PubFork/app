#pragma once


namespace user
{

   
   class CLASS_DECL_CORE menu_button :
      virtual public button
   {
   public:
      
      
      
      menu_button(::aura::application * papp);
      virtual ~menu_button();

      virtual void install_message_handling(::message::dispatch * pinterface);

      virtual void on_layout();

      virtual void _001DrawCheck(::draw2d::graphics * pgraphics);

      virtual void _001OnNcDraw(::draw2d::graphics * pgraphics);

      virtual void _001OnDraw(::draw2d::graphics * pgraphics);

      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnMouseMove);


   };


} // namespace user







