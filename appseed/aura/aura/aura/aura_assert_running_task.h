#pragma once


namespace aura
{


   class CLASS_DECL_AURA assert_running_task:
      virtual public ::thread
   {
   public:


      string               m_strAppId;
      ::duration           m_durationCheckPeriod;


      assert_running_task(::aura::application * papp,const string & strAppId);
      virtual ~assert_running_task();


      virtual void run() override;


   };


} // namespace aura



















