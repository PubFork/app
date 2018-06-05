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


   bool copydesk::initialize()
   {

      return true;

   }


   bool copydesk::finalize()
   {

      return true;

   }


   bool copydesk::string_to_filea(::file::patha  * ppatha, const string & str)
   {

      stringa stra;

      stra.add_lines(str);

      for (auto & strPath : stra)
      {

         if (strPath.has_char() && (Application.dir().is(strPath) || Application.file().exists(strPath)))
         {

            if (ppatha == NULL)
            {

               return true;

            }

            ppatha->add(::file::path(strPath));

         }

      }

      if (ppatha != NULL && ppatha->has_elements())
      {

         return true;

      }

      return false;

   }


   bool copydesk::has_filea()
   {

      if (_has_filea())
      {

         return true;

      }

      if (_has_plain_text())
      {

         string str;

         if (_get_plain_text(str))
         {

            if(string_to_filea(NULL, str))
            {

               return true;

            }

         }

      }

      return false;

   }


   bool copydesk::get_filea(::file::patha & patha, e_op & eop)
   {

      if (_get_filea(patha, eop))
      {

         return true;

      }

      string str;

      if (_get_plain_text(str))
      {

         if (string_to_filea(&patha, str))
         {

            return true;

         }

      }

      return false;

   }


   bool copydesk::set_filea(const ::file::patha & patha, e_op eop)
   {

      return _set_filea(patha, eop);

   }


   bool copydesk::set_plain_text(const string & str)
   {

      return _set_plain_text(str);

   }


   bool copydesk::get_plain_text(string & str)
   {

      if (_get_plain_text(str))
      {

         return true;

      }

      if (_has_filea())
      {

         e_op eop = op_copy;

         ::file::patha patha;

         if (get_filea(patha, eop))
         {

            str = patha.implode("\r\n");

            return true;

         }

      }

      return false;

   }


   bool copydesk::has_plain_text()
   {

      if (_has_plain_text())
      {

         return true;

      }

      if (_has_filea())
      {

         return true;

      }

      return false;

   }



   bool copydesk::desk_to_dib(::draw2d::dib * pdib)
   {

      if (_has_dib())
      {

         return _desk_to_dib(pdib);

      }

      if (has_plain_text())
      {

         string str;

         if (get_plain_text(str))
         {

            pdib->create(1, 1);

            auto pfont = Session._001GetFont(::user::font_default);

            pdib->g()->selectFont(pfont);

            sized s = pdib->g()->GetTextExtent(str);

            if (s.area() > 0)
            {

               pdib->create(ceil(s.cx), ceil(s.cy));

               pdib->FillByte(0);

               pdib->g()->selectFont(pfont);

               pdib->g()->set_text_color(ARGB(255, 0, 0, 0));

               pdib->g()->draw_text(str, rect(pdib->m_size), DT_LEFT | DT_BOTTOM);

               return true;

            }

         }

      }

      return false;

   }


   bool copydesk::dib_to_desk(::draw2d::dib * pdib)
   {

      return _dib_to_desk(pdib);

   }


   bool copydesk::has_dib()
   {

      if (_has_dib())
      {

         return true;

      }

      if (has_plain_text())
      {

         return true;

      }

      return false;

   }

   bool copydesk::_has_filea()
   {

      ::exception::throw_interface_only(get_app());

      return 0;

   }


   bool copydesk::_get_filea(::file::patha & stra, e_op & eop)
   {

      UNREFERENCED_PARAMETER(stra);

      ::exception::throw_interface_only(get_app());

      return false;

   }


   bool copydesk::_set_filea(const ::file::patha & patha, e_op eop)
   {

      UNREFERENCED_PARAMETER(patha);

      ::exception::throw_interface_only(get_app());

      return false;

   }


   bool copydesk::_set_plain_text(const string & str)
   {

      UNREFERENCED_PARAMETER(str);

      ::exception::throw_interface_only(get_app());

      return false;

   }


   bool copydesk::_get_plain_text(string & str)
   {

      ::exception::throw_interface_only(get_app());

      return false;

   }


   bool copydesk::_has_plain_text()
   {

      ::exception::throw_interface_only(get_app());

      return 0;

   }



   bool copydesk::_desk_to_dib(::draw2d::dib * pdib)
   {

      UNREFERENCED_PARAMETER(pdib);
      ::exception::throw_interface_only(get_app());

      return false;

   }

   bool copydesk::_dib_to_desk(::draw2d::dib * pdib)
   {

      UNREFERENCED_PARAMETER(pdib);
      ::exception::throw_interface_only(get_app());

      return false;

   }

   bool copydesk::_has_dib()
   {

      ::exception::throw_interface_only(get_app());

      return 0;

   }

} // namespace user


