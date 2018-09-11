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

#ifdef BUILTIN_STRLANGMAP

   pmaindata->m_pstrlangmap = BUILTIN_STRLANGMAP;

#endif

#ifdef STANDALONE

   pmaindata->m_strStandalone = STANDALONE;

#endif

#ifdef BR_INIT_SYMBOL

   br_init_set_symbol(BR_INIT_SYMBOL);

#endif

#ifdef GTKAPP

   pmaindata->m_bGtkApp = true;

#endif

   return (int) aura_aura(pmaindata, &get_acid_app);

}


#ifdef WINDOWS

BEGIN_EXTERN_C

int32_t WINAPI _tWinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int32_t nCmdShow)
{

   class aura_aura aura;

   aura_main_data * pmaindata = canew(aura_main_data(hinstance, hPrevInstance, lpCmdLine, nCmdShow));

#ifdef BUILTIN_STRLANGMAP

   pmaindata->m_pstrlangmap = BUILTIN_STRLANGMAP;

#endif

#ifdef STANDALONE

   pmaindata->m_strStandalone = STANDALONE;

#endif

   return aura_aura(pmaindata, &get_acid_app);

}

END_EXTERN_C

#endif




