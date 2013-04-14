#include "framework.h"


namespace bergedge
{


   document::document(sp(::ca::application) papp) :
      ca(papp),
      ::ca::data_container_base(papp),
      ::ca::data_container(papp),
      ::user::document(papp)
   {
      m_pplatformdocument = ::null();
      m_pnaturedocument = ::null();
   }

   bool document::on_new_document()
   {
      if (!::user::document::on_new_document())
         return FALSE;

   
      update_all_views(::null(), 0);

      return TRUE;
   }

   document::~document()
   {
   }


   #ifdef DEBUG
   void document::assert_valid() const
   {
      ::user::document::assert_valid();
   }

   void document::dump(dump_context & dumpcontext) const
   {
      ::user::document::dump(dumpcontext);
   }
   #endif //DEBUG



   sp(::bergedge::view) document::get_bergedge_view()
   {
      return get_typed_view < ::bergedge::view > ();
   }

   void document::set_platform(sp(::platform::document) pdoc)
   {
      m_pplatformdocument = pdoc;
      //platform_frame * pframe = pdoc->get_platform_frame();
      //pframe->set_parent(get_bergedge_view());
      //pframe->ModifyStyle(0, WS_CHILD);
      //pframe->ShowWindow(SW_RESTORE);
      //pframe->SetWindowPos(0, 0, 0, 200, 200, SWP_SHOWWINDOW);
   }

   void document::set_nature(sp(::nature::document) pdoc)
   {
      m_pnaturedocument = pdoc;
      //nature_frame * pframe = pdoc->get_nature_frame();
      //pframe->set_parent(get_bergedge_view());
      //pframe->ModifyStyle(0, WS_CHILD);
      //pframe->SetWindowPos(0, 200, 200, 400, 400, SWP_SHOWWINDOW);
   }



} // namespace bergedge



