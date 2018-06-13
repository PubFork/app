#include "framework.h"


namespace draw2d
{

   matrix::matrix()
   {

      a1 = 1.0;
      a2 = 0.0;
      a3 = 0.0;
      b1 = 0.0;
      b2 = 1.0;
      b3 = 0.0;
      c1 = 0.0;
      c2 = 0.0;
      c3 = 1.0;

   }




   matrix matrix::translation(double x, double y)
   {

      matrix m;

      m.c1 = x;

      m.c2 = y;

      return m;

   }

   matrix matrix::rotation(double dAngleDegrees)
   {

      matrix m;

      m.a1 = ::cos(dAngleDegrees);

      m.a2 = ::sin(dAngleDegrees);


      m.b1 = - ::sin(dAngleDegrees);

      m.b2 = ::cos(dAngleDegrees);

      return m;

   }


   matrix matrix::scaling(double dRateX, double dRateY)
   {


      matrix m;

      m.a1 = dRateX;

      m.b2 = dRateY;

      return m;

   }


   matrix & matrix::prepend(const matrix & m)
   {

      operator = (m * *this);

      return *this;
   }


   matrix & matrix::append(const matrix & m)
   {

      operator = (*this * m);

      return *this;

   }

   matrix & matrix::operator * (const matrix & m)
   {

      operator=(multiplication(*this, m));

      return *this;

   }

   void matrix::transform(point & pt)
   {

      point p;

      p.x = pt.x * a1 + pt.y * b1 + c1;
      p.y = pt.x * a2 + pt.y * b2 + c2;

      pt = p;

   }

   void matrix::transform(pointd & pt)
   {

      pointd p;

      p.x = pt.x * a1 + pt.y * b1 + c1;
      p.y = pt.x * a2 + pt.y * b2 + c2;

      pt = p;

   }

   // 6 (six) elements
   void matrix::SetElements(float * fa)
   {

      a1 = fa[0];
      a2 = fa[1];
      b1 = fa[2];
      b2 = fa[3];
      c1 = fa[4];
      c2 = fa[5];


   }

   matrix & matrix::translate(double x, double y, e_mode emode)
   {

      if (emode == mode_prepend)
      {

         return prepend(translation(x, y));

      }
      else
      {
         return append(translation(x, y));

      }

   }


   matrix & matrix::rotate(double dAngleRadians, e_mode emode)
   {

      if (emode == mode_prepend)
      {

         return prepend(rotation(dAngleRadians));

      }
      else
      {

         return append(rotation(dAngleRadians));

      }

   }


   matrix & matrix::scale(double dRateX, double dRateY, e_mode emode)
   {

      if (emode == mode_prepend)
      {

         return prepend(scale(dRateX, dRateY));

      }
      else
      {

         return append(scale(dRateX, dRateY));

      }

   }

} // namespace draw2d




