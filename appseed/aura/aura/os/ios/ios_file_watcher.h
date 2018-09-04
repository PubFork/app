/**
	Implementation header file for OSX based on KEvent.

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


#include <sys/event.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

namespace file_watcher
{
   
   
#define MAX_CHANGE_EVENT_SIZE 2000
   
   typedef struct kevent KEvent;
   
   class watch :
      virtual public ::simple_object
   {
   public:
      
      
      id                         m_id;
      string                     m_strDirName;
      listener *                 m_plistener;
      
      file_watcher *             m_pwatcher;
      
      // index 0 is always the directory
      KEvent                     m_keventaChange[MAX_CHANGE_EVENT_SIZE];
      size_t                     m_iChangeCount;
      

      watch(id watchid, const char * dirname, listener * listener);
      
      
      void addFile(const char * name, bool imitEvents = true);
      
      void removeFile(const char * name, bool imitEvents = true);
      
      // called when the directory is actually changed
      // means a file has been added or removed
      // rescans the watched directory adding/removing files and sending notices
      void rescan();
      
      void handle_action(const char * filename, e_action action);
      
      void addAll();
     
      void removeAll();
      
   };

	/// Implementation for OSX based on kqueue.
	/// @class os_file_watcher
	class os_file_watcher : public file_watcher_impl
	{
	public:
		/// type for a map from id to watch_struct pointer
		typedef map < id ,id, sp(watch), sp(watch) > watch_map;

      /// Map of id to watch_struct pointers
      watch_map m_watchmap;
      /// The descriptor for the kqueue
      int mDescriptor;
      /// time out data
      struct timespec mTimeOut;
      /// id allocator
      id mLastWatchID;
      
      sp(::thread) m_pthread;

		///
		///
      os_file_watcher(::aura::application * papp);

		///
		///
		virtual ~os_file_watcher();

		/// Add a directory watch
		/// @exception FileNotFoundException Thrown when the requested directory does not exist
		id add_watch(const string & directory, listener * watcher, bool bRecursive, bool bOwn) override;

		/// Remove a directory watch. This is a brute force lazy search O(nlogn).
		void remove_watch(const string & directory) override;

		/// Remove a directory watch. This is a map lookup O(logn).
		void remove_watch(id watchid) override;

      string watch_path(id watchid);
      
      
      virtual void defer_start();

		/// Updates the watcher. Must be called often.
		virtual bool update();

		/// Handles the action
		void handle_action(action * paction) override;


	};


} // namespace file_watcher




