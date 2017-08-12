#pragma once



class CLASS_DECL_AURA handler :
   virtual public ::object
{
public:

   
   /// accumulatted as handler history passes
   spa(::command::command)    m_ptraHistory;
   
   
   /// pending commands to run - handler doesn't "run" THEM. Let thread does it.
   // spa(::command)          m_ptra;
   
   stringa                    m_straHistory;

   /// accumulatted, reset, set, or clear as handler history passes
   var                        m_varTopicFile;

   /// accumulatted, reset, set, or clear as handler history passes
   var                        m_varTopicQuery;
   
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


   virtual void handle(::command::command * pcommand);
   
   virtual void handle(::create * pcreate);

   virtual void handle(::e_command ecommand);

   virtual void on_handle(::command::command * pcommand);
   
   virtual void on_handle(::create * pcreate);

   virtual bool is_thread();

   virtual var & property(const char * pszKey);
   
   virtual bool has_property(const char * pszKey);

   virtual void merge(::command::command * pcommand);
   
   virtual void merge(::handler * phandler);

   virtual void record(::command::command * pcommand);
   
   
};


