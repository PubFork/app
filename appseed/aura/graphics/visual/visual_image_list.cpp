#include "framework.h"

#ifndef METROWIN
//#include "freeimage/Source/FreeImage.h"
#endif


image_list::image_list(::aura::application * papp) :
   ::object(papp),
   m_spdib(allocer()),
   m_spdibWork(allocer()),
   m_spdibWork2(allocer()),
   m_spdibWork3(allocer())
{
   defer_create_mutex();
   m_iSize = 0;
   m_iGrow = 1;
   m_size.cx = 0;
   m_size.cy = 0;

}


image_list::image_list(const image_list & imagelist):
   ::object(imagelist.get_app()),
   m_spdib(imagelist.allocer()),
   m_spdibWork(imagelist.allocer()),
   m_spdibWork2(imagelist.allocer()),
   m_spdibWork3(imagelist.allocer())
{
   defer_create_mutex();
   m_iSize = 0;
   m_iGrow = 1;
   m_size.cx = 0;
   m_size.cy = 0;

   operator = (imagelist);

}


image_list::~image_list()
{

}


bool image_list::create(int32_t cx, int32_t cy)
{

   return create(cx, cy, 0, 0, 0);

}


bool image_list::create(int32_t cx, int32_t cy, UINT nFlags, int32_t nInitial, int32_t nGrow)
{

   UNREFERENCED_PARAMETER(nFlags);

   if(cx <= 0)
      return false;

   if(cy <= 0)
      return false;

   if(nInitial < 0)
      return false;

   if(nGrow < 1)
      nGrow = 1;

   synch_lock sl(m_pmutex);

   m_iSize = 0;
   m_iGrow = nGrow;

   m_size.cx = cx;
   m_size.cy = cy;

   m_spdib->create(m_size.cx * m_iSize, m_size.cy);

   return true;

}


bool image_list::realize(::draw2d::graphics * pgraphics) const
{

   synch_lock sl(m_pmutex);

   return m_spdib->realize(pgraphics);

}


image_list & image_list::operator=(const image_list & imagelist)
{

   synch_lock sl(m_pmutex);

   if(this != &imagelist)
   {

      *m_spdib    = *imagelist.m_spdib;

      m_size      = imagelist.m_size;

      m_iSize     = imagelist.m_iSize;
      m_iGrow     = imagelist.m_iGrow;
      m_size      = imagelist.m_size;

   }

   return *this;

}


int32_t image_list::get_image_count() const
{

   return m_iSize;

}

bool image_list::draw(::draw2d::graphics *pgraphics, int32_t iImage, point pt, int32_t iFlag)
{

   synch_lock sl(m_pmutex);

   try
   {

      UNREFERENCED_PARAMETER(iFlag);

      return pgraphics->BitBlt(pt.x, pt.y, m_size.cx, m_size.cy, m_spdib->get_graphics(), iImage * m_size.cx, 0, SRCCOPY);

   }
   catch(...)
   {


   }

   return true;

}


bool image_list::draw(::draw2d::graphics *pgraphics, int32_t iImage, point pt, int32_t iFlag, BYTE alpha)
{

   synch_lock sl(m_pmutex);

   UNREFERENCED_PARAMETER(iFlag);

   if(alpha == 255)
      return draw(pgraphics, iImage, pt, iFlag);

   return Application.imaging().color_blend(pgraphics, pt, m_size, m_spdib->get_graphics(), point(iImage * m_size.cx, 0), alpha / 255.0);

}


bool image_list::draw(::draw2d::graphics * pgraphics, int32_t iImage, point pt, size sz, point ptOffset, int32_t iFlag)
{

   synch_lock sl(m_pmutex);

   UNREFERENCED_PARAMETER(iFlag);

   sz.cx = MIN(m_size.cx, sz.cx);
   sz.cy = MIN(m_size.cy, sz.cy);
   ptOffset.x = MIN(m_size.cx, ptOffset.x);
   ptOffset.y = MIN(m_size.cy, ptOffset.y);

   return pgraphics->BitBlt(pt.x, pt.y, sz.cx, sz.cy, m_spdib->get_graphics(), iImage * m_size.cx + ptOffset.x, ptOffset.y, SRCCOPY);

}


int32_t image_list::add_icon_os_data(void * pvoid)
{

   ::visual::icon icon(get_app(), pvoid);

   return add(&icon);

}


int32_t image_list::add(::visual::icon * picon)
{

   if (is_null(picon))
   {

      return -1;

   }

   synch_lock sl(m_pmutex);

   if (m_spdib.is_null())
   {

      if (!create(picon->m_size.cx, picon->m_size.cy))
      {

         return -1;

      }

   }

   int32_t iItem = m_iSize;

   if(iItem >= _get_alloc_count())
   {

      _grow();

   }

   ::draw2d::brush_sp brush(allocer(), RGB(192, 192, 192));

   m_spdib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

   m_spdib->get_graphics()->FillSolidRect(iItem * m_size.cx, 0, m_size.cx, m_size.cy, 0);

#ifdef METROWIN

   m_spdib->get_graphics()->DrawIcon(iItem * m_size.cx, 0, picon, m_size.cx, m_size.cy, 0, NULL, 0);

#else

   m_spdib->get_graphics()->DrawIcon(iItem * m_size.cx, 0, picon, m_size.cx, m_size.cy, 0, NULL, DI_IMAGE);

#endif

   m_iSize++;

   return iItem;

}


int32_t image_list::add_icon(const char * psz)
{

   ::visual::icon icon(get_app());

#ifdef WINDOWSEX

   int32_t iSize = MIN(m_size.cx, m_size.cy);

   icon.m_picon = (void *) (HICON) ::LoadImage(NULL, psz, IMAGE_ICON, iSize, iSize, LR_LOADFROMFILE);

#endif

   return add(&icon);

}


int32_t image_list::add_matter_icon(const char * pszMatter)
{

   return add_icon(Application.dir().matter(pszMatter));

}


int32_t image_list::add_file(const char * lpcsz)
{

   ::visual::dib_sp dib(allocer());

   if(!dib.load_from_file(lpcsz))
   {

      return -1;

   }

   synch_lock sl(m_pmutex);

   int32_t iItem = m_iSize;

   if(iItem >= _get_alloc_count())
   {

      _grow();

   }

   m_spdib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

   m_spdib->get_graphics()->BitBlt(iItem * m_size.cx, 0, m_size.cx, m_size.cy, dib->get_graphics(), 0, 0, SRCCOPY);

   m_iSize++;

   return iItem;

}


int32_t image_list::add_dib(::draw2d::dib * pdib, int x, int y)
{

   synch_lock sl(m_pmutex);

   int32_t iItem = m_iSize;

   if (iItem >= _get_alloc_count())
   {

      _grow();

   }

   m_spdib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

   m_spdib->get_graphics()->FillSolidRect(iItem * m_size.cx, 0, m_size.cx, m_size.cy, ARGB(0, 0, 0, 0));

   m_spdib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);

   m_spdib->get_graphics()->BitBlt(iItem * m_size.cx, 0, m_size.cx, m_size.cy, pdib->get_graphics(), x, y, SRCCOPY);

   m_iSize++;

   return iItem;

}


int32_t image_list::add_matter(const char * lpcsz, ::aura::application * papp)
{

   string strMatter;

   if(papp == NULL)
   {

      auto & dir = Application.dir();

      strMatter = dir.matter(lpcsz);

   }
   else
   {

      auto & dir = Sess(papp).dir();

      strMatter = dir.matter(lpcsz);

   }

   return add_file(strMatter);

}

int32_t image_list::add_image(image_list * pil, int iImage)
{

   synch_lock sl(pil->m_pmutex);

   return add_dib(pil->m_spdib, iImage * pil->m_size.cx, 0);

}

::draw2d::dib_sp image_list::get_dib(int iImage)
{

   ::draw2d::dib_sp d(allocer());

   if (d.is_null())
   {

      return NULL;

   }

   if (!d->create(m_size))
   {

      return NULL;

   }

   draw(d->get_graphics(), iImage, null_point(), 0);

   return d;

}


int32_t image_list::add_std_matter(const char * lpcsz)
{

   return add_file(Application.dir().matter(lpcsz));

}


int32_t image_list::_get_alloc_count()
{

   if(m_size.cx == 0)
   {

      return 0;

   }
   else
      return m_spdib->m_size.cx / m_size.cx;
}

bool image_list::_grow()
{
   int32_t cx = m_size.cx;
   int32_t cy = m_size.cy;

   int32_t iAllocSize = _get_alloc_count() + m_iGrow;

   if(_get_alloc_count() == 0)
   {
      m_spdib->create(cx * iAllocSize, cy);
   }
   else
   {
      ::draw2d::dib_sp spdib(allocer());
      //::draw2d::dib_sp dibAlpha(allocer());

      *spdib = *m_spdib;

      m_spdib->create(cx * iAllocSize, cy);

      m_spdib->from(point(0, 0), spdib, point(0, 0), spdib->size());

      //m_spdib->defer_realize(spdib->get_graphics());

      //m_spdib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

      //m_spdib->get_graphics()->BitBlt(0, 0, spdib->cx, spdib->cy, spdib->get_graphics(), 0, 0, SRCCOPY);

   }

   return true;
}


bool image_list::get_image_info(int32_t nImage, info * pinfo) const
{

   try
   {

      ASSERT(pinfo != NULL);

      bool bOk = true;

      if(nImage < 0 || nImage >= get_image_count())
      {

         bOk = false;

         nImage = 0;

      }

      if(bOk && m_spdib.is_null())
      {

         bOk = false;

      }

      if(bOk && const_cast < ::draw2d::dib_sp & > (m_spdib)->get_bitmap().is_null())
      {

         bOk = false;

      }

      if(bOk && const_cast < ::draw2d::dib_sp & > (m_spdib)->get_bitmap()->get_os_data() == NULL)
      {

         bOk = false;

      }

      pinfo->m_rect.left      = nImage * m_size.cx;
      pinfo->m_rect.right     = pinfo->m_rect.left + m_size.cx;
      pinfo->m_rect.top       = 0;
      pinfo->m_rect.bottom    = m_size.cy;
      pinfo->m_pdib           = ((image_list *) this)->m_spdib;

      return bOk;

   }
   catch(...)
   {

   }

   return false;

}


void image_list::remove_all()
{
   m_iSize = 0;
}
