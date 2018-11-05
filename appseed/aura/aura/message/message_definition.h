
#pragma once



namespace message
{


   enum e_message
   {

      message_null,
      message_create = 32768,
      message_drag_and_drop,
      message_event = 65536,
      message_property,
      message_pos_create,
      message_frame_initial_update

   };


   CLASS_DECL_AURA UINT translate_to_os_message(e_message emessage);


   class base;


   enum e_prototype
   {
      PrototypeNone,
      PrototypeMouse,
      PrototypeScroll,
      PrototypeSize,
      PrototypeMove,
      PrototypeMeasureItem,
      PrototypeCreate,
      PrototypeActivate,
      PrototypeNcActivate,
      PrototypeMouseActivate,
      PrototypeEraseBkgnd,
      PrototypeShowWindow,
      PrototypeSetCursor,
      PrototypeTimer,
      PrototypeMouseWheel,
      PrototypeInitMenuPopup,
      PrototypeEnable,
      PrototypeNcHitTest,
      PrototypeKey,
      PrototypeNotify,
      PrototypeUpdateCommandUserInterface,
      PrototypeCtlColor,
      PrototypeCtlColorReflect,
      PrototypeKillFocus,
      PrototypeSetFocus,
      PrototypeCommand,
      PrototypeWindowPos,
      PrototypeNcCalcSize,
      PrototypeOnDraw,
      PrototypeSimpleCommand

   };


//   class ::message::sender * CreateSignal();


} // namespace message
