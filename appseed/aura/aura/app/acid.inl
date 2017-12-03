#include "aura/aura/aura/aura.h"


::aura::application * get_acid_app(::aura::application * papp);

#undef new

#define PRELUDE(WITH_CLASS) \
int main(int argc, char * argv[]) \
{ \
\
   WITH_CLASS with_class; \
\
   ap(aura_main_data) pmaindata = new aura_main_data(argc, argv); \
\
   return (int) aura_aura(pmaindata); \
\
}





//PRELUDE(aura_prelude, &get_acid_app)
