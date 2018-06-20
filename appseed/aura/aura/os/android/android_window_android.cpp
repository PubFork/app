#include "framework.h"
#include "android_window_android.h"


window_android::window_android(::aura::application * papp) :
   ::window_graphics(papp)
{

   //m_cairoSource = NULL;
   //m_cairosurfaceSource = NULL;

}


window_android::~window_android()
{

}


void window_android::create_window_graphics_(int64_t cxParam,int64_t cyParam,int iStrideParam)
{

   destroy_window_graphics_();


   synch_lock sl(m_pmutex);

   //if(m_cairoSource != NULL)
   //{
   //   cairo_destroy(m_cairoSource);

   //}

   //if(m_cairosurfaceSource != NULL)
   //{

   //   cairo_surface_destroy(m_cairosurfaceSource);

   //}

   //int32_t iStride = cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, cxParam);

   int32_t iStride = iStrideParam;

   //m_mem.allocate(iStride * cyParam);

   //m_cairosurfaceSource = cairo_image_surface_create_for_data((unsigned char *) m_mem.get_data(), CAIRO_FORMAT_ARGB32, cxParam, cyParam, iStride);

   //m_cairoSource = cairo_create(m_cairosurfaceSource);

   ::window_graphics::create_window_graphics_(cxParam, cyParam, iStride);

}





void window_android::destroy_window_graphics_()
{

   ::window_graphics::destroy_window_graphics_();


}


void window_android::update_window(oswindow interaction_impl, COLORREF * pOsBitmapData, const RECT & rect, int iStride)
{

   ::draw2d::copy_colorref(width(rect), height(rect), (COLORREF *) m_mem.get_data(), width(rect) * 4, pOsBitmapData, iStride);

}



