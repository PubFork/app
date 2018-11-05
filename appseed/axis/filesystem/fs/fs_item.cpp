#include "framework.h"


namespace fs
{


   item::item()
   {

   }


   item::item(const item & item) :
      object(item),
      m_filepath(item.m_filepath),
      m_filepathEx(item.m_filepathEx),
      m_flags(item.m_flags)
   {

   }


   item::item(const ::file::path & filepath, const ::file::path & filepathEx)
   {

      m_filepath        = filepath;
      m_filepathEx      = filepathEx;

   }


   item::item(const ::file::path & filepath, const ::file::path & filepathEx, const cflag < e_flag > & flags)
   {

      m_filepath        = filepath;
      m_filepathEx      = filepathEx;
      m_flags           = flags;

   }


   item::~item()
   {


   }


   ::file::path item::get_friendly_path()
   {

      if (m_filepathEx.has_char())
      {

         return m_filepathEx;

      }
      else
      {

         return m_filepath;

      }

   }


   ::file::path item::get_absolute_path()
   {

      if (m_filepath.has_char())
      {

         return m_filepath;

      }
      else
      {

         return m_filepathEx;

      }

   }


} // namespace fs



