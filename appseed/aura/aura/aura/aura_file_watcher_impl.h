/**
	Basic interface for the file_watcher backend.

	@author James Wynn
	@date 5/11/2009

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

#if defined METROWIN &&  defined(__cplusplus_winrt)
   ref class watch;
   struct watch_holder
   {
      watch ^ w;
   };

#else
   struct watch;
   struct watch_holder
   {
      watch * w;
   };
#endif


   class file_watcher_impl :
      virtual public ::object
   {
   public:

#if defined METROWIN &&  defined(__cplusplus_winrt)


      class action
      {
      public:


         watch ^ watch;
         ::Windows::Storage::Search::IStorageQueryResultBase ^ r;


      };

#else

      class action
      {
      public:

         watch * watch;
         string filename;
         uint32_t ulOsAction;

      };

#endif



      file_watcher_impl();
      virtual ~file_watcher_impl();


      /// Add a directory watch
      /// @exception file_not_found_exception Thrown when the requested directory does not exist
      virtual id add_watch(const string & directory, listener * pwatcher, bool bRecursive, bool bOwn) = 0;

      /// Remove a directory watch. This is a brute force lazy search O(nlogn).
      virtual void remove_watch(const string & directory) = 0;

      virtual void remove_watch(id id) = 0;

      /// Handles the action
      virtual void handle_action(action * paction) = 0;

   };


} // namespace file_watcher

