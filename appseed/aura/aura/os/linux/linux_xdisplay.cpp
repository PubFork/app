
xdisplay::xdisplay()
{

   m_pdata           = NULL;
   m_bOwn            = false;
   m_bLocked         = false;

}


xdisplay::xdisplay(Display * pdisplay, bool bInitialLock)
{

   m_pdata     = osdisplay_get(pdisplay);
   m_bOwn        = false;
   m_bLocked     = false;




   if(bInitialLock)
        lock();

}


bool xdisplay::open(char * display_name, bool bInitialLock)
{

   unlock();

   close();

   Display * pdisplay = x11_get_display();

   if(pdisplay == NULL)
      return false;

   m_pdata = osdisplay_get(pdisplay);

   if(m_pdata == NULL)
      return false;

   m_pdata->add_ref();

   m_bOwn = true;

   if(bInitialLock)
      lock();

   return true;

}


bool xdisplay::close()
{

   if(!m_bOwn || m_pdata == NULL || m_pdata->m_pdisplay == NULL)
      return false;

   if(m_bLocked)
      unlock();

   m_pdata->release();

   m_pdata = NULL;

   m_bOwn = false;

   return true;

}

xdisplay::~ xdisplay()
{

   unlock();

   close();

}


void xdisplay::lock()
{

   if(m_pdata == NULL || m_bLocked)
      return;

   m_pdata->m_pmutex->lock();

   m_bLocked = true;

   XLockDisplay(m_pdata->m_pdisplay);

}

void xdisplay::unlock()
{

   if(m_pdata == NULL || !m_bLocked)
      return;

   m_pdata->m_pmutex->unlock();

   XUnlockDisplay(m_pdata->m_pdisplay);

   m_bLocked = false;

}




Window xdisplay::default_root_window()
{

   if(m_pdata == NULL)
      return None;

   return DefaultRootWindow(m_pdata->m_pdisplay);

}


int xdisplay::default_screen()
{

   if(m_pdata == NULL)
      return None;

   return DefaultScreen(m_pdata->m_pdisplay);

}
