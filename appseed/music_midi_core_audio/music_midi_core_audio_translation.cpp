#include "framework.h"


namespace music
{

   
   namespace midi_core_midi
   {
      
      
      CLASS_DECL_VERIWELL_MULTIMEDIA_MUSIC_MIDI_CORE_MIDI ::multimedia::e_result translate_os_status(OSStatus status)
      {
         
         
         switch(status)
         {
            
            case noErr:
               
               return ::multimedia::result_success;
               
            default:
               
               break;
               
         }
         
         return ::multimedia::result_midi_error;
         
      }

   } // namespace midi_core_midi


} // namespace music      
