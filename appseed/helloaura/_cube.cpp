#include "framework.h"

::aura::application * get_acid_app(::aura::application * papp)
{

   return new ::helloaura::application();

}


#include "aura/aura/os/windows/windows_aura.inl"