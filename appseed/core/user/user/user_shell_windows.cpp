#include "framework.h"
#include "user_shell_windows.h"


namespace user
{


   namespace shell
   {


      windows::windows(::aura::application * papp) :
         ::object(papp),
         ::user::shell::shell(papp),
         m_mutexImage(papp)
      {

         m_iMaxThreadCount = MAX(4, ::get_processor_count());

         //m_iMaxThreadCount = 1;

         defer_create_mutex();

         m_uiThread = 0;

      }


      windows::~windows()
      {

      }


      windows::thread::thread(windows * pshell) :
         ::object(pshell->get_app()),
         ::thread(pshell->get_app())
      {

         m_pshell = pshell;

         begin();

      }


      windows::thread::~thread()
      {

      }


      bool windows::thread::init_thread()
      {

         m_bSimpleMessageLoop = false;

         if (!::thread::init_thread())
         {

            return false;

         }

         defer_co_initialize_ex(false);

         SHGetDesktopFolder(&m_pfolderDesktop);

         SHGetMalloc(&m_pmalloc);

         SHGetImageList(SHIL_SMALL, IID_IImageList, m_pilSmall);

         SHGetImageList(SHIL_LARGE, IID_IImageList, m_pilLarge);

         SHGetImageList(SHIL_EXTRALARGE, IID_IImageList, m_pilExtraLarge);

         SHGetImageList(SHIL_JUMBO, IID_IImageList, m_pilJumbo);

         return true;

      }


      int32_t windows::thread::get_image_by_extension(oswindow oswindow, image_key & imagekey, COLORREF crBk)
      {

#ifdef WINDOWSEX

         return get_foo_image(oswindow, imagekey, crBk);

#else

         return 0x80000000;

#endif // WINDOWSEX

      }


      // returned image should be "Definitive" icon/image.
      // maybe fallback but not temporary
      int32_t windows::thread::get_image(oswindow oswindow, image_key imagekey, const itemidlist & pidlAbsolute, const itemidlist & pidlChild, const unichar * lpcszExtra, COLORREF crBk)
      {

         comptr < IShellFolder> lpsf;

         lpsf = pidlAbsolute.get_shell_folder();

         if (lpsf.is_null())
         {

            return get_foo_image(oswindow, imagekey, crBk);

         }

         int iImage = 0x80000000;

         int32_t iType;

         switch (imagekey.m_eicon)
         {
         case icon_normal:
            iType = 0;
            break;
         case icon_open:
            iType = GIL_OPENICON;
            break;
         default:
            // unexpected icon type
            ASSERT(FALSE);
            return 0x80000000;
         }

         string strFileParam(imagekey.m_strPath);

         string strResource;

         WCHAR wszPath[_MAX_PATH * 6];

         WCHAR szPath[_MAX_PATH * 6];

         HICON hicon16 = NULL;

         HICON hicon48 = NULL;

         HRESULT hrIconLocation = E_FAIL;

         HRESULT hrExtract = E_FAIL;

         HRESULT hrExtractIconUI = E_FAIL;

         HRESULT hrGetOverlayInfo = E_FAIL;

         HRESULT hrGetLocation = E_FAIL;

         string strExtra;

         string strPathEx;

         strPathEx = strFileParam;

         ::str::international::unicode_to_utf8(strExtra, lpcszExtra);

         if (strExtra.get_length() > 0)
         {

            strPathEx += ":" + strExtra;

         }

         comptr < IExtractIconW > lpiextracticon;

         comptr < IShellIconOverlayIdentifier > lpioverlay;

         comptr < IExtractImage > lpiextractimage;

         UINT uiExtractIconLocationFlags = 0;

         string strIconLocation;

         if (SUCCEEDED(hrExtractIconUI = lpsf->GetUIObjectOf(
                                         oswindow,
                                         1,
                                         (LPCITEMIDLIST *)&pidlChild.m_pidl,
                                         IID_IExtractIconW,
                                         NULL,
                                         lpiextracticon)))
         {

            int iIcon = 0;

            if (SUCCEEDED(hrIconLocation = lpiextracticon->GetIconLocation(
                                           iType,
                                           wszPath,
                                           sizeof(wszPath) / sizeof(wszPath[0]),
                                           &iIcon,
                                           &uiExtractIconLocationFlags)))
            {

               if (wcscmp(wszPath, L"*") == 0)
               {

                  imagekey.m_iIcon = 0x80000000;

                  imagekey.set_extension(strFileParam);

                  imagekey.m_strPath = "";

               }
               else
               {

                  strIconLocation = expand_env(wszPath);

                  imagekey.set_path(strIconLocation);

                  imagekey.m_iIcon = iIcon;

                  imagekey.m_strExtension = "";

               }

            }

         }

         if(FAILED(hrIconLocation))
         {

            if (SUCCEEDED(lpsf->GetUIObjectOf(
                          oswindow,
                          1,
                          (LPCITEMIDLIST *)&pidlChild.m_pidl,
                          IID_IShellIconOverlayIdentifier,
                          NULL,
                          lpioverlay)))
            {

               int iIndex = 0;

               DWORD dwFlags = 0;

               if (SUCCEEDED(hrGetOverlayInfo = lpioverlay->GetOverlayInfo(
                                                wszPath,
                                                sizeof(wszPath),
                                                &iIndex,
                                                &dwFlags)))
               {

                  if (wcscmp(wszPath, L"*") == 0)
                  {

                     imagekey.m_iIcon = 0x80000000;

                     imagekey.set_extension(strFileParam);

                     imagekey.m_strPath = "";

                  }
                  else
                  {

                     imagekey.set_path(expand_env(szPath));

                     imagekey.m_iIcon = iIndex;

                     imagekey.m_strExtension = "";

                  }

               }

            }
            else
            {

               if (SUCCEEDED(lpsf->GetUIObjectOf(
                             oswindow,
                             1,
                             (LPCITEMIDLIST *)&pidlChild.m_pidl,
                             IID_IExtractImage,
                             NULL,
                             lpiextractimage)))
               {

                  SIZE s;

                  s.cx = 48;

                  s.cy = 48;

                  DWORD dwDepth = 32;

                  DWORD dwFlags = 0;

                  if (SUCCEEDED(hrGetLocation = lpiextractimage->GetLocation(
                                                wszPath,
                                                sizeof(wszPath),
                                                NULL,
                                                &s,
                                                dwDepth,
                                                &dwFlags)))
                  {


                     if (wcscmp(wszPath, L"*") == 0)
                     {

                        imagekey.m_iIcon = 0x80000000;

                        imagekey.set_path(strFileParam);

                        imagekey.m_strPath = "";

                     }
                     else
                     {

                        imagekey.set_path(expand_env(wszPath));

                        imagekey.m_iIcon = 0;

                        imagekey.m_strExtension = "";

                     }

                  }

               }
               else
               {

                  imagekey.set_path(strFileParam);

                  imagekey.m_iIcon = 0;

               }

            }

         }

         string strTarget;

         if (((FAILED(hrIconLocation) && FAILED(hrGetLocation))

               || imagekey.m_iIcon == 0x80000000

               || !Application.file().exists(strIconLocation))

               && ::str::ends_ci(strFileParam, ".lnk"))

         {

            string strFolder;

            string strParams;

            System.file().resolve_link(strTarget, strFolder, strParams, strFileParam, NULL);

            if (!Application.file().exists(strTarget) && !Application.dir().is(strTarget))
            {

               if (strTarget.ends_ci(".exe"))
               {

                  imagekey.set_path(strTarget);

               }
               else
               {

                  imagekey.set_path("");

               }

               iImage = get_foo_image(oswindow, imagekey, crBk);

               return iImage;

            }

            if (FAILED(hrIconLocation) && FAILED(hrGetLocation))
            {

               imagekey.set_path(strTarget);

               iImage = get_image(oswindow, imagekey, lpcszExtra, crBk);

               return iImage;

            }

         }
         else
         {

            strTarget = strFileParam;

         }

         if (imagekey.m_iIcon == 0x80000000)
         {

            if (imagekey.m_strShellThemePrefix.has_char())
            {

               string strExtension = file_extension_dup(strTarget);

               image_key imagekeyTheme;

               string strFooPath = imagekey.m_strShellThemePrefix + "foo." + strExtension;

               imagekeyTheme.set_path(strFooPath);

               imagekeyTheme.m_iIcon = 0;

               if (m_pshell->contains_image(imagekeyTheme, iImage))
               {

                  return iImage;

               }

               string strIcon;

               strIcon = ::dir::system() / "config/shell/app_theme" / imagekey.m_strShellThemePrefix + strExtension + ".ico";

               if (Application.file().exists(strIcon))
               {

                  if (m_pshell->reserve_image(imagekeyTheme, iImage))
                  {

                     m_pshell->add_icon_path(strIcon, crBk, iImage);

                  }

                  return iImage;

               }

            }

            if (wcscmp(wszPath, L"*") == 0)
            {

               return get_foo_image(oswindow, imagekey, crBk);

            }

         }

         if (uiExtractIconLocationFlags & GIL_NOTFILENAME)
         {

            if (m_pshell->reserve_image(imagekey, iImage))
            {

               HICON hicon = NULL;

               HRESULT hrExtract = E_FAIL;

               synch_lock sl(m_pshell->m_pmutex);

               auto iaSize = m_pshell->m_iaSize;

               sl.unlock();

               for (auto iSize : iaSize)
               {

                  if (iSize <= 16)
                  {

                     if (SUCCEEDED(hrExtract = lpiextracticon->Extract(
                                               wszPath,
                                               imagekey.m_iIcon,
                                               NULL,
                                               &hicon,
                                               iSize << 16)))
                     {

                        m_pshell->add_icon(iSize, hicon, crBk, iImage);

                        ::DestroyIcon(hicon);

                     }

                  }
                  else
                  {

                     if (SUCCEEDED(hrExtract = lpiextracticon->Extract(
                                               wszPath,
                                               imagekey.m_iIcon,
                                               &hicon,
                                               NULL,
                                               iSize)))
                     {

                        m_pshell->add_icon(iSize, hicon, crBk, iImage);

                        ::DestroyIcon(hicon);

                     }

                  }

               }

            }

            return iImage;

         }
         else if(strIconLocation.has_char())
         {

            if(strIconLocation.ends_ci(".ico"))
            {

               image_key imagekeyIco;

               imagekeyIco.set_path(strIconLocation, false);

               imagekeyIco.m_iIcon = 0;

               if (m_pshell->reserve_image(imagekeyIco, iImage))
               {

                  m_pshell->add_icon_path(strIconLocation, crBk, iImage);

               }

               return iImage;

            }
            else
            {

               image_key imagekeyIco;

               imagekeyIco.set_path(strIconLocation, false);

               imagekeyIco.m_iIcon = imagekey.m_iIcon;

               if (m_pshell->reserve_image(imagekeyIco, iImage))
               {

                  synch_lock sl(m_pshell->m_pmutex);

                  auto iaSize = m_pshell->m_iaSize;

                  sl.unlock();

                  for (auto iSize : iaSize)
                  {

                     int iSizeOut = iSize;

                     HICON hicon = (HICON)ExtractResourceIcon(strIconLocation, iSizeOut, iSizeOut, imagekey.m_iIcon);

                     m_pshell->add_icon(iSize, hicon, crBk, iImage);

                     ::DestroyIcon(hicon);

                  }

               }

               return iImage;

            }

         }

         //if (imagekey.m_iIcon >= 0 && strFileParam.get_length() > 0)
         //{

         //   SHFILEINFOW shfi16;

         //   SHFILEINFOW shfi48;

         //   wstring wstrPath(strFileParam);

         //   SHGetFileInfoW(
         //   wstrPath,
         //   FILE_ATTRIBUTE_NORMAL,
         //   &shfi16,
         //   sizeof(shfi16),
         //   SHGFI_ICON
         //   | SHGFI_SMALLICON);

         //   SHGetFileInfoW(
         //   wstrPath,
         //   FILE_ATTRIBUTE_NORMAL,
         //   &shfi48,
         //   sizeof(shfi48),
         //   SHGFI_ICON
         //   | SHGFI_LARGEICON);

         //   bool b16 = false;

         //   bool b48 = false;

         //   if (shfi16.hIcon != NULL || shfi48.hIcon != NULL)
         //   {

         //      if (m_pshell->reserve_image(imagekey, iImage))
         //      {

         //         m_pshell->add_icon_set(&shfi16, &shfi48, crBk, b16, b48, iImage);

         //         if (!b16 && shfi16.hIcon != NULL)
         //         {

         //            ::DestroyIcon(shfi16.hIcon);

         //         }

         //         if (!b48 && shfi48.hIcon != NULL)
         //         {

         //            ::DestroyIcon(shfi48.hIcon);

         //         }


         //      }

         //   }

         //}

         imagekey.set_extension(strTarget);

         imagekey.m_strPath = NULL;

         imagekey.m_iIcon = 0;

         return get_foo_image(oswindow, imagekey, crBk);

      }


      int32_t windows::thread::get_foo_image(oswindow oswindow, image_key & imagekey, COLORREF crBk)
      {

         int32_t iImage;

         if (m_pshell->reserve_image(imagekey, iImage))
         {

            SHFILEINFOW shfi16 = {};

            SHFILEINFOW shfi48 = {};

            wstring wstrFilePath;

            if (imagekey.m_eattribute.is_signalized(file_attribute_directory))
            {

               SHGetFileInfoW(
               L"foo",
               FILE_ATTRIBUTE_DIRECTORY,
               &shfi16,
               sizeof(shfi16),
               SHGFI_USEFILEATTRIBUTES
               | SHGFI_ICON
               | SHGFI_SMALLICON);

               SHGetFileInfoW(
               L"foo",
               FILE_ATTRIBUTE_DIRECTORY,
               &shfi48,
               sizeof(shfi48),
               SHGFI_USEFILEATTRIBUTES
               | SHGFI_ICON
               | SHGFI_LARGEICON);

            }
            else
            {

               wstrFilePath = wstring(L"foo.") + wstring(imagekey.m_strExtension);

               SHGetFileInfoW(
               wstrFilePath,
               FILE_ATTRIBUTE_NORMAL,
               &shfi16,
               sizeof(shfi16),
               SHGFI_USEFILEATTRIBUTES
               | SHGFI_ICON
               | SHGFI_SMALLICON);

               SHGetFileInfoW(
               wstrFilePath,
               FILE_ATTRIBUTE_NORMAL,
               &shfi48,
               sizeof(shfi48),
               SHGFI_USEFILEATTRIBUTES
               | SHGFI_ICON
               | SHGFI_LARGEICON);

            }

            bool b16 = false;

            bool b48 = false;

            add_icon_set(&shfi16, &shfi48, crBk, b16, b48, iImage);

            if (shfi16.hIcon != NULL)
            {

               ::DestroyIcon(shfi16.hIcon);

            }

            if (shfi48.hIcon != NULL)
            {

               ::DestroyIcon(shfi48.hIcon);

            }

         }

         return iImage;

      }


      //index windows::GetCSIDL(LPITEMIDLIST lpiidl)
      //{
      //   LPITEMIDLIST ppidl;

      //   int32_t csidla[] =
      //   {
      //      CSIDL_DESKTOP,
      //      CSIDL_DRIVES,
      //      CSIDL_PERSONAL,
      //      CSIDL_NETHOOD,
      //      CSIDL_NETWORK,
      //      CSIDL_BITBUCKET,
      //      -1,
      //   };

      //   int32_t * pcsidl = csidla;

      //   while (*pcsidl != -1)
      //   {
      //      if (SUCCEEDED(SHGetSpecialFolderLocation(
      //                    NULL,
      //                    *pcsidl,
      //                    &ppidl)))
      //      {
      //         if (_017ItemIDListIsEqual(ppidl, lpiidl))
      //         {
      //            m_pmalloc->Free(ppidl);
      //            break;
      //         }
      //         m_pmalloc->Free(ppidl);
      //      }
      //      pcsidl++;
      //   }

      //   return *pcsidl;


      //}


      //index windows::GetCSIDLSort(index iCsidl)
      //{
      //   switch (iCsidl)
      //   {
      //   case CSIDL_DESKTOP:
      //      return 100;
      //   case CSIDL_PERSONAL:
      //      return 200;
      //   case CSIDL_DRIVES:
      //      return 300;
      //   case CSIDL_NETHOOD:
      //      return 1000;
      //   default:
      //      return 2000 + iCsidl;
      //   }

      //}


      //void windows::GetAscendants(LPITEMIDLIST lpiidl, array < LPITEMIDLIST, LPITEMIDLIST > & lpiidla)
      //{

      //   if (lpiidl == NULL)
      //      return;

      //   for (;;)
      //   {
      //      lpiidl = _017ItemIDListGetFolderParent(lpiidl);
      //      if (lpiidl == NULL)
      //         break;
      //      lpiidla.add(lpiidl);
      //   }

      //}


      //void windows::Free(array < LPITEMIDLIST, LPITEMIDLIST > & lpiidla)
      //{

      //   for (int32_t i = 0; i < lpiidla.get_size(); i++)
      //   {

      //      m_pmalloc->Free(lpiidla[i]);

      //   }

      //   lpiidla.remove_all();

      //}


      e_folder windows::get_folder_type(::aura::application * papp, const char * lpcsz)
      {

         return get_folder_type(papp, ::str::international::utf8_to_unicode(lpcsz));

      }


      e_folder windows::get_folder_type(::aura::application * papp, const unichar * lpcszPath)
      {

         string strPath;

         ::str::international::unicode_to_utf8(strPath, lpcszPath);

         if (dir::is(strPath))
         {

            return folder_file_system;

         }
         else if (zip::util().is_unzippable(papp, strPath))
         {

            return folder_zip;

         }
         else
         {

            return folder_none;

         }

      }


      int32_t windows::thread::get_image(oswindow oswindow, image_key imagekey, const unichar * lpcszExtra, COLORREF crBk)
      {

         int32_t iImage = 0x80000000;

         if (::str::begins_ci(imagekey.m_strPath, "uifs:"))
         {

            if (m_pshell->reserve_image(imagekey, iImage))
            {

               ::file::path path = Application.dir().matter("cloud.ico");

               m_pshell->add_icon_path(path, crBk, iImage);

            }

            return iImage;

         }
         else if (::str::begins_ci(imagekey.m_strPath, "fs:"))
         {

            if (m_pshell->reserve_image(imagekey, iImage))
            {

               ::file::path path = Application.dir().matter("remote.ico");

               m_pshell->add_icon_path(path, crBk, iImage);

            }

            return iImage;

         }
         else if (::str::begins_ci(imagekey.m_strPath, "ftp:"))
         {

            if (m_pshell->reserve_image(imagekey, iImage))
            {

               ::file::path path = Application.dir().matter("ftp.ico");

               m_pshell->add_icon_path(path, crBk, iImage);

            }

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
               Application.imaging().Createcolor_blend_ImageList(
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

         // Check for URL addresses like uifs://, http://, or ftp://
         // Except A: B: C: (Windows drive letters)
         // And then should find icon by extension if
         // it is a file or as folder otherwise.

         strsize iFind = imagekey.m_strPath.find_ci("://");

         strsize iFind2 = imagekey.m_strPath.find_ci(":");

         if (iFind >= 0 || iFind2 >= 2)
         {

            string strProtocol = imagekey.m_strPath.Left(MAX(iFind, iFind2));

            int32_t i = 0;

            while (i < strProtocol.get_length() && isalnum_dup(strProtocol[i]))
            {

               i++;

            }

            if (i > 0 && i == strProtocol.get_length())
            {

               // heuristically valid protocol
               return get_image_by_extension(oswindow, imagekey, crBk);

            }

            if (imagekey.m_eattribute.is_signalized(file_attribute_directory))
            {

               return get_image_by_extension(oswindow, imagekey, crBk);

            }

         }

         string strExtension;

         if (::str::ends_ci(imagekey.m_strPath, ".sln"))
         {

            output_debug_string("test");

         }

         string str(imagekey.m_strPath);

         if (str == "foo")
         {

            return get_foo_image(oswindow, imagekey, crBk);

         }

         if (::str::begins_eat(str, "foo."))
         {

            return get_foo_image(oswindow, imagekey, crBk);

         }

         ::file::path path = imagekey.m_strPath;

         ::file::path pathFolder = path.folder();

         itemidlist idlist;

         bool bParseError = false;

         try
         {

            idlist.parse(imagekey.m_strPath);

         }
         catch (...)
         {

            bParseError = true;

         }

         if (bParseError)
         {

            return get_foo_image(oswindow, imagekey, crBk);

         }


         itemidlist idlistAbsolute;

         idlistAbsolute = idlist - 1;

         itemidlist idlistChild;

         idlistChild = idlist.last();

         iImage = get_image(oswindow, imagekey, idlistAbsolute, idlistChild, lpcszExtra, crBk);

         return iImage;

      }


      //int32_t _017ItemIDListGetLen(LPITEMIDLIST lpiidl)
      //{
      //   if (lpiidl == NULL)
      //      return 0;
      //   LPSHITEMID  lpshiid = (LPSHITEMID)lpiidl;
      //   LPSHITEMID  lpshiidLast = NULL;
      //   USHORT cb;
      //   int32_t iLen = 0;
      //   while (true)
      //   {
      //      cb = lpshiid->cb;
      //      iLen += cb;
      //      if (cb == 0)
      //         break;
      //      lpshiidLast = lpshiid;
      //      lpshiid = (LPSHITEMID)(((LPBYTE)lpshiid) + cb);

      //   }

      //   return iLen;

      //}


      void windows::initialize()
      {

         add_thread();

      }


      void windows::add_thread()
      {

         synch_lock sl(m_pmutex);

         m_threadptra.add(canew(thread(this)));

         m_uiThread = m_threadptra.get_upper_bound();

      }


      int32_t windows::thread::get_image(oswindow oswindow, const image_key & imagekey, COLORREF crBk)
      {

         int iImage;

         synch_lock sl(m_pshell->m_pmutex);

         if (m_pshell->m_imagemap.Lookup(imagekey, iImage))
         {

            if (iImage == 0x80000001)
            {

               iImage = 0x80000000;

            }

            return iImage;

         }

         image_key imagekeyStore(imagekey);

         m_pshell->m_imagemap.set_at(imagekeyStore, 0x80000001); // mark as "calculating image"

         schedule_pred([=]()
         {

            InterlockedIncrement64(&m_pshell->m_iActiveThreadCount);

            try
            {

               int iImage = get_image(oswindow, imagekeyStore, NULL, crBk);

               synch_lock sl(m_pshell->m_pmutex);

               if (iImage & 0x80000000)
               {

                  m_pshell->m_imagemap.remove_key(imagekeyStore);

               }
               else
               {

                  m_pshell->m_imagemap.set_at(imagekeyStore, iImage);

               }

            }
            catch (...)
            {

            }

            InterlockedDecrement64(&m_pshell->m_iActiveThreadCount);

         });

         return 0x80000000;

      }


      int32_t windows::get_image(oswindow oswindow, const image_key & imagekey, COLORREF crBk)
      {

         synch_lock sl(m_pmutex);

         if (m_threadptra.get_count() < m_iMaxThreadCount)
         {

            bool bMax = m_iActiveThreadCount >= m_threadptra.get_count();

            if (bMax)
            {

               if (!m_bMax)
               {

                  m_bMax = true;

                  m_dwLastMax = get_tick_count();

               }
               else if (get_tick_count() - m_dwLastMax > 50)
               {

                  add_thread();

               }

            }
            else
            {

               m_bMax = false;

            }

         }

         UINT uiThread = m_uiThread;

         uiThread = uiThread % m_threadptra.get_size();

         int32_t iImage = m_threadptra[uiThread]->get_image(oswindow, imagekey, crBk);

         uiThread++;

         m_uiThread = uiThread;

         return iImage;

      }


      int32_t windows::get_image(oswindow oswindow, const string & strPath, e_file_attribute eattribute, e_icon eicon, COLORREF crBk)
      {

         int32_t iImage = 0x80000000;

         if (argb_get_a_value(crBk) != 255)
         {

            crBk = 0;

         }

         synch_lock sl(m_pmutex);

         image_key imagekey;

         imagekey.set_path(strPath);

         imagekey.m_strShellThemePrefix = m_strShellThemePrefix;

         imagekey.m_eattribute = eattribute;

         imagekey.m_eicon = eicon;

         imagekey.m_iIcon = 0;

         imagekey.m_oswindow = oswindow;

         imagekey.m_cr = crBk;

         return get_image(oswindow, imagekey, crBk);

      }


      bool windows::contains_image(const image_key & imagekey, int32_t & iImage)
      {

         synch_lock sl(m_pmutex);

         if (m_imagemap.Lookup(imagekey, iImage))
         {

            return true;

         }

         return false;

      }


      bool windows::reserve_image(const image_key & imagekey, int32_t & iImage)
      {

         synch_lock sl(m_pmutex);

         if (contains_image(imagekey, iImage))
         {

            return false;

         }

         iImage = _reserve_image(imagekey);

         return true;

      }


      int windows::_reserve_image(const image_key & key)
      {

         synch_lock sl(m_pmutex);

         int iImage = -1;

         for (auto iSize : m_iaSize)
         {

            iImage = m_pil[iSize]->reserve_image(iImage);

            iImage = m_pilHover[iSize]->reserve_image(iImage);

         }

         m_imagemap.set_at(key, iImage);

         return iImage;

      }


      int windows::thread::add_icon_set(SHFILEINFOW * pinfo16, SHFILEINFOW * pinfo48, COLORREF crBk, bool & bUsed16, bool & bUsed48, int iImage)
      {

         synch_lock sl(m_pshell->m_pmutex);

         auto iaSize = m_pshell->m_iaSize;

         sl.unlock();

         for (auto iSize : iaSize)
         {

            iImage = add_icon_info(iSize, pinfo16, pinfo48, crBk, bUsed16, bUsed48, iImage);

         }

         return iImage;

      }


      int windows::add_icon_path(::file::path path, COLORREF crBk, int iImage)
      {

         synch_lock sl(m_pmutex);

         auto iaSize = m_iaSize;

         sl.unlock();

         for (auto iSize : m_iaSize)
         {

            HICON hicon = (HICON)LoadImage(NULL, path, IMAGE_ICON, iSize, iSize, LR_LOADFROMFILE);

            if (hicon == NULL)
            {

               DWORD dwLastError = ::GetLastError();

               output_debug_string("LastError = " + ::str::from(dwLastError));

            }

            iImage = add_icon(iSize, hicon, crBk, iImage);

            ::DestroyIcon(hicon);

         }

         return iImage;

      }


      int windows::add_icon(int iSize, HICON hicon, COLORREF crBk, int iImage)
      {

         synch_lock sl(m_pil[iSize]->m_pmutex);

         synch_lock slHover(m_pilHover[iSize]->m_pmutex);

         iImage = m_pil[iSize]->add_icon_os_data(hicon, iImage);

         iImage = add_hover_image(iSize, iImage, crBk);

         return iImage;

      }


      int windows::thread::add_icon_info(int iSize, SHFILEINFOW * pinfo16, SHFILEINFOW * pinfo48, COLORREF crBk, bool & bUsed16, bool & bUsed48, int iImage)
      {

         bool bUsed = false;

         SHFILEINFOW * pinfo;

         if (iSize <= 16)
         {

            pinfo = pinfo16 == NULL ? pinfo48 : pinfo16;

            iImage = m_pshell->add_system_icon(iSize, m_pilSmall, pinfo, crBk, bUsed, iImage);

         }
         else if (iSize <= 32)
         {

            pinfo = pinfo48 == NULL ? pinfo16 : pinfo48;

            iImage = m_pshell->add_system_icon(iSize, m_pilLarge, pinfo, crBk, bUsed, iImage);

         }
         else if (iSize <= 48)
         {

            pinfo = pinfo48 == NULL ? pinfo16 : pinfo48;

            iImage = m_pshell->add_system_icon(iSize, m_pilExtraLarge, pinfo, crBk, bUsed, iImage);

         }
         else
         {

            pinfo = pinfo48 == NULL ? pinfo16 : pinfo48;

            iImage = m_pshell->add_system_icon(iSize, m_pilJumbo, pinfo, crBk, bUsed, iImage);

         }

         if (bUsed)
         {

            if (pinfo16 == pinfo)
            {

               bUsed16 = true;

            }
            else
            {

               bUsed48 = true;

            }

         }

         return iImage;

      }


      int windows::add_system_icon(int iSize, IImageList * pil, SHFILEINFOW * pinfo, COLORREF crBk, bool & bUsedImageList, int iImage)
      {

         if (pil != NULL)
         {

            HICON hicon = NULL;

            HRESULT hr = pil->GetIcon(pinfo->iIcon, ILD_TRANSPARENT, &hicon);

            if (hicon != NULL)
            {

               iImage = add_icon(iSize, hicon, crBk, iImage);

               ::DestroyIcon(hicon);

            }
            else if (pinfo->hIcon == NULL)
            {

            }
            else
            {

               iImage = add_icon(iSize, pinfo->hIcon, crBk, iImage);

               bUsedImageList = true;

            }

         }
         else if (pinfo->hIcon == NULL)
         {

         }
         else
         {

            iImage = add_icon(iSize, pinfo->hIcon, crBk, iImage);

            bUsedImageList = true;

         }

         return iImage;

      }


      int32_t windows::get_image_foo(oswindow oswindow, const string & strExtension, e_file_attribute eattribute, e_icon eicon, COLORREF crBk)
      {

         int32_t iImage = 0x80000000;

         if (argb_get_a_value(crBk) != 255)
         {

            crBk = 0;

         }

         image_key imagekey;

         imagekey.m_strPath = "foo";

         imagekey.m_strShellThemePrefix = m_strShellThemePrefix;

         imagekey.m_strExtension = strExtension;

         imagekey.m_eattribute = eattribute;

         imagekey.m_eicon = eicon;

         imagekey.m_iIcon = 0;

         return get_image(oswindow, imagekey, crBk);

      }


      int shell::add_hover_image(int iSize, int iImage, COLORREF crBk)
      {

         synch_lock sl(m_pilHover[iSize]->m_pmutex);

         if (crBk == 0)
         {

            return m_pilHover[iSize]->pred_add_image([&](auto dib)
            {

               Application.imaging().Createcolor_blend_dib(dib, RGB(255, 255, 240), 64);

            }
            , m_pil[iSize], iImage, iImage);

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
               dib->get_graphics()->draw(null_point(), d.size(), d.get_graphics());
               dib->get_graphics()->fill_solid_rect_dim(0, 0, d.size().cx, d.size().cy, ARGB(123, argb_get_r_value(crBk), argb_get_g_value(crBk), argb_get_b_value(crBk)));
               m_pil[iSize]->m_spdib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);
               m_pil[iSize]->m_spdib->get_graphics()->draw(d.rect(), dib->get_graphics());
               m_pil[iSize]->m_spdib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);

            }

            return iImage;

         }


      }


   } // namespace shell


} // namespace user



