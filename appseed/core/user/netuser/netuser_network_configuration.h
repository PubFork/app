#pragma once


namespace usernet
{


   class CLASS_DECL_CORE network_configuration :
      public ::user::form_callback,
      public ::user::view_creator
   {
   public:


      sp(::user::document)               m_pdoc;
      sp(::user::form_view)              m_pview;


      network_configuration(::aura::application * papp);
      virtual ~network_configuration();


      bool initialize(sp(::user::interaction) puiParent);
      bool initialize_child(sp(::user::interaction) puiParent);

      void on_show();

      bool BaseOnControlEvent(::user::control_event * pevent);

   };


} // namespace usernet


