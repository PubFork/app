#include "framework.h"


window_android::window_android()
{

   m_cairoSource = NULL;
   m_cairosurfaceSource = NULL;

}


window_android::~window_android()
{

}


void window_android::create(oswindow window, int64_t cxParam, int64_t cyParam, int iStrideParam)
{

   destroy();


   mutex_lock sl(user_mutex(), true);

   if(m_cairoSource != NULL)
   {
      cairo_destroy(m_cairoSource);

   }

   if(m_cairosurfaceSource != NULL)
   {

      cairo_surface_destroy(m_cairosurfaceSource);

   }

   int32_t iStride = cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, cxParam);

   m_mem.allocate(iStride * cyParam);

   m_cairosurfaceSource = cairo_image_surface_create_for_data((unsigned char *) m_mem.get_data(), CAIRO_FORMAT_ARGB32, cxParam, cyParam, iStride);

   m_cairoSource = cairo_create(m_cairosurfaceSource);

   window_graphics::create(window, cxParam, cyParam, iStride);

}





void window_android::destroy()
{

   window_graphics::destroy();


}


void window_android::update_window(oswindow window, COLORREF * pOsBitmapData, LPCRECT lpcrect, int iStride)
{


   copy_colorref((COLORREF *) m_mem.get_data(), pOsBitmapData, iStride);


}



