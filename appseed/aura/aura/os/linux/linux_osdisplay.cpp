
#include "framework.h"
#include "linux_user_impl.h"

Display * x11_get_display();

#define CA2_X11_WINDOW_LONG "ca2_ccvotagus_window_long"
#define CA2_X11_WINDOW_LONG_STYLE "ca2_ccvotagus_window_long_style"
#define CA2_X11_WINDOW_LONG_STYLE_EX "ca2_ccvotagus_window_long_style_ex"


void windowing_output_debug_string(const char * pszDebugString);


osdisplay_dataptra * osdisplay_data::s_pdataptra = NULL;
mutex * osdisplay_data::s_pmutex = NULL;


osdisplay_data::osdisplay_data()
{

   m_pcsOsDisplayData      = new critical_section();
   m_pdisplay              = NULL;
   m_atomLongType          = None;
   m_atomLongStyle         = None;
   m_atomLongStyleEx       = 0;
   m_countReference        = 1;
   m_pmutexInput           = new mutex();

}


osdisplay_data::~ osdisplay_data()
{

   ::aura::del(m_pmutexInput);

   ::aura::del(m_pcsOsDisplayData);

}


int32_t osdisplay_find(Display * pdisplay)
{

   single_lock slOsWindow(::osdisplay_data::s_pmutex, true);

   for(int32_t i = 0; i < osdisplay_data::s_pdataptra->get_count(); i++)
   {
      if(osdisplay_data::s_pdataptra->element_at(i)->m_pdisplay == pdisplay)
      {
         return i;
      }
   }

   return -1;

}


void __axis_x11_thread(osdisplay_data * pdisplaydata);

void __axis_x11_input_thread(osdisplay_data * pdisplaydata);

osdisplay_data * osdisplay_get(Display * pdisplay)
{

   if(pdisplay == NULL)
   {

      return NULL;

   }

   single_lock slOsWindow(::osdisplay_data::s_pmutex, true);

   int_ptr iFind = osdisplay_find(pdisplay);

   if(iFind >= 0)
   {

      return osdisplay_data::s_pdataptra->element_at(iFind);

   }

   osdisplay_data * pdata     = new osdisplay_data;

   pdata->m_pdisplay          = pdisplay;
   pdata->m_atomLongType      = XInternAtom(pdisplay, CA2_X11_WINDOW_LONG            , False);
   pdata->m_atomLongStyle     = XInternAtom(pdisplay, CA2_X11_WINDOW_LONG_STYLE      , False);
   pdata->m_atomLongStyleEx   = XInternAtom(pdisplay, CA2_X11_WINDOW_LONG_STYLE_EX   , False);

   ::osdisplay_data::s_pdataptra->add(pdata);

   if(!::aura::system::g_p->m_pappcore->m_pmaindata->m_bGtkApp)
   {

      ::aura::system::g_p->fork([pdata]()
      {

         __axis_x11_thread(pdata);

      });

      ::aura::system::g_p->fork([pdata]()
      {

         __axis_x11_input_thread(pdata);

      });

   }

   return pdata;

}



bool osdisplay_remove(Display * pdisplay)
{

   single_lock slOsWindow(::osdisplay_data::s_pmutex, true);

   int_ptr iFind = osdisplay_find(pdisplay);

   if(iFind < 0)
      return false;

   osdisplay_data * pdata = ::osdisplay_data::s_pdataptra->element_at(iFind);

   XCloseDisplay(pdata->m_pdisplay);

   ::osdisplay_data::s_pdataptra->remove_at(iFind);

   return true;

}


Atom osdisplay_data::get_window_long_atom(int32_t nIndex)
{

   if(::is_null(this))
      return 0;

   switch(nIndex)
   {
   case GWL_STYLE:

      return m_atomLongStyle;

   case GWL_EXSTYLE:

      return m_atomLongStyleEx;

   default:
      {

         string strProperty;

         strProperty = CA2_X11_WINDOW_LONG + itoa_dup(nIndex);

         return XInternAtom(m_pdisplay, strProperty, False);

      }
   }

}


Atom osdisplay_data::intern_atom(const char * pszAtomName, bool bCreate)
{

   if(m_pdisplay == NULL)
   {

      return 0;

   }

   return XInternAtom(m_pdisplay, pszAtomName, bCreate ? True : False);

}


Window osdisplay_data::default_root_window()
{

   if(m_pdisplay == NULL)
   {

      return None;

   }

   return DefaultRootWindow(m_pdisplay);

}
