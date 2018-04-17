#include "framework.h"
#include "aura/aura/os/windows/windows_system_interaction_impl.h"


#ifdef MACOS

long long mm_get_user_wallpaper(long long llScreen, char ** ppp);

CLASS_DECL_CORE string macos_get_user_wallpaper(int iScreen)
{

   string str;

   char * psz = NULL;

   mm_get_user_wallpaper(iScreen, &psz);

   if(psz != NULL)
   {

      str = psz;

      free(psz);

   }

   return str;

}

#endif

namespace user
{


   CLASS_DECL_CORE sp(::user::interaction) create_virtual_window(::aura::application * papp, uint32_t dwExStyle, const char * lpClassName, const char * lpWindowName, uint32_t dwStyle,
         const RECT & rect, sp(::user::interaction) puiParent, id id, HINSTANCE hInstance, LPVOID lpParam);


   CLASS_DECL_CORE sp(::user::interaction) create_virtual_window(::aura::application * papp, uint32_t dwExStyle, const char * lpClassName, const char * lpWindowName, uint32_t dwStyle,
         const RECT & rect, sp(::user::interaction) puiParent, id id, HINSTANCE hInstance, LPVOID lpParam)
   {
      UNREFERENCED_PARAMETER(dwExStyle);
      UNREFERENCED_PARAMETER(lpClassName);
      UNREFERENCED_PARAMETER(lpWindowName);
      UNREFERENCED_PARAMETER(dwStyle);
      UNREFERENCED_PARAMETER(hInstance);
      UNREFERENCED_PARAMETER(lpParam);
      sp(::user::interaction) pui = new ::user::interaction(papp);
      if(pui->create_window(rect, puiParent, id))
      {
         return pui;
      }
      pui.release();
      return NULL;
   }




} // namespace user











namespace core
{

   void application::close(e_end eend)
   {

      close_dependent_threads(seconds(15));

      if (m_pdocmanager != NULL)
      {

         document_manager()->close_all_documents(eend != end_close);

      }

      if (eend == end_close)
      {

         return;

      }

      try
      {

         m_pdocmanager.release();

      }
      catch (...)
      {

      }

      if (m_pcoresession->m_pdocmanager != NULL)
      {

         m_pcoresession->document_manager()->close_all_documents(true);

         m_pcoresession->m_pdocmanager.release();

      }

      if (m_pcoresystem->m_pdocmanager != NULL)
      {

         m_pcoresystem->document_manager()->close_all_documents(true);

         m_pcoresystem->m_pdocmanager.release();

      }


#if !defined(LINUX) && !defined(METROWIN) && !defined(ANDROID) && !defined(APPLEOS)

      try
      {
         if (m_pcoresystem != NULL && m_pcoresystem->m_psystemwindow != NULL)
         {
            m_pcoresystem->m_psystemwindow->DestroyWindow();

         }

      }
      catch (...)
      {

         m_error.set_if_not_set(-2);

      }

      if (eend == end_app)
      {

         post_quit();

         return;

      }

      if (eend == end_session)
      {

         Session.post_quit();

         return;

      }

      try
      {

         if (m_pcoresystem != NULL)
         {
            ::aura::del(m_pcoresystem->m_psystemwindow);

         }

      }
      catch (...)
      {

         m_error.set_if_not_set(-2);

      }

#endif

      try
      {

         if (m_paurasystem != NULL)
         {

            m_paurasystem->post_quit();

         }

      }
      catch (...)
      {

      }

   }


   session_docs::session_docs()
   {

      m_pnaturedocument = NULL;
      m_pplatformdocument = NULL;
      m_pbergedgedocument = NULL;


   }


   session_docs::~session_docs()
   {

      close_all_documents();

   }


   void session_docs::close_all_documents()
   {

      if (m_pnaturedocument != NULL)
      {

         m_pnaturedocument.cast < ::user::document>()->on_close_document();

      }

      if (m_pplatformdocument != NULL)
      {

         m_pplatformdocument.cast < ::user::document>()->on_close_document();

      }

      if (m_pbergedgedocument != NULL)
      {

         m_pbergedgedocument.cast < ::user::document>()->on_close_document();

      }

   }


   session_docs * create_session_docs()
   {

      return new session_docs();

   }


   void destroy_session_docs(session_docs * pdocs)
   {

      ::aura::del(pdocs);

   }


   void session::on_app_request_bergedge_callback(::aura::application * papp)
   {

      if (&App(papp) != NULL)
      {

         Session.m_pappCurrent = papp;

      }

      if (Session.m_bShowPlatform)
      {
         //sp(::simple_frame_window) pframeApp = get_document()->get_typed_view < ::bergedge::pane_view >()->get_view_uie();
         //if(pframeApp != NULL)
         //{
         //   pframeApp->WfiFullScreen();
         //}
         //sp(::simple_frame_window) pframe = get_document()->get_typed_view < ::bergedge::pane_view >()->GetParentFrame();
         //if(pframe != NULL)
         //{
         //   pframe->ShowWindow(SW_SHOW);
         //}
      }
      else
      {
         //if(get_document() != NULL && get_document()->get_typed_view < ::bergedge::view >() != NULL)
         //{
         //   sp(::simple_frame_window) pframe = get_document()->get_typed_view < ::bergedge::view >()->GetParentFrame();
         //   if(pframe != NULL)
         //   {
         //      pframe->ShowWindow(SW_SHOW);
         //      if(pframe->GetTypedParent < ::plugin::host_interaction > () != NULL)
         //      {
         //         pframe->GetTypedParent < ::plugin::host_interaction > ()->on_layout();
         //      }
         //      else
         //      {
         //         pframe->InitialFramePosition();
         //      }
         //   }
         //}
      }

      if (Session.m_pappCurrent != NULL && Session.m_pappCurrent->m_pbasesession->m_pfontopus->m_puser != NULL)
      {
         try
         {
            get_view()->GetParentFrame()->set_window_text(Session.m_pappCurrent->m_pbasesession->m_pfontopus->m_puser->m_strLogin);
         }
         catch (...)
         {
         }
      }

   }


   sp(::user::document) session::get_document()
   {

      return m_pdocs->m_pbergedgedocument;

   }


   sp(::user::impact) session::get_view()
   {
      if (get_document() == NULL)
         return NULL;
      //      return get_document()->get_bergedge_view();
      return NULL;
   }

   sp(::user::document) session::get_platform()
   {
      return m_pdocs->m_pplatformdocument;
   }

   sp(::user::document) session::get_nature()
   {
      return m_pdocs->m_pnaturedocument;
   }

   bool session::get_monitor_rect(index iMonitor, LPRECT lprect)
   {

      if (get_document() != NULL && get_view() != NULL)
      {

         get_view()->GetWindowRect(lprect);

         return true;

      }
      else
      {

         return ::base::session::get_monitor_rect(iMonitor, lprect);

      }

   }
   sp(type) system::get_simple_frame_window_type_info()
   {

      return System.type_info < simple_frame_window >();

   }



   ::user::document_manager * application::document_manager()
   {

      return m_pdocmanager;

   }


   ::count session::get_monitor_count()
   {

      if (get_document() != NULL && get_view() != NULL)
      {

         return 1;

      }
      else
      {

         return ::base::session::get_monitor_count();

      }

   }


   ::user::interaction * session::get_request_parent_ui(::user::interaction * pinteraction, ::create * pcreate)
   {


      ::user::interaction * puiParent = NULL;

      if (pcreate->m_spCommandLine->m_varQuery["uicontainer"].cast < ::user::interaction >() != NULL)
         puiParent = pcreate->m_spCommandLine->m_varQuery["uicontainer"].cast < ::user::interaction >();

      if (puiParent == NULL && pcreate->m_puiParent != NULL)
      {
         puiParent = dynamic_cast < ::user::interaction * > (pcreate->m_puiParent);
      }

      if (puiParent == NULL && pcreate->m_spCommandLine->m_pbiasCreate != NULL)
      {
         puiParent = dynamic_cast < ::user::interaction * > (pcreate->m_spCommandLine->m_pbiasCreate->m_puiParent);
      }

      if (puiParent == NULL && pcreate->m_spApplicationBias.is_set())
      {
         puiParent = dynamic_cast < ::user::interaction * > (pcreate->m_spApplicationBias->m_puiParent);
      }


      /*      if(pui == NULL && m_puiInitialPlaceHolderContainer != NULL)
      {
      pui = m_puiInitialPlaceHolderContainer;
      }*/

      /*      if(pui == NULL && m_bShowPlatform && m_pbergedge->get_document() != NULL)
      {
      pui = Session.get_document()->get_bergedge_view();
      }

      return pui;

      }*/

      if (pcreate->m_bClientOnly ||
            Application.handler()->m_varTopicQuery.has_property("client_only") ||
            pcreate->m_bOuterPopupAlertLike)
      {
         return puiParent;
      }


      //bool bCreateBergedge = false;

      //if(bCreateBergedge)
      //{

      //   if(!create_bergedge(pcreate))
      //   {
      //      return NULL;


      //   }

      //}




      ::core::application & app = App(pinteraction->get_app());

      string strAppName = app.m_strAppName;

      if (strAppName != "bergedge")
      {

         if (get_document() != NULL)
         {

            //if(get_document()->get_typed_view < ::bergedge::pane_view >() != NULL)
            //{

            //   get_document()->get_typed_view < ::bergedge::pane_view >()->set_cur_tab_by_id("app:" + strAppName);

            //   puiParent = get_document()->get_typed_view < ::bergedge::pane_view >()->get_tab_holder(get_document()->get_typed_view < ::bergedge::pane_view >()->get_tab_by_id("app:" + strAppName));

            //}
            //else
            //{

            //   puiParent = get_document()->get_typed_view < ::bergedge::view >();

            //}

         }

      }

      return puiParent;

   }

} // namespace core


