#include "framework.h"

::aura::application * get_acid_app(::aura::application * papp)
{

   return new ::helloworld::application();

}


#include "aura/aura/os/windows/windows_core.inl"