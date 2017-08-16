

CLASS_DECL_AURA void sleep(const duration & duration)
{
   
   timespec t;
   
   t.tv_sec = duration.m_iSeconds;
   
   t.tv_nsec = duration.m_iNanoseconds;
   
   ::nanosleep(&t, NULL);

}





string & get_command_line_string()
{
   
   static string g_strCommandLine;
   
   return g_strCommandLine;
   
}


void set_command_line_dup(const char * psz)
{
   
   get_command_line_string()     = psz;
   
}


string get_command_line_dup()
{
   
   return get_command_line_string();
   
}



