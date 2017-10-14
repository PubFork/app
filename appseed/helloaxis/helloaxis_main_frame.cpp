#include "framework.h"


namespace helloworld
{


   main_frame::main_frame(::aura::application * papp) :
      object(papp),
      simple_frame_window(papp)
   {

      m_bDefaultCreateToolbar = false;

      WfiEnableFullScreen();

      m_bWindowFrame = !Application.handler()->m_varTopicQuery.has_property("client_only");



      if (Application.handler()->m_varTopicQuery.has_property("opaque"))
      {

         m_bExplicitTranslucency = true;

         m_etranslucency = ::user::translucency_none;

      }
      else
      {

         m_bExplicitTranslucency = false;

      }



   }


   main_frame::~main_frame()
   {

   }


   void main_frame::assert_valid() const
   {

      simple_frame_window::assert_valid();

   }


   void main_frame::dump(dump_context & dumpcontext) const
   {

      simple_frame_window::dump(dumpcontext);

   }


   sp(::user::wndfrm::frame::frame) main_frame::create_frame_schema()
   {



      //sp(::user::wndfrm::main_frame::main_frame) pschema = Application.wndfrm()->get_frame_schema("wndfrm_core", "001");

      sp(::user::wndfrm::frame::frame) pschema = Application.wndfrm()->get_frame_schema(NULL, "013");

      pschema->set_style("LightBlue");

      //       // pschema->m_typeinfoControlBoxButton = System.type_info < MetaButton > ();

      return pschema;

   }

   bool main_frame::has_pending_graphical_update()
   {

      return true;

   }


   bool main_frame::get_translucency(::user::e_translucency & etranslucency, ::user::e_element eelement, ::user::interaction * pui)
   {

      if (m_bExplicitTranslucency)
      {

         etranslucency = m_etranslucency;

         return true;

      }

      //if (userstyle() != NULL)
      //{

      //   if (m_puserstyle->_001GetMainFrameTranslucency(etranslucency))
      //      return true;

      //}
      //etranslucency = ::user::translucency_present;

      ////      etranslucency = ::user::translucency_none;

      //return true;

      return ::user::style::get_translucency(etranslucency, eelement, pui);

   }


} // namespace helloworld







