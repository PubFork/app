#include "linux_g.h"
#include "linux_g_internal_glue.h"
#include "aura/aura/message/message_global.h"

// apt-get install libgtk2.0-dev
// and restart codeblocks/IDE
#include <gtk/gtk.h>
#include <sys/utsname.h>

//int uname(struct utsname *buf);
#ifndef MANJARO
#include <libappindicator3-0.1/libappindicator/app-indicator.h>
#else // MANJARO
#include <libappindicator-0.1/libappindicator/app-indicator.h>
#endif


#include <malloc.h>

#include <time.h>

#include <new>

#include <gio/gio.h>

#include <string.h>

//#include <dirent.h>
#include <sys/stat.h>
//#include <unistd.h>
//#endif

#include <stdlib.h>

class pmutex_lock
{
public:

   pthread_mutex_t * m_pmutex;

   bool m_bLock;

   pmutex_lock(pthread_mutex_t * pmutex, bool bStartLocked = true) :
      m_pmutex(pmutex)
   {

      if(bStartLocked)
      {

         lock();


      }


   }

   ~pmutex_lock()
   {


   }

   void lock()
   {

      pthread_mutex_lock(m_pmutex);

   }
   void unlock()
   {

      pthread_mutex_unlock(m_pmutex);

   }

};


void os_post_quit();


GtkWidget * basecore_app_indicator_init(AppIndicator * pindicator, user_notify_icon_bridge * pbridge);


static void ___extra_action(GtkAction * action, void * data)
{

   ::user_notify_icon_bridge * pi = (::user_notify_icon_bridge *) data;

   pi->notification_area_action(gtk_action_get_stock_id(action));

}

extern "C"
{


   static void __extra_action(GtkAction * action, gpointer data)
   {

      ___extra_action(action, data);

   }


} // extern "C"









void * basecore_app_indicator_new(const char * pszId, const char * pszIcon, const char * pszFolder, user_notify_icon_bridge * pbridge)
{

   AppIndicator * pindicator = app_indicator_new_with_path(pszId, pszIcon, APP_INDICATOR_CATEGORY_APPLICATION_STATUS, pszFolder);

   if(pindicator == NULL)
   {

      return NULL;

   }

   if(!basecore_app_indicator_init(pindicator, pbridge))
   {

      basecore_app_indicator_term(pindicator);

      return NULL;

   }

   return pindicator;

}




void basecore_app_indicator_term(void * pvoidInd)
{

   AppIndicator * pindicator = (AppIndicator *) pvoidInd;

   app_indicator_set_status(pindicator, APP_INDICATOR_STATUS_PASSIVE);

}


void safe_free(void * pfree)
{

   if(pfree == NULL)
   {

      return;

   }

   ::free(pfree);

}


GtkWidget * basecore_app_indicator_init(AppIndicator * pindicator, user_notify_icon_bridge * pbridge)
{

   AppIndicator * m_pappindicator = pindicator;

   int iCount = pbridge->_get_notification_area_action_count();

   GtkWidget *  indicator_menu = NULL;

   if(iCount > 0)
   //if(false)
   {


      GError * error = NULL;

   GtkActionGroup * action_group = gtk_action_group_new ("AppActions");

   if(action_group != NULL)
   {


      GtkActionEntry * entries = new GtkActionEntry[pbridge->_get_notification_area_action_count()];

      gchar * ui_info = (gchar *) malloc(1024 * 1024);

      strcpy(ui_info, "<ui>");
      strcat(ui_info, "  <popup name='IndicatorPopup'>");

      int iEntry = 0;

      for(int i = 0; i < iCount; i++)
      {

         char * pszName = NULL;
         char * pszId = NULL;
         char * pszLabel = NULL;
         char * pszAccelerator = NULL;
         char * pszDescription = NULL;

         int iIndex = i;

         pbridge->_get_notification_area_action_info(&pszName, &pszId, &pszLabel, &pszAccelerator, &pszDescription, iIndex);

         if(strcasecmp(pszName, "separator") == 0)
         {

            strcat(ui_info, "<separator/>\n");

            safe_free(pszName);

         }
         else
         {

            entries[iEntry].name = pszLabel;

            strcat(ui_info, "    <menuitem action='");
            strcat(ui_info, pszLabel);
            strcat(ui_info, "' />");

            entries[iEntry].stock_id = pszId;

            entries[iEntry].label = pszName;

            entries[iEntry].accelerator = pszAccelerator;

            entries[iEntry].tooltip = pszDescription;

            entries[iEntry].callback = G_CALLBACK (__extra_action);

            iEntry++;

         }

      }

      strcat(ui_info, "  </popup>");
      strcat(ui_info, "</ui>");

      gtk_action_group_add_actions (action_group, entries, iEntry, pbridge);

      GtkUIManager * uim = gtk_ui_manager_new ();

      bool bOk = false;

      if(uim != NULL)
      {

         gtk_ui_manager_insert_action_group (uim, action_group, 0);

         bOk = gtk_ui_manager_add_ui_from_string (uim, ui_info, -1, &error) != FALSE;

         if(!bOk)
         {

            g_message ("Failed to build menus: %s\n", error->message);

            g_error_free (error);

            error = NULL;

         }

      }

      for(int i = 0; i < iEntry; i++)
      {

         safe_free((void *) entries[i].name);
         safe_free((void *) entries[i].stock_id);
         safe_free((void *) entries[i].label);
         safe_free((void *) entries[i].accelerator);
         safe_free((void *) entries[i].tooltip);

      }

      delete [] entries;

      free(ui_info);

      if(bOk)
      {

         indicator_menu = gtk_ui_manager_get_widget (uim, "/ui/IndicatorPopup");

         app_indicator_set_menu(m_pappindicator, GTK_MENU (indicator_menu));

      }

   }

   }

   app_indicator_set_status(m_pappindicator, APP_INDICATOR_STATUS_ACTIVE);

   return indicator_menu;

}




//GtkMenuItem * basecore_data::get_menu_item_close()
//{
//
//   GtkMenuItem * pmenuitemClose = NULL;
//
//   GList * l = gtk_container_get_children(GTK_CONTAINER(m_pmenu));
//
//   GtkWidget * pwidget = (GtkWidget *)l->data;
//
//   g_list_free1(l);
//
//   pmenuitemClose = GTK_MENU_ITEM(pwidget);
//
//   return pmenuitemClose;
//
//}



namespace user
{

   bool g_bGInitialized = false;
   pthread_mutex_t g_mutexG;


   bool gsettings_set(const char * pszSchema, const char * pszKey, const char * pszValue)
   {

      if(pszSchema == NULL)
      {

         return false;

      }

      if(pszKey == NULL)
      {

         return false;

      }

      if(pszValue == NULL)
      {

         return false;

      }

      GSettings *settings = g_settings_new(pszSchema);

      if(settings == NULL)
      {

         return false;

      }

      gboolean bOk = g_settings_set_string(settings, pszKey, pszValue);

      g_settings_sync ();

      if (settings != NULL)
      {

         g_object_unref (settings);

      }

      return bOk;

   }


   char * gsettings_get_malloc(const char * pszSchema, const char * pszKey)
   {

      if(pszSchema == NULL)
      {

         return NULL;

      }

      if(pszKey == NULL)
      {

         return NULL;

      }

      GSettings *settings = g_settings_new(pszSchema);

      if(settings == NULL)
      {

         return NULL;

      }

      gchar * pgchar = g_settings_get_string (settings, pszKey);

      if(pgchar == NULL)
      {

         g_free (pgchar);

         g_object_unref (settings);

         return NULL;

      }

      char * psz = strdup(pgchar);

      g_free (pgchar);

      g_object_unref (settings);

      return psz;

   }


   e_desktop g_edesktop = desktop_gnome;


   e_desktop get_edesktop()
   {

      return g_edesktop;

   }


   void initialize_edesktop()
   {

      g_edesktop = calc_edesktop();

   }


   e_desktop calc_edesktop()
   {

      const char * pszDesktop = getenv("XDG_CURRENT_DESKTOP");

      utsname name;

      memset(&name, 0, sizeof(utsname));

      uname(&name);

      if(pszDesktop != NULL)
      {

         if(strcasecmp(pszDesktop, "Unity") == 0)
         {

            return desktop_unity_gnome;

         }

      }

      if(is_dir("/etc/xdg/lubuntu"))
      {

         return desktop_lxde;

      }
      else if(file_exists_dup("/usr/bin/xfconf-query"))
      {

         return desktop_xfce;

      }
      else if(file_exists_dup("/usr/bin/mate-about"))
      {

         return desktop_mate;

      }
      else if(file_exists_dup("/usr/bin/unity"))
      {

         return desktop_unity_gnome;

      }
      else if(strcasecmp(pszDesktop, "ubuntu:gnome") == 0)
      {

         return desktop_ubuntu_gnome;

      }

      return desktop_gnome;

   }


   void wallpaper_change_notification (GSettings   *settings,             const gchar *key,             gpointer     data)
   {

      c_post_system_event(system_event_wallpaper_change);

   }


   GAction * g_pactionWallpaper = NULL;


   bool g_enable_wallpaper_change_notification(const char * pszSchema, const char * pszKey)
   {

      if(!g_bGInitialized)
      {

         return false;

      }

      pmutex_lock lock(&g_mutexG);

      if(g_pactionWallpaper != NULL)
      {

         return true;

      }

      GSettings * settings = g_settings_new(pszSchema);

      if(settings == NULL)
      {

         return false;

      }

      g_pactionWallpaper = g_settings_create_action (settings, pszKey);

      g_object_unref (settings);

      g_signal_connect (g_pactionWallpaper, "notify::state", G_CALLBACK (wallpaper_change_notification), NULL);

      return true;

   }


   void g_defer_init()
   {

      if(g_bGInitialized)
      {

         return;

      }

      g_bGInitialized = true;

      pthread_mutex_init(&g_mutexG, NULL);

   }

   void g_defer_term()
   {

      if(!g_bGInitialized)
      {

         return;

      }

      g_bGInitialized = false;

      if(g_pactionWallpaper != NULL)
      {

         g_object_unref(g_pactionWallpaper);

         g_pactionWallpaper = NULL;

      }

      pthread_mutex_destroy(&g_mutexG);


   }


} // namespace user



const char * basecore_get_file_icon_path(const char * pszPath, int iSize)
{

   GFile * pfile = g_file_new_for_path (pszPath);

   if(pfile == NULL)
   {

      return NULL;

   }

   GError * perror = NULL;

   GFileInfo * pfileinfo = g_file_query_info (pfile, "standard::*", G_FILE_QUERY_INFO_NONE, NULL, &perror);

   if(pfileinfo == NULL)
   {

      return NULL;

   }

   /* you'd have to use g_loadable_icon_load to get the actual icon */
   GIcon * picon = g_file_info_get_icon (pfileinfo);

   if(picon == NULL)
   {

      return NULL;

   }

   if(G_IS_FILE_ICON(G_OBJECT(picon)))
   {

      GFileIcon * pfileicon = G_FILE_ICON(G_OBJECT(picon));

      if(pfileicon == NULL)
      {

         return NULL;

      }

      GFile * pfileIcon = g_file_icon_get_file(pfileicon);

      if(pfileIcon == NULL)
      {

         return NULL;

      }

      char * psz = strdup(g_file_get_path(pfileIcon));

      return psz;

   }
   else if(G_IS_THEMED_ICON(G_OBJECT(picon)))
   {

      GtkIconInfo *pGtkIconInfo;

      GtkIconTheme *pGtkIconTheme= gtk_icon_theme_get_default();

      if(pGtkIconTheme == NULL)
      {

         return NULL;

      }

      pGtkIconInfo=gtk_icon_theme_lookup_by_gicon(pGtkIconTheme,picon,(gint)iSize,GTK_ICON_LOOKUP_USE_BUILTIN);

      if(pGtkIconInfo == NULL)
      {

         return NULL;

      }

      const char * p = gtk_icon_info_get_filename(pGtkIconInfo);

      char * psz = NULL;

      if(p != NULL)
      {

         psz = strdup(p);

      }

      return psz;

   }

   return NULL;

}


const char * basecore_get_file_content_type(const char * pszPath)
{

   GFile * pfile = g_file_new_for_path (pszPath);

   if(pfile == NULL)
   {

      return NULL;

   }

   GError * perror = NULL;

   GFileInfo * pfileinfo = g_file_query_info (pfile, "standard::*", G_FILE_QUERY_INFO_NONE, NULL, &perror);

   if(pfileinfo == NULL)
   {

      return NULL;

   }

   const char * pszContentType = g_file_info_get_content_type (pfileinfo);

   const char * p = NULL;

   if(pszContentType != NULL)
   {

      p = strdup(pszContentType);

   }

   return p;

}




