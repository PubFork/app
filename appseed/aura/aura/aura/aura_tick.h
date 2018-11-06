#pragma once


class CLASS_DECL_AURA tick
{
public:


   u64 m_ui;


   tick() {}
   tick(u64 ui) { m_ui = ui; }
   tick(const tick & count) { m_ui = count.m_ui; }

   tick & operator = (u64 ui) { m_ui = ui; return *this; }
   tick & operator = (const tick & tick) { m_ui = tick.m_ui; return *this; }

   operator u64 & () { return m_ui; }

   inline static tick now() { return tick(::get_tick_count()); }

};



namespace lemon
{


   namespace weak
   {


      template < typename TYPE >
      inline TYPE default_value()
      {

         _throw(simple_exception(::get_app(), "template only exception"));

      }

      template <  >
      inline u32 default_value < u32 >()
      {

         return 0;

      }

      template <  >
      inline tick default_value < tick > ()
      {
         // estimate a delay of half of max u32 being quite large
         return get_tick_count() - numeric_info < decltype(tick::m_ui) >::get_maximum_value() / 2;

      }


   } // namespace weak


} // namespace lemon
