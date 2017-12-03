#include "aura/aura/aura/aura.h"


#undef new

int main(int argc, char * argv[])
{

   app_prelude with_class;

   ap(aura_main_data) pmaindata = new aura_main_data(argc, argv);

   br_init_set_symbol(g_psz_br_init_symbol_app);

   return (int) aura_aura(pmaindata);

}





//PRELUDE(aura_prelude, &get_acid_app)
