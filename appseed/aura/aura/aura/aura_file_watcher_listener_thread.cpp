#include "framework.h"


namespace file_watcher
{

   listener_thread::add::add()
   {

      m_id = -2;

   }

   listener_thread::listener_thread(::aura::application * papp) :
      ::object(papp),
      ::file_watcher::file_watcher(papp)
   {


   }


   listener_thread::~listener_thread()
   {

      for (auto & plistener : m_listenerptra)
      {

         if (plistener->m_pfilewatcherlistenerthread == plistener)
         {

            plistener->m_pfilewatcherlistenerthread = NULL;

         }

      }

   }


   file_watch_id listener_thread::add_file_watch(const char * directory, bool bRecursive)
   {

      return add_file_watch(directory, this, bRecursive);

   }


   file_watch_id listener_thread::add_file_watch(const char * directory, file_watch_listener * plistener, bool bRecursive, bool bOwn)
   {

#if defined(METROWIN) || defined(MACOS)

      return file_watcher::add_watch(directory, plistener, bRecursive, bOwn);

#else

      if(get_os_data() == NULL)
      {

         begin();

      }

      add * padd = new add;

      padd->m_str = directory;
      padd->m_plistener = plistener;
      padd->m_id = -2;
      padd->m_bOwn = bOwn;
      padd->m_bRecursive = bRecursive;

      if (!post_object(message_add_watch, 0, padd))
      {

         TRACE("Failed to add watch");

         return -1;

      }

      for(index i = 0; i < 50 && padd->m_id == -2; i++)
      {

         Sleep((DWORD) (5 + i));

      }

      if (padd->m_id < 0)
      {

         return -1;

      }

      return padd->m_id;

#endif

   }


} // namespace file_watcher




