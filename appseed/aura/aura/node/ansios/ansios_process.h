#pragma once


namespace ansios
{


   class CLASS_DECL_AURA process :
      virtual public ::process::process
   {
   public:


      process(::aura::application * papp);
      virtual ~process();


      virtual bool create_child_process(const char * pszCmdLine,bool bPiped,const char * pszDir = NULL,int32_t iPriorityClass = ::multithreading::priority_none) override;

      virtual bool has_exited() override;

      virtual void synch_elevated(const char * pszCmdLine,int iShow,const ::duration & durationTimeOut,bool * pbTimeOut) override;

   };


} // namespace ansios



