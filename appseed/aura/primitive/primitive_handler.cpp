#include "framework.h"


handler::handler(::thread * pthread) :
   object(pthread->get_app())
{

   defer_create_mutex();

   m_pthread = pthread;

   m_varTopicQuery.propset().set_app(pthread->get_app());

}


handler::~handler()
{
   
}


void handler::handle(::command::command * pcommand)
{

   m_pthread->post_object(message_system, system_message_command, pcommand);

}


void handler::handle(::create * pcreate)
{
   
   m_pthread->post_object(message_system, system_message_command, pcreate);
   
}


void handler::handle(::e_command ecommand)
{

   handle(canew(::command::command(get_app(),ecommand)));

}


void handler::on_handle(::command::command * pcommand)
{

   m_pthread->handle_command(pcommand);

}


void handler::on_handle(::create * pcreate)
{
   
   m_pthread->on_create(pcreate);
   
}


void handler::merge(::command::command * pcommand)
{
   
   sp(::create) pcreate = pcommand;
   
   if(pcreate != NULL)
   {
   
      m_spcommandline = pcreate->m_spCommandLine;
   
      if(!pcreate->m_spCommandLine->m_varFile.is_empty())
      {
      
         if(m_varTopicFile != pcreate->m_spCommandLine->m_varFile)
         {
         
            if(m_varTopicFile.is_empty())
            {
            
               m_varTopicFile = pcreate->m_spCommandLine->m_varFile;
            
            }
            else
            {
            
               m_varTopicFile.stra().add(pcreate->m_spCommandLine->m_varFile.stra());
            
            }
         
         }
      
      }
   
      m_varTopicQuery.propset().merge(pcreate->m_spCommandLine->m_varQuery.propset());
   
   }
   
}


void handler::merge(::handler * phandler)
{

   if(phandler == NULL || phandler == this)
   {
      
      return;
      
   }

   if(!phandler->m_varTopicFile.is_empty())
   {
      
      m_varTopicFile.stra().add_unique(phandler->m_varTopicFile.stra());
      
   }
   
   m_varTopicQuery.propset().merge(phandler->m_varTopicQuery.propset());

}

   
bool handler::is_thread()
{
   
   return true;
   
}

   
var & handler::property(const char * pszKey)
{
   
   string strKey(pszKey);
   
   if(strKey.compare_ci("file") == 0)
   {
      
      if(m_varTopicFile.is_empty())
      {
         
         if(!m_varTopicQuery["file"].is_empty())
         {
            
            m_varTopicFile = m_varTopicQuery["file"];
            
         }
         
      }
      
      return m_varTopicFile;
      
   }
   else
   {
      
      return m_varTopicQuery[pszKey];
      
   }
   
}

   
bool handler::has_property(const char * pszKey)
{
   
   string strKey(pszKey);
   
   if(strKey.compare_ci("file") == 0)
   {
      
      if(m_varTopicFile.is_empty())
      {
         
         if(m_varTopicQuery["file"].is_empty())
         {
            
            return false;
            
         }
         
      }
      
      return true;
      
   }
   else
   {
      
      return m_varTopicQuery.has_property(pszKey);
      
   }

}


void handler::record(::command::command * pcommand)
{

   synch_lock sl(m_pmutex);
         
   m_ptraHistory.add(pcommand);
         
   m_straHistory.add(pcommand->get_description());
         
}
   
   
