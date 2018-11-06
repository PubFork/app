#pragma once


BEGIN_EXTERN_C

CLASS_DECL_AURA u64 first_tick();
CLASS_DECL_AURA DWORD get_first_tick();
CLASS_DECL_AURA uint64_t get_first_nano();
CLASS_DECL_AURA double first_milli();
CLASS_DECL_AURA DWORD get_tick_count();
CLASS_DECL_AURA u64 get_tick();
CLASS_DECL_AURA DWORD get_fast_tick_count();
CLASS_DECL_AURA uint64_t get_nanos();
CLASS_DECL_AURA double millis_now();


END_EXTERN_C

#define nano_to_tick(nano) ((u64)(((uint64_t)nano / (uint64_t)(1000000))))
#define tick_to_Tick(tick) ((u32)(((u64)tick) % ((u64)0x100000000ULL)))


