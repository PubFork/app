#pragma once


namespace metrowin
{

   class directx_interaction :
      public ::user::interaction
   {
   public:

      directx_interaction(::aura::application * papp);
      virtual ~directx_interaction();

      virtual void _001DrawThis(::draw2d::graphics * pgraphics) override;
      virtual void _001DrawChildren(::draw2d::graphics * pgraphics) override;
      virtual void _000OnDraw(::draw2d::graphics * pgraphics) override;
      virtual void _001OnNcDraw(::draw2d::graphics * pgraphics) override;
      virtual void _001OnDraw(::draw2d::graphics * pgraphics) override;

   };

   ref class directx_application :
      public Windows::ApplicationModel::Core::IFrameworkView,
      public ::aura::system_window
   {
   internal:


      ::user::interaction_impl * m_pimpl;

      Windows::Foundation::Point                m_ptLastCursor;

      DWORD                                     m_dwMouseMoveThrottle;

      DWORD                                     m_dwLastMouseMove;

      String ^                                  m_strId;

      Agile < Windows::UI::Core::CoreWindow >   m_window;

      directx_base ^                            m_directx;

      bool                                      m_bFontopusShift;

      mutex                                     m_mutex;

      ::aura::system *                          m_psystem;

      ::aura::application *                     m_papp;

      directx_interaction *                     m_pdxi;

      bool                                      m_bLeftButton;

      bool                                      m_bMiddleButton;

      bool                                      m_bRightButton;

      Windows::Foundation::Rect                 m_rectLastWindowRect;


      directx_application(::aura::system * psystem,String ^ strId);

      void init_part_2ex();

      void install_message_routing_2ex();

      ::aura::application * get_app() const;


   public:

      // IFrameworkView Methods
      virtual void Initialize(_In_ Windows::ApplicationModel::Core::CoreApplicationView^ applicationView);
      virtual void SetWindow(_In_ Windows::UI::Core::CoreWindow^ window);
      virtual void Load(_In_ String^ entryPoint);
      virtual void Run();
      virtual void Uninitialize();
      virtual Windows::Foundation::Rect get_window_rect();
      virtual Windows::Foundation::Point get_cursor_pos();

      virtual ~directx_application();

   private:
      // Event Handlers
      void OnWindowSizeChanged(
      _In_ Windows::UI::Core::CoreWindow^ sender,
      _In_ Windows::UI::Core::WindowSizeChangedEventArgs^ args
      );

      void DpiChanged(::Windows::Graphics::Display::DisplayInformation ^ sender, Object ^ obj);

      void DisplayContentsInvalidated(::Windows::Graphics::Display::DisplayInformation ^ sender, Object ^ obj);

      void OnActivated(
      _In_ Windows::ApplicationModel::Core::CoreApplicationView^ applicationView,
      _In_ Windows::ApplicationModel::Activation::IActivatedEventArgs^ args
      );

      void OnSuspending(
      _In_ Object^ sender,
      _In_ Windows::ApplicationModel::SuspendingEventArgs^ args
      );

      void OnResuming(
      _In_ Object^ sender,
      _In_ Object^ args
      );

      void OnPointerMoved(Windows::UI::Core::CoreWindow^, Windows::UI::Core::PointerEventArgs^ args);

      void OnCharacterReceived(Windows::UI::Core::CoreWindow^, Windows::UI::Core::CharacterReceivedEventArgs^ args);
      void OnKeyDown(Windows::UI::Core::CoreWindow^, Windows::UI::Core::KeyEventArgs^ args);
      void OnKeyUp(Windows::UI::Core::CoreWindow^, Windows::UI::Core::KeyEventArgs^ args);
      void OnPointerPressed(Windows::UI::Core::CoreWindow^, Windows::UI::Core::PointerEventArgs^ args);
      void OnPointerReleased(Windows::UI::Core::CoreWindow^, Windows::UI::Core::PointerEventArgs^ args);


      //Microsoft::WRL::ComPtr<ID2D1SolidColorBrush>                    m_blackBrush;
      //Microsoft::WRL::ComPtr<IDWriteTextFormat>                       m_textFormat;
      //Microsoft::WRL::ComPtr<IDWriteTypography>                       m_textTypography;
      //Microsoft::WRL::ComPtr<IDWriteTextLayout>                       m_textLayout;
      //SampleOverlay^                                                  m_sampleOverlay;

   };


   ref class directx_application_source :
      Windows::ApplicationModel::Core::IFrameworkViewSource
   {
   internal:

      ::aura::system * m_paurasystem;

      string m_strId;

      directx_application_source(::aura::system * paxissystem,const string & strId);

   public:

      virtual Windows::ApplicationModel::Core::IFrameworkView ^ CreateView();

   };


   CLASS_DECL_AURA directx_application_source ^ new_directx_application_source(::aura::system * psystem, const string & str);


} // namespace metrowin



