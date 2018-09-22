#pragma once


// define portable types for 32-bit / 64-bit OS
//typedef int32_t WINBOOL;
typedef uint8_t BYTE;
//typedef uint16_t WORD;
typedef uint32_t DWORD;
//typedef int32_t LONG;


#undef FAR
#undef  NEAR
#define FAR
#define NEAR
#ifndef CONST
#define CONST               const
#endif


struct hthread;

namespace ca2
{


   class thread_base;


} // namespace ca2


//class oswindow_data;


//typedef oswindow_data * oswindow;



namespace user
{


   class interaction;
   class interaction;


} // namespace user


class oswindow_dataptra;


class event;


class mutex;


class oswindow_data;


CLASS_DECL_AURA int32_t oswindow_find_message_only_window(::user::interaction_impl * puibaseMessageWindow);
CLASS_DECL_AURA int32_t oswindow_find(Display * pdisplay, Window window);
CLASS_DECL_AURA int32_t oswindow_find(Window window);
CLASS_DECL_AURA oswindow_data * oswindow_get_message_only_window(::user::interaction_impl * puibaseMessageWindow);
CLASS_DECL_AURA oswindow_data * oswindow_get(Display * pdisplay, Window window, Visual * pvisual = NULL, int iDepth = -1, int iScreen = -1, Colormap colormap = None);
CLASS_DECL_AURA oswindow_data * oswindow_get(Window window);
CLASS_DECL_AURA oswindow_data * oswindow_defer_get(Display * pdisplay, Window window);
CLASS_DECL_AURA oswindow oswindow_defer_get(Window w);
CLASS_DECL_AURA bool oswindow_remove(Display * pdisplay, Window window);
CLASS_DECL_AURA bool oswindow_remove_message_only_window(::user::interaction_impl * puibaseMessageOnlyWindow);


struct hthread;

namespace ca2
{


   class thread_base;


} // namespace ca2


//class oswindow_data;


//typedef oswindow_data * oswindow;



namespace user
{


   class interaction;
   class interaction;


} // namespace user


class oswindow_dataptra;


class simple_event;


class mutex;


class CLASS_DECL_AURA oswindow_data
{
public:


   osdisplay                     m_osdisplay;
   Window                        m_window;
   Visual                        m_visual;
   int                           m_iDepth;
   int                           m_iScreen;
   bool                          m_bMessageOnlyWindow;
   ::user::interaction_impl *    m_pimpl;
   HTHREAD                       m_hthread;
   //int_ptr_to_int_ptr *          m_plongptrmap;
   Colormap                      m_colormap;
   DWORD                         m_dwLastMouseMove;
   Window                        m_parent;
   RECT64                        m_rect;
   bool                          m_bHasFocus;
   point                         m_ptCursor;


   //ref_array < bool >            m_bptraTellMeDestroyed; // Telmo why!! :-)


   static oswindow_dataptra * s_pdataptra;
   static mutex * s_pmutex;

   static Atom s_atomLongType;
   static Atom s_atomLongStyle;
   static Atom s_atomLongStyleEx;

   static Atom get_window_long_atom(int32_t nIndex);




   oswindow_data();
   //oswindow_data(::user::interaction * puibaseMessageOnlyWindow);
   //oswindow_data(const void * p);
   //oswindow_data(const LPARAM & lparam);
   //oswindow_data(const WPARAM & wparam);


   ~oswindow_data();



   operator void * ()
   {
      return this;
   }

   operator void * () const
   {
      return (void *) this;
   }

   oswindow_data & operator = (const oswindow_data & window);

   bool operator == (const void * p) const
   {
      return this == p;
   }

   bool operator != (const void * p) const
   {
      return this != p;
   }

   Display * display()
   {
      return ::is_null(this) ? NULL : m_osdisplay->display();
   }

   Display * display() const
   {
      return ::is_null(this) ? NULL : m_osdisplay->display();
   }

   Window window()
   {
      return ::is_null(this) ? None : m_window;
   }

   Window window() const
   {
      return ::is_null(this) ? None : m_window;
   }

   Visual * visual()
   {
      return ::is_null(this) ? NULL : &m_visual;
   }

   Visual * visual() const
   {
      return ::is_null(this) ? NULL : (Visual *) &m_visual;
   }

   Window root_window_raw() const
   {
      return ::is_null(this) || ::is_null(m_osdisplay) ? None : RootWindow(display(), m_iScreen);
   }

   void send_client_event(Atom atom, unsigned int numArgs, ...);
   int32_t store_name(const char * psz);
   int32_t select_input(int32_t iInput);
   int32_t select_all_input();
   int32_t map_window();
   int32_t unmap_window(bool bWithdraw);

   void full_screen(LPCRECT lpcrect = null_rect());
   void exit_full_screen();

   void set_user_interaction(::user::interaction_impl * pui);


   void post_nc_destroy();


   bool is_child(oswindow oswindowcandidateChildOrDescendant); // or descendant
   oswindow get_parent();
   Window get_parent_handle();

   oswindow set_parent(oswindow oswindowNewParent);
   long get_state();
   bool is_iconic();
   bool is_window_visible();
   bool show_window(int32_t nCmdShow);
   LONG_PTR get_window_long_ptr(int32_t nIndex);
   LONG_PTR set_window_long_ptr(int32_t nIndex, LONG_PTR l);
   bool client_to_screen(LPPOINT lppoint);
   bool screen_to_client(LPPOINT lppoint);

   Atom intern_atom(const char * pszAtomName, bool bCreate);

   bool is_null() const
   {
      return ::is_null(this);
   }

   bool set_window_pos(oswindow hwndInsertAfter, int32_t x, int32_t y, int32_t cx, int32_t cy, UINT nFlags);

   bool is_destroying();

   bool bamf_set_icon();

   bool set_icon(::draw2d::dib * pdib);

   int x_change_property(Atom property, Atom type, int format, int mode, const unsigned char * data, int nelements);

};

class oswindow_dataptra :
   public pointer_array < oswindow_data * >
{
public:

   virtual ~oswindow_dataptra()
   {

         remove_all();

   }

   void remove_all()
   {

      for(auto p : *this)
      {

         delete p;

      }

      pointer_array < oswindow_data * >::remove_all();
   }

};

extern oswindow g_oswindowDesktop;
