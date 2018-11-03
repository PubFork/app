#include "framework.h"
#include "dynamic_source.h"


namespace dynamic_source
{


   script_instance::script_instance(script * pscript) :
      ::object(pscript->get_app())
   {

      m_pscript = pscript;

      m_pscriptScriptInstance = pscript;

   }


   script_instance::~script_instance()
   {

   }

   bool script_instance::ShouldBuild()
   {

      return false;

   }

} // namespace dynamic_source



