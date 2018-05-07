#include "framework.h"
#include "aura/compress/zip/zip.h"
#include "aura/compress/compress_gz.h"


namespace user
{


   namespace shell
   {


      image_key::image_key()
      {

         m_iIcon = 0x80000000;

      }

      image_key::image_key(const image_key & key)
      {

         m_oswindow = key.m_oswindow;
         m_cr = key.m_cr;
         m_strPath = key.m_strPath;
         m_iIcon = key.m_iIcon;
         m_eattribute = key.m_eattribute;
         m_eicon = key.m_eicon;
         m_strExtension = key.m_strExtension;
         m_strShellThemePrefix = key.m_strShellThemePrefix;

      }


      image_key::~image_key()
      {


      }


      void image_key::set_path(const string & strPath, bool bSetExtension)
      {

         m_strPath = strPath;

         if (bSetExtension)
         {

            set_extension(strPath);

         }
         else
         {

            m_strExtension.Empty();

         }


      }


      void image_key::set_extension(const string & strPath)
      {

         strsize iFind1 = strPath.rfind('/');

         strsize iFind2 = strPath.rfind('\\');

         strsize iFind = MAX(iFind1, iFind2) + 1;

         strsize iDot = strPath.find('.', iFind);

         if (iDot < 0)
         {

            m_strExtension.Empty();

         }
         else
         {

            m_strExtension = strPath.Mid(iDot + 1);

         }

      }


      shell::shell(::aura::application * papp) :
         object(papp)
      {

         m_iaSize.add(16);
         m_iaSize.add(24);
         m_iaSize.add(32);
         m_iaSize.add(48);
         m_iaSize.add(256);

         m_imagemap.InitHashTable(16384);

      }


      shell::~shell()
      {

      }


      void shell::initialize()
      {

         do_initialize();

      }


      void shell::on_update_sizes_interest()
      {

         m_imagemap.remove_all();

         m_pil.remove_all();

         m_pilHover.remove_all();

         if (!m_iaSize.contains(16))
         {

            m_iaSize.add(16);

         }

         if (!m_iaSize.contains(48))
         {

            m_iaSize.add(48);

         }

         m_iaSize.sort();

         for (auto iSize : m_iaSize)
         {

            m_pil[iSize] = canew(image_list(get_app()));
            m_pil[iSize]->create(iSize, iSize, 0, 10, 10);

            m_pilHover[iSize] = canew(image_list(get_app()));
            m_pilHover[iSize]->create(iSize, iSize, 0, 10, 10);

         }

      }


      void shell::do_initialize()
      {


      }


      image_list * shell::GetImageList(int iSize)
      {

         index i = 0;

         for (; i < m_iaSize.get_size(); i++)
         {

            if (iSize <= m_iaSize[i])
            {

               break;

            }

         }

         if (i >= m_iaSize.get_size())
         {

            i = m_iaSize.get_upper_bound();

         }

         return m_pil[m_iaSize[i]];

      }


      image_list * shell::GetImageListHover(int iSize)
      {
         index i = 0;

         for (; i < m_iaSize.get_size(); i++)
         {

            if (iSize <= m_iaSize[i])
            {

               break;

            }

         }

         if (i >= m_iaSize.get_size())
         {

            i = m_iaSize.get_upper_bound();

         }

         return m_pilHover[m_iaSize[i]];

      }


   } // namespace shell


} // namespace user



#ifdef WINDOWSEX
#include "core/user/user/user_shell_windows.h"
#elif defined(MACOS)
#include "core/user/user/user_shell_macos.h"
#elif defined(APPLE_IOS)
#include "core/user/user/user_shell_ios.h"
#elif defined(LINUX)
#include "core/user/user/user_shell_linux.h"
#elif defined(ANDROID)
#include "core/user/user/user_shell_android.h"
#elif defined(METROWIN)
#include "core/user/user/user_shell_metrowin.h"
#else
#error "Implement here"
#endif



namespace userex
{

   bool userex::create_user_shell()
   {

      if (m_pshell.is_null())
      {

#ifdef WINDOWSEX

         m_pshell = canew(::user::shell::windows(get_app()));

#elif defined(MACOS)

         m_pshell = canew(::user::shell::macos(get_app()));

#elif defined(APPLE_IOS)

         m_pshell = canew(::user::shell::ios(get_app()));

#elif defined(ANDROID)

         m_pshell = canew(::user::shell::android(get_app()));

#elif defined(METROWIN)

         m_pshell = canew(::user::shell::metrowin(get_app()));

#elif defined(LINUX)

         m_pshell = canew(::user::shell::linux(get_app()));

#else

#error "Implement for your platform."

#endif

      }

      if(m_pshell.is_null())
      {

         return false;

      }

      return true;

   }


}
