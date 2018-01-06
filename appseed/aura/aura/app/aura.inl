#include "aura/aura/aura/aura.h"


#ifdef METROWIN

//#include "core/core/core.h"
//
//#undef CoreApplication
//

#undef new

[MTAThread]
int main(Array < String ^ > ^ refstra)
{

   class aura_aura aura;

   ap(aura_main_data) pmaindata = new aura_main_data(refstra);

#ifdef MAIN_STRING

   pmaindata->m_strCommandLine = MAIN_STRING;

#endif

   return (int)aura_aura(pmaindata);

}

#else


#undef new

int main(int argc, char * argv[])
{

   class aura_aura aura;

   ap(aura_main_data) pmaindata = new aura_main_data(argc, argv);

#ifdef MAIN_STRING

   pmaindata->m_strCommandLine = MAIN_STRING;

#endif

   return (int)aura_aura(pmaindata);

}


#ifdef WINDOWS

BEGIN_EXTERN_C

int32_t WINAPI _tWinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int32_t nCmdShow)
{

   class aura_aura aura;

   ap(aura_main_data) pmaindata = new aura_main_data(hinstance, hPrevInstance, lpCmdLine, nCmdShow);

   return aura_aura(pmaindata);

}

END_EXTERN_C

#endif


#endif



#ifdef WINDOWS

#include "include/applink.cpp"

#endif


#define APP_PRELUDE_LEVEL(prefix, level) \
extern "C" \
::aura::application * prefix##_get_new_app(::aura::application * papp); \
aura_prelude auraprelude(&prefix##_get_new_app, level);


#define LIBRARY_PRELUDE_LEVEL(prefix, level) \
extern "C" \
::aura::library * prefix##_get_new_library(::aura::application * papp); \
aura_prelude auraprelude(&prefix##_get_new_library, level);

#define APP_PRELUDE(prefix) APP_PRELUDE_LEVEL(prefix, "core")

#define LIBRARY_PRELUDE(prefix) LIBRARY_PRELUDE_LEVEL(prefix, "core")

