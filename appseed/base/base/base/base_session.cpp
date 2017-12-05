#include "framework.h" // from "axis/user/user.h"
#include "base/user/user.h"
//#include "base/user/common_user.h"


namespace base
{


   session::session(::aura::application * papp) :
      object(papp),
      ::thread(papp),
      ::aura::session(papp),
      axis::session(papp)
   {

      m_pbasesession = this;

      m_bMatterFromHttpCache = m_pbasesystem->m_bMatterFromHttpCache;

      m_bSystemSynchronizedCursor = m_pbasesystem->m_bSystemSynchronizedCursor;

      m_bSystemSynchronizedScreen = m_pbasesystem->m_bSystemSynchronizedScreen;

      m_iMainMonitor = -1;

      m_puiCapture = NULL;

#ifdef WINDOWS

      if (m_hinstance == NULL)
      {

         m_hinstance = m_pauraapp->m_hinstance;

      }

#endif




      m_puiMouseMoveCapture = NULL;

      m_puiLastLButtonDown = NULL;


      m_ecursorDefault = ::visual::cursor_arrow;

      m_ecursor = ::visual::cursor_default;

      m_puiMouseMoveCapture = NULL;

      m_puiLastLButtonDown = NULL;

      m_psavings = canew(class ::aura::savings(this));

      m_bZipIsDir = true;

      m_pmapKeyPressed = NULL;

      m_puserstrcontext = NULL;

      //m_paxissystem->m_basesessionptra.add_unique(this);

      m_puserstyle = NULL;

      //m_puserstyle           = NULL;

      m_pcopydesk = NULL;
   }



   //void session::construct(::aura::application * papp, int iPhase)
   //{

   //   ::axis::session::construct(papp,iPhase);
   //}

   session::~session_parent
   {


   }



   bool session::process_init()
   {

      thisstart;

      if (!::axis::session::process_init())
      {

         thisfail << 2;

         return false;

      }

      if (!::base::application::process_init())
      {

         thisfail << 3;

         return false;

      }

      m_puser = create_user();

      if (m_puser == NULL)
      {

         thisfail << 4;

         return false;

      }

      m_puser->add_ref();

      m_puser->construct(this);


      return true;

   }


   bool session::init1()
   {


      if (!::axis::session::init1())
         return false;

      if (!::base::application::init1())
         return false;

      //if (m_puserstyle.is_null())
      //{
      //
      //   defer_create_user_style(preferred_userschema());
      //
      //}

      if (!m_puser->init1())
         return false;

      if (!m_puser->init2())
         return false;


      return true;

   }


   bool session::init()
   {

      if (!::axis::session::init())
      {

         return false;

      }

      if (!::base::application::init())
      {

         return false;

      }

      if (!m_puser->init())
      {

         return false;

      }

      ::set_simple_message_box(&::simple_ui_message_box);

      return true;

   }


   void session::term_application()
   {

      try
      {

         for (auto & pair : System.m_appmap)
         {

            try
            {

               if (pair.m_element2->m_pbasesession == this)
               {

                  pair.m_element2->m_pbasesession = NULL;

               }

            }
            catch (...)
            {

            }

         }

      }
      catch (...)
      {

      }

      ::base::application::term_application();

      ::axis::session::term_application();

      try
      {

         m_puser->term();

      }
      catch (...)
      {

      }

      ::release(m_puser);

   }




   bool session::prepare_menu_button(::user::menu_item * pitem)
   {

      sp(::user::button) pbutton = pitem->m_pui;

      if (pbutton->m_id == "close")
      {

         pbutton->set_user_schema(::user::schema_menu_close);

         pbutton->resize_to_fit();

         pbutton->set_stock_icon(stock_icon_close);

         return true;

      }
      else
      {

         pbutton->set_user_schema(::user::schema_menu_button);

         int cx = pbutton->width();

         int cy = pbutton->height();

         pbutton->m_pmenuitem = pitem;

         rect rectMargin = pbutton->_001GetRect(::user::rect_menu_margin);

         int iCheckBoxSize = pbutton->_001GetInt(::user::int_check_box_size);

         int iElementPadding = pbutton->_001GetInt(::user::int_element_padding);

         auto & rectCheckBox = pbutton->m_rectCheckBox;

         rectCheckBox.left = rectMargin.left;
         rectCheckBox.top = rectMargin.top;
         rectCheckBox.bottom = cy - rectMargin.bottom;
         rectCheckBox.right = rectCheckBox.left + iCheckBoxSize;

         auto & rectText = pbutton->m_rectText;

         rectText.left = rectCheckBox.right + iElementPadding;
         rectText.top = rectMargin.top;
         rectText.bottom = cy - rectMargin.bottom;
         rectText.right = cx - rectMargin.right;

      }

      return true;

   }

   void session::frame_pre_translate_message(::message::message * pobj)
   {

      try
      {

         sp(::user::interaction) pui;

         while (get_frame(pui))
         {

            try
            {

               if (pui != NULL)
               {

                  pui->pre_translate_message(pobj);

                  if (pobj->m_bRet)
                     return;

               }

            }
            catch (exit_exception * pexception)
            {

               _rethrow(pexception);

            }
            catch (::exception::exception * pexception)
            {

               esp671 esp(pexception);

            }
            catch (...)
            {
            }

         }

      }
      catch (exit_exception * pexception)
      {

         _rethrow(pexception);

      }
      catch (::exception::exception * pexception)
      {

         esp671 esp(pexception);

      }
      catch (...)
      {

         pobj->m_bRet = true;

      }

   }




   string session::fontopus_get_cred(::aura::application * papp, const string & strRequestUrlParam, const RECT & rect, string & strUsername, string & strPassword, string strToken, string strTitle, bool bInteractive, ::user::interactive * pinteractive)
   {

      string str = ::axis::session::fontopus_get_cred(papp, strRequestUrlParam, rect, strUsername, strPassword, strToken, strTitle, bInteractive, pinteractive);

      if (str == "ok")
         return "ok";

      if (!bInteractive)
         return "failed";

      sp(::fontopus::dialog) pdialog;

      string strRequestUrl(strRequestUrlParam);

      if (strRequestUrl.is_empty())
      {

         string strIgnitionServer = file_as_string_dup(::dir::system() / "config\\system\\ignition_server.txt");

         if (::str::ends_ci(strIgnitionServer, ".ca2.cc"))
         {

            strRequestUrl = "https://" + strIgnitionServer + "/";

         }
         else
         {

            strRequestUrl = "https://account.ca2.cc/";

         }

      }

      pdialog = canew(::fontopus::dialog(papp, strRequestUrl));

      pdialog->m_login.m_peditUser->set_window_text(strUsername);

      pdialog->m_login.m_ppassword->set_window_text("");

      string strResult = pdialog->get_cred(rect, strUsername, strPassword, strToken, strTitle);

      pdialog->DestroyWindow();

      return strResult;

   }




   sp(::user::impact) session::get_view()
   {

      return NULL;


   }


   void session::_001OnDefaultTabPaneDrawTitle(::user::tab_pane & pane, ::user::tab * ptab, ::draw2d::graphics * pgraphics, LPCRECT lpcrect, ::draw2d::brush_sp & brushText)
   {

      _throw(interface_only_exception(this));

   }


   ::user::interaction * session::create_menu_button(::aura::application * papp)
   {

      return canew(::user::button(get_app()));

   }
   void session::on_finally_focus_set(::user::elemental * pelementalFocus)
   {

      user()->set_mouse_focus_LButtonDown(pelementalFocus);


   }


   bool session::on_ui_mouse_message(::user::mouse * pmouse)
   {


      ::axis::session::on_ui_mouse_message(pmouse);




      // user presence status activity reporting
      if (pmouse->get_message() == WM_LBUTTONDOWN
            || pmouse->get_message() == WM_RBUTTONDOWN
            || pmouse->get_message() == WM_MBUTTONDOWN
            || pmouse->get_message() == WM_MOUSEMOVE)
      {

         if (fontopus() != NULL && fontopus()->m_puser != NULL)
         {

            if (ApplicationUser.m_ppresence != NULL)
            {

               try
               {

                  ApplicationUser.m_ppresence->report_activity();

               }
               catch (...)
               {

               }

            }

         }

      }

      return true;

   }


} // namespace base


