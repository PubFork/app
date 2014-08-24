#pragma once


namespace aura
{

   class CLASS_DECL_AURA message_queue:
      virtual public message_queue_listener
   {
   public:


      message_queue_listener *         m_plistener;


      message_queue(sp(::aura::application) papp);
      virtual ~message_queue();


      virtual bool create_message_queue(const char * pszName,::aura::message_queue_listener * plistener = NULL);


      virtual void message_handler(signal_details * pobj);
      virtual void message_queue_message_handler(signal_details * pobj);


      virtual bool message_queue_is_initialized();

      virtual bool message_queue_set_timer(uint_ptr uiId,DWORD dwMillis);

      virtual bool message_queue_del_timer(uint_ptr uiId);

      virtual bool message_queue_destroy();

   };


   typedef sp(message_queue) message_queue_sp;


} // namespace aura



















