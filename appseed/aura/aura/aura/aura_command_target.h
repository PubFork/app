#pragma once


class CLASS_DECL_AURA command_target:
   virtual public ::message::receiver,
   virtual public ::message::sender
{
public:


   command_target();
   command_target(::aura::application * papp);
   virtual ~command_target();


   template < class T >
   void connect_command_probe(const char * pszId,void (T::*pfn)(::message::message *))
   {

      connect_command_probe(id(pszId),pfn);

   }


   template < class T >
   void connect_command(const char * pszId,void (T::*pfn)(::message::message *))
   {

      connect_command(id(pszId),pfn);

   }


   template < class T >
   void connect_command_probe(id id,void (T::*pfn)(::message::message *))
   {

      connect_command_probe(id, dynamic_cast < T * > (this), pfn);

   }


   template < class T >
   void connect_command(id id,void (T::*pfn)(::message::message *))
   {
   
      connect_command(id, dynamic_cast < T * > (this), pfn);

   }

   template < class T >
   void connect_command_probe(id id, T * p, void (T::*pfn)(::message::message *))
   {
      
      ::message::id messageid;

      messageid = ::message::type_command_probe;

      messageid = id;

      add_route(messageid, p, pfn);

   }
   
   
   template < class T >
   void connect_command(id id,T * p,void (T::*pfn)(::message::message *))
   {

      ::message::id messageid;

      messageid = ::message::type_command;

      messageid = id;

      add_route(messageid, p, pfn);

   }
   
   
   //template < class T >
   //bool connect_update_cmd_range_ui(int32_t iStart,int32_t iEnd,void (T::*pfn)(::message::message *))
   //{
   //   command_signalrange signalrange;
   //   ::message::senderid * pid;
   //   signalrange.m_iStart = iStart;
   //   signalrange.m_iEnd = iEnd;
   //   pid = m_signalidaCommand.get(&signalrange);
   //   if (!m_dispatchUpdateCmdUi.AddMessageHandler(pid, dynamic_cast <T *> (this), pfn, true))
   //   {
   //      return false;
   //   }
   //   return true;
   //}
   
   
   //template < class T >
   //bool connect_command_range(int32_t iStart,int32_t iEnd,void (T::*pfn)(::message::message *))
   //{
   //   command_signalrange signalrange;
   //   ::message::senderid * pid;
   //   signalrange.m_iStart = iStart;
   //   signalrange.m_iEnd = iEnd;
   //   pid = m_signalidaCommand.get(&signalrange);
   //   if (!m_dispatchCommand.AddMessageHandler(pid, dynamic_cast <T *> (this), pfn, true))
   //   {
   //      return false;
   //   }
   //   return true;
   //}

   
   virtual void _001SendCommand(::user::command * pcommand);
   virtual void _001SendCommandProbe(::user::command * pcommand);

   virtual void on_simple_command(::user::command * pcommand);
   virtual bool _001HasCommandHandler(::user::command * pcommand);
   virtual void on_simple_command_probe(::user::command * pcommand);

   //virtual bool on_simple_command_probe(::user::command * pcommand);
   virtual void _001OnCmdMsg(::user::command * pcommand);
   //virtual bool _001HasCommandHandler(const char * pszId);

   //void get_command_signal_array(::user::command::e_type etype,::dispatch::message::sender_item_ptr_array & signalptra,id id);


   virtual void install_message_routing(::message::sender * psender);

   void CommonConstruct();

   void BeginWaitCursor();
   void EndWaitCursor();
   void RestoreWaitCursor();       // call after messagebox


   virtual bool handle(::user::command * pcommand);


   // Overridables
   // route and dispatch standard command message types
   //   (more sophisticated than OnCommand)
   //   virtual bool _001OnCmdMsg(::user::command * pcommand);





};



