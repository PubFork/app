#pragma once


#include "draw2d_fwd.h"
#include "draw2d_const.h"
#include "draw2d_common.h"
#include "draw2d_matrix.h"


namespace draw2d
{

   class graphics;

   CLASS_DECL_AURA void vertical_swap_copy_colorref(int cx,int cy,COLORREF * pcolorrefDst,int iStrideDst,COLORREF * pcolorrefSrc,int iStrideSrc);
   CLASS_DECL_AURA void copy_colorref(int cx,int cy,COLORREF * pcolorrefDst,int iStrideDst,COLORREF * pcolorrefSrc,int iStrideSrc);
   CLASS_DECL_AURA void copy_colorref(int x, int y, int cx,int cy,COLORREF * pcolorrefDst,int iStrideDst,COLORREF * pcolorrefSrc,int iStrideSrc);
   CLASS_DECL_AURA void _001ProperCopyColorref(int cx,int cy,COLORREF * pcolorrefDst,int iStrideDst,COLORREF * pcolorrefSrc,int iStrideSrc);


   inline COLORREF get_pixel(COLORREF * pcolorref, int iScan, int iHeight, int x, int y);

   CLASS_DECL_AURA e_rotate_flip exif_orientation_rotate_flip(int orientation);

} // namespace draw2d




#include "draw2d_object.h"
#include "draw2d_keep.h"
#include "draw2d_pen.h"
#include "draw2d_bitmap.h"
#include "draw2d_dib.h"
#include "draw2d_dibmap.h"
#include "draw2d_dibmap_ex1.h"
#include "draw2d_brush.h"
#include "draw2d_font.h"
#include "draw2d_palette.h"
#include "draw2d_region.h"
#include "draw2d_igui.h"
#include "draw2d_path.h"


#include "draw2d_dibmap.h"
#include "draw2d_dibmap_ex1.h"


namespace aura
{


   class str_context;


}


#include "aura/aura/aura/aura_draw_context.h"
#include "draw2d_graphics.h"








