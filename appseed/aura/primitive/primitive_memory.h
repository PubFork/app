#pragma once


inline strsize safe_strlen(void * p, strsize n)
{

   if (p == NULL)
   {

      return 0;

   }

   const char * psz = (const char *)p;

   strsize i = 0;

   for (; i < n; i++)
   {

      if (psz[i] == '\0')
      {

         break;

      }

   }

   return i;

}



class CLASS_DECL_AURA memory :
   virtual public ::primitive::memory_base
{
public:


   typedef memory data_type;


   bool        m_bAligned;


   memory(::aura::application * papp);
   memory(::aura::application * papp, bool bAligned);
   memory(const byte *,memory_size_t iCount);
   memory(const void *, memory_size_t iCount);
   memory(const memory_base & memorybase);
   memory(const memory & memory);
   memory(const char * psz);
   memory(primitive::memory_container * pmsc = NULL, memory_size_t dwAllocationAddUp = 0, UINT nAllocFlags = 0);
   memory(primitive::memory_container * pmsc, void * pMemory, memory_size_t dwSize);

   memory(manager * pmanager);
   memory(const memory & strSrc, manager * pmanager);
   memory(const memory * pmemory, manager * pmanager);
   memory(const byte * pchSrc, strsize nLength, manager * pmanager);
   memory(struct for_moving) {}

   virtual ~memory();


   //virtual ::object * clone() override;

   virtual LPBYTE impl_alloc(memory_size_t dwAllocation) override;
   virtual LPBYTE impl_realloc(void * pdata, memory_size_t dwAllocation) override;
   virtual void impl_free(LPBYTE pdata) override;


};


// binary string (may contain nulls)
typedef CLASS_DECL_AURA stdstring < memory > bstring;


// binary string (may contain nulls)
class CLASS_DECL_AURA memstring :
   public bstring
{
public:

   inline memstring() {}

   inline memstring(const bstring & bstr)
   {

      allocate(bstr.get_size());
      memcpy(get_data(), bstr.get_data(), get_size());

   }

   inline memstring(const memstring & bstr)
   {

      allocate(bstr.get_size());
      memcpy(get_data(), bstr.get_data(), get_size());

   }

   inline memstring(strsize s, char ch)
   {

      allocate(s);
      memset(get_data(), ch, s);

   }

   inline memstring(const char * psz)
   {

      if (psz != NULL)
      {

         assign(psz, strlen(psz));

      }

   }


   inline memstring(const void * p, strsize start, strsize end)
   {

      assign(p, start, end);

   }

   inline memstring(const void * p, strsize c)
   {

      assign(p, c);

   }

   inline memstring & operator = (const memstring & bstr)
   {

      if (&bstr != this)
      {

         allocate(bstr.get_size());
         memcpy(get_data(), bstr.get_data(), bstr.get_size());

      }

      return *this;

   }

   inline memstring operator + (char ch) const
   {

      memstring bstr(*this);

      bstr.append(&ch, 1);

      return bstr;

   }

   inline memstring operator + (const char * psz) const
   {

      memstring bstr(*this);

      if (psz != NULL)
      {

         bstr.append(psz, strlen(psz));

      }

      return bstr;

   }

   inline memstring & operator += (char ch)
   {

      append(&ch, 1);

      return *this;

   }

   inline memstring & operator += (const char * psz)
   {

      if (psz != NULL)
      {

         append(psz, strlen(psz));

      }

      return *this;

   }

   inline memstring & operator += (const string & str)
   {

      append(str, str.length());

      return *this;

   }

   inline memstring & operator += (const bstring & bstr)
   {

      append(bstr.get_data(), bstr.get_length());

      return *this;

   }

   inline const char * c_str() const
   {

      return (const char *) get_data();

   }

   inline char & operator [](strsize i)
   {

      return (char &) get_data()[i];

   }

   inline const char & operator [](strsize i) const
   {

      return (const char &)get_data()[i];

   }

   inline char * GetBufferSetLength(strsize s)
   {

      allocate(s);

      return (char *) get_data();

   }

   inline void ReleaseBufferSetLength(strsize s = -1)
   {

      ReleaseBuffer(s);

   }

   inline void ReleaseBuffer(strsize s = -1)
   {

      if (s < 0)
      {

         allocate(safe_strlen(get_data(), get_size()));

      }
      else
      {

         allocate(s);

      }

   }

   inline char * data()
   {

      return (char *)get_data();

   }

   inline const char * data() const
   {

      return (const char *)get_data();

   }

   inline bool empty() const
   {

      return get_size() <= 0;

   }


   int compare(const char * psz) const
   {

      if (psz == NULL)
      {

         if (get_data() == NULL)
         {

            return 0;

         }
         else
         {

            return get_data()[0] == '\0' ? 0 : -1;

         }

      }
      else if (get_data() == NULL)
      {

         return *psz == '\0' ? 0 : 1;

      }

      return strncmp((const char *)get_data(), psz, get_size());

   }

   inline bool operator == (const char * psz) const
   {

      return compare(psz) == 0;

   }

   inline bool operator != (const char * psz) const
   {

      return compare(psz) != 0;

   }

   inline bool operator <= (const char * psz) const
   {

      return compare(psz) <= 0;

   }

   inline bool operator < (const char * psz) const
   {

      return compare(psz) < 0;

   }

   inline bool operator >= (const char * psz) const
   {

      return compare(psz) >= 0;

   }

   inline bool operator > (const char * psz) const
   {

      return compare(psz) > 0;

   }


   inline int compare(const bstring & bstr) const
   {

      if (bstr.get_data() == NULL)
      {

         if (get_data() == NULL)
         {

            return 0;

         }
         else
         {

            return bstr.get_data()[0] == '\0' ? 0 : -1;

         }

      }
      else if (get_data() == NULL)
      {

         return bstr.get_data()[0] == '\0' ? 0 : 1;

      }

      int iCmp = memcmp(get_data(), bstr.get_data(), MIN(get_size(), bstr.get_size()));

      if (iCmp == 0)
      {

         iCmp = (int) (get_size() - bstr.get_size());

      }

      return iCmp;

   }

   inline bool operator != (const bstring & bstr) const
   {

      return compare(bstr) != 0;

   }


   inline bool operator == (const bstring & bstr) const
   {

      return compare(bstr) == 0;

   }

   inline bool operator <= (const bstring & bstr) const
   {

      return compare(bstr) <= 0;

   }

   inline bool operator < (const bstring & bstr) const
   {

      return compare(bstr) < 0;

   }

   inline bool operator >= (const bstring & bstr) const
   {

      return compare(bstr) >= 0;

   }

   inline bool operator > (const bstring & bstr) const
   {

      return compare(bstr) > 0;

   }

};




