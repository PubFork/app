#include "framework.h"
#include "linux_user_impl.h"


window_xlib::window_xlib(::aura::application * papp) :
   object(papp),
   window_graphics(papp),
   window_buffer(papp)
{

   m_pdc = NULL;

   m_pimage = NULL;

}


window_xlib::~window_xlib()
{

   ::aura::del(m_pdc);

}


void window_xlib::create_window_graphics_(int64_t cxParam, int64_t cyParam, int iStrideParam)
{

   if(cxParam <= 0 || cyParam <= 0)
      return;

   destroy_window_graphics_();

   m_cx = cxParam;

   m_cy = cyParam;

   m_iScan = m_cx * sizeof(COLORREF);

   m_mem.allocate(cyParam * m_iScan);

   ::aura::del(m_pdc);

   {

        xdisplay d(m_pimpl->m_oswindow->display());

        m_pimage = XCreateImage(m_pimpl->m_oswindow->display(), m_pimpl->m_oswindow->visual(), m_pimpl->m_oswindow->m_iDepth, ZPixmap, 0, (char *) m_mem.get_data(), cxParam, cyParam, sizeof(COLORREF) * 8, m_iScan);

        XGCValues gcvalues;

        m_pdc = new device_context();

        m_pdc->m_gc = XCreateGC(m_pimpl->m_oswindow->display(), m_pimpl->m_oswindow->window(), 0, &gcvalues);

   }

   m_pdc->m_pdisplay = m_pimpl->m_oswindow->display();

   defer_prepare_ipc_copy_();

   window_graphics::create_window_graphics_(cxParam, cyParam, m_iScan);

}



void window_xlib::destroy_window_graphics_()
{

   window_graphics::destroy_window_graphics_();


}


void window_xlib::update_window(::draw2d::dib * pdib)
{

   if(pdib == NULL)
   {

      return;

   }

   synch_lock sl(m_pmutex);

   pdib->map();

   if(pdib->m_pcolorref == NULL)
   {

      return;

   }

   if(m_pdc == NULL)
   {

      return;

   }

   if(m_pimpl == NULL)
   {

      return;

   }

   if(m_pimpl->m_oswindow == NULL)
   {

      return;

   }

   if(m_pimage == NULL)
   {

      return;

   }

   if(m_cx <= 0)
   {

      return;

   }

   if(m_cy <= 0)
   {

      return;

   }

   int cx = MIN(pdib->m_size.cx, m_cx);

   int cy = MIN(pdib->m_size.cy, m_cy);

   ::draw2d::copy_colorref(cx, cy, (COLORREF *) m_mem.get_data(), m_iScan, pdib->m_pcolorref, pdib->m_iScan);

   byte * pdata = (byte *) m_mem.get_data();

   m_pcolorref = (COLORREF *) pdata;

   int size = m_iScan * m_cy;

   byte * pb = pdata + size - 4;

   int sizeB = (size / 16) * 16;

   byte * pbB = pdata + (size - sizeB);

   while(pb >= pbB)
   {

      pb[0] = (byte) ((pb[0] * pb[3]) >> 8);
      pb[1] = (byte) ((pb[1] * pb[3]) >> 8);
      pb[2] = (byte) ((pb[2] * pb[3]) >> 8);
      pb[4] = (byte) ((pb[4] * pb[7]) >> 8);
      pb[5] = (byte) ((pb[5] * pb[7]) >> 8);
      pb[6] = (byte) ((pb[6] * pb[7]) >> 8);
      pb[8] = (byte) ((pb[8] * pb[11]) >> 8);
      pb[9] = (byte) ((pb[9] * pb[11]) >> 8);
      pb[10] = (byte) ((pb[10] * pb[11]) >> 8);
      pb[12] = (byte) ((pb[12] * pb[15]) >> 8);
      pb[13] = (byte) ((pb[13] * pb[15]) >> 8);
      pb[14] = (byte) ((pb[14] * pb[15]) >> 8);
      pb -= 16;

   }

   while(pb >= pdata)
   {

      pb[0] = (byte) ((pb[0] * pb[3]) >> 8);
      pb[1] = (byte) ((pb[1] * pb[3]) >> 8);
      pb[2] = (byte) ((pb[2] * pb[3]) >> 8);
      pb -= 4;

   }

   try
   {

      xdisplay d(m_pimpl->m_oswindow->display());

      XPutImage(m_pimpl->m_oswindow->display(), m_pimpl->m_oswindow->window(), m_pdc->m_gc, m_pimage, 0, 0, 0, 0, cx, cy);

   }
   catch(...)
   {

   }

      if (m_pimpl->m_bIpcCopy)
      {

         ipc_copy(cx, cy, pdib->m_pcolorref, pdib->m_iScan);

      }

}


::draw2d::graphics * window_xlib::on_begin_draw()
{

   if (m_spdibBuffer.is_null())
   {

      m_spdibBuffer.alloc(allocer());

   }

   if(!m_spdibBuffer->create(m_pimpl->m_rectParentClient.size()))
   {

      return NULL;

   }

   if (m_cx != m_pimpl->m_rectParentClient.size().cx || m_cy != m_pimpl->m_rectParentClient.size().cy)
   {

      create_window_graphics_(m_pimpl->m_rectParentClient.size().cx, m_pimpl->m_rectParentClient.size().cy, m_spdibBuffer->m_iScan);

   }

   return m_spdibBuffer->get_graphics();

}

