#include "framework.h"
#include "framework.h"


namespace filemanager
{


   child_frame::child_frame(::aura::application * papp) :
      object(papp),
      simple_frame_window(papp),
      simple_child_frame(papp)
   {



   }


   child_frame::~child_frame()
   {
   }


   void child_frame::install_message_routing(::message::sender * psender)
   {

      simple_child_frame::install_message_routing(psender);

      MSG_TYPE_LINK(::message::type_language, psender, this, &child_frame::_001OnAppLanguage);
      IGUI_MSG_LINK(WM_SHOWWINDOW, psender, this, &child_frame::_001OnShowWindow);
      IGUI_MSG_LINK(WM_CREATE, psender, this, &child_frame::_001OnCreate);

   }


   bool child_frame::on_create_bars()
   {

      manager * pmanager = dynamic_cast < manager * >(m_pdocumenttemplate->get_document());

      return pmanager->on_create_bars(this);

   }


   bool child_frame::DestroyBars()
   {

      return true;

   }


   void child_frame::route_command_message(::user::command * pcommand)
   {

      simple_child_frame::route_command_message(pcommand);

   }


   void child_frame::OnChangeEditSearch()
   {

      sp(::user::document) pdoc = GetActiveDocument();

      if (pdoc != NULL)
      {
         update_hint uh;
         uh.set_type(update_hint::TypeFilter);
         string str;

      }

   }

   sp(manager) child_frame::get_filemanager_template()
   {
      return  GetActiveDocument();
   }


   void child_frame::_001OnCreate(::message::message * pobj)
   {
      if (pobj->m_bRet)
         return;


      m_hMenuDefault = NULL;


   }


   void child_frame::_001OnAppLanguage(::message::message * pobj)
   {
//      CreateBars();
      pobj->m_bRet = false;
   }

   void child_frame::GetSelected(::fs::item_array &itema)
   {
      sp(file_list) plistinterface = GetActiveView();
      if (plistinterface != NULL)
      {
         plistinterface->GetSelected(itema);
      }
   }

   void child_frame::_001OnShowWindow(::message::message * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }




} // namespace filemanager




