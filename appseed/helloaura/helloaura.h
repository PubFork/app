#pragma once


#include "axis/axis/axis.h"


#ifdef _APP_CORE_HELLOAXIS_LIBRARY
#define CLASS_DECL_APP_CORE_HELLOAXIS  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_APP_CORE_HELLOAXIS  CLASS_DECL_IMPORT
#endif


namespace helloaxis
{

   class application;

} // namespace flag


#undef App
#define App(pbaseapp) (pbaseapp->m_paxisapp->cast_app < ::helloaxis::application > ())


#include "helloaxis_render.h"


#include "helloaxis_application.h"

