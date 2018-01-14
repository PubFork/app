#include "framework.h"
//#include <math.h>

point_array::point_array(const POINTD * lppt,::count c)
{
   while(c > 0)
   {
      add((int32_t) lppt->x,(int32_t) lppt->y);
      lppt++;
      c--;
   }
}

point_array::~point_array()
{
}



point64_array::~point64_array()
{
}



pointd_array::~pointd_array()
{
}

