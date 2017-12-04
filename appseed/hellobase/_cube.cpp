#include "framework.h"

::aura::application * get_acid_app(::aura::application * papp)
{

   return new ::hellobase::application();

}


#include "aura/aura/os/windows/windows_base.inl"