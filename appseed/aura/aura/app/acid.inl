#include "aura/aura/aura/aura.h"


::aura::application * get_acid_app(::aura::application * papp);


typedef aura_prelude app_prelude;


#undef new

int main(int argc, char * argv[])
{

   app_prelude with_class(&get_acid_app);

   ap(aura_main_data) pmaindata = new aura_main_data(argc, argv);

   return (int) aura_aura(pmaindata);

}


#ifdef WINDOWS

BEGIN_EXTERN_C

int32_t WINAPI _tWinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int32_t nCmdShow)
{

   app_prelude with_class(&get_acid_app);

   ap(aura_main_data) pmaindata = new aura_main_data(hinstance, hPrevInstance, lpCmdLine, nCmdShow);

   return aura_aura(pmaindata);

}

END_EXTERN_C

#endif




