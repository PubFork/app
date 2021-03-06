#pragma once


namespace datetime
{


   class CLASS_DECL_AURA zonetime :
      public time
   {
   public:


      __time64_t        m_iZoneOffset;


      static zonetime WINAPI get_current_time(__time64_t iZone) NOTHROW;

      zonetime() NOTHROW;
      zonetime(const zonetime & zonetime) NOTHROW;
      zonetime(__time64_t zonetime, int iZoneOffset) NOTHROW;
      zonetime(int32_t nYear, int32_t nMonth, int32_t nDay, int32_t nHour, int32_t nMin, int32_t nSec, int32_t iZoneOffset);


      struct tm* GetZoneTm(struct tm* ptm) const;


      int32_t GetZoneYear() const NOTHROW;
      int32_t GetZoneMonth() const NOTHROW;
      int32_t GetZoneDay() const NOTHROW;
      int32_t GetZoneHour() const NOTHROW;
      int32_t GetZoneMinute() const NOTHROW;
      int32_t GetZoneSecond() const NOTHROW;
      int32_t GetZoneDayOfWeek() const NOTHROW; // 1 = Sunday, 7 = Saturday

      __time64_t GetZoneTimeOfDay() const NOTHROW;
      int64_t GetZoneDaySig() const NOTHROW;


      string FormatZone(string & str, const string & strFormat) const;
      string FormatZone(const string & strFormat);

   };

   inline string zonetime::FormatZone(const string & strFormat)
   {
      string str;
      FormatZone(str, strFormat);
      return str;
   }


} // namespace datetime


#ifdef DEBUG
CLASS_DECL_AURA dump_context & operator <<(dump_context & dumpcontext, ::datetime::zonetime time);
#endif

CLASS_DECL_AURA stream & operator << (stream & os, ::datetime::zonetime & time);
CLASS_DECL_AURA stream & operator >> (stream & is, ::datetime::zonetime & time);
