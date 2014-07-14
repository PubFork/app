#include "framework.h"


namespace hotplugin
{


   composer::composer()
   {

      m_estatus               = status_start_system;
      m_bSystemOk             = false;
      m_bTryInitHost          = false;
      m_bHostOk               = false;
      m_bTryInitWindow        = false;
      m_bWindowOk             = false;
      m_bOk                   = false;
      m_bResponsive           = true;
      m_bWrite                = false;

   }
   
   
   composer::~composer()
   {

   }


   void composer::hotplugin_composer_on_timer()
   {

      if(m_estatus == status_start_system)
      {

         if(m_bSystemOk)
         {

            m_estatus = status_start_host;

         }
         else
         {

            if(::hotplugin::get_base_system() == NULL)
            {

               ::hotplugin::start_base_system();

            }
            else
            {


               if(::hotplugin::get_base_system()->m_bReady)
               {

                  if(::hotplugin::get_base_system()->m_iReturnCode != 0)
                  {

                     string str;
                     
                     str.Format("::hotplugin::g_pbasesystem initialization error %d",::hotplugin::get_base_system()->m_iReturnCode);

                     ::OutputDebugString(str);

                  }
                  else
                  {

                     m_bSystemOk = true;

                  }

               }

            }


         }


      }
      else if(m_estatus == status_start_host)
      {

         if(m_bHostOk)
         {

            m_estatus = status_init_host;

         }
         else
         {

            if(m_pbasehost == NULL)
            {

               m_pbasehost = create_host(::hotplugin::get_base_system());

               m_pbasehost->m_pbasecomposer = this;

               m_pbasehost->hotplugin_host_begin();

            }
            else
            {

               if(m_pbasehost->m_bReady)
               {

                  if(m_pbasehost->m_iReturnCode != 0)
                  {

                     string str;

                     str.Format("::hotplugin::composer::m_pbasehost initialization error %d",::hotplugin::get_base_system()->m_iReturnCode);

                     ::OutputDebugString(str);

                  }
                  else
                  {

                     m_bHostOk = true;

                  }

               }

            }

         }

      }
      else if(m_estatus == status_init_host)
      {

         if(m_bHostInit)
         {

            m_estatus = status_start_window;

         }
         else if(!m_bTryInitHost)
         {

            m_bTryInitHost = true;

            if(!m_pbasehost->hotplugin_host_is_initialized())
            {

               if(m_pbasehost->hotplugin_host_initialize())
               {

                  m_bHostInit = true;

               }

            }

         }

      }
      else if(m_estatus == status_start_window)
      {

         if(m_bWindowOk)
         {

            m_estatus = status_ok;

         }
         else if(!m_bTryInitWindow)
         {

            m_bTryInitWindow = true;

            if(on_composer_init_window())
            {
               
               m_bWindowOk = true;

            }

         }

      }
      else if(m_estatus == status_ok)
      {

         if(!m_bOk)
         {

            m_bOk = true;

         }
      }


      if(m_pbasehost != NULL && m_pbasehost->hotplugin_host_is_initialized())
      {

         if(m_bWrite)
         {

            m_bWrite = false;

            m_pbasehost->hotplugin_host_on_write(); // at least m_strPluginUrl is ready

         }

      }


      if(m_bOpenUrl)
      {

         m_bOpenUrl = false;

         if(!_open_url(m_strOpenUrl))
         {

            m_bOpenUrl = true;

         }

      }

   }


   bool composer::on_composer_init_window()
   {

      return true;

   }


   bool composer::open_url(const char * pszUrl)
   {

      m_strOpenUrl = pszUrl;

      m_bOpenUrl = true;

      return true;

   }


   bool composer::_open_url(const char * pszUrl)
   {

      return true;

   }


   // if composer on paint returns (returns true), it has painted something meaningful : no other painting is needed or even desired (finally when system, and host are ok, 
   // if host returns in a fashion-timed way the response for bitmap, it draw this bitmap, and not the default waiting [hall] screen painted by this composer).

#ifdef WINDOWS

   bool composer::windows_on_paint(HDC hdc)
   {

      if((!m_bOk || !m_bResponsive) || m_pbasehost == NULL || !m_pbasehost->hotplugin_host_is_initialized())
      {

         ::hotplugin::entry_hall_windows_on_paint(hdc,m_rect);

         return true;

      }
      else 
      {

         m_pbasehost->m_bOnPaint = true;

         ::draw2d::graphics_sp g(m_pbasehost->allocer());

         g->Attach((HDC)hdc);

         ::rect rect;

         m_pbasehost->GetWindowRect(rect);

         m_pbasehost->on_paint(g,rect);

         g->Detach();

         m_pbasehost->m_bOnPaint = false;

      }
      
      return false;


   }

#endif

   void composer::deferred_prodevian_redraw()
   {

      if(m_pbasehost != NULL && m_pbasehost->hotplugin_host_is_initialized())
      {

         m_pbasehost->deferred_prodevian_redraw();

      }

   }


} // namespace hotplugin

