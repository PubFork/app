#pragma once


#include <gtk/gtk.h>



typedef struct
{

  GtkApplication parent_instance;

  //guint quit_inhibit;
  //GMenu *time;
  //guint timeout;

} BloatPad; // you can search for BloatPad in 2017 and so Internet

typedef GtkApplicationClass BloatPadClass;

G_DEFINE_TYPE (BloatPad, bloat_pad, GTK_TYPE_APPLICATION)

extern BloatPad * g_pappBloatPad;
