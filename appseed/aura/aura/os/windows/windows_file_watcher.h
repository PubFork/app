/**
Implementation for Windows. Uses ReadDirectoryChangesW to watch for
file system changes.

@author James Wynn
@date 4/15/2009

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
#pragma once


namespace file_watcher
{

   /// watch
   struct CLASS_DECL_AURA  watch :
      virtual simple_object
   {

      id                   m_id;
      OVERLAPPED           m_overlapped;
      HANDLE               m_hDirectory;
      BYTE                 m_buffer[32 * 1024];
      LPARAM               m_lparam;
      uint32_t             m_dwNotify;
      bool                 m_bRefresh;
      bool                 m_bStop;
      file_watcher_impl *  m_pwatcher;
      sp(listener)         m_plistener;
      bool                 m_bOwn;
      string               m_strDirName;
      bool                 m_bRecursive;

      /// Starts monitoring a directory.
      watch();
      virtual ~watch();

      bool open(LPCTSTR szDirectory, uint32_t dwNotify, bool bRecursive);


      /// Unpacks events and passes them to a user defined callback.
      static void CALLBACK callback(DWORD dwErrorCode, DWORD dwNumberOfBytesTransfered, LPOVERLAPPED lpOverlapped);

      /// Refreshes the directory monitoring.
      bool refresh(bool bClear = false);

      void defer_refresh();

   };

   /// Implementation for Win32 based on ReadDirectoryChangesW.
   /// @class os_file_watcher
   class CLASS_DECL_AURA os_file_watcher :
      virtual public file_watcher_impl
   {
   public:


      /// type for a map from id to watch_struct pointer
      typedef map < id, id, sp(watch),sp(watch)> watch_map;

      /// Map of id to watch_struct pointers
      watch_map            m_watchmap;

      /// The last watchid
      id                   m_idLast;

      sp(::thread)         m_pthread;


      os_file_watcher(::aura::application *papp);
      virtual ~os_file_watcher();


      /// Add a directory watch
      /// @exception FileNotFoundException Thrown when the requested directory does not exist
      id add_watch(const string & directory, listener * watcher,bool bRecursive, bool bOwn);

      /// Remove a directory watch. This is a brute force lazy search O(nlogn).
      void remove_watch(const string & directory);

      void remove_watch(id id);

      string watch_path(id watchid);

      virtual void run();

      /// Updates the watcher. Must be called often.
      virtual bool step();

      /// Handles the action
      void handle_action(action * paction);


   };


} // namespace file_watcher







