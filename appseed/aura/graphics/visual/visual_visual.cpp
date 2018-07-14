#include "framework.h"

/*
namespace visual
{


   visual::visual(::draw2d::dib * pdib)
   {
      m_pdc = pgraphics;
   }


   visual::~visual()
   {
   }


   void visual::Polygon(const point_array & pointa)
   {
      m_pdc->Polygon(pointa.get_data(), (int32_t) pointa.get_size());
   }


} // visual


#include "framework.h"

*/


namespace visual
{


   double visual::g_dEmboss = 2.0;


   visual::visual(::aura::application * papp) :
      ::object(papp),
      ::aura::department(papp)
   {

      defer_create_mutex();


      m_pfontdepartment = NULL;
      m_pvisualapi = new ::visual::api(papp);

   }


   visual::~visual()
   {

      ::aura::del(m_pvisualapi);
      ::aura::del(m_pfontdepartment);

   }


   void visual::construct(::aura::application * papp)
   {

      ::aura::department::construct(papp);



   }

   api & visual::api()
   {

      return *m_pvisualapi;

   }


   bool visual::init1()
   {

      if (!::aura::department::init1())
         return false;

      synch_lock sl(m_pmutex);

      if (m_pfontdepartment == NULL)
      {

         m_pfontdepartment = new class font_department(get_app());

         if (m_pfontdepartment == NULL)
            return false;

         if (!m_pfontdepartment->Initialize())
            return false;

      }

      return true;

   }


   bool visual::process_init()
   {

      if (!::aura::department::process_init())
         return false;

      synch_lock sl(m_pmutex);

      if (!m_pvisualapi->open())
         return false;

      return true;

   }


   bool visual::init()
   {

      if (!::aura::department::init())
      {

         return false;

      }

      ////if(Application.dir().is(System.dir().commonappdata("")))
      //{

      //   __begin_thread(get_app(), &visual::thread_proc_parallel_initialize, this, ::multithreading::priority_highest);

      //}

      return true;

   }

   //uint32_t c_cdecl visual::thread_proc_parallel_initialize(void * pparamThis)
   //{

   //   visual * pvisual = (visual *)pparamThis;

   //   pvisual->set_cursor_set_from_matter("cursor/antialiased-classic");

   //   return 0;

   //}


   void visual::term()
   {

      synch_lock sl(m_pmutex);

      try
      {

         if (m_pvisualapi != NULL)
         {

            m_pvisualapi->close();

         }

      }
      catch (...)
      {

      }

      try
      {

         if (m_pfontdepartment != NULL)
         {

            m_pfontdepartment->Finalize();

         }

      }
      catch (...)
      {


      }

      ::aura::del(m_pvisualapi);

      ::aura::del(m_pfontdepartment);

      for (auto & p : m_cursormap)
      {

         delete p.m_element2;

      }

      m_cursormap.remove_all();

   }


   class font_department & visual::fonts()
   {
      return *m_pfontdepartment;
   }

   cursor * visual::set_cursor_file(e_cursor ecursor, const ::file::path & psz, bool bFromCache)
   {

      synch_lock sl(m_pmutex);

      cursor * pcursor = get_cursor(ecursor);

      if (Application.imaging().load_from_file(pcursor, psz, bFromCache))
      {

         return pcursor;

      }
      else
      {

         if (pcursor->initialize_system_default())
         {

            return pcursor;

         }

         return NULL;

      }

   }


   cursor * visual::set_system_default_cursor(e_cursor ecursor)
   {

      synch_lock sl(m_pmutex);

      cursor * pcursor = get_cursor(ecursor);

      if (pcursor->initialize_system_default())
      {

         return pcursor;

      }

      return NULL;

   }



   cursor * visual::get_cursor(e_cursor ecursor)
   {

      synch_lock sl(m_pmutex);

      cursor * pcursor = NULL;

      if (m_cursormap.Lookup(ecursor, pcursor))
      {

         return pcursor;

      }
      else
      {

         pcursor = new cursor(get_app());

         pcursor->m_ecursor = ecursor;

         m_cursormap.set_at(ecursor, pcursor);

         return pcursor;

      }

   }



   ::count visual::set_cursor_set_from_matter(const ::file::path & pszMatter)
   {

      // "arrow.png" is a troll/bait for getting the right path of the cursor file, then the directory where found

      return set_cursor_set_from_dir(::file::path(Application.dir().matter(pszMatter / "arrow.png")).folder());

   }


   ::count visual::set_cursor_set_from_dir(const ::file::path & pszDir, bool bFromCache)
   {

      ::count count = 0;

      if (set_cursor_file(::visual::cursor_arrow, pszDir / "arrow.png", bFromCache))
      {
         count++;
      }
      else
      {
         return 0;
      }
      if (set_cursor_file(::visual::cursor_hand, pszDir / "hand.png", bFromCache))
      {
         count++;
      }
      else
      {
         set_cursor_file(::visual::cursor_hand, pszDir / "arrow.png", bFromCache);
      }
      if (set_cursor_file(::visual::cursor_text_select, pszDir / "text_select.png", bFromCache))
      {
         count++;
      }
      else
      {
         set_cursor_file(::visual::cursor_text_select, pszDir / "arrow.png", bFromCache);
      }
      if (set_cursor_file(::visual::cursor_size_top_left, pszDir / "size_top_left.png", bFromCache))
      {
         count++;
      }
      else
      {
         set_cursor_file(::visual::cursor_size_top_left, pszDir / "arrow.png", bFromCache);
      }
      if (set_cursor_file(::visual::cursor_size_top, pszDir / "size_top.png", bFromCache))
      {
         count++;
      }
      else
      {
         set_cursor_file(::visual::cursor_size_top, pszDir / "arrow.png", bFromCache);
      }
      if (set_cursor_file(::visual::cursor_size_top_right, pszDir / "size_top_right.png", bFromCache))
      {
         count++;
      }
      else
      {
         set_cursor_file(::visual::cursor_size_top_right, pszDir / "arrow.png", bFromCache);
      }
      if (set_cursor_file(::visual::cursor_size_right, pszDir / "size_right.png", bFromCache))
      {
         count++;
      }
      else
      {
         set_cursor_file(::visual::cursor_size_right, pszDir / "arrow.png", bFromCache);
      }
      if (set_cursor_file(::visual::cursor_size_bottom_right, pszDir / "size_bottom_right.png", bFromCache))
      {
         count++;
      }
      else
      {
         set_cursor_file(::visual::cursor_size_bottom_right, pszDir / "arrow.png", bFromCache);
      }
      if (set_cursor_file(::visual::cursor_size_bottom, pszDir / "size_bottom.png", bFromCache))
      {
         count++;
      }
      else
      {
         set_cursor_file(::visual::cursor_size_bottom, pszDir / "arrow.png", bFromCache);
      }
      if (set_cursor_file(::visual::cursor_size_bottom_left, pszDir / "size_bottom_left.png", bFromCache))
      {
         count++;
      }
      else
      {
         set_cursor_file(::visual::cursor_size_bottom_left, pszDir / "arrow.png", bFromCache);
      }
      if (set_cursor_file(::visual::cursor_size_left, pszDir / "size_left.png", bFromCache))
      {
         count++;
      }
      else
      {
         set_cursor_file(::visual::cursor_size_left, pszDir / "arrow.png", bFromCache);
      }
      if (set_cursor_file(::visual::cursor_size_vertical, pszDir / "size_vertical.png", bFromCache))
      {
         count++;
      }
      else
      {
         set_cursor_file(::visual::cursor_size_vertical, pszDir / "arrow.png", bFromCache);
      }
      if (set_cursor_file(::visual::cursor_size_horizontal, pszDir / "size_horizontal.png", bFromCache))
      {
         count++;
      }
      else
      {
         set_cursor_file(::visual::cursor_size_horizontal, pszDir / "arrow.png", bFromCache);
      }
      if (set_cursor_file(::visual::cursor_move, pszDir / "move.png", false))
      {
         count++;
      }
      else
      {
         set_cursor_file(::visual::cursor_move, pszDir / "arrow.png", bFromCache);
      }

      return count;
   }


   ::count visual::set_cursor_set_system_default()
   {

      ::count count = 0;

      if (set_system_default_cursor(::visual::cursor_arrow))
      {
         count++;
      }

      if (set_system_default_cursor(::visual::cursor_hand))
      {
         count++;
      }

      if (set_system_default_cursor(::visual::cursor_text_select))
      {
         count++;
      }

      if (set_system_default_cursor(::visual::cursor_size_top_left))
      {
         count++;
      }

      if (set_system_default_cursor(::visual::cursor_size_top))
      {
         count++;
      }

      if (set_system_default_cursor(::visual::cursor_size_top_right))
      {
         count++;
      }

      if (set_system_default_cursor(::visual::cursor_size_right))
      {
         count++;
      }

      if (set_system_default_cursor(::visual::cursor_size_bottom_right))
      {
         count++;
      }

      if (set_system_default_cursor(::visual::cursor_size_bottom))
      {
         count++;
      }

      if (set_system_default_cursor(::visual::cursor_size_bottom_left))
      {
         count++;
      }

      if (set_system_default_cursor(::visual::cursor_size_left))
      {
         count++;
      }

      if (set_system_default_cursor(::visual::cursor_size_vertical))
      {
         count++;
      }

      if (set_system_default_cursor(::visual::cursor_size_horizontal))
      {
         count++;
      }

      return count;

   }


   // should not call axis class implementation because visual::visual is inside a n-furcation of user::visual
   void visual::term_instance()
   {

      try
      {

         ::aura::department::term_instance();

      }
      catch (...)
      {

         ::simple_message_box(NULL, "except", "except", MB_OK);

      }

   }


   bool visual::embossed_text_out(
   ::draw2d::graphics * pgraphics,
   LPCRECT lpcrect,
   string strText,
   ::visual::fastblur & dib2,
   ::draw2d::font * pfont,
   int iDrawTextFlags,
   COLORREF crText,
   COLORREF crGlow,
   int iSpreadRadius,
   int iBlurRadius,
   int iBlur,
   bool bUpdate,
   double dAlpha)
   {

      if (strText.is_empty())
      {

         return false;

      }

      auto pred = [&](::draw2d::graphics * pgraphics)
      {

         pgraphics->SelectObject(pfont);
         pgraphics->_DrawText(strText, *lpcrect, iDrawTextFlags);

      };

      emboss_pred(
      pgraphics,
      lpcrect,
      pred,
      dib2,
      crGlow,
      iSpreadRadius,
      iBlurRadius,
      iBlur,
      bUpdate,
      dAlpha);

      byte bA = (byte)(dAlpha * 255.0);
      ::draw2d::brush_sp brushText(allocer());
      brushText->create_solid((crText & 0x00ffffffu) | (bA << 24));
      pgraphics->SelectObject(brushText);
      pgraphics->SelectObject(pfont);
      pgraphics->_DrawText(strText, *lpcrect, iDrawTextFlags);

      return true;

   }

   void visual::alpha_spread__24CC(
   LPBYTE lpbDst, int32_t xDest, int32_t yDest, int32_t wDest, int32_t cx, int32_t cy,
   LPBYTE lpbSrc, int32_t xSrc, int32_t ySrc, int32_t wSrc,
   BYTE bMin, int32_t iRadius)
   {
      UNREFERENCED_PARAMETER(xDest);
      UNREFERENCED_PARAMETER(yDest);
      UNREFERENCED_PARAMETER(xSrc);
      UNREFERENCED_PARAMETER(ySrc);
      int32_t iFilterW = iRadius * 2 + 1;
      int32_t iFilterH = iRadius * 2 + 1;
      int32_t iFilterHalfW = iFilterW / 2;
      int32_t iFilterHalfH = iFilterH / 2;
      int32_t iFilterArea = iFilterW * iFilterH;
      int32_t divisor = iFilterW * iFilterH;
      BYTE *lpbSource;
      BYTE *lpbSource_1;
      BYTE *lpbSource_2;
      BYTE *lpwDestination;
      BYTE *lpFilter;
      BYTE *pFilter;


      int32_t i;
      int32_t x;
      int32_t y;
      int32_t x1;
      int32_t y1;
      int32_t x2;
      int32_t y2;

      int32_t iRadius2 = iRadius * iRadius;
      int32_t r2;

      synch_lock sl(m_pmutex);

      auto & filter = m_alpha_spread__24CC_filterMap[iRadius];

      if (filter.is_set())
      {

         pFilter = filter->get_data();

      }
      else
      {

         filter = canew(memory());

         filter->allocate(iFilterArea);

         pFilter = filter->get_data();

         for (y = 0; y <= iFilterHalfH; y++)
         {

            for (x = 0; x <= iFilterHalfW; x++)
            {

               x1 = iFilterHalfW - x;

               y1 = iFilterHalfH - y;

               r2 = x1 * x1 + y1 * y1;

               if (r2 <= iRadius2)
               {

                  i = 1;

               }
               else
               {

                  i = 0;

               }

               pFilter[x + y * iFilterW] = (byte)i;

               pFilter[iFilterW - 1 - x + y * iFilterW] = (byte)i;

               pFilter[iFilterW - 1 - x + (iFilterH - 1 - y) * iFilterW] = (byte)i;

               pFilter[x + (iFilterH - 1 - y) * iFilterW] = (byte)i;

            }

         }

      }

      sl.unlock();

      int32_t maxx1 = cx;
      int32_t maxy1 = cy;
      int32_t max3x1 = maxx1 * 3;


      uint32_t dwR;
      uint32_t dwG;
      uint32_t dwB;


      int32_t iFilterXLowerBound;
      int32_t iFilterXUpperBound;
      int32_t iFilterYLowerBound;
      int32_t iFilterYUpperBound;

      int32_t yLowerBound[4];
      int32_t yUpperBound[4];
      int32_t xLowerBound[4];
      int32_t xUpperBound[4];

      // top
      xLowerBound[0] = 0;
      xUpperBound[0] = cx - 1;
      yLowerBound[0] = 0;
      yUpperBound[0] = iFilterHalfH - 1;

      // left
      xLowerBound[1] = 0;
      xUpperBound[1] = iFilterHalfW - 1;
      yLowerBound[1] = iFilterHalfH;
      yUpperBound[1] = cy - iFilterHalfH - 1;

      // right
      xLowerBound[2] = cx - iFilterHalfW;
      xUpperBound[2] = cx - 1;
      yLowerBound[2] = iFilterHalfH;
      yUpperBound[2] = cy - iFilterHalfH - 1;

      // bottom
      xLowerBound[3] = 0;
      xUpperBound[3] = cx - 1;
      yLowerBound[3] = cy - iFilterHalfW;
      yUpperBound[3] = cy - 1;

      int32_t xL;
      int32_t xU;
      int32_t yL;
      int32_t yU;

      bool bSpread;
      uint32_t bMin3 = bMin * 3;


      for (i = 0; i < 4; i++)
      {
         xL = xLowerBound[i];
         xU = xUpperBound[i];
         yL = yLowerBound[i];
         yU = yUpperBound[i];

         y1 = yL;
         y2 = y1 - iFilterHalfH;
         for (; y1 <= yU;)
         {
            if (y1 < iFilterHalfH)
            {
               iFilterYLowerBound = iFilterHalfH - y1;
            }
            else
            {
               iFilterYLowerBound = 0;
            }
            if (y1 >(cy - iFilterHalfH))
            {
               iFilterYUpperBound = iFilterH - (y1 - (cy - iFilterHalfH)) - 1;
            }
            else
            {
               iFilterYUpperBound = iFilterH - 1;
            }

            lpbSource = lpbSrc + (wSrc * MAX(y2, 0));

            x1 = xL;
            x2 = (x1 - iFilterHalfW) * 3;
            lpwDestination = lpbDst + (wDest  * y1) + x1 * 3;
            for (; x1 <= xU;)
            {
               if (x1 < iFilterHalfH)
               {
                  iFilterXLowerBound = iFilterHalfH - x1;
               }
               else
               {
                  iFilterXLowerBound = 0;
               }
               if (x1 >(cx - iFilterHalfH + 1))
               {
                  iFilterXUpperBound = iFilterH - (x1 - (cx - iFilterHalfH + 1));
               }
               else
               {
                  iFilterXUpperBound = iFilterH - 1;
               }

               lpbSource_1 = lpbSource + MAX(x2, 0);


               dwR = 0;
               dwG = 0;
               dwB = 0;
               bSpread = false;
               for (int32_t yFilter = iFilterYLowerBound; yFilter < iFilterYUpperBound; yFilter++)
               {
                  lpbSource_2 = lpbSource_1 + (wSrc * yFilter);
                  lpFilter = pFilter + yFilter * iFilterW + iFilterXLowerBound;
                  for (int32_t xFilter = iFilterXLowerBound; xFilter < iFilterXUpperBound; xFilter++)
                  {
                     if (*lpFilter >= 1)
                     {
                        dwB = lpbSource_2[0];
                        dwG = lpbSource_2[1];
                        dwR = lpbSource_2[2];

                        if (dwR + dwG + dwB > bMin3)
                        {
                           *((uint32_t *)lpwDestination) |= 0x00ffffff;
                           goto breakFilter;
                        }
                     }
                     lpFilter++;
                     lpbSource_2 += 3;
                  }
               }
breakFilter:
               lpwDestination += 3;
               x1++;
               x2 += 3;
            }
            y1++;
            y2++;
         }
      }

      iFilterYLowerBound = 0;
      iFilterYUpperBound = iFilterW - 1;
      iFilterXLowerBound = 0;
      iFilterXUpperBound = iFilterH - 1;

      int32_t iFilterHalfWidth = iFilterW / 2;
      int32_t iFilterHalfWidthBytes = iFilterHalfWidth * 3;

      yL = iFilterHalfWidth;
      yU = maxy1 - iFilterHalfWidth;
      xL = iFilterHalfWidthBytes;
      xU = max3x1 - iFilterHalfWidthBytes;

      y1 = yL;
      y2 = yL - iFilterHalfWidth;



      divisor = (iFilterYUpperBound - iFilterYLowerBound + 1) * (iFilterXUpperBound - iFilterXLowerBound + 1);


      for (; y1 < yU;)
      {
         lpbSource = lpbSrc + (wSrc * y2);

         x1 = xL;
         x2 = xL - iFilterHalfWidthBytes;
         lpwDestination = lpbDst + (wDest  * y1) + x1;
         for (; x1 < xU;)
         {
            lpbSource_1 = lpbSource + x2;
            lpFilter = pFilter;

            dwR = 0;
            dwG = 0;
            dwB = 0;
            bSpread = false;
            for (int32_t yFilter = iFilterYLowerBound; yFilter <= iFilterYUpperBound; yFilter++)
            {
               lpbSource_2 = lpbSource_1 + (wSrc * yFilter);
               lpFilter = pFilter + yFilter * iFilterW + iFilterXLowerBound;
               for (int32_t xFilter = iFilterXLowerBound; xFilter <= iFilterXUpperBound; xFilter++)
               {
                  if (*lpFilter >= 1)
                  {
                     dwB = lpbSource_2[0];
                     dwG = lpbSource_2[1];
                     dwR = lpbSource_2[2];

                     if (dwR + dwG + dwB > bMin3)
                     {
                        bSpread = true;
                        break;
                     }
                  }
                  lpFilter++;
                  lpbSource_2 += 3;
               }
            }

            if (bSpread)
            {
               *((uint32_t *)lpwDestination) |= 0x00ffffff;
               lpwDestination += 3;
            }
            else
            {
               lpwDestination += 3;
            }
            x1 += 3;
            x2 += 3;
         }
         y1++;
         y2++;
      }

   }


   bool visual::channel_spread__32CC(::draw2d::dib * pdibDst, ::draw2d::dib * pdibSrc, int32_t iChannel, int32_t iRadius, COLORREF crSpreadSetColor)
   {
      int32_t iFilterW = iRadius * 2 + 1;
      int32_t iFilterH = iRadius * 2 + 1;
      int32_t iFilterHalfW = iRadius;
      int32_t iFilterHalfH = iRadius;
      int32_t iFilterArea = iFilterW * iFilterH;
      int32_t divisor = iFilterW * iFilterH;
      BYTE *lpbSource;
      BYTE *lpbSource_1;
      BYTE *lpbSource_2;
      BYTE *lpwDestination;
      BYTE *lpFilter;
      BYTE * pFilter;

      int32_t i;
      int32_t x;
      int32_t y;
      int32_t x1;
      int32_t y1;
      int32_t x2;
      int32_t y2;

      int32_t iRadiusSquare = iRadius * iRadius;
      int32_t rSquare;


      synch_lock sl(m_pmutex);

      auto & filter = m_alpha_spread__32CC_filterMap[iRadius];

      if (filter.is_set())
      {
         pFilter = filter->get_data();
      }
      else
      {
         filter = canew(memory());
         filter->allocate(iFilterArea);
         pFilter = filter->get_data();
         for (y = 0; y < iFilterH; y++)
         {
            for (x = 0; x < iFilterW; x++)
            {
               x1 = iFilterHalfW - x;
               y1 = iFilterHalfH - y;
               rSquare = x1 * x1 + y1 * y1;
               if (rSquare <= iRadiusSquare)
                  i = 1;
               else
                  i = 0;
               pFilter[x + y * iFilterW] = (byte)i;
            }
         }
      }

      sl.unlock();

      int32_t cx = pdibDst->m_size.cx;
      int32_t cy = pdibDst->m_size.cy;

      if (cx != pdibSrc->m_size.cx
            || cy != pdibSrc->m_size.cy)
         return false;

      LPBYTE lpbDst = (LPBYTE)pdibDst->get_data();
      LPBYTE lpbSrc = (LPBYTE)pdibSrc->get_data();

      //int32_t wSrc = cx * 4;
      //int32_t wDst = cx * 4;
      int32_t wSrc = pdibSrc->m_iScan;
      int32_t wDst = pdibDst->m_iScan;

      int32_t maxx1 = cx;
      int32_t maxy1 = cy;
      //   int32_t maxy2 = cy - iFilterW;
      //   int32_t maxy3 = cy - iFilterW / 2;
      int32_t max3x1 = maxx1 * 4;
      //   int32_t max3x2 = (maxx1 - iFilterH) * 4;
      //   int32_t max3x3 = (maxx1 - iFilterH / 2) * 4;
      //int32_t w = cx * 4;

      ::draw2d::copy_colorref(cx, cy, (COLORREF *)lpbDst, pdibDst->m_iScan, (COLORREF *)lpbSrc, pdibSrc->m_iScan);
      //memcpy(lpbDst,lpbSrc,cx * cy * 4);


      int32_t iFilterXLowerBound;
      int32_t iFilterXUpperBound;
      int32_t iFilterYLowerBound;
      int32_t iFilterYUpperBound;

      int32_t yLowerBound[4];
      int32_t yUpperBound[4];
      int32_t xLowerBound[4];
      int32_t xUpperBound[4];

      // top
      xLowerBound[0] = 0;
      xUpperBound[0] = cx - 1;
      yLowerBound[0] = 0;
      yUpperBound[0] = iFilterHalfH - 1;

      // left
      xLowerBound[1] = 0;
      xUpperBound[1] = iFilterHalfW - 1;
      yLowerBound[1] = iFilterHalfH;
      yUpperBound[1] = cy - iFilterHalfH - 1;

      // right
      xLowerBound[2] = cx - iFilterHalfW;
      xUpperBound[2] = cx - 1;
      yLowerBound[2] = iFilterHalfH;
      yUpperBound[2] = cy - iFilterHalfH - 1;

      // bottom
      xLowerBound[3] = 0;
      xUpperBound[3] = cx - 1;
      yLowerBound[3] = cy - iFilterHalfH;
      yUpperBound[3] = cy - 1;

      int32_t xL;
      int32_t xU;
      int32_t yL;
      int32_t yU;


      int32_t xMax = cx - 1;
      int32_t yMax = cy - 1;

      // limits due the filter
      int32_t xMaxFilterBound = xMax - iFilterHalfW;
      int32_t yMaxFilterBound = yMax - iFilterHalfH;

      int32_t xFilterMax = iFilterW - 1;
      int32_t yFilterMax = iFilterH - 1;

      for (i = 0; i < 4; i++)
      {
         xL = xLowerBound[i];
         xU = xUpperBound[i];
         yL = yLowerBound[i];
         yU = yUpperBound[i];

         y1 = yL;
         y2 = y1 - iFilterHalfH;
         for (; y1 <= yU;)
         {
            if (y1 < iFilterHalfH)
            {
               iFilterYLowerBound = iFilterHalfH - y1;
            }
            else
            {
               iFilterYLowerBound = 0;
            }
            if (y1 > yMaxFilterBound)
            {
               iFilterYUpperBound = yFilterMax - (y1 - yMaxFilterBound);
            }
            else
            {
               iFilterYUpperBound = yFilterMax;
            }

            lpbSource = lpbSrc + wSrc * y2;

            x1 = xL;
            x2 = (x1 - iFilterHalfW) * 4;
            lpwDestination = lpbDst + (wDst  * y1) + x1 * 4;
            if (*((uint32_t *)lpwDestination) != 0xffffffff)
            {
               for (; x1 <= xU; x1++)
               {
                  if (x1 < iFilterHalfH)
                  {
                     iFilterXLowerBound = iFilterHalfH - x1;
                  }
                  else
                  {
                     iFilterXLowerBound = 0;
                  }
                  if (x1 > xMaxFilterBound)
                  {
                     iFilterXUpperBound = xFilterMax - (x1 - xMaxFilterBound);
                  }
                  else
                  {
                     iFilterXUpperBound = xFilterMax;
                  }

                  lpbSource_1 = lpbSource + MAX(x2, 0) + iChannel;


                  for (int32_t yFilter = iFilterYLowerBound; yFilter < iFilterYUpperBound; yFilter++)
                  {
                     lpbSource_2 = lpbSource_1 + (wSrc * yFilter);
                     lpFilter = pFilter + yFilter * iFilterW + iFilterXLowerBound;
                     for (int32_t xFilter = iFilterXLowerBound; xFilter < iFilterXUpperBound; xFilter++)
                     {
                        if (*lpFilter >= 1)
                        {
                           if (lpbSource_2[0] > 0)
                           {
                              *((uint32_t *)lpwDestination) = crSpreadSetColor;
                              goto breakFilter;
                           }
                        }
                        lpFilter++;
                        lpbSource_2 += 4;
                     }
                  }
breakFilter:
                  lpwDestination += 4;
                  x2 += 4;
               }
            }
            y1++;
            y2++;
         }
      }

      iFilterYLowerBound = 0;
      iFilterYUpperBound = iFilterW - 1;
      iFilterXLowerBound = 0;
      iFilterXUpperBound = iFilterH - 1;

      int32_t iFilterHalfWidth = iFilterW / 2;
      int32_t iFilterHalfWidthBytes = iFilterHalfWidth * 4;

      yL = iFilterHalfWidth;
      yU = maxy1 - iFilterHalfWidth;
      xL = iFilterHalfWidthBytes;
      xU = max3x1 - iFilterHalfWidthBytes;

      y1 = yL;
      y2 = yL - iFilterHalfWidth;



      divisor = (iFilterYUpperBound - iFilterYLowerBound + 1) * (iFilterXUpperBound - iFilterXLowerBound + 1);


      for (; y1 < yU;)
      {
         lpbSource = lpbSrc + (wSrc * y2) + iChannel;

         x1 = xL;
         x2 = xL - iFilterHalfWidthBytes;
         lpwDestination = lpbDst + (wDst  * y1) + x1;
         for (; x1 < xU;)
         {
            lpbSource_1 = lpbSource + x2;
            lpFilter = pFilter;

            if (*((uint32_t *)lpwDestination) != 0xffffffff)
            {
               for (int32_t yFilter = iFilterYLowerBound; yFilter <= iFilterYUpperBound; yFilter++)
               {
                  lpbSource_2 = lpbSource_1 + (wSrc * yFilter);
                  lpFilter = pFilter + yFilter * iFilterW + iFilterXLowerBound;
                  for (int32_t xFilter = iFilterXLowerBound; xFilter <= iFilterXUpperBound; xFilter++)
                  {
                     if (*lpFilter >= 1)
                     {
                        if (lpbSource_2[0] > 0)
                        {
                           *((uint32_t *)lpwDestination) = crSpreadSetColor;
                           goto breakFilter2;
                        }
                     }
                     lpFilter++;
                     lpbSource_2 += 4;
                  }
               }
            }
breakFilter2:
            lpwDestination += 4;
            x1 += 4;
            x2 += 4;
         }
         y1++;
         y2++;
      }

      return true;
   }
















} // namespace visual
