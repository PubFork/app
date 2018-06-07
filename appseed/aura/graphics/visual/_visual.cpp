#include "framework.h"


#include "visual_cursor.cpp"
#include "visual_icon.cpp"




#ifdef SMALLCODE

#ifndef USE_OS_IMAGE_LOADER
// With TBS<3 in
#define USE_OS_IMAGE_LOADER

#endif

#endif


#include "antialias_8bit.cpp"
#include "detect_8bit_borders.cpp"
#ifdef USE_OS_IMAGE_LOADER
#if defined(WINDOWS)
#include "visual_gdiplus_image.cpp"
#include "visual_gdiplus_image_gif.cpp"
#include "visual_windows_image.cpp"
#endif
#else
#include "visual_freeimage_image.cpp"
#include "visual_freeimage_image_gif.cpp"
#endif
#include "load_gif_frame.cpp"
#include "visual_api.cpp"
#include "visual_buffered_graphics.cpp"
#include "visual_dib.cpp"
#include "visual_fastblur.cpp"
#include "visual_font.cpp"
#include "visual_font_department.cpp"
#include "visual_font_enumeration.cpp"
#include "visual_font_list.cpp"
#include "visual_glyph.cpp"
#include "visual_glyph_set.cpp"
#include "visual_graphics_extension.cpp"
#include "visual_image_list.cpp"
#include "visual_imaging.cpp"
#include "visual_rgb_quad_array.cpp"
#include "visual_visual.cpp"
#include "visual_water_routine.cpp"