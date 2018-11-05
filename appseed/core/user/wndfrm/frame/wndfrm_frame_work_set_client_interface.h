#pragma once


namespace user
{


   namespace wndfrm
   {


      namespace frame
      {


         class CLASS_DECL_CORE WorkSetClientInterface :
            virtual public WorkSetUpDownInterface,
            virtual public ::user::box
         {
            public:


               WorkSet                    m_workset;
               ::user::e_appearance        m_eappearanceBefore;
               int32_t                    m_iIndex;
               bool                       m_bFullScreenOnZoom;
               bool                       m_bInitialFramePosition;



               //CWorkSetDownUpInterface();



               WorkSetClientInterface();
               virtual ~WorkSetClientInterface();


               sp(::user::interaction) WfiGetWindow();


               virtual void _001OnDraw(::draw2d::graphics * pgraphics);


               virtual void WfiEnableFullScreen(bool bEnable = true);
               virtual bool WfiIsFullScreen();
               virtual bool WfiIsFullScreenEnabled();


               virtual bool Wfi(e_appearance eappearance = appearance_current);

               virtual bool WfiDock(e_appearance eappearance);
               virtual bool WfiClose();
               virtual bool WfiRestore(bool bForceNormal = false);
               virtual bool WfiMinimize(bool bNoActivate = false);
               virtual bool WfiMaximize();
               virtual bool WfiFullScreen();
               virtual bool WfiUp();
               virtual bool WfiDown();
               virtual bool WfiToggleTransparentFrame();
               virtual bool WfiNotifyIcon();


               virtual bool WfiOnBeginSizing(UINT nType, point pt);
               virtual bool WfiOnBeginMoving(point pt);
               virtual bool WfiOnSize(bool bTracking);
               virtual bool WfiOnMove(bool bTracking);

               virtual bool WfiOnStartDock();
               virtual void WfiOnDock(e_appearance eapperance);
               virtual void WfiOnDown();
               virtual void WfiOnUp();
               virtual void WfiOnRestore();
               virtual void WfiOnMinimize(bool bNoActivate);
               virtual void WfiOnMaximize();
               virtual void WfiOnFullScreen();
               virtual void WfiOnExitFullScreen();
               virtual void WfiOnClose();
               virtual void WfiOnNotifyIcon();
               virtual bool WfiOnBeforeDock(e_appearance eapperance);
               virtual bool WfiOnBeforeDown();
               virtual bool WfiOnBeforeUp();
               virtual bool WfiOnBeforeRestore();
               virtual bool WfiOnBeforeMinimize();
               virtual bool WfiOnBeforeMaximize();
               virtual bool WfiOnBeforeClose();
               virtual bool WfiOnBeforeFullScreen();
               virtual bool WfiOnBeforeNotifyIcon();
               virtual void WfiOnAfterDock(e_appearance eapperance);
               virtual void WfiOnAfterDown();
               virtual void WfiOnAfterUp();
               virtual void WfiOnAfterRestore();
               virtual void WfiOnAfterMinimize();
               virtual void WfiOnAfterMaximize();
               virtual void WfiOnAfterClose();
               virtual void WfiOnAfterFullScreen();
               virtual void WfiOnAfterNotifyIcon();




               virtual bool WndFrameworkDownUpGetUpEnable() = 0;
               virtual bool WndFrameworkDownUpGetDownEnable() = 0;

               virtual void frame_Attach();
               virtual void frame_Detach();


               virtual void _001OnTimer(::timer * ptimer);


         };


      } // namespace frame


   } // namespace wndfrm


} // namespace user








