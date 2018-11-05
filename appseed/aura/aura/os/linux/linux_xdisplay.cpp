

xdisplay::xdisplay()
{

   m_pdata           = NULL;

   m_bOwn            = false;

   m_bLocked         = false;

}


xdisplay::xdisplay(Display * pdisplay, bool bInitialLock)
{

   m_pdata        = osdisplay_get(pdisplay);

   m_bOwn         = false;

   m_bLocked      = false;

   if(bInitialLock)
   {

      lock();

   }

}


xdisplay::~ xdisplay()
{

   unlock();

   close();

}


bool xdisplay::open(char * display_name, bool bInitialLock)
{

   unlock();

   close();

   Display * pdisplay = x11_get_display();

   if(pdisplay == NULL)
   {

      return false;

   }

   m_pdata = osdisplay_get(pdisplay);

   if(m_pdata == NULL)
   {

      return false;

   }

   m_pdata->add_ref();

   m_bOwn = true;

   if(bInitialLock)
   {

      lock();

   }

   return true;

}


bool xdisplay::close()
{

   if(!m_bOwn || m_pdata == NULL || m_pdata->m_pdisplay == NULL)
   {

      return false;

   }

   if(m_bLocked)
   {

      unlock();

   }

   m_pdata->release();

   m_pdata = NULL;

   m_bOwn = false;

   return true;

}


bool b_prevent_xdisplay_lock_log = false;


void xdisplay::lock()
{

   if(m_pdata == NULL || m_bLocked)
   {

      return;

   }

   if(!b_prevent_xdisplay_lock_log)
   {

      windowing_output_debug_string("\nxdisplay::lock x1");

   }

   m_pdata->m_pcsOsDisplayData->lock();

   if(!b_prevent_xdisplay_lock_log)
   {

      windowing_output_debug_string("\nxdisplay::lock x2");

   }

   m_bLocked = true;

   XLockDisplay(m_pdata->m_pdisplay);

   if(!b_prevent_xdisplay_lock_log)
   {

      windowing_output_debug_string("\nxdisplay::lock x3");

   }

}


void xdisplay::unlock()
{

   if(m_pdata == NULL || !m_bLocked)
   {

      return;

   }

   if(!b_prevent_xdisplay_lock_log)
   {

      windowing_output_debug_string("\nxdisplay::unlock");

   }

   m_pdata->m_pcsOsDisplayData->unlock();

   XUnlockDisplay(m_pdata->m_pdisplay);

   m_bLocked = false;

}


Window xdisplay::default_root_window()
{

   if(m_pdata == NULL)
   {

      return None;

   }

   return m_pdata->default_root_window();

}


int xdisplay::default_screen()
{

   if(m_pdata == NULL)
   {

      return None;

   }

   return DefaultScreen(m_pdata->m_pdisplay);

}


Atom xdisplay::intern_atom(const char * pszAtomName, bool bCreate)
{

   if(m_pdata == NULL)
   {

      return 0;

   }

   return m_pdata->intern_atom(pszAtomName, bCreate);

}

