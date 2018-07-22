#include "framework.h"
#include "linux.h"
#include "aura/aura/os/linux/linux_user_impl.h"

#include <gtk/gtk.h>


extern GMainContext * gtk_main_context;


enum e_clipboard
{

   clipboard_none,
   clipboard_error,
   clipboard_get_plain_text,
   clipboard_set_patha,
   clipboard_get_patha,
   clipboard_get_file_target_count,
   clipboard_get_dib,

};


struct clipboard_data :
   virtual public ::object
{
public:


   clipboard_data(::aura::application * papp, e_clipboard eclipboard) :
   object(papp),
   m_event(papp)
   {

      m_eclipboard = eclipboard;

      m_event.ResetEvent();

   }

   ::user::copydesk::e_op     m_eop;
   e_clipboard                m_eclipboard;
   manual_reset_event         m_event;
   string                     m_str;
   ::draw2d::dib_sp           m_dib;
   ::file::patha              m_patha;
   int                        m_nTargets;
   GtkImage *                 m_pgtkimage;

};


BEGIN_EXTERN_C

void clipboard_targets_func(GtkClipboard *clipboard, GdkAtom *atoms, gint n_atoms, gpointer data)
{

   clipboard_data * pdata = (clipboard_data *) data;

   GdkAtom target = gdk_atom_intern("x-special/gnome-copied-files", false);

   pdata->m_nTargets = 0;

   for(int i = 0; i < n_atoms; i++)
   {

      if(atoms[i] == target)
      {

         pdata->m_nTargets = 1;

         break;

      }

   }

   pdata->m_event.SetEvent();

}

void clipboard_image_received_func(GtkClipboard * clipboard, GdkPixbuf * pixbuf,	gpointer data)
{

   clipboard_data * pdata = (clipboard_data *) data;

   int iBitsPerSample = gdk_pixbuf_get_bits_per_sample(pixbuf);

   int iChannels = gdk_pixbuf_get_n_channels (pixbuf);

   GdkColorspace space = gdk_pixbuf_get_colorspace (pixbuf);

   bool bHasAlpha = gdk_pixbuf_get_has_alpha (pixbuf);

   if(iBitsPerSample == 8
      && (iChannels == 4 || iChannels == 3)
      && (space == GDK_COLORSPACE_RGB)
      && (bHasAlpha || !bHasAlpha))
   {

      int w = gdk_pixbuf_get_width(pixbuf);

      int h = gdk_pixbuf_get_height(pixbuf);

      COLORREF * pcolorrefSrc = (COLORREF *) gdk_pixbuf_read_pixels(pixbuf);

      int iSrcScan = gdk_pixbuf_get_rowstride(pixbuf);

      if(pdata->m_dib->create(w, h))
      {

         ::draw2d::copy_colorref(
            pdata->m_dib->m_size.cx,
            pdata->m_dib->m_size.cy,
            pdata->m_dib->m_pcolorref,
            pdata->m_dib->m_iScan,
            pcolorrefSrc,
            iSrcScan);

         if(!bHasAlpha)
         {

            pdata->m_dib->fill_channel(255, visual::rgba::channel_alpha);

         }

      }

   }

   pdata->m_event.SetEvent();

}



void clipboard_received_func(GtkClipboard * clipboard, GtkSelectionData * selection_data, gpointer data)
{

   clipboard_data * pdata = (clipboard_data *) data;

   string str = gtk_selection_data_get_data(selection_data);

   stringa stra;

   stra.add_lines(str);

   if(stra.is_empty())
   {

      pdata->m_eclipboard = clipboard_error;

      pdata->m_event.SetEvent();

      return;

   }

   string strOp = stra[0];

   if(strOp.compare_ci("copy") == 0)
   {

      pdata->m_eop = ::user::copydesk::op_copy;

   }
   else if(strOp.compare_ci("cut") == 0)
   {

      pdata->m_eop = ::user::copydesk::op_cut;

   }
   else
   {

      pdata->m_eclipboard = clipboard_error;

      pdata->m_event.SetEvent();

      return;

   }

   for(index i = 1; i < stra.get_size(); i++)
   {

      string strItem = stra[i];

      ::str::begins_eat_ci(strItem, "file://");

      pdata->m_patha.add(::file::path(strItem));

   }

   pdata->m_event.SetEvent();

}


void clipboard_get_func(GtkClipboard * clipboard, GtkSelectionData * selection_data, guint info, gpointer user_data)
{

   clipboard_data * pdata = (clipboard_data *) user_data;

   //var temp = _action + "\n" + _source; _action "cut"/"copy"

   string strAction;

   if(pdata->m_eop == ::user::copydesk::op_copy)
   {

      strAction = "copy";

   }
   else if(pdata->m_eop == ::user::copydesk::op_cut)
   {

     strAction = "cut";

   }
   else
   {

      pdata->m_eclipboard = clipboard_error;

      return;

   }

   string str;

   if(info == 1)
   {

      str = "# ";

   }

   str += strAction;

   for(auto & path : pdata->m_patha)
   {

      str += "\n";

      str += "file://" + path;

   }

   GdkAtom target = gtk_selection_data_get_target(selection_data);

   gtk_selection_data_set(selection_data, target, 8, (const guchar *) (const char *) str, str.get_length());


}


void clipboard_clear_func(GtkClipboard * clipboard, gpointer user_data)
{

   clipboard_data * pdata = (clipboard_data *) user_data;

   ::release(pdata);

}

void clipboard_text_request_callback(GtkClipboard *clipboard, const gchar * text, gpointer data)
{

   clipboard_data * pdata = (clipboard_data *) data;

   if(text != NULL)
   {

      pdata->m_str = text;

   }

   pdata->m_event.SetEvent();

}


gboolean clipboard_callback(gpointer data)
{

   clipboard_data * pdata = (clipboard_data *) data;

   GtkClipboard* clipboard = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);

   if(pdata->m_eclipboard == clipboard_get_plain_text)
   {


      gtk_clipboard_request_text(clipboard, &clipboard_text_request_callback, pdata);

   }
   else if(pdata->m_eclipboard == clipboard_set_patha)
   {

      //_source = _fileCopy.Uri;
      //     _action = _radioMove.Active ? "cut" : "copy";

      GtkTargetEntry entrya[2];

      entrya[0].target = "x-special/gnome-copied-files";
      entrya[0].flags = 0;
      entrya[0].info = 0;

      entrya[1].target = "text/uri-list";
      entrya[1].flags = 0;
      entrya[1].info = 1;

      gtk_clipboard_set_with_data(clipboard, entrya, 2, &clipboard_get_func, &clipboard_clear_func, pdata);

      pdata->m_event.SetEvent();

   }
   else if(pdata->m_eclipboard == clipboard_get_patha)
   {

      GdkAtom target = gdk_atom_intern("x-special/gnome-copied-files", false);

      gtk_clipboard_request_contents(clipboard, target, &clipboard_received_func, pdata);

   }
   else if(pdata->m_eclipboard == clipboard_get_file_target_count)
   {

      gtk_clipboard_request_targets(clipboard, &clipboard_targets_func, pdata);

   }
   else if(pdata->m_eclipboard == clipboard_get_dib)
   {

      if(gtk_clipboard_wait_is_image_available(clipboard))
      {

         gtk_clipboard_request_image (clipboard, &clipboard_image_received_func, pdata);

         return false;

      }

      clipboard = gtk_clipboard_get(GDK_SELECTION_PRIMARY);

      if(gtk_clipboard_wait_is_image_available(clipboard))
      {

         gtk_clipboard_request_image (clipboard, &clipboard_image_received_func, pdata);

         return false;

      }

      clipboard = gtk_clipboard_get(GDK_SELECTION_SECONDARY);

      if(gtk_clipboard_wait_is_image_available(clipboard))
      {

         gtk_clipboard_request_image (clipboard, &clipboard_image_received_func, pdata);

         return false;

      }

      pdata->m_event.SetEvent();

//      GdkPixbuf * pixbuf = gtk_clipboard_wait_for_image(clipboard);
//
//      if(pixbuf == NULL)
//      {
//
//         clipboard = gtk_clipboard_get(GDK_SELECTION_PRIMARY);
//
//         pixbuf = gtk_clipboard_wait_for_image(clipboard);
//
//      }
//
//      if(pixbuf != NULL)
//      {
//
//         clipboard_data * pdata = (clipboard_data *) data;
//
//         int iBitsPerSample = gdk_pixbuf_get_bits_per_sample(pixbuf);
//
//         int iChannels = gdk_pixbuf_get_n_channels (pixbuf);
//
//         GdkColorspace space = gdk_pixbuf_get_colorspace (pixbuf);
//
//         bool bHasAlpha = gdk_pixbuf_get_has_alpha (pixbuf);
//
//         if(iBitsPerSample == 8
//            && (iChannels == 4 || iChannels == 3)
//            && (space == GDK_COLORSPACE_RGB)
//            && (bHasAlpha || !bHasAlpha))
//         {
//
//            int w = gdk_pixbuf_get_width(pixbuf);
//
//            int h = gdk_pixbuf_get_height(pixbuf);
//
//            COLORREF * pcolorrefSrc = (COLORREF *) gdk_pixbuf_read_pixels(pixbuf);
//
//            int iSrcScan = gdk_pixbuf_get_rowstride(pixbuf);
//
//            if(pdata->m_dib->create(w, h))
//            {
//
//               ::draw2d::copy_colorref(
//                  pdata->m_dib->m_size.cx,
//                  pdata->m_dib->m_size.cy,
//                  pdata->m_dib->m_pcolorref,
//                  pdata->m_dib->m_iScan,
//                  pcolorrefSrc,
//                  iSrcScan);
//
//               if(!bHasAlpha)
//               {
//
//                  pdata->m_dib->fill_channel(255, visual::rgba::channel_alpha);
//
//               }
//
//            }
//
//         }
//
//      }
//
//      pdata->m_event.SetEvent();


   }
   else
   {

      throw invalid_argument_exception(pdata->get_app());

   }

   return false;

}

END_EXTERN_C


namespace linux
{


   copydesk::copydesk(::aura::application * papp) :
      ::object(papp),
      ::user::copydesk(papp)
   {


   }


   copydesk::~copydesk()
   {

   }


   bool copydesk::initialize()
   {


      if(!::user::copydesk::initialize())
         return false;

      return true;

   }


   bool copydesk::finalize()
   {

      bool bOk;

      bOk = ::user::copydesk::finalize();

      return bOk;

   }


   bool copydesk::_set_plain_text(const string & str)
   {

      GtkClipboard * clipboard = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);

      gtk_clipboard_set_text (clipboard, str.c_str(), str.get_length());

      return true;

   }


   bool copydesk::_get_plain_text(string & str)
   {

      sp(clipboard_data) pdata = canew(clipboard_data(get_app(), clipboard_get_plain_text));

      pdata->add_ref();

      auto idle_source = g_idle_source_new();

      g_source_set_callback(idle_source, &clipboard_callback, pdata, NULL);

      g_source_attach(idle_source, gtk_main_context);

      if(!pdata->m_event.wait(seconds(5)).succeeded())
      {

         return false;

      }

      g_source_destroy(idle_source);

      str = pdata->m_str;

      return true;

   }


   bool copydesk::_has_plain_text()
   {

      sp(ovar) var(canew(ovar));

      var->m_var = false;

      gdk_sync(seconds(5), [=]()
      {

         GtkClipboard* clipboard = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);

         var->m_var = gtk_clipboard_wait_is_text_available (clipboard);

      });

      return var->m_var.operator bool();

   }


   bool copydesk::_has_filea()
   {

      sp(clipboard_data) pdata = canew(clipboard_data(get_app(), clipboard_get_file_target_count));

      pdata->add_ref();

      auto idle_source = g_idle_source_new();

      g_source_set_callback(idle_source, &clipboard_callback, pdata, NULL);

      g_source_attach(idle_source, gtk_main_context);

      if(!pdata->m_event.wait(seconds(5)).succeeded())
      {

         return false;

      }

      return pdata->m_nTargets > 0;

   }


   bool copydesk::_get_filea(::file::patha & patha, e_op & eop)
   {

      sp(clipboard_data) pdata = canew(clipboard_data(get_app(), clipboard_get_patha));

      pdata->add_ref();

      auto idle_source = g_idle_source_new();

      g_source_set_callback(idle_source, &clipboard_callback, pdata, NULL);

      g_source_attach(idle_source, gtk_main_context);

      if(!pdata->m_event.wait(seconds(5)).succeeded() || pdata->m_eclipboard == clipboard_error)
      {

         return false;

      }

      eop = pdata->m_eop;

      patha = pdata->m_patha;

      return true;

   }


   bool copydesk::_set_filea(const ::file::patha & patha, e_op eop)
   {

      sp(clipboard_data) pdata = canew(clipboard_data(get_app(), clipboard_set_patha));

      pdata->add_ref();

      pdata->m_eop = eop;

      pdata->m_patha = patha;

      auto idle_source = g_idle_source_new();

      g_source_set_callback(idle_source, &clipboard_callback, pdata, NULL);

      g_source_attach(idle_source, gtk_main_context);

      if(!pdata->m_event.wait(seconds(5)).succeeded())
      {

         return false;

      }

      g_source_destroy(idle_source);

      return true;

   }



   bool copydesk::_desk_to_dib(::draw2d::dib * pdib)
   {

      sp(clipboard_data) pdata = canew(clipboard_data(get_app(), clipboard_get_dib));

      pdata->add_ref();

      pdata->m_dib.alloc(allocer());

      auto idle_source = g_idle_source_new();

      g_source_set_callback(idle_source, &clipboard_callback, pdata, NULL);

      g_source_attach(idle_source, gtk_main_context);

      if(!pdata->m_event.wait(seconds(5)).succeeded() || pdata->m_eclipboard == clipboard_error)
      {

         return false;

      }

      pdib->from(pdata->m_dib);

      return true;

   }


   bool copydesk::_dib_to_desk(::draw2d::dib * pdib)
   {


      return false;


   }


   bool copydesk::_has_dib()
   {

      GtkClipboard* clipboard = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);

      return gtk_clipboard_wait_is_image_available (clipboard);


   }


} // namespace linux




