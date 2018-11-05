#include "framework.h"
#include "windows_common_graphics.h"


namespace draw2d
{

   ID2D1Factory1 * device_lock::g_pfactory = NULL;


   mutex * lock::g_pmutex = NULL;

} // namespace draw2d

