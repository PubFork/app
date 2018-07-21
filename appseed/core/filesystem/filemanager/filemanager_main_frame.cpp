#include "framework.h"


namespace filemanager
{



   main_frame::main_frame(::aura::application * papp) :
      object(papp),
      simple_frame_window(papp)
   {

      set_pro_devian();

   }


   main_frame::~main_frame()
   {

   }


   void main_frame::_001OnCreate(::message::message * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);


   }


   bool main_frame::on_create_bars()
   {


      sp(manager) pmanager = m_pdocumenttemplate->get_document();

      return pmanager->on_create_bars(this);

   }


} // namespace filemanager



