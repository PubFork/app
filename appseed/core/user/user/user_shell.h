#pragma once


namespace user
{


   namespace shell
   {


      enum e_file_attribute
      {

         file_attribute_none,
         file_attribute_normal,
         file_attribute_directory,

      };

      enum e_folder
      {

         folder_none,
         folder_file_system,
         folder_zip,

      };


      enum e_icon
      {

         icon_normal,
         icon_open,

      };


      class image_key
      {
      public:


         string                        m_strPath;
         string                        m_strShellThemePrefix;
         cflag < e_file_attribute >    m_eattribute;
         cflag < e_icon >              m_eicon;
         int32_t                       m_iIcon;
         string                        m_strExtension;

         oswindow                      m_oswindow;
         COLORREF                      m_cr;


         image_key();
         image_key(const image_key & imagekey);
         virtual ~image_key();


         bool operator == (const image_key & key) const;
         void set_path(const string & strPath, bool bSetExtension = true);
         void set_extension(const string & strPath);


      };


      inline bool image_key::operator == (const image_key & key) const
      {
         return m_eattribute == key.m_eattribute
                && m_eicon == key.m_eicon
                && m_strExtension == key.m_strExtension
                && m_strShellThemePrefix == key.m_strShellThemePrefix
                && m_strPath == key.m_strPath;
      }

      template < typename VALUE, typename ARG_VALUE >
      using image_key_map = map< image_key, const image_key &, VALUE, ARG_VALUE >;


      class CLASS_DECL_CORE shell :
         virtual public ::object
      //,         virtual public ::thread

      {
      protected:

         ::int_map < sp(image_list) >                                   m_pil; // int is the size
         ::int_map < sp(image_list) >                                   m_pilHover; // int is the size;

      public:

         int_array                                                      m_iaSize;
         image_key_map < int32_t, int32_t >                             m_imagemap;
         image_key_map < image_key, const image_key & >                 m_imagekeymap;

         string                                                         m_strShellThemePrefix;
         stringa                                                        m_straThemeableIconName;


         shell(::aura::application * papp);
         virtual ~shell();


         virtual void on_update_sizes_interest();

         virtual int32_t get_image_foo(oswindow oswindow, const string & strExtension, e_file_attribute eattribute, e_icon eicon, COLORREF crBk = 0) = 0;
         virtual int32_t get_image(oswindow oswindow, const string & strPath, e_file_attribute eattribute, e_icon eicon, COLORREF crBk = 0) = 0;

         image_list * GetImageList(int iSize);
         image_list * GetImageListHover(int iSize);

         virtual void initialize();
         virtual void do_initialize();

         virtual e_folder get_folder_type(::aura::application * papp, const unichar * lpcszPath) = 0;
         virtual e_folder get_folder_type(::aura::application * papp, const char * lpcszPath) = 0;
         int add_hover_image(int iSize, int iIndex, COLORREF crBk);


      };


   } // namespace shell


} // namespace user


template < >
inline UINT HashKey<const ::user::shell::image_key &>(const ::user::shell::image_key & key)
{
   // default identity hash - works for most primitive values
   return (UINT)harmannieves_camwhite_hash(key.m_strPath,
                                           harmannieves_camwhite_hash(key.m_strShellThemePrefix,
                                                 harmannieves_camwhite_hash(key.m_strExtension,
                                                       (((int)key.m_eicon) << 8) | (((int)key.m_eattribute) << 16))));
}



template <  >
inline bool EqualElements(const ::user::shell::image_key & element1, const ::user::shell::image_key & element2)
{

   return element1 == element2;

}
