#include "framework.h"


#ifdef DEBUG


dump_context & operator<<(dump_context & dumpcontext,SIZE size)
{
   dumpcontext << "(" << size.cx << " x " << size.cy << ")";
   
   return dumpcontext;
   
}

dump_context & operator<<(dump_context & dumpcontext,POINT point)
{
   dumpcontext << "(" << point.x << ", " << point.y << ")";
   return dumpcontext;
}

dump_context & operator<<(dump_context & dumpcontext,const RECT& rect)
{
   dumpcontext << "(L " << rect.left << ", T " << rect.top << ", R " <<
          rect.right << ", B " << rect.bottom << ")";
   return dumpcontext;
}


#endif


