/**
   Copyright (c) 2009 James Wynn (james@jameswynn.com)

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to uxse, cxopy, mxodify, mxerge, pxublish, dxistribute, sxublicense, and/or sxell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.

   James Wynn james@jameswynn.com
*/
#include "framework.h"

#include <sys/stat.h>
#include <fcntl.h>
#include <sys/inotify.h>
#include <unistd.h>

#define BUFF_SIZE ((sizeof(struct inotify_event)+FILENAME_MAX)*1024)

namespace file_watcher
{




   os_file_watcher::os_file_watcher(::aura::application * papp) :
      ::object(papp),
      thread(papp)
   {

      m_pDescriptorSet = new fd_set;

      mFD = inotify_init();

      if (mFD < 0)
      {

         fprintf(stderr, "Error: %s\n", strerror(errno));

      }

      mTimeOut.tv_sec = 0;

      mTimeOut.tv_usec = 300 * 1000;

      FD_ZERO((fd_set *) m_pDescriptorSet);


   }


   os_file_watcher::~os_file_watcher()
   {

      multithreading::post_quit_and_wait(seconds(15));

      WatchMap::pair * ppair = m_watchmap.PGetFirstAssoc();

      for(; ppair != NULL; ppair = m_watchmap.PGetNextAssoc(ppair))
      {

         delete ppair->m_element2;

      }

      m_watchmap.remove_all();

      delete (fd_set*) m_pDescriptorSet;

   }


   id os_file_watcher::add_watch(const string & directory,  listener * pwatcher, bool bRecursive, bool bOwn)
   {

      synch_lock sl(m_pmutex);

      int32_t wd = inotify_add_watch (mFD, directory, IN_CLOSE_WRITE | IN_MOVED_TO | IN_CREATE | IN_MOVED_FROM | IN_DELETE);

      if (wd < 0)
      {

         return -1;

         //if (errno == ENOENT)
         //{

         //   _throw(file_not_found_exception(directory));

         //}
         //else
         //{

         //   _throw(exception(strerror(errno)));

         //}

      }

      sp(watch) pWatch = new watch();

      pWatch->m_plistener = pwatcher;
      pWatch->m_id = wd;
      pWatch->m_strDirName = directory;
      pWatch->m_bOwn = bOwn;
      pWatch->m_pwatcher = this;

      if(bRecursive)
      {

         pWatch->m_bRecursive = true;

         ::file::patha stra;

         dir::rls_dir(stra, directory);

         for(index index = 0; index < stra.get_count(); index++)
         {

            int32_t inaw = inotify_add_watch (mFD, stra[index], IN_CLOSE_WRITE | IN_MOVED_TO | IN_CREATE | IN_MOVED_FROM | IN_DELETE);

            if(inaw < 0)
            {
               if(errno == ENOENT)
                  _throw(file_not_found_exception(directory));
               else
                  _throw(exception(strerror(errno)));
            }

            watch_item item;

            item.m_strDirName = stra[index];

            item.m_id = inaw;

            pWatch->m_itema.add(item);

         }

      }
      else
      {

         pWatch->m_bRecursive = false;

      }

      return wd;

   }


   void os_file_watcher::remove_watch(const string & directory)
   {

      synch_lock sl(m_pmutex);

      WatchMap::pair * ppair = m_watchmap.PGetFirstAssoc();

      for(; ppair != NULL; ppair = m_watchmap.PGetNextAssoc(ppair))
      {

         if(directory == ppair->m_element2->m_strDirName)
         {

            remove_watch(ppair->m_element1);

            return;

         }

      }

   }


   void os_file_watcher::remove_watch(id watchid)
   {

      synch_lock sl(m_pmutex);

      WatchMap::pair * ppair = m_watchmap.PLookup(watchid);

      if (ppair == NULL)
      {

         return;

      }

      m_watchmap.remove_key(ppair->m_element1);

      inotify_rm_watch(mFD, watchid);

   }


   string os_file_watcher::watch_path(id id)
   {

      synch_lock sl(m_pmutex);

      return m_watchmap[id]->m_strDirName;

   }


   void os_file_watcher::run()
   {

      while (thread_get_run())
      {

         select();

      }

   }


   bool os_file_watcher::select()
   {

      synch_lock sl(m_pmutex);

      FD_SET(mFD, (fd_set *) m_pDescriptorSet);

      int32_t ret = ::select(mFD + 1,(fd_set *)m_pDescriptorSet,NULL,NULL,&mTimeOut);

      if(ret < 0)
      {

         perror("select");

         return false;

      }
      else if (ret == 0)
      {

         return false;

      }
      else if(FD_ISSET(mFD, (fd_set *) m_pDescriptorSet))
      {

         ssize_t len, i = 0;

         char action[81+FILENAME_MAX] = {0};

         char buff[BUFF_SIZE] = {0};

         len = read (mFD, buff, BUFF_SIZE);

         file_watcher_impl::action a;

         struct inotify_event *pevent = NULL;

         while (i < len)
         {

            pevent = (struct inotify_event *)&buff[i];

            a.m_strFilename = pevent->name;

            a.m_pwatch = m_watchmap[(id &)pevent->wd];

            a.m_ulOsAction = pevent->mask;

            handle_action(&a);

            i += sizeof(struct inotify_event) + pevent->len;

         }

      }

      return true;

   }


   void os_file_watcher::handle_action(action * paction)
   {

      if (!paction->m_pwatch)
      {

         return;

      }

      if (!paction->m_pwatch->m_plistener)
      {

         return;

      }

      if (IN_CLOSE_WRITE & paction->m_ulOsAction)
      {

         paction->m_pwatch->m_plistener->handle_file_action(paction->m_pwatch->m_id, paction->m_pwatch->m_strDirName, paction->m_strFilename, action_modify);

      }

      if (IN_MOVED_TO & paction->m_ulOsAction || IN_CREATE & paction->m_ulOsAction)
      {

         paction->m_pwatch->m_plistener->handle_file_action(paction->m_pwatch->m_id, paction->m_pwatch->m_strDirName, paction->m_strFilename, action_add);

      }

      if (IN_MOVED_FROM & paction->m_ulOsAction || IN_DELETE & paction->m_ulOsAction)
      {

         paction->m_pwatch->m_plistener->handle_file_action(paction->m_pwatch->m_id, paction->m_pwatch->m_strDirName, paction->m_strFilename, action_delete);

      }


   }


} // namespace file_watcher



