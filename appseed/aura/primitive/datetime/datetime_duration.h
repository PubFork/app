#pragma once


class CLASS_DECL_AURA duration
{
public:

   enum e_duration
   {

      duration_infinite,
      duration_dirac,
      duration_finite

   };

   enum e_unit
   {

      unit_nanos,
      unit_micros,
      unit_millis,
      unit_seconds,
      unit_minutes,
      unit_hours,
      unit_days

   };


   e_duration     m_eduration;
   int64_t        m_iNanoseconds;
   int64_t        m_iSeconds;


   explicit duration(double dSeconds);
   duration(int64_t iSeconds = 0, int64_t iNanoSeconds = 0);
   duration(int32_t iSeconds, int32_t iNanoSeconds = 0) :duration((i64)iSeconds, (i64)iNanoSeconds) {}
   duration(uint32_t uiSeconds, uint32_t uiNanoSeconds = 0) :duration((i64)uiSeconds, (i64)uiNanoSeconds) {}
#if !defined(__GNUC__)
   duration(DWORD dwSeconds, DWORD dwNanoSeconds = 0) :duration((i64)dwSeconds, (i64)dwNanoSeconds) {}
#endif
   duration(e_duration eduration);

   inline void raw_set(int64_t iSeconds, int64_t iNanoseconds = 0);
   inline void set(int64_t iSeconds, int64_t iNanoseconds);
   inline void set_null();
   static inline duration raw_create(int64_t iSeconds, int64_t iNanoseconds);
   static inline duration create(int64_t iSeconds, int64_t iNanoseconds);
   static inline duration create_null();

   void fset(double dSeconds);
   void fset(double dSeconds, double dNanoseconds);
   static inline duration fcreate(double dSeconds, double dNanoseconds);

   void set(int64_t i, e_unit eunit);
   void set(double d, e_unit eunit);


   inline int64_t get_total_nanoseconds() const;
   inline int64_t total_nanoseconds() const;
   inline int64_t get_total_microseconds() const;
   inline int64_t total_microseconds() const;
   inline int64_t get_total_milliseconds() const;
   inline int64_t total_milliseconds() const;
   inline int64_t get_total_seconds() const;
   inline int64_t total_seconds() const;
   inline bool is_pos_infinity() const;
   inline static duration infinite();
   inline static duration pos_infinity();
   inline static duration zero();
   inline bool operator == (const duration & duration) const;


   void normalize();

   inline class lock_duration lock_duration() const;
   inline operator class lock_duration() const;

   inline class tick_duration tick_duration() const;
   inline operator class tick_duration() const;

   inline operator bool() const;

   inline duration & operator = (const ::datetime::time_span & span);
   inline duration & operator += (const ::datetime::time_span & duration);
   inline duration & operator -= (const ::datetime::time_span & duration);

   inline __time64_t GetTimeSpan() const;

   duration operator - (const duration & duration) const;

   void sleep();

};


inline duration::duration(int64_t iSeconds, int64_t iNanoSeconds)
{

   m_eduration = duration_finite;

   m_iSeconds = iSeconds;

   m_iNanoseconds = iNanoSeconds;

   normalize();

}


inline duration::duration(double dSeconds)
{

   fset(dSeconds);

}


inline void duration::raw_set(int64_t iSeconds,int64_t iNanoseconds)
{

   m_iSeconds = iSeconds;

   m_iNanoseconds = iNanoseconds;

}


inline void duration::set(int64_t iSeconds,int64_t iNanoseconds)
{

   raw_set(iSeconds, iNanoseconds);

   normalize();

}


inline void duration::set_null()
{

   raw_set(0, 0);

}

inline duration duration::raw_create(int64_t iSeconds,int64_t iNanoseconds)
{

   duration duration;

   duration.raw_set(iSeconds, iNanoseconds);

   return duration;

}



inline duration duration::fcreate(double d,double dNano)
{

   duration duration;

   duration.fset(d, dNano);

   return duration;

}


inline duration duration::create(int64_t iSeconds,int64_t iNanoseconds)
{

   duration duration;

   duration.set(iSeconds, iNanoseconds);

   return duration;

}


inline duration duration::create_null()
{

   duration duration;

   duration.set_null();

   return duration;

}


inline int64_t duration::get_total_milliseconds() const
{

   return m_iSeconds * 1000 + m_iNanoseconds / 1000000;

}


inline int64_t duration::get_total_microseconds() const
{

   return m_iSeconds * 1000000 + m_iNanoseconds / 1000;

}


inline int64_t duration::get_total_nanoseconds() const
{

   return m_iSeconds * 1000 * 1000 * 1000 + m_iNanoseconds;

}


inline lock_duration duration::lock_duration() const
{

   if(is_pos_infinity())
      return INFINITE;

   if(get_total_milliseconds() >= 0xffffffff)
      return 0xfffffffe;

   return (uint32_t) get_total_milliseconds();

}


inline duration::operator ::lock_duration() const
{
   return ::duration::lock_duration();
}

inline tick_duration duration::tick_duration() const
{

   if(is_pos_infinity())
      return 0xffffffff;

   auto uiTotal = get_total_milliseconds();

   if(uiTotal >= ::numeric_info < tick_duration::TYPE >::max())
      return ::numeric_info < tick_duration::TYPE >::max();

   return (tick_duration::TYPE) uiTotal;

}


inline duration::operator ::tick_duration() const
{
   return ::duration::tick_duration();
}


inline int64_t duration::total_milliseconds() const
{
   return get_total_milliseconds();
}


inline int64_t duration::total_microseconds() const
{
   return get_total_microseconds();
}


inline int64_t duration::total_nanoseconds() const
{
   return get_total_nanoseconds();
}


inline bool duration::is_pos_infinity() const
{

   return m_eduration == duration_infinite;

}

inline duration duration::infinite()
{

   return duration_infinite;

}

inline duration duration::pos_infinity()
{

   return duration::raw_create(0x7fffffffffffffffLL, 999999999);

}


inline duration duration::zero()
{

   return duration::create(0, 0);

}


inline bool duration::operator == (const duration & duration) const
{
   const_cast < class duration * >(this)->normalize();
   const_cast < class duration * >(&duration)->normalize();
   return m_iSeconds == duration.m_iSeconds
          && m_iNanoseconds == duration.m_iNanoseconds;
}

class CLASS_DECL_AURA nanos :
   public duration
{
public:


   inline nanos(int64_t iNanos = 0);
   inline nanos(int32_t iNanos);
   inline nanos(uint32_t dwNanos);
   nanos(double dNanos);

};

class CLASS_DECL_AURA micros :
   public duration
{
public:


   inline micros(int64_t iMicros = 0);
   inline micros(int32_t iMicros);
   inline micros(uint32_t dwMicros);
   micros(double dMicros);

};


class CLASS_DECL_AURA millis :
   public duration
{
public:


   inline millis(int64_t iMillis = 0);
   inline millis(int32_t iMillis);
   inline millis(uint32_t dwMillis);
   millis(double dMillis);

};


class CLASS_DECL_AURA seconds :
   public duration
{
public:


   inline seconds(int64_t iSeconds = 0);
   inline seconds(int32_t iSeconds);
   inline seconds(uint32_t dwSeconds);
   seconds(double dSeconds);


};

class CLASS_DECL_AURA one_second :
   public duration
{
public:


   one_second() : duration(1) {}


};



class CLASS_DECL_AURA minutes :
   public duration
{
public:


   inline minutes(int64_t iMinutes = 0);
   inline minutes(int32_t iMinutes);
   inline minutes(uint32_t dwMinutes);
   inline minutes(double dMinutes);


};


class CLASS_DECL_AURA one_minute :
   public duration
{
public:


   one_minute() : duration(60) {}


};




class CLASS_DECL_AURA hours :
   public duration
{
public:


   inline hours(int64_t iHours = 0);
   inline hours(int32_t iHours);
   inline hours(uint32_t dwHours);
   inline hours(double dHours);


};


class CLASS_DECL_AURA one_hour :
   public duration
{
public:


   one_hour() : duration(3600) {}


};

class CLASS_DECL_AURA days :
   public duration
{
public:


   inline days(int64_t iDays = 0);
   inline days(int32_t iDays);
   inline days(uint32_t dwDays);
   inline days(double dDays);


};



inline nanos::nanos(int64_t i) :
   duration(i / (1000 * 1000 * 1000), (i % (1000 * 1000 * 1000)))
{

}


inline nanos::nanos(int32_t i) :
   duration(i / (1000 * 1000 * 1000), (i % (1000 * 1000 * 1000)))
{

}


inline nanos::nanos(uint32_t dw) :
   duration(dw / (1000 * 1000 * 1000), (dw % (1000 * 1000 * 1000)))
{

}


inline micros::micros(int64_t i) :
   duration(i / (1000 * 1000), (i % (1000 * 1000)) * 1000)
{

}


inline micros::micros(int32_t i) :
   duration(i / (1000 * 1000), (i % (1000 * 1000)) * 1000)
{

}


inline micros::micros(uint32_t dw) :
   duration(dw / (1000 * 1000), (dw % (1000 * 1000)) * 1000)
{

}


inline millis::millis(int64_t i) :
   duration(i / 1000, (i % 1000) * 1000000)
{

}


inline millis::millis(int32_t i) :
   duration(i / 1000, (i % 1000) * 1000000)
{

}


inline millis::millis(uint32_t dw) :
   duration(dw / 1000, (dw % 1000) * 1000000)
{

}


inline seconds::seconds(int64_t i) :
   duration(i)
{

}

inline seconds::seconds(int32_t i) :
   duration(i)
{

}

inline seconds::seconds(uint32_t dw) :
   duration(dw)
{

}


inline seconds::seconds(double d) :
   duration(d)
{

}



inline minutes::minutes(int64_t i) :
   duration(i * 60)
{

}

inline minutes::minutes(int32_t i) :
   duration(i * 60)
{

}

inline minutes::minutes(uint32_t dw) :
   duration(dw * 60)
{

}

inline minutes::minutes(double d) :
   duration(d * 60.0)
{

}

inline hours::hours(int64_t i) :
   duration(i * 3600)
{

}

inline hours::hours(int32_t i) :
   duration(i * 3600)
{

}

inline hours::hours(uint32_t dw) :
   duration(dw * 3600)
{

}

inline hours::hours(double d) :
   duration(d * 3600.0)
{

}

inline days::days(int64_t i) :
   duration(i * 86400)
{

}

inline days::days(int32_t i) :
   duration(i * 86400)
{

}

inline days::days(uint32_t dw) :
   duration(dw * 86400)
{

}

inline days::days(double d) :
   duration(d * 86400.0)
{

}

inline __time64_t duration::GetTimeSpan() const
{
   return total_seconds();
}


inline void duration::sleep()
{

   ::Sleep(*this);

}

inline int64_t duration::get_total_seconds() const
{
   return (get_total_milliseconds() + 500) / 1000;
}

inline int64_t duration::total_seconds() const
{
   return (total_milliseconds() + 500) / 1000;
}


inline duration::operator bool() const
{

   return m_iSeconds != 0 || m_iNanoseconds != 0;

}


CLASS_DECL_AURA void Sleep(const duration & duration);













