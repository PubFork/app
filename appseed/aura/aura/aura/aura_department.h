#pragma once


namespace aura
{

   
   class CLASS_DECL_AURA department :
      virtual public ::message::receiver
   {
   public:


      department(application * papp);
      virtual ~department();


      void construct(::aura::application * papp);
      virtual void connect_to_application_signal();

      virtual bool process_init();

      virtual bool init();
      virtual bool init1();
      virtual bool init2();
      virtual bool init3();
      virtual bool init_instance();

      virtual void term_instance();
      virtual bool term3();
      virtual bool term2();
      virtual bool term1();
      virtual void term();

      void on_application_message(::message::message * pobj);
      

   };


} // namespace aura



