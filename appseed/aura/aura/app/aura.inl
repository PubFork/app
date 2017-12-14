#include "aura/aura/aura/aura.h"


#ifdef METROWIN

//#include "core/core/core.h"
//
//#undef CoreApplication
//

#undef new

[MTAThread]
int main(Array<String^>^)
{

   class aura_aura aura;

   aura_aura aura;

   ap(aura_main_data) pmaindata = new aura_main_data(MAIN_STRING);

   return (int)aura_aura(pmaindata);

}

#else


#undef new

int main(int argc, char * argv[])
{

   class aura_aura aura;

   ap(aura_main_data) pmaindata = new aura_main_data(argc, argv);

#ifdef MAIN_STRING

   pmaindata->m_lpCmdLine = ::str::dup(MAIN_STRING);

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







