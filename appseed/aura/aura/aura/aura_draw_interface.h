#pragma once


namespace aura
{

   class CLASS_DECL_AURA drawable:
      virtual public ::object
   {
   public:


      virtual void _001OnDraw(::draw2d::graphics * pgraphics);

   };

   class CLASS_DECL_AURA draw_interface :
      virtual public drawable
   {
   public:


      virtual void _000OnDraw(::draw2d::graphics * pgraphics);

      virtual void _001DeferPaintLayeredWindowBackground(::draw2d::graphics * pgraphics);

      virtual void _001OnDeferPaintLayeredWindowBackground(::draw2d::graphics * pgraphics);

      virtual bool GetWindowRect(LPRECT lprect);
      virtual bool GetWindowRect(RECT64 * lprect);
      virtual rect GetWindowRect();
      virtual rect64 GetWindowRect64();


      virtual ::window_graphics * get_window_graphics();
      virtual oswindow get_handle() const;

      virtual bool is_composite();


   };


} // namespace aura


