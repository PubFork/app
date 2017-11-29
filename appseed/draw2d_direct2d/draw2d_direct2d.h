#pragma once


#include "aura/aura/aura/aura.h"


#undef new

#include <D2d1_1.h>


#include <winapifamily.h>
#include <windows.h>
#include <shlwapi.h>
#include <wrl/client.h>
#include <DXGI1_2.h>
#include <Dwrite.h>
#include <D3D11.h>
#include <D3D11_1.h>




#ifdef _DRAW2D_DIRECT2D_LIBRARY
#define CLASS_DECL_DRAW2D_DIRECT2D  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_DRAW2D_DIRECT2D  CLASS_DECL_IMPORT
#endif


namespace d2d1
{


   inline D2D1_RECT_F rectf(LPCRECT lpcrect)
   {

      return D2D1::Rect<FLOAT>(
             (FLOAT)(lpcrect->left),
             (FLOAT)(lpcrect->top),
             (FLOAT)(lpcrect->right),
             (FLOAT)(lpcrect->bottom)
             );

   }


   inline D2D1_POINT_2F Point2F(double x = 0.0, double y = 0.0)
   {

      return Point2F(
             (FLOAT)(x),
             (FLOAT)(y)
             );

   }


} // namespace d2d1




namespace draw2d_direct2d
{

   void initialize();

   void finalize();

   class graphics;

   inline void throw_if_failed(HRESULT hr)
   {

      if(FAILED(hr))
         _throw(hresult_exception(get_app(), hr));
      //if(FAILED(hr))
      // _throw(hr);

   }


} // namespace draw2d_direct2d



#include "aura/aura/os/windows_common/draw2d_direct2d_global.h"


#include "draw2d_direct2d_factory_exchange.h"


#include "draw2d_direct2d_object.h"
#include "draw2d_direct2d_pen.h"
#include "draw2d_direct2d_bitmap.h"
#include "draw2d_direct2d_brush.h"
#include "draw2d_direct2d_font.h"
#include "draw2d_direct2d_palette.h"
#include "draw2d_direct2d_region.h"
#include "draw2d_direct2d_dib.h"
#include "draw2d_direct2d_path.h"
#include "draw2d_direct2d_printer.h"


#include "draw2d_direct2d_graphics.h"




#define new AURA_NEW

