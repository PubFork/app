#pragma once


class osdisplay_dataptra;
class osdisplay_data;
class mutex;


CLASS_DECL_AURA int32_t osdisplay_find(Display * pdisplay);
CLASS_DECL_AURA osdisplay_data * osdisplay_get(Display * pdisplay);
CLASS_DECL_AURA bool osdisplay_remove(Display * pdisplay);


class CLASS_DECL_AURA xdisplay
{
public:


   osdisplay_data *  m_pdata;
   bool              m_bLocked;
   bool              m_bOwn;


   xdisplay();
   xdisplay(Display * pdisplay, bool bInitialLock = true);
   ~ xdisplay();


   bool open(char * display_name, bool bInitialLock = true);

   void lock();
   void unlock();

   bool close();

   inline operator Display *();
   inline bool is_null();
   inline bool is_set();

   Window default_root_window();

   int default_screen();

   Atom intern_atom(const char * pszAtomName, bool bCreate);


};

