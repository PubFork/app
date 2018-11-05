#include "framework.h"


namespace html
{


   namespace impl
   {


      void image::_001OnDraw(data * pdata)
      {

         ::draw2d::graphics * pgraphics = pdata->m_pgraphics;

         if (m_pelemental->m_pbase->get_type() == ::html::base::type_tag)
         {

            pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

            pdata->m_imagea[m_iImage]->m_spdib->defer_realize(pgraphics);

            pgraphics->BitBlt((int32_t)get_x(), (int32_t)get_y(), (int32_t)get_cx(), (int32_t)get_cy(),
                              pdata->m_imagea[m_iImage]->m_spdib->get_graphics(), 0, 0, SRCCOPY);

         }

      }


      void image::implement_phase1(data * pdata, ::html::elemental * pelemental)
      {

         m_bHasChar = true;

         elemental::implement_phase1(pdata, pelemental);
         if (pelemental->m_pbase->get_type() == ::html::base::type_tag)
         {

            string strSrc = pelemental->m_propertyset["src"];
            m_iImage = pdata->get_image_index(strSrc);
            int cx = pdata->m_imagea[m_iImage]->m_spdib->m_size.cx;
            int cy = pdata->m_imagea[m_iImage]->m_spdib->m_size.cy;
            if (pelemental->m_propertyset.has_property("width"))
            {
               cx = pelemental->m_propertyset["width"];
            }
            if (pelemental->m_propertyset.has_property("height"))
            {
               cy = pelemental->m_propertyset["height"];
            }
            m_cxMax = (float)cx;
            m_cxMin = (float)cy;
         }
      }


      bool image::layout_phase1(data * pdata)
      {

         if (m_pelemental->m_pbase->get_type() == ::html::base::type_tag)
         {

            single_lock lockImage(pdata->m_imagea[m_iImage]->m_pmutex);

            if (lockImage.lock(duration::zero()))
            {

               int cx = pdata->m_imagea[m_iImage]->m_spdib->m_size.cx;
               int cy = pdata->m_imagea[m_iImage]->m_spdib->m_size.cy;
               if (m_pelemental->m_propertyset.has_property("width"))
               {
                  cx = m_pelemental->m_propertyset["width"];
               }
               if (m_pelemental->m_propertyset.has_property("height"))
               {
                  cy = m_pelemental->m_propertyset["height"];
               }

               m_box.set_cxy(size((float) cx, (float) cy));
            }
            else
            {
               m_box.set_cxy(0, 0);
            }

         }

         return true;

      }


      void image::layout_phase3(data * pdata)
      {

         elemental::layout_phase3(pdata);
         /*if (m_pelemental->m_pbase->get_type() == ::html::base::type_tag)
         {
            single_lock lockImage(&pdata->m_imagea[m_iImage]);

            if (lockImage.lock(duration::zero()))
            {
               pdata->m_layoutstate3.m_cx = (float)pdata->m_imagea[m_iImage]->m_spdib->m_size.cx;
               if (pdata->m_imagea[m_iImage]->m_spdib->m_size.cy > pdata->m_layoutstate3.m_cya.last())
               {
                  pdata->m_layoutstate3.m_cya.last() = (float)pdata->m_imagea[m_iImage]->m_spdib->m_size.cy;
               }
            }
            else
            {
               pdata->m_layoutstate3.m_cx = 0;
               pdata->m_layoutstate3.m_cya.last() = 0;
            }

            m_box.set_cxy(pdata->m_imagea[m_iImage]->m_spdib->size());

         }
         */
      }


   } // namespace impl


} // namespace html_impl


