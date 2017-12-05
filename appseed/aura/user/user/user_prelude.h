#pragma once


namespace user
{

   class place_holder;

#if defined METROWIN

   class CLASS_DECL_AURA native_window_initialize
   {
   public:


      Agile<Windows::UI::Core::CoreWindow> window;
      ::aura::system_window ^ pwindow;


   };

#elif defined(APPLE_IOS) || defined(ANDROID)

   class CLASS_DECL_AURA native_window_initialize
   {
   public:

      RECT   m_rect;

   };

#else

   class native_window_initialize;

#endif


   class control_event;
   class frame_window;


   CLASS_DECL_AURA bool is_descendant(::user::interaction * puiParent, ::user::interaction * puiChild);


} // namespace user


