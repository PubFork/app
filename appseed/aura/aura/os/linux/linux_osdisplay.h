#include "linux_user_impl.h"


#include "aura/os/linux/linux_cross_win_gdi.h"



class CLASS_DECL_AURA osdisplay_data
{
public:


   mutex *                 m_pmutex;
   Display *               m_pdisplay;
   Atom                    m_atomLongType;
   Atom                    m_atomLongStyle;
   Atom                    m_atomLongStyleEx;
   int_ptr                 m_countReference;
   array < MESSAGE >       m_messsageaMouse;
   mutex *                 m_pmutexMouse;

   static osdisplay_dataptra * s_pdataptra;
   static mutex * s_pmutex;

   osdisplay_data();
   ~osdisplay_data();

   Display * display()
   {
      return ::is_null(this) ? NULL : m_pdisplay;
   }

   Display * display() const
   {
      return ::is_null(this) ? NULL : m_pdisplay;
   }

   Atom atom_long_type()
   {
      return ::is_null(this) ? 0 : m_atomLongType;
   }

   Atom atom_long_style()
   {
      return ::is_null(this) ? 0 : m_atomLongStyle;
   }

   Atom atom_long_style_ex()
   {
      return ::is_null(this) ? 0 : m_atomLongStyleEx;
   }

   bool is_null() const
   {
      return ::is_null(this);
   }

   Atom get_window_long_atom(int32_t nIndex);


   Atom intern_atom(const char * pszAtomName, bool bCreate);





   inline int64_t get_ref_count()
   {

      return m_countReference;

   }


   inline int64_t add_ref()
   {

#ifdef WINDOWS

      return InterlockedIncrement64(&m_countReference);

#elif defined(RASPBIAN) && defined(OS32BIT)

      return __sync_add_and_fetch_4(&m_countReference,1);

#else

      return __sync_add_and_fetch(&m_countReference,1);

#endif

   }


   inline int64_t dec_ref()
   {

#ifdef WINDOWS

      return InterlockedDecrement64(&m_countReference);

#elif defined(RASPBIAN) && defined(OS32BIT)

      return __sync_sub_and_fetch_4(&m_countReference,1);

#else

      return __sync_sub_and_fetch(&m_countReference,1);

#endif

   }


   inline int64_t release()
   {

      int64_t i = dec_ref();

      if(i == 0)
      {

         osdisplay_remove(m_pdisplay);

      }

      return i;

   }

};




typedef osdisplay_data * osdisplay;


inline xdisplay::operator Display *()
{

   return m_pdata->m_pdisplay;

}

inline bool xdisplay::is_null()
{

   return m_pdata == NULL;

}


inline bool xdisplay::is_set()
{

   return m_pdata != NULL;

}





class osdisplay_dataptra :
   public ::raw_array < osdisplay_data * >
{
public:

   virtual ~osdisplay_dataptra()
   {

         remove_all();

   }

   void remove_all()
   {

      for(auto p : *this)
      {

         delete p;

      }

      raw_array < osdisplay_data * >::remove_all();
   }

};
