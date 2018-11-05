#include "framework.h"


namespace draw2d_quartz2d
{
   
   
   pen::pen(sp(::aura::application) papp) :
      ::object(papp)
   {
      
   }
   
   
   pen::~pen()
   {
      
   }
   
   
   
   
#ifdef DEBUG
   
   void pen::dump(dump_context & dumpcontext) const
   {
      
      ::draw2d::object::dump(dumpcontext);
   }
   
#endif
   
   
   
   
} // namespace draw2d_quartz2d




