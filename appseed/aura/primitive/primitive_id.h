#pragma once


#include "comparison/comparison_equals.h"
#include "comparison/comparison_hash.h"


struct id_all
{

   int64_t            m_iBody;
   int64_t            m_iType;

};

class CLASS_DECL_AURA id
{
public:


   enum e_type : int64_t
   {

      type_null = 0,
      type_empty = 1,
      type_integer = 2,
      type_text = 3

   };


   union
   {
      
      int64_t              m_iId;
      const char *         m_pszId;

      struct
      {

         union
         {
            
            int64_t              m_i;
            const char *         m_psz;
            
         };

         e_type                  m_etype;


      };

      struct
      {

         int64_t            m_iBody;
         int64_t            m_iType;

      };

      id_all                  m_all;

   };

protected:
   friend id_space;
   inline id(const char * psz, id_space *);
public:


   inline id();
   inline id(e_type etype);
   inline id(const id & id);
   id(const char * psz);
   id(int_ptr i);
   id(uint_ptr ui);
#if defined(_LP64) || defined(_AMD64_)
   id(int32_t i);
   id(uint32_t ui);
#endif
   id(const string & str);
//   id(const string_interface & str);
   id(const var & var);


   void raw_set(const char * psz);


   string str() const;
#ifndef __GNUC__
   //operator string() const;
#endif


   inline bool operator == (const id & id) const;
   inline bool operator != (const id & id) const;
   inline bool operator < (const id & id) const;
   inline bool operator <= (const id & id) const;
   inline bool operator > (const id & id) const;
   inline bool operator >= (const id & id) const;
   inline id & operator = (const id & id);


   inline bool operator == (const char * psz) const;
   inline bool operator != (const char * psz) const;
   inline bool operator < (const char * psz) const;
   inline bool operator <= (const char * psz) const;
   inline bool operator > (const char * psz) const;
   inline bool operator >= (const char * psz) const;
   id & operator = (const char * psz);


   inline bool operator == (const string & str) const;
   inline bool operator != (const string & str) const;
   inline bool operator < (const string & str) const;
   inline bool operator <= (const string & str) const;
   inline bool operator > (const string & str) const;
   inline bool operator >= (const string & str) const;
   id & operator = (const string & str);


   inline bool operator == (int_ptr i) const;
   inline bool operator != (int_ptr i) const;
   inline bool operator < (int_ptr i) const;
   inline bool operator <= (int_ptr i) const;
   inline bool operator > (int_ptr i) const;
   inline bool operator >= (int_ptr i) const;
   inline id & operator = (int_ptr i);


#if defined(_LP64) || defined(_AMD64_)


   inline bool operator == (int32_t i) const;
   inline bool operator != (int32_t i) const;
   inline bool operator < (int32_t i) const;
   inline bool operator <= (int32_t i) const;
   inline bool operator > (int32_t i) const;
   inline bool operator >= (int32_t i) const;
   inline id & operator = (int32_t i);


#endif


   //inline bool operator == (const string_interface & str) const;
   //inline bool operator != (const string_interface & str) const;
   //inline bool operator < (const string_interface & str) const;
   //inline bool operator <= (const string_interface & str) const;
   //inline bool operator > (const string_interface & str) const;
   //inline bool operator >= (const string_interface & str) const;

   //id & operator = (const string_interface & str);
   id & operator = (const var & var);
   id & operator = (const property & prop);

#if OSBIT == 32

   inline operator int32_t() const;

#elif OSBIT == 64

   inline operator int64_t() const;

#else

#error "need to implement"

#endif

   inline int64_t i64() const;

   inline int32_t i32() const;


   inline operator const char *() const;
   inline void to_string(string & str) const;
   inline string to_string() const;



   inline bool is_null() const;
   inline bool is_empty() const;
   inline bool has_char() const;
   inline void empty();
   inline void clear();


   inline int_ptr CompareNoCase(const char * psz) const { return compare_ci(psz); }
   inline int_ptr compare_ci(const char * psz) const;


   inline bool is_text() const { return m_etype == type_text; }
   inline bool is_integer() const { return m_etype == type_integer; }

   inline id & operator +=(const char * psz);
   inline id operator +(const id & id) const;

};




inline id::id()
{

   m_all = {};

}


inline id::id(e_type etype) :
   ::id()
{

   if(etype == type_null)
   {

      m_etype = type_null;

   }
   else if(etype == type_empty)
   {

      m_etype = type_empty;

   }
   else if(etype == type_integer)
   {

      m_etype = type_integer;

   }
   else if(etype == type_text)
   {

      operator = ("");

   }

}


inline id::id(const id & id)
{

   m_all = id.m_all;

}

inline id::id(const char * psz,id_space *)
{

   m_all = {};

   m_etype = type_text;
   m_psz    = psz;

}

inline bool id::operator == (const id & id) const
{
   return m_iType == id.m_iType && m_iBody == id.m_iBody;
}

inline bool id::operator != (const id & id) const
{
   return ! operator == (id);
}

inline bool id::operator < (const id & id) const
{
   return m_iType < id.m_iType || ((m_iType == id.m_iType) && m_iBody < id.m_iBody);
}
inline bool id::operator >(const id & id) const
{
   return m_iType > id.m_iType || ((m_iType == id.m_iType) && m_iBody > id.m_iBody);
}
inline bool id::operator <= (const id & id) const
{
   return id > *this;
}
inline bool id::operator >= (const id & id) const
{
   return id < *this;
}

inline id & id::operator = (const id & id)
{
   m_all         = id.m_all;
   return *this;
}


















inline bool id::operator == (const string & str) const
{
   return m_etype == type_text && (m_psz == NULL ? false : str.compare(m_psz) == 0);
}
inline bool id::operator != (const string & str) const
{
   return !operator==(str);
}
inline bool id::operator < (const string & str) const
{
   return (m_etype < type_text) || (m_psz == NULL ? true : str.compare(m_psz) > 0);
}
inline bool id::operator <= (const string & str) const
{
   return !operator > (str);
}
inline bool id::operator > (const string & str) const
{
   return (m_etype > type_text) || (m_psz == NULL ? false : str.compare(m_psz) < 0);
}
inline bool id::operator >= (const string & str) const
{
   return !operator < (str);
}


//inline bool id::operator == (const string_interface & str) const
//{
//   return m_etype == type_text && (m_psz == NULL ? false : string(str).compare(m_psz) == 0);
//}
//inline bool id::operator != (const string_interface & str) const
//{
//   return !operator==(str);
//}
//inline bool id::operator < (const string_interface & str) const
//{
//   return (m_etype < type_text) || (m_psz == NULL ? true : string(str).compare(m_psz) > 0);
//}
//inline bool id::operator <= (const string_interface & str) const
//{
//   return !operator > (str);
//}
//inline bool id::operator > (const string_interface & str) const
//{
//   return (m_etype > type_text) || (m_psz == NULL ? false : string(str).compare(m_psz) < 0);
//}
//inline bool id::operator >= (const string_interface & str) const
//{
//   return !operator < (str);
//}


inline char string::last_char() const
{
   return operator[] (get_length() - 1);
}




inline id::operator const char *() const
{
   return (m_etype != type_text || m_psz == NULL) ? NULL : m_psz;
}


inline void id::to_string(string & strRet) const
{

   strRet =  str();

}

inline string id::to_string() const
{

   return str();

}

//inline string id::to_string() const
//{
//
//   return str();
//
//}























inline bool id::is_empty() const
{
   return is_null() || m_etype == type_empty || (m_etype == type_text && *m_psz == '\0');
}



inline CLASS_DECL_AURA int_ptr id_strcmp(const id * pid1,const id * pid2)
{
   return strcmp(pid1->m_psz,pid2->m_psz);
}

inline void id::raw_set(const char * psz)
{

   m_etype     = type_text;
   m_psz       = psz;

}

inline string id::str() const
{
   if(m_etype == type_null)
   {
      return "(null)";
   }
   else if(m_etype == type_null)
   {
      return "(empty)";
   }
   else if(m_etype == type_text)
   {
      return m_psz;
   }
   else if(m_etype == type_integer)
   {
      return ::str::from(m_i);
   }
   else
   {
      return string("(type:") + ::str::from(m_iType) + ",body:" + ::str::from(m_iBody) + ")";
   }
}


inline bool id::operator == (const char * psz) const
{
   return m_etype == type_text && (m_psz == NULL ? psz == NULL : strcmp(m_psz,psz) == 0);
}
inline bool id::operator != (const char * psz) const
{
   return !operator ==(psz);
}
inline bool id::operator < (const char * psz) const
{
   return m_etype < type_text || (m_etype == type_text && (m_psz == NULL ? psz != NULL : strcmp(m_psz,psz) < 0));
}
inline bool id::operator > (const char * psz) const
{
   return m_etype > type_text || (m_etype == type_text && (m_psz == NULL ? psz == NULL : strcmp(m_psz,psz) > 0));
}
inline bool id::operator <= (const char * psz) const
{
   return !operator>(psz);
}
inline bool id::operator >= (const char * psz) const
{
   return !operator<(psz);
}



#if defined(_LP64) || defined(_AMD64_)

inline bool id::operator == (int32_t i) const
{
   return m_etype == type_integer && m_i == i;
}
inline bool id::operator != (int32_t i) const
{
   return m_etype != type_integer || m_i != i;
}
inline bool id::operator < (int32_t i) const
{
   return m_etype == type_integer && m_i < i;
}
inline bool id::operator <= (int32_t i) const
{
   return m_etype == type_integer && m_i <= i;
}
inline bool id::operator > (int32_t i) const
{
   return m_etype == type_integer && m_i > i;
}
inline bool id::operator >= (int32_t i) const
{
   return m_etype == type_integer && m_i >= i;
}

#endif


inline bool id::operator == (int_ptr i) const
{
   return m_etype == type_integer && m_i == i;
}
inline bool id::operator != (int_ptr i) const
{
   return m_etype != type_integer || m_i != i;
}
inline bool id::operator < (int_ptr i) const
{
   return m_etype == type_integer && m_i < i;
}
inline bool id::operator <= (int_ptr i) const
{
   return m_etype == type_integer && m_i <= i;
}
inline bool id::operator > (int_ptr i) const
{
   return m_etype == type_integer && m_i > i;
}
inline bool id::operator >= (int_ptr i) const
{
   return m_etype == type_integer && m_i >= i;
}

#if OSBIT == 32

inline id::operator int32_t () const
{

   return i32();

}

#elif OSBIT == 64

inline id::operator int64_t () const
{

   return i64();

}

#else

#error "not implemented"

#endif

inline int64_t id::i64() const
{

   return m_etype == type_integer ? m_i : 0x8000000000000000ll;

}

inline int32_t id::i32() const
{

   return m_etype == type_integer ? (int32_t) m_i : 0x80000000;

}



//inline id::operator int_ptr()
//{
//   if(is_number())
//      return m_i;
//   else
//      return 0;
//}

inline bool id::is_null() const
{
   return m_etype == type_null || (m_etype == type_text && m_psz == NULL);
}

inline bool id::has_char() const
{
   return m_etype == type_text && m_psz != NULL && *m_psz != '\0';
}

inline void id::empty()
{
   m_etype  = type_empty;
   m_psz    = NULL;
}

inline void id::clear()
{
   m_all = {};
}


inline CLASS_DECL_AURA id & id::operator += (const char * psz)
{

   *this = *this + psz;

   return *this;

}

inline CLASS_DECL_AURA id id::operator + (const id & id) const
{

   if(is_integer())
   {
      if(id.is_integer())
      {
         return (int_ptr)(m_i + id.m_i);
      }
      else if(id.is_text())
      {
         return ::str::from(m_i) + "." + string(id.m_psz);
      }
      else
      {
         return *this;
      }
   }
   else if(id.is_integer())
   {
      if(is_text())
      {
         return string(m_psz) + "." + ::str::from(id.m_i);
      }
      else
      {
         return id;
      }
   }
   else if(is_text())
   {
      if(id.is_text())
      {
         return string(m_psz) + string(id.m_psz);
      }
      else
      {
         return *this;
      }
   }
   else if(id.is_text())
   {
      return id;
   }
   else
   {
      return ::id();
   }



}



inline int_ptr id::compare_ci(const char * psz) const
{
   if(m_psz == NULL)
   {
      if(psz == NULL)
         return 0;
      else
         return -1;
   }
   else if(psz == NULL)
   {
      return 1;
   }
   else
   {
      return stricmp(m_psz,psz);
   }
}







template < >
inline bool EqualElements< id >(id element1, id element2)
{
   return element1 == element2;
}



template < >
inline UINT HashKey< const id & >(const id & key)
{

   if (key.m_etype == id::type_text)
   {

      return HashKey(key.m_psz);

   }

   return ((((UINT)(uint_ptr)key.m_iType) << 24) & 0xffffffffu) | ((((UINT)(uint_ptr)key.m_iBody) >> 8) & 0xffffffffu);

}

template < >
inline UINT HashKey< id>(id key)
{
   return HashKey<const id & > ((const id &)key);
}
