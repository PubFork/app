#include "framework.h"

#ifdef WINDOWS
#include <wincodec.h>
#include <ShCore.h>
//#elif defined(METROWIN)
//#include <ShCore.h>
#endif





namespace visual
{

   dib_sp::pointer::pointer()
   {

      m_dwTime = 0;

   }

   dib_sp::pointer::~pointer()
   {


   }


   dib_sp::array::array(::aura::application * papp) :
      object(papp)
   {

      m_uiLoop = 0;
      m_uiLoopCount = 0;
      m_bStart = false;
      m_iLastFrame = -1;

   }

   dib_sp::array::~array()
   {

   }




   dib_sp::dib_sp()
   {
      m_eload = load_none;
      m_dSpeed = 1.0;


   }


   dib_sp::dib_sp(const ::aura::allocatorsp & allocer) :
      ::draw2d::dib_sp(allocer)
   {
      m_eload = load_none;
      m_dSpeed = 1.0;


   }


   dib_sp::~dib_sp()
   {
      if (m_sparray.is_set())
      {

         if (m_sparray->pred_find_first([&](auto & i) { return i->m_dib.m_p == m_p; }) >= 0)
         {
            m_p = NULL;
         }

      }
   }

   bool dib_sp::load_thumbnail(var varFile, int w, int h)
   {

#ifdef WINDOWS

      if (!m_p->create(w, h))
      {
         return false;
      }

      if (!m_p->load_thumbnail(varFile))
      {

         return false;

      }


      return true;

#else

      todo(get_app());

      return false;

#endif


   }

   bool dib_sp::load_from_file(var varFile, bool bCache, bool bCreateHelperMaps)
   {

      auto * pdib = varFile.cast<::draw2d::dib>();

      if (pdib != NULL)
      {

         ::draw2d::dib_sp::operator =(pdib);

         return true;

      }

      if (varFile.is_empty())
      {

         m_eload = load_fail;

         return false;

      }

      if (varFile.get_file_path().extension().compare_ci("svg") == 0
            || varFile.get_file_path().find_ci(".svg?") > 0)
      {

         m_p->create_nanosvg(App(m_p->m_pauraapp).file().as_string(varFile));

         m_eload = load_ok;

         if (bCreateHelperMaps)
         {

            m_p->create_helper_map();

         }

         return true;

      }

      if (varFile.get_file_path().extension().compare_ci("gif") == 0
            || varFile.get_file_path().find_ci(".gif?") > 0)
      {

         m_sparray = canew(array(m_p->m_pauraapp));

         if (!App(m_p->m_pauraapp).imaging().load_from_file(m_sparray, varFile, bCache))
         {

            m_sparray.release();

            m_eload = load_fail;

            return false;

         }

         if (!m_p->create(m_sparray->m_size))
         {

            m_sparray.release();

            m_eload = load_fail;

            return false;

         }

         if (bCreateHelperMaps)
         {

            for (auto & p : *m_sparray)
            {

               p->m_dib->create_helper_map();

            }

         }

         m_eload = load_ok;

         return true;

      }

      if (!App(m_p->m_pauraapp).imaging().load_from_file(m_p, varFile, bCache))
      {

         m_eload = load_fail;

         return false;

      }

      if (bCreateHelperMaps)
      {

         m_p->create_helper_map();

      }

      m_p->on_load_image();

      m_eload = load_ok;

      return true;

   }


   bool dib_sp::load_from_matter(const char * pszMatter, bool bCache, bool bCreateHelperMaps)
   {

      ::file::path path = m_p->m_pauraapp->dir().matter(pszMatter);
      
      ::draw2d::dib_sp dib(m_p->allocer());

      if (!App(m_p->m_pauraapp).imaging().load_from_file(dib, path, bCache))
      {

         m_eload = load_fail;

         return false;

      }

      if (bCreateHelperMaps)
      {

         dib->create_helper_map();

      }
      
      operator = (dib);

      m_eload = load_ok;

      return true;

   }


   bool dib_sp::read_from_file(::file::file_sp spfile)
   {

      if (!App(m_p->m_pauraapp).imaging().LoadImageFromFile(m_p, spfile))
      {

         m_eload = load_fail;

         return false;

      }

      m_eload = load_ok;

      return true;

   }


   bool dib_sp::save_to_file(var varFile, save_image * psaveimage)
   {

      return write_to_file(varFile, psaveimage);

   }


   save_image::save_image()
   {

      m_eformat = ::visual::image::format_png;

      m_iQuality = 100;

   }


   bool dib_sp::load_matter_icon(stringa & straMatter, string strIcon)
   {

      ::file::path path;

      for (auto & strMatter : straMatter)
      {

         path = strMatter;

         path = App(m_p->get_app()).dir().matter(path / strIcon);

         if(load_from_file(path))
         {

            return true;

         }

      }

      return false;

   }


//#ifndef  WINDOWS
//
//   bool dib_sp::from(class draw2d::graphics * pgraphics, struct FIBITMAP * pfi, bool bUnload)
//   {
//
//      return App(m_p->m_pauraapp).imaging().from(m_p, pgraphics, pfi, bUnload);
//
//   }
//
//#endif

   /*::size dib_sp::size()
   {

      if (m_sparray.is_set() && m_sparray->get_count() > 0 && m_sparray->m_dwTotal > 0)
      {

         return m_sparray->m_size;

      }

      return m_p->size();

   }*/


   void dib_sp::defer_update()
   {

      if (m_sparray.is_set() && m_sparray->get_count() > 0 && m_sparray->m_dwTotal > 0)
      {

         if (m_sparray->get_count() == 1)
         {

            m_p = m_sparray->element_at(0)->m_dib.m_p;

            return;

         }

         if (!m_sparray->m_bStart)
         {

            m_sparray->m_bStart = true;

            m_sparray->m_dwStart = get_tick_count();

         }

         DWORD dwTime = (DWORD) (((double)(get_tick_count()) - m_sparray->m_dwStart)  * m_dSpeed);

         UINT uiLoop = dwTime / m_sparray->m_dwTotal;

         if (uiLoop > m_sparray->m_uiLoop)
         {

            m_sparray->m_uiLoop = uiLoop;

            m_sparray->m_iLastFrame = -1;

         }

         index iCurrentFrame = 0;

         if (m_sparray->m_uiLoopCount == 0 || m_sparray->m_uiLoop < m_sparray->m_uiLoopCount)
         {

            dwTime %= m_sparray->m_dwTotal;

            DWORD dwT = 0;

            for (index i = 0; i < m_sparray->get_count(); i++)
            {

               dwT += m_sparray->element_at(i)->m_dwTime;

               if (dwTime < dwT)
               {

                  iCurrentFrame = i;

                  break;

               }

            }

         }

         if (m_sparray->m_iLastFrame != iCurrentFrame)
         {

            m_sparray->m_iLastFrame = iCurrentFrame;

            m_p = m_sparray->element_at(iCurrentFrame)->m_dib.m_p;

         }

      }

   }

   bool dib_sp::pointer::to(::draw2d::graphics * pgraphics)
   {


      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      if (!m_dib->to(pgraphics, m_rect.top_left(), m_rect.get_size()))
      {

         return false;

      }

      return true;

   }

   bool dib_sp::dispose_current_frame()
   {

      if (m_sparray->m_dibCompose.is_null())
      {

         m_sparray->m_dibCompose.alloc(m_p->allocer());

         m_sparray->m_dibCompose->create(m_sparray->m_size);

         m_sparray->m_dibCompose->Fill(m_sparray->m_crBack);

      }
      else
      {

         m_sparray->m_dibCompose->create(m_sparray->m_size);

      }


      if (m_sparray->m_iLastFrame < 0)
      {

         // Draw background and increase loop count
         m_sparray->m_dibCompose->Fill(m_sparray->m_crBack);

         return false;

      }

      //bool bOk = true;


      switch (m_sparray->element_at(m_sparray->m_iLastFrame)->m_edisposal)
      {
      case dib_sp::pointer::disposal_undefined:
      case dib_sp::pointer::disposal_none:
      {
         COLORREF crBack = m_sparray->m_crBack;

         // We simply draw on the previous frames. Do nothing here.
         m_sparray->m_dibCompose->get_graphics()->fill_solid_rect(m_sparray->element_at(m_sparray->m_iLastFrame)->m_rect, crBack);

      }
      break;
      case dib_sp::pointer::disposal_background:
      {
         // Dispose background
         // Clear the area covered by the current raw frame with background color
         m_sparray->m_dibCompose->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);
         COLORREF crBack = m_sparray->m_crBack;
         //byte bAlpha = argb_get_a_value(crBack);

         m_sparray->m_dibCompose->get_graphics()->fill_solid_rect(m_sparray->element_at(m_sparray->m_iLastFrame)->m_rect, crBack);
      }
      break;
      case dib_sp::pointer::disposal_previous:
         // Dispose previous
         // We restore the previous composed frame first
         //hr = RestoreSavedFrame();
         break;
      default:
         // Invalid disposal method
         return false;
      }

      return true;
   }

   bool dib_sp::overlay_frame(int iFrame)
   {

      //// If starting a new animation loop
      //if (iFrame <= 0)
      //{

      //}

      // Produce the next frame
      if (!m_sparray->element_at(iFrame)->to(m_sparray->m_dibCompose->get_graphics()))
      {

         return false;

      }

      m_p->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

      m_p->get_graphics()->BitBlt(0, 0, m_p->m_size.cx, m_p->m_size.cy,
                                  m_sparray->m_dibCompose->get_graphics());




      return true;

   }


   bool dib_sp::write_to_file(var varFile, save_image * psaveimage)
   {

      if(m_p == NULL)
      {

         return false;

      }

      return App(m_p->get_app()).imaging().save_image(varFile, m_p, psaveimage);

   }

} // namespace visual


#if 0


CLASS_DECL_AURA void draw_freetype_bitmap(::draw2d::dib * m_p, int32_t dx, int32_t dy, void * pftbitmap, int xParam, int yParam)
{

   FT_Bitmap * bitmap = (FT_Bitmap *)pftbitmap;
   FT_Int x = (FT_Int)xParam;
   FT_Int y = (FT_Int)yParam;

   FT_Int  i, j, p, q;
   FT_Int  x_max = x + bitmap->width;
   FT_Int  y_max = y + bitmap->rows;

   m_p->map();

   for (i = x, p = 0; i < x_max; i++, p++)
   {
      for (j = y, q = 0; j < y_max; j++, q++)
      {
         if (i < 0 || j < 0 || i >= m_p->m_size.cx || j >= m_p->m_size.cy)
            continue;

         int32_t a = bitmap->buffer[q * bitmap->width + p];

         *((COLORREF *)&((byte *)m_p->get_data())[(dy + j) * m_p->m_iScan + (dx + i) * 4]) = ARGB(a, 0, 0, 0);

      }
   }

}


CLASS_DECL_AURA void draw_freetype_bitmap(::draw2d::dib * m_p, int32_t dx, int32_t dy, void * pftbitmap, int xParam, int yParam, byte aParam, byte r, byte g, byte b)
{

   FT_Bitmap * bitmap = (FT_Bitmap *)pftbitmap;
   FT_Int x = (FT_Int)xParam;
   FT_Int y = (FT_Int)yParam;

   FT_Int  i, j, p, q;
   FT_Int  x_max = x + bitmap->width;
   FT_Int  y_max = y + bitmap->rows;

   m_p->map();

   for (i = x, p = 0; i < x_max; i++, p++)
   {
      for (j = y, q = 0; j < y_max; j++, q++)
      {
         if (i < 0 || j < 0 || i >= m_p->m_size.cx || j >= m_p->m_size.cy)
            continue;

         int32_t a = bitmap->buffer[q * bitmap->width + p];

         if (a > 0)
         {

            *((COLORREF *)&((byte *)m_p->get_data())[(dy + j) * m_p->m_iScan + (dx + i) * 4]) = ARGB(a * aParam / 255, r, g, b);

         }
         else
         {

            *((COLORREF *)&((byte *)m_p->get_data())[(dy + j) * m_p->m_iScan + (dx + i) * 4]) = 0;

         }

      }
   }

}

#endif




