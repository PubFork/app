#pragma once

//#pragma pack(show)

#include "setup/debug.h"

#define CA2_AURA

#include "ace/ace.h"

#include "aura_aura.h"

#include "aura_types.h"

#if !defined(METROWIN) && !defined(APPLE_IOS) && !defined(VSNORD) && !defined(SMALLCODE) && !defined(RASPBIAN)

#define HOTPLUGIN_SUBSYSTEM

#endif

#include "aura/aura/os/os_aura.h"

#include "aura/primitive/math/math_math.h"

#include "aura_heap.h"

#include "aura_allocate_processor_cache_oriented.h"

#include "aura/primitive/str/str_c.h"

#include "aura/filesystem/file/file_c.h"

#include "aura/primitive/primitive_memory_c.h"

#include "aura/primitive/datetime/datetime_c.h"

#include "aura_number.h"

#include "aura/aura/aura_policy/aura_policy.h"

#define new AURA_NEW

