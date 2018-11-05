#pragma once



namespace music
{

   namespace midi_core_midi
   {


      class CLASS_DECL_VERIWELL_MULTIMEDIA_MUSIC_MIDI_CORE_MIDI sequence_thread : 
         virtual public ::music::midi::sequence_thread
      {
      public:

         
         sequence_thread(sp(::aura::application) papp);
         virtual ~sequence_thread();


         void install_message_routing(::message::sender * pinterface) override;

         virtual ::music::midi::sequence * get_sequence() override;
         virtual void Stop(imedia_time msEllapse) override;

         bool PostMidiSequenceEvent(::music::midi::sequence * pseq, ::music::midi::sequence::e_event event);

         bool PostMidiSequenceEvent(::music::midi::sequence * pseq, ::music::midi::sequence::e_event event, LPMIDIHDR lpmh);

         void PostNotifyEvent(::music::midi::player::e_notify_event eevent);

         void PrerollAndWait(double rate = 0.0) override;
         void PrerollRateAndWait(imedia_position tkStart) override;
         void PlayRate(double dRate = 0.0) override;
         void Play(imedia_position tkStart) override;
         void PostGMReset() override;
         void PostTempoChange() override;
         void SendTempoChange() override;

         void ExecuteCommand(::music::midi::player::command * pcommand) override;
         void _ExecuteCommand(::music::midi::player::command * pcommand) override;

         virtual bool init_thread() override;
         virtual void term_thread() override;

         DECL_GEN_SIGNAL(OnCommand);
         DECL_GEN_SIGNAL(OnMidiSequenceEvent);
         DECL_GEN_SIGNAL(OnRun);

      };


   } // namespace midi_core_midi


} // namespace music





