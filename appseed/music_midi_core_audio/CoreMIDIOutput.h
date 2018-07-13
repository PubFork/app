//
//  CoreMIDIOutput.hpp
//  music_midi_core_audio
//
//  Created by Camilo Sasuke Tsumanuma on 9/8/16.
//  Copyright © 2016 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

/*
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License along
 with this program; if not, write to the Free Software Foundation, Inc.,
 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */



/**
 * @ingroup midi
 *
 * An OS X MIDI output port that uses CoreMIDI. This output device is used to send output
 * to external devices, not for playing with the built-in software synthesizer.
 */
class CoreMidiOutput : public OutputBase,
   virtual public ::music::midi::message_out
{
public:
   

   struct Destination
   {
      
      
      MIDIEndpointRef m_endpoint;
      string m_strName;
      
      
   };
   
   uint64_t                m_ui64Start;
   


   MIDIEndpointRef m_endpoint;
   
   MIDIPortRef m_port;
   
   char m_buffer[65535];
   
   MIDIPacketList * m_packetlist;

   MIDIPacket * m_packet;


   //MIDIClientRef m_client;
   
   
   CoreMidiOutput(::aura::application * papp, string driver);
   virtual ~CoreMidiOutput();
   
   virtual void start() override;
   
   static array < Destination > get_destinations();
   
   virtual void note_on(int iChannel, unsigned char uchNote, unsigned char uchVelocity) override;
   virtual void note_off(int iChannel, unsigned char uchNote, unsigned char uchVelocity) override;
   virtual void program_change(int iChannel, unsigned char uchProgram) override;
   virtual void control_change(int iChannel, unsigned char uchController, unsigned char uchValue) override;
   virtual void pitch_bend(int iChannel, unsigned short ushBend) override;
   
   virtual void step() override;
   
   virtual void reset_all_controllers() override;
   
   virtual void add_short_message(Byte * pmessage, int iSize);
   
};

