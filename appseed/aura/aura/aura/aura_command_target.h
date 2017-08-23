#pragma once


class CLASS_DECL_AURA command_target_interface:
   virtual public ::message::receiver,
   virtual public ::message::sender
{
public:


   //class CLASS_DECL_AURA command_signalid :
   //   public signalid
   //{
   //public:


   //   id m_id;


   //   command_signalid() { }
   //   virtual ~command_signalid();


   //   virtual bool is_equal(signalid * pidParam)
   //   {

   //      command_signalid * pid = dynamic_cast < command_signalid * > (pidParam);

   //      if(pid == NULL)
   //         return false;

   //      return pid->m_id == m_id;

   //   };



   //   virtual bool matches(signalid * pidParam)
   //   {
   //      
   //      command_signalid * pid = dynamic_cast < command_signalid * > (pidParam);
   //      
   //      if(pid == NULL)
   //         return false;

   //      return pid->m_id == m_id;

   //   }

   //   
   //   virtual signalid * copy()
   //   {
   //      
   //      command_signalid * pid = canew(command_signalid());
   //      
   //      pid->m_id = m_id;

   //      return pid;

   //   }

   //};


   //class CLASS_DECL_AURA command_signalrange: public signalid
   //{
   //public:


   //   index m_iStart;
   //   index m_iEnd;


   //   command_signalrange() { }
   //   virtual ~command_signalrange();


   //   virtual bool is_equal(signalid * pidParam)
   //   {
   //      
   //      command_signalrange * prange = dynamic_cast < command_signalrange * > (pidParam);
   //      
   //      if(prange == NULL)
   //         return false;

   //      return prange->m_iStart == m_iStart && prange->m_iEnd == m_iEnd;

   //   }


   //   virtual bool matches(signalid * pidParam)
   //   {

   //      command_signalid * pid = dynamic_cast < command_signalid * > (pidParam);

   //      if(pid == NULL)
   //         return false;
   //      return pid->m_id >= m_iStart && pid->m_id <= m_iEnd;

   //   }


   //   virtual signalid * copy()
   //   {
   //   
   //      command_signalrange * pid = canew(command_signalrange());
   //      
   //      pid->m_iStart = m_iStart;

   //      pid->m_iEnd = m_iEnd;

   //      return pid;

   //   }

   //};


   //::message::senderid_array m_signalidaCommand;

   //
   //::dispatch  m_dispatchUpdateCmdUi;
   //::dispatch  m_dispatchCommand;

   
   command_target_interface();
   command_target_interface(::aura::application * papp);


   template < class T >
   bool connect_update_cmd_ui(const char * pszId,void (T::*pfn)(::message::message *))
   {

      return connect_update_cmd_ui(id(pszId),pfn);

   }


   template < class T >
   bool connect_command(const char * pszId,void (T::*pfn)(::message::message *))
   {

      return connect_command(id(pszId),pfn);

   }


   template < class T >
   bool connect_update_cmd_ui(id id,void (T::*pfn)(::message::message *))
   {

      command_signalid signalid;

      ::message::senderid * pid;

      signalid.m_id = id;

      pid = m_signalidaCommand.get(&signalid);

      if (!m_dispatchUpdateCmdUi.AddMessageHandler(pid, dynamic_cast <T *> (this), pfn, true))
      {

         return false;

      }

      return true;

   }


   template < class T >
   bool connect_command(id id,void (T::*pfn)(::message::message *))
   {
      command_signalid signalid;
      ::message::senderid * pid;
      signalid.m_id = id;
      pid = m_signalidaCommand.get(&signalid);
      if (!m_dispatchCommand.AddMessageHandler(pid, dynamic_cast <T *> (this), pfn, true))
      {
         return false;
      }
      return true;
   }
   template < class T >
   bool connect_update_cmd_ui(id id,T * psignalizable, void (T::*pfn)(::message::message *))
   {
      command_signalid signalid;
      ::message::senderid * pid;
      signalid.m_id = id;
      pid = m_signalidaCommand.get(&signalid);
      if (!m_dispatchUpdateCmdUi.AddMessageHandler(pid, psignalizable, pfn, true))
      {
         return false;
      }
      return true;
   }
   
   
   template < class T >
   bool connect_command(id id,T * psignalizable,void (T::*pfn)(::message::message *))
   {
      command_signalid signalid;
      ::message::senderid * pid;
      signalid.m_id = id;
      pid = m_signalidaCommand.get(&signalid);
      if (!m_dispatchCommand.AddMessageHandler(pid, psignalizable, pfn, true))
      {
         return false;
      }
      return true;
   }
   
   
   template < class T >
   bool connect_update_cmd_range_ui(int32_t iStart,int32_t iEnd,void (T::*pfn)(::message::message *))
   {
      command_signalrange signalrange;
      ::message::senderid * pid;
      signalrange.m_iStart = iStart;
      signalrange.m_iEnd = iEnd;
      pid = m_signalidaCommand.get(&signalrange);
      if (!m_dispatchUpdateCmdUi.AddMessageHandler(pid, dynamic_cast <T *> (this), pfn, true))
      {
         return false;
      }
      return true;
   }
   
   
   template < class T >
   bool connect_command_range(int32_t iStart,int32_t iEnd,void (T::*pfn)(::message::message *))
   {
      command_signalrange signalrange;
      ::message::senderid * pid;
      signalrange.m_iStart = iStart;
      signalrange.m_iEnd = iEnd;
      pid = m_signalidaCommand.get(&signalrange);
      if (!m_dispatchCommand.AddMessageHandler(pid, dynamic_cast <T *> (this), pfn, true))
      {
         return false;
      }
      return true;
   }

   
   virtual void _001SendCommand(::user::command * pcommand);
   virtual void _001SendUpdateCommand(::user::command * pcommand);

   virtual void on_simple_action(::user::command * pcommand);
   virtual bool _001HasCommandHandler(::user::command * pcommand);
   virtual void on_simple_update(command_ui * pcommandui);

   //virtual bool on_simple_update(command_ui * pcommandui);
   virtual void _001OnCmdMsg(::user::command * pcommand);
   //virtual bool _001HasCommandHandler(const char * pszId);

   //void get_command_signal_array(::user::command::e_type etype,::dispatch::message::sender_item_ptr_array & signalptra,id id);


   virtual void install_message_routing(::message::sender * psender);


};



class CLASS_DECL_AURA command_target:
   virtual public command_target_interface
{
public:
   command_target();
   command_target(::aura::application * papp);

   void CommonConstruct();

   void BeginWaitCursor();
   void EndWaitCursor();
   void RestoreWaitCursor();       // call after messagebox


   virtual bool handle(::user::command * pcommand);


   // Overridables
   // route and dispatch standard command message types
   //   (more sophisticated than OnCommand)
   //   virtual bool _001OnCmdMsg(::user::command * pcommand);


   // Implementation
public:
   virtual ~command_target() = 0;


};








