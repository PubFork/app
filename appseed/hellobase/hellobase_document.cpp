#include "framework.h"


namespace hellobase
{


   document::document(::aura::application * papp) :
      object(papp),
      ::data::data_container_base(papp),
      ::user::controller(papp),
      ::user::document(papp)
   {

   }


   document::~document()
   {

   }





   void document::assert_valid() const
   {

      ::user::document::assert_valid();

   }


   void document::dump(dump_context & dumpcontext) const
   {

      ::user::document::dump(dumpcontext);

   }


   bool document::on_new_document()
   {

      return ::user::document::on_new_document();

   }


   bool document::on_open_document(var varFile)
   {

      view * pview = get_typed_view < view >();

      if(pview == NULL)
      {

         return true;

      }

      string strPath = varFile.get_file_path();

      varFile["url"] = strPath;

      varFile["http_set"]["raw_http"] = true;
      varFile["http_set"]["disable_common_name_cert_check"] = true;

      string str;

      if(pview->m_prender->m_dibImage.load_from_file(varFile))
      {

         get_typed_view < view >()->m_strImage = varFile["url"];

         {

            synch_lock slText(get_typed_view < view >() != NULL  ? &get_typed_view < view >()->m_mutexText : NULL);

            get_typed_view < view >()->m_strHelloMultiverse = "image:" + get_typed_view < view >()->m_strImage + "," + get_typed_view < view >()->m_strHelloMultiverse;

            get_typed_view < view >()->set_need_layout(true);

         }

      }
      else if(get_typed_view < ::user::plain_edit_view >() != NULL
              && Application.file().exists(varFile)
              && (str = Application.file().as_string(varFile)).has_char())
      {

         get_typed_view < ::user::plain_edit_view >()->_001SetText(str.Left(84),::action::source_user);

      }

      return true;

   }


   int64_t document::add_ref()
   {

      return  ::user::document::add_ref();

   }

   int64_t document::dec_ref()
   {

      return  ::user::document::dec_ref();

   }



} // namespace hellobase

















