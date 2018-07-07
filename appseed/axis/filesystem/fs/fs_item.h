#pragma once


namespace fs
{


   class CLASS_DECL_AXIS item :
      virtual public object
   {
   public:


      ::file::path               m_filepath;
      ::file::path               m_filepathEx;
      cflag < e_flag >           m_flags;


      item();
      item(const item & item);
      item(const ::file::path & filepath, const ::file::path & filepathEx);
      item(const ::file::path & filepath, const ::file::path & filepathEx, const cflag < e_flag > & flags);
      virtual ~item();


      virtual ::file::path get_friendly_path();
      virtual ::file::path get_absolute_path();


   };


} // namespace fs



