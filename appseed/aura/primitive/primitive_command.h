#pragma once


namespace command
{
   
   
   class CLASS_DECL_AURA command :
      virtual public ::object
   {
   public:


      e_command                  m_ecommand;
      string                     m_strCommandLine;
      stringa                    m_straFile;
            
 
      command();
      command(const command & command);
      command(::aura::application * papp);
      command(::aura::application * papp, e_command ecommand);
      virtual ~command();

   
      virtual var run();
   
      virtual void on_request(::create * pcreate);
 
      virtual string get_description();
   
      command & operator = (const command & command);
      

   };


} // namespace command



