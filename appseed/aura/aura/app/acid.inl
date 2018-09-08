#include "aura/aura/aura/aura.h"


::aura::application * get_acid_app(::aura::application * papp);


//typedef aura_prelude app_prelude;
//
//
#undef new

int main(int argc, char * argv[])
{

   class aura_aura aura;

   ap(aura_main_data) pmaindata = new aura_main_data(argc, argv);

   return (int) aura_aura(pmaindata, &get_acid_app);

}


#ifdef WINDOWS

BEGIN_EXTERN_C

int32_t WINAPI _tWinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int32_t nCmdShow)
{

   class aura_aura aura;

   aura_main_data * pmaindata = canew(aura_main_data(hinstance, hPrevInstance, lpCmdLine, nCmdShow));

   return aura_aura(pmaindata, &get_acid_app);

}

END_EXTERN_C

#endif




