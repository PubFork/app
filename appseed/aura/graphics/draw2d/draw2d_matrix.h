#pragma once


namespace draw2d
{


   class CLASS_DECL_AURA matrix
   {
   public:


      enum e_mode
      {

         mode_append,
         mode_prepend,

      };

      union
      {
         struct
         {

            double a1;
            double a2;
            double a3;
            double b1;
            double b2;
            double b3;
            double c1;
            double c2;
            double c3;

         };

         double da[9];

         double a[3][3];

      };


      matrix();
      matrix(const matrix &) = default;


      matrix & operator = (const matrix &) = default;

      static matrix translation(pointd p) { return translation(p.x, p.y); }
      static matrix translation(double x, double y);
      static matrix rotation(double dAngleRadians);
      static matrix scaling(double dRateX, double dRateY);
      static matrix scaling(pointd p) { return scaling(p.x, p.y); }


      matrix & translate(pointd p, e_mode emode = mode_append) { return translate(p.x, p.y, emode); }
      matrix & translate(double x, double y, e_mode emode = mode_append);
      matrix & rotate(double dAngleRadians, e_mode emode = mode_append);
      matrix & scale(double dRateX, double dRateY, e_mode emode = mode_append);
      matrix & scale(point p, e_mode emode = mode_append) { return scale(p.x, p.y, emode); }


      matrix & prepend(const matrix & m);
      matrix & append(const matrix & m);


      matrix & operator * (const matrix & m);

      // 6 (six) elements
      virtual void SetElements(float * fa);


      void transform(point & pt);

      void transform(pointd & pt);

   };


   inline matrix multiplication (const matrix & m1, const matrix & m2)
   {

      matrix m;

      m.a1 = m1.a1 * m2.a1 + m1.a2 * m2.b1 + m1.a3 * m2.c1;
      m.a2 = m1.a1 * m2.a2 + m1.a2 * m2.b2 + m1.a3 * m2.c2;
      m.a3 = m1.a1 * m2.a3 + m1.a2 * m2.b3 + m1.a3 * m2.c3;
      m.b1 = m1.b1 * m2.a1 + m1.b2 * m2.b1 + m1.b3 * m2.c1;
      m.b2 = m1.b1 * m2.a2 + m1.b2 * m2.b2 + m1.b3 * m2.c2;
      m.b3 = m1.b1 * m2.a3 + m1.b2 * m2.b3 + m1.b3 * m2.c3;
      m.c1 = m1.c1 * m2.a1 + m1.c2 * m2.b1 + m1.c3 * m2.c1;
      m.c2 = m1.c1 * m2.a2 + m1.c2 * m2.b2 + m1.c3 * m2.c2;
      m.c3 = m1.c1 * m2.a3 + m1.c2 * m2.b3 + m1.c3 * m2.c3;

      return m;

   }

   inline matrix operator*(const matrix & m1, const matrix & m2)
   {
      return multiplication(m1, m2);
   }

} // namespace draw2d