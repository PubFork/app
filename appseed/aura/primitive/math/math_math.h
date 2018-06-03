#pragma once


#include "math_count.h"

#include "math_index.h"

#define os_max_int int64_t

CLASS_DECL_AURA os_max_int ceil_div(os_max_int num, os_max_int den);
CLASS_DECL_AURA double tri(double angle);

#ifdef __cplusplus

#include "math_natural.h"

#endif



CLASS_DECL_AURA int ccvt_dup(char * buf,int nchar, double arg, int ndigits,int *decpt,int *sign,int eflag);
CLASS_DECL_AURA int ecvt_dup(char * buf,int nchar, double arg, int ndigits,int *decpt,int *sign);
CLASS_DECL_AURA int fcvt_dup(char * buf,int nchar, double arg, int ndigits,int *decpt,int *sign);
CLASS_DECL_AURA int gcvt_dup(char * buf,int nchar, double arg, int ndigits);
CLASS_DECL_AURA int max_cvt_dup(char *buf,int nchar,double arg,int ndigits,int *decpt,int *sign, int * pi);




#define DOUBLE_PI 3.14159265358979323846

#include <math.h>


namespace degree
{

   inline CLASS_DECL_AURA double to_radian(double dAngleDegrees)
   {

      return dAngleDegrees * DOUBLE_PI / 180.0;

   }

   inline CLASS_DECL_AURA double sin(double dAngleDegrees)
   {

      return ::sin(to_radian(dAngleDegrees));

   }

   inline CLASS_DECL_AURA double cos(double dAngleDegrees)
   {

      return ::cos(to_radian(dAngleDegrees));

   }

   inline CLASS_DECL_AURA double tan(double dAngleDegrees)
   {

      return ::tan(to_radian(dAngleDegrees));

   }

} // namespace degree








