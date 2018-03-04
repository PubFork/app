//
//  CoreMIDIOutput.cpp
//  music_midi_core_audio
//
//  Created by Camilo Sasuke Tsumanuma on 9/8/16.
//  Copyright © 2016 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#include "framework.h"
#include <CoreAudio/CoreAudio.h>
#include <mach/mach_time.h>


static mach_timebase_info_data_t sTimebaseInfo;

UInt64 nano_to_absolute(UInt64 nano)
{
   
   return nano * sTimebaseInfo.denom / sTimebaseInfo.numer;
   
}



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


// The following is copied from: http://developer.apple.com/qa/qa2004/qa1374.html
static CFStringRef EndpointName(MIDIEndpointRef endpoint, bool isExternal)
{
   CFMutableStringRef result = CFStringCreateMutable(NULL, 0);
   CFStringRef str;
   
   // begin with the endpoint's name
   str = NULL;
   MIDIObjectGetStringProperty(endpoint, kMIDIPropertyName, &str);
   if (str != NULL) {
      CFStringAppend(result, str);
      CFRelease(str);
   }
   
   MIDIEntityRef entity = NULL;
   MIDIEndpointGetEntity(endpoint, &entity);
   if (entity == 0)
      // probably virtual
      return result;
   
   if (CFStringGetLength(result) == 0) {
      // endpoint name has zero length -- try the entity
      str = NULL;
      MIDIObjectGetStringProperty(entity, kMIDIPropertyName, &str);
      if (str != NULL) {
         CFStringAppend(result, str);
         CFRelease(str);
      }
   }
   // now consider the device's name
   MIDIDeviceRef device = NULL;
   MIDIEntityGetDevice(entity, &device);
   if (device == 0)
      return result;
   
   str = NULL;
   MIDIObjectGetStringProperty(device, kMIDIPropertyName, &str);
   if (str != NULL) {
      // if an external device has only one entity, _throw( away
      // the endpoint name and just use the device name
      if (isExternal && MIDIDeviceGetNumberOfEntities(device) < 2) {
         CFRelease(result);
         return str;
      } else {
         // does the entity name already start with the device name?
         // (some drivers do this though they shouldn't)
         // if so, do not prepend
         if (CFStringCompareWithOptions(str /* device name */,
                                        result /* endpoint name */,
                                        CFRangeMake(0, CFStringGetLength(str)), 0) != kCFCompareEqualTo) {
            // prepend the device name to the entity name
            if (CFStringGetLength(result) > 0)
               CFStringInsert(result, 0, CFSTR(" "));
            CFStringInsert(result, 0, str);
         }
         CFRelease(str);
      }
   }
   return result;
}


CFStringRef ConnectedEndpointName(MIDIEndpointRef endpoint)
{
   CFMutableStringRef result = CFStringCreateMutable(NULL, 0);
   CFStringRef str;
   OSStatus err;
   int i = 0;
   
   // Does the endpoint have connections?
   CFDataRef connections = NULL;
   int nConnected = 0;
   bool anyStrings = false;
   err = MIDIObjectGetDataProperty(endpoint, kMIDIPropertyConnectionUniqueID, &connections);
   if (connections != NULL) {
      // It has connections, follow them
      // Concatenate the names of all connected devices
      nConnected = (int) (CFDataGetLength(connections) / sizeof(MIDIUniqueID));
      if (nConnected) {
         const SInt32 *pid = (SInt32*) CFDataGetBytePtr(connections);
         for (i = 0; i < nConnected; ++i, ++pid) {
#ifdef MACOS
            MIDIUniqueID id = EndianS32_BtoN(*pid);
#else
            
      MIDIUniqueID id = *pid;
#endif
            MIDIObjectRef connObject;
            MIDIObjectType connObjectType;
            err = MIDIObjectFindByUniqueID(id, &connObject, &connObjectType);
            if (err == noErr) {
               if (connObjectType == kMIDIObjectType_ExternalSource  ||
                   connObjectType == kMIDIObjectType_ExternalDestination) {
                  // Connected to an external device's endpoint (10.3 and later).
                  str = EndpointName((MIDIEndpointRef)(connObject), true);
                  //str = EndpointName(connObject, true);
               } else {
                  // Connected to an external device (10.2) (or something else, catch-all)
                  str = NULL;
                  MIDIObjectGetStringProperty(connObject, kMIDIPropertyName, &str);
               }
               if (str != NULL) {
                  if (anyStrings)
                     CFStringAppend(result, CFSTR(", "));
                  else anyStrings = true;
                  CFStringAppend(result, str);
                  CFRelease(str);
               }
            }
         }
      }
      CFRelease(connections);
   }
   if (anyStrings)
      return result;
   
   // Here, either the endpoint had no connections, or we failed to obtain names for any of them.
   return EndpointName(endpoint, false);
}

// ------------------------------------------------------------------------------------------------------

array < CoreMidiOutput::Destination > CoreMidiOutput::get_destinations()
{
   
   array < CoreMidiOutput::Destination > destinations;
   
   ItemCount iEndpointCount = MIDIGetNumberOfDestinations();
   
   printf("[AUNotePlayer] %i MIDI destinations\n", (int)iEndpointCount);
   
   for (int iEndpoint =0; iEndpoint < (int) iEndpointCount; iEndpoint++)
   {
      
      MIDIEndpointRef endpoint = MIDIGetDestination(iEndpoint);
      
      CFStringRef name = ConnectedEndpointName(endpoint);
      
      char szBuffer[256];
      
      CFStringGetCString(name, szBuffer, 256, kCFStringEncodingUTF8);
      
      CFRelease(name);
      
      printf("[AUNotePlayer]  %i - '%s'\n", iEndpoint, szBuffer);
      
      Destination destination;
      
      destination.m_endpoint = endpoint;
      
      destination.m_strName = szBuffer;
      
      destinations.add(destination);
      
   }
   
   return destinations;
   
}


CoreMidiOutput::CoreMidiOutput(::aura::application * papp, string driver) :
::object(papp),
::music::midi::message_out(papp),
OutputBase()
{
   
   mach_timebase_info(&sTimebaseInfo);

   m_packetlist = NULL;
   
   m_port = NULL;
   
   OSStatus result = MIDIOutputPortCreate(m_client, CFSTR("ariaport"), &m_port);

   if (result != 0)
   {
      
      string str;
      
      str.Format("MIDIOutputPortCreate failed with code %i\n", (int) result);
      
      throw resource_exception(get_app(), str);
      
   }

   bool bFound = false;
   
   auto destinations  = get_destinations();
   
   for (unsigned int n = 0; n < destinations.size(); n++)
   {
      
      if (destinations[n].m_strName == "sforzando")
      {
         
         m_endpoint = destinations[n].m_endpoint;
         
         bFound = true;
         
         return;
         
      }
      
   }
   
   if(!bFound && driver != "sforzando")
   {
   
      for (unsigned int n = 0; n < destinations.size(); n++)
      {
         
         if (destinations[n].m_strName == driver)
         {
         
            m_endpoint = destinations[n].m_endpoint;
         
            bFound = true;
         
            return;
      
         }
         
      }
      
   }

   if (!bFound)
   {
      
      //wxMessageBox(_("Unknown MIDI port : ") + driver);
      
      m_endpoint = MIDIGetDestination(0);
      
   }
   
}


void CoreMidiOutput::reset_all_controllers()
{

   ::music::midi::message_out::reset_all_controllers();
   
}


CoreMidiOutput::~CoreMidiOutput()
{
   
   MIDIPortDispose (m_port);
   
}


void CoreMidiOutput::note_on(int channel, unsigned char note, unsigned char volume)
{

   Byte message[3];
   
   message[0] = 0x90 | channel;
   
   message[1] = note;
   
   message[2] = volume;
   
   add_short_message(message, 3);
   
}


void CoreMidiOutput::note_off(int channel, unsigned char note, unsigned char velocity)
{
   
   Byte message[3];
   
   message[0] = 0x80 | channel;
   
   message[1] = note;
   
   message[2] = velocity;
   
   add_short_message(message, 3);
   
}


void CoreMidiOutput::program_change(int channel, unsigned char instrument)
{
   
   Byte message[2];
   
   message[0] = 0xC0 | channel;
   
   message[1] = instrument;
   
   add_short_message(message, 2);
   
}


void CoreMidiOutput::step()
{
   
   OSStatus result = MIDISend(m_port, m_endpoint, m_packetlist);
   
   if (result != 0)
   {
      
      fprintf(stderr, "MIDISend failed!!\n");
      
   }

   m_packetlist = NULL;
   
}


void CoreMidiOutput::start()
{
   
   m_ui64Start =AudioGetCurrentHostTime();
   
}

void CoreMidiOutput::add_short_message(Byte * pmessage, int iSize)
{
   
   MIDITimeStamp timestamp = m_ui64Start + nano_to_absolute((m_ps->m_timeFile - m_ps->m_timeFileStart + 100.0) * 1000000.0);
   
   if(m_packetlist == NULL)
   {
   
      m_packetlist = (MIDIPacketList *) m_buffer;
   
      m_packet = MIDIPacketListInit(m_packetlist);
      
   }
   
   m_packet = MIDIPacketListAdd(m_packetlist, sizeof(m_buffer), m_packet, timestamp, iSize, pmessage);

}


void CoreMidiOutput::control_change(int channel, unsigned char controller, unsigned char value)
{
   
   Byte message[3];
   
   message[0] = 0xB0 | channel;
   
   message[1] = controller;
   
   message[2] = value;

   add_short_message(message, 3);
   
}


void CoreMidiOutput::pitch_bend(int channel, unsigned short value)
{

   int c1 = (value & 0x7F);

   int c2 = ((value >> 7) & 0x7F);
   
   Byte message[3];
   
   message[0] = 0xE0 | channel;
   
   message[1] = c1;
   
   message[2] = c2;
   
   add_short_message(message, 3);
   
}


