#include "framework.h"
#include "user_shell_linux.h"




const char * basecore_get_file_icon_path(const char * pszPath, int iSize);
string linux_get_file_icon_path(string strPath, int iSize)
{

   const char* psz = basecore_get_file_icon_path(strPath, iSize);

   if (psz == NULL)
   {
      return "";
   }

   string str = psz;

   free((void*)psz);

   return str;

}

const char * basecore_get_file_content_type(const char * pszFile);
string linux_get_file_content_type(string strPath)
{

   const char* psz = basecore_get_file_content_type(strPath);

   if (psz == NULL)
   {
      return "";
   }

   string str = psz;

   free((void*)psz);

   return str;

}

namespace user
{


   namespace shell
   {


      linux::linux(::aura::application * papp) :
         ::object(papp),
         //::thread(papp),
         m_evKey(papp),
         ::user::shell::shell(papp),
         m_mutexQueue(papp)
      {

         defer_create_mutex();
         //begin();

         //SHGetImageList(SHIL_SMALL, IID_IImageList, m_pilSmall);
         //SHGetImageList(SHIL_LARGE, IID_IImageList, m_pilLarge);
         //SHGetImageList(SHIL_EXTRALARGE, IID_IImageList, m_pilExtraLarge);
         //SHGetImageList(SHIL_JUMBO, IID_IImageList, m_pilJumbo);
         /// SHGetMalloc(&m_pmalloc);

         for (index i = 0; i < get_processor_count() * 2; i++)
         {

            m_threadaGetImage.add(::fork(get_app(),
               [&]()
            {

               ::multithreading::set_priority(::multithreading::priority_highest);
               run();

            }));

         }

      }

      linux::~linux()
      {

      }


      void linux::initialize()
      {


      }

      void linux::defer_start()
      {


      }

      int32_t linux::get_image_by_extension(per_fork * pfork, oswindow oswindow, image_key & key, COLORREF crBk)
      {

         return 0x80000000;

      }




      int32_t linux::get_foo_image(per_fork * pfork, oswindow oswindow, image_key imagekey, COLORREF crBk)
      {

         int32_t iImage;

         wstring wstrFilePath;

         imagekey.m_strPath = "foo";

         imagekey.m_strShellThemePrefix = (char *)m_strShellThemePrefix.c_str();

         {

            synch_lock sl(m_pmutex);

            if (m_imagemap.Lookup(imagekey, iImage))
            {

               return iImage;

            }

         }

//         if (imagekey.m_eattribute.is_signalized(file_attribute_directory))
//         {
//
//            SHGetFileInfoW(
//               L"foo",
//               FILE_ATTRIBUTE_DIRECTORY,
//               &shfi16,
//               sizeof(shfi16),
//               SHGFI_USEFILEATTRIBUTES
//               | SHGFI_ICON
//               | SHGFI_SMALLICON);
//
//            SHGetFileInfoW(
//               L"foo",
//               FILE_ATTRIBUTE_DIRECTORY,
//               &shfi48,
//               sizeof(shfi48),
//               SHGFI_USEFILEATTRIBUTES
//               | SHGFI_ICON
//               | SHGFI_LARGEICON);
//
//         }
//         else
//         {
//
//            wstrFilePath = wstring(L"foo.") + wstring(imagekey.m_pszExtension);
//
//            SHGetFileInfoW(
//               wstrFilePath,
//               FILE_ATTRIBUTE_NORMAL,
//               &shfi16,
//               sizeof(shfi16),
//               SHGFI_USEFILEATTRIBUTES
//               | SHGFI_ICON
//               | SHGFI_SMALLICON);
//
//            SHGetFileInfoW(
//               wstrFilePath,
//               FILE_ATTRIBUTE_NORMAL,
//               &shfi48,
//               sizeof(shfi48),
//               SHGFI_USEFILEATTRIBUTES
//               | SHGFI_ICON
//               | SHGFI_LARGEICON);
//
//         }
         per_fork f(false);
         if (pfork == NULL)
         {
            f.init();
            pfork = &f;

         }
//
//         bool b16 = false;
//         bool b48 = false;
//         iImage = add_icon_set(pfork, &shfi16, &shfi48, crBk, b16, b48);
//         if (!b16 && shfi16.hIcon != NULL)
//         {
//            ::DestroyIcon(shfi16.hIcon);
//         }
//         if (!b48 && shfi48.hIcon != NULL)
//         {
//            ::DestroyIcon(shfi48.hIcon);
//         }         synch_lock sl(m_pmutex);
//
//         m_imagemap.set_at(imagekey, iImage);
//
         return iImage;

      }





      //bool linux::get_icon(
      //   per_fork * pfork,
      //   oswindow oswindow,
      //   IShellFolder * lpsf,
      //   LPITEMIDLIST lpiidlAbsolute,
      //   LPITEMIDLIST lpiidlChild,
      //   const unichar * lpcszExtra,
      //   e_icon eicon,
      //   HICON * phicon16,
      //   HICON * phicon48)
      //{

      //   single_lock sl(m_pmutex, true);

      //   if (lpsf == NULL)
      //      return false;
      //   int32_t iType;
      //   switch (eicon)
      //   {
      //   case icon_normal:
      //      iType = 0;
      //      break;
      //   case icon_open:
      //      iType = GIL_OPENICON;
      //      break;
      //   default:
      //      // unexpected icon type
      //      ASSERT(FALSE);
      //      return false;
      //   }


      //   WCHAR szFilePath[_MAX_PATH * 10];
      //   SHGetPathFromIDListW(
      //      lpiidlAbsolute,
      //      szFilePath);
      //   string strFilePath(szFilePath);

      //   //   WCHAR wszFilePath[_MAX_PATH * 10];
      //   SHGetPathFromIDListW(
      //      lpiidlAbsolute,
      //      szFilePath);

      //   CHAR szPath[_MAX_PATH * 10];
      //   string strPath;
      //   //   int32_t iImage = 0x80000000;

      //   HICON hicon16 = NULL;
      //   HICON hicon48 = NULL;
      //   HRESULT hrIconLocation;
      //   HRESULT hrExtract;
      //   image_key imagekey;


      //   string strPathEx(strFilePath);
      //   string strExtra;

      //   ::str::international::unicode_to_utf8(strExtra, lpcszExtra);

      //   if (strExtra.get_length() > 0)
      //   {
      //      strPathEx += ":" + strExtra;
      //   }



      //   int32_t iIcon = 0x80000000;
      //   UINT uiFlags = 0;

      //   SHFILEINFO shfi16;
      //   SHFILEINFO shfi48;

      //   ::linux::comptr< IExtractIcon > lpiextracticon;

      //   if (SUCCEEDED(lpsf->GetUIObjectOf(
      //      oswindow,
      //      1,
      //      (LPCITEMIDLIST *)&lpiidlChild,
      //      IID_IExtractIcon,
      //      NULL,
      //      lpiextracticon)))
      //   {
      //      if (SUCCEEDED(hrIconLocation = lpiextracticon->GetIconLocation(
      //         iType,
      //         szPath,
      //         sizeof(szPath),
      //         &iIcon,
      //         &uiFlags)))
      //      {
      //         strPath = szPath;
      //         if (strPath == "*")
      //         {
      //            strsize iFind = strFilePath.reverse_find('.');

      //            imagekey.m_iIcon = 0x80000000;
      //            imagekey.m_pszExtension = (char*)&strFilePath[iFind];
      //            imagekey.m_strPath = "";
      //         }
      //         else
      //         {
      //            imagekey.m_strPath = (char *)strPath.c_str();
      //            imagekey.m_iIcon = iIcon;
      //            imagekey.m_pszExtension = NULL;
      //         }
      //      }
      //   }
      //   if (Application.dir().is(::str::international::unicode_to_utf8(szFilePath)))
      //   {
      //      if (imagekey.m_iIcon == 0x80000000)
      //      {
      //         SHGetFileInfo(
      //            "foo",
      //            FILE_ATTRIBUTE_DIRECTORY,
      //            &shfi16,
      //            sizeof(shfi16),
      //            SHGFI_USEFILEATTRIBUTES
      //            | SHGFI_ICON
      //            | SHGFI_SMALLICON);
      //         SHGetFileInfo(
      //            "foo",
      //            FILE_ATTRIBUTE_DIRECTORY,
      //            &shfi48,
      //            sizeof(shfi48),
      //            SHGFI_USEFILEATTRIBUTES
      //            | SHGFI_ICON
      //            | SHGFI_LARGEICON);
      //      }
      //      else
      //      {
      //         strPath = "foo." + string(imagekey.m_pszExtension);
      //         SHGetFileInfo(
      //            strPath,
      //            FILE_ATTRIBUTE_NORMAL,
      //            &shfi16,
      //            sizeof(shfi16),
      //            SHGFI_USEFILEATTRIBUTES
      //            | SHGFI_ICON
      //            | SHGFI_SMALLICON);
      //         SHGetFileInfo(
      //            strPath,
      //            FILE_ATTRIBUTE_NORMAL,
      //            &shfi48,
      //            sizeof(shfi48),
      //            SHGFI_USEFILEATTRIBUTES
      //            | SHGFI_ICON
      //            | SHGFI_LARGEICON);
      //      }
      //      *phicon16 = shfi16.hIcon;
      //      *phicon48 = shfi48.hIcon;
      //   }
      //   else
      //   {
      //      try
      //      {
      //         hicon16 = NULL;
      //         strPath.Truncate(0);
      //         strPath.free_extra();
      //         strPath = imagekey.m_strPath;
      //         iIcon = imagekey.m_iIcon;
      //         bool bExtract = false;
      //         //HGLOBAL hglobal = ::GlobalAlloc(GPTR, strPath.get_length() + 1);
      //         //LPTSTR lpsz = (LPTSTR) ::GlobalLock(hglobal);
      //         //strcpy(lpsz, strPath);
      //         try
      //         {
      //            if ((hrIconLocation == S_OK && !(uiFlags & GIL_NOTFILENAME))
      //               && lpiextracticon.is_null()
      //               && (NOERROR == (hrExtract = lpiextracticon->Extract(
      //                  strPath,
      //                  iIcon,
      //                  &hicon48,
      //                  &hicon16,
      //                  0x00100030)))
      //               )
      //            {
      //               bExtract = true;
      //               *phicon16 = hicon16;
      //               *phicon48 = hicon48;
      //            }
      //         }
      //         catch (...)
      //         {
      //         }
      //         //::GlobalUnlock(hglobal);
      //         //::GlobalFree(hglobal);
      //         if (!bExtract)
      //         {
      //            if (strlen(imagekey.m_strPath) <= 0)
      //            {
      //               SHGetFileInfo(
      //                  (const char *)lpiidlAbsolute,
      //                  FILE_ATTRIBUTE_NORMAL,
      //                  &shfi16,
      //                  sizeof(shfi16),
      //                  SHGFI_PIDL
      //                  | SHGFI_ICON
      //                  | SHGFI_SMALLICON);
      //               hicon16 = shfi16.hIcon;
      //               SHGetFileInfo(
      //                  (const char *)lpiidlAbsolute,
      //                  FILE_ATTRIBUTE_NORMAL,
      //                  &shfi48,
      //                  sizeof(shfi48),
      //                  SHGFI_PIDL
      //                  | SHGFI_ICON
      //                  | SHGFI_LARGEICON);
      //               hicon16 = shfi16.hIcon;
      //               hicon48 = shfi48.hIcon;
      //            }
      //            else
      //            {
      //               ExtractIconEx(
      //                  imagekey.m_strPath,
      //                  imagekey.m_iIcon,
      //                  &hicon48,
      //                  &hicon16,
      //                  1);
      //            }
      //            if (hicon16 == NULL)
      //            {
      //               SHGetFileInfo(
      //                  "foo",
      //                  FILE_ATTRIBUTE_NORMAL,
      //                  &shfi16,
      //                  sizeof(shfi16),
      //                  SHGFI_USEFILEATTRIBUTES
      //                  | SHGFI_ICON
      //                  | SHGFI_SMALLICON);
      //               hicon16 = shfi16.hIcon;
      //            }
      //            if (hicon48 == NULL)
      //            {
      //               SHGetFileInfo(
      //                  "foo",
      //                  FILE_ATTRIBUTE_NORMAL,
      //                  &shfi48,
      //                  sizeof(shfi48),
      //                  SHGFI_USEFILEATTRIBUTES
      //                  | SHGFI_ICON
      //                  | SHGFI_LARGEICON);
      //               hicon48 = shfi48.hIcon;
      //            }
      //            *phicon16 = hicon16;
      //            *phicon48 = hicon48;
      //         }
      //      }
      //      catch (...)
      //      {
      //      }
      //   }

      //   return true;

      //}



      //int32_t linux::get_image(per_fork * pfork, oswindow oswindow, image_key imagekey, LPITEMIDLIST lpiidlAbsolute, const unichar * lpcszExtra, COLORREF crBk)
      //{

      //   int32_t iImage = get_image(pfork, oswindow, imagekey, lpiidlAbsolute, lpiidlChild, lpcszExtra, crBk);

      //   _017ItemIDListFree(pfork, lpiidlChild);

      //   return iImage;

      //}





//      bool linux::get_icon( oswindow oswindow, const char * psz, const unichar * lpcszExtra, e_icon eicon, HICON * phicon16, HICON * phicon48)
//      {
//
//         single_lock sl(m_pmutex, true);
//
//         per_fork fork;
//         LPITEMIDLIST lpiidlAbsolute;
//         _017ItemIDListParsePath(oswindow, &lpiidlAbsolute, psz);
//         bool bGet = get_icon(oswindow, lpiidlAbsolute, lpcszExtra, eicon, phicon16, phicon48);
//         _017ItemIDListFree(&fork, lpiidlAbsolute);
//         return bGet;
//
//      }
//
//      bool linux::get_icon(per_fork * pfork, oswindow oswindow, LPITEMIDLIST lpiidlAbsolute, const unichar * lpcszExtra, e_icon eicon, HICON * phicon16, HICON * phicon48)
//      {
//
//         single_lock sl(m_pmutex, true);
//
//         wstring wstr;
//
////         ::linux::comptr < IShellFolder > lpsf = _017GetShellFolder(wstr, lpiidlAbsolute);
//         ::linux::comptr < IShellFolder > lpsf = _017GetShellFolder(lpiidlAbsolute);
//
//
//         LPITEMIDLIST lpiidlChild = _017ItemIDListGetLast(pfork, lpiidlAbsolute);
//         bool bGet = get_icon(
//            oswindow,
//            lpsf,
//            lpiidlAbsolute,
//            lpiidlChild,
//            lpcszExtra,
//            eicon,
//            phicon16,
//            phicon48);
//
//         _017ItemIDListFree(pfork, lpiidlChild);
//
//         return bGet;
//      }
//


      e_folder linux::get_folder_type(::aura::application * papp, const char * lpcsz)
      {

         return get_folder_type(papp, ::str::international::utf8_to_unicode(lpcsz));

      }


      e_folder linux::get_folder_type(::aura::application * papp, const unichar * lpcszPath)
      {

         string strPath;

         ::str::international::unicode_to_utf8(strPath, lpcszPath);

         if (dir::is(strPath))
         {
            return folder_file_system;
         }
         else
         {
            return folder_none;
         }

      }

      //int linux::run()
      //{

      //   // These images are the Shell standard extra-large icon size. This is typically 48x48, but the size can be customized by the user.

      //   return 0;

      //   while (this->get_thread_run())
      //   {

      //      if (!do_call())
      //      {

      //         Sleep(100);

      //      }

      //      try
      //      {

      //         {

      //         restart:

      //            {

      //               synch_lock sl(m_pmutex);

      //               for (auto & folder : m_mapFolder)
      //               {

      //                  if (get_tick_count() - folder.m_element2.m_dwStart > 30000)
      //                  {

      //                     m_mapFolder.remove_key(folder.m_element1);

      //                     goto restart;

      //                  }

      //               }

      //            }

      //         }

      //         //int i = 20;

      //         //while (thread_get_run() && i >= 0)
      //         //{

      //         //   Sleep(500);

      //         //   i--;

      //         //}


      //      }
      //      catch (...)
      //      {


      //      }


      //   }


      //   return 0;

      //}

      //bool linux::do_call()
      //{

      //   if (m_callCurrent.m_bCall)
      //   {

      //      m_callCurrent.m_iImage = get_image(
      //         m_callCurrent.m_oswindow,
      //         m_callCurrent.m_imagekey,
      //         m_callCurrent.m_lpcszExtra,
      //         m_callCurrent.m_crBk);
      //      m_callCurrent.m_bCall = false;
      //      m_eventReady.SetEvent();

      //      return true;

      //   }

      //   return false;

      //}

      int32_t linux::get_image(per_fork * pfork, oswindow oswindow, image_key imagekey, const unichar * lpcszExtra, COLORREF crBk)
      {

         int32_t iImage = 0x80000000;

         if (::str::begins_ci(imagekey.m_strPath, "uifs:"))
         {

            ::file::path path = Application.dir().matter("cloud.ico");

            for (auto iSize : m_iaSize)
            {


//               HICON hicon = (HICON)LoadImage(NULL, path, IMAGE_ICON, iSize, iSize, LR_LOADFROMFILE);

  //             iImage = add_icon(iSize, hicon, crBk);

            }

            single_lock sl(m_pmutex, true);

            m_imagemap.set_at(imagekey, iImage);

            return iImage;

         }
         else if (::str::begins_ci(imagekey.m_strPath, "fs:"))
         {

            ::file::path path = Application.dir().matter("remote.ico");

            for (auto iSize : m_iaSize)
            {


//               HICON hicon = (HICON)LoadImage(NULL, path, IMAGE_ICON, iSize, iSize, LR_LOADFROMFILE);

  //             iImage = add_icon(iSize, hicon, crBk);

            }

            single_lock sl(m_pmutex, true);

            m_imagemap.set_at(imagekey, iImage);

            return iImage;

         }
         else if (::str::begins_ci(imagekey.m_strPath, "ftp:"))
         {

            ::file::path path = Application.dir().matter("ftp.ico");

            for (auto iSize : m_iaSize)
            {


               //HICON hicon = (HICON)LoadImage(NULL, path, IMAGE_ICON, iSize, iSize, LR_LOADFROMFILE);

               //iImage = add_icon(iSize, hicon, crBk);

            }

            single_lock sl(m_pmutex, true);

            m_imagemap.set_at(imagekey, iImage);

            return iImage;

         }





         if (::str::ends_ci(imagekey.m_strPath, ".core"))
         {
            string str = Application.file().as_string(imagekey.m_strPath);
            if (::str::begins_eat_ci(str, "ca2prompt\r\n"))
            {
               str.trim();
               /*HICON hicon16 = (HICON) ::LoadImage(NULL, Application.dir().matter(str + "/mainframe/icon.ico"), IMAGE_ICON, 16, 16, LR_LOADFROMFILE);
               HICON hicon48 = (HICON) ::LoadImage(NULL, Application.dir().matter(str + "/mainframe/icon.ico"), IMAGE_ICON, 48, 48, LR_LOADFROMFILE);
               synch_lock sl1(m_pil48Hover->m_pmutex);
               synch_lock sl2(m_pil48->m_pmutex);
               iImage = m_pil16->add_icon_os_data(hicon16);
               m_pil48Hover->add_icon_os_data(hicon48);

               if (crBk == 0)
               {
                  System.visual().imaging().Createcolor_blend_ImageList(
                     m_pil48,
                     m_pil48Hover,
                     RGB(255, 255, 240),
                     64);
               }
               else
               {
                  *m_pil48 = *m_pil48Hover;
               }*/

            }
            return iImage;
         }
         // try to find "uifs:// http:// ftp:// like addresses"
         // then should show icon by extension or if is folder
         strsize iFind = imagekey.m_strPath.find_ci("://");
         strsize iFind2 = imagekey.m_strPath.find_ci(":");
         if (iFind >= 0 || iFind2 >= 2)
         {
            string strProtocol = string(imagekey.m_strPath).Left(MAX(iFind, iFind2));
            int32_t i = 0;

            while (i < strProtocol.get_length() && isalnum_dup(strProtocol[i]))
            {

               i++;

            }

            if (i > 0 && i == strProtocol.get_length())
            {

               // heuristically valid protocol
               return get_image_by_extension(pfork, oswindow, imagekey, crBk);

            }

            if (imagekey.m_eattribute.is_signalized(file_attribute_directory))
            {

               return get_image_by_extension(pfork, oswindow, imagekey, crBk);

            }

         }

         string strExtension;

         if (::str::ends_ci(imagekey.m_strPath, ".sln"))
         {
            output_debug_string("test");
         }


         string strIcon48;

         string strIcon16;

         if (::str::ends_ci(imagekey.m_strPath, ".desktop"))
         {

            string str = Application.file().as_string(imagekey.m_strPath);

            stringa stra;

            stra.add_lines(str);

            stra.filter_begins_ci("icon=");

            if (stra.get_size() <= 0)
            {

               return -1;

            }

            string strIcon = stra[0];

            ::str::begins_eat_ci(strIcon, "icon=");

            strIcon48 = strIcon;

            strIcon16 = strIcon;

         }
         else
         {

            strIcon48 = linux_get_file_icon_path(imagekey.m_strPath, 48);

            strIcon16 = linux_get_file_icon_path(imagekey.m_strPath, 16);

         }

         if (strIcon48.has_char())
         {

            ::visual::dib_sp dib1(allocer());

            if (!dib1.load_from_file(strIcon16))
            {

               return -1;

            }

            ::visual::dib_sp dib(allocer());

            if (!dib.load_from_file(strIcon48))
            {

               return -1;

            }

            ::draw2d::dib_sp dib16(allocer());

            if (!dib16->create(16, 16))
            {

               return -1;

            }

            ::draw2d::dib_sp dib48(allocer());

            if (!dib48->create(48, 48))
            {

               return -1;

            }

            dib16->get_graphics()->SetStretchBltMode(HALFTONE);

            dib16->get_graphics()->StretchBlt(0, 0, 16, 16, dib1->get_graphics(), 0, 0, dib1->m_size.cx, dib1->m_size.cy);

            dib48->get_graphics()->SetStretchBltMode(HALFTONE);

            dib48->get_graphics()->StretchBlt(0, 0, 48, 48, dib->get_graphics(), 0, 0, dib->m_size.cx, dib->m_size.cy);

            synch_lock sl1(m_pilHover[48]->m_pmutex);

            synch_lock sl2(m_pil[48]->m_pmutex);

            iImage = m_pil[16]->add_dib(dib16, 0, 0);

            m_pilHover[48]->add_dib(dib48, 0, 0);

            if (crBk == 0)
            {

               System.visual().imaging().Createcolor_blend_ImageList(m_pil[48], m_pilHover[48], RGB(255, 255, 240), 64);

            }
            else
            {

               *m_pil[48] = *m_pilHover[48];

            }

            return iImage;

         }


         string str(imagekey.m_strPath);


         //iImage = GetImageByExtension(oswindow, imagekey.m_strPath, imagekey.m_eicon, imagekey.m_eattribute, crBk);

         return iImage;

      }



      linux::per_fork::per_fork(bool bInit)
      {
        if (bInit)
         {

            init();

         }

      }


      linux::per_fork::~per_fork()
      {

      }


      void linux::per_fork::init()
      {



      }

      int linux::run()
      {

         per_fork fork;




         synch_lock sl(&m_mutexQueue);

         while (get_thread_run())
         {

            if(m_keyptra.is_empty())
            {

               sl.unlock();

               Sleep(100);

            }
            else
            {

              image_key * pkey = m_keyptra.first();

              m_keyptra.remove_at(0);

              sl.unlock();

              int iImage = get_image(&fork, pkey->m_oswindow, *pkey, NULL, pkey->m_cr);

              {

                 synch_lock s(m_pmutex);

                 m_imagemap.set_at(*pkey, iImage);

              }

              delete pkey;

            }

            sl.lock();

         }

         return 0;

      }



      int32_t linux::get_image(oswindow oswindow, const string & strPath, e_file_attribute eattribute, e_icon eicon, COLORREF crBk)
      {

         int32_t iImage = 0x80000000;

         {
            if (argb_get_a_value(crBk) != 255)
            {

               crBk = 0;

            }



            image_key imagekey;

            imagekey.set_path(strPath);

            imagekey.m_strShellThemePrefix = (char *)m_strShellThemePrefix.c_str();

            imagekey.m_eattribute = eattribute;

            imagekey.m_eicon = eicon;

            imagekey.m_iIcon = 0;

            imagekey.m_oswindow = oswindow;

            imagekey.m_cr = crBk;

            {

               synch_lock sl(m_pmutex);

               if (m_imagemap.Lookup(imagekey, iImage))
               {

                  return iImage;

               }

            }

            image_key_store * pstore = new image_key_store(imagekey);

            {

               synch_lock sl(&m_mutexQueue);

               m_keyptra.add(pstore);

            }

            imagekey.set_path("foo");

            iImage = get_foo_image(NULL, oswindow, imagekey, imagekey.m_cr);

            synch_lock sl(m_pmutex);

            m_imagemap.set_at(imagekey, iImage);

         }

         return iImage;


      }





      int32_t linux::get_image_foo(oswindow oswindow, const string & strExtension, e_file_attribute eattribute, e_icon eicon, COLORREF crBk)
      {

         int32_t iImage = 0x80000000;

         {

            if (argb_get_a_value(crBk) != 255)
            {

               crBk = 0;

            }


            image_key imagekey;

            imagekey.m_strPath = "foo";

            imagekey.m_strShellThemePrefix = (char *)m_strShellThemePrefix.c_str();

            imagekey.m_strExtension = strExtension;

            imagekey.m_eattribute = eattribute;

            imagekey.m_eicon = eicon;

            imagekey.m_iIcon = 0;

            {

               synch_lock sl(m_pmutex);

               if (m_imagemap.Lookup(imagekey, iImage))
               {

                  return iImage;

               }

            }

            per_fork f;

            iImage = get_image(&f, oswindow, imagekey, NULL, crBk);

            synch_lock sl(m_pmutex);

            m_imagemap.set_at(imagekey, iImage);

         }

         return iImage;

      }

      int shell::add_hover_image(int iSize, int iImage, COLORREF crBk)
      {

         if (crBk == 0)
         {

            return m_pilHover[iSize]->pred_add_image([&](auto dib)
            { System.visual().imaging().Createcolor_blend_dib(dib, RGB(255, 255, 240), 64); }
            , m_pil[iSize], iImage);

         }
         else
         {

            iImage = m_pilHover[iSize]->add_image(m_pil[iSize], iImage);

            {

               ::draw2d::dib_sp dib(allocer());
               dib->create(iSize, iSize);
               dib->Fill(255, argb_get_r_value(crBk), argb_get_g_value(crBk), argb_get_b_value(crBk));
               dib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);

               m_pilHover[iSize]->draw(dib->get_graphics(), iImage, null_point(), 0);
               m_pilHover[iSize]->m_spdib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);
               m_pilHover[iSize]->m_spdib->get_graphics()->BitBlt(iImage * 48, 0, 48, 48, dib->get_graphics());
               m_pilHover[iSize]->m_spdib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);

            }

            {
               ::draw2d::dib & d = *m_pilHover[iSize]->m_spdib;
               size s = m_pil[iSize]->m_spdib->m_size;
               ::draw2d::dib_sp dib(allocer());
               dib->create(d.size());
               dib->Fill(255, argb_get_r_value(crBk), argb_get_g_value(crBk), argb_get_b_value(crBk));
               dib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);
               dib->get_graphics()->BitBlt(null_point(), d.size(), d.get_graphics());
               dib->get_graphics()->FillSolidRect(0, 0, d.size().cx, d.size().cy, ARGB(123, argb_get_r_value(crBk), argb_get_g_value(crBk), argb_get_b_value(crBk)));
               m_pil[iSize]->m_spdib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);
               m_pil[iSize]->m_spdib->get_graphics()->BitBlt(null_point(), d.size(), dib->get_graphics());
               m_pil[iSize]->m_spdib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);

            }

            return iImage;

         }

      }

   } // namespace shell


} // namespace user







