#include "framework.h"


namespace prompt
{


   application::application()
   {

   }


   application::~application()
   {

   }


   void application::construct()
   {

      m_strAppName            = _strdup("command");
      m_strBaseSupportId      = "ca2_command";
      m_eexclusiveinstance    = ::ExclusiveInstanceLocal;

   }


   bool application::init_instance()
   {

      System.factory().creatable_small < prompt::document >();
      System.factory().creatable_small < prompt::frame >();
      System.factory().creatable_small < prompt::view >();
      System.factory().creatable_small < prompt::pane_view >();
      System.factory().creatable_small < prompt::primary_view >();

      if(!::asphere::application::init_instance())
         return false;

      Session.filemanager()->m_strLevelUp = "levelup";

      if(m_strId == "command")
      {

         ::user::single_document_template* pDocTemplate;
         pDocTemplate = new ::user::single_document_template(
            this,
            "system/form",
            System.type_info < prompt::document > (),
            System.type_info < prompt::frame > (),
            System.type_info < prompt::pane_view > ());
         add_document_template(pDocTemplate);
         m_ptemplateCommandMain = pDocTemplate;


         m_ptemplateCommandMain->open_new_document();
      }

      return true;
   }

   int32_t application::exit_application()
   {
      return 0;
   }


   void application::_001OnCmdMsg(::user::command * pcommand)
   {

      ::core::application::_001OnCmdMsg(pcommand);

   }


   void application::OnFileManagerOpenFile(::filemanager::data * pdata, ::fs::item_array & itema)
   {
      UNREFERENCED_PARAMETER(pdata);
      if(itema.get_size() > 0)
      {

#ifdef WINDOWSEX

         ::ShellExecuteW(
            NULL,
            L"open",
            ::str::international::utf8_to_unicode(itema[0]->m_filepath),
            NULL,
            ::str::international::utf8_to_unicode(itema[0]->m_filepath.folder()),
            SW_SHOW);

#else

         _throw(todo(get_app()));

#endif

      }

   }

} // namespace prompt



