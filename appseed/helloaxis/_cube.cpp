#include "framework.h"

::aura::application * get_acid_app(::aura::application * papp)
{

   return new ::helloaxis::application();

}


#include "aura/aura/os/windows/windows_axis.inl"