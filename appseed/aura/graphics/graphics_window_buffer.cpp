#include "framework.h"
//#include "base/user/user.h"
//#include "graphics_window_buffer.h"

i64 oswindow_id(oswindow w);

window_buffer::window_buffer(::aura::application * papp) :
   object(papp),
   window_graphics(papp)
{

}


window_buffer::~window_buffer()
{

}

void window_buffer::on_create_window(::user::interaction_impl * pimpl)
{

   window_graphics::on_create_window(pimpl);

   m_hwnd = pimpl->m_oswindow;

}
void window_buffer::update_window()
{

   update_window(m_spdibBuffer);

}


void window_buffer::update_window(::draw2d::dib * pdib)
{

   UNREFERENCED_PARAMETER(pdib);

}

::draw2d::dib_sp & window_buffer::get_buffer()
{

   return m_spdibBuffer;

}


::draw2d::graphics * window_buffer::on_begin_draw()
{

   synch_lock sl(m_pmutex);

   if (m_spdibBuffer.is_null())
   {

      //output_debug_string("window_buffer m_spdibBuffer NULL");

      m_spdibBuffer.alloc(allocer());

   }

   if (!(m_pimpl->GetExStyle() & WS_EX_LAYERED))
   {
      rect r;
      m_pimpl->GetWindowRect(&r);
      m_pimpl->m_rectParentClientRequest = r;

   }

   if (m_cx != m_pimpl->m_rectParentClientRequest.size().cx || m_cy != m_pimpl->m_rectParentClientRequest.size().cy)
   {

      create_buffer(m_pimpl->m_rectParentClientRequest.size().cx, m_pimpl->m_rectParentClientRequest.size().cy, m_spdibBuffer->m_iScan);

   }

   if (m_spdibBuffer->host(m_pcolorref, m_iScan, abs(m_cx), abs(m_cy)))
   {

      m_bDibIsHostingBuffer = true;

   }
   else if(m_spdibBuffer->create(m_pimpl->m_rectParentClientRequest.size()))
   {

      m_bDibIsHostingBuffer = false;

   }
   else
   {

      return NULL;

   }

   return m_spdibBuffer->get_graphics();

}

   void window_buffer::defer_prepare_ipc_copy_()
   {

      if (m_hwnd == NULL || !m_pimpl->m_bIpcCopy)
      {

         return;

      }

      CHAR szName[] = "Local\\ca2screen-%d";

      string strPath;

      strPath.Format(szName, oswindow_id(m_hwnd));

      m_memorymap.open(strPath, false, true, true, 8192 * 4096 * 4);

   }


   void window_buffer::ipc_copy(int cx, int cy, COLORREF * pcolorref, int iScan)
   {

      void * pdata = m_memorymap.get_data();

      if (pdata == NULL)
      {

         return;

      }

      synch_lock sl(m_memorymap.m_pmutex);

      try
      {

         int64_t * p = (int64_t *)pdata;

         *p++ = cx;
         *p++ = cy;
         *p++ = sizeof(COLORREF) * cx;

         ::draw2d::copy_colorref(cx, cy, (COLORREF *)p, sizeof(COLORREF) * cx, pcolorref, iScan);

      }
      catch (...)
      {

      }

   }






window_double_buffer::window_double_buffer(::aura::application * papp) :
   object(papp),
   window_graphics(papp),
   window_buffer(papp),
   m_mutex2(papp),
   m_spdibBuffer2(allocer())
{

}


window_double_buffer::~window_double_buffer()
{

}


void window_double_buffer::update_window()
{

   synch_lock sl1(m_pmutex);

   synch_lock sl(&m_mutex2);

   m_spdibBuffer2->from(m_spdibBuffer);

}
