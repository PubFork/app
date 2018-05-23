#include "basecore.h"
#include "basecore_shared.h"
#include "basecore_internal_glue.h"

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

struct indicator;

void os_post_quit();

GtkWidget * idle_basecore_app_indicator_init(indicator * pind, user_notify_icon_appindicator_bridge * pi);

void * basecore_app_indicator_init(indicator * pind, struct user_notify_icon_appindicator_bridge * pi);


static void ___close(void * data)
{

   ::user_notify_icon_appindicator_bridge * pi = (::user_notify_icon_appindicator_bridge *) data;

   if(pi->__close_is_closed())
   {

      pi->__open();

   }
   else
   {

      pi->__close();

   }

}


static void ___quit(void * data)
{

   ::user_notify_icon_appindicator_bridge * pi = (::user_notify_icon_appindicator_bridge *) data;

   pi->__quit();

}


static void ___extra_action(GtkAction * action, void * data)
{

   ::user_notify_icon_appindicator_bridge * pi = (::user_notify_icon_appindicator_bridge *) data;

   pi->notification_area_extra_action(gtk_action_get_stock_id(action));

}

extern "C"
{

   static void __close(GtkAction * action, gpointer data)
   {

      ___close(data);

   }


   static void __quit(GtkAction * action, gpointer data)
   {

      ___quit(data);

   }


   static void __extra_action(GtkAction * action, gpointer data)
   {

      ___extra_action(action, data);

   }


   static gboolean f1(gpointer data);


} // extern "C"









void basecore_init()
{

   // deprecated
   // g_thread_init (NULL);

   // g_type_init ();

   //gtk_init_check(0, 0);

   //gtk_main();

}



struct basecore_data
{
public:

   const char *         m_pszId;
   const char *         m_pszIcon;
   const char *         m_pszFolder;
   AppIndicator *       m_pindicator;
   user_notify_icon_appindicator_bridge *       m_piclosequit;
   indicator *          m_pind;
   bool                 m_bReady;
   bool                 m_bLoop;
   bool                 m_bTerm;
   int                  m_iTry;
   void *               m_pvoidRet;
   GtkWidget *          m_pmenu;
   int                  m_iOpen;
   bool                 m_bQuitGtk;


   basecore_data();
   ~basecore_data();

   virtual void post();
   virtual void * process();
   virtual void * wait();
   gboolean run();

   GtkMenuItem * get_menu_item_close();

};


basecore_data::basecore_data()
{
   m_pszId = NULL;
   m_pszIcon = NULL;
   m_pindicator = NULL;
   m_pind = NULL;
   m_piclosequit = NULL;
   m_bReady = false;
   m_iTry = 0;
   m_pvoidRet = NULL;
   m_pmenu = NULL;
   m_bLoop = false;
   m_bTerm = true;
   m_iOpen = -1;
   m_bQuitGtk = false;
}


basecore_data::~basecore_data()
{
   if(m_pszId != NULL)
   {
      free((void *)m_pszId);
   }
   if(m_pszIcon != NULL)
   {
      free((void *)m_pszIcon);
   }
   if(m_pszFolder != NULL)
   {
      free((void *)m_pszFolder);
   }

}


struct indicator_new : public basecore_data
{
   indicator_new(const char * pszId, const char *pszIcon, const char * pszFolder)
   {
      m_pszId     = strdup(pszId);
      m_pszIcon   = strdup(pszIcon);
      m_pszFolder = strdup(pszFolder);
   }

};

struct indicator : public basecore_data
{

   indicator(AppIndicator * pindicator)
   {

      m_pind            = this;
      m_pindicator = pindicator;

   }

   void init(user_notify_icon_appindicator_bridge * piclosequit, GtkWidget * pmenu)
   {

      m_piclosequit = piclosequit;
      m_pmenu = pmenu;
      m_bLoop = false;
      m_bTerm = false;

   }

};

struct indicator_init : public basecore_data
{
   indicator_init(indicator * pind, user_notify_icon_appindicator_bridge * piclosequit)
   {
      m_pind         = pind;
      m_pindicator   = pind->m_pindicator;
      m_piclosequit  = piclosequit;
   }

};



struct indicator_term : public basecore_data
{
   indicator_term(indicator * pind)
   {
      m_pind = pind;
      m_pindicator   = pind->m_pindicator;
   }

};

void basecore_data::post()
{
   g_idle_add(f1,(basecore_data*)this);
}

void * basecore_data::process()
{

   post();

   return wait();
}

void * basecore_data::wait()
{
   timespec req;
   req.tv_sec=0;
   req.tv_nsec = 284*1000*1000;
   timespec rem;
   while(m_iTry < 100 && !m_bReady)
   {
      nanosleep(&req, &rem);
      m_iTry++;
   }
   void * pRet = m_pvoidRet;
   delete this;
   return pRet;
}


gboolean f1(gpointer p)
{

   basecore_data * data = (basecore_data *) p;

   return data->run();

}


void basecore_step(void * p)
{

   indicator * pind = (indicator *)p;

   pind->post();

}


void * basecore_app_indicator_new(const char * pszId, const char * pszIcon, const char * pszFolder, user_notify_icon_appindicator_bridge * pi)
{

   indicator_new * data = new indicator_new(pszId, pszIcon, pszFolder);

   indicator * pind = (indicator *) data->process();

   if(pind == NULL)
   {

      return NULL;

   }

   if(!basecore_app_indicator_init(pind,pi))
   {

      basecore_app_indicator_term(pind);

      return NULL;

   }

   return pind;

}



void * basecore_app_indicator_init(indicator * pind, user_notify_icon_appindicator_bridge * pi)
{

   indicator_init * data = new indicator_init(pind, pi);

   return data->process();

}


void basecore_app_indicator_term(void * pvoidInd)
{

   indicator * pind = (indicator *) pvoidInd;

   indicator_term * data = new indicator_term(pind);

   data->process();

   //pind->wait();

}


GtkWidget * idle_basecore_app_indicator_init(indicator * pind, user_notify_icon_appindicator_bridge * pi)
{

   AppIndicator * m_pappindicator = (AppIndicator *) pind->m_pindicator;

   GError *error = NULL;

   GtkActionGroup * action_group = gtk_action_group_new ("AppActions");

   if(action_group == NULL)
   {

      return NULL;

   }

   GtkActionEntry sentries[] =
   {

      { "Close" , "application-close" , "_Close" , "<control>C" , "Close the application", G_CALLBACK (__close) },
      { "Quit"  , "application-exit"  , "_Quit"  , "<control>Q" , "Exit the application", G_CALLBACK (__quit) },

   };

   guint n_entries = G_N_ELEMENTS (sentries);

   GtkActionEntry * entries = new GtkActionEntry[n_entries + pi->notification_extra_action_count()];


   gchar *ui_info = (gchar *) malloc(1024 * 1024);

   strcpy(ui_info, "<ui>");
   strcat(ui_info, "  <popup name='IndicatorPopup'>");
   strcat(ui_info, "    <menuitem action='Close' />");
   strcat(ui_info, "    <menuitem action='Quit' />");
   strcat(ui_info, "    <separator/>");

   for(int i = 0; i < pi->notification_extra_action_count(); i++)
   {

      char * pszName = NULL;
      char * pszId = NULL;
      char * pszLabel = NULL;
      char * pszAccelerator = NULL;
      char * pszDescription = NULL;

      pi->notification_area_action_info(&pszName, &pszId, &pszLabel, &pszAccelerator, &pszDescription, i);

      entries[i].name = pszName;

      strcat(ui_info, "    <menuitem action='");
      strcat(ui_info, pszName);
      strcat(ui_info, "' />");

      entries[i].stock_id = pszId;

      entries[i].label = pszLabel;

      entries[i].accelerator = pszAccelerator;

      entries[i].tooltip = pszDescription;

      entries[i].callback = G_CALLBACK (__extra_action);

   }

   strcat(ui_info, "  </popup>");
   strcat(ui_info, "</ui>");


   memcpy(&entries[pi->notification_extra_action_count()], sentries, sizeof(sentries));


//static const gchar *ui_info =
//   "<ui>"
//  "  <popup name='IndicatorPopup'>"
//  "    <menuitem action='Close' />"
//  "    <menuitem action='Quit' />"
//  "  </popup>"
//  "</ui>";
//

   gtk_action_group_add_actions (action_group, entries, n_entries + pi->notification_extra_action_count(), pi);

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

   for(int i = 0; i < pi->notification_extra_action_count(); i++)
   {

      free((void *) entries[i].name);
      free((void *) entries[i].stock_id);
      free((void *) entries[i].label);
      free((void *) entries[i].accelerator);
      free((void *) entries[i].tooltip);

   }

   delete [] entries;

   free(ui_info);


   if(!bOk)
   {

      return NULL;

   }



   GtkWidget *  indicator_menu = gtk_ui_manager_get_widget (uim, "/ui/IndicatorPopup");

   app_indicator_set_menu(m_pappindicator, GTK_MENU (indicator_menu));

   app_indicator_set_status(m_pappindicator, APP_INDICATOR_STATUS_ACTIVE);

   return indicator_menu;

}


void basecore_term()
{

   basecore_data * data = new basecore_data();

   data->m_bQuitGtk = true;

   data->process();

}


GtkMenuItem * basecore_data::get_menu_item_close()
{

   GtkMenuItem * pmenuitemClose = NULL;

   GList * l = gtk_container_get_children(GTK_CONTAINER(m_pmenu));

//   int count = m_piclosequit->bridge_extra_action_count();
//
//   while(count > 0)
//   {
//      l = l->next;
//      count--;
//
//   }

   GtkWidget * pwidget = (GtkWidget *)l->data;

   g_list_free1(l);

   pmenuitemClose = GTK_MENU_ITEM(pwidget);

   return pmenuitemClose;

}

gboolean basecore_data::run()
{

   if(m_pszId != NULL && m_pszIcon != NULL)
   {

      AppIndicator * pindicator = app_indicator_new_with_path(m_pszId, m_pszIcon, APP_INDICATOR_CATEGORY_APPLICATION_STATUS, m_pszFolder);

      if(pindicator == NULL)
      {

         m_pvoidRet = NULL;

      }
      else
      {

         ::indicator * pind = new indicator(pindicator);

         m_pvoidRet = pind;

      }



   }
   else if(m_pind != NULL)
   {

      if(m_piclosequit != NULL)
      {

         if(m_pmenu)
         {


            if(m_piclosequit->__close_is_closed())
            {

               if(m_iOpen != 0)
               {

                  gtk_menu_item_set_label(get_menu_item_close(), "Open");

                  m_iOpen = 0;

               }

            }
            else
            {

               if(m_iOpen != 1)
               {

                  gtk_menu_item_set_label(get_menu_item_close(), "Close");

                  m_iOpen = 1;

               }

            }

            if(m_bTerm)
            {

               m_bLoop = false;

            }

         }
         else
         {

            GtkWidget * pmenu = idle_basecore_app_indicator_init(m_pind, m_piclosequit);

            m_pind->init(m_piclosequit, pmenu);

            m_pind->post();

            m_pvoidRet = m_pind;

         }

      }
      else
      {

         app_indicator_set_status(m_pindicator, APP_INDICATOR_STATUS_PASSIVE);

         m_pind->m_bTerm = true;

      }

   }
   else if(m_bQuitGtk)
   {

      os_post_quit();

   }

   if(!m_bLoop)
   {

      m_bReady = true;

   }

   return m_bLoop;

}



namespace user
{


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


   int gsettings_get(char * pszValue, int iSize, const char * pszSchema, const char * pszKey)
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

         return -1;

      }

      gchar * pgchar = g_settings_get_string (settings, pszKey);

      if(pgchar == NULL)
      {

         g_free (pgchar);

         g_object_unref (settings);

         return -1;

      }

      int iLen = strlen(pgchar);

      if(pszValue == NULL)
      {

         g_object_unref (settings);

         return iLen;

      }

      if(iLen > iSize)
      {

         strncpy(pszValue, pgchar, MIN(iSize, iLen));

      }
      else
      {

         strcpy(pszValue, pgchar);

      }

      g_free (pgchar);

      if (settings != NULL)
      {

         g_object_unref (settings);

      }

      return iLen;

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
