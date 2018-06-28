#pragma once


class plex_heap;



#undef new

class CLASS_DECL_AURA plex_heap_alloc_sync
{
public:


   struct node
   {
#ifdef DEBUG
      char m_puchPalaceLeft[16];
#endif
      node * m_pnext;               // only valid when in free list
#ifdef DEBUG
      char m_puchPalaceRight[16];
#endif
   };


   UINT                       m_nAllocSize;  // size of each block from Alloc
   UINT                       m_nBlockSize;  // number of blocks to get at a time
   plex_heap *                m_pBlocks;     // linked list of blocks (is nBlocks*nAllocSize)
   node*                      m_pnodeFree;   // first free node (NULL if no free nodes)
   critical_section           m_protect;
   int64_t                    m_iFreeHitCount;
   node *                     m_pnodeLastBlock;


   plex_heap_alloc_sync(UINT nAllocSize, UINT nBlockSize = 64);
   virtual ~plex_heap_alloc_sync();

   UINT GetAllocSize() { return m_nAllocSize; }

   inline void * Alloc();               // return a chunk of memory of nAllocSize
   inline void Free(void * p);          // free chunk of memory returned from Alloc
   void FreeAll();               // free everything allocated from this allocator

   void NewBlock();

   void * operator new(size_t s);
   void operator delete(void * p);


};


