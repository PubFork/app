#include "framework.h"


namespace draw2d_quartz2d
{
   
   
   bitmap::bitmap(::aura::application * papp) :
      ::object(papp)
   {
      
      m_size.cx = 0;
      m_size.cy = 0;
      m_pdc = NULL;
      m_iScan = 0;
      
   }
   
   
   bitmap::~bitmap()
   {
      
      destroy();
      
   }
   
   
   bool bitmap::CreateBitmap(::draw2d::graphics * pgraphics, int32_t cx, int32_t cy, UINT nPlanes, UINT nBitcount, const void * pdata)
   {
      
      if(nPlanes != 1 || nBitcount != 32)
      {
         
         _throw(not_implemented(get_app()));
         
      }
      
      destroy();
      
      int iScan = cx * 4;
      
      CGColorSpaceRef colorspace = CGColorSpaceCreateDeviceRGB();
      
      try
      {
      
         m_mem.allocate(cy * iScan);
         
      }
      catch(...)
      {
         
      }
      
      if(m_mem.get_data() == NULL)
      {
         
         return false;
         
      }
      
      m_pdc = CGBitmapContextCreate(m_mem.get_data(), cx, cy, 8, iScan, colorspace, kCGImageAlphaPremultipliedLast);
      
      CGColorSpaceRelease(colorspace);
      
      if(m_pdc == NULL)
      {
         
         destroy();
         
         return false;
         
      }
      
      m_iScan = (int) CGBitmapContextGetBytesPerRow(m_pdc);
      
      if(m_iScan <= 0)
      {
         
         destroy();
         
         return false;
         
      }
      
      if(pdata != NULL)
      {
      
         memcpy(m_mem.get_data(), pdata, cy * iScan);
         
      }
      
      m_size.cx = cx;
      
      m_size.cy = cy;
      
      return true;
      
   }
   
   
   bool bitmap::CreateBitmapIndirect(::draw2d::graphics * pgraphics, LPBITMAP lpBitmap)
   {
      
      return false;
      
   }
   
   
   bool bitmap::CreateDIBSection(::draw2d::graphics * pgraphics, int cx, int cy, UINT usage, void ** ppdata, int * piStride, HANDLE hSection, uint32_t offset)
   {
      
      if(!CreateBitmap(pgraphics, cx, cy, 1, 32, NULL))
      {
         
         return false;
         
      }
      
      if(ppdata != NULL)
      {
         
         *ppdata = m_mem.get_data();
         
      }
      
      if(piStride)
      {
         
         *piStride = m_iScan;
         
      }
      
      return true;
      
   }
   
   
   bool bitmap::CreateDIBitmap(::draw2d::graphics * pgraphics, int cx, int cy, DWORD flInit, const void *pjBits, UINT iUsage)
   {
      
      return false;
      
   }
   
   
   DWORD bitmap::SetBitmapBits(DWORD dwCount, const void * lpBits)
   {
      
      return 0;
      
   }
   
   
   DWORD bitmap::GetBitmapBits(DWORD dwCount, LPVOID lpBits) const
   {

      return 0;
      
   }
   
   
   bool bitmap::LoadBitmap(const char * lpszResourceName)
   {

      return false;
      
   }
   
   
   size bitmap::SetBitmapDimension(int32_t nWidth, int32_t nHeight)
   {
      
      return ::size(0, 0);
      
   }
   
   
   size bitmap::GetBitmapDimension() const
   {
      
      if(get_os_data() == NULL)
      {

         return ::size(0, 0);

      }
      
      return m_size;
      
   }
   
   
   bool bitmap::LoadBitmap(UINT nIDResource)
   {
      
      return false;
      
   }
   
   
   bool bitmap::LoadOEMBitmap(UINT nIDBitmap)
   {

      return false;
      
   }
   
   
   bool bitmap::CreateCompatibleBitmap(::draw2d::graphics * pgraphics, int32_t cx, int32_t cy)
   {
      
      if(!CreateBitmap(pgraphics, cx, cy, 1, 32, NULL))
      {
         
         return false;
         
      }
      
      return true;
      
   }
   
   
   bool bitmap::CreateDiscardableBitmap(::draw2d::graphics * pgraphics, int32_t nWidth, int32_t nHeight)
   {
      
      return CreateCompatibleBitmap(pgraphics, nWidth, nHeight);
      
   }
   
   
   int32_t bitmap::GetBitmap(BITMAP* pBitMap)
   {
      
      return 0;
      
   }
   
#ifdef DEBUG

   
   void bitmap::dump(dump_context & dumpcontext) const
   {

      ::draw2d::object::dump(dumpcontext);
      
      if(get_os_data() == NULL)
         return;
       
      //dumpcontext << "bm.bmType = " << bm.bmType;
      dumpcontext << "\nbm.bmHeight = " << m_size.cy;
      dumpcontext << "\nbm.bmWidth = " << m_size.cx;
      dumpcontext << "\nbm.bmWidthBytes = " << m_iScan;
      dumpcontext << "\nbm.bmPlanes = " << 1;
      dumpcontext << "\nbm.bmBitsPixel = " << 32;
      dumpcontext << "\n";
      
   }
   
#endif
   
   void * bitmap::get_os_data() const
   {
      
      return m_pdc;
      
   }
   
   
   bool bitmap::Attach(void * pbitmapcontext)
   {
      
      throw interface_only_exception(get_app());
      
      destroy();
      
      m_pdc       = (CGContextRef) pbitmapcontext;
      
      m_size.cx   = (int) CGBitmapContextGetWidth(m_pdc);
      
      m_size.cy   = (int) CGBitmapContextGetHeight(m_pdc);
      
      m_iScan     = (int) CGBitmapContextGetBytesPerRow(m_pdc);
      
      //m_pdata     = (COLORREF *) CGBitmapContextGetData(m_pdc);
      
      return true;
      
   }
   
   
   bool bitmap::destroy()
   {
      
      if(m_pdc != NULL)
      {
         
         CGContextRelease(m_pdc);
         
         m_pdc = NULL;
         
      }
      
      //m_pdata = NULL;
      
      m_size.cx = 0;
      
      m_size.cy = 0;
      
      m_iScan = 0;
      
      return true;
      
   }
   
   
} // namespace draw2d_quartz2d







