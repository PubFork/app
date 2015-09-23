#pragma once


#if !defined(METROWIN)

namespace primitive
{


   class CLASS_DECL_AURA shared_memory :
      public ::primitive::memory_base
   {
   public:


      UINT                                   m_nAllocFlags;
   HGLOBAL                                m_hGlobalMemory;
      bool                                   m_bAllowGrow;


      shared_memory(const memory_base & memory);
      shared_memory(memory_container * pmsc = NULL, memory_size_t dwAllocationAddUp = 4096, UINT nAllocFlags = 0);
      shared_memory(memory_container * pmsc, void * pMemory, memory_size_t dwSize);
      shared_memory(const void *, memory_size_t iCount);
      virtual ~shared_memory();


      virtual void SetHandle(HGLOBAL hGlobalMemory, bool bAllowGrow = TRUE);
      virtual BYTE* Alloc(SIZE_T nBytes);
      virtual BYTE* Realloc(BYTE* lpMem, SIZE_T nBytes);
      virtual void Free(BYTE* lpMem);


      LPBYTE detach_shared_memory(HGLOBAL & hglobal);
      virtual bool allocate_internal(memory_size_t dwNewLength);

      HGLOBAL detach();

      void free_data();


   };


} // namespace primitive


#endif


