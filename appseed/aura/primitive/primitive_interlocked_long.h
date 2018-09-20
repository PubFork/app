#pragma once


class CLASS_DECL_AURA interlocked_long
{
public:


   long *       m_plong;


   interlocked_long();
   virtual ~interlocked_long();


   void add(long l);
   void subtract(long l);


   inline operator long() { return *m_plong; }

   interlocked_long & operator = (long i);
   //bool operator == (long i) const;
   //bool operator > (long i) const;
   //bool operator >= (long i) const;
   //bool operator < (long i) const;
   //bool operator <= (long i) const;
   //bool operator != (long i) const;


   interlocked_long & operator++();
   interlocked_long & operator--();
   long operator++(int);
   long operator--(int);


};




