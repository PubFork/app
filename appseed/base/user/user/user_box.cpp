#include "framework.h"


namespace user
{


   box::box() :
      ::object(get_app())
   {

      m_strWindowRectDataAddUp = ".local://";

   }


   box::~box()
   {

   }


   void box::install_message_routing(::message::sender * pinterface)
   {

      ::simple_ui::interaction::install_message_routing(pinterface);
      scroll::install_message_routing(pinterface);

      IGUI_MSG_LINK(WM_CREATE, pinterface, this, &box::_001OnCreate);
      IGUI_MSG_LINK(WM_SIZE, pinterface, this, &box::_001OnSize);
      IGUI_MSG_LINK(WM_SHOWWINDOW, pinterface, this, &box::_001OnShowWindow);

   }


   void box::_001OnCreate(::message::message * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

      if (pobj->previous())
         return;

      set_data_server(&System.dataserver());

      if (m_id.is_empty())
      {

         m_id = typeid(*this).name();

      }

   }


   void box::_001OnSize(::message::message * pobj)
   {

      pobj->previous();

   }


   void box::_001OnShowWindow(::message::message * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

   }


   void box::WindowDataEnableSaveWindowRect(bool bEnable)
   {
      m_bEnableSaveWindowRect = bEnable;
   }

   bool box::WindowDataSaveWindowRect()
   {

      //single_lock sl(m_pmutex, true);

      bool bSave = false;

      if (m_bEnableSaveWindowRect)
      {

         defer_update_display();

         ::id idKey = m_strWindowRectDataAddUp + get_data_id().m_id + ".WindowRect." + m_strDisplay;

         //sl.unlock();

         bSave = SaveWindowRect_(idKey, this);
      }

      return true;

   }


   bool box::WindowDataLoadWindowRect(bool bForceRestore, bool bInitialFramePosition)
   {

      //single_lock sl(m_pmutex, true);

      bool bLoad = false;

      keep < bool > keepEnable(&m_bEnableSaveWindowRect, false, m_bEnableSaveWindowRect, true);

      defer_update_display();

      ::id idKey = m_strWindowRectDataAddUp + get_data_id().m_id + ".WindowRect." + m_strDisplay;

      //sl.unlock();

      bLoad = LoadWindowRect_(idKey, this, bForceRestore, bInitialFramePosition);

      if (!bLoad && (bForceRestore || bInitialFramePosition))
      {

         bool bRestore = good_restore(NULL, null_rect(), true) >= 0;

         if (!bRestore)
         {

            on_layout(); // did not changed size, but appearance may have change (e.g., Full Screen to Normal)

            ShowWindow(SW_SHOW);

         }

         return bRestore;

      }

      return bLoad;

   }


   bool box::IsFullScreen()
   {

      return false;

   }


   bool box::LoadWindowRect_(::database::id id, sp(::user::box) pwindow, bool bForceRestore, bool bInitialFramePosition)
   {

      try
      {

         sync_io_error error;

         memory_file file(get_app());

         ::file::byte_stream memstream(&file);

         if (!data_get(id, memstream))
         {

            return false;

         }

         memstream.seek_to_begin();

         int iBefore = 0;

         memstream >> iBefore;

         set_appearance_before((::user::e_appearance)iBefore);

         bool bZoomed = false;

         memstream >> bZoomed;

         bool bFullScreen = false;

         memstream >> bFullScreen;

         bool bIconic = false;

         memstream >> bIconic;

         int iAppearance = 0;

         memstream >> iAppearance;

         ::user::e_appearance eappearance = (::user::e_appearance) iAppearance;

         rect rectWindow;

         memstream >> rectWindow;

         if (error)
            return false;

         if (!bForceRestore)
         {

            if (bZoomed || (bInitialFramePosition && m_eappearanceBefore == ::user::appearance_zoomed))
            {

               pwindow->set_appearance(::user::appearance_zoomed);

               pwindow->best_wkspace(NULL, rectWindow, true);

            }
            else if (bFullScreen || (bInitialFramePosition && m_eappearanceBefore == ::user::appearance_full_screen))
            {

               pwindow->set_appearance(::user::appearance_full_screen);

               pwindow->best_monitor(NULL, rectWindow, true);

            }
            else if (bIconic && !bInitialFramePosition)
            {

               pwindow->set_appearance(::user::appearance_iconic);

               pwindow->good_iconify(NULL, rectWindow, true);

            }
            else if (::user::is_docking_appearance(eappearance))
            {

               pwindow->make_zoneing(NULL, rectWindow, true, &eappearance);

            }
            else
            {

               pwindow->set_appearance(::user::appearance_normal);

               pwindow->good_restore(NULL, rectWindow, true);

            }

         }
         else
         {

            pwindow->set_appearance(::user::appearance_normal);

            pwindow->good_restore(NULL, rectWindow, true);

         }

         return true;

      }
      catch (exit_exception & e)
      {
         throw e;
      }
      catch (...)
      {

         return false;

      }


   }


   bool box::SaveWindowRect_(::database::id id, sp(::user::box) pwindow)
   {
      //WINDOWPLACEMENT wp;
      //pwindow->GetWindowPlacement(&wp);

      memory_file file(get_app());
      ::file::byte_stream stream(&file);

      memory_file fileGet(get_app());
      ::file::byte_stream streamGet(&fileGet);
      bool bGet = data_get(id, streamGet);
      streamGet.seek_to_begin();
      int iBeforeOld = 0;
      bool bZoomedOld = false;
      bool bFullScreenOld = false;
      bool bIconicOld = false;
      int iAppearanceOld = 0;
      rect rectOld;
      if (bGet)
      {
         try
         {
            sync_io_error error;
            streamGet >> iBeforeOld;
            streamGet >> bZoomedOld;
            streamGet >> bFullScreenOld;
            streamGet >> bIconicOld;
            streamGet >> iAppearanceOld;
            streamGet >> rectOld;
            bGet = error.none();
         }
         catch (...)
         {
            bGet = false;
         }
      }

      e_appearance eappearance = get_appearance_before();

      int iBefore = (int)eappearance;
      stream << iBefore;
      bool bZoomed = pwindow->WfiIsZoomed() != FALSE;
      stream << bZoomed;
      bool bFullScreen = pwindow->WfiIsFullScreen();
      stream << bFullScreen;
      bool bIconic = pwindow->WfiIsIconic();
      stream << bIconic;
      int iAppearance = (int)pwindow->get_appearance();
      stream << iAppearance;
      if (bGet && (bZoomed || bFullScreen || bIconic || ::user::is_docking_appearance((::user::e_appearance)iAppearance)))
      {
         stream << rectOld;
      }
      else
      {
         rect rect;
         pwindow->GetWindowRect(rect);
         stream << rect;
      }
      return data_set(id, stream);
   }


   void box::_001WindowRestore()
   {

      set_appearance(::user::appearance_normal);

      WindowDataLoadWindowRect(true);



   }


   string box::calc_display()
   {

      string strDisplay;

      rect rectNormal;

      get_rect_normal(rectNormal);

      rect rectScreen;

      best_monitor(rectScreen, rectNormal);

      strDisplay.Format("Display(%d, %d)", rectScreen.width(), rectScreen.height());

      return strDisplay;

   }

   bool box::does_display_match()
   {

      single_lock sl(m_pmutex, true);

      if (m_strDisplay.is_empty())
         return false;

      return m_strDisplay == calc_display();

   }

   void box::defer_update_display()
   {

      if (m_strDisplay.is_empty())
      {

         if (!data_get(m_strWindowRectDataAddUp + get_data_id().m_id + ".lastdisplay", m_strDisplay) || m_strDisplay.is_empty())
         {

            m_strDisplay = calc_display();

         }

      }
      else
      {

         m_strDisplay = calc_display();

         data_set(m_strWindowRectDataAddUp + get_data_id().m_id + ".lastdisplay", m_strDisplay);

      }

   }


   void box::on_simple_command(::message::simple_command * psimplecommand)
   {

      switch (psimplecommand->m_esimplecommand)
      {
      case simple_command_load_window_rect:

         WindowDataLoadWindowRect(psimplecommand->m_lparam != FALSE);

         psimplecommand->m_bRet = true;

         break;

      default:

         break;

      }

      if (psimplecommand->m_bRet)
      {

         return;

      }

      ::simple_ui::interaction::on_simple_command(psimplecommand);

   }



   void box::on_command(::user::command * pcommand)
   {

      ::simple_ui::interaction::on_command(pcommand);

   }


   bool box::on_before_set_parent(::user::interaction * puiParent)
   {

      if (!::simple_ui::interaction::on_before_set_parent(puiParent))
         return false;

      WindowDataEnableSaveWindowRect(false);

      return true;

   }


   void box::on_set_parent(::user::interaction * puiParent)
   {

      try
      {

         ::simple_ui::interaction::on_set_parent(puiParent);

      }
      catch (...)
      {

      }

   }


   string box::calc_data_id()
   {

      string str;

      str = Application.get_data_id();

      if (str.has_char())
      {

         str += ".";

      }

      return str + m_id;

   }



} // namespace user
















