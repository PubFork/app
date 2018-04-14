#pragma once


#include <shlobj.h>
#include <Shellapi.h>
#include <CommonControls.h>


namespace user
{


   namespace shell
   {


      class CLASS_DECL_CORE windows :
         virtual public ::user::shell::shell
      {
      public:

         class CLASS_DECL_CORE thread :
            virtual public ::thread
         {
         public:


            windows *                                       m_pshell;
            comptr < IMalloc >                              m_pmalloc;
            comptr < IShellFolder >                         m_pfolderDesktop;
            comptr < IImageList >                           m_pilSmall;
            comptr < IImageList >                           m_pilLarge;
            comptr < IImageList >                           m_pilExtraLarge;
            comptr < IImageList >                           m_pilJumbo;



            thread(windows * pshell);
            virtual ~thread();


            virtual bool init_thread() override;

            int32_t get_image(oswindow oswindow, image_key key, const itemidlist & pidlAbsolute, const itemidlist & pidlChild, const unichar * lpcszExtra, COLORREF crBk);
            int32_t get_foo_image(oswindow oswindow, image_key & key, COLORREF crBk);
            int32_t get_image_by_extension(oswindow oswindow, image_key & key, COLORREF crBk);


            int32_t add_icon_set(SHFILEINFOW * pinfo16, SHFILEINFOW * pinfo48, COLORREF crBk, bool & bUsedImageList16, bool & bUsedImageList48, int iImage);
            int32_t add_icon_info(int iSize, SHFILEINFOW * pinfo16, SHFILEINFOW * pinfo48, COLORREF crBk, bool & bUsedImageList16, bool & bUsedImageList48, int iImage);


            int32_t get_image(oswindow oswindow, const image_key & key, COLORREF crBk);

            int32_t get_image(oswindow oswindow, image_key key, const unichar * lpcszExtra, COLORREF crBk);



         };

         int                     m_iMaxThreadCount;
         int64_t                 m_iActiveThreadCount;
         uint32_t                m_uiThread;
         mutex                   m_mutexImage;
         spa(thread)             m_threadptra;
         DWORD                   m_dwLastMax;
         DWORD                   m_bMax;


         windows(::aura::application * papp);
         virtual ~windows();

         virtual void initialize() override;

         virtual void add_thread();

         virtual int32_t get_image_foo(oswindow oswindow, const string & strExtension, e_file_attribute eattribute, e_icon eicon, COLORREF crBk = 0) override;
         virtual int32_t get_image(oswindow oswindow, const string & strPath, e_file_attribute eattribute, e_icon eicon, COLORREF crBk = 0) override;

         int32_t get_image(oswindow oswindow, const image_key & key, COLORREF crBk);


         int _reserve_image(const image_key & key);


         bool contains_image(const image_key & imagekey, int32_t & iImage);
         bool reserve_image(const image_key & imagekey, int32_t & iImage);

         int32_t add_icon(int iSize, HICON hicon, COLORREF crBk, int iImage);

         int32_t add_icon_path(::file::path path, COLORREF crBk, int iImage);

         int32_t add_system_icon(int iSize, IImageList * plist, SHFILEINFOW * pinfo, COLORREF crBck, bool & bUsedImageList, int iImage);


         virtual ::user::shell::e_folder get_folder_type(::aura::application * papp, const unichar * lpcszPath) override;
         virtual ::user::shell::e_folder get_folder_type(::aura::application * papp, const char * lpcszPath) override;

      };


   } // namespace windows


} // namespace filemanager


