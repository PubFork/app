//
//  ios_window.h
//  base
//
//  Created by Camilo Sasuke Tsumanuma on 2013-09-17.
//
//
#pragma once


#ifdef __MM

typedef void * int_to_int;

#else

struct UIWindow;

#endif

typedef UIWindow * nswindow;


namespace user
{
   
   
   class interaction;
   class interaction;
   
   
} // namespace user



class CLASS_DECL_AURA oswindow_data
{
public:
   
   
   nswindow                      m_nswindow;
   ::user::interaction_impl *    m_pimpl;
   
   
   int_to_int *                  m_plongmap;
   
   
   oswindow_data();
   oswindow_data(nswindow window);
   oswindow_data(const oswindow_data & oswindow);
   ~oswindow_data();
   
   
   operator void * ()
   {
      
      return this;
      
   }
   
   operator void * () const
   {
      
      return (void *) this;
      
   }
   
#ifdef __MM
   
   operator ::nswindow ()
   {
      return window();
   }
   
#endif
   
   oswindow_data & operator = (const oswindow_data & window);
   
   bool operator == (const void * p) const
   {
      return this == p;
   }
   bool operator != (const void * p) const
   {
      return this != p;
   }
   
   nswindow window()
   {
      return is_null() ? NULL : m_nswindow;
   }
   
   
   void set_user_interaction_impl(::user::interaction_impl * pimpl);
   ::user::interaction_impl * get_user_interaction_impl();
   ::user::interaction_impl * get_user_interaction_impl() const;
   ::user::interaction * get_user_interaction();
   ::user::interaction * get_user_interaction() const;
   
   
   void post_nc_destroy();
   
   
   bool is_child(oswindow oswindowCandidateChildOrDescendant); // or descendant
   oswindow get_parent();
   oswindow set_parent(oswindow oswindowNewParent);
   long get_state();
   bool is_iconic();
   bool is_window_visible();
   bool show_window(int32_t nCmdShow);
   int32_t get_window_long(int32_t nIndex);
   int32_t set_window_long(int32_t nIndex, int32_t l);
   bool client_to_screen(POINT * lppoint);
   bool screen_to_client(POINT * lppoint);
   
   bool is_null() const
   {
      
      return ::is_null(this);
      
   }
   
};





int oswindow_find(nswindow window);
oswindow_data * oswindow_get(nswindow window);
bool oswindow_remove(nswindow window);


int IsWindow(oswindow oswindow);
int IsChild(oswindow oswindowParent, ::oswindow oswindowCandidateChildOrDescendant);
oswindow GetParent(::oswindow oswindow);
oswindow SetParent(::oswindow oswindow, ::oswindow oswindowNewParent);
int ShowWindow(::oswindow oswindow, int32_t nCmdShow);
int32_t GetWindowLongA(::oswindow oswindow, int32_t nIndex);
int32_t SetWindowLongA(::oswindow oswindow, int32_t nIndex, int32_t l);
int ClientToScreen(::oswindow oswindow, POINT * lppoint);
int ScreenToClient(::oswindow oswindow, POINT * lppoint);
int32_t IsIconic(::oswindow oswindow);
int32_t IsWindowVisible(::oswindow oswindow);


#define GetWindowLong GetWindowLongA
#define SetWindowLong SetWindowLongA





