#include "framework.h"


namespace user
{


   copydesk::copydesk(::aura::application * papp) :
      object(papp)
   {

   }


   copydesk::~copydesk()
   {

   }


   bool copydesk::has_filea()
   {

      ::exception::throw_interface_only(get_app());

      return 0;

   }


   bool copydesk::get_filea(::file::patha & stra, e_op & eop)
   {

      UNREFERENCED_PARAMETER(stra);

      ::exception::throw_interface_only(get_app());

      return false;

   }


   bool copydesk::set_filea(const ::file::patha & patha, e_op eop)
   {

      UNREFERENCED_PARAMETER(patha);

      ::exception::throw_interface_only(get_app());

      return false;

   }


   bool copydesk::initialize()
   {

      return true;

   }


   bool copydesk::finalize()
   {

      return true;

   }


   bool copydesk::set_plain_text(const string & str)
   {

      UNREFERENCED_PARAMETER(str);

      ::exception::throw_interface_only(get_app());

      return false;

   }


   bool copydesk::get_plain_text(string & str)
   {

      ::exception::throw_interface_only(get_app());

      return false;

   }


   bool copydesk::has_plain_text()
   {

      ::exception::throw_interface_only(get_app());

      return 0;

   }



   bool copydesk::desk_to_dib(::draw2d::dib * pdib)
   {

      UNREFERENCED_PARAMETER(pdib);
      ::exception::throw_interface_only(get_app());

      return false;

   }

   bool copydesk::dib_to_desk(::draw2d::dib * pdib)
   {

      UNREFERENCED_PARAMETER(pdib);
      ::exception::throw_interface_only(get_app());

      return false;

   }

   bool copydesk::has_dib()
   {

      ::exception::throw_interface_only(get_app());

      return 0;

   }


} // namespace user


