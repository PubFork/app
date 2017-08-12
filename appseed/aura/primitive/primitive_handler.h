#pragma once



class CLASS_DECL_AURA handler :
   virtual public ::object
{
public:

   
   spa(::command)             m_ptraHistory; // accumulatted as handler history passes
   //spa(::command)        m_ptra; // pending commands to be run - handler does not "run" forks, let it's own thread/process run it
   stringa                    m_straHistory;


   var                        m_varTopicFile;  // accumulatted, reset, set, or clear as handler history passes
   var                        m_varTopicQuery; // accumulatted, reset, set, or clear as handler history passes
   //manual_reset_event               m_ev;
   sp(command_line)           m_spcommandline;
   ::thread *                 m_pthread;


   handler(::thread * pthread);
   virtual ~handler();

   virtual int64_t add_ref()
   {

      return ::object::add_ref();

   }
   virtual int64_t dec_ref()
   {

      return ::object::dec_ref();

   }


   virtual void handle(::command * pcommand);

   virtual void handle(::e_command ecommand);

   virtual void on_handle(::command * pcommand);

   virtual bool is_thread();

   virtual var & property(const char * pszKey);
   
   virtual bool has_property(const char * pszKey);

   virtual void merge(::command * pcommand);
   
   virtual void merge(::handler * phandler);

   virtual void record(::command * pcommand);
   
};


