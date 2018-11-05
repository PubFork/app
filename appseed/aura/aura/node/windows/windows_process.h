#pragma once


namespace windows
{


   class CLASS_DECL_AURA process :
      virtual public ::process::process
   {
   public:


      PROCESS_INFORMATION     m_pi;
      STARTUPINFOW             m_si;


      process(::aura::application * papp);
      virtual ~process();


      virtual bool create_child_process(const char * pszCmdLine,bool bPiped,const char * pszDir = NULL,int32_t iPriorityClass = ::multithreading::priority_none) override;

      virtual bool has_exited() override;

      virtual bool synch_elevated(const char * pszCmdLine,int iShow,const ::duration & durationTimeOut,bool * pbTimeOut) override;

      virtual bool kill() override;

   };


} // namespace windows
