#include "framework.h"


namespace user
{


   box::box() :
      ::object(get_app())
   {

      m_strWindowRectDataAddUp = "&data_source=local&";

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

      initialize_data_client(&System.dataserver());

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

      ::id idData = get_data_id().m_id;

      ::id idKey = m_strWindowRectDataAddUp + idData + ".WindowRect." + m_strDisplay;

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

         {

            writer writer(&file);

            if (!data_get(id, writer))
            {

               return false;

            }

         }

         file.seek_to_begin();

         {

            reader reader(&file);

            int iBefore = 0;

            reader >> iBefore;

            set_appearance_before((::user::e_appearance)iBefore);

            bool bZoomed = false;

            reader >> bZoomed;

            bool bFullScreen = false;

            reader >> bFullScreen;

            bool bIconic = false;

            reader >> bIconic;

            int iAppearance = 0;

            reader >> iAppearance;

            ::user::e_appearance eappearance = (::user::e_appearance) iAppearance;

            rect rectRestored;

            reader >> rectRestored;

            rect rectWindow;

            reader >> rectWindow;

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

                  pwindow->good_restore(NULL, rectRestored, true);

               }

            }
            else
            {

               pwindow->set_appearance(::user::appearance_normal);

               pwindow->good_restore(NULL, rectRestored, true);

            }

         }

         return true;

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

      return false;

   }


   bool box::SaveWindowRect_(::database::id id, sp(::user::box) pwindow)
   {

      memory_file fileGet(get_app());

      bool bGet;

      {

         writer writer(&fileGet);

         bGet = data_get(id, writer);

      }

      fileGet.seek_to_begin();

      int iBeforeOld = 0;
      bool bZoomedOld = false;
      bool bFullScreenOld = false;
      bool bIconicOld = false;
      int iAppearanceOld = 0;
      rect rectOld;
      rect rectRestoredOld;
      if (bGet)
      {

         reader reader(&fileGet);

         try
         {

            sync_io_error error;

            reader >> iBeforeOld;
            reader >> bZoomedOld;
            reader >> bFullScreenOld;
            reader >> bIconicOld;
            reader >> iAppearanceOld;
            reader >> rectRestoredOld;
            reader >> rectOld;

            bGet = error.none();

         }
         catch (...)
         {

            bGet = false;

         }

      }

      e_appearance eappearance = get_appearance_before();

      memory_file file(get_app());

      {

         writer writer(&file);

         int iBefore = (int)eappearance;
         writer << iBefore;
         bool bZoomed = pwindow->WfiIsZoomed() != FALSE;
         writer << bZoomed;
         bool bFullScreen = pwindow->WfiIsFullScreen();
         writer << bFullScreen;
         bool bIconic = pwindow->WfiIsIconic();
         writer << bIconic;
         int iAppearance = (int)pwindow->get_appearance();
         writer << iAppearance;
         rect rect;
         pwindow->GetWindowRect(rect);
         if (bGet && (bZoomed || bFullScreen || bIconic || ::user::is_docking_appearance((::user::e_appearance)iAppearance)))
         {
            writer << rectRestoredOld;
         }
         else
         {
            writer << rect;
         }
         writer << rect;

      }

      file.seek_begin();

      {

         reader reader(&file);

         return data_set(id, reader);

      }

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

      if(m_id.is_empty())
      {

         m_id = calc_user_interaction_id();

         if(m_id.is_empty())
         {

            m_id = calc_default_user_interaction_id();

            if(m_id.is_empty())
            {

               return "";

            }

         }

      }

      string str;

      str = Application.get_data_id();

      if (str.has_char())
      {

         str += ".";

      }

      str += m_id;

      string strModifier = get_data_key_modifier();

      if (strModifier.has_char())
      {

         str += "&";

         str += strModifier;

      }

      return str;

      return str + m_id + get_data_key_modifier();

   }


   bool box::parent_is_local_data()
   {

      ::user::interaction * puiParent = GetParent();

      sp(::database::client) pclient = puiParent;

      if(pclient.is_set())
      {

         if(pclient->is_local_data())
         {

            return true;

         }
         else
         {

            return false;

         }

      }

      return false;

   }


   bool box::is_local_data()
   {

      if(::database::client::is_local_data() || Application.is_local_data())
      {

         return true;

      }

      if(parent_is_local_data())
      {

         return true;

      }

      return false;

   }


} // namespace user
















