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
*/
#include "framework.h"


namespace file_watcher
{


   /// Starts monitoring a directory.
   watch::watch()
   {

   }

   watch::~watch()
   {

      m_bRefresh = false;
      m_bStop = TRUE;

      CancelIo(m_hDirectory);

      refresh(true);

      if (!HasOverlappedIoCompleted(&m_overlapped))
      {
         SleepEx(5, TRUE);
      }

      if (m_overlapped.hEvent != INVALID_HANDLE_VALUE)
      {
         CloseHandle(m_overlapped.hEvent);
         m_overlapped.hEvent = INVALID_HANDLE_VALUE;
      }
      if (m_hDirectory != INVALID_HANDLE_VALUE)
      {
         CloseHandle(m_hDirectory);
         m_hDirectory = INVALID_HANDLE_VALUE;
      }

   }


   bool watch::open(LPCTSTR szDirectory, uint32_t dwNotify, bool bRecursive)
   {

      ZERO(m_overlapped);

      m_bRefresh = true;
      m_overlapped.hEvent = INVALID_HANDLE_VALUE;
      m_hDirectory = INVALID_HANDLE_VALUE;

      m_hDirectory = CreateFileW(wstring(szDirectory), FILE_LIST_DIRECTORY,
                                 FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL,
                                 OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED, NULL);

      DWORD dwLen = GetFinalPathNameByHandleW(m_hDirectory, NULL, 0, 0);

      if (dwLen > 0)
      {

         wstring wstr;

         auto * pwsz = wstr.alloc(dwLen + 1);

         if (GetFinalPathNameByHandleW(m_hDirectory, pwsz, dwLen + 1, 0) > 0)
         {

            CloseHandle(m_hDirectory);

            m_hDirectory = CreateFileW(pwsz, FILE_LIST_DIRECTORY,
                                       FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL,
                                       OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED, NULL);

         }


      }

      if (m_hDirectory == INVALID_HANDLE_VALUE)
      {

         return false;

      }

      m_overlapped.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
      m_overlapped.Pointer = this;
      m_dwNotify = dwNotify;
      m_bRecursive = bRecursive;
      m_bStop = false;
      m_bRefresh = true;

      return true;

   }


   /// Unpacks events and passes them to a user defined callback.
   void CALLBACK watch::callback(DWORD dwErrorCode,DWORD dwNumberOfBytesTransfered,LPOVERLAPPED lpOverlapped)
   {
      TCHAR szFile[MAX_PATH];
      PFILE_NOTIFY_INFORMATION pNotify;
      watch* pWatch = (watch*)lpOverlapped->Pointer;
      size_t offset = 0;

      if(dwNumberOfBytesTransfered == 0)
         return;

      if(dwErrorCode == ERROR_SUCCESS)
      {
         do
         {
            pNotify = (PFILE_NOTIFY_INFORMATION)&pWatch->m_buffer[offset];
            offset += pNotify->NextEntryOffset;

#			if defined(UNICODE)
            {
               lstrcpynW(szFile, pNotify->FileName,
                         MIN(MAX_PATH, pNotify->FileNameLength / sizeof(WCHAR) + 1));
            }
#			else
            {
               int32_t count = WideCharToMultiByte2(CP_ACP, 0, pNotify->FileName,
                                                    pNotify->FileNameLength / sizeof(WCHAR),
                                                    szFile, MAX_PATH - 1, NULL, NULL);
               szFile[count] = TEXT('\0');
            }
#			endif

            string strFile = szFile;

            ULONG ulAction = pNotify->Action;

            ::file_watcher::file_watcher_impl::action action;

            action.watch = pWatch;
            action.filename = strFile;
            action.ulOsAction = ulAction;

            pWatch->m_pwatcher->handle_action(&action);

         }
         while(pNotify->NextEntryOffset != 0);

      }

      if(!pWatch->m_bStop)
      {

         pWatch->m_bRefresh = true;

      }

   }

   /// Refreshes the directory monitoring.
   bool watch::refresh(bool bClear)
   {

      return ReadDirectoryChangesW(
             m_hDirectory,
             m_buffer,
             sizeof(m_buffer),
             m_bRecursive ? TRUE : FALSE,
             m_dwNotify,
             NULL,
             &m_overlapped,
             bClear ? 0 : &watch::callback) != 0;

   }


   void watch::defer_refresh()
   {

      if (m_bRefresh)
      {

         refresh();

         m_bRefresh = false;

      }

   }


   os_file_watcher::os_file_watcher(::aura::application * papp) :
      ::object(papp),
      m_idLast(0)
   {

   }

   //--------
   os_file_watcher::~os_file_watcher()
   {

      ::multithreading::post_quit_and_wait(m_pthread, seconds(15));

      //watch_map::pair * ppair = m_watchmap.PGetFirstAssoc();

      //for(; ppair != NULL; ppair = m_watchmap.PGetNextAssoc(ppair))
      //{

      //   delete ppair->m_element2;

      //}

      m_watchmap.clear();

   }


   id os_file_watcher::add_watch(const string & directory,listener* watcher,bool bRecursive, bool bOwn)
   {

      sp(listener) pwatcher(watcher);

      if (m_pthread.is_null())
      {

         m_pthread = fork([this]() { run(); });

      }

      if (directory.is_empty())
      {

         // Intentionally put after possible thread creation.
         // This way add_watch called with empty directory argument,
         // can make provision of thread creation.

         return -1;

      }

      synch_lock sl(m_pmutex);

      sp(watch) pwatch;

      try
      {

         pwatch = canew(watch());

         if (!pwatch->open(directory,
                           FILE_NOTIFY_CHANGE_CREATION
                           | FILE_NOTIFY_CHANGE_SIZE
                           | FILE_NOTIFY_CHANGE_FILE_NAME
                           | FILE_NOTIFY_CHANGE_LAST_WRITE
                           , bRecursive))
         {

            return -1;

         }

      }
      catch (...)
      {


      }

      if (pwatch.is_null())
      {

         return -1;

      }

      pwatch->m_id = ++m_idLast;
      pwatch->m_pwatcher = this;
      pwatch->m_plistener = watcher;
      pwatch->m_strDirName = directory;
      pwatch->m_bOwn = bOwn;

      m_watchmap[pwatch->m_id] = pwatch;

      return pwatch->m_id;

   }


   void os_file_watcher::remove_watch(const string & directory)
   {

      synch_lock sl(m_pmutex);

      watch_map::pair * ppair = m_watchmap.PGetFirstAssoc();

      for(; ppair != NULL; m_watchmap.PGetNextAssoc(ppair))
      {

         if(stricmp(directory,ppair->m_element2->m_strDirName) == 0)
         {

            remove_watch(ppair->m_element1);

            return;

         }

      }

   }


   void os_file_watcher::run()
   {

      while (::get_thread_run())
      {

         step();

      }

   }


   void os_file_watcher::remove_watch(id id)
   {

      synch_lock sl(m_pmutex);

      watch_map::pair * ppair = m_watchmap.PLookup(id);

      if(ppair == NULL)
         return;

      watch * pwatch = ppair->m_element2;

      m_watchmap.remove_key(ppair->m_element1);

      delete pwatch;

   }


   string os_file_watcher::watch_path(id id)
   {

      synch_lock sl(m_pmutex);

      return m_watchmap.PLookup(id)->m_element2->m_strDirName;

   }


   bool os_file_watcher::step()
   {

      MESSAGE msg;

      while (PeekMessage(&msg, NULL, 0, 0, TRUE));

      MsgWaitForMultipleObjectsEx(0,NULL,500,QS_ALLINPUT,MWMO_ALERTABLE);

      if (!::get_thread_run())
      {

         return false;

      }

      watch_map::pair * ppair = m_watchmap.PGetFirstAssoc();

      for (; ppair != NULL; ppair = m_watchmap.PGetNextAssoc(ppair))
      {

         ppair->m_element2->defer_refresh();

      }

      return true;

   }


   void os_file_watcher::handle_action(action * paction)
   {

      watch* watch = paction->watch;
      const char * filename = paction->filename;
      uint32_t action = paction->ulOsAction;
      e_action eaction;

      switch(action)
      {
      case FILE_ACTION_RENAMED_NEW_NAME:
      case FILE_ACTION_ADDED:
         eaction = action_add;
         break;
      case FILE_ACTION_RENAMED_OLD_NAME:
      case FILE_ACTION_REMOVED:
         eaction = action_delete;
         break;
      case FILE_ACTION_MODIFIED:
         eaction = action_modify;
         break;
      };

      watch->m_plistener->handle_file_action(watch->m_id,watch->m_strDirName,filename,eaction);
   }


} // namespace file_watcher




