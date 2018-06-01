﻿#pragma once

#pragma pack(1)

#undef new
class CLASS_DECL_AURA plex_heap     // warning var length structure
{
public:
   plex_heap* pNext;
   // BYTE data[maxNum*elementSize];

   void * data() { return this+1; }

   static plex_heap* create(plex_heap*& head, uint_ptr nMax, uint_ptr cbElement);
   // like 'calloc' but no zero fill
   // may _throw( memory exceptions

   void FreeDataChain();       // free this one and links
};




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

#ifdef WINDOWS

   void * operator new(size_t s)
   {
      return system_heap_alloc(sizeof(plex_heap_alloc_sync));
   }

   void operator delete(void * p)
   {
      system_heap_free(p);
   }

#else

   void * operator new(size_t s)
   {
      return ::malloc(sizeof(plex_heap_alloc_sync));
   }

   void operator delete(void * p)
   {
      return free(p);
   }

#endif

};

CLASS_DECL_AURA void defer_check_plex_heap_alloc_sync_node_palace_guard(plex_heap_alloc_sync::node * pnode, UINT nAllocSize);

inline void * plex_heap_alloc_sync::Alloc()
{

   cslock sl(&m_protect);

   if (m_pnodeFree == NULL)
   {

      NewBlock();

   }

   void * pnode = m_pnodeFree;

#ifdef DEBUG

   defer_check_plex_heap_alloc_sync_node_palace_guard(m_pnodeFree, m_nAllocSize);

   pnode = ((byte*)pnode) + 16 + sizeof(node *) + 16;

#endif

   m_pnodeFree = m_pnodeFree->m_pnext;

   memset(pnode, 0, m_nAllocSize);

   return pnode;

}


inline void plex_heap_alloc_sync::Free(void * pParam)
{

   if (is_null(pParam))
   {

      return;

   }

#ifdef DEBUG

   void * p = ((byte*)pParam) - (16 + sizeof(node *) + 16);

   node * pnode = (node *)p;

   defer_check_plex_heap_alloc_sync_node_palace_guard(pnode, m_nAllocSize);

#else

   node * pnode = (node *)pParam;

#endif

   cslock sl(&m_protect);

#ifdef MEMDFREE // Free Debug - duplicate freeing ?

   node * pnodeFree = m_pnodeFree;

   while (pnodeFree != NULL)
   {

      if (pnode == pnodeFree) // dbgsnp - debug snippet
      {

         // already in free list

         if (is_debugger_attached())
         {

            debug_break();

         }

         return;

      }

      pnodeFree = pnodeFree->m_pnext;

   }

#endif

#if STORE_LAST_BLOCK

   if (m_pnodeLastBlock != NULL)
   {

      system_heap_free(m_pnodeLastBlock);

   }

   m_pnodeLastBlock = (node *)system_heap_alloc(m_nAllocSize + 32);

   memcpy(m_pnodeLastBlock, pnode, m_nAllocSize + 32);

#endif

   pnode->m_pnext = m_pnodeFree;

   m_pnodeFree = pnode;

}


#pragma pack()
